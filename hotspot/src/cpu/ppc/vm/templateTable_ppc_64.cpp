/*
 * Copyright (c) 2014, 2017 Oracle and/or its affiliates. All rights reserved.
 * Copyright 2013, 2017 SAP AG. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */
// This file is a derivative work resulting from (and including) modifications
// made by Azul Systems, Inc.  The dates of such changes are 2013-2016.
// Copyright 2013-2016 Azul Systems, Inc.  All Rights Reserved.
//
// Please contact Azul Systems, 385 Moffett Park Drive, Suite 115, Sunnyvale,
// CA 94089 USA or visit www.azul.com if you need additional information or
// have any questions.

#include "precompiled.hpp"
#include "asm/macroAssembler.inline.hpp"
#include "interpreter/interpreter.hpp"
#include "interpreter/interpreterRuntime.hpp"
#include "interpreter/templateInterpreter.hpp"
#include "interpreter/templateTable.hpp"
#include "memory/universe.inline.hpp"
#include "oops/objArrayKlass.hpp"
#include "oops/oop.inline.hpp"
#include "prims/methodHandles.hpp"
#include "runtime/sharedRuntime.hpp"
#include "runtime/stubRoutines.hpp"
#include "runtime/synchronizer.hpp"
#include "utilities/macros.hpp"

#ifndef CC_INTERP

#undef __
#define __ _masm->

// ============================================================================
// Misc helpers

// Do an oop store like *(base + index) = val OR *(base + offset) = val
// (only one of both variants is possible at the same time).
// Index can be noreg.
// Kills:
//   Rbase, Rtmp
static void do_oop_store(InterpreterMacroAssembler* _masm,
                         Register           Rbase,
                         RegisterOrConstant offset,
                         Register           Rval,         // Noreg means always null.
                         Register           Rtmp1,
                         Register           Rtmp2,
                         Register           Rtmp3,
                         BarrierSet::Name   barrier,
                         bool               precise,
                         bool               check_null) {
  assert_different_registers(Rtmp1, Rtmp2, Rtmp3, Rval, Rbase);

  switch (barrier) {
#if INCLUDE_ALL_GCS
    case BarrierSet::G1SATBCT:
    case BarrierSet::G1SATBCTLogging:
      {
        // Load and record the previous value.
        __ g1_write_barrier_pre(Rbase, offset,
                                Rtmp3, /* holder of pre_val ? */
                                Rtmp1, Rtmp2, false /* frame */);

        Label Lnull, Ldone;
        if (Rval != noreg) {
          if (check_null) {
            __ cmpi(CCR0, Rval, 0);
            __ beq(CCR0, Lnull);
          }
          __ store_heap_oop_not_null(Rval, offset, Rbase, /*Rval must stay uncompressed.*/ Rtmp1);
          // Mark the card.
          if (!(offset.is_constant() && offset.as_constant() == 0) && precise) {
            __ add(Rbase, offset, Rbase);
          }
          __ g1_write_barrier_post(Rbase, Rval, Rtmp1, Rtmp2, Rtmp3, /*filtered (fast path)*/ &Ldone);
          if (check_null) { __ b(Ldone); }
        }

        if (Rval == noreg || check_null) { // Store null oop.
          Register Rnull = Rval;
          __ bind(Lnull);
          if (Rval == noreg) {
            Rnull = Rtmp1;
            __ li(Rnull, 0);
          }
          if (UseCompressedOops) {
            __ stw(Rnull, offset, Rbase);
          } else {
            __ st(Rnull, offset, Rbase);
          }
        }
        __ bind(Ldone);
      }
      break;
#endif // INCLUDE_ALL_GCS
    case BarrierSet::CardTableModRef:
    case BarrierSet::CardTableExtension:
      {
        Label Lnull, Ldone;
        if (Rval != noreg) {
          if (check_null) {
            __ cmpi(CCR0, Rval, 0);
            __ beq(CCR0, Lnull);
          }
          __ store_heap_oop_not_null(Rval, offset, Rbase, /*Rval should better stay uncompressed.*/ Rtmp1);
          // Mark the card.
          if (!(offset.is_constant() && offset.as_constant() == 0) && precise) {
            __ add(Rbase, offset, Rbase);
          }
          __ card_write_barrier_post(Rbase, Rval, Rtmp1);
          if (check_null) {
            __ b(Ldone);
          }
        }

        if (Rval == noreg || check_null) { // Store null oop.
          Register Rnull = Rval;
          __ bind(Lnull);
          if (Rval == noreg) {
            Rnull = Rtmp1;
            __ li(Rnull, 0);
          }
          if (UseCompressedOops) {
            __ stw(Rnull, offset, Rbase);
          } else {
            __ st(Rnull, offset, Rbase);
          }
        }
        __ bind(Ldone);
      }
      break;
    case BarrierSet::ModRef:
    case BarrierSet::Other:
      ShouldNotReachHere();
      break;
    default:
      ShouldNotReachHere();
  }
}

// ============================================================================
// Platform-dependent initialization

void TemplateTable::pd_initialize() {
  // No ppc64 specific initialization.
}

Address TemplateTable::at_bcp(int offset) {
  // Not used on ppc.
  ShouldNotReachHere();
  return Address();
}

// Patches the current bytecode (ptr to it located in bcp)
// in the bytecode stream with a new one.
void TemplateTable::patch_bytecode(Bytecodes::Code new_bc, Register Rnew_bc, Register Rtemp, bool load_bc_into_bc_reg /*=true*/, int byte_no) {
  // With sharing on, may need to test method flag.
  if (!RewriteBytecodes) return;
  Label L_patch_done;

  switch (new_bc) {
    case Bytecodes::_fast_aputfield:
    case Bytecodes::_fast_bputfield:
    case Bytecodes::_fast_zputfield:
    case Bytecodes::_fast_cputfield:
    case Bytecodes::_fast_dputfield:
    case Bytecodes::_fast_fputfield:
    case Bytecodes::_fast_iputfield:
    case Bytecodes::_fast_lputfield:
    case Bytecodes::_fast_sputfield:
    {
      // We skip bytecode quickening for putfield instructions when
      // the put_code written to the constant pool cache is zero.
      // This is required so that every execution of this instruction
      // calls out to InterpreterRuntime::resolve_get_put to do
      // additional, required work.
      assert(byte_no == f1_byte || byte_no == f2_byte, "byte_no out of range");
      assert(load_bc_into_bc_reg, "we use bc_reg as temp");
      __ get_cache_and_index_at_bcp(Rtemp /* dst = cache */, 1);
      // ((*(cache+indices))>>((1+byte_no)*8))&0xFF:
#if defined(VM_LITTLE_ENDIAN)
      __ lbz(Rnew_bc, in_bytes(ConstantPoolCache::base_offset() + ConstantPoolCacheEntry::indices_offset()) + 1 + byte_no, Rtemp);
#else
      __ lbz(Rnew_bc, in_bytes(ConstantPoolCache::base_offset() + ConstantPoolCacheEntry::indices_offset()) + PPC64_ONLY(7) NOT_PPC64(3) - (1 + byte_no), Rtemp);
#endif
      __ cmpwi(CCR0, Rnew_bc, 0);
      __ li(Rnew_bc, (unsigned int)(unsigned char)new_bc);
      __ beq(CCR0, L_patch_done);
      // __ isync(); // acquire not needed
      break;
    }

    default:
      assert(byte_no == -1, "sanity");
      if (load_bc_into_bc_reg) {
        __ li(Rnew_bc, (unsigned int)(unsigned char)new_bc);
      }
  }

  if (JvmtiExport::can_post_breakpoint()) {
    Label L_fast_patch;
    __ lbz(Rtemp, 0, R14_bcp);
    __ cmpwi(CCR0, Rtemp, (unsigned int)(unsigned char)Bytecodes::_breakpoint);
    __ bne(CCR0, L_fast_patch);
    // Perform the quickening, slowly, in the bowels of the breakpoint table.
    __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::set_original_bytecode_at), R19_method, R14_bcp, Rnew_bc);
    __ b(L_patch_done);
    __ bind(L_fast_patch);
  }

  // Patch bytecode.
  __ stb(Rnew_bc, 0, R14_bcp);

  __ bind(L_patch_done);
}

// ============================================================================
// Individual instructions

void TemplateTable::nop() {
  transition(vtos, vtos);
  // Nothing to do.
}

void TemplateTable::shouldnotreachhere() {
  transition(vtos, vtos);
  __ stop("shouldnotreachhere bytecode");
}

void TemplateTable::aconst_null() {
  transition(vtos, atos);
  __ li(R17_tos, 0);
}

void TemplateTable::iconst(int value) {
  transition(vtos, itos);
  assert(value >= -1 && value <= 5, "");
  __ li(R17_tos, value);
}

void TemplateTable::lconst(int value) {
  transition(vtos, ltos);
  assert(value >= 0 && value <= 1, "");
  __ li(R17_tos, value);
#ifndef PPC64
  __ li(R30_tos2, 0);
#endif
}

void TemplateTable::fconst(int value) {
  transition(vtos, ftos);
#ifndef USE_SPE
  static float zero = 0.0;
  static float one  = 1.0;
  static float two  = 2.0;
#endif
  switch (value) {
    default: ShouldNotReachHere();
    case 0: {
#ifndef USE_SPE
      int simm16_offset = __ load_const_optimized(R11_scratch1, (address*)&zero, R0, true);
      __ lfs(F15_ftos, simm16_offset, R11_scratch1);
#else
      __ li(R17_tos, 0);
#endif
      break;
    }
    case 1: {
#ifndef USE_SPE
      int simm16_offset = __ load_const_optimized(R11_scratch1, (address*)&one, R0, true);
      __ lfs(F15_ftos, simm16_offset, R11_scratch1);
#else
      __ lis(R17_tos, 0x3f80);
#endif
      break;
    }
    case 2: {
#ifndef USE_SPE
      int simm16_offset = __ load_const_optimized(R11_scratch1, (address*)&two, R0, true);
      __ lfs(F15_ftos, simm16_offset, R11_scratch1);
#else
      __ lis(R17_tos, 0x4000);
#endif
      break;
    }
  }
}

void TemplateTable::dconst(int value) {
  transition(vtos, dtos);
  static double zero = 0.0;
  static double one  = 1.0;
  switch (value) {
    case 0: {
#ifndef USE_SPE
      int simm16_offset = __ load_const_optimized(R11_scratch1, (address*)&zero, R0, true);
      __ lfd(F15_ftos, simm16_offset, R11_scratch1);
#else
      __ li(R17_tos, 0);
      __ evmergelo(R17_tos, R17_tos, R17_tos);
#endif
      break;
    }
    case 1: {
#ifndef USE_SPE
      int simm16_offset = __ load_const_optimized(R11_scratch1, (address*)&one, R0, true);
      __ lfd(F15_ftos, simm16_offset, R11_scratch1);
#else
      __ lis(R17_tos, 0x3ff0);
      __ li(R11_scratch1, 0);
      __ evmergelo(R17_tos, R17_tos, R11_scratch1);
#endif
      break;
    }
    default: ShouldNotReachHere();
  }
}

void TemplateTable::bipush() {
  transition(vtos, itos);
  __ lbz(R17_tos, 1, R14_bcp);
  __ extsb(R17_tos, R17_tos);
}

void TemplateTable::sipush() {
  transition(vtos, itos);
  __ get_2_byte_integer_at_bcp(1, R17_tos, InterpreterMacroAssembler::Signed);
}

void TemplateTable::ldc(bool wide) {
  Register Rscratch1 = R11_scratch1,
           Rscratch2 = R12_scratch2,
           Rcpool    = R3_ARG1;

  transition(vtos, vtos);
  Label notInt, notClass, exit;

  __ get_cpool_and_tags(Rcpool, Rscratch2); // Set Rscratch2 = &tags.
  if (wide) { // Read index.
    __ get_2_byte_integer_at_bcp(1, Rscratch1, InterpreterMacroAssembler::Unsigned);
  } else {
    __ lbz(Rscratch1, 1, R14_bcp);
  }

  const int base_offset = ConstantPool::header_size() * wordSize;
  const int tags_offset = Array<u1>::base_offset_in_bytes();

  // Get type from tags.
  __ addi(Rscratch2, Rscratch2, tags_offset);
  __ lbzx(Rscratch2, Rscratch2, Rscratch1);

  __ cmpwi(CCR0, Rscratch2, JVM_CONSTANT_UnresolvedClass); // Unresolved class?
  __ cmpwi(CCR1, Rscratch2, JVM_CONSTANT_UnresolvedClassInError); // Unresolved class in error state?
  __ cror(/*CR0 eq*/2, /*CR1 eq*/4+2, /*CR0 eq*/2);

  // Resolved class - need to call vm to get java mirror of the class.
  __ cmpwi(CCR1, Rscratch2, JVM_CONSTANT_Class);
  __ crnor(/*CR0 eq*/2, /*CR1 eq*/4+2, /*CR0 eq*/2); // Neither resolved class nor unresolved case from above?
  __ beq(CCR0, notClass);

  __ li(R4, wide ? 1 : 0);
  call_VM(R17_tos, CAST_FROM_FN_PTR(address, InterpreterRuntime::ldc), R4);
  __ push(atos);
  __ b(exit);

  __ align(32, 12);
  __ bind(notClass);
  __ addi(Rcpool, Rcpool, base_offset);
  __ sli(Rscratch1, Rscratch1, LogBytesPerWord);
  __ cmpi(CCR0, Rscratch2, JVM_CONSTANT_Integer);
  __ bne(CCR0, notInt);
  __ lwax(R17_tos, Rcpool, Rscratch1);
  __ push(itos);
  __ b(exit);

  __ align(32, 12);
  __ bind(notInt);
#ifdef ASSERT
  // String and Object are rewritten to fast_aldc
  __ cmpi(CCR0, Rscratch2, JVM_CONSTANT_Float);
  __ asm_assert_eq("unexpected type", 0x8765);
#endif
#ifndef USE_SPE
  __ lfsx(F15_ftos, Rcpool, Rscratch1);
#else
  __ lwax(R17_tos, Rcpool, Rscratch1);
#endif
  __ push(ftos);

  __ align(32, 12);
  __ bind(exit);
}

// Fast path for caching oop constants.
void TemplateTable::fast_aldc(bool wide) {
  transition(vtos, atos);

  int index_size = wide ? sizeof(u2) : sizeof(u1);
  const Register Rscratch = R11_scratch1;
  Label resolved;

  // We are resolved if the resolved reference cache entry contains a
  // non-null object (CallSite, etc.)
  __ get_cache_index_at_bcp(Rscratch, 1, index_size);  // Load index.
  __ load_resolved_reference_at_index(R17_tos, Rscratch);
  __ cmpi(CCR0, R17_tos, 0);
  __ bne(CCR0, resolved);
  __ load_const_optimized(R3_ARG1, (int)bytecode());

  address entry = CAST_FROM_FN_PTR(address, InterpreterRuntime::resolve_ldc);

  // First time invocation - must resolve first.
  __ call_VM(R17_tos, entry, R3_ARG1);

  __ align(32, 12);
  __ bind(resolved);
  __ verify_oop(R17_tos);
}

void TemplateTable::ldc2_w() {
  transition(vtos, vtos);
  Label Llong, Lexit;
  Register Rindex = R11_scratch1,
           Rcpool = R12_scratch2,
           Rtag   = R3_ARG1;
  __ get_cpool_and_tags(Rcpool, Rtag);
  __ get_2_byte_integer_at_bcp(1, Rindex, InterpreterMacroAssembler::Unsigned);

  const int base_offset = ConstantPool::header_size() * wordSize;
  const int tags_offset = Array<u1>::base_offset_in_bytes();
  // Get type from tags.
  __ addi(Rcpool, Rcpool, base_offset);
  __ addi(Rtag, Rtag, tags_offset);

  __ lbzx(Rtag, Rtag, Rindex);

  __ sli(Rindex, Rindex, LogBytesPerWord);
  __ cmpi(CCR0, Rtag, JVM_CONSTANT_Double);
  __ bne(CCR0, Llong);
  // A double can be placed at word-aligned locations in the constant pool.
  // Check out Conversions.java for an example.
  // Also ConstantPool::header_size() is 20, which makes it very difficult
  // to double-align double on the constant pool. SG, 11/7/97
#ifndef USE_SPE
  __ lfdx(F15_ftos, Rcpool, Rindex);
#else
  __ evlddx_unaligned(R17_tos, Rcpool, Rindex, R0_SCRATCH);
#endif
  __ push(dtos);
  __ b(Lexit);

  __ bind(Llong);
#ifdef PPC64
  __ ldx(R17_tos, Rcpool, Rindex);
#else
  __ lwzx(R30_tos2, Rcpool, Rindex);
  __ addi(Rindex, Rindex, wordSize);
  __ lwzx(R17_tos, Rcpool, Rindex);
#endif
  __ push(ltos);

  __ bind(Lexit);
}

// Get the locals index located in the bytecode stream at bcp + offset.
void TemplateTable::locals_index(Register Rdst, int offset) {
  __ lbz(Rdst, offset, R14_bcp);
}

void TemplateTable::iload() {
  transition(vtos, itos);

  // Get the local value into tos
  const Register Rindex = R22_tmp2;
  locals_index(Rindex);

  // Rewrite iload,iload  pair into fast_iload2
  //         iload,caload pair into fast_icaload
  if (RewriteFrequentPairs) {
    Label Lrewrite, Ldone;
    Register Rnext_byte  = R3_ARG1,
             Rrewrite_to = R6_ARG4,
             Rscratch    = R11_scratch1;

    // get next byte
    __ lbz(Rnext_byte, Bytecodes::length_for(Bytecodes::_iload), R14_bcp);

    // if _iload, wait to rewrite to iload2. We only want to rewrite the
    // last two iloads in a pair. Comparing against fast_iload means that
    // the next bytecode is neither an iload or a caload, and therefore
    // an iload pair.
    __ cmpwi(CCR0, Rnext_byte, (unsigned int)(unsigned char)Bytecodes::_iload);
    __ beq(CCR0, Ldone);

    __ cmpwi(CCR1, Rnext_byte, (unsigned int)(unsigned char)Bytecodes::_fast_iload);
    __ li(Rrewrite_to, (unsigned int)(unsigned char)Bytecodes::_fast_iload2);
    __ beq(CCR1, Lrewrite);

    __ cmpwi(CCR0, Rnext_byte, (unsigned int)(unsigned char)Bytecodes::_caload);
    __ li(Rrewrite_to, (unsigned int)(unsigned char)Bytecodes::_fast_icaload);
    __ beq(CCR0, Lrewrite);

    __ li(Rrewrite_to, (unsigned int)(unsigned char)Bytecodes::_fast_iload);

    __ bind(Lrewrite);
    patch_bytecode(Bytecodes::_iload, Rrewrite_to, Rscratch, false);
    __ bind(Ldone);
  }

  __ load_local_int(R17_tos, Rindex, Rindex);
}

// Load 2 integers in a row without dispatching
void TemplateTable::fast_iload2() {
  transition(vtos, itos);

  __ lbz(R3_ARG1, 1, R14_bcp);
  __ lbz(R17_tos, Bytecodes::length_for(Bytecodes::_iload) + 1, R14_bcp);

  __ load_local_int(R3_ARG1, R11_scratch1, R3_ARG1);
  __ load_local_int(R17_tos, R12_scratch2, R17_tos);
  __ push_i(R3_ARG1);
}

void TemplateTable::fast_iload() {
  transition(vtos, itos);
  // Get the local value into tos

  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
  __ load_local_int(R17_tos, Rindex, Rindex);
}

// Load a local variable type long from locals area to TOS cache register.
// Local index resides in bytecodestream.
void TemplateTable::lload() {
  transition(vtos, ltos);

  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
#ifdef PPC64
  __ load_local_long(R17_tos, Rindex, Rindex);
#else
  __ load_local_long(R17_tos, R30_tos2, Rindex, Rindex);
#endif
}

void TemplateTable::fload() {
  transition(vtos, ftos);
  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
  __ load_local_float(NOT_USE_SPE(F15_ftos) USE_SPE_ONLY(R17_tos), Rindex, Rindex);
}

void TemplateTable::dload() {
  transition(vtos, dtos);
  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
  __ load_local_double(NOT_USE_SPE(F15_ftos) USE_SPE_ONLY(R17_tos), Rindex, Rindex);
}

void TemplateTable::aload() {
  transition(vtos, atos);

  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
  __ load_local_ptr(R17_tos, Rindex, Rindex);
}

void TemplateTable::locals_index_wide(Register Rdst) {
  // Offset is 2, not 1, because Lbcp points to wide prefix code.
  __ get_2_byte_integer_at_bcp(2, Rdst, InterpreterMacroAssembler::Unsigned);
}

void TemplateTable::wide_iload() {
  // Get the local value into tos.

  const Register Rindex = R11_scratch1;
  locals_index_wide(Rindex);
  __ load_local_int(R17_tos, Rindex, Rindex);
}

void TemplateTable::wide_lload() {
  transition(vtos, ltos);

  const Register Rindex = R11_scratch1;
  locals_index_wide(Rindex);
#ifdef PPC64
  __ load_local_long(R17_tos, Rindex, Rindex);
#else
  __ load_local_long(R17_tos, R30_tos2, Rindex, Rindex);
#endif
}

void TemplateTable::wide_fload() {
  transition(vtos, ftos);
  const Register Rindex = R11_scratch1;
  locals_index_wide(Rindex);
#ifndef USE_SPE
  __ load_local_float(F15_ftos, Rindex, Rindex);
#else
  __ load_local_float(R17_tos, Rindex, Rindex);
#endif

}

void TemplateTable::wide_dload() {
  transition(vtos, dtos);
  const Register Rindex = R11_scratch1;
  locals_index_wide(Rindex);
  __ load_local_double(NOT_USE_SPE(F15_ftos) USE_SPE_ONLY(R17_tos), Rindex, Rindex);
}

void TemplateTable::wide_aload() {
  transition(vtos, atos);

  const Register Rindex = R11_scratch1;
  locals_index_wide(Rindex);
  __ load_local_ptr(R17_tos, Rindex, Rindex);
}

void TemplateTable::iaload() {
  transition(itos, itos);

  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R5_ARG3;
  __ index_check(Rarray, R17_tos /* index */, LogBytesPerInt, Rtemp, Rload_addr);
  __ lwa(R17_tos, arrayOopDesc::base_offset_in_bytes(T_INT), Rload_addr);
}

void TemplateTable::laload() {
  transition(itos, ltos);

  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R5_ARG3;
  __ index_check(Rarray, R17_tos /* index */, LogBytesPerLong, Rtemp, Rload_addr);
#ifdef PPC64
  __ l(R17_tos, arrayOopDesc::base_offset_in_bytes(T_LONG), Rload_addr);
#else
  __ l(R17_tos, arrayOopDesc::base_offset_in_bytes(T_LONG) + BytesPerWord, Rload_addr);
  __ l(R30_tos2, arrayOopDesc::base_offset_in_bytes(T_LONG), Rload_addr);
#endif
}

void TemplateTable::faload() {
  transition(itos, ftos);

  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R5_ARG3;
  __ index_check(Rarray, R17_tos /* index */, LogBytesPerInt, Rtemp, Rload_addr);
#ifndef USE_SPE
  __ lfs(F15_ftos, arrayOopDesc::base_offset_in_bytes(T_FLOAT), Rload_addr);
#else
  __ lwa(R17_tos, arrayOopDesc::base_offset_in_bytes(T_FLOAT), Rload_addr);
#endif
}

void TemplateTable::daload() {
  transition(itos, dtos);

  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R5_ARG3;
  __ index_check(Rarray, R17_tos /* index */, LogBytesPerLong, Rtemp, Rload_addr);
#ifdef USE_SPE
  __ evldd_unaligned(R17_tos, arrayOopDesc::base_offset_in_bytes(T_DOUBLE), Rload_addr, R11_scratch1);
#else
  __ lfd(F15_ftos, arrayOopDesc::base_offset_in_bytes(T_DOUBLE), Rload_addr);
#endif
}

void TemplateTable::aaload() {
  transition(itos, atos);

  // tos: index
  // result tos: array
  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R5_ARG3;
  __ index_check(Rarray, R17_tos /* index */, UseCompressedOops ? 2 : LogBytesPerWord, Rtemp, Rload_addr);
  __ load_heap_oop(R17_tos, arrayOopDesc::base_offset_in_bytes(T_OBJECT), Rload_addr);
  __ verify_oop(R17_tos);
  //__ dcbt(R17_tos); // prefetch
}

void TemplateTable::baload() {
  transition(itos, itos);

  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R5_ARG3;
  __ index_check(Rarray, R17_tos /* index */, 0, Rtemp, Rload_addr);
  __ lbz(R17_tos, arrayOopDesc::base_offset_in_bytes(T_BYTE), Rload_addr);
  __ extsb(R17_tos, R17_tos);
}

void TemplateTable::caload() {
  transition(itos, itos);

  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R5_ARG3;
  __ index_check(Rarray, R17_tos /* index */, LogBytesPerShort, Rtemp, Rload_addr);
  __ lhz(R17_tos, arrayOopDesc::base_offset_in_bytes(T_CHAR), Rload_addr);
}

// Iload followed by caload frequent pair.
void TemplateTable::fast_icaload() {
  transition(vtos, itos);

  const Register Rload_addr = R3_ARG1,
                 Rarray     = R4_ARG2,
                 Rtemp      = R11_scratch1;

  locals_index(R17_tos);
  __ load_local_int(R17_tos, Rtemp, R17_tos);
  __ index_check(Rarray, R17_tos /* index */, LogBytesPerShort, Rtemp, Rload_addr);
  __ lhz(R17_tos, arrayOopDesc::base_offset_in_bytes(T_CHAR), Rload_addr);
}

void TemplateTable::saload() {
  transition(itos, itos);

  const Register Rload_addr = R11_scratch1,
                 Rarray     = R12_scratch2,
                 Rtemp      = R3_ARG1;
  __ index_check(Rarray, R17_tos /* index */, LogBytesPerShort, Rtemp, Rload_addr);
  __ lha(R17_tos, arrayOopDesc::base_offset_in_bytes(T_SHORT), Rload_addr);
}

void TemplateTable::iload(int n) {
  transition(vtos, itos);

  __ lwz(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
}

void TemplateTable::lload(int n) {
  transition(vtos, ltos);

#ifdef PPC64
  __ ld(R17_tos, Interpreter::local_offset_in_bytes(n + 1), R18_locals);
#else
  __ lwz(R30_tos2, Interpreter::local_offset_in_bytes(n + 1), R18_locals);
  __ lwz(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
#endif
}

void TemplateTable::fload(int n) {
  transition(vtos, ftos);
#ifndef USE_SPE
  __ lfs(F15_ftos, Interpreter::local_offset_in_bytes(n), R18_locals);
#else
  __ lwz(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
#endif
}

void TemplateTable::dload(int n) {
  transition(vtos, dtos);

#ifndef USE_SPE
  __ lfd(F15_ftos, Interpreter::local_offset_in_bytes(n + 1), R18_locals);
#else
  __ evldd_unaligned(R17_tos, Interpreter::local_offset_in_bytes(n + 1), R18_locals, R11_scratch1);
#endif
}

void TemplateTable::aload(int n) {
  transition(vtos, atos);

  __ l(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
}

void TemplateTable::aload_0() {
  transition(vtos, atos);
  // According to bytecode histograms, the pairs:
  //
  // _aload_0, _fast_igetfield
  // _aload_0, _fast_agetfield
  // _aload_0, _fast_fgetfield
  //
  // occur frequently. If RewriteFrequentPairs is set, the (slow)
  // _aload_0 bytecode checks if the next bytecode is either
  // _fast_igetfield, _fast_agetfield or _fast_fgetfield and then
  // rewrites the current bytecode into a pair bytecode; otherwise it
  // rewrites the current bytecode into _0 that doesn't do
  // the pair check anymore.
  //
  // Note: If the next bytecode is _getfield, the rewrite must be
  //       delayed, otherwise we may miss an opportunity for a pair.
  //
  // Also rewrite frequent pairs
  //   aload_0, aload_1
  //   aload_0, iload_1
  // These bytecodes with a small amount of code are most profitable
  // to rewrite.

  if (RewriteFrequentPairs) {

    Label Lrewrite, Ldont_rewrite;
    Register Rnext_byte  = R3_ARG1,
             Rrewrite_to = R6_ARG4,
             Rscratch    = R11_scratch1;

    // Get next byte.
    __ lbz(Rnext_byte, Bytecodes::length_for(Bytecodes::_aload_0), R14_bcp);

    // If _getfield, wait to rewrite. We only want to rewrite the last two bytecodes in a pair.
    __ cmpwi(CCR0, Rnext_byte, (unsigned int)(unsigned char)Bytecodes::_getfield);
    __ beq(CCR0, Ldont_rewrite);

    __ cmpwi(CCR1, Rnext_byte, (unsigned int)(unsigned char)Bytecodes::_fast_igetfield);
    __ li(Rrewrite_to, (unsigned int)(unsigned char)Bytecodes::_fast_iaccess_0);
    __ beq(CCR1, Lrewrite);

    __ cmpwi(CCR0, Rnext_byte, (unsigned int)(unsigned char)Bytecodes::_fast_agetfield);
    __ li(Rrewrite_to, (unsigned int)(unsigned char)Bytecodes::_fast_aaccess_0);
    __ beq(CCR0, Lrewrite);

    __ cmpwi(CCR1, Rnext_byte, (unsigned int)(unsigned char)Bytecodes::_fast_fgetfield);
    __ li(Rrewrite_to, (unsigned int)(unsigned char)Bytecodes::_fast_faccess_0);
    __ beq(CCR1, Lrewrite);

    __ li(Rrewrite_to, (unsigned int)(unsigned char)Bytecodes::_fast_aload_0);

    __ bind(Lrewrite);
    patch_bytecode(Bytecodes::_aload_0, Rrewrite_to, Rscratch, false);
    __ bind(Ldont_rewrite);
  }

  // Do actual aload_0 (must do this after patch_bytecode which might call VM and GC might change oop).
  aload(0);
}

void TemplateTable::istore() {
  transition(itos, vtos);

  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
  __ store_local_int(R17_tos, Rindex);
}

void TemplateTable::lstore() {
  transition(ltos, vtos);
  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
#ifdef PPC64
  __ store_local_long(R17_tos, Rindex);
#else
  __ store_local_long(R17_tos, R30_tos2, Rindex);
#endif
}

void TemplateTable::fstore() {
  transition(ftos, vtos);
  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
  __ store_local_float(NOT_USE_SPE(F15_ftos) USE_SPE_ONLY(R17_tos), Rindex);

}

void TemplateTable::dstore() {
  transition(dtos, vtos);
  const Register Rindex = R11_scratch1;
  locals_index(Rindex);
  __ store_local_double(NOT_USE_SPE(F15_ftos) USE_SPE_ONLY(R17_tos), Rindex);
}

void TemplateTable::astore() {
  transition(vtos, vtos);

  const Register Rindex = R11_scratch1;
  __ pop_ptr();
  __ verify_oop_or_return_address(R17_tos, Rindex);
  locals_index(Rindex);
  __ store_local_ptr(R17_tos, Rindex);
}

void TemplateTable::wide_istore() {
  transition(vtos, vtos);

  const Register Rindex = R11_scratch1;
  __ pop_i();
  locals_index_wide(Rindex);
  __ store_local_int(R17_tos, Rindex);
}

void TemplateTable::wide_lstore() {
  transition(vtos, vtos);

  const Register Rindex = R11_scratch1;
  __ pop_l();
  locals_index_wide(Rindex);
#ifdef PPC64
  __ store_local_long(R17_tos, Rindex);
#else
  __ store_local_long(R17_tos, R30_tos2, Rindex);
#endif
}

void TemplateTable::wide_fstore() {
  transition(vtos, vtos);

  const Register Rindex = R11_scratch1;
  __ pop_f();
  locals_index_wide(Rindex);
  __ store_local_float(NOT_USE_SPE(F15_ftos) USE_SPE_ONLY(R17_tos), Rindex);
}

void TemplateTable::wide_dstore() {
  transition(vtos, vtos);

  const Register Rindex = R11_scratch1;
  __ pop_d();
  locals_index_wide(Rindex);
  __ store_local_double(NOT_USE_SPE(F15_ftos) USE_SPE_ONLY(R17_tos), Rindex);
}

void TemplateTable::wide_astore() {
  transition(vtos, vtos);

  const Register Rindex = R11_scratch1;
  __ pop_ptr();
  __ verify_oop_or_return_address(R17_tos, Rindex);
  locals_index_wide(Rindex);
  __ store_local_ptr(R17_tos, Rindex);
}

void TemplateTable::iastore() {
  transition(itos, vtos);

  const Register Rindex      = R3_ARG1,
                 Rstore_addr = R4_ARG2,
                 Rarray      = R5_ARG3,
                 Rtemp       = R6_ARG4;
  __ pop_i(Rindex);
  __ index_check(Rarray, Rindex, LogBytesPerInt, Rtemp, Rstore_addr);
  __ stw(R17_tos, arrayOopDesc::base_offset_in_bytes(T_INT), Rstore_addr);
  }

void TemplateTable::lastore() {
  transition(ltos, vtos);

  const Register Rindex      = R3_ARG1,
                 Rstore_addr = R4_ARG2,
                 Rarray      = R5_ARG3,
                 Rtemp       = R6_ARG4;
  __ pop_i(Rindex);
  __ index_check(Rarray, Rindex, LogBytesPerLong, Rtemp, Rstore_addr);
#ifdef PPC64
  __ st(R17_tos, arrayOopDesc::base_offset_in_bytes(T_LONG), Rstore_addr);
#else
  __ st(R17_tos, arrayOopDesc::base_offset_in_bytes(T_LONG) + BytesPerWord, Rstore_addr);
  __ st(R30_tos2, arrayOopDesc::base_offset_in_bytes(T_LONG), Rstore_addr);
#endif
  }

void TemplateTable::fastore() {
  transition(ftos, vtos);

  const Register Rindex      = R3_ARG1,
                 Rstore_addr = R4_ARG2,
                 Rarray      = R5_ARG3,
                 Rtemp       = R6_ARG4;
  __ pop_i(Rindex);
  __ index_check(Rarray, Rindex, LogBytesPerInt, Rtemp, Rstore_addr);
#ifndef USE_SPE
  __ stfs(F15_ftos, arrayOopDesc::base_offset_in_bytes(T_FLOAT), Rstore_addr);
#else
  __ stw(R17_tos, arrayOopDesc::base_offset_in_bytes(T_FLOAT), Rstore_addr);
#endif
  }

void TemplateTable::dastore() {
  transition(dtos, vtos);

  const Register Rindex      = R3_ARG1,
                 Rstore_addr = R4_ARG2,
                 Rarray      = R5_ARG3,
                 Rtemp       = R6_ARG4;
  __ pop_i(Rindex);
  __ index_check(Rarray, Rindex, LogBytesPerLong, Rtemp, Rstore_addr);
#ifndef USE_SPE
  __ stfd(F15_ftos, arrayOopDesc::base_offset_in_bytes(T_DOUBLE), Rstore_addr);
#else
  __ evstdd_unaligned(R17_tos, arrayOopDesc::base_offset_in_bytes(T_DOUBLE), Rstore_addr, R11_scratch1);
#endif
  }

// Pop 3 values from the stack and...
void TemplateTable::aastore() {
  transition(vtos, vtos);

  Label Lstore_ok, Lis_null, Ldone;
  const Register Rindex    = R3_ARG1,
                 Rarray    = R4_ARG2,
                 Rscratch  = R11_scratch1,
                 Rscratch2 = R12_scratch2,
                 Rarray_klass = R5_ARG3,
                 Rarray_element_klass = Rarray_klass,
                 Rvalue_klass = R6_ARG4,
                 Rstore_addr = R31;    // Use register which survives VM call.

  __ l(R17_tos, Interpreter::expr_offset_in_bytes(0), R15_esp); // Get value to store.
  __ lwz(Rindex, Interpreter::expr_offset_in_bytes(1), R15_esp); // Get index.
  __ l(Rarray, Interpreter::expr_offset_in_bytes(2), R15_esp);  // Get array.

  __ verify_oop(R17_tos);
  __ index_check_without_pop(Rarray, Rindex, UseCompressedOops ? 2 : LogBytesPerWord, Rscratch, Rstore_addr);
  // Rindex is dead!
  Register Rscratch3 = Rindex;

  // Do array store check - check for NULL value first.
  __ cmpi(CCR0, R17_tos, 0);
  __ beq(CCR0, Lis_null);

  __ load_klass(Rarray_klass, Rarray);
  __ load_klass(Rvalue_klass, R17_tos);

  // Do fast instanceof cache test.
  __ l(Rarray_element_klass, in_bytes(ObjArrayKlass::element_klass_offset()), Rarray_klass);

  // Generate a fast subtype check. Branch to store_ok if no failure. Throw if failure.
  __ gen_subtype_check(Rvalue_klass /*subklass*/, Rarray_element_klass /*superklass*/, Rscratch, Rscratch2, Rscratch3, Lstore_ok);

  // Fell through: subtype check failed => throw an exception.
  __ load_dispatch_table(R11_scratch1, (address*)Interpreter::_throw_ArrayStoreException_entry);
  __ mtctr(R11_scratch1);
  __ bctr();

  __ bind(Lis_null);
  do_oop_store(_masm, Rstore_addr, arrayOopDesc::base_offset_in_bytes(T_OBJECT), noreg /* 0 */,
               Rscratch, Rscratch2, Rscratch3, _bs->kind(), true /* precise */, false /* check_null */);
  __ profile_null_seen(Rscratch, Rscratch2);
  __ b(Ldone);

  // Store is OK.
  __ bind(Lstore_ok);
  do_oop_store(_masm, Rstore_addr, arrayOopDesc::base_offset_in_bytes(T_OBJECT), R17_tos /* value */,
               Rscratch, Rscratch2, Rscratch3, _bs->kind(), true /* precise */, false /* check_null */);

  __ bind(Ldone);
  // Adjust sp (pops array, index and value).
  __ addi(R15_esp, R15_esp, 3 * Interpreter::stackElementSize);
}

void TemplateTable::bastore() {
  transition(itos, vtos);

  const Register Rindex   = R11_scratch1,
                 Rarray   = R12_scratch2,
                 Rscratch = R3_ARG1;
  __ pop_i(Rindex);
  __ pop_ptr(Rarray);
  // tos: val

  // Need to check whether array is boolean or byte
  // since both types share the bastore bytecode.
  __ load_klass(Rscratch, Rarray);
  __ lwz(Rscratch, in_bytes(Klass::layout_helper_offset()), Rscratch);
  int diffbit = exact_log2(Klass::layout_helper_boolean_diffbit());
  __ testbitdi(CCR0, R0, Rscratch, diffbit);
  Label L_skip;
  __ bfalse(CCR0, L_skip);
  __ andi(R17_tos, R17_tos, 1);  // if it is a T_BOOLEAN array, mask the stored value to 0/1
  __ bind(L_skip);

  __ index_check_without_pop(Rarray, Rindex, 0, Rscratch, Rarray);
  __ stb(R17_tos, arrayOopDesc::base_offset_in_bytes(T_BYTE), Rarray);
}

void TemplateTable::castore() {
  transition(itos, vtos);

  const Register Rindex   = R11_scratch1,
                 Rarray   = R12_scratch2,
                 Rscratch = R3_ARG1;
  __ pop_i(Rindex);
  // tos: val
  // Rarray: array ptr (popped by index_check)
  __ index_check(Rarray, Rindex, LogBytesPerShort, Rscratch, Rarray);
  __ sth(R17_tos, arrayOopDesc::base_offset_in_bytes(T_CHAR), Rarray);
}

void TemplateTable::sastore() {
  castore();
}

void TemplateTable::istore(int n) {
  transition(itos, vtos);
  __ stw(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
}

void TemplateTable::lstore(int n) {
  transition(ltos, vtos);
#ifdef PPC64
  __ std(R17_tos, Interpreter::local_offset_in_bytes(n + 1), R18_locals);
#else
  __ stw(R30_tos2, Interpreter::local_offset_in_bytes(n + 1), R18_locals);
  __ stw(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
#endif
}

void TemplateTable::fstore(int n) {
  transition(ftos, vtos);
#ifndef USE_SPE
  __ stfs(F15_ftos, Interpreter::local_offset_in_bytes(n), R18_locals);
#else
  __ stw(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
#endif

}

void TemplateTable::dstore(int n) {
  transition(dtos, vtos);
#ifndef USE_SPE
  __ stfd(F15_ftos, Interpreter::local_offset_in_bytes(n + 1), R18_locals);
#else
  __ evstdd_unaligned(R17_tos, Interpreter::local_offset_in_bytes(n + 1), R18_locals, R11_scratch1);
#endif
}

void TemplateTable::astore(int n) {
  transition(vtos, vtos);

  __ pop_ptr();
  __ verify_oop_or_return_address(R17_tos, R11_scratch1);
  __ st(R17_tos, Interpreter::local_offset_in_bytes(n), R18_locals);
}

void TemplateTable::pop() {
  transition(vtos, vtos);

  __ addi(R15_esp, R15_esp, Interpreter::stackElementSize);
}

void TemplateTable::pop2() {
  transition(vtos, vtos);

  __ addi(R15_esp, R15_esp, Interpreter::stackElementSize * 2);
}

void TemplateTable::dup() {
  transition(vtos, vtos);

  __ l(R11_scratch1, Interpreter::stackElementSize, R15_esp);
  __ push_ptr(R11_scratch1);
}

void TemplateTable::dup_x1() {
  transition(vtos, vtos);

  Register Ra = R11_scratch1,
           Rb = R12_scratch2;
  // stack: ..., a, b
  __ l(Rb, Interpreter::stackElementSize,     R15_esp);
  __ l(Ra, Interpreter::stackElementSize * 2, R15_esp);
  __ st(Rb, Interpreter::stackElementSize * 2, R15_esp);
  __ st(Ra, Interpreter::stackElementSize,     R15_esp);
  __ push_ptr(Rb);
  // stack: ..., b, a, b
}

void TemplateTable::dup_x2() {
  transition(vtos, vtos);

  Register Ra = R11_scratch1,
           Rb = R12_scratch2,
           Rc = R3_ARG1;

  // stack: ..., a, b, c
  __ l(Rc, Interpreter::stackElementSize,     R15_esp);  // load c
  __ l(Ra, Interpreter::stackElementSize * 3, R15_esp);  // load a
  __ st(Rc, Interpreter::stackElementSize * 3, R15_esp); // store c in a
  __ l(Rb, Interpreter::stackElementSize * 2, R15_esp);  // load b
  // stack: ..., c, b, c
  __ st(Ra, Interpreter::stackElementSize * 2, R15_esp); // store a in b
  // stack: ..., c, a, c
  __ st(Rb, Interpreter::stackElementSize,     R15_esp); // store b in c
  __ push_ptr(Rc);                                        // push c
  // stack: ..., c, a, b, c
}

void TemplateTable::dup2() {
  transition(vtos, vtos);

  Register Ra = R11_scratch1,
           Rb = R12_scratch2;
  // stack: ..., a, b
  __ l(Rb, Interpreter::stackElementSize,     R15_esp);
  __ l(Ra, Interpreter::stackElementSize * 2, R15_esp);
  __ push_2ptrs(Ra, Rb);
  // stack: ..., a, b, a, b
}

void TemplateTable::dup2_x1() {
  transition(vtos, vtos);

  Register Ra = R11_scratch1,
           Rb = R12_scratch2,
           Rc = R3_ARG1;
  // stack: ..., a, b, c
  __ l(Rc, Interpreter::stackElementSize,     R15_esp);
  __ l(Rb, Interpreter::stackElementSize * 2, R15_esp);
  __ st(Rc, Interpreter::stackElementSize * 2, R15_esp);
  __ l(Ra, Interpreter::stackElementSize * 3, R15_esp);
  __ st(Ra, Interpreter::stackElementSize,     R15_esp);
  __ st(Rb, Interpreter::stackElementSize * 3, R15_esp);
  // stack: ..., b, c, a
  __ push_2ptrs(Rb, Rc);
  // stack: ..., b, c, a, b, c
}

void TemplateTable::dup2_x2() {
  transition(vtos, vtos);

  Register Ra = R11_scratch1,
           Rb = R12_scratch2,
           Rc = R3_ARG1,
           Rd = R4_ARG2;
  // stack: ..., a, b, c, d
  __ l(Rb, Interpreter::stackElementSize * 3, R15_esp);
  __ l(Rd, Interpreter::stackElementSize,     R15_esp);
  __ st(Rb, Interpreter::stackElementSize,     R15_esp);  // store b in d
  __ st(Rd, Interpreter::stackElementSize * 3, R15_esp);  // store d in b
  __ l(Ra, Interpreter::stackElementSize * 4, R15_esp);
  __ l(Rc, Interpreter::stackElementSize * 2, R15_esp);
  __ st(Ra, Interpreter::stackElementSize * 2, R15_esp);  // store a in c
  __ st(Rc, Interpreter::stackElementSize * 4, R15_esp);  // store c in a
  // stack: ..., c, d, a, b
  __ push_2ptrs(Rc, Rd);
  // stack: ..., c, d, a, b, c, d
}

void TemplateTable::swap() {
  transition(vtos, vtos);
  // stack: ..., a, b

  Register Ra = R11_scratch1,
           Rb = R12_scratch2;
  // stack: ..., a, b
  __ l(Rb, Interpreter::stackElementSize,     R15_esp);
  __ l(Ra, Interpreter::stackElementSize * 2, R15_esp);
  __ st(Rb, Interpreter::stackElementSize * 2, R15_esp);
  __ st(Ra, Interpreter::stackElementSize,     R15_esp);
  // stack: ..., b, a
}

void TemplateTable::iop2(Operation op) {
  transition(itos, itos);

  Register Rscratch = R11_scratch1;

  __ pop_i(Rscratch);
  // tos  = number of bits to shift
  // Rscratch = value to shift
  switch (op) {
    case  add:   __ add(R17_tos, Rscratch, R17_tos); break;
    case  sub:   __ sub(R17_tos, Rscratch, R17_tos); break;
    case  mul:   __ mullw(R17_tos, Rscratch, R17_tos); break;
    case  _and:  __ andr(R17_tos, Rscratch, R17_tos); break;
    case  _or:   __ orr(R17_tos, Rscratch, R17_tos); break;
    case  _xor:  __ xorr(R17_tos, Rscratch, R17_tos); break;
    case  shl:   __ rlicl(R17_tos, R17_tos, 0, 64-5); __ slw(R17_tos, Rscratch, R17_tos); break;
    case  shr:   __ rlicl(R17_tos, R17_tos, 0, 64-5); __ sraw(R17_tos, Rscratch, R17_tos); break;
    case  ushr:  __ rlicl(R17_tos, R17_tos, 0, 64-5); __ srw(R17_tos, Rscratch, R17_tos); break;
    default:     ShouldNotReachHere();
  }
}

void TemplateTable::lop2(Operation op) {
  transition(ltos, ltos);
#ifdef PPC64
  Register Rscratch = R11_scratch1;
  __ pop_l(Rscratch);
  switch (op) {
    case  add:   __ add(R17_tos, Rscratch, R17_tos); break;
    case  sub:   __ sub(R17_tos, Rscratch, R17_tos); break;
    case  _and:  __ andr(R17_tos, Rscratch, R17_tos); break;
    case  _or:   __ orr(R17_tos, Rscratch, R17_tos); break;
    case  _xor:  __ xorr(R17_tos, Rscratch, R17_tos); break;
    default:     ShouldNotReachHere();
  }
#else
  Register Rscratch = R11_scratch1;
  Register Rscratch2 = R12_scratch2;
  __ pop_l(Rscratch, Rscratch2);
  switch (op) {
    case add:
      __ addc(R17_tos, Rscratch, R17_tos);
      __ adde(R30_tos2, Rscratch2, R30_tos2);
      break;
    case sub:
      __ subfc(R17_tos, R17_tos, Rscratch);
      __ subfe(R30_tos2, R30_tos2, Rscratch2);
      break;
    case _and:
      __ andr(R17_tos, Rscratch, R17_tos);
      __ andr(R30_tos2, Rscratch2, R30_tos2);
      break;
    case _or:
      __ orr(R17_tos, Rscratch, R17_tos);
      __ orr(R30_tos2, Rscratch2, R30_tos2);
      break;
    case _xor:
      __ xorr(R17_tos, Rscratch, R17_tos);
      __ xorr(R30_tos2, Rscratch2, R30_tos2);
      break;
    default:
      ShouldNotReachHere();
  }
#endif
}

void TemplateTable::idiv() {
  transition(itos, itos);

  Label Lnormal, Lexception, Ldone;
  Register Rdividend = R11_scratch1; // Used by irem.

  __ addi(R0, R17_tos, 1);
  __ cmplwi(CCR0, R0, 2);
  __ bgt(CCR0, Lnormal); // divisor <-1 or >1

  __ cmpwi(CCR1, R17_tos, 0);
  __ beq(CCR1, Lexception); // divisor == 0

  __ pop_i(Rdividend);
  __ mullw(R17_tos, Rdividend, R17_tos); // div by +/-1
  __ b(Ldone);

  __ bind(Lexception);
  __ load_dispatch_table(R11_scratch1, (address*)Interpreter::_throw_ArithmeticException_entry);
  __ mtctr(R11_scratch1);
  __ bctr();

  __ align(32, 12);
  __ bind(Lnormal);
  __ pop_i(Rdividend);
  __ divw(R17_tos, Rdividend, R17_tos); // Can't divide minint/-1.
  __ bind(Ldone);
}

void TemplateTable::irem() {
  transition(itos, itos);

  __ mr(R12_scratch2, R17_tos);
  idiv();
  __ mullw(R17_tos, R17_tos, R12_scratch2);
  __ subf(R17_tos, R17_tos, R11_scratch1); // Dividend set by idiv.
}

void TemplateTable::lmul() {
  transition(ltos, ltos);

#ifdef PPC64
  __ pop_l(R11_scratch1);
  __ mull(R17_tos, R11_scratch1, R17_tos);
#else
  __ mr(R3_ARG1, R30_tos2);
  __ mr(R4_ARG2, R17_tos);
  __ pop_l(R6_ARG4, R5_ARG3);
  __ mullw(R11_scratch1, R3_ARG1, R6_ARG4);
  __ mullw(R12_scratch2, R4_ARG2, R5_ARG3);
  __ add(R11_scratch1, R11_scratch1, R12_scratch2);
  __ mulhwu(R30_tos2, R4_ARG2, R6_ARG4);
  __ mullw(R17_tos, R4_ARG2, R6_ARG4);
  __ add(R30_tos2, R11_scratch1, R30_tos2);
#endif
}

void TemplateTable::ldiv() {
  transition(ltos, ltos);

#ifdef PPC64
  Label Lnormal, Lexception, Ldone;
  Register Rdividend = R11_scratch1; // Used by lrem.

  __ addi(R0, R17_tos, 1);
  __ cmpli(CCR0, R0, 2);
  __ bgt(CCR0, Lnormal); // divisor <-1 or >1

  __ cmpi(CCR1, R17_tos, 0);
  __ beq(CCR1, Lexception); // divisor == 0

  __ pop_l(Rdividend);
  __ mull(R17_tos, Rdividend, R17_tos); // div by +/-1
  __ b(Ldone);

  __ bind(Lexception);
  __ load_dispatch_table(R11_scratch1, (address*)Interpreter::_throw_ArithmeticException_entry);
  __ mtctr(R11_scratch1);
  __ bctr();

  __ align(32, 12);
  __ bind(Lnormal);
  __ pop_l(Rdividend);
  __ div(R17_tos, Rdividend, R17_tos); // Can't divide minint/-1.
  __ bind(Ldone);
#else
  Label Lnormal;

  __ or_(R0, R17_tos, R30_tos2);
  __ bne(CCR0, Lnormal);

  __ load_dispatch_table(R11_scratch1, (address*)Interpreter::_throw_ArithmeticException_entry);
  __ mtctr(R11_scratch1);
  __ bctr();

  __ bind(Lnormal);

  __ mr(R3_ARG1, R30_tos2);
  __ mr(R4_ARG2, R17_tos);
  __ pop_l(R6_ARG4, R5_ARG3);
  __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::ldiv));
  __ mr(R30_tos2, R3_RET);
  __ mr(R17_tos, R4_RET2);
#endif
}

void TemplateTable::lrem() {
  transition(ltos, ltos);

#ifdef PPC64
  __ mr(R12_scratch2, R17_tos);
  ldiv();
  __ mull(R17_tos, R17_tos, R12_scratch2);
  __ subf(R17_tos, R17_tos, R11_scratch1); // Dividend set by ldiv.
#else
  Label Lnormal;

  __ or_(R0, R17_tos, R30_tos2);
  __ bne(CCR0, Lnormal);

  __ load_dispatch_table(R11_scratch1, (address*)Interpreter::_throw_ArithmeticException_entry);
  __ mtctr(R11_scratch1);
  __ bctr();

  __ bind(Lnormal);

  __ mr(R3_ARG1, R30_tos2);
  __ mr(R4_ARG2, R17_tos);
  __ pop_l(R6_ARG4, R5_ARG3);
  __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::lrem));
  __ mr(R30_tos2, R3_RET);
  __ mr(R17_tos, R4_RET2);
#endif
}

void TemplateTable::lshl() {
  transition(itos, ltos);

  __ rlicl(R17_tos, R17_tos, 0, 64-6); // Extract least significant bits.
#ifdef PPC64
  __ pop_l(R11_scratch1);
  __ sld(R17_tos, R11_scratch1, R17_tos);
#else
  __ pop_l(R11_scratch1, R12_scratch2);

  Label Llt32, Ldone;

  __ cmpi(CCR0, R17_tos, 32);
  __ blt(CCR0, Llt32);

  __ addi(R17_tos, R17_tos, -32);
  __ slw(R30_tos2, R11_scratch1, R17_tos);
  __ li(R17_tos, 0);
  __ b(Ldone);

  __ bind(Llt32);

  __ slw(R30_tos2, R12_scratch2, R17_tos);
  __ subfic(R12_scratch2, R17_tos, 32);
  __ srw(R12_scratch2, R11_scratch1, R12_scratch2);
  __ orr(R30_tos2, R30_tos2, R12_scratch2);
  __ slw(R17_tos, R11_scratch1, R17_tos);

  __ bind(Ldone);
#endif // PPC64
}

void TemplateTable::lshr() {
  transition(itos, ltos);

  __ rlicl(R17_tos, R17_tos, 0, 64-6); // Extract least significant bits.
#ifdef PPC64
  __ pop_l(R11_scratch1);
  __ srad(R17_tos, R11_scratch1, R17_tos);
#else
  __ pop_l(R11_scratch1, R12_scratch2);

  Label Llt32, Ldone;

  __ cmpi(CCR0, R17_tos, 32);
  __ blt(CCR0, Llt32);

  __ addi(R17_tos, R17_tos, -32);
  __ sraw(R17_tos, R12_scratch2, R17_tos);
  __ srawi(R30_tos2, R12_scratch2, 31);
  __ b(Ldone);

  __ bind(Llt32);

  __ srw(R11_scratch1, R11_scratch1, R17_tos);
  __ subfic(R30_tos2, R17_tos, 32);
  __ slw(R0, R12_scratch2, R30_tos2);
  __ sraw(R30_tos2, R12_scratch2, R17_tos);
  __ orr(R17_tos, R11_scratch1, R0);

  __ bind(Ldone);
#endif // PPC64
}

void TemplateTable::lushr() {
  transition(itos, ltos);

  __ rlicl(R17_tos, R17_tos, 0, 64-6); // Extract least significant bits.
#ifdef PPC64
  __ pop_l(R11_scratch1);
  __ srd(R17_tos, R11_scratch1, R17_tos);
#else
  __ pop_l(R11_scratch1, R12_scratch2);

  Label Llt32, Ldone;

  __ cmpi(CCR0, R17_tos, 32);
  __ blt(CCR0, Llt32);

  __ addi(R17_tos, R17_tos, -32);
  __ srw(R17_tos, R12_scratch2, R17_tos);
  __ li(R30_tos2, 0);
  __ b(Ldone);

  __ bind(Llt32);

  __ srw(R11_scratch1, R11_scratch1, R17_tos);
  __ subfic(R30_tos2, R17_tos, 32);
  __ slw(R0, R12_scratch2, R30_tos2);
  __ srw(R30_tos2, R12_scratch2, R17_tos);
  __ orr(R17_tos, R11_scratch1, R0);

  __ bind(Ldone);
#endif // PPC64
}

void TemplateTable::fop2(Operation op) {
  transition(ftos, ftos);
#ifndef USE_SPE
  switch (op) {
    case add: __ pop_f(F0_SCRATCH); __ fadds(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case sub: __ pop_f(F0_SCRATCH); __ fsubs(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case mul: __ pop_f(F0_SCRATCH); __ fmuls(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case div: __ pop_f(F0_SCRATCH); __ fdivs(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case rem:
#ifndef SPE_ABI
      __ pop_f(F1_ARG1);
      __ fmr(F2_ARG2, F15_ftos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::frem));
      __ fmr(F15_ftos, F1_RET);
#else
      __ lwzu(R3_ARG1, Interpreter::stackElementSize, R15_esp);
      __ stfs(F15_ftos, 0, R15_esp);
      __ lwz(R4_ARG2, 0, R15_esp);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::frem));
      __ stw(R3_RET, 0, R15_esp);
      __ lfs(F15_ftos, 0, R15_esp);
#endif
      break;

    default: ShouldNotReachHere();
  }
#else // USE_SPE
  // read and set rounding toward zero
  Label Ldone, Leq;
  switch (op) {
    case add:
      if (VM_Version::is_incorrect_single_fp()) {
        __ efdcfs(R17_tos, R17_tos);
        __ pop_f(R11_scratch1);
        __ efdcfs(R11_scratch1, R11_scratch1);
        __ efdadd(R17_tos, R11_scratch1, R17_tos);
        __ efscfd(R17_tos, R17_tos);
      } else {
        __ pop_f(R11_scratch1);
        __ efsadd(R17_tos, R11_scratch1, R17_tos);
      }
      break;
    case sub:
      if (VM_Version::is_incorrect_single_fp()) {
        __ efdcfs(R17_tos, R17_tos);
        __ pop_f(R11_scratch1);
        __ efdcfs(R11_scratch1, R11_scratch1);
        __ efdsub(R17_tos, R11_scratch1, R17_tos);
        __ efscfd(R17_tos, R17_tos);
      } else {
        __ pop_f(R11_scratch1);
        __ efssub(R17_tos, R11_scratch1, R17_tos);
      }
      break;
    case mul: __ pop_f(R11_scratch1); __ efsmul(R17_tos, R11_scratch1, R17_tos); break;
    case div: __ pop_f(R11_scratch1); __ efsdiv(R17_tos, R11_scratch1, R17_tos); break;
    case rem:
      __ pop_f(R3_ARG1);
      __ mr(R4_ARG2, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::frem));
      __ mr(R17_tos, R3_RET);
      break;

    default: ShouldNotReachHere();
  }
  __ bind(Ldone);
#endif // USE_SPE
}

void TemplateTable::dop2(Operation op) {
  transition(dtos, dtos);
#ifndef USE_SPE
  switch (op) {
    case add: __ pop_d(F0_SCRATCH); __ fadd(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case sub: __ pop_d(F0_SCRATCH); __ fsub(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case mul: __ pop_d(F0_SCRATCH); __ fmul(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case div: __ pop_d(F0_SCRATCH); __ fdiv(F15_ftos, F0_SCRATCH, F15_ftos); break;
    case rem:
#ifndef SPE_ABI
      __ pop_d(F1_ARG1);
      __ fmr(F2_ARG2, F15_ftos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::drem));
      __ fmr(F15_ftos, F1_RET);
#else // SPE_ABI
      __ lwz(R3_ARG1, Interpreter::stackElementSize, R15_esp);
      __ lwz(R4_ARG2, 2 * Interpreter::stackElementSize, R15_esp);
      __ addi(R15_esp, R15_esp, 2 *Interpreter::stackElementSize);
      __ stfd(F15_ftos, -4, R15_esp);
      __ lwz(R5_ARG3, -4, R15_esp);
      __ lwz(R6_ARG4, 0, R15_esp);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::drem));
      __ stw(R3_RET, -4, R15_esp);
      __ stw(R4_RET2, 0, R15_esp);
      __ lfd(F15_ftos, -4, R15_esp);
#endif // SPE_ABI
      break;

    default: ShouldNotReachHere();
  }
#else // USE_SPE
  Label Ldone, Leq;
  switch (op) {
    case add: __ pop_d(R11_scratch1); __ efdadd(R17_tos, R11_scratch1, R17_tos); break;
    case sub: __ pop_d(R11_scratch1); __ efdsub(R17_tos, R11_scratch1, R17_tos); break;
    case mul: __ pop_d(R11_scratch1); __ efdmul(R17_tos, R11_scratch1, R17_tos); break;
    case div: __ pop_d(R11_scratch1); __ efddiv(R17_tos, R11_scratch1, R17_tos); break;
    case rem:
      __ pop_l(R4_ARG2, R3_ARG1);
      __ evmergehi(R5_ARG3, R5_ARG3, R17_tos);
      __ mr(R6_ARG4, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::drem));
      __ evmergelo(R17_tos, R3_RET, R4_RET2);
      break;

    default: ShouldNotReachHere();
  }
  __ bind(Ldone);
#endif // USE_SPE
}

// Negate the value in the TOS cache.
void TemplateTable::ineg() {
  transition(itos, itos);

  __ neg(R17_tos, R17_tos);
}

// Negate the value in the TOS cache.
void TemplateTable::lneg() {
  transition(ltos, ltos);

#ifdef PPC64
  __ neg(R17_tos, R17_tos);
#else
  __ subfic(R17_tos, R17_tos, 0);
  __ subfze(R30_tos2, R30_tos2);
#endif
}

void TemplateTable::fneg() {
  transition(ftos, ftos);
#ifndef USE_SPE
  __ fneg(F15_ftos, F15_ftos);
#else
  __ efsneg(R17_tos, R17_tos);
#endif
}

void TemplateTable::dneg() {
  transition(dtos, dtos);
#ifndef USE_SPE
  __ fneg(F15_ftos, F15_ftos);
#else
  __ efdneg(R17_tos, R17_tos);
#endif
}

// Increments a local variable in place.
void TemplateTable::iinc() {
  transition(vtos, vtos);

  const Register Rindex     = R11_scratch1,
                 Rincrement = R0,
                 Rvalue     = R12_scratch2;

  locals_index(Rindex);              // Load locals index from bytecode stream.
  __ lbz(Rincrement, 2, R14_bcp);    // Load increment from the bytecode stream.
  __ extsb(Rincrement, Rincrement);

  __ load_local_int(Rvalue, Rindex, Rindex); // Puts address of local into Rindex.

  __ add(Rvalue, Rincrement, Rvalue);
  __ stw(Rvalue, 0, Rindex);
}

void TemplateTable::wide_iinc() {
  transition(vtos, vtos);

  Register Rindex       = R11_scratch1,
           Rlocals_addr = Rindex,
           Rincr        = R12_scratch2;
  locals_index_wide(Rindex);
  __ get_2_byte_integer_at_bcp(4, Rincr, InterpreterMacroAssembler::Signed);
  __ load_local_int(R17_tos, Rlocals_addr, Rindex);
  __ add(R17_tos, Rincr, R17_tos);
  __ stw(R17_tos, 0, Rlocals_addr);
}

void TemplateTable::convert() {
  // %%%%% Factor this first part accross platforms
#ifdef ASSERT
  TosState tos_in  = ilgl;
  TosState tos_out = ilgl;
  switch (bytecode()) {
    case Bytecodes::_i2l: // fall through
    case Bytecodes::_i2f: // fall through
    case Bytecodes::_i2d: // fall through
    case Bytecodes::_i2b: // fall through
    case Bytecodes::_i2c: // fall through
    case Bytecodes::_i2s: tos_in = itos; break;
    case Bytecodes::_l2i: // fall through
    case Bytecodes::_l2f: // fall through
    case Bytecodes::_l2d: tos_in = ltos; break;
    case Bytecodes::_f2i: // fall through
    case Bytecodes::_f2l: // fall through
    case Bytecodes::_f2d: tos_in = ftos; break;
    case Bytecodes::_d2i: // fall through
    case Bytecodes::_d2l: // fall through
    case Bytecodes::_d2f: tos_in = dtos; break;
    default             : ShouldNotReachHere();
  }
  switch (bytecode()) {
    case Bytecodes::_l2i: // fall through
    case Bytecodes::_f2i: // fall through
    case Bytecodes::_d2i: // fall through
    case Bytecodes::_i2b: // fall through
    case Bytecodes::_i2c: // fall through
    case Bytecodes::_i2s: tos_out = itos; break;
    case Bytecodes::_i2l: // fall through
    case Bytecodes::_f2l: // fall through
    case Bytecodes::_d2l: tos_out = ltos; break;
    case Bytecodes::_i2f: // fall through
    case Bytecodes::_l2f: // fall through
    case Bytecodes::_d2f: tos_out = ftos; break;
    case Bytecodes::_i2d: // fall through
    case Bytecodes::_l2d: // fall through
    case Bytecodes::_f2d: tos_out = dtos; break;
    default             : ShouldNotReachHere();
  }
  transition(tos_in, tos_out);
#endif

  // Conversion
  Label done, LNaNorInfinityD, LNaNorInfinityF;
  switch (bytecode()) {
    case Bytecodes::_l2i:
      // Nothing to do, we'll continue to work with the lower bits.
      break;

    case Bytecodes::_i2b:
      __ extsb(R17_tos, R17_tos);
      break;

    case Bytecodes::_i2c:
      __ rlicl(R17_tos, R17_tos, 0, 64-2*8);
      break;

    case Bytecodes::_i2s:
      __ extsh(R17_tos, R17_tos);
      break;

    case Bytecodes::_f2d:
#ifdef USE_SPE
      __ efdcfs(R17_tos, R17_tos);
#endif
      break;

    case Bytecodes::_d2f:
#ifndef USE_SPE
      __ frsp(F15_ftos, F15_ftos);
#else
      __ efscfd(R17_tos, R17_tos);
#endif
      break;

#ifdef PPC64
    case Bytecodes::_i2l:
      __ extsw(R17_tos, R17_tos);
      break;

    case Bytecodes::_i2d:
      __ extsw(R17_tos, R17_tos);
    case Bytecodes::_l2d:
      __ push_l_pop_d();
      __ fcfid(F15_ftos, F15_ftos);
      break;

    case Bytecodes::_i2f:
      __ extsw(R17_tos, R17_tos);
      __ push_l_pop_d();
      if (VM_Version::has_fcfids()) { // fcfids is >= Power7 only
        // Comment: alternatively, load with sign extend could be done by lfiwax.
        __ fcfids(F15_ftos, F15_ftos);
      } else {
        __ fcfid(F15_ftos, F15_ftos);
        __ frsp(F15_ftos, F15_ftos);
      }
      break;

    case Bytecodes::_l2f:
      if (VM_Version::has_fcfids()) { // fcfids is >= Power7 only
        __ push_l_pop_d();
        __ fcfids(F15_ftos, F15_ftos);
      } else {
        // Avoid rounding problem when result should be 0x3f800001: need fixup code before fcfid+frsp.
        __ mr(R3_ARG1, R17_tos);
        __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::l2f));
        __ fmr(F15_ftos, F1_RET);
      }
      break;

    case Bytecodes::_d2l:
    case Bytecodes::_f2l:
      __ fcmpu(CCR0, F15_ftos, F15_ftos);
      __ li(R17_tos, 0); // 0 in case of NAN
      __ bso(CCR0, done);
      __ fctidz(F15_ftos, F15_ftos);
      __ push_d_pop_l();
      break;

    case Bytecodes::_d2i:
    case Bytecodes::_f2i:
      __ fcmpu(CCR0, F15_ftos, F15_ftos);
      __ li(R17_tos, 0); // 0 in case of NAN
      __ bso(CCR0, done);
      __ fctiwz(F15_ftos, F15_ftos);
      __ push_d_pop_l();
      break;

#else // PPC64

    case Bytecodes::_i2l:
      __ srawi(R30_tos2, R17_tos, 31);
      break;

#ifdef USE_SPE

    case Bytecodes::_i2d:
      __ efdcfsi(R17_tos, R17_tos);
      break;

    case Bytecodes::_l2d:
      __ mr(R3_ARG1, R30_tos2);
      __ mr(R4_ARG2, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::l2d));
      __ evmergelo(R17_tos, R3_RET, R4_RET2);
      break;

    case Bytecodes::_i2f:
      __ efscfsi(R17_tos, R17_tos);
      break;

    case Bytecodes::_l2f:
      __ mr(R3_ARG1, R30_tos2);
      __ mr(R4_ARG2, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::l2f));
      __ mr(R17_tos, R3_RET);
      break;

    case Bytecodes::_d2l:
      __ evmergehi(R3_ARG1, R17_tos, R17_tos);
      __ mr(R4_ARG2, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::d2l));
      __ mr(R17_tos, R4_RET2);
      __ mr(R30_tos2, R3_RET);
      break;

    case Bytecodes::_f2l:
        __ mr(R3_ARG1, R17_tos);
        __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::f2l));
        __ mr(R17_tos, R4_RET2);
        __ mr(R30_tos2, R3_RET);
      break;

    case Bytecodes::_d2i:
      __ evmergehi(R11_scratch1, R17_tos, R17_tos);
      __ rotrwi(R11_scratch1,R11_scratch1,20);
      __ clrlwi(R11_scratch1,R11_scratch1,21);
      __ cmpwi(CCR0, R11_scratch1, 0x7FF);
      __ beq(CCR0, LNaNorInfinityD);

      __ efdctsiz(R17_tos, R17_tos);
      __ b(done);

      __ bind(LNaNorInfinityD);
      __ evmergehi(R3_ARG1, R17_tos, R17_tos);
      __ mr(R4_ARG2, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::d2i));
      __ mr(R17_tos, R3_RET);
      break;

    case Bytecodes::_f2i:
      __ rotrwi(R11_scratch1,R17_tos,23);
      __ clrlwi(R11_scratch1,R11_scratch1,24);
      __ cmpwi(CCR0, R11_scratch1, 0xFF);
      __ beq(CCR0, LNaNorInfinityF);

      __ efsctsiz(R17_tos, R17_tos);
      __ b(done);

      __ bind(LNaNorInfinityF);
      __ mr(R3_ARG1, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::f2i));
      __ mr(R17_tos, R3_RET);
      break;
#else // USE_SPE
    case Bytecodes::_i2d:
      // fcfid may be missed on PPC32
      __ mr(R3_ARG1, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::i2d));
#ifndef SPE_ABI
      __ fmr(F15_ftos, F1_RET);
#else // SPE_ABI and not USE_SPE implicitly
      __ stw(R3_RET, -4, R15_esp);
      __ stw(R4_RET2, 0, R15_esp);
      __ lfd(F15_ftos, -4, R15_esp);
#endif // SPE_ABI
      break;

    case Bytecodes::_l2d:
      // fcfid may be missed on PPC32
      __ mr(R3_ARG1, R30_tos2);
      __ mr(R4_ARG2, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::l2d));
#ifndef SPE_ABI
      __ fmr(F15_ftos, F1_RET);
#else // SPE_ABI and not USE_SPE implicitly
      __ stw(R3_RET, -4, R15_esp);
      __ stw(R4_RET2, 0, R15_esp);
      __ lfd(F15_ftos, -4, R15_esp);
#endif // SPE_ABI
      break;

    case Bytecodes::_i2f:
      // fcfid may be missed on PPC32
      __ mr(R3_ARG1, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::i2f));
#ifndef SPE_ABI
      __ fmr(F15_ftos, F1_RET);
#else // SPE_ABI and not USE_SPE implicitly
      __ stw(R3_RET, 0, R15_esp);
      __ lfs(F15_ftos, 0, R15_esp);
#endif // SPE_ABI
      break;

    case Bytecodes::_l2f:
      // fcfid may be missed on PPC32
      __ mr(R3_ARG1, R30_tos2);
      __ mr(R4_ARG2, R17_tos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::l2f));
#ifndef SPE_ABI
      __ fmr(F15_ftos, F1_RET);
#else // SPE_ABI and not USE_SPE implicitly
      __ stw(R3_RET, 0, R15_esp);
      __ lfs(F15_ftos, 0, R15_esp);
#endif // SPE_ABI
      break;

    case Bytecodes::_d2l:
    case Bytecodes::_f2l:
      // fctidz may be missed on PPC32
#ifndef SPE_ABI
      __ fmr(F1_ARG1, F15_ftos);
#else // SPE_ABI and not USE_SPE implicitly
      __ stfd(F15_ftos, -4, R15_esp);
      __ lwz(R3_ARG1, -4, R15_esp);
      __ lwz(R4_ARG2, 0, R15_esp);
#endif // SPE_ABI
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::d2l));
      __ mr(R17_tos, R4_RET2);
      __ mr(R30_tos2, R3_RET);
      break;

    case Bytecodes::_d2i:
    case Bytecodes::_f2i:
      __ fcmpu(CCR0, F15_ftos, F15_ftos);
      __ li(R17_tos, 0); // 0 in case of NAN
      __ bso(CCR0, done);
      __ fctiwz(F15_ftos, F15_ftos);
      __ stfd(F15_ftos, - Interpreter::stackElementSize, R15_esp);
      __ lwz(R17_tos, 0, R15_esp);
      break;
#endif // USE_SPE
#endif // PPC64

    default: ShouldNotReachHere();
  }
  __ bind(done);
}

// Long compare
void TemplateTable::lcmp() {
  transition(ltos, itos);

  const Register Rscratch = R11_scratch1;
#ifdef PPC64
  __ pop_l(Rscratch); // first operand, deeper in stack

  __ cmp(CCR0, Rscratch, R17_tos); // compare
#else
  const Register Rscratch2 = R12_scratch2;
  Label done;
  __ pop_l(Rscratch, Rscratch2);
  __ cmpw(CCR0, Rscratch2, R30_tos2);// signed compare
  __ bne(CCR0, done);
  __ cmplw(CCR0, Rscratch, R17_tos);// unsigned compare
  __ bind(done);
#endif // PPC64
  __ mfcr(R17_tos); // set bit 32..33 as follows: <: 0b10, =: 0b00, >: 0b01
  __ srwi(Rscratch, R17_tos, 30);
  __ srawi(R17_tos, R17_tos, 31);
  __ orr(R17_tos, Rscratch, R17_tos); // set result as follows: <: -1, =: 0, >: 1
}

// fcmpl/fcmpg and dcmpl/dcmpg bytecodes
// unordered_result == -1 => fcmpl or dcmpl
// unordered_result ==  1 => fcmpg or dcmpg
void TemplateTable::float_cmp(bool is_float, int unordered_result) {
#ifndef USE_SPE
  const FloatRegister Rfirst  = F0_SCRATCH,
                      Rsecond = F15_ftos;
  const Register Rscratch = R11_scratch1;
  if (is_float) {
    __ pop_f(Rfirst);
  } else {
    __ pop_d(Rfirst);
  }

  Label Lunordered, Ldone;
  __ fcmpu(CCR0, Rfirst, Rsecond); // compare
  if (unordered_result) {
    __ bso(CCR0, Lunordered);
  }
  __ mfcr(R17_tos); // set bit 32..33 as follows: <: 0b10, =: 0b00, >: 0b01
  __ srwi(Rscratch, R17_tos, 30);
  __ srawi(R17_tos, R17_tos, 31);
  __ orr(R17_tos, Rscratch, R17_tos); // set result as follows: <: -1, =: 0, >: 1
  if (unordered_result) {
    __ b(Ldone);
    __ bind(Lunordered);
    __ load_const_optimized(R17_tos, unordered_result);
  }
  __ bind(Ldone);
#else
  const Register Rfirst  = R11_scratch1,
                 Rsecond = R17_tos;
  const Register Rscratch = R12_scratch2;
  Label Ldone;

  if (is_float) {
    __ pop_f(Rfirst);
    __ li(Rscratch, 0);
    __ efscmpeq(CCR0, Rfirst, Rsecond);
    __ bgt(CCR0, Ldone);
    if (unordered_result > 0) {
        __ li(Rscratch, -1);
        __ efscmplt(CCR0, Rfirst, Rsecond);
        __ bgt(CCR0, Ldone);
        __ li(Rscratch, 1);
    } else {
        __ li(Rscratch, 1);
        __ efscmpgt(CCR0, Rfirst, Rsecond);
        __ bgt(CCR0, Ldone);
        __ li(Rscratch, -1);
    }
  } else {
    __ pop_d(Rfirst);
    __ li(Rscratch, 0);
    __ efdcmpeq(CCR0, Rfirst, Rsecond);
    __ bgt(CCR0, Ldone);
    if (unordered_result > 0) {
        __ li(Rscratch, -1);
        __ efdcmplt(CCR0, Rfirst, Rsecond);
        __ bgt(CCR0, Ldone);
        __ li(Rscratch, 1);
    } else {
        __ li(Rscratch, 1);
        __ efdcmpgt(CCR0, Rfirst, Rsecond);
        __ bgt(CCR0, Ldone);
        __ li(Rscratch, -1);
    }
  }
  __ bind(Ldone);
  __ mr(R17_tos, Rscratch);
#endif
}

// Branch_conditional which takes TemplateTable::Condition.
void TemplateTable::branch_conditional(ConditionRegister crx, TemplateTable::Condition cc, Label& L, bool invert) {
  bool positive = false;
  Assembler::Condition cond = Assembler::equal;
  switch (cc) {
    case TemplateTable::equal:         positive = true ; cond = Assembler::equal  ; break;
    case TemplateTable::not_equal:     positive = false; cond = Assembler::equal  ; break;
    case TemplateTable::less:          positive = true ; cond = Assembler::less   ; break;
    case TemplateTable::less_equal:    positive = false; cond = Assembler::greater; break;
    case TemplateTable::greater:       positive = true ; cond = Assembler::greater; break;
    case TemplateTable::greater_equal: positive = false; cond = Assembler::less   ; break;
    default: ShouldNotReachHere();
  }
  int bo = (positive != invert) ? Assembler::bcondCRbiIs1 : Assembler::bcondCRbiIs0;
  int bi = Assembler::bi0(crx, cond);
  __ bc(bo, bi, L);
}

void TemplateTable::branch(bool is_jsr, bool is_wide) {

  // Note: on SPARC, we use InterpreterMacroAssembler::if_cmp also.
  __ verify_thread();

  const Register Rscratch1    = R11_scratch1,
                 Rscratch2    = R12_scratch2,
                 Rscratch3    = R3_ARG1,
                 R4_counters  = R4_ARG2,
                 bumped_count = R31,
                 Rdisp        = R22_tmp2;

  __ profile_taken_branch(Rscratch1, bumped_count);

  // Get (wide) offset.
  if (is_wide) {
    __ get_4_byte_integer_at_bcp(1, Rdisp, InterpreterMacroAssembler::Signed);
  } else {
    __ get_2_byte_integer_at_bcp(1, Rdisp, InterpreterMacroAssembler::Signed);
  }

  // --------------------------------------------------------------------------
  // Handle all the JSR stuff here, then exit.
  // It's much shorter and cleaner than intermingling with the
  // non-JSR normal-branch stuff occurring below.
  if (is_jsr) {
    // Compute return address as bci in Otos_i.
    __ l(Rscratch1, in_bytes(Method::const_offset()), R19_method);
    __ addi(Rscratch2, R14_bcp, -in_bytes(ConstMethod::codes_offset()) + (is_wide ? 5 : 3));
    __ subf(R17_tos, Rscratch1, Rscratch2);

    // Bump bcp to target of JSR.
    __ add(R14_bcp, Rdisp, R14_bcp);
    // Push returnAddress for "ret" on stack.
    __ push_ptr(R17_tos);
    // And away we go!
    __ dispatch_next(vtos);
    return;
  }

  // --------------------------------------------------------------------------
  // Normal (non-jsr) branch handling

  const bool increment_invocation_counter_for_backward_branches = UseCompiler && UseLoopCounter;
  if (increment_invocation_counter_for_backward_branches) {
    //__ unimplemented("branch invocation counter");

    Label Lforward;
    __ add(R14_bcp, Rdisp, R14_bcp); // Add to bc addr.

    // Check branch direction.
    __ cmpi(CCR0, Rdisp, 0);
    __ bgt(CCR0, Lforward);

    __ get_method_counters(R19_method, R4_counters, Lforward);

    if (TieredCompilation) {
      Label Lno_mdo, Loverflow;
      const int increment = InvocationCounter::count_increment;
      const int mask = ((1 << Tier0BackedgeNotifyFreqLog) - 1) << InvocationCounter::count_shift;
      if (ProfileInterpreter) {
        Register Rmdo = Rscratch1;

        // If no method data exists, go to profile_continue.
        __ l(Rmdo, in_bytes(Method::method_data_offset()), R19_method);
        __ cmpi(CCR0, Rmdo, 0);
        __ beq(CCR0, Lno_mdo);

        // Increment backedge counter in the MDO.
        const int mdo_bc_offs = in_bytes(MethodData::backedge_counter_offset()) + in_bytes(InvocationCounter::counter_offset());
        __ lwz(Rscratch2, mdo_bc_offs, Rmdo);
        __ load_const_optimized(Rscratch3, mask, R0);
        __ addi(Rscratch2, Rscratch2, increment);
        __ stw(Rscratch2, mdo_bc_offs, Rmdo);
        __ and_(Rscratch3, Rscratch2, Rscratch3);
        __ bne(CCR0, Lforward);
        __ b(Loverflow);
      }

      // If there's no MDO, increment counter in method.
      const int mo_bc_offs = in_bytes(MethodCounters::backedge_counter_offset()) + in_bytes(InvocationCounter::counter_offset());
      __ bind(Lno_mdo);
      __ lwz(Rscratch2, mo_bc_offs, R4_counters);
      __ load_const_optimized(Rscratch3, mask, R0);
      __ addi(Rscratch2, Rscratch2, increment);
      __ stw(Rscratch2, mo_bc_offs, R19_method);
      __ and_(Rscratch3, Rscratch2, Rscratch3);
      __ bne(CCR0, Lforward);

      __ bind(Loverflow);

      // Notify point for loop, pass branch bytecode.
      __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::frequency_counter_overflow), R14_bcp, true);

      // Was an OSR adapter generated?
      // O0 = osr nmethod
      __ cmpi(CCR0, R3_RET, 0);
      __ beq(CCR0, Lforward);

      // Has the nmethod been invalidated already?
      __ lwz(R0, nmethod::entry_bci_offset(), R3_RET);
      __ cmpwi(CCR0, R0, InvalidOSREntryBci);
      __ beq(CCR0, Lforward);

      // Migrate the interpreter frame off of the stack.
      // We can use all registers because we will not return to interpreter from this point.

      // Save nmethod.
      const Register osr_nmethod = R31;
      __ mr(osr_nmethod, R3_RET);
      __ set_top_ijava_frame_at_SP_as_last_Java_frame(R1_SP, R11_scratch1);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::OSR_migration_begin), R16_thread);
      __ reset_last_Java_frame();
      // OSR buffer is in ARG1.

      // Remove the interpreter frame.
      __ merge_frames(/*top_frame_sp*/ R21_sender_SP, /*return_pc*/ R0, R11_scratch1, R12_scratch2);

      // Jump to the osr code.
      __ l(R11_scratch1, nmethod::osr_entry_point_offset(), osr_nmethod);
      __ mtlr(R0);
      __ mtctr(R11_scratch1);
      __ bctr();

    } else {

      const Register invoke_ctr = Rscratch1;
      // Update Backedge branch separately from invocations.
      __ increment_backedge_counter(R4_counters, invoke_ctr, Rscratch2, Rscratch3);

      if (ProfileInterpreter) {
        __ test_invocation_counter_for_mdp(invoke_ctr, R4_counters, Rscratch2, Lforward);
        if (UseOnStackReplacement) {
          __ test_backedge_count_for_osr(bumped_count, R4_counters, R14_bcp, Rdisp, Rscratch2);
        }
      } else {
        if (UseOnStackReplacement) {
          __ test_backedge_count_for_osr(invoke_ctr, R4_counters, R14_bcp, Rdisp, Rscratch2);
        }
      }
    }

    __ bind(Lforward);

  } else {
    // Bump bytecode pointer by displacement (take the branch).
    __ add(R14_bcp, Rdisp, R14_bcp); // Add to bc addr.
  }
  // Continue with bytecode @ target.
  // %%%%% Like Intel, could speed things up by moving bytecode fetch to code above,
  // %%%%% and changing dispatch_next to dispatch_only.
  __ dispatch_next(vtos);
}

// Helper function for if_cmp* methods below.
// Factored out common compare and branch code.
void TemplateTable::if_cmp_common(Register Rfirst, Register Rsecond, Register Rscratch1, Register Rscratch2, Condition cc, bool is_jint, bool cmp0) {
  Label Lnot_taken;
  // Note: The condition code we get is the condition under which we
  // *fall through*! So we have to inverse the CC here.

  if (is_jint) {
    if (cmp0) {
      __ cmpwi(CCR0, Rfirst, 0);
    } else {
      __ cmpw(CCR0, Rfirst, Rsecond);
    }
  } else {
    if (cmp0) {
      __ cmpi(CCR0, Rfirst, 0);
    } else {
      __ cmp(CCR0, Rfirst, Rsecond);
    }
  }
  branch_conditional(CCR0, cc, Lnot_taken, /*invert*/ true);

  // Conition is false => Jump!
  branch(false, false);

  // Condition is not true => Continue.
  __ align(32, 12);
  __ bind(Lnot_taken);
  __ profile_not_taken_branch(Rscratch1, Rscratch2);
}

// Compare integer values with zero and fall through if CC holds, branch away otherwise.
void TemplateTable::if_0cmp(Condition cc) {
  transition(itos, vtos);

  if_cmp_common(R17_tos, noreg, R11_scratch1, R12_scratch2, cc, true, true);
}

// Compare integer values and fall through if CC holds, branch away otherwise.
//
// Interface:
//  - Rfirst: First operand  (older stack value)
//  - tos:    Second operand (younger stack value)
void TemplateTable::if_icmp(Condition cc) {
  transition(itos, vtos);

  const Register Rfirst  = R0,
                 Rsecond = R17_tos;

  __ pop_i(Rfirst);
  if_cmp_common(Rfirst, Rsecond, R11_scratch1, R12_scratch2, cc, true, false);
}

void TemplateTable::if_nullcmp(Condition cc) {
  transition(atos, vtos);

  if_cmp_common(R17_tos, noreg, R11_scratch1, R12_scratch2, cc, false, true);
}

void TemplateTable::if_acmp(Condition cc) {
  transition(atos, vtos);

  const Register Rfirst  = R0,
                 Rsecond = R17_tos;

  __ pop_ptr(Rfirst);
  if_cmp_common(Rfirst, Rsecond, R11_scratch1, R12_scratch2, cc, false, false);
}

void TemplateTable::ret() {
  locals_index(R11_scratch1);
  __ load_local_ptr(R17_tos, R11_scratch1, R11_scratch1);

  __ profile_ret(vtos, R17_tos, R11_scratch1, R12_scratch2);

  __ l(R11_scratch1, in_bytes(Method::const_offset()), R19_method);
  __ add(R11_scratch1, R17_tos, R11_scratch1);
  __ addi(R14_bcp, R11_scratch1, in_bytes(ConstMethod::codes_offset()));
  __ dispatch_next(vtos);
}

void TemplateTable::wide_ret() {
  transition(vtos, vtos);

  const Register Rindex = R3_ARG1,
                 Rscratch1 = R11_scratch1,
                 Rscratch2 = R12_scratch2;

  locals_index_wide(Rindex);
  __ load_local_ptr(R17_tos, R17_tos, Rindex);
  __ profile_ret(vtos, R17_tos, Rscratch1, R12_scratch2);
  // Tos now contains the bci, compute the bcp from that.
  __ l(Rscratch1, in_bytes(Method::const_offset()), R19_method);
  __ addi(Rscratch2, R17_tos, in_bytes(ConstMethod::codes_offset()));
  __ add(R14_bcp, Rscratch1, Rscratch2);
  __ dispatch_next(vtos);
}

void TemplateTable::tableswitch() {
  transition(itos, vtos);

  Label Ldispatch, Ldefault_case;
  Register Rlow_byte         = R3_ARG1,
           Rindex            = Rlow_byte,
           Rhigh_byte        = R4_ARG2,
           Rdef_offset_addr  = R5_ARG3, // is going to contain address of default offset
           Rscratch1         = R11_scratch1,
           Rscratch2         = R12_scratch2,
           Roffset           = R6_ARG4;

  // Align bcp.
  __ addi(Rdef_offset_addr, R14_bcp, BytesPerInt);
  __ clrri(Rdef_offset_addr, Rdef_offset_addr, log2_long((jlong)BytesPerInt));

  // Load lo & hi.
  __ get_u4(Rlow_byte, Rdef_offset_addr, BytesPerInt, InterpreterMacroAssembler::Unsigned);
  __ get_u4(Rhigh_byte, Rdef_offset_addr, 2 *BytesPerInt, InterpreterMacroAssembler::Unsigned);

  // Check for default case (=index outside [low,high]).
  __ cmpw(CCR0, R17_tos, Rlow_byte);
  __ cmpw(CCR1, R17_tos, Rhigh_byte);
  __ blt(CCR0, Ldefault_case);
  __ bgt(CCR1, Ldefault_case);

  // Lookup dispatch offset.
  __ sub(Rindex, R17_tos, Rlow_byte);
  __ extsw(Rindex, Rindex);
  __ profile_switch_case(Rindex, Rhigh_byte /* scratch */, Rscratch1, Rscratch2);
  __ sli(Rindex, Rindex, LogBytesPerInt);
  __ addi(Rindex, Rindex, 3 * BytesPerInt);
#if defined(VM_LITTLE_ENDIAN)
  __ lwbrx(Roffset, Rdef_offset_addr, Rindex);
  __ extsw(Roffset, Roffset);
#else
  __ lwax(Roffset, Rdef_offset_addr, Rindex);
#endif
  __ b(Ldispatch);

  __ bind(Ldefault_case);
  __ profile_switch_default(Rhigh_byte, Rscratch1);
  __ get_u4(Roffset, Rdef_offset_addr, 0, InterpreterMacroAssembler::Signed);

  __ bind(Ldispatch);

  __ add(R14_bcp, Roffset, R14_bcp);
  __ dispatch_next(vtos);
}

void TemplateTable::lookupswitch() {
  transition(itos, itos);
  __ stop("lookupswitch bytecode should have been rewritten");
}

// Table switch using linear search through cases.
// Bytecode stream format:
// Bytecode (1) | 4-byte padding | default offset (4) | count (4) | value/offset pair1 (8) | value/offset pair2 (8) | ...
// Note: Everything is big-endian format here.
void TemplateTable::fast_linearswitch() {
  transition(itos, vtos);

  Label Lloop_entry, Lsearch_loop, Lcontinue_execution, Ldefault_case;
  Register Rcount           = R3_ARG1,
           Rcurrent_pair    = R4_ARG2,
           Rdef_offset_addr = R5_ARG3, // Is going to contain address of default offset.
           Roffset          = R31,     // Might need to survive C call.
           Rvalue           = R12_scratch2,
           Rscratch         = R11_scratch1,
           Rcmp_value       = R17_tos;

  // Align bcp.
  __ addi(Rdef_offset_addr, R14_bcp, BytesPerInt);
  __ clrri(Rdef_offset_addr, Rdef_offset_addr, log2_long((jlong)BytesPerInt));

  // Setup loop counter and limit.
  __ get_u4(Rcount, Rdef_offset_addr, BytesPerInt, InterpreterMacroAssembler::Unsigned);
  __ addi(Rcurrent_pair, Rdef_offset_addr, 2 * BytesPerInt); // Rcurrent_pair now points to first pair.

  __ mtctr(Rcount);
  __ cmpwi(CCR0, Rcount, 0);
  __ bne(CCR0, Lloop_entry);

  // Default case
  __ bind(Ldefault_case);
  __ get_u4(Roffset, Rdef_offset_addr, 0, InterpreterMacroAssembler::Signed);
  if (ProfileInterpreter) {
    __ profile_switch_default(Rdef_offset_addr, Rcount/* scratch */);
  }
  __ b(Lcontinue_execution);

  // Next iteration
  __ bind(Lsearch_loop);
  __ bdz(Ldefault_case);
  __ addi(Rcurrent_pair, Rcurrent_pair, 2 * BytesPerInt);
  __ bind(Lloop_entry);
  __ get_u4(Rvalue, Rcurrent_pair, 0, InterpreterMacroAssembler::Unsigned);
  __ cmpw(CCR0, Rvalue, Rcmp_value);
  __ bne(CCR0, Lsearch_loop);

  // Found, load offset.
  __ get_u4(Roffset, Rcurrent_pair, BytesPerInt, InterpreterMacroAssembler::Signed);
  // Calculate case index and profile
  __ mfctr(Rcurrent_pair);
  if (ProfileInterpreter) {
    __ sub(Rcurrent_pair, Rcount, Rcurrent_pair);
    __ profile_switch_case(Rcurrent_pair, Rcount /*scratch*/, Rdef_offset_addr/*scratch*/, Rscratch);
  }

  __ bind(Lcontinue_execution);
  __ add(R14_bcp, Roffset, R14_bcp);
  __ dispatch_next(vtos);
}

// Table switch using binary search (value/offset pairs are ordered).
// Bytecode stream format:
// Bytecode (1) | 4-byte padding | default offset (4) | count (4) | value/offset pair1 (8) | value/offset pair2 (8) | ...
// Note: Everything is big-endian format here. So on little endian machines, we have to revers offset and count and cmp value.
void TemplateTable::fast_binaryswitch() {

  transition(itos, vtos);
  // Implementation using the following core algorithm: (copied from Intel)
  //
  // int binary_search(int key, LookupswitchPair* array, int n) {
  //   // Binary search according to "Methodik des Programmierens" by
  //   // Edsger W. Dijkstra and W.H.J. Feijen, Addison Wesley Germany 1985.
  //   int i = 0;
  //   int j = n;
  //   while (i+1 < j) {
  //     // invariant P: 0 <= i < j <= n and (a[i] <= key < a[j] or Q)
  //     // with      Q: for all i: 0 <= i < n: key < a[i]
  //     // where a stands for the array and assuming that the (inexisting)
  //     // element a[n] is infinitely big.
  //     int h = (i + j) >> 1;
  //     // i < h < j
  //     if (key < array[h].fast_match()) {
  //       j = h;
  //     } else {
  //       i = h;
  //     }
  //   }
  //   // R: a[i] <= key < a[i+1] or Q
  //   // (i.e., if key is within array, i is the correct index)
  //   return i;
  // }

  // register allocation
  const Register Rkey     = R17_tos;          // already set (tosca)
  const Register Rarray   = R3_ARG1;
  const Register Ri       = R4_ARG2;
  const Register Rj       = R5_ARG3;
  const Register Rh       = R6_ARG4;
  const Register Rscratch = R11_scratch1;

  const int log_entry_size = 3;
  const int entry_size = 1 << log_entry_size;

  Label found;

  // Find Array start,
  __ addi(Rarray, R14_bcp, 3 * BytesPerInt);
  __ clrri(Rarray, Rarray, log2_long((jlong)BytesPerInt));

  // initialize i & j
  __ li(Ri,0);
  __ get_u4(Rj, Rarray, -BytesPerInt, InterpreterMacroAssembler::Unsigned);

  // and start.
  Label entry;
  __ b(entry);

  // binary search loop
  { Label loop;
    __ bind(loop);
    // int h = (i + j) >> 1;
    __ sri(Rh, Rh, 1);
    // if (key < array[h].fast_match()) {
    //   j = h;
    // } else {
    //   i = h;
    // }
    __ sli(Rscratch, Rh, log_entry_size);
#if defined(VM_LITTLE_ENDIAN)
    __ lwbrx(Rscratch, Rscratch, Rarray);
#else
    __ lwzx(Rscratch, Rscratch, Rarray);
#endif

    // if (key < current value)
    //   Rh = Rj
    // else
    //   Rh = Ri
    Label Lgreater;
    __ cmpw(CCR0, Rkey, Rscratch);
    __ bge(CCR0, Lgreater);
    __ mr(Rj, Rh);
    __ b(entry);
    __ bind(Lgreater);
    __ mr(Ri, Rh);

    // while (i+1 < j)
    __ bind(entry);
    __ addi(Rscratch, Ri, 1);
    __ cmpw(CCR0, Rscratch, Rj);
    __ add(Rh, Ri, Rj); // start h = i + j >> 1;

    __ blt(CCR0, loop);
  }

  // End of binary search, result index is i (must check again!).
  Label default_case;
  Label continue_execution;
  if (ProfileInterpreter) {
    __ mr(Rh, Ri);              // Save index in i for profiling.
  }
  // Ri = value offset
  __ sli(Ri, Ri, log_entry_size);
  __ add(Ri, Ri, Rarray);
  __ get_u4(Rscratch, Ri, 0, InterpreterMacroAssembler::Unsigned);

  Label not_found;
  // Ri = offset offset
  __ cmpw(CCR0, Rkey, Rscratch);
  __ beq(CCR0, not_found);
  // entry not found -> j = default offset
  __ get_u4(Rj, Rarray, -2 * BytesPerInt, InterpreterMacroAssembler::Unsigned);
  __ b(default_case);

  __ bind(not_found);
  // entry found -> j = offset
  __ profile_switch_case(Rh, Rj, Rscratch, Rkey);
  __ get_u4(Rj, Ri, BytesPerInt, InterpreterMacroAssembler::Unsigned);

  if (ProfileInterpreter) {
    __ b(continue_execution);
  }

  __ bind(default_case); // fall through (if not profiling)
  __ profile_switch_default(Ri, Rscratch);

  __ bind(continue_execution);

  __ extsw(Rj, Rj);
  __ add(R14_bcp, Rj, R14_bcp);
  __ dispatch_next(vtos);
}

void TemplateTable::_return(TosState state) {
  transition(state, state);
  assert(_desc->calls_vm(),
         "inconsistent calls_vm information"); // call in remove_activation

  if (_desc->bytecode() == Bytecodes::_return_register_finalizer) {

    Register Rscratch     = R11_scratch1,
             Rklass       = R12_scratch2,
             Rklass_flags = Rklass;
    Label Lskip_register_finalizer;

    // Check if the method has the FINALIZER flag set and call into the VM to finalize in this case.
    assert(state == vtos, "only valid state");
    __ l(R17_tos, 0, R18_locals);

    // Load klass of this obj.
    __ load_klass(Rklass, R17_tos);
    __ lwz(Rklass_flags, in_bytes(Klass::access_flags_offset()), Rklass);
    __ testbitdi(CCR0, R0, Rklass_flags, exact_log2(JVM_ACC_HAS_FINALIZER));
    __ bfalse(CCR0, Lskip_register_finalizer);

    __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::register_finalizer), R17_tos /* obj */);

    __ align(32, 12);
    __ bind(Lskip_register_finalizer);
  }

  // Move the result value into the correct register and remove memory stack frame.
  __ remove_activation(state, /* throw_monitor_exception */ true);
  // Restoration of lr done by remove_activation.
  switch (state) {
    // Narrow result if state is itos but result type is smaller.
    // Need to narrow in the return bytecode rather than in generate_return_entry
    // since compiled code callers expect the result to already be narrowed.
    case itos: PPC64_ONLY( __ narrow(R17_tos); ) /* fall through */
    case btos:
    case ztos:
    case ctos:
    case stos:
    case atos: __ mr(R3_RET, R17_tos); break;
    case ltos: NOT_PPC64( __ mr(R3_RET, R30_tos2); __ mr(R4_RET2, R17_tos);)
               PPC64_ONLY(__ mr(R3_RET, R17_tos);)
               break;
#ifndef SPE_ABI
    case ftos:
    case dtos: __ fmr(F1_RET, F15_ftos); break;
#elif defined(USE_SPE) // SPE_ABI defined
    case ftos: __ mr(R3_RET, R17_tos); break;
    case dtos:
     __ evmergehilo(R3_RET, R17_tos, R17_tos);
     break;
#else // SPE_ABI and not USE_SPE
    case ftos: __ stfs(F15_ftos, 0, R15_esp);
               __ lwz(R3_RET, 0, R15_esp);
               break;
    case dtos: __ stfd(F15_ftos, -4, R15_esp);
               __ lwz(R3_RET, -4, R15_esp);
               __ lwz(R4_RET2, 0, R15_esp);
               break;
#endif
    case vtos: // This might be a constructor. Final fields (and volatile fields on PPC64) need
               // to get visible before the reference to the object gets stored anywhere.
               __ membar(Assembler::StoreStore); break;
    default  : ShouldNotReachHere();
  }
  __ blr();
}

// ============================================================================
// Constant pool cache access
//
// Memory ordering:
//
// Like done in C++ interpreter, we load the fields
//   - _indices
//   - _f12_oop
// acquired, because these are asked if the cache is already resolved. We don't
// want to float loads above this check.
// See also comments in ConstantPoolCacheEntry::bytecode_1(),
// ConstantPoolCacheEntry::bytecode_2() and ConstantPoolCacheEntry::f1();

// Call into the VM if call site is not yet resolved
//
// Input regs:
//   - None, all passed regs are outputs.
//
// Returns:
//   - Rcache:  The const pool cache entry that contains the resolved result.
//   - Rresult: Either noreg or output for f1/f2.
//
// Kills:
//   - Rscratch
void TemplateTable::resolve_cache_and_index(int byte_no, Register Rcache, Register Rscratch, size_t index_size) {

  __ get_cache_and_index_at_bcp(Rcache, 1, index_size);
  Label Lresolved, Ldone;

  assert(byte_no == f1_byte || byte_no == f2_byte, "byte_no out of range");
  // We are resolved if the indices offset contains the current bytecode.
#if defined(VM_LITTLE_ENDIAN)
  __ lbz(Rscratch, in_bytes(ConstantPoolCache::base_offset() + ConstantPoolCacheEntry::indices_offset()) + byte_no + 1, Rcache);
#else
  __ lbz(Rscratch, in_bytes(ConstantPoolCache::base_offset() + ConstantPoolCacheEntry::indices_offset()) + PPC64_ONLY(7) NOT_PPC64(3) - (byte_no + 1), Rcache);
#endif
  // Acquire by cmp-br-isync (see below).
  __ cmpi(CCR0, Rscratch, (int)bytecode());
  __ beq(CCR0, Lresolved);

  address entry = NULL;
  switch (bytecode()) {
    case Bytecodes::_getstatic      : // fall through
    case Bytecodes::_putstatic      : // fall through
    case Bytecodes::_getfield       : // fall through
    case Bytecodes::_putfield       : entry = CAST_FROM_FN_PTR(address, InterpreterRuntime::resolve_get_put); break;
    case Bytecodes::_invokevirtual  : // fall through
    case Bytecodes::_invokespecial  : // fall through
    case Bytecodes::_invokestatic   : // fall through
    case Bytecodes::_invokeinterface: entry = CAST_FROM_FN_PTR(address, InterpreterRuntime::resolve_invoke); break;
    case Bytecodes::_invokehandle   : entry = CAST_FROM_FN_PTR(address, InterpreterRuntime::resolve_invokehandle); break;
    case Bytecodes::_invokedynamic  : entry = CAST_FROM_FN_PTR(address, InterpreterRuntime::resolve_invokedynamic); break;
    default                         : ShouldNotReachHere(); break;
  }
  __ li(R4_ARG2, (int)bytecode());
  __ call_VM(noreg, entry, R4_ARG2, true);

  // Update registers with resolved info.
  __ get_cache_and_index_at_bcp(Rcache, 1, index_size);
  __ b(Ldone);

  __ bind(Lresolved);
  __ isync(); // Order load wrt. succeeding loads.
  __ bind(Ldone);
}

// Load the constant pool cache entry at field accesses into registers.
// The Rcache and Rindex registers must be set before call.
// Input:
//   - Rcache, Rindex
// Output:
//   - Robj, Roffset, Rflags
void TemplateTable::load_field_cp_cache_entry(Register Robj,
                                              Register Rcache,
                                              Register Rindex /* unused on PPC64 */,
                                              Register Roffset,
                                              Register Rflags,
                                              bool is_static = false) {
  assert_different_registers(Rcache, Rflags, Roffset);
  // assert(Rindex == noreg, "parameter not used on PPC64");

  ByteSize cp_base_offset = ConstantPoolCache::base_offset();
  __ l(Rflags, in_bytes(cp_base_offset) + in_bytes(ConstantPoolCacheEntry::flags_offset()), Rcache);
  __ l(Roffset, in_bytes(cp_base_offset) + in_bytes(ConstantPoolCacheEntry::f2_offset()), Rcache);
  if (is_static) {
    __ l(Robj, in_bytes(cp_base_offset) + in_bytes(ConstantPoolCacheEntry::f1_offset()), Rcache);
    __ l(Robj, in_bytes(Klass::java_mirror_offset()), Robj);
    // Acquire not needed here. Following access has an address dependency on this value.
  }
}

// Load the constant pool cache entry at invokes into registers.
// Resolve if necessary.

// Input Registers:
//   - None, bcp is used, though
//
// Return registers:
//   - Rmethod       (f1 field or f2 if invokevirtual)
//   - Ritable_index (f2 field)
//   - Rflags        (flags field)
//
// Kills:
//   - R21
//
void TemplateTable::load_invoke_cp_cache_entry(int byte_no,
                                               Register Rmethod,
                                               Register Ritable_index,
                                               Register Rflags,
                                               bool is_invokevirtual,
                                               bool is_invokevfinal,
                                               bool is_invokedynamic) {

  ByteSize cp_base_offset = ConstantPoolCache::base_offset();
  // Determine constant pool cache field offsets.
  assert(is_invokevirtual == (byte_no == f2_byte), "is_invokevirtual flag redundant");
  const int method_offset = in_bytes(cp_base_offset + (is_invokevirtual ? ConstantPoolCacheEntry::f2_offset() : ConstantPoolCacheEntry::f1_offset()));
  const int flags_offset  = in_bytes(cp_base_offset + ConstantPoolCacheEntry::flags_offset());
  // Access constant pool cache fields.
  const int index_offset  = in_bytes(cp_base_offset + ConstantPoolCacheEntry::f2_offset());

  Register Rcache = R21_tmp1; // Note: same register as R21_sender_SP.

  if (is_invokevfinal) {
    assert(Ritable_index == noreg, "register not used");
    // Already resolved.
    __ get_cache_and_index_at_bcp(Rcache, 1);
  } else {
    resolve_cache_and_index(byte_no, Rcache, R0, is_invokedynamic ? sizeof(u4) : sizeof(u2));
  }

  __ l(Rmethod, method_offset, Rcache);
  __ l(Rflags, flags_offset, Rcache);

  if (Ritable_index != noreg) {
    __ l(Ritable_index, index_offset, Rcache);
  }
}

// ============================================================================
// Field access

// Volatile variables demand their effects be made known to all CPU's
// in order. Store buffers on most chips allow reads & writes to
// reorder; the JMM's ReadAfterWrite.java test fails in -Xint mode
// without some kind of memory barrier (i.e., it's not sufficient that
// the interpreter does not reorder volatile references, the hardware
// also must not reorder them).
//
// According to the new Java Memory Model (JMM):
// (1) All volatiles are serialized wrt to each other. ALSO reads &
//     writes act as aquire & release, so:
// (2) A read cannot let unrelated NON-volatile memory refs that
//     happen after the read float up to before the read. It's OK for
//     non-volatile memory refs that happen before the volatile read to
//     float down below it.
// (3) Similar a volatile write cannot let unrelated NON-volatile
//     memory refs that happen BEFORE the write float down to after the
//     write. It's OK for non-volatile memory refs that happen after the
//     volatile write to float up before it.
//
// We only put in barriers around volatile refs (they are expensive),
// not _between_ memory refs (that would require us to track the
// flavor of the previous memory refs). Requirements (2) and (3)
// require some barriers before volatile stores and after volatile
// loads. These nearly cover requirement (1) but miss the
// volatile-store-volatile-load case.  This final case is placed after
// volatile-stores although it could just as well go before
// volatile-loads.

// The registers cache and index expected to be set before call.
// Correct values of the cache and index registers are preserved.
// Kills:
//   Rcache (if has_tos)
//   Rscratch
void TemplateTable::jvmti_post_field_access(Register Rcache, Register Rscratch, bool is_static, bool has_tos) {

  assert_different_registers(Rcache, Rscratch);

  if (JvmtiExport::can_post_field_access()) {
    ByteSize cp_base_offset = ConstantPoolCache::base_offset();
    Label Lno_field_access_post;

    // Check if post field access in enabled.
    int offs = __ load_const_optimized(Rscratch, JvmtiExport::get_field_access_count_addr(), R0, true);
    __ lwz(Rscratch, offs, Rscratch);

    __ cmpwi(CCR0, Rscratch, 0);
    __ beq(CCR0, Lno_field_access_post);

    // Post access enabled - do it!
    __ addi(Rcache, Rcache, in_bytes(cp_base_offset));
    if (is_static) {
      __ li(R17_tos, 0);
    } else {
      if (has_tos) {
        // The fast bytecode versions have obj ptr in register.
        // Thus, save object pointer before call_VM() clobbers it
        // put object on tos where GC wants it.
        __ push_ptr(R17_tos);
      } else {
        // Load top of stack (do not pop the value off the stack).
        __ l(R17_tos, Interpreter::expr_offset_in_bytes(0), R15_esp);
      }
      __ verify_oop(R17_tos);
    }
    // tos:   object pointer or NULL if static
    // cache: cache entry pointer
    __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::post_field_access), R17_tos, Rcache);
    if (!is_static && has_tos) {
      // Restore object pointer.
      __ pop_ptr(R17_tos);
      __ verify_oop(R17_tos);
    } else {
      // Cache is still needed to get class or obj.
      __ get_cache_and_index_at_bcp(Rcache, 1);
    }

    __ align(32, 12);
    __ bind(Lno_field_access_post);
  }
}

// kills R11_scratch1
void TemplateTable::pop_and_check_object(Register Roop) {
  Register Rtmp = R11_scratch1;

  assert_different_registers(Rtmp, Roop);
  __ pop_ptr(Roop);
  // For field access must check obj.
  __ null_check_throw(Roop, -1, Rtmp);
  __ verify_oop(Roop);
}

// PPC64: implement volatile loads as fence-store-acquire.
void TemplateTable::getfield_or_static(int byte_no, bool is_static) {
  transition(vtos, vtos);

  Label Lacquire, Lisync;

  const Register Rcache        = R3_ARG1,
                 Rclass_or_obj = R22_tmp2,
                 Roffset       = R23_tmp3,
                 Rflags        = R31,
                 Rbtable       = R5_ARG3,
                 Rbc           = R6_ARG4,
                 Rscratch      = R12_scratch2;

  static address field_branch_table[number_of_states],
                 static_branch_table[number_of_states];

  address* branch_table = is_static ? static_branch_table : field_branch_table;

  // Get field offset.
  resolve_cache_and_index(byte_no, Rcache, Rscratch, sizeof(u2));

  // JVMTI support
  jvmti_post_field_access(Rcache, Rscratch, is_static, false);

  // Load after possible GC.
  load_field_cp_cache_entry(Rclass_or_obj, Rcache, noreg, Roffset, Rflags, is_static);

  // Load pointer to branch table.
  __ load_const_optimized(Rbtable, (address)branch_table, Rscratch);

  // Get volatile flag.
  __ rlicl(Rscratch, Rflags, 64-ConstantPoolCacheEntry::is_volatile_shift, 63); // Extract volatile bit.
  // Note: sync is needed before volatile load on PPC64.

  // Check field type.
  __ rlicl(Rflags, Rflags, 64-ConstantPoolCacheEntry::tos_state_shift, 64-ConstantPoolCacheEntry::tos_state_bits);

#ifdef ASSERT
  Label LFlagInvalid;
  __ cmpli(CCR0, Rflags, number_of_states);
  __ bge(CCR0, LFlagInvalid);
#endif

  // Load from branch table and dispatch (volatile case: one instruction ahead).
  __ sli(Rflags, Rflags, LogBytesPerWord);
  __ cmpwi(CCR6, Rscratch, 1); // Volatile?
  if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ sli(Rscratch, Rscratch, exact_log2(BytesPerInstWord)); // Volatile ? size of 1 instruction : 0.
  }
  __ lx(Rbtable, Rbtable, Rflags);

  // Get the obj from stack.
  if (!is_static) {
    pop_and_check_object(Rclass_or_obj); // Kills R11_scratch1.
  } else {
    __ verify_oop(Rclass_or_obj);
  }

  if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ subf(Rbtable, Rscratch, Rbtable); // Point to volatile/non-volatile entry point.
  }
  __ mtctr(Rbtable);
  __ bctr();

#ifdef ASSERT
  __ bind(LFlagInvalid);
  __ stop("got invalid flag", 0x654);

  // __ bind(Lvtos);
  address pc_before_fence = __ pc();
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(__ pc() - pc_before_fence == (ptrdiff_t)BytesPerInstWord, "must be single instruction");
  assert(branch_table[vtos] == 0, "can't compute twice");
  branch_table[vtos] = __ pc(); // non-volatile_entry point
  __ stop("vtos unexpected", 0x655);
#endif

  __ align(32, 28, 28); // Align load.
  // __ bind(Ldtos);
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[dtos] == 0, "can't compute twice");
  branch_table[dtos] = __ pc(); // non-volatile_entry point
#ifndef USE_SPE
  __ lfdx(F15_ftos, Rclass_or_obj, Roffset);
  __ push(dtos);

  if (!is_static) patch_bytecode(Bytecodes::_fast_dgetfield, Rbc, Rscratch);
  {
    Label acquire_double;
    __ beq(CCR6, acquire_double); // Volatile?
    __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
    __ bind(acquire_double);
    __ fcmpu(CCR0, F15_ftos, F15_ftos); // Acquire by cmp-br-isync.
    __ beq_predict_taken(CCR0, Lisync);
    __ b(Lisync); // In case of NAN.
  }
#else
  __ evlddx_aligned(R17_tos, Rclass_or_obj, Roffset);
  __ push(dtos);
  if (!is_static) patch_bytecode(Bytecodes::_fast_dgetfield, Rbc, Rscratch);
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
#endif

  __ align(32, 28, 28); // Align load.
  // __ bind(Lftos);
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ftos] == 0, "can't compute twice");
  branch_table[ftos] = __ pc(); // non-volatile_entry point
#ifndef USE_SPE
  __ lfsx(F15_ftos, Rclass_or_obj, Roffset);
  __ push(ftos);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_fgetfield, Rbc, Rscratch); }
  {
    Label acquire_float;
    __ beq(CCR6, acquire_float); // Volatile?
    __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
    __ bind(acquire_float);
    __ fcmpu(CCR0, F15_ftos, F15_ftos); // Acquire by cmp-br-isync.
    __ beq_predict_taken(CCR0, Lisync);
    __ b(Lisync); // In case of NAN.
  }
#else
  __ lwax(R17_tos, Rclass_or_obj, Roffset);
  __ push(ftos);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_fgetfield, Rbc, Rscratch); }
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
#endif
  __ align(32, 28, 28); // Align load.
  // __ bind(Litos);
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[itos] == 0, "can't compute twice");
  branch_table[itos] = __ pc(); // non-volatile_entry point
  __ lwax(R17_tos, Rclass_or_obj, Roffset);
  __ push(itos);
  if (!is_static) patch_bytecode(Bytecodes::_fast_igetfield, Rbc, Rscratch);
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align load.
  // __ bind(Lltos);
#ifdef PPC64
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ltos] == 0, "can't compute twice");
  branch_table[ltos] = __ pc(); // non-volatile_entry point
  __ ldx(R17_tos, Rclass_or_obj, Roffset);
  __ push(ltos);
  if (!is_static) patch_bytecode(Bytecodes::_fast_lgetfield, Rbc, Rscratch);
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
#else

  {
    Label LltosVolatile;
    __ bind(LltosVolatile);
    __ fence();
#ifndef SPE_ATOMIC
    __ lfdx(F15_ftos, Rclass_or_obj, Roffset);
#else // SPE_ATOMIC
    __ evlddx_aligned(R17_tos, Rclass_or_obj, Roffset);
#endif // SPE_ATOMIC
    __ push(dtos);
    if (!is_static) patch_bytecode(Bytecodes::_fast_lgetfield, Rbc, Rscratch);
    __ b(Lacquire); // Volatile!
    __ b(LltosVolatile); // Volatile entry point (one instruction before non-volatile_entry point).
  }
  assert(branch_table[ltos] == 0, "can't compute twice");
  branch_table[ltos] = __ pc(); // non-volatile_entry point
  __ lwz(R30_tos2, Rclass_or_obj, Roffset);
  __ add(Rscratch, wordSize, Roffset);
  __ lwz(R17_tos, Rclass_or_obj, Rscratch);
  __ push(ltos);
  if (!is_static) patch_bytecode(Bytecodes::_fast_lgetfield, Rbc, Rscratch);
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
#endif // PPC64

  __ align(32, 28, 28); // Align load.
  // __ bind(Lbtos);
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[btos] == 0, "can't compute twice");
  branch_table[btos] = __ pc(); // non-volatile_entry point
  __ lbzx(R17_tos, Rclass_or_obj, Roffset);
  __ extsb(R17_tos, R17_tos);
  __ push(btos);
  if (!is_static) patch_bytecode(Bytecodes::_fast_bgetfield, Rbc, Rscratch);
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align load.
  // __ bind(Lztos); (same code as btos)
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ztos] == 0, "can't compute twice");
  branch_table[ztos] = __ pc(); // non-volatile_entry point
  __ lbzx(R17_tos, Rclass_or_obj, Roffset);
  __ extsb(R17_tos, R17_tos);
  __ push(ztos);
  if (!is_static) {
    // use btos rewriting, no truncating to t/f bit is needed for getfield.
    patch_bytecode(Bytecodes::_fast_bgetfield, Rbc, Rscratch);
  }
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align load.
  // __ bind(Lctos);
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ctos] == 0, "can't compute twice");
  branch_table[ctos] = __ pc(); // non-volatile_entry point
  __ lhzx(R17_tos, Rclass_or_obj, Roffset);
  __ push(ctos);
  if (!is_static) patch_bytecode(Bytecodes::_fast_cgetfield, Rbc, Rscratch);
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align load.
  // __ bind(Lstos);
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[stos] == 0, "can't compute twice");
  branch_table[stos] = __ pc(); // non-volatile_entry point
  __ lhax(R17_tos, Rclass_or_obj, Roffset);
  __ push(stos);
  if (!is_static) patch_bytecode(Bytecodes::_fast_sgetfield, Rbc, Rscratch);
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align load.
  // __ bind(Latos);
  __ fence(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[atos] == 0, "can't compute twice");
  branch_table[atos] = __ pc(); // non-volatile_entry point
  __ load_heap_oop(R17_tos, (RegisterOrConstant)Roffset, Rclass_or_obj);
  __ verify_oop(R17_tos);
  __ push(atos);
  //__ dcbt(R17_tos); // prefetch
  if (!is_static) patch_bytecode(Bytecodes::_fast_agetfield, Rbc, Rscratch);
  __ beq(CCR6, Lacquire); // Volatile?
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 12);
  __ bind(Lacquire);
#ifndef PPC64
  __ twi_0(R30_tos2);
#endif
  __ twi_0(R17_tos);
  __ bind(Lisync);
  __ isync(); // acquire

#ifdef ASSERT
  for (int i = 0; i<number_of_states; ++i) {
    assert(branch_table[i], "get initialization");
    //tty->print_cr("get: %s_branch_table[%d] = 0x%llx (opcode 0x%llx)",
    //              is_static ? "static" : "field", i, branch_table[i], *((unsigned int*)branch_table[i]));
  }
#endif
}

void TemplateTable::getfield(int byte_no) {
  getfield_or_static(byte_no, false);
}

void TemplateTable::getstatic(int byte_no) {
  getfield_or_static(byte_no, true);
}

// The registers cache and index expected to be set before call.
// The function may destroy various registers, just not the cache and index registers.
void TemplateTable::jvmti_post_field_mod(Register Rcache, Register Rscratch, bool is_static) {

  assert_different_registers(Rcache, Rscratch, R6_ARG4);

  if (JvmtiExport::can_post_field_modification()) {
    Label Lno_field_mod_post;

    // Check if post field access in enabled.
    int offs = __ load_const_optimized(Rscratch, JvmtiExport::get_field_modification_count_addr(), R0, true);
    __ lwz(Rscratch, offs, Rscratch);

    __ cmpwi(CCR0, Rscratch, 0);
    __ beq(CCR0, Lno_field_mod_post);

    // Do the post
    ByteSize cp_base_offset = ConstantPoolCache::base_offset();
    const Register Robj = Rscratch;

    __ addi(Rcache, Rcache, in_bytes(cp_base_offset));
    if (is_static) {
      // Life is simple. Null out the object pointer.
      __ li(Robj, 0);
    } else {
      // In case of the fast versions, value lives in registers => put it back on tos.
      int offs = Interpreter::expr_offset_in_bytes(0);
      Register base = R15_esp;
      switch(bytecode()) {
        case Bytecodes::_fast_aputfield: __ push_ptr(); offs+= Interpreter::stackElementSize; break;
        case Bytecodes::_fast_iputfield: // Fall through
        case Bytecodes::_fast_bputfield: // Fall through
        case Bytecodes::_fast_zputfield: // Fall through
        case Bytecodes::_fast_cputfield: // Fall through
        case Bytecodes::_fast_sputfield: __ push_i(); offs+=  Interpreter::stackElementSize; break;
        case Bytecodes::_fast_lputfield: __ push_l(); offs+=2*Interpreter::stackElementSize; break;
        case Bytecodes::_fast_fputfield: __ push_f(); offs+=  Interpreter::stackElementSize; break;
        case Bytecodes::_fast_dputfield: __ push_d(); offs+=2*Interpreter::stackElementSize; break;
        default: {
          offs = 0;
          base = Robj;
          const Register Rflags = Robj;
          Label is_one_slot;
          // Life is harder. The stack holds the value on top, followed by the
          // object. We don't know the size of the value, though; it could be
          // one or two words depending on its type. As a result, we must find
          // the type to determine where the object is.
          __ l(Rflags, in_bytes(ConstantPoolCacheEntry::flags_offset()), Rcache); // Big Endian
          __ rlicl(Rflags, Rflags, 64-ConstantPoolCacheEntry::tos_state_shift, 64-ConstantPoolCacheEntry::tos_state_bits);

          __ cmpwi(CCR0, Rflags, ltos);
          __ cmpwi(CCR1, Rflags, dtos);
          __ addi(base, R15_esp, Interpreter::expr_offset_in_bytes(1));
          __ crnor(/*CR0 eq*/2, /*CR1 eq*/4+2, /*CR0 eq*/2);
          __ beq(CCR0, is_one_slot);
          __ addi(base, R15_esp, Interpreter::expr_offset_in_bytes(2));
          __ bind(is_one_slot);
          break;
        }
      }
      __ l(Robj, offs, base);
      __ verify_oop(Robj);
    }

    __ addi(R6_ARG4, R15_esp, Interpreter::expr_offset_in_bytes(0));
    __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::post_field_modification), Robj, Rcache, R6_ARG4);
    __ get_cache_and_index_at_bcp(Rcache, 1);

    // In case of the fast versions, value lives in registers => put it back on tos.
    switch(bytecode()) {
      case Bytecodes::_fast_aputfield: __ pop_ptr(); break;
      case Bytecodes::_fast_iputfield: // Fall through
      case Bytecodes::_fast_bputfield: // Fall through
      case Bytecodes::_fast_zputfield: // Fall through
      case Bytecodes::_fast_cputfield: // Fall through
      case Bytecodes::_fast_sputfield: __ pop_i(); break;
      case Bytecodes::_fast_lputfield: __ pop_l(); break;
      case Bytecodes::_fast_fputfield: __ pop_f(); break;
      case Bytecodes::_fast_dputfield: __ pop_d(); break;
      default: break; // Nothin' to do.
    }

    __ align(32, 12);
    __ bind(Lno_field_mod_post);
  }
}

// PPC64: implement volatile stores as release-store (return bytecode contains an additional release).
void TemplateTable::putfield_or_static(int byte_no, bool is_static) {
  Label Lvolatile;

  const Register Rcache        = R5_ARG3,  // Do not use ARG1/2 (causes trouble in jvmti_post_field_mod).
                 Rclass_or_obj = R31,      // Needs to survive C call.
                 Roffset       = R22_tmp2, // Needs to survive C call.
                 Rflags        = R3_ARG1,
                 Rbtable       = R4_ARG2,
                 Rscratch      = R11_scratch1,
                 Rscratch2     = R12_scratch2,
                 Rscratch3     = R6_ARG4,
                 Rbc           = Rscratch3;
  const ConditionRegister CR_is_vol = CCR2; // Non-volatile condition register (survives runtime call in do_oop_store).

  static address field_branch_table[number_of_states],
                 static_branch_table[number_of_states];

  address* branch_table = is_static ? static_branch_table : field_branch_table;

  // Stack (grows up):
  //  value
  //  obj

  // Load the field offset.
  resolve_cache_and_index(byte_no, Rcache, Rscratch, sizeof(u2));
  jvmti_post_field_mod(Rcache, Rscratch, is_static);
  load_field_cp_cache_entry(Rclass_or_obj, Rcache, noreg, Roffset, Rflags, is_static);

  // Load pointer to branch table.
  __ load_const_optimized(Rbtable, (address)branch_table, Rscratch);

  // Get volatile flag.
  __ rlicl(Rscratch, Rflags, 64-ConstantPoolCacheEntry::is_volatile_shift, 63); // Extract volatile bit.

  // Check the field type.
  __ rlicl(Rflags, Rflags, 64-ConstantPoolCacheEntry::tos_state_shift, 64-ConstantPoolCacheEntry::tos_state_bits);

#ifdef ASSERT
  Label LFlagInvalid;
  __ cmpli(CCR0, Rflags, number_of_states);
  __ bge(CCR0, LFlagInvalid);
#endif

  // Load from branch table and dispatch (volatile case: one instruction ahead).
  __ sli(Rflags, Rflags, LogBytesPerWord);
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) { __ cmpwi(CR_is_vol, Rscratch, 1); } // Volatile?
  __ sli(Rscratch, Rscratch, exact_log2(BytesPerInstWord)); // Volatile? size of instruction 1 : 0.
  __ lx(Rbtable, Rbtable, Rflags);

  __ subf(Rbtable, Rscratch, Rbtable); // Point to volatile/non-volatile entry point.
  __ mtctr(Rbtable);
  __ bctr();

#ifdef ASSERT
  __ bind(LFlagInvalid);
  __ stop("got invalid flag", 0x656);

  // __ bind(Lvtos);
  address pc_before_release = __ pc();
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(__ pc() - pc_before_release == (ptrdiff_t)BytesPerInstWord, "must be single instruction");
  assert(branch_table[vtos] == 0, "can't compute twice");
  branch_table[vtos] = __ pc(); // non-volatile_entry point
  __ stop("vtos unexpected", 0x657);
#endif

  __ align(32, 28, 28); // Align pop.
  // __ bind(Ldtos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[dtos] == 0, "can't compute twice");
  branch_table[dtos] = __ pc(); // non-volatile_entry point
  __ pop(dtos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
#ifndef USE_SPE
  __ stfdx(F15_ftos, Rclass_or_obj, Roffset);
#else
  __ evstddx_aligned(R17_tos, Rclass_or_obj, Roffset);
#endif
  if (!is_static) { patch_bytecode(Bytecodes::_fast_dputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align pop.
  // __ bind(Lftos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ftos] == 0, "can't compute twice");
  branch_table[ftos] = __ pc(); // non-volatile_entry point
  __ pop(ftos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
#ifndef USE_SPE
  __ stfsx(F15_ftos, Rclass_or_obj, Roffset);
#else
  __ stwx(R17_tos, Rclass_or_obj, Roffset);
#endif
  if (!is_static) { patch_bytecode(Bytecodes::_fast_fputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align pop.
  // __ bind(Litos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[itos] == 0, "can't compute twice");
  branch_table[itos] = __ pc(); // non-volatile_entry point
  __ pop(itos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
  __ stwx(R17_tos, Rclass_or_obj, Roffset);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_iputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align pop.
  // __ bind(Lltos);
#ifdef PPC64
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ltos] == 0, "can't compute twice");
  branch_table[ltos] = __ pc(); // non-volatile_entry point
  __ pop(ltos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
  __ stdx(R17_tos, Rclass_or_obj, Roffset);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_lputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
#else
  {
    Label LltosVolatile;
    __ bind(LltosVolatile);
    __ release();
    __ pop(dtos);
    if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
#ifndef SPE_ATOMIC
    __ stfdx(F15_ftos, Rclass_or_obj, Roffset);
#else // SPE_ATOMIC
    __ evstddx_aligned(R17_tos, Rclass_or_obj, Roffset);
#endif // SPE_ATOMIC
    if (!is_static) { patch_bytecode(Bytecodes::_fast_lputfield, Rbc, Rscratch, true, byte_no); }
    if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ b(Lvolatile); // Volatile!
    } else {
      __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
    }
    __ b(LltosVolatile); // Volatile entry point (one instruction before non-volatile_entry point).
  }
  assert(branch_table[ltos] == 0, "can't compute twice");
  branch_table[ltos] = __ pc(); // non-volatile_entry point
  __ pop(ltos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
  __ stwx(R30_tos2, Rclass_or_obj, Roffset);
  __ addi(Rscratch2, Roffset, wordSize);
  __ stwx(R17_tos, Rclass_or_obj, Rscratch2);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_lputfield, Rbc, Rscratch, true, byte_no); }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
#endif

  __ align(32, 28, 28); // Align pop.
  // __ bind(Lbtos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[btos] == 0, "can't compute twice");
  branch_table[btos] = __ pc(); // non-volatile_entry point
  __ pop(btos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
  __ stbx(R17_tos, Rclass_or_obj, Roffset);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_bputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align pop.
  // __ bind(Lztos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ztos] == 0, "can't compute twice");
  branch_table[ztos] = __ pc(); // non-volatile_entry point
  __ pop(ztos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
  __ andi(R17_tos, R17_tos, 0x1);
  __ stbx(R17_tos, Rclass_or_obj, Roffset);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_zputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align pop.
  // __ bind(Lctos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[ctos] == 0, "can't compute twice");
  branch_table[ctos] = __ pc(); // non-volatile_entry point
  __ pop(ctos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1..
  __ sthx(R17_tos, Rclass_or_obj, Roffset);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_cputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align pop.
  // __ bind(Lstos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[stos] == 0, "can't compute twice");
  branch_table[stos] = __ pc(); // non-volatile_entry point
  __ pop(stos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // Kills R11_scratch1.
  __ sthx(R17_tos, Rclass_or_obj, Roffset);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_sputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
  }
  __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

  __ align(32, 28, 28); // Align pop.
  // __ bind(Latos);
  __ release(); // Volatile entry point (one instruction before non-volatile_entry point).
  assert(branch_table[atos] == 0, "can't compute twice");
  branch_table[atos] = __ pc(); // non-volatile_entry point
  __ pop(atos);
  if (!is_static) { pop_and_check_object(Rclass_or_obj); } // kills R11_scratch1
  do_oop_store(_masm, Rclass_or_obj, Roffset, R17_tos, Rscratch, Rscratch2, Rscratch3, _bs->kind(), false /* precise */, true /* check null */);
  if (!is_static) { patch_bytecode(Bytecodes::_fast_aputfield, Rbc, Rscratch, true, byte_no); }
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) {
    __ beq(CR_is_vol, Lvolatile); // Volatile?
    __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

    __ align(32, 12);
    __ bind(Lvolatile);
    __ fence();
  }
  // fallthru: __ b(Lexit);

#ifdef ASSERT
  for (int i = 0; i<number_of_states; ++i) {
    assert(branch_table[i], "put initialization");
    //tty->print_cr("put: %s_branch_table[%d] = 0x%llx (opcode 0x%llx)",
    //              is_static ? "static" : "field", i, branch_table[i], *((unsigned int*)branch_table[i]));
  }
#endif
}

void TemplateTable::putfield(int byte_no) {
  putfield_or_static(byte_no, false);
}

void TemplateTable::putstatic(int byte_no) {
  putfield_or_static(byte_no, true);
}

// See SPARC. On PPC64, we have a different jvmti_post_field_mod which does the job.
void TemplateTable::jvmti_post_fast_field_mod() {
  __ should_not_reach_here();
}

void TemplateTable::fast_storefield(TosState state) {
  transition(state, vtos);

  const Register Rcache        = R5_ARG3,  // Do not use ARG1/2 (causes trouble in jvmti_post_field_mod).
                 Rclass_or_obj = R31,      // Needs to survive C call.
                 Roffset       = R22_tmp2, // Needs to survive C call.
                 Rflags        = R3_ARG1,
                 Rscratch      = R11_scratch1,
                 Rscratch2     = R12_scratch2,
                 Rscratch3     = R4_ARG2;
  const ConditionRegister CR_is_vol = CCR2; // Non-volatile condition register (survives runtime call in do_oop_store).

  // Constant pool already resolved => Load flags and offset of field.
  __ get_cache_and_index_at_bcp(Rcache, 1);
  jvmti_post_field_mod(Rcache, Rscratch, false /* not static */);
  load_field_cp_cache_entry(noreg, Rcache, noreg, Roffset, Rflags, false);

  // Get the obj and the final store addr.
  pop_and_check_object(Rclass_or_obj); // Kills R11_scratch1.

  // Get volatile flag.
  __ rlicl_(Rscratch, Rflags, 64-ConstantPoolCacheEntry::is_volatile_shift, 63); // Extract volatile bit.
  if (!support_IRIW_for_not_multiple_copy_atomic_cpu) { __ cmpi(CR_is_vol, Rscratch, 1); }
  {
    Label LnotVolatile;
    __ beq(CCR0, LnotVolatile);
    __ release();
    __ align(32, 12);
#ifndef PPC64
    if (bytecode() == Bytecodes::_fast_lputfield) {
#ifndef SPE_ATOMIC
      __ stw(R30_tos2, - Interpreter::stackElementSize, R15_esp);
      __ stw(R17_tos, 0, R15_esp);
      __ lfd(F15_ftos, - Interpreter::stackElementSize, R15_esp);
      __ stfdx(F15_ftos, Rclass_or_obj, Roffset);
#else // SPE_ATOMIC
      __ evmergelo(R17_tos, R30_tos2, R17_tos);
      __ evstddx_aligned(R17_tos, Rclass_or_obj, Roffset);
#endif // SPE_ATOMIC
      __ fence();
      __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));
    }
#endif

    __ bind(LnotVolatile);
  }

  // Do the store and fencing.
  switch(bytecode()) {
    case Bytecodes::_fast_aputfield:
      // Store into the field.
      do_oop_store(_masm, Rclass_or_obj, Roffset, R17_tos, Rscratch, Rscratch2, Rscratch3, _bs->kind(), false /* precise */, true /* check null */);
      break;

    case Bytecodes::_fast_fputfield:
#ifndef USE_SPE
      __ stfsx(F15_ftos, Rclass_or_obj, Roffset);
      break;
#else // USE_SPE
      /* passthrough */
#endif // USE_SPE

    case Bytecodes::_fast_iputfield:
      __ stwx(R17_tos, Rclass_or_obj, Roffset);
      break;

    case Bytecodes::_fast_lputfield:
#ifdef PPC64
      __ stdx(R17_tos, Rclass_or_obj, Roffset);
#else // PPC64
      __ stwx(R30_tos2, Rclass_or_obj, Roffset);
      __ addi(Rscratch, Roffset, wordSize);
      __ stwx(R17_tos, Rclass_or_obj, Rscratch);
#endif // PPC64
      break;

    case Bytecodes::_fast_dputfield:
#ifndef USE_SPE
      __ stfdx(F15_ftos, Rclass_or_obj, Roffset);
#else // USE_SPE
      __ evstddx_aligned(R17_tos, Rclass_or_obj, Roffset);
#endif // USE_SPE
      break;
    case Bytecodes::_fast_zputfield:
      __ andi(R17_tos, R17_tos, 0x1);  // boolean is true if LSB is 1
      // fall through to bputfield
    case Bytecodes::_fast_bputfield:
      __ stbx(R17_tos, Rclass_or_obj, Roffset);
      break;

    case Bytecodes::_fast_cputfield:
    case Bytecodes::_fast_sputfield:
      __ sthx(R17_tos, Rclass_or_obj, Roffset);
      break;
    default: ShouldNotReachHere();
  }

  if (!support_IRIW_for_not_multiple_copy_atomic_cpu
      NOT_PPC64(&& (bytecode() != Bytecodes::_fast_lputfield))) {
    Label LVolatile;
    __ beq(CR_is_vol, LVolatile);
    __ dispatch_epilog(vtos, Bytecodes::length_for(bytecode()));

    __ align(32, 12);
    __ bind(LVolatile);
    __ fence();
  }
}

void TemplateTable::fast_accessfield(TosState state) {
  transition(atos, state);

  Label LisVolatile;
  ByteSize cp_base_offset = ConstantPoolCache::base_offset();

  const Register Rcache        = R3_ARG1,
                 Rclass_or_obj = R17_tos,
                 Roffset       = R22_tmp2,
                 Rflags        = R23_tmp3,
                 Rscratch      = R12_scratch2;

  // Constant pool already resolved. Get the field offset.
  __ get_cache_and_index_at_bcp(Rcache, 1);
  load_field_cp_cache_entry(noreg, Rcache, noreg, Roffset, Rflags, false);

  // JVMTI support
  jvmti_post_field_access(Rcache, Rscratch, false, true);

  // Get the load address.
  __ null_check_throw(Rclass_or_obj, -1, Rscratch);

  // Get volatile flag.
  __ rlicl_(Rscratch, Rflags, 64-ConstantPoolCacheEntry::is_volatile_shift, 63); // Extract volatile bit.
  __ bne(CCR0, LisVolatile);

  switch(bytecode()) {
    case Bytecodes::_fast_agetfield:
    {
      __ load_heap_oop(R17_tos, (RegisterOrConstant)Roffset, Rclass_or_obj);
      __ verify_oop(R17_tos);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ load_heap_oop(R17_tos, (RegisterOrConstant)Roffset, Rclass_or_obj);
      __ verify_oop(R17_tos);
      __ twi_0(R17_tos);
      __ isync();
      break;
    }
    case Bytecodes::_fast_lgetfield:
    {
#ifdef PPC64
      __ ldx(R17_tos, Rclass_or_obj, Roffset);
#else
      __ lwz(R30_tos2, Rclass_or_obj, Roffset);
      __ add(Rscratch, wordSize, Roffset);
      __ lwz(R17_tos, Rclass_or_obj, Rscratch);
#endif
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
#ifdef PPC64
      __ ldx(R17_tos, Rclass_or_obj, Roffset);
#else
#ifndef SPE_ATOMIC
      __ lfdx(F15_ftos, Rclass_or_obj, Roffset);
      __ stfd(F15_ftos, - Interpreter::stackElementSize, R15_esp);
      __ lwz(R30_tos2, - Interpreter::stackElementSize, R15_esp);
      __ lwz(R17_tos, 0, R15_esp);
#else // SPE_ATOMIC
      __ evlddx_aligned(R17_tos, Rclass_or_obj, Roffset);
      __ evmergehi(R30_tos2, R30_tos2, R17_tos);
#endif // SPE_ATOMIC
      __ twi_0(R30_tos2);
#endif
      __ twi_0(R17_tos);
      __ isync();
      break;
    }
    case Bytecodes::_fast_bgetfield:
    {
      __ lbzx(R17_tos, Rclass_or_obj, Roffset);
      __ extsb(R17_tos, R17_tos);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lbzx(R17_tos, Rclass_or_obj, Roffset);
      __ twi_0(R17_tos);
      __ extsb(R17_tos, R17_tos);
      __ isync();
      break;
    }
    case Bytecodes::_fast_cgetfield:
    {
      __ lhzx(R17_tos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lhzx(R17_tos, Rclass_or_obj, Roffset);
      __ twi_0(R17_tos);
      __ isync();
      break;
    }
    case Bytecodes::_fast_sgetfield:
    {
      __ lhax(R17_tos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lhax(R17_tos, Rclass_or_obj, Roffset);
      __ twi_0(R17_tos);
      __ isync();
      break;
    }
    case Bytecodes::_fast_fgetfield:
#ifndef USE_SPE
    {
      __ lfsx(F15_ftos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      Label Ldummy;
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lfsx(F15_ftos, Rclass_or_obj, Roffset);
      __ fcmpu(CCR0, F15_ftos, F15_ftos); // Acquire by cmp-br-isync.
      __ bne_predict_not_taken(CCR0, Ldummy);
      __ bind(Ldummy);
      __ isync();
      break;
    }
#else
    // pass-through to igetfield when USE_SPE
#endif
    case Bytecodes::_fast_igetfield:
    {
      __ lwax(R17_tos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lwax(R17_tos, Rclass_or_obj, Roffset);
      __ twi_0(R17_tos);
      __ isync();
      break;
    }
    case Bytecodes::_fast_dgetfield:
    {
#ifndef USE_SPE
      __ lfdx(F15_ftos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      Label Ldummy;
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lfdx(F15_ftos, Rclass_or_obj, Roffset);
      __ fcmpu(CCR0, F15_ftos, F15_ftos); // Acquire by cmp-br-isync.
      __ bne_predict_not_taken(CCR0, Ldummy);
      __ bind(Ldummy);
      __ isync();
#else
      __ evlddx_aligned(R17_tos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()));

      __ bind(LisVolatile);
      Label Ldummy;
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ evlddx_aligned(R17_tos, Rclass_or_obj, Roffset);
      __ efdcmpeq(CCR0, R17_tos, R17_tos); // Acquire by cmp-br-isync.
      __ bne_predict_not_taken(CCR0, Ldummy);
      __ bind(Ldummy);
      __ isync();
#endif
      break;
    }
    default: ShouldNotReachHere();
  }
}

void TemplateTable::fast_xaccess(TosState state) {
  transition(vtos, state);

  Label LisVolatile;
  ByteSize cp_base_offset = ConstantPoolCache::base_offset();
  const Register Rcache        = R3_ARG1,
                 Rclass_or_obj = R17_tos,
                 Roffset       = R22_tmp2,
                 Rflags        = R23_tmp3,
                 Rscratch      = R12_scratch2;

  __ l(Rclass_or_obj, 0, R18_locals);

  // Constant pool already resolved. Get the field offset.
  __ get_cache_and_index_at_bcp(Rcache, 2);
  load_field_cp_cache_entry(noreg, Rcache, noreg, Roffset, Rflags, false);

  // JVMTI support not needed, since we switch back to single bytecode as soon as debugger attaches.

  // Needed to report exception at the correct bcp.
  __ addi(R14_bcp, R14_bcp, 1);

  // Get the load address.
  __ null_check_throw(Rclass_or_obj, -1, Rscratch);

  // Get volatile flag.
  __ rlicl_(Rscratch, Rflags, 64-ConstantPoolCacheEntry::is_volatile_shift, 63); // Extract volatile bit.
  __ bne(CCR0, LisVolatile);

  switch(state) {
  case atos:
    {
      __ load_heap_oop(R17_tos, (RegisterOrConstant)Roffset, Rclass_or_obj);
      __ verify_oop(R17_tos);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()) - 1); // Undo bcp increment.

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ load_heap_oop(R17_tos, (RegisterOrConstant)Roffset, Rclass_or_obj);
      __ verify_oop(R17_tos);
      __ twi_0(R17_tos);
      __ isync();
      break;
    }
  case ftos:
#ifndef USE_SPE
    {
      __ lfsx(F15_ftos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()) - 1); // Undo bcp increment.

      __ bind(LisVolatile);
      Label Ldummy;
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lfsx(F15_ftos, Rclass_or_obj, Roffset);
      __ fcmpu(CCR0, F15_ftos, F15_ftos); // Acquire by cmp-br-isync.
      __ bne_predict_not_taken(CCR0, Ldummy);
      __ bind(Ldummy);
      __ isync();
      break;
    }
#else
  // passthough into itos when USE_SPE
#endif
  case itos:
    {
      __ lwax(R17_tos, Rclass_or_obj, Roffset);
      __ dispatch_epilog(state, Bytecodes::length_for(bytecode()) - 1); // Undo bcp increment.

      __ bind(LisVolatile);
      if (support_IRIW_for_not_multiple_copy_atomic_cpu) { __ fence(); }
      __ lwax(R17_tos, Rclass_or_obj, Roffset);
      __ twi_0(R17_tos);
      __ isync();
      break;
    }
  default: ShouldNotReachHere();
  }
  __ addi(R14_bcp, R14_bcp, -1);
}

// ============================================================================
// Calls

// Common code for invoke
//
// Input:
//   - byte_no
//
// Output:
//   - Rmethod:        The method to invoke next.
//   - Rret_addr:      The return address to return to.
//   - Rindex:         MethodType (invokehandle) or CallSite obj (invokedynamic)
//   - Rrecv:          Cache for "this" pointer, might be noreg if static call.
//   - Rflags:         Method flags from const pool cache.
//
//  Kills:
//   - Rscratch1
//
void TemplateTable::prepare_invoke(int byte_no,
                                   Register Rmethod,  // linked method (or i-klass)
                                   Register Rret_addr,// return address
                                   Register Rindex,   // itable index, MethodType, etc.
                                   Register Rrecv,    // If caller wants to see it.
                                   Register Rflags,   // If caller wants to test it.
                                   Register Rscratch
                                   ) {
  // Determine flags.
  const Bytecodes::Code code = bytecode();
  const bool is_invokeinterface  = code == Bytecodes::_invokeinterface;
  const bool is_invokedynamic    = code == Bytecodes::_invokedynamic;
  const bool is_invokehandle     = code == Bytecodes::_invokehandle;
  const bool is_invokevirtual    = code == Bytecodes::_invokevirtual;
  const bool is_invokespecial    = code == Bytecodes::_invokespecial;
  const bool load_receiver       = (Rrecv != noreg);
  assert(load_receiver == (code != Bytecodes::_invokestatic && code != Bytecodes::_invokedynamic), "");

  assert_different_registers(Rmethod, Rindex, Rflags, Rscratch);
  assert_different_registers(Rmethod, Rrecv, Rflags, Rscratch);
  assert_different_registers(Rret_addr, Rscratch);

  load_invoke_cp_cache_entry(byte_no, Rmethod, Rindex, Rflags, is_invokevirtual, false, is_invokedynamic);

  // Saving of SP done in call_from_interpreter.

  // Maybe push "appendix" to arguments.
  if (is_invokedynamic || is_invokehandle) {
    Label Ldone;
    __ rlicl_(R0, Rflags, 64-ConstantPoolCacheEntry::has_appendix_shift, 63);
    __ beq(CCR0, Ldone);
    // Push "appendix" (MethodType, CallSite, etc.).
    // This must be done before we get the receiver,
    // since the parameter_size includes it.
    __ load_resolved_reference_at_index(Rscratch, Rindex);
    __ verify_oop(Rscratch);
    __ push_ptr(Rscratch);
    __ bind(Ldone);
  }

  // Load receiver if needed (after appendix is pushed so parameter size is correct).
  if (load_receiver) {
    const Register Rparam_count = Rscratch;
    __ andi(Rparam_count, Rflags, ConstantPoolCacheEntry::parameter_size_mask);
    __ load_receiver(Rparam_count, Rrecv);
    __ verify_oop(Rrecv);
  }

  // Get return address.
  {
    Register Rtable_addr = Rscratch;
    Register Rret_type = Rret_addr;
    address table_addr = (address) Interpreter::invoke_return_entry_table_for(code);

    // Get return type. It's coded into the upper 4 bits of the lower half of the 64 bit value.
    __ rlicl(Rret_type, Rflags, 64-ConstantPoolCacheEntry::tos_state_shift, 64-ConstantPoolCacheEntry::tos_state_bits);
    __ load_dispatch_table(Rtable_addr, (address*)table_addr);
    __ sli(Rret_type, Rret_type, LogBytesPerWord);
    // Get return address.
    __ lx(Rret_addr, Rtable_addr, Rret_type);
  }
}

// Helper for virtual calls. Load target out of vtable and jump off!
// Kills all passed registers.
void TemplateTable::generate_vtable_call(Register Rrecv_klass, Register Rindex, Register Rret, Register Rtemp) {

  assert_different_registers(Rrecv_klass, Rtemp, Rret);
  const Register Rtarget_method = Rindex;

  // Get target method & entry point.
  const int base = InstanceKlass::vtable_start_offset() * wordSize;
  // Calc vtable addr scale the vtable index by 8.
  __ sli(Rindex, Rindex, exact_log2(vtableEntry::size() * wordSize));
  // Load target.
  __ addi(Rrecv_klass, Rrecv_klass, base + vtableEntry::method_offset_in_bytes());
  __ lx(Rtarget_method, Rindex, Rrecv_klass);
  // Argument and return type profiling.
  __ profile_arguments_type(Rtarget_method, Rrecv_klass /* scratch1 */, Rtemp /* scratch2 */, true);
  __ call_from_interpreter(Rtarget_method, Rret, Rrecv_klass /* scratch1 */, Rtemp /* scratch2 */);
}

// Virtual or final call. Final calls are rewritten on the fly to run through "fast_finalcall" next time.
void TemplateTable::invokevirtual(int byte_no) {
  transition(vtos, vtos);

  Register Rtable_addr = R11_scratch1,
           Rret_type = R12_scratch2,
           Rret_addr = R5_ARG3,
           Rflags = R22_tmp2, // Should survive C call.
           Rrecv = R3_ARG1,
           Rrecv_klass = Rrecv,
           Rvtableindex_or_method = R31, // Should survive C call.
           Rnum_params = R4_ARG2,
           Rnew_bc = R6_ARG4;

  Label LnotFinal;

  load_invoke_cp_cache_entry(byte_no, Rvtableindex_or_method, noreg, Rflags, /*virtual*/ true, false, false);

  __ testbitdi(CCR0, R0, Rflags, ConstantPoolCacheEntry::is_vfinal_shift);
  __ bfalse(CCR0, LnotFinal);

  patch_bytecode(Bytecodes::_fast_invokevfinal, Rnew_bc, R12_scratch2);
  invokevfinal_helper(Rvtableindex_or_method, Rflags, R11_scratch1, R12_scratch2);

  __ align(32, 12);
  __ bind(LnotFinal);
  // Load "this" pointer (receiver).
  __ rlicl(Rnum_params, Rflags, 64, 48);
  __ load_receiver(Rnum_params, Rrecv);
  __ verify_oop(Rrecv);

  // Get return type. It's coded into the upper 4 bits of the lower half of the 64 bit value.
  __ rlicl(Rret_type, Rflags, 64-ConstantPoolCacheEntry::tos_state_shift, 64-ConstantPoolCacheEntry::tos_state_bits);
  __ load_dispatch_table(Rtable_addr, Interpreter::invoke_return_entry_table());
  __ sli(Rret_type, Rret_type, LogBytesPerWord);
  __ lx(Rret_addr, Rret_type, Rtable_addr);
  __ null_check_throw(Rrecv, oopDesc::klass_offset_in_bytes(), R11_scratch1);
  __ load_klass(Rrecv_klass, Rrecv);
  __ verify_klass_ptr(Rrecv_klass);
  __ profile_virtual_call(Rrecv_klass, R11_scratch1, R12_scratch2, false);

  generate_vtable_call(Rrecv_klass, Rvtableindex_or_method, Rret_addr, R11_scratch1);
}

void TemplateTable::fast_invokevfinal(int byte_no) {
  transition(vtos, vtos);

  assert(byte_no == f2_byte, "use this argument");
  Register Rflags  = R22_tmp2,
           Rmethod = R31;
  load_invoke_cp_cache_entry(byte_no, Rmethod, noreg, Rflags, /*virtual*/ true, /*is_invokevfinal*/ true, false);
  invokevfinal_helper(Rmethod, Rflags, R11_scratch1, R12_scratch2);
}

void TemplateTable::invokevfinal_helper(Register Rmethod, Register Rflags, Register Rscratch1, Register Rscratch2) {

  assert_different_registers(Rmethod, Rflags, Rscratch1, Rscratch2);

  // Load receiver from stack slot.
  Register Rrecv = Rscratch2;
  Register Rnum_params = Rrecv;

  __ l(Rnum_params, in_bytes(Method::const_offset()), Rmethod);
  __ lhz(Rnum_params /* number of params */, in_bytes(ConstMethod::size_of_parameters_offset()), Rnum_params);

  // Get return address.
  Register Rtable_addr = Rscratch1,
           Rret_addr   = Rflags,
           Rret_type   = Rret_addr;
  // Get return type. It's coded into the upper 4 bits of the lower half of the 64 bit value.
  __ rlicl(Rret_type, Rflags, 64-ConstantPoolCacheEntry::tos_state_shift, 64-ConstantPoolCacheEntry::tos_state_bits);
  __ load_dispatch_table(Rtable_addr, Interpreter::invoke_return_entry_table());
  __ sli(Rret_type, Rret_type, LogBytesPerWord);
  __ lx(Rret_addr, Rret_type, Rtable_addr);

  // Load receiver and receiver NULL check.
  __ load_receiver(Rnum_params, Rrecv);
  __ null_check_throw(Rrecv, -1, Rscratch1);

  __ profile_final_call(Rrecv, Rscratch1);
  // Argument and return type profiling.
  __ profile_arguments_type(Rmethod, Rscratch1, Rscratch2, true);

  // Do the call.
  __ call_from_interpreter(Rmethod, Rret_addr, Rscratch1, Rscratch2);
}

void TemplateTable::invokespecial(int byte_no) {
  assert(byte_no == f1_byte, "use this argument");
  transition(vtos, vtos);

  Register Rtable_addr = R3_ARG1,
           Rret_addr   = R4_ARG2,
           Rflags      = R5_ARG3,
           Rreceiver   = R6_ARG4,
           Rmethod     = R31;

  prepare_invoke(byte_no, Rmethod, Rret_addr, noreg, Rreceiver, Rflags, R11_scratch1);

  // Receiver NULL check.
  __ null_check_throw(Rreceiver, -1, R11_scratch1);

  __ profile_call(R11_scratch1, R12_scratch2);
  // Argument and return type profiling.
  __ profile_arguments_type(Rmethod, R11_scratch1, R12_scratch2, false);
  __ call_from_interpreter(Rmethod, Rret_addr, R11_scratch1, R12_scratch2);
}

void TemplateTable::invokestatic(int byte_no) {
  assert(byte_no == f1_byte, "use this argument");
  transition(vtos, vtos);

  Register Rtable_addr = R3_ARG1,
           Rret_addr   = R4_ARG2,
           Rflags      = R5_ARG3;

  prepare_invoke(byte_no, R19_method, Rret_addr, noreg, noreg, Rflags, R11_scratch1);

  __ profile_call(R11_scratch1, R12_scratch2);
  // Argument and return type profiling.
  __ profile_arguments_type(R19_method, R11_scratch1, R12_scratch2, false);
  __ call_from_interpreter(R19_method, Rret_addr, R11_scratch1, R12_scratch2);
}

void TemplateTable::invokeinterface_object_method(Register Rrecv_klass,
                                                  Register Rret,
                                                  Register Rflags,
                                                  Register Rmethod,
                                                  Register Rtemp1,
                                                  Register Rtemp2) {

  assert_different_registers(Rmethod, Rret, Rrecv_klass, Rflags, Rtemp1, Rtemp2);
  Label LnotFinal;

  // Check for vfinal.
  __ testbitdi(CCR0, R0, Rflags, ConstantPoolCacheEntry::is_vfinal_shift);
  __ bfalse(CCR0, LnotFinal);

  Register Rscratch = Rflags; // Rflags is dead now.

  // Final call case.
  __ profile_final_call(Rtemp1, Rscratch);
  // Argument and return type profiling.
  __ profile_arguments_type(Rmethod, Rscratch, Rrecv_klass /* scratch */, true);
  // Do the final call - the index (f2) contains the method.
  __ call_from_interpreter(Rmethod, Rret, Rscratch, Rrecv_klass /* scratch */);

  // Non-final callc case.
  __ bind(LnotFinal);
  __ profile_virtual_call(Rrecv_klass, Rtemp1, Rscratch, false);
  generate_vtable_call(Rrecv_klass, Rmethod, Rret, Rscratch);
}

void TemplateTable::invokeinterface(int byte_no) {
  assert(byte_no == f1_byte, "use this argument");
  transition(vtos, vtos);

  const Register Rscratch1        = R11_scratch1,
                 Rscratch2        = R12_scratch2,
                 Rmethod          = R6_ARG4,
                 Rmethod2         = R9_ARG7,
                 Rinterface_klass = R5_ARG3,
                 Rret_addr        = R8_ARG6,
                 Rindex           = R10_ARG8,
                 Rreceiver        = R3_ARG1,
                 Rrecv_klass      = R4_ARG2,
                 Rflags           = R7_ARG5;

  prepare_invoke(byte_no, Rinterface_klass, Rret_addr, Rmethod, Rreceiver, Rflags, Rscratch1);

  // Get receiver klass.
  __ null_check_throw(Rreceiver, oopDesc::klass_offset_in_bytes(), Rscratch2);
  __ load_klass(Rrecv_klass, Rreceiver);

  // Check corner case object method.
  Label LobjectMethod, L_no_such_interface, Lthrow_ame;
  __ testbitdi(CCR0, R0, Rflags, ConstantPoolCacheEntry::is_forced_virtual_shift);
  __ btrue(CCR0, LobjectMethod);

  __ lookup_interface_method(Rrecv_klass, Rinterface_klass, noreg, noreg, Rscratch1, Rscratch2,
                             L_no_such_interface, /*return_method=*/false);

  __ profile_virtual_call(Rrecv_klass, Rscratch1, Rscratch2, false);

  // Find entry point to call.

  // Get declaring interface class from method
  __ l(Rinterface_klass, in_bytes(Method::const_offset()), Rmethod);
  __ l(Rinterface_klass, in_bytes(ConstMethod::constants_offset()), Rinterface_klass);
  __ l(Rinterface_klass, ConstantPool::pool_holder_offset_in_bytes(), Rinterface_klass);

  // Get itable index from method
  __ lwa(Rindex, in_bytes(Method::itable_index_offset()), Rmethod);
  __ subfic(Rindex, Rindex, Method::itable_index_max);

  __ lookup_interface_method(Rrecv_klass, Rinterface_klass, Rindex, Rmethod2, Rscratch1, Rscratch2,
                             L_no_such_interface);

  __ cmpi(CCR0, Rmethod2, 0);
  __ beq(CCR0, Lthrow_ame);
  // Found entry. Jump off!
  // Argument and return type profiling.
  __ profile_arguments_type(Rmethod2, Rscratch1, Rscratch2, true);
  //__ profile_called_method(Rindex, Rscratch1);
  __ call_from_interpreter(Rmethod2, Rret_addr, Rscratch1, Rscratch2);

  // Vtable entry was NULL => Throw abstract method error.
  __ bind(Lthrow_ame);
  call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::throw_AbstractMethodError));

  // Interface was not found => Throw incompatible class change error.
  __ bind(L_no_such_interface);
  call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::throw_IncompatibleClassChangeError));
  DEBUG_ONLY( __ should_not_reach_here(); )

  // Special case of invokeinterface called for virtual method of
  // java.lang.Object. See ConstantPoolCacheEntry::set_method() for details:
  // The invokeinterface was rewritten to a invokevirtual, hence we have
  // to handle this corner case. This code isn't produced by javac, but could
  // be produced by another compliant java compiler.
  __ bind(LobjectMethod);
  invokeinterface_object_method(Rrecv_klass, Rret_addr, Rflags, Rmethod, Rscratch1, Rscratch2);
}

void TemplateTable::invokedynamic(int byte_no) {
  transition(vtos, vtos);

  const Register Rret_addr = R3_ARG1,
                 Rflags    = R4_ARG2,
                 Rmethod   = R22_tmp2,
                 Rscratch1 = R11_scratch1,
                 Rscratch2 = R12_scratch2;

  if (!EnableInvokeDynamic) {
    // We should not encounter this bytecode if !EnableInvokeDynamic.
    // The verifier will stop it. However, if we get past the verifier,
    // this will stop the thread in a reasonable way, without crashing the JVM.
    __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::throw_IncompatibleClassChangeError));
    // The call_VM checks for exception, so we should never return here.
    __ should_not_reach_here();
    return;
  }

  prepare_invoke(byte_no, Rmethod, Rret_addr, Rscratch1, noreg, Rflags, Rscratch2);

  // Profile this call.
  __ profile_call(Rscratch1, Rscratch2);

  // Off we go. With the new method handles, we don't jump to a method handle
  // entry any more. Instead, we pushed an "appendix" in prepare invoke, which happens
  // to be the callsite object the bootstrap method returned. This is passed to a
  // "link" method which does the dispatch (Most likely just grabs the MH stored
  // inside the callsite and does an invokehandle).
  // Argument and return type profiling.
  __ profile_arguments_type(Rmethod, Rscratch1, Rscratch2, false);
  __ call_from_interpreter(Rmethod, Rret_addr, Rscratch1 /* scratch1 */, Rscratch2 /* scratch2 */);
}

void TemplateTable::invokehandle(int byte_no) {
  transition(vtos, vtos);

  const Register Rret_addr = R3_ARG1,
                 Rflags    = R4_ARG2,
                 Rrecv     = R5_ARG3,
                 Rmethod   = R22_tmp2,
                 Rscratch1 = R11_scratch1,
                 Rscratch2 = R12_scratch2;

  if (!EnableInvokeDynamic) {
    // Rewriter does not generate this bytecode.
    __ should_not_reach_here();
    return;
  }

  prepare_invoke(byte_no, Rmethod, Rret_addr, Rscratch1, Rrecv, Rflags, Rscratch2);
  __ verify_method_ptr(Rmethod);
  __ null_check_throw(Rrecv, -1, Rscratch2);

  __ profile_final_call(Rrecv, Rscratch1);

  // Still no call from handle => We call the method handle interpreter here.
  // Argument and return type profiling.
  __ profile_arguments_type(Rmethod, Rscratch1, Rscratch2, true);
  __ call_from_interpreter(Rmethod, Rret_addr, Rscratch1 /* scratch1 */, Rscratch2 /* scratch2 */);
}

// =============================================================================
// Allocation

// Puts allocated obj ref onto the expression stack.
void TemplateTable::_new() {
  transition(vtos, atos);

  Label Lslow_case,
        Ldone,
        Linitialize_header,
        Lallocate_shared,
        Linitialize_object;  // Including clearing the fields.

  const Register RallocatedObject = R17_tos,
                 RinstanceKlass   = R9_ARG7,
                 Rscratch         = R11_scratch1,
                 Roffset          = R8_ARG6,
                 Rinstance_size   = Roffset,
                 Rcpool           = R4_ARG2,
                 Rtags            = R3_ARG1,
                 Rindex           = R5_ARG3;

  const bool allow_shared_alloc = Universe::heap()->supports_inline_contig_alloc() && !CMSIncrementalMode;

  // --------------------------------------------------------------------------
  // Check if fast case is possible.

  // Load pointers to const pool and const pool's tags array.
  __ get_cpool_and_tags(Rcpool, Rtags);
  // Load index of constant pool entry.
  __ get_2_byte_integer_at_bcp(1, Rindex, InterpreterMacroAssembler::Unsigned);

  if (UseTLAB) {
    // Make sure the class we're about to instantiate has been resolved
    // This is done before loading instanceKlass to be consistent with the order
    // how Constant Pool is updated (see ConstantPoolCache::klass_at_put).
    __ addi(Rtags, Rtags, Array<u1>::base_offset_in_bytes());
    __ lbzx(Rtags, Rindex, Rtags);

    __ cmpi(CCR0, Rtags, JVM_CONSTANT_Class);
    __ bne(CCR0, Lslow_case);

    // Get instanceKlass (load from Rcpool + sizeof(ConstantPool) + Rindex*BytesPerWord).
    __ sli(Roffset, Rindex, LogBytesPerWord);
    __ addi(Rscratch, Rcpool, sizeof(ConstantPool));
    __ isync(); // Order load of instance Klass wrt. tags.
    __ lx(RinstanceKlass, Roffset, Rscratch);

    // Make sure klass is fully initialized and get instance_size.
    __ lbz(Rscratch, in_bytes(InstanceKlass::init_state_offset()), RinstanceKlass);
    __ lwz(Rinstance_size, in_bytes(Klass::layout_helper_offset()), RinstanceKlass);

    __ cmpi(CCR1, Rscratch, InstanceKlass::fully_initialized);
    // Make sure klass does not have has_finalizer, or is abstract, or interface or java/lang/Class.
    __ andi_(R0, Rinstance_size, Klass::_lh_instance_slow_path_bit); // slow path bit equals 0?

    __ crnand(/*CR0 eq*/2, /*CR1 eq*/4+2, /*CR0 eq*/2); // slow path bit set or not fully initialized?
    __ beq(CCR0, Lslow_case);

    // --------------------------------------------------------------------------
    // Fast case:
    // Allocate the instance.
    // 1) Try to allocate in the TLAB.
    // 2) If fail, and the TLAB is not full enough to discard, allocate in the shared Eden.
    // 3) If the above fails (or is not applicable), go to a slow case (creates a new TLAB, etc.).

    Register RoldTopValue = RallocatedObject; // Object will be allocated here if it fits.
    Register RnewTopValue = R6_ARG4;
    Register RendValue    = R7_ARG5;

    // Check if we can allocate in the TLAB.
    __ l(RoldTopValue, in_bytes(JavaThread::tlab_top_offset()), R16_thread);
    __ l(RendValue,    in_bytes(JavaThread::tlab_end_offset()), R16_thread);

    __ add(RnewTopValue, Rinstance_size, RoldTopValue);

    // If there is enough space, we do not CAS and do not clear.
    __ cmpl(CCR0, RnewTopValue, RendValue);
    __ bgt(CCR0, allow_shared_alloc ? Lallocate_shared : Lslow_case);

    __ st(RnewTopValue, in_bytes(JavaThread::tlab_top_offset()), R16_thread);

    if (ZeroTLAB) {
      // The fields have already been cleared.
      __ b(Linitialize_header);
    } else {
      // Initialize both the header and fields.
      __ b(Linitialize_object);
    }

    // Fall through: TLAB was too small.
    if (allow_shared_alloc) {
      Register RtlabWasteLimitValue = R10_ARG8;
      Register RfreeValue = RnewTopValue;

      __ bind(Lallocate_shared);
      // Check if tlab should be discarded (refill_waste_limit >= free).
      __ l(RtlabWasteLimitValue, in_bytes(JavaThread::tlab_refill_waste_limit_offset()), R16_thread);
      __ subf(RfreeValue, RoldTopValue, RendValue);
      __ sri(RfreeValue, RfreeValue, LogHeapWordSize); // in dwords
      __ cmpl(CCR0, RtlabWasteLimitValue, RfreeValue);
      __ bge(CCR0, Lslow_case);

      // Increment waste limit to prevent getting stuck on this slow path.
      __ addi(RtlabWasteLimitValue, RtlabWasteLimitValue, (int)ThreadLocalAllocBuffer::refill_waste_limit_increment());
      __ st(RtlabWasteLimitValue, in_bytes(JavaThread::tlab_refill_waste_limit_offset()), R16_thread);
    }
    // else: No allocation in the shared eden. // fallthru: __ b(Lslow_case);
  }
  // else: Always go the slow path.

  // --------------------------------------------------------------------------
  // slow case
  __ bind(Lslow_case);
  call_VM(R17_tos, CAST_FROM_FN_PTR(address, InterpreterRuntime::_new), Rcpool, Rindex);

  if (UseTLAB) {
    __ b(Ldone);
    // --------------------------------------------------------------------------
    // Init1: Zero out newly allocated memory.

    if (!ZeroTLAB || allow_shared_alloc) {
      // Clear object fields.
      __ bind(Linitialize_object);

      // Initialize remaining object fields.
      Register Rbase = Rtags;
      // Skip oopDesk, clear is word aligned.
      __ addi(Rinstance_size, Rinstance_size, BytesPerWord - ((int)sizeof(oopDesc)+1));
      __ addi(Rbase, RallocatedObject, sizeof(oopDesc));
      __ sri(Rinstance_size, Rinstance_size, LogBytesPerWord);

      // Clear out object skipping header. Takes also care of the zero length case.
      __ clear_memory_word(Rbase, Rinstance_size);
      // fallthru: __ b(Linitialize_header);
    }

    // --------------------------------------------------------------------------
    // Init2: Initialize the header: mark, klass
    __ bind(Linitialize_header);

    // Init mark.
    if (UseBiasedLocking) {
      __ l(Rscratch, in_bytes(Klass::prototype_header_offset()), RinstanceKlass);
    } else {
      __ load_const_optimized(Rscratch, markOopDesc::prototype(), R0);
    }
    __ st(Rscratch, oopDesc::mark_offset_in_bytes(), RallocatedObject);

    // Init klass.
    __ store_klass_gap(RallocatedObject);
    __ store_klass(RallocatedObject, RinstanceKlass, Rscratch); // klass (last for cms)

    // Check and trigger dtrace event.
    {
      SkipIfEqualZero skip_if(_masm, Rscratch, &DTraceAllocProbes);
      __ push(atos);
      __ call_VM_leaf(CAST_FROM_FN_PTR(address, SharedRuntime::dtrace_object_alloc));
      __ pop(atos);
    }
  }

  // continue
  __ bind(Ldone);

  // Must prevent reordering of stores for object initialization with stores that publish the new object.
  __ membar(Assembler::StoreStore);
}

void TemplateTable::newarray() {
  transition(itos, atos);

  __ lbz(R4, 1, R14_bcp);
  __ extsw(R5, R17_tos);
  call_VM(R17_tos, CAST_FROM_FN_PTR(address, InterpreterRuntime::newarray), R4, R5 /* size */);

  // Must prevent reordering of stores for object initialization with stores that publish the new object.
  __ membar(Assembler::StoreStore);
}

void TemplateTable::anewarray() {
  transition(itos, atos);

  __ get_constant_pool(R4);
  __ get_2_byte_integer_at_bcp(1, R5, InterpreterMacroAssembler::Unsigned);
  __ extsw(R6, R17_tos); // size
  call_VM(R17_tos, CAST_FROM_FN_PTR(address, InterpreterRuntime::anewarray), R4 /* pool */, R5 /* index */, R6 /* size */);

  // Must prevent reordering of stores for object initialization with stores that publish the new object.
  __ membar(Assembler::StoreStore);
}

// Allocate a multi dimensional array
void TemplateTable::multianewarray() {
  transition(vtos, atos);

  Register Rptr = R31; // Needs to survive C call.

  // Put ndims * wordSize into frame temp slot
  __ lbz(Rptr, 3, R14_bcp);
  __ sli(Rptr, Rptr, Interpreter::logStackElementSize);
  // Esp points past last_dim, so set to R4 to first_dim address.
  __ add(R4, Rptr, R15_esp);
  call_VM(R17_tos, CAST_FROM_FN_PTR(address, InterpreterRuntime::multianewarray), R4 /* first_size_address */);
  // Pop all dimensions off the stack.
  __ add(R15_esp, Rptr, R15_esp);

  // Must prevent reordering of stores for object initialization with stores that publish the new object.
  __ membar(Assembler::StoreStore);
}

void TemplateTable::arraylength() {
  transition(atos, itos);

  Label LnoException;
  __ verify_oop(R17_tos);
  __ null_check_throw(R17_tos, arrayOopDesc::length_offset_in_bytes(), R11_scratch1);
  __ lwa(R17_tos, arrayOopDesc::length_offset_in_bytes(), R17_tos);
}

// ============================================================================
// Typechecks

void TemplateTable::checkcast() {
  transition(atos, atos);

  Label Ldone, Lis_null, Lquicked, Lresolved;
  Register Roffset         = R6_ARG4,
           RobjKlass       = R4_ARG2,
           RspecifiedKlass = R5_ARG3, // Generate_ClassCastException_verbose_handler will read value from this register.
           Rcpool          = R11_scratch1,
           Rtags           = R12_scratch2;

  // Null does not pass.
  __ cmpi(CCR0, R17_tos, 0);
  __ beq(CCR0, Lis_null);

  // Get constant pool tag to find out if the bytecode has already been "quickened".
  __ get_cpool_and_tags(Rcpool, Rtags);

  __ get_2_byte_integer_at_bcp(1, Roffset, InterpreterMacroAssembler::Unsigned);

  __ addi(Rtags, Rtags, Array<u1>::base_offset_in_bytes());
  __ lbzx(Rtags, Rtags, Roffset);

  __ cmpi(CCR0, Rtags, JVM_CONSTANT_Class);
  __ beq(CCR0, Lquicked);

  // Call into the VM to "quicken" instanceof.
  __ push_ptr();  // for GC
  call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::quicken_io_cc));
  __ get_vm_result_2(RspecifiedKlass);
  __ pop_ptr();   // Restore receiver.
  __ b(Lresolved);

  // Extract target class from constant pool.
  __ bind(Lquicked);
  __ sli(Roffset, Roffset, LogBytesPerWord);
  __ addi(Rcpool, Rcpool, sizeof(ConstantPool));
  __ isync(); // Order load of specified Klass wrt. tags.
  __ lx(RspecifiedKlass, Rcpool, Roffset);

  // Do the checkcast.
  __ bind(Lresolved);
  // Get value klass in RobjKlass.
  __ load_klass(RobjKlass, R17_tos);
  // Generate a fast subtype check. Branch to cast_ok if no failure. Return 0 if failure.
  __ gen_subtype_check(RobjKlass, RspecifiedKlass, /*3 temp regs*/ Roffset, Rcpool, Rtags, /*target if subtype*/ Ldone);

  // Not a subtype; so must throw exception
  // Target class oop is in register R6_ARG4 == RspecifiedKlass by convention.
  __ load_dispatch_table(R11_scratch1, (address*)Interpreter::_throw_ClassCastException_entry);
  __ mtctr(R11_scratch1);
  __ bctr();

  // Profile the null case.
  __ align(32, 12);
  __ bind(Lis_null);
  __ profile_null_seen(R11_scratch1, Rtags); // Rtags used as scratch.

  __ align(32, 12);
  __ bind(Ldone);
}

// Output:
//   - tos == 0: Obj was null or not an instance of class.
//   - tos == 1: Obj was an instance of class.
void TemplateTable::instanceof() {
  transition(atos, itos);

  Label Ldone, Lis_null, Lquicked, Lresolved;
  Register Roffset         = R5_ARG3,
           RobjKlass       = R4_ARG2,
           RspecifiedKlass = R6_ARG4, // Generate_ClassCastException_verbose_handler will expect the value in this register.
           Rcpool          = R11_scratch1,
           Rtags           = R12_scratch2;

  // Null does not pass.
  __ cmpi(CCR0, R17_tos, 0);
  __ beq(CCR0, Lis_null);

  // Get constant pool tag to find out if the bytecode has already been "quickened".
  __ get_cpool_and_tags(Rcpool, Rtags);

  __ get_2_byte_integer_at_bcp(1, Roffset, InterpreterMacroAssembler::Unsigned);

  __ addi(Rtags, Rtags, Array<u1>::base_offset_in_bytes());
  __ lbzx(Rtags, Rtags, Roffset);

  __ cmpi(CCR0, Rtags, JVM_CONSTANT_Class);
  __ beq(CCR0, Lquicked);

  // Call into the VM to "quicken" instanceof.
  __ push_ptr();  // for GC
  call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::quicken_io_cc));
  __ get_vm_result_2(RspecifiedKlass);
  __ pop_ptr();   // Restore receiver.
  __ b(Lresolved);

  // Extract target class from constant pool.
  __ bind(Lquicked);
  __ sli(Roffset, Roffset, LogBytesPerWord);
  __ addi(Rcpool, Rcpool, sizeof(ConstantPool));
  __ isync(); // Order load of specified Klass wrt. tags.
  __ lx(RspecifiedKlass, Rcpool, Roffset);

  // Do the checkcast.
  __ bind(Lresolved);
  // Get value klass in RobjKlass.
  __ load_klass(RobjKlass, R17_tos);
  // Generate a fast subtype check. Branch to cast_ok if no failure. Return 0 if failure.
  __ li(R17_tos, 1);
  __ gen_subtype_check(RobjKlass, RspecifiedKlass, /*3 temp regs*/ Roffset, Rcpool, Rtags, /*target if subtype*/ Ldone);
  __ li(R17_tos, 0);

  if (ProfileInterpreter) {
    __ b(Ldone);
  }

  // Profile the null case.
  __ align(32, 12);
  __ bind(Lis_null);
  __ profile_null_seen(Rcpool, Rtags); // Rcpool and Rtags used as scratch.

  __ align(32, 12);
  __ bind(Ldone);
}

// =============================================================================
// Breakpoints

void TemplateTable::_breakpoint() {
  transition(vtos, vtos);

  // Get the unpatched byte code.
  __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::get_original_bytecode_at), R19_method, R14_bcp);
  __ mr(R31, R3_RET);

  // Post the breakpoint event.
  __ call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::_breakpoint), R19_method, R14_bcp);

  // Complete the execution of original bytecode.
  __ dispatch_Lbyte_code(vtos, R31, Interpreter::normal_table(vtos));
}

// =============================================================================
// Exceptions

void TemplateTable::athrow() {
  transition(atos, vtos);

  // Exception oop is in tos
  __ verify_oop(R17_tos);

  __ null_check_throw(R17_tos, -1, R11_scratch1);

  // Throw exception interpreter entry expects exception oop to be in R3.
  __ mr(R3_RET, R17_tos);
  __ load_dispatch_table(R11_scratch1, (address*)Interpreter::throw_exception_entry());
  __ mtctr(R11_scratch1);
  __ bctr();
}

// =============================================================================
// Synchronization
// Searches the basic object lock list on the stack for a free slot
// and uses it to lock the obect in tos.
//
// Recursive locking is enabled by exiting the search if the same
// object is already found in the list. Thus, a new basic lock obj lock
// is allocated "higher up" in the stack and thus is found first
// at next monitor exit.
void TemplateTable::monitorenter() {
  transition(atos, vtos);

  __ verify_oop(R17_tos);

  Register Rcurrent_monitor  = R11_scratch1,
           Rcurrent_obj      = R12_scratch2,
           Robj_to_lock      = R17_tos,
           Rscratch1         = R3_ARG1,
           Rscratch2         = R4_ARG2,
           Rscratch3         = R5_ARG3,
           Rcurrent_obj_addr = R6_ARG4;

  // ------------------------------------------------------------------------------
  // Null pointer exception.
  __ null_check_throw(Robj_to_lock, -1, R11_scratch1);

  // Try to acquire a lock on the object.
  // Repeat until succeeded (i.e., until monitorenter returns true).

  // ------------------------------------------------------------------------------
  // Find a free slot in the monitor block.
  Label Lfound, Lexit, Lallocate_new;
  ConditionRegister found_free_slot = CCR0,
                    found_same_obj  = CCR1,
                    reached_limit   = CCR6;
  {
    Label Lloop, Lentry;
    Register Rlimit = Rcurrent_monitor;

    // Set up search loop - start with topmost monitor.
    __ add(Rcurrent_obj_addr, BasicObjectLock::obj_offset_in_bytes(), R26_monitor);

    __ l(Rlimit, 0, R1_SP);
    __ addi(Rlimit, Rlimit, - (frame::ijava_state_size + frame::interpreter_frame_monitor_size_in_bytes() - BasicObjectLock::obj_offset_in_bytes())); // Monitor base

    // Check if any slot is present => short cut to allocation if not.
    __ cmpl(reached_limit, Rcurrent_obj_addr, Rlimit);
    __ bgt(reached_limit, Lallocate_new);

    // Pre-load topmost slot.
    __ l(Rcurrent_obj, 0, Rcurrent_obj_addr);
    __ addi(Rcurrent_obj_addr, Rcurrent_obj_addr, frame::interpreter_frame_monitor_size() * wordSize);
    // The search loop.
    __ bind(Lloop);
    // Found free slot?
    __ cmpi(found_free_slot, Rcurrent_obj, 0);
    // Is this entry for same obj? If so, stop the search and take the found
    // free slot or allocate a new one to enable recursive locking.
    __ cmp(found_same_obj, Rcurrent_obj, Robj_to_lock);
    __ cmpl(reached_limit, Rcurrent_obj_addr, Rlimit);
    __ beq(found_free_slot, Lexit);
    __ beq(found_same_obj, Lallocate_new);
    __ bgt(reached_limit, Lallocate_new);
    // Check if last allocated BasicLockObj reached.
    __ l(Rcurrent_obj, 0, Rcurrent_obj_addr);
    __ addi(Rcurrent_obj_addr, Rcurrent_obj_addr, frame::interpreter_frame_monitor_size() * wordSize);
    // Next iteration if unchecked BasicObjectLocks exist on the stack.
    __ b(Lloop);
  }

  // ------------------------------------------------------------------------------
  // Check if we found a free slot.
  __ bind(Lexit);

  __ addi(Rcurrent_monitor, Rcurrent_obj_addr, -(frame::interpreter_frame_monitor_size() * wordSize) - BasicObjectLock::obj_offset_in_bytes());
  __ addi(Rcurrent_obj_addr, Rcurrent_obj_addr, - frame::interpreter_frame_monitor_size() * wordSize);
  __ b(Lfound);

  // We didn't find a free BasicObjLock => allocate one.
  __ align(32, 12);
  __ bind(Lallocate_new);
  __ add_monitor_to_stack(false, Rscratch1, Rscratch2);
  __ mr(Rcurrent_monitor, R26_monitor);
  __ addi(Rcurrent_obj_addr, R26_monitor, BasicObjectLock::obj_offset_in_bytes());

  // ------------------------------------------------------------------------------
  // We now have a slot to lock.
  __ bind(Lfound);

  // Increment bcp to point to the next bytecode, so exception handling for async. exceptions work correctly.
  // The object has already been poped from the stack, so the expression stack looks correct.
  __ addi(R14_bcp, R14_bcp, 1);

  __ st(Robj_to_lock, 0, Rcurrent_obj_addr);
  __ lock_object(Rcurrent_monitor, Robj_to_lock);

  // Check if there's enough space on the stack for the monitors after locking.
  Label Lskip_stack_check;
  // Optimization: If the monitors stack section is less then a st page size (4K) don't run
  // the stack check. There should be enough shadow pages to fit that in.
  __ l(Rscratch3, 0, R1_SP);
  __ sub(Rscratch3, Rscratch3, R26_monitor);
  __ cmpi(CCR0, Rscratch3, 4*K);
  __ blt(CCR0, Lskip_stack_check);

  DEBUG_ONLY(__ untested("stack overflow check during monitor enter");)
  __ li(Rscratch1, 0);
  __ generate_stack_overflow_check_with_compare_and_throw(Rscratch1, Rscratch2);

  __ align(32, 12);
  __ bind(Lskip_stack_check);

  // The bcp has already been incremented. Just need to dispatch to next instruction.
  __ dispatch_next(vtos);
}

void TemplateTable::monitorexit() {
  transition(atos, vtos);
  __ verify_oop(R17_tos);

  Register Rcurrent_monitor  = R11_scratch1,
           Rcurrent_obj      = R12_scratch2,
           Robj_to_lock      = R17_tos,
           Rcurrent_obj_addr = R3_ARG1,
           Rlimit            = R4_ARG2;
  Label Lfound, Lillegal_monitor_state;

  // Check corner case: unbalanced monitorEnter / Exit.
  __ l(Rlimit, 0, R1_SP);
  __ addi(Rlimit, Rlimit, - (frame::ijava_state_size + frame::interpreter_frame_monitor_size_in_bytes())); // Monitor base

  // Null pointer check.
  __ null_check_throw(Robj_to_lock, -1, R11_scratch1);

  __ cmpl(CCR0, R26_monitor, Rlimit);
  __ bgt(CCR0, Lillegal_monitor_state);

  // Find the corresponding slot in the monitors stack section.
  {
    Label Lloop;

    // Start with topmost monitor.
    __ addi(Rcurrent_obj_addr, R26_monitor, BasicObjectLock::obj_offset_in_bytes());
    __ addi(Rlimit, Rlimit, BasicObjectLock::obj_offset_in_bytes());
    __ l(Rcurrent_obj, 0, Rcurrent_obj_addr);
    __ addi(Rcurrent_obj_addr, Rcurrent_obj_addr, frame::interpreter_frame_monitor_size() * wordSize);

    __ bind(Lloop);
    // Is this entry for same obj?
    __ cmp(CCR0, Rcurrent_obj, Robj_to_lock);
    __ beq(CCR0, Lfound);

    // Check if last allocated BasicLockObj reached.

    __ l(Rcurrent_obj, 0, Rcurrent_obj_addr);
    __ cmpl(CCR0, Rcurrent_obj_addr, Rlimit);
    __ addi(Rcurrent_obj_addr, Rcurrent_obj_addr, frame::interpreter_frame_monitor_size() * wordSize);

    // Next iteration if unchecked BasicObjectLocks exist on the stack.
    __ ble(CCR0, Lloop);
  }

  // Fell through without finding the basic obj lock => throw up!
  __ bind(Lillegal_monitor_state);
  call_VM(noreg, CAST_FROM_FN_PTR(address, InterpreterRuntime::throw_illegal_monitor_state_exception));
  __ should_not_reach_here();

  __ align(32, 12);
  __ bind(Lfound);
  __ addi(Rcurrent_monitor, Rcurrent_obj_addr,
          -(frame::interpreter_frame_monitor_size() * wordSize) - BasicObjectLock::obj_offset_in_bytes());
  __ unlock_object(Rcurrent_monitor);
}

// ============================================================================
// Wide bytecodes

// Wide instructions. Simply redirects to the wide entry point for that instruction.
void TemplateTable::wide() {
  transition(vtos, vtos);

  const Register Rtable = R11_scratch1,
                 Rindex = R12_scratch2,
                 Rtmp   = R0;

  __ lbz(Rindex, 1, R14_bcp);

  __ load_dispatch_table(Rtable, Interpreter::_wentry_point);

  __ slwi(Rindex, Rindex, LogBytesPerWord);
  __ lx(Rtmp, Rtable, Rindex);
  __ mtctr(Rtmp);
  __ bctr();
  // Note: the bcp increment step is part of the individual wide bytecode implementations.
}
#endif // !CC_INTERP

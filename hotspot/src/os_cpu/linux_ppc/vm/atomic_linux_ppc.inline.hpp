/*
 * Copyright (c) 1997, 2013, Oracle and/or its affiliates. All rights reserved.
 * Copyright 2012, 2013 SAP AG. All rights reserved.
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

#ifndef OS_CPU_LINUX_PPC_VM_ATOMIC_LINUX_PPC_INLINE_HPP
#define OS_CPU_LINUX_PPC_VM_ATOMIC_LINUX_PPC_INLINE_HPP

#include "runtime/atomic.hpp"
#include "runtime/os.hpp"
#include "vm_version_ppc.hpp"

#define ptr_type OPENJDK_PPC32_ONLY(jint) PPC64_ONLY(jlong)

// Implementation of class atomic

inline void Atomic::store    (jbyte    store_value, jbyte*    dest) { *dest = store_value; }
inline void Atomic::store    (jshort   store_value, jshort*   dest) { *dest = store_value; }
inline void Atomic::store    (jint     store_value, jint*     dest) { *dest = store_value; }
inline void Atomic::store_ptr(intptr_t store_value, intptr_t* dest) { *dest = store_value; }
inline void Atomic::store_ptr(void*    store_value, void*     dest) { *(void**)dest = store_value; }
inline void Atomic::store    (jlong    store_value, jlong*    dest) {
#ifdef PPC64
  *dest = store_value;
#else
  Atomic::store(store_value, (volatile jlong*) dest);
#endif
}

inline void Atomic::store    (jbyte    store_value, volatile jbyte*    dest) { *dest = store_value; }
inline void Atomic::store    (jshort   store_value, volatile jshort*   dest) { *dest = store_value; }
inline void Atomic::store    (jint     store_value, volatile jint*     dest) { *dest = store_value; }
inline void Atomic::store_ptr(intptr_t store_value, volatile intptr_t* dest) { *dest = store_value; }
inline void Atomic::store_ptr(void*    store_value, volatile void*     dest) { *(void* volatile *)dest = store_value; }
inline void Atomic::store    (jlong    store_value, volatile jlong*    dest) {
#ifdef PPC64
  *dest = store_value;
#elif !defined(SPE_ATOMIC)
  double tmp;
  __asm__ __volatile__ (
    "lfd  %0, 0(%1)\n"
    "stfd %0, 0(%2)\n"
    : "=f"(tmp)
    : "b"(&store_value),
      "b"(dest)
    : "memory");
#else // SPE
  long tmp;
  __asm__ __volatile__ (
    "evldd  %0, 0(%1)\n"
    "evstdd %0, 0(%2)\n"
    : "=&r"(tmp)
    : "b"(&store_value),
      "b"(dest)
    : "memory");
#endif
}

inline jlong Atomic::load(volatile jlong* src) {
#ifdef PPC64
  return *src;
#elif !defined(SPE_ATOMIC)
  double tmp;
  jlong result;
  __asm__ __volatile__ (
    "lfd  %0, 0(%1)\n"
    "stfd %0, 0(%2)\n"
    : "=f"(tmp)
    : "b"(src),
      "b"(&result)
    : "memory");
  return result;
#else // SPE
  long tmp;
  jlong result;
  __asm__ __volatile__ (
    "evldd  %0, 0(%1)\n"
    "evstdd %0, 0(%2)\n"
    : "=&r"(tmp)
    : "b"(src),
      "b"(&result)
    : "memory");
  return result;
#endif
}

//
// machine barrier instructions:
//
// - sync            two-way memory barrier, aka fence
// - lwsync          orders  Store|Store,
//                            Load|Store,
//                            Load|Load,
//                   but not Store|Load
// - eieio           orders memory accesses for device memory (only)
// - isync           invalidates speculatively executed instructions
//                   From the POWER ISA 2.06 documentation:
//                    "[...] an isync instruction prevents the execution of
//                   instructions following the isync until instructions
//                   preceding the isync have completed, [...]"
//                   From IBM's AIX assembler reference:
//                    "The isync [...] instructions causes the processor to
//                   refetch any instructions that might have been fetched
//                   prior to the isync instruction. The instruction isync
//                   causes the processor to wait for all previous instructions
//                   to complete. Then any instructions already fetched are
//                   discarded and instruction processing continues in the
//                   environment established by the previous instructions."
//
// semantic barrier instructions:
// (as defined in orderAccess.hpp)
//
// - release         orders Store|Store,       (maps to lwsync)
//                           Load|Store
// - acquire         orders  Load|Store,       (maps to lwsync)
//                           Load|Load
// - fence           orders Store|Store,       (maps to sync)
//                           Load|Store,
//                           Load|Load,
//                          Store|Load
//

#define strasm_sync                       "\n  sync    \n"

#ifndef __NO_LWSYNC__
#define strasm_lwsync                     "\n  lwsync  \n"
#else // __NO_LWSYNC__
#define strasm_lwsync                     "\n  sync    \n"
#endif // __NO_LWSYNC__

#define strasm_isync                      "\n  isync   \n"
#define strasm_release                    strasm_lwsync
#define strasm_acquire                    strasm_lwsync
#define strasm_fence                      strasm_sync
#define strasm_nobarrier                  ""
#define strasm_nobarrier_clobber_memory   ""

#ifdef PPC64
#define ptr_larx "ldarx"
#define ptr_stcx "stdcx"
#else
#define ptr_larx "lwarx"
#define ptr_stcx "stwcx"
#endif

inline jint     Atomic::add    (jint     add_value, volatile jint*     dest) {

  unsigned int result;

  __asm__ __volatile__ (
    strasm_lwsync
    "1: lwarx   %0,  0, %2    \n"
    "   add     %0, %0, %1    \n"
    "   stwcx.  %0,  0, %2    \n"
    "   bne-    1b            \n"
    strasm_isync
    : /*%0*/"=&r" (result)
    : /*%1*/"r" (add_value), /*%2*/"r" (dest)
    : "cc", "memory" );

  return (jint) result;
}


inline intptr_t Atomic::add_ptr(intptr_t add_value, volatile intptr_t* dest) {

  long result;

  __asm__ __volatile__ (
    strasm_lwsync
    "1:" ptr_larx "  %0,  0, %2    \n"
    "   add          %0, %0, %1    \n"
    "  " ptr_stcx ". %0,  0, %2    \n"
    "   bne-         1b            \n"
    strasm_isync
    : /*%0*/"=&r" (result)
    : /*%1*/"r" (add_value), /*%2*/"r" (dest)
    : "cc", "memory" );

  return (intptr_t) result;
}

inline void*    Atomic::add_ptr(intptr_t add_value, volatile void*     dest) {
  return (void*)add_ptr(add_value, (volatile intptr_t*)dest);
}


inline void Atomic::inc    (volatile jint*     dest) {

  unsigned int temp;

  __asm__ __volatile__ (
    strasm_nobarrier
    "1: lwarx   %0,  0, %2    \n"
    "   addic   %0, %0,  1    \n"
    "   stwcx.  %0,  0, %2    \n"
    "   bne-    1b            \n"
    strasm_nobarrier
    : /*%0*/"=&r" (temp), "=m" (*dest)
    : /*%2*/"r" (dest), "m" (*dest)
    : "cc" strasm_nobarrier_clobber_memory);

}

inline void Atomic::inc_ptr(volatile intptr_t* dest) {

  long temp;

  __asm__ __volatile__ (
    strasm_nobarrier
    "1:" ptr_larx "  %0,  0, %2    \n"
    "   addic        %0, %0,  1    \n"
    "  " ptr_stcx ". %0,  0, %2    \n"
    "   bne-         1b            \n"
    strasm_nobarrier
    : /*%0*/"=&r" (temp), "=m" (*dest)
    : /*%2*/"r" (dest), "m" (*dest)
    : "cc" strasm_nobarrier_clobber_memory);

}

inline void Atomic::inc_ptr(volatile void*     dest) {
  inc_ptr((volatile intptr_t*)dest);
}


inline void Atomic::dec    (volatile jint*     dest) {

  unsigned int temp;

  __asm__ __volatile__ (
    strasm_nobarrier
    "1: lwarx   %0,  0, %2    \n"
    "   addic   %0, %0, -1    \n"
    "   stwcx.  %0,  0, %2    \n"
    "   bne-    1b            \n"
    strasm_nobarrier
    : /*%0*/"=&r" (temp), "=m" (*dest)
    : /*%2*/"r" (dest), "m" (*dest)
    : "cc" strasm_nobarrier_clobber_memory);

}

inline void Atomic::dec_ptr(volatile intptr_t* dest) {

  long temp;

  __asm__ __volatile__ (
    strasm_nobarrier
    "1:" ptr_larx "  %0,  0, %2    \n"
    "   addic        %0, %0, -1    \n"
    "  " ptr_stcx ". %0,  0, %2    \n"
    "   bne-         1b            \n"
    strasm_nobarrier
    : /*%0*/"=&r" (temp), "=m" (*dest)
    : /*%2*/"r" (dest), "m" (*dest)
    : "cc" strasm_nobarrier_clobber_memory);

}

inline void Atomic::dec_ptr(volatile void*     dest) {
  dec_ptr((volatile intptr_t*)dest);
}

inline jint Atomic::xchg(jint exchange_value, volatile jint* dest) {

  // Note that xchg_ptr doesn't necessarily do an acquire
  // (see synchronizer.cpp).

  unsigned int old_value;
  const uint64_t zero = 0;

  __asm__ __volatile__ (
    /* lwsync */
    strasm_lwsync
    /* atomic loop */
    "1:                                                 \n"
    "   lwarx   %[old_value], %[dest], %[zero]          \n"
    "   stwcx.  %[exchange_value], %[dest], %[zero]     \n"
    "   bne-    1b                                      \n"
    /* isync */
    strasm_sync
    /* exit */
    "2:                                                 \n"
    /* out */
    : [old_value]       "=&r"   (old_value),
                        "=m"    (*dest)
    /* in */
    : [dest]            "b"     (dest),
      [zero]            "r"     (zero),
      [exchange_value]  "r"     (exchange_value),
                        "m"     (*dest)
    /* clobber */
    : "cc",
      "memory"
    );

  return (jint) old_value;
}

inline intptr_t Atomic::xchg_ptr(intptr_t exchange_value, volatile intptr_t* dest) {

  // Note that xchg_ptr doesn't necessarily do an acquire
  // (see synchronizer.cpp).

  long old_value;
  const intptr_t zero = 0;

  __asm__ __volatile__ (
    /* lwsync */
    strasm_lwsync
    /* atomic loop */
    "1:                                                 \n"
    " " ptr_larx "  %[old_value], %[dest], %[zero]      \n"
    " " ptr_stcx ". %[exchange_value], %[dest], %[zero] \n"
    "   bne-        1b                                  \n"
    /* isync */
    strasm_sync
    /* exit */
    "2:                                                 \n"
    /* out */
    : [old_value]       "=&r"   (old_value),
                        "=m"    (*dest)
    /* in */
    : [dest]            "b"     (dest),
      [zero]            "r"     (zero),
      [exchange_value]  "r"     (exchange_value),
                        "m"     (*dest)
    /* clobber */
    : "cc",
      "memory"
    );

  return (intptr_t) old_value;
}

inline void* Atomic::xchg_ptr(void* exchange_value, volatile void* dest) {
  return (void*)xchg_ptr((intptr_t)exchange_value, (volatile intptr_t*)dest);
}

inline jint Atomic::cmpxchg(jint exchange_value, volatile jint* dest, jint compare_value) {

  // Note that cmpxchg guarantees a two-way memory barrier across
  // the cmpxchg, so it's really a a 'fence_cmpxchg_acquire'
  // (see atomic.hpp).

  unsigned int old_value;
  const uint64_t zero = 0;

  __asm__ __volatile__ (
    /* fence */
    strasm_sync
    /* simple guard */
    "   lwz     %[old_value], 0(%[dest])                \n"
    "   cmpw    %[compare_value], %[old_value]          \n"
    "   bne-    2f                                      \n"
    /* atomic loop */
    "1:                                                 \n"
    "   lwarx   %[old_value], %[dest], %[zero]          \n"
    "   cmpw    %[compare_value], %[old_value]          \n"
    "   bne-    2f                                      \n"
    "   stwcx.  %[exchange_value], %[dest], %[zero]     \n"
    "   bne-    1b                                      \n"
    /* acquire */
    strasm_sync
    /* exit */
    "2:                                                 \n"
    /* out */
    : [old_value]       "=&r"   (old_value),
                        "=m"    (*dest)
    /* in */
    : [dest]            "b"     (dest),
      [zero]            "r"     (zero),
      [compare_value]   "r"     (compare_value),
      [exchange_value]  "r"     (exchange_value),
                        "m"     (*dest)
    /* clobber */
    : "cc",
      "memory"
    );

  return (jint) old_value;
}

inline jlong Atomic::cmpxchg(jlong exchange_value, volatile jlong* dest, jlong compare_value) {

  // Note that cmpxchg guarantees a two-way memory barrier across
  // the cmpxchg, so it's really a a 'fence_cmpxchg_acquire'
  // (see atomic.hpp).

#ifdef PPC64
  long old_value;
  const uint64_t zero = 0;

  __asm__ __volatile__ (
    /* fence */
    strasm_sync
    /* simple guard */
    "   ld      %[old_value], 0(%[dest])                \n"
    "   cmpd    %[compare_value], %[old_value]          \n"
    "   bne-    2f                                      \n"
    /* atomic loop */
    "1:                                                 \n"
    "   ldarx   %[old_value], %[dest], %[zero]          \n"
    "   cmpd    %[compare_value], %[old_value]          \n"
    "   bne-    2f                                      \n"
    "   stdcx.  %[exchange_value], %[dest], %[zero]     \n"
    "   bne-    1b                                      \n"
    /* acquire */
    strasm_sync
    /* exit */
    "2:                                                 \n"
    /* out */
    : [old_value]       "=&r"   (old_value),
                        "=m"    (*dest)
    /* in */
    : [dest]            "b"     (dest),
      [zero]            "r"     (zero),
      [compare_value]   "r"     (compare_value),
      [exchange_value]  "r"     (exchange_value),
                        "m"     (*dest)
    /* clobber */
    : "cc",
      "memory"
    );

  return (jlong) old_value;
#else
  assert(!VM_Version::supports_cx8(), "PPC32 doesn't support 8byte compare-exchange");
  ShouldNotCallThis();
  return 0;
#endif // PPC64
}

inline intptr_t Atomic::cmpxchg_ptr(intptr_t exchange_value, volatile intptr_t* dest, intptr_t compare_value) {
  return (intptr_t)cmpxchg((ptr_type)exchange_value, (volatile ptr_type*)dest, (ptr_type)compare_value);
}

inline void* Atomic::cmpxchg_ptr(void* exchange_value, volatile void* dest, void* compare_value) {
  return (void*)cmpxchg((intptr_t)exchange_value, (volatile intptr_t*)dest, (intptr_t)compare_value);
}

#undef strasm_sync
#undef strasm_lwsync
#undef strasm_isync
#undef strasm_release
#undef strasm_acquire
#undef strasm_fence
#undef strasm_nobarrier
#undef strasm_nobarrier_clobber_memory
#undef ptr_larx
#undef ptr_stcx
#undef ptr_type

#endif // OS_CPU_LINUX_PPC_VM_ATOMIC_LINUX_PPC_INLINE_HPP

/*
 * Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
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
 */

package sun.security.pkcs11;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import sun.nio.ch.DirectBuffer;

import java.util.Hashtable;
import java.util.Arrays;
import java.security.*;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.MGF1ParameterSpec;
import java.security.spec.PSSParameterSpec;
import java.security.interfaces.*;
import sun.security.pkcs11.wrapper.*;
import static sun.security.pkcs11.wrapper.PKCS11Constants.*;


/**
 * RSASSA-PSS Signature implementation class. This class currently supports the
 * following algorithms:
 *
 * . RSA-PSS:
 *   . RSASSA-PSS
 *   . SHA1withRSASSA-PSS
 *   . SHA224withRSASSA-PSS
 *   . SHA256withRSASSA-PSS
 *   . SHA384withRSASSA-PSS
 *   . SHA512withRSASSA-PSS
 *
 * Note that the underlying PKCS#11 token may support complete signature
 * algorithm (e.g. CKM_<md>_RSA_PKCS_PSS), or it may just
 * implement the signature algorithm without hashing (i.e. CKM_RSA_PKCS_PSS).
 * This class uses what is available and adds whatever extra processing
 * is needed.
 *
 * @since   13
 */
final class P11PSSSignature extends SignatureSpi {

    private static final int TRAILER_FIELD_BC = 1;

    private final static boolean DEBUG = false;

    // mappings of digest algorithms and their output length in bytes
    private static final Hashtable<String, Integer> DIGEST_LENGTHS =
        new Hashtable<String, Integer>();

    static {
        DIGEST_LENGTHS.put("SHA-1", 20);
        DIGEST_LENGTHS.put("SHA", 20);
        DIGEST_LENGTHS.put("SHA1", 20);
        DIGEST_LENGTHS.put("SHA-224", 28);
        DIGEST_LENGTHS.put("SHA224", 28);
        DIGEST_LENGTHS.put("SHA-256", 32);
        DIGEST_LENGTHS.put("SHA256", 32);
        DIGEST_LENGTHS.put("SHA-384", 48);
        DIGEST_LENGTHS.put("SHA384", 48);
        DIGEST_LENGTHS.put("SHA-512", 64);
        DIGEST_LENGTHS.put("SHA512", 64);
        DIGEST_LENGTHS.put("SHA-512/224", 28);
        DIGEST_LENGTHS.put("SHA512/224", 28);
        DIGEST_LENGTHS.put("SHA-512/256", 32);
        DIGEST_LENGTHS.put("SHA512/256", 32);
    }

    // utility method for comparing digest algorithms
    // NOTE that first argument is assumed to be standard digest name
    private static boolean isDigestEqual(String stdAlg, String givenAlg) {
        if (stdAlg == null || givenAlg == null) return false;

        if (givenAlg.indexOf("-") != -1) {
            return stdAlg.equalsIgnoreCase(givenAlg);
        } else {
            if (stdAlg.equals("SHA-1")) {
                return (givenAlg.equalsIgnoreCase("SHA")
                        || givenAlg.equalsIgnoreCase("SHA1"));
            } else {
                StringBuilder sb = new StringBuilder(givenAlg);
                // case-insensitive check
                if (givenAlg.regionMatches(true, 0, "SHA", 0, 3)) {
                    givenAlg = sb.insert(3, "-").toString();
                    return stdAlg.equalsIgnoreCase(givenAlg);
                } else {
                    throw new ProviderException("Unsupported digest algorithm "
                            + givenAlg);
                }
            }
        }
    }

    // token instance
    private final Token token;

    // algorithm name
    private final String algorithm;

    // name of the key algorithm, currently just RSA
    private static final String KEY_ALGO = "RSA";

    // mechanism id
    private final CK_MECHANISM mechanism;

    // type, one of T_* below
    private final int type;

    // key instance used, if init*() was called
    private P11Key p11Key = null;

    // PSS parameters and the flag controlling its access
    private PSSParameterSpec sigParams = null;
    private boolean isActive = false;

    // message digest alg, if implied by the algorithm name
    private final String mdAlg;

    // message digest, if we do the digesting ourselves
    private MessageDigest md = null;

    // associated session, if any
    private Session session;

    // mode, one of M_* below
    private int mode;

    // flag indicating whether an operation is initialized
    private boolean initialized = false;

    // buffer, for update(byte)
    private final byte[] buffer = new byte[1];

    // total number of bytes processed in current operation
    private int bytesProcessed = 0;

    // constant for signing mode
    private final static int M_SIGN   = 1;
    // constant for verification mode
    private final static int M_VERIFY = 2;

    // constant for type digesting, we do the hashing ourselves
    private final static int T_DIGEST = 1;
    // constant for type update, token does everything
    private final static int T_UPDATE = 2;

    P11PSSSignature(Token token, String algorithm, long mechId)
            throws NoSuchAlgorithmException, PKCS11Exception {
        super();
        this.token = token;
        this.algorithm = algorithm;
        this.mechanism = new CK_MECHANISM(mechId);
        int idx = algorithm.indexOf("with");
        this.mdAlg = (idx == -1? null : algorithm.substring(0, idx));
        switch ((int)mechId) {
        case (int)CKM_SHA1_RSA_PKCS_PSS:
        case (int)CKM_SHA224_RSA_PKCS_PSS:
        case (int)CKM_SHA256_RSA_PKCS_PSS:
        case (int)CKM_SHA384_RSA_PKCS_PSS:
        case (int)CKM_SHA512_RSA_PKCS_PSS:
            type = T_UPDATE;
            break;
        case (int)CKM_RSA_PKCS_PSS:
            type = T_DIGEST;
            break;
        default:
            throw new ProviderException("Unsupported mechanism: " + mechId);
        }
        this.md = null;
    }

    private void ensureInitialized() throws SignatureException {
        token.ensureValid();
        if (this.p11Key == null) {
            throw new SignatureException("Missing key");
        }
        if (this.sigParams == null) {
            if (this.mdAlg == null) {
                // PSS Parameters are required for signature verification
                throw new SignatureException
                    ("Parameters required for RSASSA-PSS signature");
            } else {
                int saltLen = DIGEST_LENGTHS.get(this.mdAlg).intValue();
                // generate default params for both sign and verify?
                this.sigParams = new PSSParameterSpec(this.mdAlg,
                        "MGF1", new MGF1ParameterSpec(this.mdAlg),
                        saltLen, TRAILER_FIELD_BC);
                this.mechanism.setParameter(new CK_RSA_PKCS_PSS_PARAMS(
                        this.mdAlg, "MGF1", this.mdAlg,
                        DIGEST_LENGTHS.get(this.mdAlg).intValue()));
            }
        }

        if (initialized == false) {
            initialize();
        }
    }

    // reset the states to the pre-initialized values
    private void reset(boolean doCancel) {
        if (!initialized) {
            return;
        }
        initialized = false;
        try {
            if (session == null) {
                return;
            }
            if (doCancel && token.explicitCancel) {
                cancelOperation();
            }
        } finally {
            p11Key.releaseKeyID();
            mechanism.freeHandle();
            session = token.releaseSession(session);
            isActive = false;
        }
    }

    private void cancelOperation() {
        token.ensureValid();
        if (DEBUG) System.out.print("Cancelling operation");

        if (session.hasObjects() == false) {
            if (DEBUG) System.out.println(" by killing session");
            session = token.killSession(session);
            return;
        }
        // "cancel" operation by finishing it
        if (mode == M_SIGN) {
            try {
                if (type == T_UPDATE) {
                    if (DEBUG) System.out.println(" by C_SignFinal");
                    token.p11.C_SignFinal(session.id(), 0);
                } else {
                    byte[] digest =
                        (md == null? new byte[0] : md.digest());
                    if (DEBUG) System.out.println(" by C_Sign");
                    token.p11.C_Sign(session.id(), digest);
                }
            } catch (PKCS11Exception e) {
                throw new ProviderException("cancel failed", e);
            }
        } else { // M_VERIFY
            try {
                byte[] signature =
                    new byte[(p11Key.length() + 7) >> 3];
                if (type == T_UPDATE) {
                    if (DEBUG) System.out.println(" by C_VerifyFinal");
                    token.p11.C_VerifyFinal(session.id(), signature);
                } else {
                    byte[] digest =
                        (md == null? new byte[0] : md.digest());
                    if (DEBUG) System.out.println(" by C_Verify");
                    token.p11.C_Verify(session.id(), digest, signature);
                }
            } catch (PKCS11Exception e) {
                // will fail since the signature is incorrect
                // XXX check error code
            }
        }
    }

    // assumes current state is initialized == false
    private void initialize() {
        if (DEBUG) System.out.println("Initializing");

        if (p11Key == null) {
            throw new ProviderException(
                    "No Key found, call initSign/initVerify first");
        }

        long keyID = p11Key.getKeyID();
        try {
            if (session == null) {
                session = token.getOpSession();
            }
            if (mode == M_SIGN) {
                token.p11.C_SignInit(session.id(), mechanism, keyID);
            } else {
                token.p11.C_VerifyInit(session.id(), mechanism, keyID);
            }
        } catch (PKCS11Exception e) {
            p11Key.releaseKeyID();
            session = token.releaseSession(session);
            throw new ProviderException("Initialization failed", e);
        }
        if (bytesProcessed != 0) {
            bytesProcessed = 0;
            if (md != null) {
                md.reset();
            }
        }
        initialized = true;
        isActive = false;
        if (DEBUG) System.out.println("Initialized");
    }

    private void checkKeySize(Key key) throws InvalidKeyException {
        if (DEBUG) System.out.print("Checking Key");

        if (!key.getAlgorithm().equals(KEY_ALGO)) {
            throw new InvalidKeyException("Only " + KEY_ALGO +
                " keys are supported");
        }

        CK_MECHANISM_INFO mechInfo = null;
        try {
            mechInfo = token.getMechanismInfo(mechanism.mechanism);
        } catch (PKCS11Exception e) {
            // should not happen, ignore for now
            if (DEBUG) {
                System.out.println("Unexpected exception");
                e.printStackTrace();
            }
        }

        int keySize = 0; // in bytes
        if (mechInfo != null) {
            if (key instanceof P11Key) {
                keySize = (((P11Key) key).length() + 7) >> 3;
            } else if (key instanceof RSAKey) {
                keySize = ((RSAKey) key).getModulus().bitLength() >> 3;
            } else {
                throw new InvalidKeyException("Unrecognized key type " + key);
            }
            // check against available native info which are in bits
            if ((mechInfo.iMinKeySize != 0) &&
                    (keySize < (mechInfo.iMinKeySize >> 3))) {
                throw new InvalidKeyException(KEY_ALGO +
                    " key must be at least " + mechInfo.iMinKeySize + " bits");
            }
            if ((mechInfo.iMaxKeySize != Integer.MAX_VALUE) &&
                    (keySize > (mechInfo.iMaxKeySize >> 3))) {
                throw new InvalidKeyException(KEY_ALGO +
                    " key must be at most " + mechInfo.iMaxKeySize + " bits");
            }
        }
        if (this.sigParams != null) {
            String digestAlg = this.sigParams.getDigestAlgorithm();
            int sLen = this.sigParams.getSaltLength();
            int hLen = DIGEST_LENGTHS.get(digestAlg).intValue();
            int minKeyLen = Math.addExact(Math.addExact(sLen, hLen), 2);

            if (keySize < minKeyLen) {
                throw new InvalidKeyException
                    ("Key is too short for current params, need min " + minKeyLen);
            }
        }
    }

    private void setSigParams(AlgorithmParameterSpec p)
            throws InvalidAlgorithmParameterException {
        if (p == null) {
            throw new InvalidAlgorithmParameterException("PSS Parameter required");
        }
        if (!(p instanceof PSSParameterSpec)) {
            throw new InvalidAlgorithmParameterException
                ("Only PSSParameterSpec is supported");
        }
        // no need to validate again if same as current signature parameters
        PSSParameterSpec params = (PSSParameterSpec) p;
        if (params == this.sigParams) return;

        String digestAlgorithm = params.getDigestAlgorithm();
        if (this.mdAlg != null && !isDigestEqual(digestAlgorithm, this.mdAlg)) {
            throw new InvalidAlgorithmParameterException
                    ("Digest algorithm in Signature parameters must be " +
                     this.mdAlg);
        }
        Integer digestLen = DIGEST_LENGTHS.get(digestAlgorithm);
        if (digestLen == null) {
            throw new InvalidAlgorithmParameterException
                ("Unsupported digest algorithm in Signature parameters: " +
                 digestAlgorithm);
        }
        if (!(params.getMGFAlgorithm().equalsIgnoreCase("MGF1"))) {
            throw new InvalidAlgorithmParameterException("Only supports MGF1");
        }

        // defaults to the digest algorithm unless overridden
        String mgfDigestAlgo = digestAlgorithm;
        AlgorithmParameterSpec mgfParams = params.getMGFParameters();
        if (mgfParams != null) {
            if (!(mgfParams instanceof MGF1ParameterSpec)) {
               throw new InvalidAlgorithmParameterException
                        ("Only MGF1ParameterSpec is supported");
            }
            mgfDigestAlgo = ((MGF1ParameterSpec)mgfParams).getDigestAlgorithm();
        }

        if (params.getTrailerField() != TRAILER_FIELD_BC) {
            throw new InvalidAlgorithmParameterException
                ("Only supports TrailerFieldBC(1)");
        }
        int saltLen = params.getSaltLength();
        if (this.p11Key != null) {
            int maxSaltLen = ((this.p11Key.length() + 7) >> 3) - digestLen.intValue() - 2;

            if (DEBUG) {
                System.out.println("Max saltLen = " + maxSaltLen);
                System.out.println("Curr saltLen = " + saltLen);
            }
            if (maxSaltLen < 0 || saltLen > maxSaltLen) {
                throw new InvalidAlgorithmParameterException("Invalid with current key size");
            }
        } else {
            if (DEBUG) System.out.println("No key available for validating saltLen");
        }

        // validated, now try to store the parameter internally
        try {
            this.mechanism.setParameter(
                    new CK_RSA_PKCS_PSS_PARAMS(digestAlgorithm, "MGF1",
                        mgfDigestAlgo, saltLen));
            this.sigParams = params;
        } catch (IllegalArgumentException iae) {
            throw new InvalidAlgorithmParameterException(iae);
        }
    }

    // see JCA spec
    @Override
    protected void engineInitVerify(PublicKey publicKey)
            throws InvalidKeyException {

        if (publicKey == null) {
            throw new InvalidKeyException("Key must not be null");
        }

        // Need to check key length whenever a new key is set
        if (publicKey != p11Key) {
            checkKeySize(publicKey);
        }

        reset(true);
        mode = M_VERIFY;
        p11Key = P11KeyFactory.convertKey(token, publicKey, KEY_ALGO);

        // For PSS, defer PKCS11 initialization calls to update/doFinal as it
        // needs both key and params
    }

    // see JCA spec
    @Override
    protected void engineInitSign(PrivateKey privateKey)
            throws InvalidKeyException {

        if (privateKey == null) {
            throw new InvalidKeyException("Key must not be null");
        }

        // Need to check RSA key length whenever a new key is set
        if (privateKey != p11Key) {
            checkKeySize(privateKey);
        }

        reset(true);
        mode = M_SIGN;
        p11Key = P11KeyFactory.convertKey(token, privateKey, KEY_ALGO);

        // For PSS, defer PKCS11 initialization calls to update/doFinal as it
        // needs both key and params
    }

    // see JCA spec
    @Override
    protected void engineUpdate(byte b) throws SignatureException {
        ensureInitialized();
        isActive = true;
        buffer[0] = b;
        engineUpdate(buffer, 0, 1);
    }

    // see JCA spec
    @Override
    protected void engineUpdate(byte[] b, int ofs, int len)
            throws SignatureException {
        ensureInitialized();
        if (len == 0) {
            return;
        }
        // check for overflow
        if (len + bytesProcessed < 0) {
            throw new ProviderException("Processed bytes limits exceeded.");
        }
        isActive = true;
        switch (type) {
        case T_UPDATE:
            try {
                if (mode == M_SIGN) {
                    System.out.println(this + ": Calling C_SignUpdate");
                    token.p11.C_SignUpdate(session.id(), 0, b, ofs, len);
                } else {
                    System.out.println(this + ": Calling C_VerfifyUpdate");
                    token.p11.C_VerifyUpdate(session.id(), 0, b, ofs, len);
                }
                bytesProcessed += len;
            } catch (PKCS11Exception e) {
                reset(false);
                throw new ProviderException(e);
            }
            break;
        case T_DIGEST:
            // should not happen as this should be covered by earlier checks
            if (md == null) {
                throw new ProviderException("PSS Parameters required");
            }
            md.update(b, ofs, len);
            bytesProcessed += len;
            break;
        default:
            throw new ProviderException("Internal error");
        }
    }

    // see JCA spec
    @Override
    protected void engineUpdate(ByteBuffer byteBuffer) {
        try {
            ensureInitialized();
        } catch (SignatureException se) {
            throw new ProviderException(se);
        }
        int len = byteBuffer.remaining();
        if (len <= 0) {
            return;
        }
        isActive = true;
        switch (type) {
        case T_UPDATE:
            if (byteBuffer instanceof DirectBuffer == false) {
                // cannot do better than default impl
                super.engineUpdate(byteBuffer);
                return;
            }
            long addr = ((DirectBuffer)byteBuffer).address();
            int ofs = byteBuffer.position();
            try {
                if (mode == M_SIGN) {
                    System.out.println(this + ": Calling C_SignUpdate");
                    token.p11.C_SignUpdate
                        (session.id(), addr + ofs, null, 0, len);
                } else {
                    System.out.println(this + ": Calling C_VerifyUpdate");
                    token.p11.C_VerifyUpdate
                        (session.id(), addr + ofs, null, 0, len);
                }
                bytesProcessed += len;
                byteBuffer.position(ofs + len);
            } catch (PKCS11Exception e) {
                reset(false);
                throw new ProviderException("Update failed", e);
            }
            break;
        case T_DIGEST:
            // should not happen as this should be covered by earlier checks
            if (md == null) {
                throw new ProviderException("PSS Parameters required");
            }
            md.update(byteBuffer);
            bytesProcessed += len;
            break;
        default:
            reset(false);
            throw new ProviderException("Internal error");
        }
    }

    // see JCA spec
    @Override
    protected byte[] engineSign() throws SignatureException {
        ensureInitialized();
        boolean doCancel = true;
        if (DEBUG) System.out.print("Generating signature");
        try {
            byte[] signature;
            if (type == T_UPDATE) {
                if (DEBUG) System.out.println(" by C_SignFinal");
                signature = token.p11.C_SignFinal(session.id(), 0);
            } else {
                if (md == null) {
                    throw new ProviderException("PSS Parameters required");
                }
                byte[] digest = md.digest();
                if (DEBUG) System.out.println(" by C_Sign");
                signature = token.p11.C_Sign(session.id(), digest);
            }
            doCancel = false;
            return signature;
        } catch (PKCS11Exception pe) {
            doCancel = false;
            throw new ProviderException(pe);
        } catch (ProviderException e) {
            throw e;
        } finally {
            reset(doCancel);
        }
    }

    // see JCA spec
    @Override
    protected boolean engineVerify(byte[] signature) throws SignatureException {
        ensureInitialized();
        boolean doCancel = true;
        if (DEBUG) System.out.print("Verifying signature");
        try {
            if (type == T_UPDATE) {
                if (DEBUG) System.out.println(" by C_VerifyFinal");
                token.p11.C_VerifyFinal(session.id(), signature);
            } else {
                if (md == null) {
                    throw new ProviderException("PSS Parameters required");
                }
                byte[] digest = md.digest();
                if (DEBUG) System.out.println(" by C_Verify");
                token.p11.C_Verify(session.id(), digest, signature);
            }
            doCancel = false;
            return true;
        } catch (PKCS11Exception pe) {
            doCancel = false;
            long errorCode = pe.getErrorCode();
            if (errorCode == CKR_SIGNATURE_INVALID) {
                return false;
            }
            if (errorCode == CKR_SIGNATURE_LEN_RANGE) {
                // return false rather than throwing an exception
                return false;
            }
            // ECF bug?
            if (errorCode == CKR_DATA_LEN_RANGE) {
                return false;
            }
            throw new ProviderException(pe);
        }  catch (ProviderException e) {
            throw e;
        } finally {
            reset(doCancel);
        }
    }

    // see JCA spec
    @SuppressWarnings("deprecation")
    @Override
    protected void engineSetParameter(String param, Object value)
            throws InvalidParameterException {
        throw new UnsupportedOperationException("setParameter() not supported");
    }

    // see JCA spec
    @Override
    protected void engineSetParameter(AlgorithmParameterSpec params)
            throws InvalidAlgorithmParameterException {
        // disallow changing parameters when update has been called
        if (isActive) {
            throw new ProviderException
                ("Cannot set parameters during operations");
        }
        setSigParams(params);
        if (type == T_DIGEST) {
            try {
                this.md = MessageDigest.getInstance(sigParams.getDigestAlgorithm());
            } catch (NoSuchAlgorithmException nsae) {
                throw new InvalidAlgorithmParameterException(nsae);
            }
        }
    }

    // see JCA spec
    @SuppressWarnings("deprecation")
    @Override
    protected Object engineGetParameter(String param)
            throws InvalidParameterException {
        throw new UnsupportedOperationException("getParameter() not supported");
    }

    // see JCA spec
    @Override
    protected AlgorithmParameters engineGetParameters() {
        if (this.sigParams != null) {
            try {
                AlgorithmParameters ap = AlgorithmParameters.getInstance("RSASSA-PSS");
                ap.init(this.sigParams);
                return ap;
            } catch (GeneralSecurityException e) {
                throw new RuntimeException(e);
            }
        }
        return null;
    }
}

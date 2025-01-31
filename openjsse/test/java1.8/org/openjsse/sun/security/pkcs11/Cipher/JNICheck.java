/*
 * Copyright (c) 2014, 2018, Oracle and/or its affiliates. All rights reserved.
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
 */

/*
 * @test
 * @bug 8063700
 * @library /lib /
 * @run main/othervm -Xcheck:jni JNICheck
 */

import javax.crypto.Cipher;
import javax.crypto.SealedObject;
import javax.crypto.SecretKey;
import javax.crypto.KeyGenerator;
import java.security.NoSuchProviderException;

public class JNICheck {

    /* This test is similar to the JCK test that found 8063700. */
    static class SealedObjectTest {
        Cipher c;

        SealedObjectTest() throws Exception {
            try {
                c = Cipher.getInstance("AES", "SunPKCS11-Solaris");
            } catch (NoSuchProviderException nspe) {
                System.out.println("No SunPKCS11-Solaris provider.  Test skipped");
                return;
            }

            String s = "Test string";
            SealedObject so;
            SecretKey key = KeyGenerator.getInstance("AES").generateKey();

            c.init(Cipher.ENCRYPT_MODE, key);
            so = new SealedObject(s, c);

            so.getObject(key, "SunPKCS11-Solaris");
        }
    }

    public static void main(String args[]) throws Exception {
        new SealedObjectTest();
    }
}

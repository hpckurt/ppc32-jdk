/*
 * Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.
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
 * @bug 4898428 7022855
 * @summary verify getInstance() works using Provider.getService()
 *          Export "PKIX" as the standard algorithm name of KeyManagerFactory
 * @author Andreas Sterbenz
 */

import java.security.*;

import javax.net.ssl.*;

public class GetInstance {

    private static void same(Provider p1, Provider p2) throws Exception {
        if (p1 != p2) {
            throw new Exception("not same object");
        }
    }

    public static void main(String[] args) throws Exception {
        long start = System.currentTimeMillis();

        Provider p = Security.getProvider("Legacy8uJSSE");

        SSLContext context;
        context = SSLContext.getInstance("SSL");
        same(p, context.getProvider());
        context = SSLContext.getInstance("SSL", "Legacy8uJSSE");
        same(p, context.getProvider());
        context = SSLContext.getInstance("SSL", p);
        same(p, context.getProvider());

        KeyManagerFactory kmf;
        kmf = KeyManagerFactory.getInstance("SunX509");
        same(p, kmf.getProvider());
        kmf = KeyManagerFactory.getInstance("SunX509", "Legacy8uJSSE");
        same(p, kmf.getProvider());
        kmf = KeyManagerFactory.getInstance("SunX509", p);
        same(p, kmf.getProvider());

        kmf = KeyManagerFactory.getInstance("NewSunX509");
        same(p, kmf.getProvider());
        kmf = KeyManagerFactory.getInstance("NewSunX509", "Legacy8uJSSE");
        same(p, kmf.getProvider());
        kmf = KeyManagerFactory.getInstance("NewSunX509", p);
        same(p, kmf.getProvider());

        kmf = KeyManagerFactory.getInstance("PKIX");
        same(p, kmf.getProvider());
        kmf = KeyManagerFactory.getInstance("PKIX", "Legacy8uJSSE");
        same(p, kmf.getProvider());
        kmf = KeyManagerFactory.getInstance("PKIX", p);
        same(p, kmf.getProvider());

        TrustManagerFactory tmf;
        tmf = TrustManagerFactory.getInstance("SunX509");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("SunX509", "Legacy8uJSSE");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("SunX509", p);
        same(p, tmf.getProvider());

        tmf = TrustManagerFactory.getInstance("PKIX");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("PKIX", "Legacy8uJSSE");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("PKIX", p);
        same(p, tmf.getProvider());

        tmf = TrustManagerFactory.getInstance("SunPKIX");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("SunPKIX", "Legacy8uJSSE");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("SunPKIX", p);
        same(p, tmf.getProvider());

        tmf = TrustManagerFactory.getInstance("X509");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("X509", "Legacy8uJSSE");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("X509", p);
        same(p, tmf.getProvider());

        tmf = TrustManagerFactory.getInstance("X.509");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("X.509", "Legacy8uJSSE");
        same(p, tmf.getProvider());
        tmf = TrustManagerFactory.getInstance("X.509", p);
        same(p, tmf.getProvider());

        testComSun();

        long stop = System.currentTimeMillis();
        System.out.println("Done (" + (stop - start) + " ms).");
    }

    private static void testComSun() throws Exception {
        Provider p = Security.getProvider("Legacy8uJSSE");

        com.sun.net.ssl.SSLContext context;
        context = com.sun.net.ssl.SSLContext.getInstance("SSL");
        same(p, context.getProvider());
        context = com.sun.net.ssl.SSLContext.getInstance("SSL", "Legacy8uJSSE");
        same(p, context.getProvider());
        context = com.sun.net.ssl.SSLContext.getInstance("SSL", p);
        same(p, context.getProvider());

        com.sun.net.ssl.KeyManagerFactory kmf;
        kmf = com.sun.net.ssl.KeyManagerFactory.getInstance("SunX509");
        same(p, kmf.getProvider());
        kmf = com.sun.net.ssl.KeyManagerFactory.getInstance("SunX509", "Legacy8uJSSE");
        same(p, kmf.getProvider());
        kmf = com.sun.net.ssl.KeyManagerFactory.getInstance("SunX509", p);
        same(p, kmf.getProvider());

        com.sun.net.ssl.TrustManagerFactory tmf;
        tmf = com.sun.net.ssl.TrustManagerFactory.getInstance("SunX509");
        same(p, tmf.getProvider());
        tmf = com.sun.net.ssl.TrustManagerFactory.getInstance("SunX509", "Legacy8uJSSE");
        same(p, tmf.getProvider());
        tmf = com.sun.net.ssl.TrustManagerFactory.getInstance("SunX509", p);
        same(p, tmf.getProvider());
    }

}

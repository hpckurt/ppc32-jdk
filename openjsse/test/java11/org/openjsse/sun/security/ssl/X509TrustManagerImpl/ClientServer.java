/*
 * Copyright (c) 2002, 2014, Oracle and/or its affiliates. All rights reserved.
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
 * @bug 4717766
 * @author Brad Wetmore
 * @summary 1.0.3 JsseX509TrustManager erroneously calls isClientTrusted()
 * @modules org.openjsse/org.openjsse.com.sun.net.ssl
 * @run main/manual ClientServer
 */

/*
 * SunJSSE does not support dynamic system properties, no way to re-use
 * system properties in samevm/agentvm mode.
 *
 * JSSE supports algorithm constraints with CR 6916074, need to update
 * this test case in JDK 7 soon.
 *
 * This problem didn't exist in JSSE 1.4, only JSSE 1.0.3.  However,
 * this is a useful test, so I decided to include it in 1.4.2.
 */

import java.io.*;
import java.net.*;
import javax.net.ssl.*;
import java.security.cert.*;
import java.security.*;
import org.openjsse.com.sun.net.ssl.*;

public class ClientServer {

    /*
     * =============================================================
     * Set the various variables needed for the tests, then
     * specify what tests to run on each side.
     */

    /*
     * Should we run the client or server in a separate thread?
     * Both sides can throw exceptions, but do you have a preference
     * as to which side should be the main thread.
     */
    static boolean separateServerThread = true;

    /*
     * Where do we find the keystores?
     */
    static String pathToStores = "../../../../javax/net/ssl/etc";
    static String keyStoreFile = "keystore";
    static String trustStoreFile = "truststore";
    static String passwd = "passphrase";

    /*
     * Is the server ready to serve?
     */
    volatile static boolean serverReady = false;

    /*
     * Turn on SSL debugging?
     */
    static boolean debug = false;

    /*
     * If the client or server is doing some kind of object creation
     * that the other side depends on, and that thread prematurely
     * exits, you may experience a hang.  The test harness will
     * terminate all hung threads after its timeout has expired,
     * currently 3 minutes by default, but you might try to be
     * smart about it....
     */

    /*
     * Define the server side of the test.
     *
     * If the server prematurely exits, serverReady will be set to true
     * to avoid infinite hangs.
     */
    void doServerSide() throws Exception {
        SSLServerSocketFactory sslssf = getDefaultServer();
        SSLServerSocket sslServerSocket =
            (SSLServerSocket) sslssf.createServerSocket(serverPort);
        serverPort = sslServerSocket.getLocalPort();

        /*
         * Signal Client, we're ready for his connect.
         */
        serverReady = true;

        SSLSocket sslSocket = (SSLSocket) sslServerSocket.accept();
        sslSocket.setNeedClientAuth(true);
        InputStream sslIS = sslSocket.getInputStream();
        OutputStream sslOS = sslSocket.getOutputStream();

        sslIS.read();
        sslOS.write(85);
        sslOS.flush();

        sslSocket.close();

        if (!serverTM.wasServerChecked() && serverTM.wasClientChecked()) {
            System.out.println("SERVER TEST PASSED!");
        } else {
            throw new Exception("SERVER TEST FAILED!  " +
                !serverTM.wasServerChecked() + " " +
                serverTM.wasClientChecked());
        }
    }

    /*
     * Define the client side of the test.
     *
     * If the server prematurely exits, serverReady will be set to true
     * to avoid infinite hangs.
     */
    void doClientSide() throws Exception {

        /*
         * Wait for server to get started.
         */
        while (!serverReady) {
            Thread.sleep(50);
        }

        SSLSocketFactory sslsf = getDefaultClient();
        SSLSocket sslSocket = (SSLSocket)
            sslsf.createSocket("localhost", serverPort);

        InputStream sslIS = sslSocket.getInputStream();
        OutputStream sslOS = sslSocket.getOutputStream();

        sslOS.write(280);
        sslOS.flush();
        sslIS.read();

        sslSocket.close();

        if (clientTM.wasServerChecked() && !clientTM.wasClientChecked()) {
            System.out.println("CLIENT TEST PASSED!");
        } else {
            throw new Exception("CLIENT TEST FAILED!  " +
                clientTM.wasServerChecked() + " " +
                !clientTM.wasClientChecked());
        }
    }

    private org.openjsse.com.sun.net.ssl.SSLContext getDefault(MyX509TM tm)
            throws Exception {

        String keyFilename =
            System.getProperty("test.src", "./") + "/" + pathToStores +
                "/" + keyStoreFile;
        String trustFilename =
            System.getProperty("test.src", "./") + "/" + pathToStores +
                "/" + trustStoreFile;

        char[] passphrase = "passphrase".toCharArray();
        KeyStore ks = KeyStore.getInstance("JKS");
        ks.load(new FileInputStream(keyFilename), passphrase);

        org.openjsse.com.sun.net.ssl.KeyManagerFactory kmf =
            org.openjsse.com.sun.net.ssl.KeyManagerFactory.getInstance("SunX509");
        kmf.init(ks, passphrase);

        ks = KeyStore.getInstance("JKS");
        ks.load(new FileInputStream(trustFilename), passphrase);

        org.openjsse.com.sun.net.ssl.TrustManagerFactory tmf =
            org.openjsse.com.sun.net.ssl.TrustManagerFactory.getInstance("SunX509");
        tmf.init(ks);

        org.openjsse.com.sun.net.ssl.TrustManager [] tms = tmf.getTrustManagers();

        int i;
        for (i = 0; i < tms.length; i++) {
            if (tms[i] instanceof org.openjsse.com.sun.net.ssl.X509TrustManager) {
                break;
            }
        }

        if (i >= tms.length) {
            throw new Exception("Couldn't find X509TM");
        }

        tm.init((org.openjsse.com.sun.net.ssl.X509TrustManager)tms[i]);
        tms = new MyX509TM [] { tm };

        org.openjsse.com.sun.net.ssl.SSLContext ctx =
            org.openjsse.com.sun.net.ssl.SSLContext.getInstance("TLS");
        ctx.init(kmf.getKeyManagers(), tms, null);
        return ctx;
    }

    MyX509TM serverTM;
    MyX509TM clientTM;

    private SSLServerSocketFactory getDefaultServer() throws Exception {
        serverTM = new MyX509TM();
        return getDefault(serverTM).getServerSocketFactory();
    }

    private SSLSocketFactory getDefaultClient() throws Exception {
        clientTM = new MyX509TM();
        return getDefault(clientTM).getSocketFactory();
    }

    static class MyX509TM implements org.openjsse.com.sun.net.ssl.X509TrustManager {

        org.openjsse.com.sun.net.ssl.X509TrustManager tm;
        boolean clientChecked;
        boolean serverChecked;

        void init(org.openjsse.com.sun.net.ssl.X509TrustManager x509TM) {
            tm = x509TM;
        }

        public boolean wasClientChecked() {
            return clientChecked;
        }

        public boolean wasServerChecked() {
            return serverChecked;
        }

        public boolean isClientTrusted(X509Certificate[] chain) {
            clientChecked = true;
            return true;
        }

        public boolean isServerTrusted(X509Certificate[] chain) {
            serverChecked = true;
            return true;
        }

        public X509Certificate[] getAcceptedIssuers() {
            return tm.getAcceptedIssuers();
        }
    }

    /*
     * =============================================================
     * The remainder is just support stuff
     */

    // use any free port by default
    volatile int serverPort = 0;

    volatile Exception serverException = null;
    volatile Exception clientException = null;

    public static void main(String[] args) throws Exception {

        if (debug)
            System.setProperty("javax.net.debug", "all");

        /*
         * Start the tests.
         */
        new ClientServer();
    }

    Thread clientThread = null;
    Thread serverThread = null;

    /*
     * Primary constructor, used to drive remainder of the test.
     *
     * Fork off the other side, then do your work.
     */
    ClientServer() throws Exception {
        if (separateServerThread) {
            startServer(true);
            startClient(false);
        } else {
            startClient(true);
            startServer(false);
        }

        /*
         * Wait for other side to close down.
         */
        if (separateServerThread) {
            serverThread.join();
        } else {
            clientThread.join();
        }

        /*
         * When we get here, the test is pretty much over.
         *
         * If the main thread excepted, that propagates back
         * immediately.  If the other thread threw an exception, we
         * should report back.
         */
        if (serverException != null)
            throw serverException;
        if (clientException != null)
            throw clientException;
    }

    void startServer(boolean newThread) throws Exception {
        if (newThread) {
            serverThread = new Thread() {
                public void run() {
                    try {
                        doServerSide();
                    } catch (Exception e) {
                        /*
                         * Our server thread just died.
                         *
                         * Release the client, if not active already...
                         */
                        System.err.println("Server died...");
                        serverReady = true;
                        serverException = e;
                    }
                }
            };
            serverThread.start();
        } else {
            doServerSide();
        }
    }

    void startClient(boolean newThread) throws Exception {
        if (newThread) {
            clientThread = new Thread() {
                public void run() {
                    try {
                        doClientSide();
                    } catch (Exception e) {
                        /*
                         * Our client thread just died.
                         */
                        System.err.println("Client died...");
                        clientException = e;
                    }
                }
            };
            clientThread.start();
        } else {
            doClientSide();
        }
    }
}

/*
 * reserved comment block
 * DO NOT REMOVE OR ALTER!
 */
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
package com.sun.org.apache.xml.internal.security.keys.keyresolver.implementations;

import java.security.PublicKey;
import java.security.cert.Certificate;
import java.security.cert.X509Certificate;
import java.util.Iterator;


import com.sun.org.apache.xml.internal.security.exceptions.XMLSecurityException;
import com.sun.org.apache.xml.internal.security.keys.content.x509.XMLX509SubjectName;
import com.sun.org.apache.xml.internal.security.keys.keyresolver.KeyResolverException;
import com.sun.org.apache.xml.internal.security.keys.keyresolver.KeyResolverSpi;
import com.sun.org.apache.xml.internal.security.keys.storage.StorageResolver;
import com.sun.org.apache.xml.internal.security.utils.Constants;
import com.sun.org.apache.xml.internal.security.utils.XMLUtils;
import org.w3c.dom.Element;

public class X509SubjectNameResolver extends KeyResolverSpi {

    private static final java.util.logging.Logger LOG =
        java.util.logging.Logger.getLogger(X509SubjectNameResolver.class.getName());


    /**
     * Method engineResolvePublicKey
     *
     * @param element
     * @param baseURI
     * @param storage
     * @return null if no {@link PublicKey} could be obtained
     * @throws KeyResolverException
     */
    public PublicKey engineLookupAndResolvePublicKey(
        Element element, String baseURI, StorageResolver storage
    ) throws KeyResolverException {

        X509Certificate cert =
            this.engineLookupResolveX509Certificate(element, baseURI, storage);

        if (cert != null) {
            return cert.getPublicKey();
        }

        return null;
    }

    /**
     * Method engineResolveX509Certificate
     * {@inheritDoc}
     * @param element
     * @param baseURI
     * @param storage
     *
     * @throws KeyResolverException
     */
    public X509Certificate engineLookupResolveX509Certificate(
        Element element, String baseURI, StorageResolver storage
    ) throws KeyResolverException {
        LOG.log(java.util.logging.Level.FINE, "Can I resolve " +  element.getTagName() + "?");
        Element[] x509childNodes = null;
        XMLX509SubjectName x509childObject[] = null;

        if (!XMLUtils.elementIsInSignatureSpace(element, Constants._TAG_X509DATA)) {
            LOG.log(java.util.logging.Level.FINE, "I can't");
            return null;
        }
        x509childNodes =
            XMLUtils.selectDsNodes(element.getFirstChild(), Constants._TAG_X509SUBJECTNAME);

        if (!(x509childNodes != null && x509childNodes.length > 0)) {
            LOG.log(java.util.logging.Level.FINE, "I can't");
            return null;
        }

        try {
            if (storage == null) {
                Object exArgs[] = { Constants._TAG_X509SUBJECTNAME };
                KeyResolverException ex =
                    new KeyResolverException("KeyResolver.needStorageResolver", exArgs);

                LOG.log(java.util.logging.Level.FINE, "", ex);

                throw ex;
            }

            x509childObject = new XMLX509SubjectName[x509childNodes.length];

            for (int i = 0; i < x509childNodes.length; i++) {
                x509childObject[i] = new XMLX509SubjectName(x509childNodes[i], baseURI);
            }

            Iterator<Certificate> storageIterator = storage.getIterator();
            while (storageIterator.hasNext()) {
                X509Certificate cert = (X509Certificate)storageIterator.next();
                XMLX509SubjectName certSN =
                    new XMLX509SubjectName(element.getOwnerDocument(), cert);

                LOG.log(java.util.logging.Level.FINE, "Found Certificate SN: " +  certSN.getSubjectName() + "");

                for (int i = 0; i < x509childObject.length; i++) {
                    LOG.log(java.util.logging.Level.FINE, "Found Element SN:     " +  x509childObject[i].getSubjectName() + "");

                    if (certSN.equals(x509childObject[i])) {
                        LOG.log(java.util.logging.Level.FINE, "match !!! ");

                        return cert;
                    }
                    LOG.log(java.util.logging.Level.FINE, "no match...");
                }
            }

            return null;
        } catch (XMLSecurityException ex) {
            LOG.log(java.util.logging.Level.FINE, "XMLSecurityException", ex);

            throw new KeyResolverException(ex);
        }
    }

    /**
     * Method engineResolveSecretKey
     * {@inheritDoc}
     * @param element
     * @param baseURI
     * @param storage
     *
     */
    public javax.crypto.SecretKey engineLookupAndResolveSecretKey(
        Element element, String baseURI, StorageResolver storage
    ) {
        return null;
    }
}

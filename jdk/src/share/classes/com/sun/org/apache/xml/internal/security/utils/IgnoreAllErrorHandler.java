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
package com.sun.org.apache.xml.internal.security.utils;

import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

/**
 * This {@link org.xml.sax.ErrorHandler} does absolutely nothing but LOG
 * the events.
 *
 */
public class IgnoreAllErrorHandler implements ErrorHandler {

    /** {@link org.apache.commons.logging} logging facility */
    private static final java.util.logging.Logger log =
        java.util.logging.Logger.getLogger(IgnoreAllErrorHandler.class.getName());

    /** Field throwExceptions */
    private static final boolean warnOnExceptions = getProperty(
            "com.sun.org.apache.xml.internal.security.test.warn.on.exceptions");

    /** Field throwExceptions           */
    private static final boolean throwExceptions = getProperty(
            "com.sun.org.apache.xml.internal.security.test.throw.exceptions");

    private static boolean getProperty(String name) {
        return java.security.AccessController.doPrivileged(
                new java.security.PrivilegedAction<Boolean>() {

                    @Override
                    public Boolean run() {
                        return Boolean.getBoolean(name);
                    }
                });
    }

    /** {@inheritDoc} */
    @Override
    public void warning(SAXParseException ex) throws SAXException {
        if (IgnoreAllErrorHandler.warnOnExceptions) {
            log.log(java.util.logging.Level.WARNING, "", ex);
        }
        if (IgnoreAllErrorHandler.throwExceptions) {
            throw ex;
        }
    }


    /** {@inheritDoc} */
    @Override
    public void error(SAXParseException ex) throws SAXException {
        if (IgnoreAllErrorHandler.warnOnExceptions) {
            log.log(java.util.logging.Level.SEVERE, "", ex);
        }
        if (IgnoreAllErrorHandler.throwExceptions) {
            throw ex;
        }
    }


    /** {@inheritDoc} */
    @Override
    public void fatalError(SAXParseException ex) throws SAXException {
        if (IgnoreAllErrorHandler.warnOnExceptions) {
            log.log(java.util.logging.Level.WARNING, "", ex);
        }
        if (IgnoreAllErrorHandler.throwExceptions) {
            throw ex;
        }
    }
}

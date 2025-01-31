#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
#
# This code is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 only, as
# published by the Free Software Foundation.
#
# This code is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# version 2 for more details (a copy is included in the LICENSE file that
# accompanied this code).
#
# You should have received a copy of the GNU General Public License version
# 2 along with this work; if not, write to the Free Software Foundation,
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
# or visit www.oracle.com if you need additional information or have any
# questions.
#

#
# @test
# @bug 8046321
# @library ../../../../java/security/testlibrary
# @build CertificateBuilder SimpleOCSPServer
# @run shell StatusResponseManager.sh
# @summary OCSP Stapling for TLS


if [ "${TESTJAVA}" = "" ]
then
        echo "TESTJAVA not set.  Test cannot execute.  Failed."
        exit 1
fi

if [ "${COMPILEJAVA}" = "" ]; then
        COMPILEJAVA="${TESTJAVA}"
fi

if [ "${TESTSRC}" = "" ]
then
        TESTSRC="."
fi

OS=`uname -s`
case "$OS" in
    SunOS | Linux | Darwin | AIX )
        FILESEP="/"
        PATHSEP=":"
        ;;

    CYGWIN* )
        FILESEP="/"
        PATHSEP=";"
        ;;

    Windows* )
        FILESEP="\\"
        PATHSEP=";"
        ;;
esac

set -ex
echo TESTCLASSES=${TESTCLASSES}
echo CPAPPEND=${CPAPPEND}

#
# Compile the tests, package into their respective jars
#
${COMPILEJAVA}${FILESEP}bin${FILESEP}javac ${TESTJAVACOPTS} ${TESTTOOLVMOPTS} -d . \
    -classpath ${TESTCLASSES}/../../../../java/security/testlibrary \
    ${TESTSRC}${FILESEP}org${FILESEP}openjsse${FILESEP}sun${FILESEP}security${FILESEP}ssl${FILESEP}StatusResponseManagerTests.java

${COMPILEJAVA}${FILESEP}bin${FILESEP}jar ${TESTTOOLVMOPTS} -cvf strmt.jar \
    org${FILESEP}openjsse${FILESEP}sun${FILESEP}security${FILESEP}ssl${FILESEP}StatusResponseManagerTests*.class

#
# Don't want the original class files to be used, because
# we want the jar files with the associated contexts to
# be used.
#
rm -rf org

#
# This is the only thing we really care about as far as
# test status goes.
#
${TESTJAVA}${FILESEP}bin${FILESEP}java ${TESTVMOPTS} \
    -Dtest.src=${TESTSRC} \
    -Xbootclasspath/a:"strmt.jar"${PATHSEP}${COMPILEJAVA}${FILESEP}jre${FILESEP}lib${FILESEP}ext${FILESEP}openjsse.jar${PATHSEP}${TESTCLASSES}/../../../../java/security/testlibrary \
    -Djavax.net.debug=ssl:respmgr \
    org.openjsse.sun.security.ssl.StatusResponseManagerTests
retval=$?

rm strmt.jar

exit $retval

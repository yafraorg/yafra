#!/bin/sh
#-------------------------------------------------------------------------------
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
# (c) yafra.org, 2002, Switzerland
#
# function:	generate SSH key to work with putty
#
# argument: cert basename
#
# CVS tag:   $Name:  $
# author:    $Author: mwn $
# revision:  $Revision: 16 $
#-------------------------------------------------------------------------------

# arguments are: 1: cert basename
if [ -z "$1" ]; then
	echo gensshcert tool for openssl
	echo use: gensshcert name_of_cert
	echo afterwards convert with ssh-keygen2 -k name_of_cert.pfx
	echo use the CN like this CN=servername;dns=servername.domain.com
	echo make sure that the subjectAltName is set to DNS:hostname.domain.net within the openssl.cnf!!!
        exit
fi


# create SSHd server request
openssl genrsa -des3 -rand /var/log/wtmp -out $1.key 1024
# enter as CN hostname;dns=hostname.domain.net
openssl req -config openssl.cnf -new -key $1.key -out $1.csr
# before you sign, make sure that the subjectAltName is set to DNS:hostname.domain.net
# sign SSHd server request with CA
openssl ca -config openssl.cnf -policy policy_anything -out $1.crt -infiles $1.csr
# create PKCS12 pfx file - this includes public and private key with an export password
openssl pkcs12 -export -in $1.crt -inkey $1.key -out $1.pfx -des3

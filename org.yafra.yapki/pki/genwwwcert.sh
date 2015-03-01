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
# function:	PKI generate web certificate (apache mod_ssl)
#
# argument: cert basename
#
# CVS tag:   $Name:  $
# author:    $Author: mwn $
# revision:  $Revision: 16 $
#-------------------------------------------------------------------------------

# arguments are: 1: certificate basename
if [ -z "$1" ]; then
        echo Please specify certfile basename
        exit
fi

# create WWW server request
openssl genrsa -des3 -out $1.key 1024
openssl req -config openssl.cnf -new -sha1 -key $1.key -out $1.csr
# sign WWW server request with CA
openssl ca -config openssl.cnf -policy policy_anything -out $1.crt -infiles $1.csr
# create RSA private key with password for automatic server startup
cp $1.key $1.key.org
openssl rsa -in $1.key.org -out $1.key

@echo off

REM Licensed to the Apache Software Foundation (ASF) under one
REM or more contributor license agreements.  See the NOTICE file
REM distributed with this work for additional information
REM regarding copyright ownership.  The ASF licenses this file
REM to you under the Apache License, Version 2.0 (the
REM "License"); you may not use this file except in compliance
REM with the License.  You may obtain a copy of the License at
REM
REM http://www.apache.org/licenses/LICENSE-2.0
REM
REM Unless required by applicable law or agreed to in writing,
REM software distributed under the License is distributed on an
REM "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
REM KIND, either express or implied.  See the License for the
REM specific language governing permissions and limitations
REM under the License.
REM
REM generate a new CA and WWW server certification (Apache compliant)
REM

REM check first argument
if ""%1""=="""" goto about

REM create WWW server request
openssl genrsa -des3 -rand C:\xy.log -out %1.key 1024
openssl req -config openssl.cnf -new -sha1 -key %1.key -out %1.csr
REM sign WWW server request with CA
openssl ca -config openssl.cnf -policy policy_anything -out %1.crt -infiles %1.csr
REM create RSA private key with password for automatic server startup
copy %1.key %1.key.org
openssl rsa -in %1.key.org -out %1.key
goto end

:about
echo yafra.org - genwwwcert tool for openssl
echo use "genwwwcert name_of_cert"

:end
REM that's it
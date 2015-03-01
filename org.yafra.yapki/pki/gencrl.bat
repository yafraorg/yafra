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
REM generate a cert revocation list
REM

REM check first argument
if ""%1""=="""" goto about

REM execute revoke - you will be prompted for the CA password!
openssl ca -gencrl -config openssl.cnf -crldays %1 -crlexts crl_ext -out YOURCA/crl/caYOURCA.crl
openssl crl -in YOURCA/crl/caYOURCA.crl -outform DER -out YOURCA/crl/caYOURCA-der.crl
goto end

:about
echo generate crl tool for openssl
echo use "gencrl 30" where 30 are the days when the next CRL is published

:end
REM that's it
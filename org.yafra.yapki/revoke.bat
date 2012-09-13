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
REM revoke first argument which is the serial
REM

REM check first argument
if ""%1""=="""" goto about

REM execute revoke - you will be prompted for the CA password!
openssl ca -config openssl.cnf -revoke CA_ROOT/newcerts/%1.pem
goto end

:about
echo yafra.org - revoke tool for openssl
echo use "revoke 03" where 03 is the serial of the cert to revoke

:end
REM that's it
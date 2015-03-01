@echo off

REM
REM revoke first argument which is the serial
REM

REM check first argument
if ""%1""=="""" goto about

REM execute revoke - you will be prompted for the CA password!
openssl ca -config openssl.cnf -revoke nissle/newcerts/%1.pem
goto end

:about
echo revoke tool for openssl
echo use "revoke 03" where 03 is the serial of the cert to revoke

:end
REM that's it
@ echo off
if  {%1}=={} goto help
echo Exports from %1 the dump %2 with root passwd %3 and system passwd %4
echo.
pushd ..
cd sql
sqlplus root/%3@%1 < dbe_drop_functions.sql >> ../dump/exp%1.log
cd ..
cd dump
exp root/%3@%1 FILE=%2 OWNER=root BUFFER=103200 LOG=exp%1.ilog GRANTS= no
type exp%1.ilog >> ../dump/exp%1.log
rm exp%1.ilog
cd ..
cd sql
sqlplus root/%3@%1 < dbe_functions.sql >> ../dump/exp%1.log
cd ..

goto end
:help

echo.
echo Syntax :
echo    export database_name dump_name root_password system_password 
echo.

:end
popd
@ echo on
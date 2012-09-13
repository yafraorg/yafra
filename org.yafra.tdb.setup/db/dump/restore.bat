@ echo off
if  {%1}=={} goto help
echo Plays on %1 the dump %2 with root passwd %3 and system passwd %4
echo.

pushd ..
cd sql
sqlplus system/%4@%1 < dbe_drop_users.sql > ../dump/%1.log
sqlplus system/%4@%1 < dbe_users.sql >> ../dump/%1.log

cd ..
cd dump
imp root/%3@%1 FILE=%2 FROMUSER=root TOUSER=root COMMIT=yes IGNORE=yes BUFFER=103200 LOG=%1.ilog GRANTS= no
type %1.flog >> %1.log
type %1.ilog >> %1.log
del %1.flog
del %1.ilog
cd ..
cd sql
sqlplus root/%3@%1 < dbe_drop_views.sql >> ../dump/%1.log
sqlplus root/%3@%1 < dbe_drop_functions.sql >> ../dump/%1.log
sqlplus root/%3@%1 < dbe_drop_index.sql >> ../dump/%1.log
sqlplus root/%3@%1 < dbe_functions.sql >> ../dump/%1.log
sqlplus root/%3@%1 < dbe_views.sql >> ../dump/%1.log
sqlplus root/%3@%1 < dbe_index.sql >> ../dump/%1.log
sqlplus root/%3@%1 < dbe_grant.sql >> ../dump/%1.log
cd ..
cd dump

goto end
:help

echo.
echo Syntax :
echo    restore database_name dump_name root_password system_password 
echo.

:end
popd
@ echo on
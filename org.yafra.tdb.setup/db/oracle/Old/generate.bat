@ echo off


REM
REM %1,2 : Analyse {dbname}, {system_pwd} parameters
REM

if {%1} == {} goto help
if {%1} == {help} goto help
if {%2} == {} goto help

echo.  
echo Creates a Marco Polo database on %1 with systen password %2


REM
REM %3 : Analyse [{release} local] parameter and set RELEASE flag
REM

if {%3} == {} goto usinglocalparam
if {%3} == {local} goto usinglocalparam
goto usingcheckoutparam 

:usinglocalparam
set RELEASE=
echo    using local files
goto endreleaseparam

:usingcheckoutparam
set RELEASE=%3
echo    using checkout from release %RELEASE%
goto endreleaseparam

:endreleaseparam


REM 
REM %4 : Analyse [{dump} nodump] parameter and set CORE_DUMP, BASE_DUMP flags
REM 

if {%4} == {} goto withnodumpparam
if {%4} == {nodump} goto withnodumpparam
REM allowed exceptions : core or base specified at the fourth place
if {%4} == {core} goto withnodumpparam
if {%4} == {base} goto withnodumpparam
goto withdumpparam

: withnodumpparam
set CORE_DUMP=
set BASE_DUMP=
echo    creates no dump
REM allowed exceptions : core or base specified at the fourth place
if {%4} == {core} goto insertcoreparam
if {%4} == {base} goto insertbaseparam
goto enddumpparam

: withdumpparam
if {%5} == {core} goto withcoredumpparam
goto withbasedumpparam

:withcoredumpparam
set CORE_DUMP=mapo_core_%4.dmp
set BASE_DUMP=
echo    creates core dump with name %CORE_DUMP%
goto enddumpparam

:withbasedumpparam
set CORE_DUMP=mapo_core_%4.dmp
set BASE_DUMP=mapo_base_%4.dmp
echo    creates core and base dump with names %CORE_DUMP%
echo                                      and %BASE_DUMP%
goto enddumpparam

:enddumpparam

REM
REM %5 : Analyse [core base] parameter and set INSERT_BASE flag
REM

if {%5} == {core} goto insertcoreparam
if {%5} == {base} goto insertbaseparam
goto insertbaseparam

: insertbaseparam
set INSERT_BASE=true
echo    insert base data
goto endcoreparam

: insertcoreparam
set INSERT_BASE=false
echo    insert core data only
goto endcoreparam

: endcoreparam

echo.
choice /C:yn Shall we go on ?
IF ERRORLEVEL 2 goto follow
:follow
echo Ignore previous error. let's go...


REM  ###   
REM #   #   
REM #   #   
REM #   #   
REM #   #   
REM #   #   
REM  ### 
REM
REM CREATE TEMP PATH
REM

set TEMP_DRIVE=C:
set TEMP_PATH=\temp\%1%RELEASE%
echo. 
echo Default creation path is %TEMP_DRIVE%%TEMP_PATH%
echo. 
mkdir %TEMP_DRIVE%%TEMP_PATH%

:checkout
if {%RELEASE%} == {} goto nocheckout

REM   #   
REM  ##   
REM # #   
REM   #   
REM   #   
REM   #   
REM ##### 
REM
REM CHECKOUT OF NEEDED RESOURCES
REM

pushd %TEMP_DRIVE%
%TEMP_DRIVE%
cd %TEMP_PATH%

echo checkout Core Database structure ...
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_drop.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_drop_users.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_users.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_tables.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_functions.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_views.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_index.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_grant.sql
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_sequences.sql

echo checkout Core Database structure ...
call cvs checkout -r %RELEASE% mpto/database/excel/Core.zip

REM
REM checkout base files if necessary
REM
if {%INSERT_BASE%} == {false} goto endcheckoutbase

echo checkout update sequences
call cvs checkout -r %RELEASE% mpto/database/sql/update_sequences.plsql

echo checkout PISO internal
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_users_piso.sql

echo checkout Base Database structure ...
call cvs checkout -r %RELEASE% mpto/database/excel/TOAktion.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOAngebotsTyp.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOKollektivTyp.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOKundenTyp.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOLabel.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOLand.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOOrt.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOReisenderTyp.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOSprachen.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOStatus.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOTraegerTyp.zip
call cvs checkout -r %RELEASE% mpto/database/excel/TOWaehrung.zip
:endcheckoutbase

REM
REM checkout export script to create dump(s) if necessary
REM
if {%CORE_DUMP%} == {} goto endcheckoutexport

echo checkout export script to create dump(s)
call cvs checkout -r %RELEASE% mpto/database/dump/export.bat
call cvs checkout -r %RELEASE% mpto/database/sql/dbe_drop_functions.sql

:endcheckoutexport


goto endcheckout

:nocheckout

REM  #### 
REM #    #
REM      #
REM  #### 
REM #     
REM #     
REM ##### 
REM
REM COPY OF NEEDED RESOURCES

mkdir %TEMP_DRIVE%%TEMP_PATH%\mpto
mkdir %TEMP_DRIVE%%TEMP_PATH%\mpto\database
mkdir %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql

echo copy Core Database structure ...
copy sql\dbe_drop.sql           %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_drop_users.sql     %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_users.sql          %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_tables.sql         %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_functions.sql      %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_views.sql          %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_index.sql          %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_grant.sql          %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\dbe_sequences.sql      %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\

echo checkout Core Database structure ...
mkdir %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel
copy excel\Core.zip         %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\

REM
REM copy base files if necessary
REM
if {%INSERT_BASE%} == {false} goto endcopybase

echo Copy update sequences
copy sql\update_sequences.plsql %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\

echo Copy PISO internal
copy sql\dbe_users_piso.sql     %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\
copy sql\update_sequences.plsql %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\

echo checkout Base Database structure ...
copy excel\TOAktion.zip         %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOAngebotsTyp.zip    %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOKollektivTyp.zip   %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOKundenTyp.zip      %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOLabel.zip          %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOLand.zip           %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOOrt.zip            %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOReisenderTyp.zip   %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOSprachen.zip       %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOStatus.zip         %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOTraegerTyp.zip     %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
copy excel\TOWaehrung.zip       %TEMP_DRIVE%%TEMP_PATH%\mpto\database\excel\
:endcopybase


REM
REM copy export script to create dump(s) if necessary
REM
if {%CORE_DUMP%} == {} goto endcopyexport

echo copy export script to create dump(s)
mkdir %TEMP_DRIVE%%TEMP_PATH%\mpto\database\dump
copy dump\export.bat            %TEMP_DRIVE%%TEMP_PATH%\mpto\database\dump\
copy sql\dbe_drop_functions.sql %TEMP_DRIVE%%TEMP_PATH%\mpto\database\sql\

:endcopyexport

:endcheckout


REM  ####
REM #    #
REM      #
REM  #### 
REM      #     
REM #    #
REM  #### 
REM
REM UNZIP OF NEEDED BASE DATA

%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database
cd excel
del *.sql

echo Extracting the sql core scripts from the excel file

unzip Core.zip
type CoreBez*.sql > current.sql
del CoreBez*.sql
type Core*.sql > current2.sql
del Core*.sql
type current.sql > CoreBez.sql
type current2.sql > Core.sql

if {%INSERT_BASE%} == {false} goto endunzipbase

echo Extracting the sql base scripts from the excel file

unzip TOAktion.zip
type TOAktionBez*.sql > current.sql
del TOAktionBez*.sql
type TOAktion*.sql > current2.sql
del TOAktion*.sql
type current.sql > TOAktionBez.sql
type current2.sql > TOAktion.sql

unzip TOAngebotsTyp.zip
type TOAngebotstypBez*.sql > current.sql
del TOAngebotstypBez*.sql 
type TOAngebotstyp*.sql > current2.sql
del TOAngebotstyp*.sql
type current.sql > TOAngebotstypBez.sql
type current2.sql > TOAngebotstyp.sql

unzip TOKollektivTyp.zip
type TOKollektivTypBez*.sql > current.sql
del TOKollektivTypBez*.sql 
type TOKollektivTyp*.sql > current2.sql
del TOKollektivTyp*.sql
type current.sql > TOKollektivTypBez.sql
type current2.sql > TOKollektivTyp.sql

unzip TOKundenTyp.zip
type TOKundenTypBez*.sql > current.sql
del TOKundenTypBez*.sql 
type TOKundenTyp*.sql > current2.sql
del TOKundenTyp*.sql
type current.sql > TOKundenTypBez.sql
type current2.sql > TOKundenTyp.sql

unzip TOLabel.zip
type TOLabel*.sql > current.sql
del TOLabel*.sql
type current.sql  > TOLabel.sql

unzip TOLand.zip
type TOLandBez*.sql > current.sql
del TOLandBez*.sql
type TOLand*.sql > current2.sql
del TOLand*.sql
type current.sql > TOLandBez.sql
type current2.sql > TOLand.sql

unzip TOOrt.zip
type TOOrtBez*.sql > current.sql
del TOOrtBez*.sql
type TOOrt*.sql > current2.sql
del TOOrt*.sql
type current.sql > TOOrtBez.sql
type current2.sql > TOOrt.sql

unzip TOReisenderTyp.zip
type TOReisenderTypBez*.sql > current.sql
del TOReisenderTypBez*.sql 
type TOReisenderTyp*.sql > current2.sql
del TOReisenderTyp*.sql
type current.sql > TOReisenderTypBez.sql
type current2.sql > TOReisenderTyp.sql

unzip TOSprachen.zip
type TOSprachenBez*.sql > current.sql
del TOSprachenBez*.sql
type TOSprachen*.sql > current2.sql
del TOSprachen*.sql
type current.sql > TOSprachenBez.sql
type current2.sql > TOSprachen.sql

unzip TOStatus.zip
type TOStatusBez*.sql > current.sql
del TOStatusBez*.sql
type TOStatus*.sql > current2.sql
del TOStatus*.sql
type current.sql > TOStatusBez.sql
type current2.sql > TOStatus.sql

unzip TOTraegertyp.zip
type TOTraegerTypBez*.sql > current.sql
del TOTraegerTypBez*.sql 
type TOTraegerTyp*.sql > current2.sql
del TOTraegerTyp*.sql
type current.sql > TOTraegerTypBez.sql
type current2.sql > TOTraegerTyp.sql

unzip TOWaehrung.zip
type TOWaehrungBez*.sql > current.sql
del TOWaehrungBez*.sql 
type TOWaehrung*.sql > current2.sql
del TOWaehrung*.sql
type current.sql > TOWaehrungBez.sql
type current2.sql > TOWaehrung.sql

:endunzipbase

del current*.sql
del *.xls
del *.zip


REM #
REM #    #
REM #    #
REM #    #
REM #######
REM      #
REM      #
REM 
REM CREATE CORE DATABASE

echo Creates on %1 a new "core" database with system passwd %2
echo. 

%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database
cd sql

echo Deletes the old data.
sqlplus system/%2@%1 < dbe_drop.sql > ../mapo_core_%1.log

echo Deletes the old users. 
sqlplus system/%2@%1 < dbe_drop_users.sql >> ../mapo_core_%1.log

echo Create users...
sqlplus system/%2@%1 < dbe_users.sql >> ../mapo_core_%1.log

echo Creates the core database ...
echo ... tables
sqlplus root/root@%1 < dbe_tables.sql >> ../mapo_core_%1.log
echo ... functions
sqlplus root/root@%1 < dbe_functions.sql >> ../mapo_core_%1.log
echo ... views
sqlplus root/root@%1 < dbe_views.sql >> ../mapo_core_%1.log
echo ... index
sqlplus root/root@%1 < dbe_index.sql >> ../mapo_core_%1.log
echo ... grant
sqlplus root/root@%1 < dbe_grant.sql >> ../mapo_core_%1.log
echo ... sequences
sqlplus root/root@%1 < dbe_sequences.sql >> ../mapo_core_%1.log

echo Insert core data ...
%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database
cd excel

echo Insert Core data to the database ...
sqlplus root/root@%1 < Core.sql>> ../mapo_core_%1.log
sqlplus root/root@%1 < CoreBez.sql>> ../mapo_core_%1.log

REM
REM Export core dump if necessary
REM
if {%CORE_DUMP%} == {} goto endexportcore

%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database
cd dump

echo Export core dump ...
call export %1 %CORE_DUMP% root %2
@ echo off

:endexportcore

REM #######
REM #
REM #
REM ######
REM       #
REM #     #
REM  #####  
REM 
REM INSERT BASE DATA TO THE DATABASE

if {%INSERT_BASE%} == {false} goto endinsertbase

%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database
cd excel

echo Insert Base data to the database ...
echo ... languages
sqlplus root/root@%1 < TOSprachenBez.sql> ../mapo_base_%1.log
sqlplus root/root@%1 < TOSprachen.sql>> ../mapo_base_%1.log

echo ... labels
sqlplus root/root@%1 < TOLabel.sql>> ../mapo_base_%1.log

echo ... actions
sqlplus root/root@%1 < TOAktionBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOAktion.sql>> ../mapo_base_%1.log

echo ... moneys
sqlplus root/root@%1 < TOWaehrungBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOWaehrung.sql>> ../mapo_base_%1.log

echo ... countries
sqlplus root/root@%1 < TOLandBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOLand.sql>> ../mapo_base_%1.log

echo ... places (city, airports)
sqlplus root/root@%1 < TOOrtBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOOrt.sql>> ../mapo_base_%1.log

echo ... statuses
sqlplus root/root@%1 < TOStatusBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOStatus.sql>> ../mapo_base_%1.log

echo ... traveler types
sqlplus root/root@%1 < TOReisenderTypBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOReisenderTyp.sql>> ../mapo_base_%1.log

echo ... kollektiv types
sqlplus root/root@%1 < TOKollektivTypBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOKollektivTyp.sql>> ../mapo_base_%1.log

echo ... kunden types
sqlplus root/root@%1 < TOKundenTypBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOKundenTyp.sql>> ../mapo_base_%1.log


echo ... offer types
sqlplus root/root@%1 < TOAngebotstypBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOAngebotstyp.sql>> ../mapo_base_%1.log

echo ... carrier types
sqlplus root/root@%1 < TOTraegerTypBez.sql>> ../mapo_base_%1.log
sqlplus root/root@%1 < TOTraegerTyp.sql>> ../mapo_base_%1.log


echo ...updates the sequences

%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database
cd sql
sqlplus root/root@%1 < update_sequences.plsql >> base%1.log
cd ..

REM
REM Export base dump if necessary
REM
if {%BASE_DUMP%} == {} goto endexportbase

%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database
cd dump

echo Export base dump ...
call export %1 %BASE_DUMP% root %2
@ echo off

:endexportbase

:endinsertbase

REM   #####
REM  #
REM #
REM ######
REM #     #
REM #     #
REM  #####  
REM 
REM OPTIMISE DATABASE

echo Setting analyse_schema to optimize the database

%TEMP_DRIVE%
cd %TEMP_PATH%
cd mpto
cd database

echo  BEGIN DBMS_UTILITY.ANALYZE_SCHEMA('ROOT', 'ESTIMATE'); END; commit; > optimize.plsql
sqlplus root/root@%1 < optimize.plsql > optimize%1.log
del optimize.plsql

goto end

REM #    #  ######  #       #####
REM #    #  #       #       #    #
REM ######  #####   #       #    #
REM #    #  #       #       #####
REM #    #  #       #       #
REM #    #  ######  ######  #

:help

echo.
echo Database generation script use :
echo.
echo  generate {dbname} {system_pwd} [{release} local] [{dump} nodump] [core base]  
echo.
echo  1: {dbname} : database SID or alias
echo  2: {system_pwd} : database password of system user
echo  3: {release} : CVS tag to checkout to generate the database, as 'r_5_0_1'
echo                 NB: you can use 'head' to have the last CVS files
echo     local     : use local version of files
echo  4: {dump}: creates a dump from core database named mapo_core_{dump}.dmp 
echo             and, if base was chosen, from base database, with name 
echo             mapo_base_{dump}.dmp 
echo     nodump: creates no dump
echo  5: core : generate database with no data 
echo            (only tables, views, indexes, functions, sequences,
echo            -1 entries in tables)
echo     base : generate database with minimal data 
echo            (core + language list, country list...)
echo.    
echo Default values for optional parameters are :
echo.    
echo  generate {dbname} {system_password} local base nodump

:end

popd
set RELEASE=
set CORE_DUMP=
set BASE_DUMP=
set INSERT_BASE=

@ echo on

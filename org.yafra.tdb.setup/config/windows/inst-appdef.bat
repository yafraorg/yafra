@ echo off
if  {%1}=={} goto help

REM
REM installs the MPgui X11 app-defaults %1 to %2
REM
copy %1 %2
goto end

:help
echo.
echo Syntax :
echo    inst-appdef c:\xy\MPgui YOUR_HOME_PATH 
echo.

:end
@ echo on
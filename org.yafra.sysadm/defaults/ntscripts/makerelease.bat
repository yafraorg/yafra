@ echo off
REM
REM Build release (only java)
REM

echo.
echo build java release - make sure source is up to date
echo.

cd org.yafra.server.core
ant
cd ..\org.yafra.server.directclient
ant
cd ..\org.yafra.server.ejb-openejb
ant


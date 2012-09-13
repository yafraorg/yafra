@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by HELPMW.HPJ. >"hlp\helpmw.hm"
echo. >>"hlp\helpmw.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\helpmw.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\helpmw.hm"
echo. >>"hlp\helpmw.hm"
echo // Prompts (IDP_*) >>"hlp\helpmw.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\helpmw.hm"
echo. >>"hlp\helpmw.hm"
echo // Resources (IDR_*) >>"hlp\helpmw.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\helpmw.hm"
echo. >>"hlp\helpmw.hm"
echo // Dialogs (IDD_*) >>"hlp\helpmw.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\helpmw.hm"
echo. >>"hlp\helpmw.hm"
echo // Frame Controls (IDW_*) >>"hlp\helpmw.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\helpmw.hm"
REM -- Make help for Project HELPMW


echo Building Win32 Help files
start /wait hcrtf -x "hlp\helpmw.hpj"
echo.
if exist Debug\nul copy "hlp\helpmw.hlp" Debug
if exist Debug\nul copy "hlp\helpmw.cnt" Debug
if exist Release\nul copy "hlp\helpmw.hlp" Release
if exist Release\nul copy "hlp\helpmw.cnt" Release
echo.



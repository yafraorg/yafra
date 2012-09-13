;
; Installer Script for Nullsoft NSIS v1.8+
;
; Application: travelDB TO Classic
; Copyright:   yafra.org
; Autor:       info@yafra.org
; Version:     check git revision
; ChangeLog:
; - 05/2002 mw initial setup done
; - 06/2002 mw finalized and tested on naked win2k pc

;
; compiler settings (uncomment and change at will):
;
; SetCompress auto ; (can be off or force)
; SetDatablockOptimize on ; (can be off)
; CRCCheck on ; (can be off)
; AutoCloseWindow false ; (can be true for the window go away automatically at end)
; ShowInstDetails hide ; (can be show to have them shown, or nevershow to disable)
; SetDateSave off ; (can be on to have files restored to their orginal date)

;
; global defines
;
; setx.exe and sc.exe comes from w2k resource kit
;
!define VER_MAJOR 5
!define VER_MINOR 40
!define CYGWINDLL "c:\opt\cygwin\bin\cygwin1.dll"
#!define X11DLL "c:\opt\cygwin\usr\X11R6\bin\lib*.dll"
!define X11DLL2 "c:\opt\cygwin\usr\X11R6\bin\cyg*.dll"
!define GNOMEDLL "c:\opt\cygwin\opt\gnome\lib\*.dll"
!define MAPOBIN "c:\opt\cygwin\work\bin"
!define MAPOLICENSE "c:\opt\cygwin\work\cvs\mapo\data\license.txt"
!define MAPOREADME "c:\opt\cygwin\work\cvs\mapo\data\readme.txt"
!define MAPOETC "c:\opt\cygwin\work\cvs\mapo\data\windows"
!define MAPODB "c:\opt\cygwin\work\cvs\mapo\db"

;
; project name and installer output file
;
Name "travelDB"
OutFile "tdbclassic-v${VER_MAJOR}r${VER_MINOR}.exe"
Icon ${MAPOETC}\mapo.ico

;
; PISO License for MARCO POLO TO Classic
;
LicenseText "You must read the following license before installing:"
LicenseData ${MAPOLICENSE}

;
; install section and settings
;
ComponentText "This will install MARCO POLO TO Classic v${VER_MAJOR}.${VER_MINOR} on your computer:"
InstType "GTK user interface (required)"
InstType "X11/Motif user interface"
InstType "Server program (without database !)"
InstType "Outputs and actions"
InstallDir "$PROGRAMFILES\mapo"
InstallDirRegKey HKEY_LOCAL_MACHINE "SOFTWARE\PISOAG\mapo" ""
; DirShow show
DirText "Select the directory to install MARCO POLO in:"

; Pages
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Section "" ; (default installation for ALL)
	SetOutPath "$INSTDIR"
	File ${MAPOLICENSE}
	File ${MAPOREADME}
	File ${MAPOETC}\mpgui.ico
	File ${MAPOETC}\mapo.ico
	File ${MAPOETC}\InstallOptions.dll
	File ${MAPOETC}\mpgui.ini
	File ${MAPOETC}\setx.exe
	File ${MAPOETC}\update-services.exe
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\pswhat.exe"

	; setzen vom Pfad
	Exec '$INSTDIR\setx.exe Path "%PATH%;$INSTDIR\bin"'

	; edit services
	Exec "$INSTDIR\update-services.exe"

	; write registry
	WriteRegStr HKEY_LOCAL_MACHINE "SOFTWARE\PISOAG\mapo" "" "$INSTDIR"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\mapo" "DisplayName" "MARCO POLO TO Classic"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\mapo" "UninstallString" '"$INSTDIR\uninst.exe"'
	; write uninstaller
	WriteUninstaller "$INSTDIR\uninst.exe"
SectionEnd

Section "" ; (default start programs entries)
	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\MARCO POLO"
	Delete "$SMPROGRAMS\MARCO POLO\MAPO Home Page.lnk"
	WriteINIStr "$SMPROGRAMS\MARCO POLO\MAPO Home Page.url" \
		"InternetShortcut" "URL" "http://www.touristic.ch/"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\Uninstall MAPO.lnk" \
		"$INSTDIR\uninst.exe"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\Documentation.lnk" \
		"$INSTDIR\manual\index.htm"
SectionEnd

Section "GTK user interface"
	SectionIn 1
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\mpgui.exe"
	#File ${GNOMEDLL}

	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\MARCO POLO"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\MAPO-Gtk.lnk" \
		"$INSTDIR\bin\mpgtk.exe" "" "$INSTDIR\mapo.ico"
	SetOutPath $INSTDIR
	CreateShortCut "$DESKTOP\MAPO.lnk" "$INSTDIR\bin\mpgtk.exe" "" "$INSTDIR\mapo.ico"
SectionEnd

Section "X11/Motif user interface (without X11 server)"
	SectionIn 2
	
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\mpgui.exe"
	#File "${MAPOBIN}\psedit.exe"
	File ${CYGWINDLL}
	#File ${X11DLL}
	File ${X11DLL2}
	
	SetOutPath "$INSTDIR\etc"
	File "${MAPOETC}\MPgui"
	File "${MAPOETC}\errors"
	File "${MAPOETC}\labels_d"
	File "${MAPOETC}\cursback.bm"
	File "${MAPOETC}\curscomm.bm"
	File "${MAPOETC}\error.wav"
	File "${MAPOETC}\message.wav"
	File "${MAPOETC}\mptogra.icon"
	File "${MAPOETC}\mptogui.icon"
	File "${MAPOETC}\quit.wav"
	File "${MAPOETC}\toggle.wav"
	File "${MAPOETC}\welcome.wav"
	File "${MAPOETC}\makempguipro.bat"
	File "${MAPOETC}\inst-appdef.bat"

	Push $INSTDIR\mpgui.ini
	InstallOptions::dialog "$INSTDIR\InstallOptions.dll"
	; CallInstDLL $INSTDIR\InstallOptions.dll dialog
	Pop $1
	; mapo mpdbi server hostname
	ReadINIStr $R0 $INSTDIR\mpgui.ini "Field 2" State
	; db user
	ReadINIStr $R1 $INSTDIR\mpgui.ini "Field 5" State
	; db user pwd
	ReadINIStr $R2 $INSTDIR\mpgui.ini "Field 7" State
	; db name (oracle db name)
	ReadINIStr $R3 $INSTDIR\mpgui.ini "Field 10" State
	; home directory
	ReadINIStr $R4 $INSTDIR\mpgui.ini "Field 12" State

	; setzen von home im user space
	Exec "$INSTDIR\setx.exe HOME $R4"

	; erstellen von mpgui.pro und .mpgui im home des users
	Exec "$INSTDIR\etc\makempguipro.bat $R4\.mpgui $R3 $R1 $R2"

	; aendern von MPgui X11 appdefaults fehlt und restliche dateien
	Exec "$INSTDIR\etc\inst-appdef.bat $INSTDIR\etc\MPgui $R4\MPgui"

	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\MARCO POLO"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\MAPO-X11.lnk" \
		"$INSTDIR\bin\mpgui.exe" "-D -s $R0 -display localhost:0.0" "$INSTDIR\mpgui.ico"
	SetOutPath $INSTDIR
	CreateShortCut "$DESKTOP\MAPO-X11.lnk" \
		"$INSTDIR\bin\mpgui.exe" "-D -s $R0 -display localhost:0.0" "$INSTDIR\mpgui.ico"
SectionEnd

Section "Database server (without Oracle)"
	SectionIn 3
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\mpdbi.exe"
	#File "${MAPOBIN}\mpnet.exe"
	File "${MAPOBIN}\psfifo.exe"
	File ${CYGWINDLL}
	File "${MAPODB}\oracle\oci.dll"
	; database creation files
	SetOutPath "$INSTDIR\db"
	; File "${MAPODB}\dump\mapodemo.dmp"
	; File "${MAPODB}\sql\dbe_drop_views.sql"
	; File "${MAPODB}\sql\dbe_drop_functions.sql"
	; File "${MAPODB}\sql\dbe_drop_index.sql"
	; File "${MAPODB}\sql\dbe_functions.sql"
	; File "${MAPODB}\sql\dbe_views.sql"
	; File "${MAPODB}\sql\dbe_index.sql"
	; File "${MAPODB}\sql\dbe_grant.sql"
	; File "${MAPODB}\abstract\def_mp2000.sql"
	; File "${MAPODB}\abstract\def_d_aktionen.sql"
	; File "${MAPODB}\abstract\def_e_aktionen.sql"
	File "${MAPODB}\abstract\def_d_msg*.sql"
	File "${MAPODB}\abstract\def_e_msg*.sql"
	; File "${MAPODB}\abstract\out_d_*.sql"
	; File "${MAPODB}\mapo-dbsetup.exe"

	; ExecWait "$INSTDIR\db\mapo-dbsetup.exe $INSTDIR\db"

	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\MARCO POLO"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\MAPO-Server.lnk" \
		"$INSTDIR\bin\mpdbi.exe" "-debug" "$INSTDIR\mpgui.ico"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\MAPOnet-Server.lnk" \
		"$INSTDIR\bin\mpnet.exe" "-debug" "$INSTDIR\mpgui.ico"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\Execute-Server.lnk" \
		"$INSTDIR\bin\psfifo.exe" "-debug" "$INSTDIR\mpgui.ico"
	CreateShortCut "$SMPROGRAMS\MARCO POLO\MAPO-DB-Setup-Wizard.lnk" \
		"$INSTDIR\db\mapo-dbsetup.exe" '"$INSTDIR\db"' "$INSTDIR\mpgui.ico"
	SetOutPath $INSTDIR
	CreateShortCut "$DESKTOP\MAPO-Server.lnk" \
		"$INSTDIR\bin\mpdbi.exe" "-debug" "$INSTDIR\mpgui.ico"
SectionEnd

Section "Outputs and actions (without Oracle)"
	SectionIn 4
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\OUT*.exe"
	File ${CYGWINDLL}
SectionEnd

;
; uninstall settings/section
;
UninstallText "This will uninstall MARCO POLO from your system"
Section Uninstall
	SetShellVarContext all
	Delete "$SMPROGRAMS\MARCO POLO\*.lnk"
	Delete "$SMPROGRAMS\MARCO POLO\*.url"
	RMDir "$SMPROGRAMS\MARCO POLO"
	Delete "$DESKTOP\MAPO.lnk"
	Delete "$DESKTOP\MAPO-X11.lnk"
	Delete $DESKTOP\MAPO-Server.lnk"

	DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\PISOAG\mapo"
	DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\mapo"

	Delete "$INSTDIR\*.*"
	Delete "$INSTDIR\bin\*.*"
	RMDir "$INSTDIR\bin"
	Delete "$INSTDIR\etc\*.*"
	RMDir "$INSTDIR\etc"
	Delete "$INSTDIR\db\*.*"
	RMDir "$INSTDIR\db"
	RMDir "$INSTDIR"
SectionEnd ; end of uninstall section

Function .onInstSuccess
	MessageBox MB_YESNO "Thank you for installing MARCO POLO TO Classic - would you like to see the README.txt ?" IDNO NoReadme
		Exec "notepad.exe $INSTDIR\readme.txt"
	NoReadme:
FunctionEnd

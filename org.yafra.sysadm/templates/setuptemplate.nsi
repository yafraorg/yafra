;
; Installer Script for Nullsoft NSIS v1.8+
;
; Application: put your application name here
; Copyright:   yafra.org, 2002, Switzerland
; Autor:       x@y
; Version:     check cvs revision
; ChangeLog:
; - 05/2002 mw initial setup done

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
!define VER_MAJOR 5
!define VER_MINOR 00
!define CYGWINDLL "e:\opt\cygwin\bin\cygwin1.dll"
!define X11DLL "e:\opt\cygwin\usr\X11R6\bin\lib*.dll"
!define GNOMEDLL "e:\opt\gnome\lib\*.dll"
!define MAPOBIN "e:\work\bin"
!define MAPOLICENSE "e:\softech\mapo\data\license.txt"
!define MAPOREADME "e:\softech\mapo\data\readme.txt"
!define MAPOETC "e:\softech\mapo\data\windows"

;
; project name and installer output file
;
Name "travelDB"
OutFile "mapotoclassic-v${VER_MAJOR}r${VER_MINOR}.exe"
Icon ${MAPOETC}\mapo.ico

;
; License for travelDB TO Classic
;
LicenseText "You must read the following license before installing:"
LicenseData ${MAPOLICENSE}

;
; install section and settings
;
ComponentText "This will install travelDB TO Classic v${VER_MAJOR}.${VER_MINOR} on your computer:"
InstType "GTK user interface (required)"
InstType "X11/Motif user interface"
InstType "Server program (without Oracle !)"
InstType "Outputs and actions"
InstallDir "$PROGRAMFILES\mapo"
InstallDirRegKey HKEY_LOCAL_MACHINE "SOFTWARE\PISOAG\mapo" ""
DirShow show
DirText "Select the directory to install travelDB in:"

Section "" ; (default installation for ALL)
	SetOutPath "$INSTDIR"
	File ${MAPOLICENSE}
	File ${MAPOREADME}
	File ${MAPOETC}\mpgui.ico
	File ${MAPOETC}\mapo.ico
	File ${MAPOETC}\InstallOptions.dll
	File ${MAPOETC}\mpgui.ini
	; write registry
	WriteRegStr HKEY_LOCAL_MACHINE "SOFTWARE\PISOAG\mapo" "" "$INSTDIR"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\mapo" "DisplayName" "travelDB TO Classic"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\mapo" "UninstallString" '"$INSTDIR\uninst.exe"'
	; write uninstaller
	WriteUninstaller "$INSTDIR\uninst.exe"
SectionEnd

Section "" ; (default installation for ALL)
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\pswhat.exe"
SectionEnd

Section "" ; (default start programs entries)
	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\travelDB"
	Delete "$SMPROGRAMS\travelDB\yafra.org Home Page.lnk"
	WriteINIStr "$SMPROGRAMS\travelDB\yafra.org Home Page.url" \
		"InternetShortcut" "URL" "http://www.touristic.ch/"
	CreateShortCut "$SMPROGRAMS\travelDB\Uninstall TDB.lnk" \
		"$INSTDIR\uninst.exe"
	CreateShortCut "$SMPROGRAMS\travelDB\Documentation.lnk" \
		"$INSTDIR\manual\index.htm"
SectionEnd

Section "GTK user interface"
	SectionIn 1
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\mpgtk.exe"
	File ${GNOMEDLL}

	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\travelDB"
	CreateShortCut "$SMPROGRAMS\travelDB\TDB-Gtk.lnk" \
		"$INSTDIR\bin\mpgtk.exe" "" "$INSTDIR\mapo.ico"
	SetOutPath $INSTDIR
	CreateShortCut "$DESKTOP\MAPO.lnk" "$INSTDIR\bin\mpgtk.exe" "" "$INSTDIR\mapo.ico"
SectionEnd

Section "X11/Motif user interface (without X11 server)"
	SectionIn 2
	; etc/services fehlt noch
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\mpgui.exe"
	File "${MAPOBIN}\psedit.exe"
	File ${CYGWINDLL}
	File ${X11DLL}
	SetOutPath "$INSTDIR\etc"
	File "${MAPOETC}\MPgui"
	File "${MAPOETC}\errors"
	File "${MAPOETC}\labels_d"

	Push $INSTDIR\mpgui.ini
	CallInstDLL $INSTDIR\InstallOptions.dll dialog
	Pop $1
	ReadINIStr $R0 $INSTDIR\mpgui.ini "Field 2" State
	ReadINIStr $R1 $INSTDIR\mpgui.ini "Field 5" State
	ReadINIStr $R2 $INSTDIR\mpgui.ini "Field 7" State

	; setzen von home
	; erstellen von mpgui.pro und .mpgui im home des users
	; aendern von MPgui fehlt und restliche dateien

	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\travelDB"
	CreateShortCut "$SMPROGRAMS\travelDB\TDB-X11.lnk" \
		"$INSTDIR\bin\mpgui.exe" "-D -s $R0 -display localhost:0.0" "$INSTDIR\mpgui.ico"
	SetOutPath $INSTDIR
	CreateShortCut "$DESKTOP\MAPO-X11.lnk" \
		"$INSTDIR\bin\mpgui.exe" "-D -s $R0 -display localhost:0.0" "$INSTDIR\mpgui.ico"
SectionEnd

Section "Database server (without Oracle)"
	SectionIn 3
	; etc/services fehlt noch
	; database creation fehlt
	; test ohne cygwin installiert fuer tmp etc
	; start von mpdbi und psfifo fehlt
	SetOutPath "$INSTDIR\bin"
	File "${MAPOBIN}\mpdbi.exe"
	File "${MAPOBIN}\psfifo.exe"
	File ${CYGWINDLL}
	SetShellVarContext all
	SetOutPath "$SMPROGRAMS\travelDB"
	CreateShortCut "$SMPROGRAMS\travelDB\MAPO-Server.lnk" \
		"$INSTDIR\bin\mpdbi.exe" "-debug" "$INSTDIR\mpgui.ico"
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
UninstallText "This will uninstall travelDB from your system"
Section Uninstall
	SetShellVarContext all
	Delete "$SMPROGRAMS\travelDB\*.lnk"
	Delete "$SMPROGRAMS\travelDB\*.url"
	RMDir "$SMPROGRAMS\travelDB"
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
	RMDir "$INSTDIR"
SectionEnd ; end of uninstall section

Function .onInstSuccess
	MessageBox MB_YESNO "Thank you for installing travelDB TO Classic - would you like to see the README.txt ?" IDNO NoReadme
		Exec "notepad.exe ${MAPOREADME}"
	NoReadme:
FunctionEnd
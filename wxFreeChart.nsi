#
# NSIS (http://nsis.sourceforge.net) script for creating Windows installer.
#
!include "MUI2.nsh"

Name "wxFreeChart"
OutFile "wxFreeChart-1.7.exe"

InstallDir "c:\wxFreeChart-1.7"

!define MUI_ABORTWARNINGS
!define MUI_FINISHPAGE_LINK "http://wxcode.sourceforge.net/components/freechart/"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "license.txt"
!insertmacro MUI_PAGE_DIRECTORY 
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "German"

Section "wxFreeChart"
	SetOutPath $INSTDIR

	File /r build
	File /r doc
	File /r include
	File /r lib
	File /r sample
	File /r src
	File configure
	File Makefile.in
	File Readme.txt

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "DisplayName" "wxFreeChart"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "UninstallString" "$INSTDIR\uninstall.exe"
	
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "NoRepair" 1

	WriteUninstaller "uninstall.exe"
SectionEnd

Section "Start menu shortcuts"
	CreateDirectory "$SMPROGRAMS\wxFreeChart"

	# TODO add here link to documentation and demo application 
	#CreateShortcut "$SMPROGRAMS\wxFreeChart\.lnk" \
	#	"$INSTDIR\Binaries\Win32\UDK.exe" "-seekfreeloading" "$INSTDIR\Mnogomir.ico" 0

	CreateShortcut "$SMPROGRAMS\wxFreeChart\Reference manual.lnk" \
		"$INSTDIR\doc\html\index.html" "" "" 0

	CreateShortcut "$SMPROGRAMS\wxFreeChart\Uninstall.lnk" "$INSTDIR\uninstall.exe" \
		"" "$INSTDIR\uninstall.exe" 0
SectionEnd

Section "Uninstall"
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart"

	RmDir /r $INSTDIR
	
	RmDir /r "$SMPROGRAMS\wxFreeChart"
SectionEnd
	



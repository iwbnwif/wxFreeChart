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
	File license.txt

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "DisplayName" "wxFreeChart-1.7"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "UninstallString" "$INSTDIR\uninstall.exe"
	
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart" "NoRepair" 1

	WriteUninstaller "uninstall.exe"
SectionEnd

Section "Start menu shortcuts"
	SetShellVarContext all

	CreateDirectory "$SMPROGRAMS\wxFreeChart-1.7"

	# TODO add here link to demo application 
	
	CreateShortcut "$SMPROGRAMS\wxFreeChart-1.7\Reference manual.lnk" \
		"$INSTDIR\doc\html\index.html" "" "" 0

	CreateShortcut "$SMPROGRAMS\wxFreeChart-1.7\Uninstall.lnk" "$INSTDIR\uninstall.exe" \
		"" "$INSTDIR\uninstall.exe" 0
SectionEnd

Section "Uninstall"
	SetShellVarContext all

	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\wxFreeChart"

	RmDir /r $INSTDIR
	
	Delete "$SMPROGRAMS\wxFreeChart-1.7\Reference manual.lnk"
	Delete "$SMPROGRAMS\wxFreeChart-1.7\Uninstall.lnk"
	RmDir /r "$SMPROGRAMS\wxFreeChart-1.7"
SectionEnd

VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "wxFreeChart"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" ""
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" ""
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© Moskvichev Andrey V."
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "wxFreeChart Installer"
VIProductVersion "1.7.0.1"

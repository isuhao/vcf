# Microsoft Developer Studio Project File - Name="VCFNewClassWiz" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VCFNewClassWiz - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFNewClassWiz.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFNewClassWiz.mak" CFG="VCFNewClassWiz - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VCFNewClassWiz - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo

# ADD BSC32 /nologo /o"Release/VCFNewClassWiz_vc6.bsc"

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Rpcrt4.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/VCFNewClassWiz.dll"
# Begin Target

# Name "VCFNewClassWiz - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=./Commands.cpp
# End Source File
# Begin Source File

SOURCE=./NewClassDlg.cpp
# End Source File
# Begin Source File

SOURCE=./PostHeaderDlg.cpp
# End Source File
# Begin Source File

SOURCE=./PreHeaderDlg.cpp
# End Source File
# Begin Source File

SOURCE=./PropertyInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=./StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=./VCFNewClassWiz.cpp
# End Source File
# Begin Source File

SOURCE=./VCFNewClassWiz.def
# End Source File
# Begin Source File

SOURCE=./VCFNewClassWiz.idl
# ADD MTL /tlb "./VCFNEWCLASSWIZ.tlb" /h "VCFNEWCLASSWIZ.h" /Oicf
# End Source File
# Begin Source File

SOURCE=./VCFNewClassWiz.rc
# End Source File
# Begin Source File

SOURCE=./VCFNewClassWizAddin.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=./Commands.h
# End Source File
# Begin Source File

SOURCE=./NewClassDlg.h
# End Source File
# Begin Source File

SOURCE=./PostHeaderDlg.h
# End Source File
# Begin Source File

SOURCE=./PreHeaderDlg.h
# End Source File
# Begin Source File

SOURCE=./PropertyInfoDlg.h
# End Source File
# Begin Source File

SOURCE=./resource.h
# End Source File
# Begin Source File

SOURCE=./StdAfx.h
# End Source File
# Begin Source File

SOURCE=./VCFNewClassWizAddin.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=./res/bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=./Commands.rgs
# End Source File
# Begin Source File

SOURCE=./res/TBarLrge.bmp
# End Source File
# Begin Source File

SOURCE=./res/TBarMedm.bmp
# End Source File
# Begin Source File

SOURCE=./res/toolbar_.bmp
# End Source File
# Begin Source File

SOURCE=./res/VCFNewClassWiz.rc2
# End Source File
# Begin Source File

SOURCE=./VCFNewClassWizAddin.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=./VCFNewClassWiz.tlb
# End Source File
# End Target
# End Project

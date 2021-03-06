# Microsoft Developer Studio Project File - Name="AppResources" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AppResources - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AppResources.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AppResources.mak" CFG="AppResources - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AppResources - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AppResources - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AppResources - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\"
# PROP Intermediate_Dir "Release\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /machine:I386 /out:"AppResources.exe" /libpath:"$(VCF_ROOT)/lib"

!ELSEIF  "$(CFG)" == "AppResources - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\"
# PROP Intermediate_Dir "Debug\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"AppResources.exe" /pdbtype:sept /libpath:"$(VCF_ROOT)/lib"

!ENDIF 

# Begin Target

# Name "AppResources - Win32 Release"
# Name "AppResources - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=AppResources.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resources"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "en_US"

# PROP Default_Filter ""
# Begin Source File

SOURCE=Resources\en_US\brushed-metal.bmp
# End Source File
# Begin Source File

SOURCE=Resources\en_US\WhatIsVCF.txt
# End Source File
# End Group
# Begin Group "de_DE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=Resources\de_DE\brushed-metal.bmp
# End Source File
# End Group
# Begin Group "it_IT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=Resources\it_IT\brushed-metal.bmp
# End Source File
# Begin Source File

SOURCE=Resources\it_IT\WhatIsVCF.txt
# End Source File
# End Group
# Begin Source File

SOURCE=Resources\brushed-metal.bmp
# End Source File
# Begin Source File

SOURCE=Resources\WhatIsVCF.txt
# End Source File
# End Group
# End Target
# End Project

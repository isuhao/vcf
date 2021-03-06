# Microsoft Developer Studio Project File - Name="NetworkKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=NetworkKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NetworkKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NetworkKit.mak" CFG="NetworkKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NetworkKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "NetworkKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NetworkKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\ReleaseS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_FOUNDATIONKIT_LIB" /Yu"vcf/NetworkKit/NetworkKit.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/NetworkKit_vc6_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/NetworkKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "NetworkKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\DebugS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "USE_FOUNDATIONKIT_LIB" /Yu"vcf/NetworkKit/NetworkKit.h" /Fd"..\..\..\lib\NetworkKit_vc6_sd.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/NetworkKit_vc6_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/NetworkKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "NetworkKit - Win32 Release"
# Name "NetworkKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\IPAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkKit.cpp
# ADD CPP /Yc"vcf/NetworkKit/NetworkKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Socket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32IPAddressPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32NetworkToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32SocketPeer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\IPAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\IPAddressPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkExceptions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Socket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32IPAddressPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32NetworkToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32SocketPeer.h
# End Source File
# End Group
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="NetworkKitDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=NetworkKitDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NetworkKitDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NetworkKitDLL.mak" CFG="NetworkKitDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NetworkKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NetworkKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NetworkKitDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "icl7\Release\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NETKIT_DLL" /D "NETKIT_EXPORTS" /D "USE_FOUNDATIONKIT_DLL" /Yu"vcf/NetworkKit/NetworkKit.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/NetworkKit_icl7.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 Ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\..\..\bin\NetworkKit_icl7.dll" /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "NetworkKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "icl7\DebugDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NETWORKKITDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NETKIT_DLL" /D "NETKIT_EXPORTS" /Fd"..\..\..\bin\NetworkKit_icl7_d.pdb" /Yu"vcf/NetworkKit/NetworkKit.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/NetworkKit_icl7_d.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Ws2_32.lib comctl32.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\..\..\bin\NetworkKit_icl7_d.dll" /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "NetworkKitDLL - Win32 Release"
# Name "NetworkKitDLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\DatagramSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetToolkit.cpp
# ADD CPP /Yc"vcf/NetworkKit/NetworkKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\ServerSocketEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Socket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketListeningLoop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\URL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32DatagramSocketPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32SocketPeer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\DatagramSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\ServerSocketEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Socket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketListeningLoop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\URL.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32DatagramSocketPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32SocketPeer.h
# End Source File
# End Group
# End Target
# End Project

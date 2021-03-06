# Microsoft Developer Studio Project File - Name="SharedLibraries" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SharedLibraries - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SharedLibraries.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SharedLibraries.mak" CFG="SharedLibraries - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SharedLibraries - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SharedLibraries - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SharedLibraries - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc80\Release\"
# PROP Intermediate_Dir "vc80\Release\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_CONSOLE" /D "USE_FOUNDATIONKIT_DLL" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"vc80/Release/SharedLibraries_vc80.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /subsystem:console /machine:I386 /out:"vc80\Release\SharedLibraries_vc80.exe" /libpath:"$(VCF_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "SharedLibraries - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc80\Debug\"
# PROP Intermediate_Dir "vc80\Debug\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_CONSOLE" /D "USE_FOUNDATIONKIT_DLL" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"vc80/Debug/SharedLibraries_vc80.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /subsystem:console /debug /machine:I386 /out:"vc80\Debug\SharedLibraries_vc80.exe" /pdbtype:sept /libpath:"$(VCF_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SharedLibraries - Win32 Release"
# Name "SharedLibraries - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=SharedLibraries.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "sharedLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=SimpleDLL.cpp

!IF  "$(CFG)" == "SharedLibraries - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__SIMPL="SimpleDLL.obj"	"SimpleDLL.so"	
# Begin Custom Build
InputPath=SimpleDLL.cpp

"SimpleDLL.so" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl /nologo /c /GR SimpleDLL.cpp 
	link /nologo /dll /out:SimpleDLL.so SimpleDLL.obj 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SharedLibraries - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__SIMPL="SimpleDLL.so"	"SimpleDLL.obj"	
# Begin Custom Build
InputPath=SimpleDLL.cpp

"SimpleDLL.so" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl /nologo /c /GR SimpleDLL.cpp 
	link /nologo /dll /out:SimpleDLL.so SimpleDLL.obj 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=SimpleDLL.h
# End Source File
# End Group
# End Target
# End Project

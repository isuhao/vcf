# Microsoft Developer Studio Project File - Name="VCF_GraphicsKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GraphicsKit - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_GraphicsKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_GraphicsKit.mak" CFG="GraphicsKit - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GraphicsKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GraphicsKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GraphicsKit - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "GraphicsKit - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GraphicsKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GraphicsKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GraphicsKit - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "GraphicsKit - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GraphicsKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\GraphicsKit_vc6_d.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\GraphicsKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\GraphicsKit_vc6_d.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\GraphicsKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib ..\..\..\lib\AGG_vc6_sd.lib ..\..\..\lib\LibJPEG_vc6_sd.lib ..\..\..\lib\LibPNG_vc6_sd.lib ..\..\..\lib\ZLib_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\GraphicsKit_vc6_d.pdb"
# ADD LINK32 FoundationKit_vc6_d.lib ..\..\..\lib\AGG_vc6_sd.lib ..\..\..\lib\LibJPEG_vc6_sd.lib ..\..\..\lib\LibPNG_vc6_sd.lib ..\..\..\lib\ZLib_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\GraphicsKit_vc6_d.pdb"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\GraphicsKit_vc6.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6\GraphicsKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\GraphicsKit_vc6.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6\GraphicsKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib ..\..\..\lib\AGG_vc6_s.lib ..\..\..\lib\LibJPEG_vc6_s.lib ..\..\..\lib\LibPNG_vc6_s.lib ..\..\..\lib\ZLib_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\GraphicsKit_vc6.pdb"
# ADD LINK32 FoundationKit_vc6.lib ..\..\..\lib\AGG_vc6_s.lib ..\..\..\lib\LibJPEG_vc6_s.lib ..\..\..\lib\LibPNG_vc6_s.lib ..\..\..\lib\ZLib_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\GraphicsKit_vc6.pdb"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\GraphicsKit_vc6_sd.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\GraphicsKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\GraphicsKit_vc6_sd.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\GraphicsKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\GraphicsKit_vc6_s.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_s\GraphicsKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\GraphicsKit_vc6_s.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_s\GraphicsKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\GraphicsKit_d.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_d\GraphicsKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\GraphicsKit_d.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_d\GraphicsKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib ..\..\..\lib\AGG_sd.lib ..\..\..\lib\LibJPEG_sd.lib ..\..\..\lib\LibPNG_sd.lib ..\..\..\lib\ZLib_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\GraphicsKit_d.pdb"
# ADD LINK32 FoundationKit_d.lib ..\..\..\lib\AGG_sd.lib ..\..\..\lib\LibJPEG_sd.lib ..\..\..\lib\LibPNG_sd.lib ..\..\..\lib\ZLib_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\GraphicsKit_d.pdb"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\GraphicsKit.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj\GraphicsKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\GraphicsKit.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj\GraphicsKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "GRAPHICSKIT_DLL" /d GRAPHICSKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib ..\..\..\lib\AGG_s.lib ..\..\..\lib\LibJPEG_s.lib ..\..\..\lib\LibPNG_s.lib ..\..\..\lib\ZLib_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit.lib" /pdb:"..\..\..\lib\..\bin\GraphicsKit.pdb"
# ADD LINK32 FoundationKit.lib ..\..\..\lib\AGG_s.lib ..\..\..\lib\LibJPEG_s.lib ..\..\..\lib\LibPNG_s.lib ..\..\..\lib\ZLib_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\GraphicsKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\GraphicsKit.lib" /pdb:"..\..\..\lib\..\bin\GraphicsKit.pdb"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\GraphicsKit_sd.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_sd\GraphicsKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\GraphicsKit_sd.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_sd\GraphicsKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_sd.lib"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\GraphicsKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\GraphicsKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\GraphicsKit_s.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_s\GraphicsKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\GraphicsKit_s.pdb /Yu"vcf\GraphicsKit\GraphicsKit.h" /Fp"..\..\..\lib\msvc6prj_s\GraphicsKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\GraphicsKit_s.lib"

!ENDIF

# Begin Target

# Name "GraphicsKit - Win32 vc6 DLL Debug"
# Name "GraphicsKit - Win32 vc6 DLL Release"
# Name "GraphicsKit - Win32 vc6 LIB Debug"
# Name "GraphicsKit - Win32 vc6 LIB Release"
# Name "GraphicsKit - Win32 DLL Debug"
# Name "GraphicsKit - Win32 DLL Release"
# Name "GraphicsKit - Win32 LIB Debug"
# Name "GraphicsKit - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AbstractImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicFill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicStroke.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BezierCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Color.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKit.cpp
# ADD BASE CPP /Yc"vcf\GraphicsKit\GraphicsKit.h"
# ADD CPP /Yc"vcf\GraphicsKit\GraphicsKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsToolKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GrayScaleImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\JPEGLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Matrix2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PNGLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Point.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSession.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Rect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Context.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32FontManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32PrintSession.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AbstractImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AggCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicFill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicRectangle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicStroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BezierCurve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Circle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Color.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Composition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ContextPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\DrawUIState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Ellipse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Fill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Filter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\FontPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GradientFills.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKitPrivate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundlePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsToolKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GrayScaleImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoaderException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageTile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\InvalidImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\JPEGLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Kernel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Layer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\MagicFMLibType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Matrix2D.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\NoGraphicsToolkitFoundException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PNGLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PixelFormats.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Pixels.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Point.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSessionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Printable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ShadowFill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Size.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\TileManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\UIMetricsManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\UVMap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Context.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32FontManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32PrintSession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32VisualStylesWrapper.h
# End Source File
# End Group
# End Target
# End Project


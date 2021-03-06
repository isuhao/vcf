# Microsoft Developer Studio Project File - Name="VCF_ImageKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ImageKit - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_ImageKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_ImageKit.mak" CFG="ImageKit - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImageKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageKit - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageKit - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageKit - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageKit - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImageKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\ImageKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\ImageKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
# ADD RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib OpenGLKit_vc6_d.lib ..\..\..\lib\glew_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\ImageKit_vc6_d.pdb"
# ADD LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib OpenGLKit_vc6_d.lib ..\..\..\lib\glew_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\ImageKit_vc6_d.pdb"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
# ADD RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib OpenGLKit_vc6.lib ..\..\..\lib\glew_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\ImageKit_vc6.pdb"
# ADD LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib OpenGLKit_vc6.lib ..\..\..\lib\glew_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\ImageKit_vc6.pdb"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ImageKit_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ImageKit_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageKit_vc6_s.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageKit_vc6_s.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\ImageKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\ImageKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
# ADD RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib OpenGLKit_d.lib ..\..\..\lib\glew_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\ImageKit_d.pdb"
# ADD LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib OpenGLKit_d.lib ..\..\..\lib\glew_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\ImageKit_d.pdb"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEKIT_DLL" /D "IMAGEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
# ADD RSC /l 0x409 /i "..\..\..\src\vcf\ImageKit\glew\include" /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "OPENGLKIT_DLL" /d "GLEW_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEKIT_DLL" /d "IMAGEKIT_EXPORTS" /i ..\..\src\vcf\ImageKit
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib OpenGLKit.lib ..\..\..\lib\glew_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit.lib" /pdb:"..\..\..\lib\..\bin\ImageKit.pdb"
# ADD LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib OpenGLKit.lib ..\..\..\lib\glew_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageKit.lib" /pdb:"..\..\..\lib\..\bin\ImageKit.pdb"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ImageKit_sd.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ImageKit_sd.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageKit_sd.lib"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\ImageKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\ImageKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageKit_s.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\vcf\ImageKit\glew\include" /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageKit_s.pdb /D "WIN32" /D "_LIB" /D "GLEW_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageKit_s.lib"

!ENDIF

# Begin Target

# Name "ImageKit - Win32 vc6 DLL Debug"
# Name "ImageKit - Win32 vc6 DLL Release"
# Name "ImageKit - Win32 vc6 LIB Debug"
# Name "ImageKit - Win32 vc6 LIB Release"
# Name "ImageKit - Win32 DLL Debug"
# Name "ImageKit - Win32 DLL Release"
# Name "ImageKit - Win32 LIB Debug"
# Name "ImageKit - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\ImageKit\ImageKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\..\src\vcf\ImageKit\ImageKit.rc

!IF  "$(CFG)" == "ImageKit - Win32 vc6 DLL Debug"


!ELSEIF  "$(CFG)" == "ImageKit - Win32 vc6 DLL Release"


!ELSEIF  "$(CFG)" == "ImageKit - Win32 vc6 LIB Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ImageKit - Win32 vc6 LIB Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ImageKit - Win32 DLL Debug"


!ELSEIF  "$(CFG)" == "ImageKit - Win32 DLL Release"


!ELSEIF  "$(CFG)" == "ImageKit - Win32 LIB Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ImageKit - Win32 LIB Release"

# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\ImageKit\ImageKit.h
# End Source File
# End Group
# End Target
# End Project


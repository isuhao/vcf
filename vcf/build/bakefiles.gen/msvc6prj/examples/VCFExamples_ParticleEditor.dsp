# Microsoft Developer Studio Project File - Name="VCFExamples_ParticleEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ParticleEditor - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_ParticleEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_ParticleEditor.mak" CFG="ParticleEditor - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ParticleEditor - Win32 vc6 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "ParticleEditor - Win32 vc6 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "ParticleEditor - Win32 vc6 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "ParticleEditor - Win32 vc6 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE "ParticleEditor - Win32 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "ParticleEditor - Win32 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "ParticleEditor - Win32 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "ParticleEditor - Win32 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ParticleEditor - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib OpenGLKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib OpenGLKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ELSEIF  "$(CFG)" == "ParticleEditor - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib OpenGLKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib OpenGLKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ELSEIF  "$(CFG)" == "ParticleEditor - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_sd.lib GraphicsKit_vc6_sd.lib ApplicationKit_vc6_sd.lib OpenGLKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_sd.lib GraphicsKit_vc6_sd.lib ApplicationKit_vc6_sd.lib OpenGLKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ELSEIF  "$(CFG)" == "ParticleEditor - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6_s.lib GraphicsKit_vc6_s.lib ApplicationKit_vc6_s.lib OpenGLKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6_s.lib GraphicsKit_vc6_s.lib ApplicationKit_vc6_s.lib OpenGLKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ELSEIF  "$(CFG)" == "ParticleEditor - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib OpenGLKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib OpenGLKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ELSEIF  "$(CFG)" == "ParticleEditor - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "OPENGLKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d OPENGLKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib OpenGLKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib OpenGLKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ELSEIF  "$(CFG)" == "ParticleEditor - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_sd.lib GraphicsKit_sd.lib ApplicationKit_sd.lib OpenGLKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_sd.lib GraphicsKit_sd.lib ApplicationKit_sd.lib OpenGLKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ELSEIF  "$(CFG)" == "ParticleEditor - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\ParticleEditor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\ParticleEditor"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\ParticleEditor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb /I "..\..\..\..\examples\ParticleEditor" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\examples\ParticleEditor" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i ..\..\..\..\src\thirdparty\common\agg\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit_s.lib GraphicsKit_s.lib ApplicationKit_s.lib OpenGLKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit_s.lib GraphicsKit_s.lib ApplicationKit_s.lib OpenGLKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\ParticleEditor\ParticleEditor.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\ParticleEditor\ParticleEditor.pdb"

!ENDIF

# Begin Target

# Name "ParticleEditor - Win32 vc6 DLL Debug"
# Name "ParticleEditor - Win32 vc6 DLL Release"
# Name "ParticleEditor - Win32 vc6 LIB Debug"
# Name "ParticleEditor - Win32 vc6 LIB Release"
# Name "ParticleEditor - Win32 DLL Debug"
# Name "ParticleEditor - Win32 DLL Release"
# Name "ParticleEditor - Win32 LIB Debug"
# Name "ParticleEditor - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\main.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\vrtoad\Math.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleEditor.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleRenderer.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleResource.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleResourceManager.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\ParticleSystem.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\Spinner.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\ParticleEditor\XMLParticleResourceHandler.h
# End Source File
# End Group
# End Target
# End Project


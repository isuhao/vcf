; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=VCF Builder 1.0.3 Alpha
AppVerName=VCF Builder 1.0.3 Alpha
AppPublisher=Diegoware
AppPublisherURL=http://vcf.sourceforge.net
AppSupportURL=http://vcf.sourceforge.net
AppUpdatesURL=http://vcf.sourceforge.net
DefaultDirName={pf}\VCFBuilder.1.0.3Alpha
DefaultGroupName=VCF Builder 1.0.3 Alpha
OutputDir=E:\code\vcfdev\stable\vcf\uploadToSF
OutputBaseFilename=VCFBuilder1.0.3.alpha
AppCopyright=�2002 Jim Crafton



LicenseFile=E:\code\vcfdev\stable\vcf\vcfLicense.txt
UninstallDisplayIcon={app}\VCFBuilder2_vc6.exe

; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]
Name: desktopicon; Description: Create a &desktop icon; GroupDescription: Additional icons:; MinVersion: 4,4

[Files]
Source: ..\..\BlackBox\BlackBox.dll; DestDir: {app}; Components: Application_Core
Source: ..\..\BlackBox\lib\dbghelp.dll; DestDir: {app}; Components: Application_Core
Source: ..\..\BlackBox\lib\psapi.dll; DestDir: {app}; Components: Application_Core
Source: ..\..\bin\Win32HTMLBrowser_vc6.dll; DestDir: {app}; Components: Application_Core
Source: ..\..\VCFBuilder2\Bin\help\back-pattern.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\bannerLogo.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\fade1.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\index.html; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\left sidebar.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\logo.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\stripe1.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\stripe2.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\stripe3.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\top-background.jpg; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\C++ Applications\C++ Applications.vcfdir; DestDir: {app}\ObjectRepository\C++ Applications\; Components: ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\Web Applications\Web Applications.vcfdir; DestDir: {app}\ObjectRepository\Web Applications\; Components: ObjectRepository
Source: ..\..\VCFBuilder2\Bin\help\features.html; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\getting_help.html; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\intro.html; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\help\tutorial1.html; DestDir: {app}\help; Components: Help
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\Form1.vff; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\project1.vcp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\console.vcp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\ObjectRepository.vcfdir; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\vwsp_spec.txt; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\vcp_spec.txt; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\vcfdir_spec.txt; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\FormResources.rc; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\blank_form.form; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\text.file; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\cppimpl.file; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\cppheader.file; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\simple_vcfobj_class.class; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\simple_cpp_class.class; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\blank_form.class; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\MainApplication.cpp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\Form1.cpp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\MainApplication.h; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\Form1.h; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\simple_console_proj.bmp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\CPPImpl.bmp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\CPPHeader.bmp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\ObjectRepository\basic_ui_proj.bmp; DestDir: {app}\ObjectRepository
Source: ..\..\VCFBuilder2\Bin\xmake.exe; DestDir: {app}
Source: ..\..\xmake\xmake_documentation.html; DestDir: {app}\help
Source: ..\..\VCFBuilder2\Bin\readme.txt; DestDir: {app}; Flags: isreadme
Source: C:\WINNT\system32\msvcp60.dll; DestDir: {app}
Source: C:\WINNT\system32\msvcrt.dll; DestDir: {sys}; CopyMode: alwaysskipifsameorolder; Flags: restartreplace
Source: ..\..\VCFBuilder2\Bin\CPPParser_vc6.dll; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\CPPParser_vc6.map; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\CPPParser_vc6.pdb; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\TextEditor_vc6.dll; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\TextEditor_vc6.map; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\TextEditor_vc6.pdb; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\VCFBuilder2_vc6.exe; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\VCFBuilder2_vc6.map; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\VCFBuilder2_vc6.pdb; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\VCFBuilderUI_vc6.dll; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\VCFBuilderUI_vc6.map; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\VCFBuilderUI_vc6.pdb; DestDir: {app}
Source: ..\..\bin\GraphicsKit_vc6.map; DestDir: {app}
Source: ..\..\bin\ApplicationKit_vc6.map; DestDir: {app}
Source: ..\..\bin\ApplicationKit_vc6.pdb; DestDir: {app}
Source: ..\..\bin\FoundationKit_vc6.dll; DestDir: {app}
Source: ..\..\bin\FoundationKit_vc6.map; DestDir: {app}
Source: ..\..\bin\FoundationKit_vc6.pdb; DestDir: {app}
Source: ..\..\bin\GraphicsKit_vc6.dll; DestDir: {app}
Source: ..\..\bin\ApplicationKit_vc6.dll; DestDir: {app}
Source: ..\..\bin\GraphicsKit_vc6.pdb; DestDir: {app}
Source: ..\..\VCFBuilder2\Bin\SciLexer.dll; DestDir: {app}

[Icons]
Name: {group}\VCF Builder 1.0.3 Alpha; Filename: {app}\VCFBuilder2_vc6.exe; IconIndex: 0
Name: {userdesktop}\VCF Builder 1.0.3 Alpha; Filename: {app}\VCFBuilder2_vc6.exe; MinVersion: 4,4; Tasks: desktopicon; IconIndex: 0
Name: {group}\Uninstall VCF Builder1.0.3.alpha; Filename: {uninstallexe}
Name: {group}\Submit a Bug !; Filename: http://sourceforge.net/tracker/?func=add&group_id=6796&atid=106796
Name: {group}\VCF's XMake Documentation; Filename: {app}\help\xmake_documentation.html; IconFilename: {app}\ApplicationKit_vc6.dll; IconIndex: 0
Name: {group}\VCF Builder Readme; Filename: {app}\readme.txt

[Run]

[_ISTool]
EnableISX=false

[Dirs]
Name: {app}\Configs; Flags: uninsalwaysuninstall
Name: {app}\ObjectRepository
Name: {app}\ProjectTemplates
Name: {app}\help
Name: {app}\ObjectRepository\C++ Applications
Name: {app}\ObjectRepository\Web Applications

[Components]
Name: Application_Core; Description: Core VCF Builder Files; Types: custom compact full
Name: Help; Description: VCF Builder Documentation; Types: custom full
Name: ObjectRepository; Description: Object Repository Files; Types: custom full

[Registry]
Root: HKCU; Subkey: Software\VCF\Builder; ValueType: string; ValueName: ConfigurationManagerDir; ValueData: Configs; Flags: createvalueifdoesntexist uninsdeletekey; Components: Application_Core
Root: HKCU; Subkey: Software\VCF\Builder; ValueType: string; ValueName: DefaultProjectDir; ValueData: My VCF Projects; Flags: createvalueifdoesntexist uninsdeletekey; Components: Application_Core
Root: HKCU; Subkey: Software\VCF\Builder; ValueType: string; ValueName: ObjectRepository; ValueData: ObjectRepository; Flags: createvalueifdoesntexist uninsdeletekey; Components: Application_Core
Root: HKCU; Subkey: Software\VCF\Builder; ValueType: string; ValueName: ProjectTemplatesDir; ValueData: ProjectTemplates; Flags: createvalueifdoesntexist uninsdeletekey; Components: Application_Core

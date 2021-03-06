//Application.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationPeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"
#include "vcf/ApplicationKit/ApplicationResourceBundle.h"

#if defined  (VCF_OSX) 
#include <Cocoa/Cocoa.h>
#include "vcf/FoundationKit/OSXPeer.h"
#endif

using namespace VCF;


Application* Application::appInstance_ = NULL;


void initLoadedLibraryApplications()
{
	//enumerate through all the loaded LibraryApplications
	Enumerator<VCF::LibraryApplication*>* libaries = LibraryApplication::getRegisteredLibraries();
	bool libraryInitializationFailed = false;
	String failedLib;
	while ( (true == libaries->hasMoreElements()) && (!libraryInitializationFailed) ) {
		VCF::LibraryApplication* libraryApp = libaries->nextElement();
		libraryInitializationFailed = !libraryApp->initRunningApplication();
		if ( libraryInitializationFailed ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("Error initializing " + libraryApp->getName() ) );
		}
	}
}

void terminateLoadedLibraryApplications()
{
	Enumerator<VCF::LibraryApplication*>* libaries = LibraryApplication::getRegisteredLibraries();
	bool libraryInitializationFailed = false;
	String failedLib;
	while ( (true == libaries->hasMoreElements()) && (!libraryInitializationFailed) ) {
		VCF::LibraryApplication* libraryApp = libaries->nextElement();
		libraryApp->terminateRunningApplication();
	}
}



Application::Application( int argc, char** argv ):
	autoLoadSaveAppState_(false),
	mainWindow_(NULL),
	singleInstance_(false)
{
	Application::appInstance_ = this;

	//initialize the ApplicationKit!!!
	ApplicationKit::init( argc, argv );

	//gets added automatically to the app list of event handlers
	WindowHandler* wh =
		new ClassProcedure1<WindowEvent*,Application>( this,&Application::onMainWindowClose, "AppWindowHandler" );

	//install a new resource bundle
	//this new resource bundle is aware of the 
	//application resource handle, which may be different if the app is the 
	//main app instance (like it is here), or if it's a library application
	System::internal_replaceResourceBundleInstance( new ApplicationResourceBundle(this) );
}

Application::~Application()
{

}

void Application::internal_terminate()
{
	if ( !applicationPeer_->shouldPerformCleanup() ) {
		applicationPeer_->terminateApp();
	}

	std::map<String,Library*>::iterator it = VPLMap_.begin();
	while ( it != VPLMap_.end() ){
		Library* lib = it->second;
		delete lib;
		lib = NULL;
		it++;
	}

	if ( !applicationPeer_->shouldPerformCleanup() ) {
		delete applicationPeer_;
	}

	Application::appInstance_ = NULL;
}

void Application::init()
{


	applicationPeer_ = UIToolkit::createApplicationPeer();

	if ( NULL == applicationPeer_ )
	{
		throw InvalidPointerException( MAKE_ERROR_MSG_2("Application peer is NULL - UIToolkit::createApplicationPeer() implementation not implemented correctly") );
	}

	applicationPeer_->setApplication( this );
/*
I am turning this off completely. There is an MS DLL called blackbox, and 
I'd like to revisit this later.
JC
#if defined( VCF_WIN ) && defined ( VCF_MSC )
	//load the BlacBox error trapper
	try {
		//at the moment this is only meaningful on Win32 platforms
		Library lib( L"BlackBox.dll" );
	}
	catch (...) {
		StringUtils::trace( "Unable to load the BlackBox error detection library\n" );
	}
#endif
	*/
}

void Application::internal_main()
{
	// this is used in order to break in the right place when an exception is thrown. - MP -
	Window* mainWindow = NULL;

	//main try...catch
	try {
		if ( NULL == Application::getRunningInstance() ){
			//throw exception
		}
		else{//enter the main loop

			Application* runningInstance = Application::getRunningInstance();
			if ( runningInstance->getName().empty() ) {
				String className = runningInstance->getClassName();
				size_t pos = className.find( "::" );
				while ( pos != String::npos ) {
					className = className.replace( pos, 2, "." );
					pos = className.find( "::" );
				}
				runningInstance->setName( className );
			}

			//init the running instance
			runningInstance->init();

			/**
			*initialize the implementer first - we are not going to rely
			*on someone remembering to call the base class functionality of the Application
			*if the Peer returns false then bomb out and terminate
			*/
			ApplicationPeer* appPeer = runningInstance->getPeer();
			if ( NULL == appPeer ){
				//throw exception - this is very BADDDDD
				throw InvalidPointerException( MAKE_ERROR_MSG_2("Application Peer is NULL") );
			}

			if ( appPeer->initApp() ){
				if ( runningInstance->initRunningApplication() ) { 
				
					mainWindow = runningInstance->mainWindow_;

					bool libsInitialized = false;
					try {
						initLoadedLibraryApplications();
						libsInitialized = true;
					}
					catch ( BasicException& e  ){
						String errString = e.getMessage().c_str();

						Dialog::showMessage( errString, "Exception Initializing Library Applications", Dialog::mbOK, Dialog::msError  );
					}
					catch ( ... ){
						String errString = "unknown error occured attempting to initialize a VCF Library Application";
						Dialog::showMessage( errString, "Exception Initializing Library Applications", Dialog::mbOK, Dialog::msError  );
					}

					if ( libsInitialized ) {
					
						runningInstance->processCommandLine( FoundationKit::getCommandLine() );

						runningInstance->run();
					}
				}
			}

			
			runningInstance->Terminating(); //notify other that we're going to terminate


			terminateLoadedLibraryApplications();

			/**
			JC - I moved the code to free the main window inside of terminateRunningApplication()
			This requires that people correctly call the application super class's terminateRunningApplication()
			inside of their overide of it.
			*/
			

			runningInstance->terminateRunningApplication();

			mainWindow = runningInstance->mainWindow_;

			if ( runningInstance->mainWindow_ != NULL ) {
				StringUtils::trace( "Oops! The Main window has not been freed.\nDid you forget to call the super class's terminateRunningApplication() method?\n" );
			}

			
			
			
			if ( appPeer->shouldPerformCleanup() ) {
				appPeer->terminateApp();
			}
			else {
				runningInstance->internal_terminate();
			
				runningInstance->free();

				ApplicationKit::terminate();			
			}			
		}
	}

	catch ( BasicException& e  ){
		String errString = e.getMessage().c_str();

		StringUtils::trace( "!!! Framework Exception: !!!\n\t" + errString + "\n" );
	
		Application::showErrorMessage( errString, "Framework Exception" );	

#ifdef _DEBUG
		throw;
#endif
	}
	catch (FoundationKit::Assertion& e){
		String errString = "Assertion Exception caught.\n\"";
		errString += e.what();
		errString += "\".\nApplication exiting abnormally.";

		StringUtils::trace( "!!! Framework Exception: !!!\n\t" + errString + "\n" );
		
		Application::showErrorMessage( errString, "Framework Assertion Exception"  );
#ifdef _DEBUG
			//rethrow the exception and let the application fail out.
		throw;
#endif			
	}
	catch (std::exception& e){
		String errString = "STL C++ exception throw.\nError : \"";
#ifdef VCF_RTTI
		String clasName = typeid(e).name();
#else
		String clasName = "Unknown - RTTI not enabled";
#endif
		errString += " (Exception of type : " + clasName + ")";
		errString += e.what();
		errString += "\".\nApplication exiting abnormally.";
		
		Application::showErrorMessage( errString, "Framework Exception"  );		

#ifdef _DEBUG
		throw;
#endif
	}
	catch (...){
		//if ( NULL != mainWindow ) {
			Application::showErrorMessage( "Unknown exception occurred. Application exiting abnormally.",
									"Framework Exception"  );
		//}
//#ifdef _DEBUG
		throw ;
//#endif
	}
}





void Application::showErrorMessage( const String& message, const String& title )
{

#if defined (VCF_WIN)
	if ( System::isUnicodeEnabled() ) {
		Control* focused = Control::getCurrentFocusedControl();
		HWND h = NULL;
		if ( NULL != focused ) {
			h = (HWND)focused->getPeer()->getHandleID();
		}
		else {
			h = ::GetFocus();
		}

		::MessageBoxW( h, message.c_str(), title.c_str(), MB_OK | MB_ICONERROR );	
		if ( focused )  {
			focused->setFocused();
		}
		
	}
	else {
		::MessageBoxA( GetActiveWindow(), message.ansi_c_str(), title.ansi_c_str(), MB_OK | MB_ICONERROR );
	}
#elif defined (VCF_OSX)	
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle:@"OK"];
	[alert setAlertStyle:NSCriticalAlertStyle];
	CFTextString tmp(title);
	[alert setMessageText:tmp];
	tmp = message;
	[alert setInformativeText:tmp];
	Application* app = Application::getRunningInstance();
	if ( app ) {
		tmp = app->getName();
		[[alert window] setTitle: (NSString*)tmp];
	}
	
	[alert runModal];
	[alert release];
	
#endif

}

bool Application::showAssertMessage( const String& message, const String& title )
{
	bool result = false;
	String msg = message;
	msg += "\nDo you want to continue with the program execution?";
#if defined (VCF_WIN)
	if ( System::isUnicodeEnabled() ) {
		Control* focused = Control::getCurrentFocusedControl();
		HWND h = NULL;
		if ( NULL != focused ) {
			h = (HWND)focused->getPeer()->getHandleID();
		}
		else {
			h = ::GetFocus();
		}		
		
		if ( IDYES == ::MessageBoxW( h, msg.c_str(), title.c_str(), MB_YESNO | MB_ICONERROR ) ) {
			result = true;
		}

		if ( focused )  {
			focused->setFocused();
		}

	}
	else {
		if ( IDYES == ::MessageBoxA( NULL, msg.ansi_c_str(), title.ansi_c_str(), MB_YESNO | MB_ICONERROR ) ) {
			result = true;
		}
	}
#elif defined  (VCF_OSX) 	
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle:@"Yes"];
	[alert addButtonWithTitle:@"No"];
	[alert setAlertStyle:NSCriticalAlertStyle];
	CFTextString tmp(title);
	[alert setMessageText:tmp];
	tmp = msg;
	[alert setInformativeText:tmp];
	Application* app = Application::getRunningInstance();
	if ( app ) {
		tmp = app->getName();
		[[alert window] setTitle: (NSString*)tmp];
	}
	
	if ([alert runModal] == NSAlertFirstButtonReturn) {
		result = true;
	}
	[alert release];
#endif

	return result;
}



int Application::main()
{
	try {
		internal_main();
	}
	catch (std::exception& e){
		String msg = String(L"Exiting main function due to uncaught exception.\nException: ") + e.what() + L"\n";
		StringUtils::trace( msg );
		System::println( msg );
		Application::showErrorMessage( msg, L"Uncaught Exception Handler" );
		ApplicationKit::terminate();
		return -1;
	}
	catch (...){
		String msg = String(L"Exiting main function due to uncaught exception. Exception type unknown.\n");
		StringUtils::trace( msg );
		System::println( msg );
		Application::showErrorMessage( msg, L"Uncaught Exception Handler" );
		ApplicationKit::terminate();
		return -1;	
	}
	return 0;
}

Application* Application::getRunningInstance()
{
	return Application::appInstance_;
}

Window* Application::getMainWindow()
{
	return mainWindow_;
}

void Application::setMainWindow( Window* mainWindow )
{
	CallBack* wl = getCallback("AppWindowHandler");
	if ( NULL != mainWindow_ && NULL != wl ){		
		mainWindow_->FrameClose.remove( wl );		
	}
	mainWindow_ = mainWindow;
	if ( NULL != mainWindow_ && NULL != wl ){
		
		addComponent( mainWindow_ );

		mainWindow_->FrameClose.add( wl );
	}
}

bool Application::initRunningApplication()
{
	return true;
}

void Application::onMainWindowClose( WindowEvent* event )
{
	Control* comp = (Control*)event->getSource();

	comp->storeSettings(true);

	removeComponent( comp );
}


void Application::terminateRunningApplication()
{	
	storeSettings(true);

	/**
	JC - I moved this code here to guarantee that the main window is
	destroyed during derinved Application class's terminateRunningApplication()
	*/
	if ( NULL != mainWindow_ ){
		removeComponent( mainWindow_ );
		mainWindow_->free();
		mainWindow_ = NULL;
	}
}

void Application::run()
{
	//run the event loop from the toolkit

	UIToolkit::runEventLoop();

	//finished with events - app can terminate

}

void Application::loadVPL( const String& vplFileName )
{
	std::map<String,Library*>::iterator found = VPLMap_.find( vplFileName );
	if ( found == VPLMap_.end() ){
		Library* vplLib = new Library();
		try{
			vplLib->load( vplFileName );
			typedef void (*InitFunc)();
			InitFunc initFunc = (InitFunc)vplLib->getFunction("initPackage");
			initFunc();

			VPLMap_[vplFileName] = vplLib;
		}
		catch ( BasicException& ex ){
			Dialog::showMessage( ex.getMessage(), "Framework Exception", Dialog::mbOK, Dialog::msError  );
		}
	}
}
void Application::setAutoLoadSaveAppState( const bool& autoLoadSaveState )
{
	autoLoadSaveAppState_ = autoLoadSaveState;
}

bool Application::displayHelpContents()
{
	return false;
}

bool Application::displayHelpIndex()
{
	return false;
}

void Application::getHelpInfo( String& helpBookName, String& helpDirectory )
{
	helpBookName = "";
	helpDirectory = "";
}

void Application::setSingleInstance( bool val )
{
	if ( singleInstance_ != val ) {
		singleInstance_ = val;
	}
}


/**
$Id$
*/

//$$Root$$Application.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "$$Root$$Application.h"
#include "$$MainWindow$$.h"

$$IF(SPLASH_SCR)
#include "$$SplashScreen$$.h"
$$ENDIF


using namespace VCF;



$$Root$$Application::$$Root$$Application( int argc, char** argv ):
	Application( argc, argv )

{
	
}

$$Root$$Application::~$$Root$$Application()
{
	
}

bool $$Root$$Application::initRunningApplication(){
	bool result = Application::initRunningApplication();
$$IF(SPLASH_SCR)
	$$SplashScreen$$* splash = new $$SplashScreen$$();
$$ENDIF
	$$MainWindow$$* mainWindow = new $$MainWindow$$();
	
	setMainWindow(mainWindow);
	mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );	
	mainWindow->setCaption( "$$Root$$" );
	mainWindow->show();

	return result;
}



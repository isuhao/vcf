//Toolbars.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"


using namespace VCF;

class ToolbarsWindow : public Window {
public:
	ToolbarsWindow() {
		setCaption( "Toolbars" );
		

		CallBack* ev = new ClassProcedure1<ButtonEvent*,ToolbarsWindow>( this, &ToolbarsWindow::onItemClicked, "ToolbarsWindow::onItemClicked" );

		Toolbar* tb = new Toolbar();
		tb->setName( "Toolbar1" );
		tb->setHeight( 25 );
		add( tb, AlignTop );

		ImageList* il = new ImageList();
		il->setImageHeight( 16 );
		il->setImageWidth( 16 );
		il->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
		addComponent( il );

		tb->setImageList( il );

		GraphicsResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();
		Image* img = resBundle->getImage( "bmp1" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "bmp2" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "bmp3" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "bmp4" );
		il->addImage( img );
		delete img;


		ToolbarItem* item = tb->addToolBarButton( "tbn1" );
		item->setTooltip( "Toolbar Item 1" );


		item = tb->addToolBarButton( "" );
		item->setAsSeparator();

		item = tb->addToolBarButton( "tbn2" );
		item->setImageIndex(1);
		item->setWidth( 200 );
		item->setTooltip( "Toolbar Item 2" );

		item = tb->addToolBarButton( "tbn3" );
		item->setEnabled( false );

		ComboBoxControl* cb = new ComboBoxControl();
		//TextControl* tc = new TextControl();
		cb->setWidth( 175 );
		cb->addItem( "Item 1" );
		cb->addItem( "Item 2" );
		cb->addItem( "Item 3" );
		cb->addItem( "Item 4" );

		item->setItemControl( cb );




		item = tb->addToolBarButton( "Click Me!" );
		item->setTooltip( "Toolbar Item 4" );
		item->setTag( 3 );
		item->setImageIndex(2);


		//item = tb->addToolBarButton( "" );
		//item->setAsSeparator();

		item = tb->addToolBarButton( "Horz Captions" );
		item->setTooltip( "Toolbar Item 5 - Click to toggle horizontal captions" );
		item->ItemClicked += ev;
		item->setImageIndex(3);

		item->setChecked(true);


		item->setTag( 2 );

		item = tb->addToolBarButton( "Captions" );
		item->setTooltip( "Toolbar Item 6 - Click to toggle visible captions" );

		item->ItemClicked += ev;

		item->setChecked(true);


		item->ItemUpdate +=
			new ClassProcedure1<Event*,ToolbarsWindow>( this, &ToolbarsWindow::onItemUpdate, "ToolbarsWindow::onItemUpdate" );

		item->setTag( 1 );
		tb->setShowButtonCaptions( false );



		Panel* p = new Panel();
		add( p, AlignClient );





		tb->setButtonCaptionsHorizontal( false );

		showButtonCaptions = false;
		capsHorz = false;

	}

	virtual ~ToolbarsWindow(){};

	bool showButtonCaptions;
	bool capsHorz;

	void onItemUpdate( Event* e ) {
		ToolbarItem* item = (ToolbarItem*)e->getSource();

	}

	void onItemClicked( ButtonEvent* e ) {
		ToolbarItem* item = (ToolbarItem*)e->getSource();

		Toolbar* tb = (Toolbar*)findComponent( "Toolbar1" );

		switch( item->getTag() ) {
			case 1 : {
				showButtonCaptions = !showButtonCaptions;

				tb->setShowButtonCaptions( showButtonCaptions );
			}
			break;

			case 2 : {
				capsHorz = !capsHorz;

				tb->setButtonCaptionsHorizontal( capsHorz );
			}
			break;

			case 3 : {
				Size sz(100,100);
				tb->setButtonSize( sz );
			}
			break;


		}

	}
};




class ToolbarsApplication : public Application {
public:

	ToolbarsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new ToolbarsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 800.0, 500.0 ) );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ToolbarsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
$Id$
*/

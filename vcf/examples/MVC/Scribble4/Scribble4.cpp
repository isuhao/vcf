//Scribble1.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/GraphicsKit/Ellipse.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/StatusBar.h"
#include "vcf/ApplicationKit/ListViewControl.h"

#include "ScribbleModel.h"
#include "ScribbleView.h"
#include "ScribbleController.h"


using namespace VCF;

class AboutDialog : public Dialog {
public:
	Label* program;
	Label* author;
	Label* company;
	Label* copyright;
	AboutDialog(){}

	virtual ~AboutDialog()
	{

	}
};



class Scribble4Window : public Window {
public:
	Scribble4Window() {
		
	}
	virtual ~Scribble4Window(){};

	Panel* contentPanel;
	ScribbleModel* scribble;	
	StatusBar* status;	
	ListViewControl* scribbleListing;
};




class Scribble4App : public Application {
public:

	Scribble4App( int argc, char** argv );

	virtual bool initRunningApplication(){
		contentMouseDown = false;

		bool result = Application::initRunningApplication();
		
		ScribbleController* controller = new ScribbleController();
		controller->setName( "controller" );
		addComponent(controller);


		Scribble4Window* mainWindow = (Scribble4Window*) Frame::createWindow( classid(Scribble4Window) );
		setMainWindow(mainWindow);
		
		ScribbleView* view = new ScribbleView();
		mainWindow->contentPanel->setView( view );
		mainWindow->scribble->addView( view );
		
		
		controller->setControl( mainWindow->contentPanel );
		controller->setModel( mainWindow->scribble );

		Rect r = mainWindow->scribble->getMaxBounds();
		mainWindow->status->setStatusPaneText( 1, Format("Dimensions: %0.1f x %0.1f") % r.getWidth() % r.getHeight() );

		mainWindow->show();
		
		return result;
	}

	void onAbout(Event*) {		
		AboutDialog* aboutDlg = (AboutDialog*)Frame::createDialog( classid(AboutDialog) );
		ProgramInfo* info = this->getResourceBundle()->getProgramInfo();
		if ( NULL != info ) {
			aboutDlg->program->setCaption( info->getProgramName() );
			aboutDlg->author->setCaption( info->getAuthor() );
			aboutDlg->company->setCaption( info->getCompany() );
			aboutDlg->copyright->setCaption( info->getCopyright() );
			delete info;
		}
		aboutDlg->showModal();
		delete aboutDlg;		
	}

	void onContentMouseMove( MouseEvent* e ) {
		Scribble4Window* mainWindow = (Scribble4Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseDown( MouseEvent* e ) {
		contentMouseDown = true;
		Scribble4Window* mainWindow = (Scribble4Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseUp( MouseEvent* e ) {
		contentMouseDown = false;
	}

	

	void onListSelectionChanged( Event* e ) {
		ItemEvent* ie = (ItemEvent*)e;
		Scribble4Window* mainWindow = (Scribble4Window*)getMainWindow();
		mainWindow->scribble->setActiveShape( mainWindow->scribble->getShape(ie->index) );
	}

	void onViewListing( Event* e ) {
		Scribble4Window* mainWindow = (Scribble4Window*)getMainWindow();
		mainWindow->scribbleListing->setVisible( !mainWindow->scribbleListing->getVisible() );
		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( mainWindow->scribbleListing->getVisible() );
	}

	void onViewStatusbar( Event* e ) {
		Scribble4Window* mainWindow = (Scribble4Window*)getMainWindow();
		mainWindow->status->setVisible( !mainWindow->status->getVisible() );
		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( mainWindow->status->getVisible() );
	}

	void onScribbleModelChanged( Event* e ) {
		if ( e->getType() == ScribbleModel::ActiveShapeChanged && contentMouseDown ) {
			ScribbleModel* model = (ScribbleModel*)e->getSource();
			Scribble4Window* mainWindow = (Scribble4Window*)getMainWindow();
			if ( NULL != model->getActiveShape() ) {
				VariantData v = (ScribbleShape*) model->getActiveShape();
				mainWindow->scribbleListing->selectItem( model->getIndexOf( v ) );
			}
			else {
				mainWindow->scribbleListing->selectItem( ListModel::InvalidIndex );
			}
		}
	}

	bool contentMouseDown;
};











_class_rtti_(ScribbleController, "VCF::Component", "ScribbleController")
_class_rtti_end_

_class_rtti_(Scribble4Window, "VCF::Window", "Scribble4Window")
_field_obj_( Panel*, contentPanel )
_field_obj_( ScribbleModel*, scribble )
_field_obj_( StatusBar*, status )
_field_obj_( ListViewControl*, scribbleListing )

_class_rtti_end_

_class_rtti_(AboutDialog, "VCF::Dialog", "AboutDialog")
_field_obj_( Label*, program )
_field_obj_( Label*, copyright )
_field_obj_( Label*, author )
_field_obj_( Label*, company )
_class_rtti_end_


_class_rtti_(ScribbleShape, "VCF::Object", "ScribbleShape")
_property_object_( Color, "fill", getFill, setFill, "" );
_property_object_( Color, "stroke", getStroke, setStroke, "" );
_property_( double, "strokeWidth", getStrokeWidth, setStrokeWidth, "" );
_property_( bool, "filled", getFilled, setFilled, "" );
_property_( String, "data", getData, setData, "" );
_property_( double, "rotation", getRotation, setRotation, "" );
_property_( double, "transX", getTranslateX, setTranslateX, "" );
_property_( double, "transY", getTranslateY, setTranslateY, "" );
_property_( double, "scaleX", getScaleX, setScaleX, "" );
_property_( double, "scaleY", getScaleY, setScaleY, "" );
_property_( double, "shearX", getShearX, setShearX, "" );
_property_( double, "shearY", getShearY, setShearY, "" );
_class_rtti_end_

_class_rtti_(ScribbleModel, "VCF::SimpleListModel", "ScribbleModel")
_property_array_( VariantData, "shapes", get,set,insert,remove,getCount, "" )
_property_object_( Color, "backColor", getBackColor, setBackColor, "" );
_property_object_( Color, "defaultFill", getDefaultFillColor, setDefaultFillColor, "" );
_property_object_( Color, "defaultStroke", getDefaultStrokeColor, setDefaultStrokeColor, "" );
_property_( double, "defaultStrokeWidth", getDefaultWidth, setDefaultWidth, "" );
_property_( bool, "defaultFilled", getDefaultFilled, setDefaultFilled, "" );
_class_rtti_end_

Scribble4App::Scribble4App( int argc, char** argv ) : 
	Application(argc, argv)
{
	REGISTER_CLASSINFO_EXTERNAL(Scribble4Window);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleShape);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleModel);
	REGISTER_CLASSINFO_EXTERNAL(AboutDialog);
	
	
	addCallback( new ClassProcedure1<Event*,Scribble4App>(this, &Scribble4App::onAbout), "Scribble4App::onAbout" );
	addCallback( new ClassProcedure1<Event*,Scribble4App>(this, &Scribble4App::onListSelectionChanged), "Scribble4App::onListSelectionChanged" );
	addCallback( new ClassProcedure1<Event*,Scribble4App>(this, &Scribble4App::onViewListing), "Scribble4App::onViewListing" );
	addCallback( new ClassProcedure1<Event*,Scribble4App>(this, &Scribble4App::onViewStatusbar), "Scribble4App::onViewStatusbar" );
	
	addCallback( new ClassProcedure1<Event*,Scribble4App>(this, &Scribble4App::onScribbleModelChanged), "Scribble4App::onScribbleModelChanged" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble4App>(this, &Scribble4App::onContentMouseMove), "Scribble4App::onContentMouseMove" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble4App>(this, &Scribble4App::onContentMouseDown), "Scribble4App::onContentMouseDown" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble4App>(this, &Scribble4App::onContentMouseUp), "Scribble4App::onContentMouseUp" );
	
	
}


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble4App>(argc,argv);
}




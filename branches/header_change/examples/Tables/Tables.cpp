//Tables.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"


using namespace VCF;



class TablesWindow : public Window {
public:
	TablesWindow() {
		setCaption( "Tables" );
		

		TableControl* table = new TableControl();

		add( table, AlignClient );

		TableModel* model = table->getTableModel();

		model->empty();

		table->setDefaultTableCellFont( &Font("Tahoma") );

		model->addColumns( 12 );
		model->addRows(300);
		model->setFixedRowsCount( 1 );
		model->setFixedColumnsCount( 1 );		

		for (int y=0;y<model->getRowCount();y++ ){
			for ( int x=0;x<model->getColumnCount();x++ ) {
				model->getItem( y, x )->setCaption( Format( "Cell [%d,%d]" ) % y % x );
				if ( y == 10 && x == 5 ) {
					Font font = model->getItem( y, x )->getFont();
					font.setName( "Times New Roman" );
					font.setPointSize( 12.6 );
					font.setBold( true );
					model->getItem( y, x )->setFont( &font );
					model->getItem( y, x )->setColor( Color::getColor("yellow") );
				}
			}
		}



		/*******************************************
		---------------------------------------------
		|	Hey there!!!! Yes you! The following line 
		|	turns *OFF* row selection!! :)		
		---------------------------------------------
		********************************************/
		table->setAllowFixedRowSelection( false );

	}

	virtual ~TablesWindow(){};

};




class TablesApplication : public Application {
public:

	TablesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new TablesWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();

		return result;
	}

};



int main(int argc, char *argv[])
{
	Application* app = new TablesApplication( argc, argv );

	Application::main();


	return 0;
}


/**
$Id$
*/

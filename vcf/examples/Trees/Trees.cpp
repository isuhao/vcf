//Trees.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TreeControl.h"
#include "vcf/ApplicationKit/ColumnModel.h"
#include "vcf/ApplicationKit/TreePeer.h"
#include "vcf/ApplicationKit/TreeListControl.h"


using namespace VCF;






class HiResClock {
public:

	HiResClock(){
		QueryPerformanceFrequency( (LARGE_INTEGER*)&frequency_ );
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}



	void start() {		
		QueryPerformanceCounter( (LARGE_INTEGER*)&performanceCounter1_ );
	}

	void stop() {
		QueryPerformanceCounter( (LARGE_INTEGER*)&performanceCounter2_ );
	}

	void clear() {
		//QueryPerformanceFrequency( &frequency_ );
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}

	operator double() const {
		return duration();
	}

	double duration() const {
		return ((double)(performanceCounter2_ - performanceCounter1_))/((double)frequency_);
	}
protected:
	__int64 frequency_;
	__int64 performanceCounter1_;
	__int64 performanceCounter2_;
private:
	HiResClock( const HiResClock& rhs );


	HiResClock& operator=( const HiResClock& rhs );
};



#define TREESWINDOW_CLASSID		"6d549178-fc6d-4942-9828-6e7314d8be4f"


class TreesWindow : public Window {
public:
};

_class_rtti_(TreesWindow, "VCF::Window", TREESWINDOW_CLASSID)
_class_rtti_end_



class MyTreeItem : public TreeItem {
public:
	virtual bool canPaint() const {
		return true;
	}

	virtual void paint( GraphicsContext* context, Rect* paintRect ) {
		
		Rect r = *paintRect;

		context->setColor( Color::getColor("blue") );
		r.inflate( -2, -2 );
		context->rectangle( r );

		context->strokePath();
	}
};


class TreesApplication : public Application {
public:

	TreesApplication( int argc, char** argv ) : Application(argc, argv) {

	}


	void onPopup( Event* e ) {
		TreeControl* treeCtrl = (TreeControl*)this->getMainWindow()->findComponent( "treeCtrl", true );

		ControlPopupMenuMenuEvent* cpe = (ControlPopupMenuMenuEvent*)e;
		TreeModel::Key k = treeCtrl->hitTest( cpe->popupPt );
		String s = treeCtrl->getTreeModel()->getAsString(k);

		Rect r = treeCtrl->getItemRect(k);

		TreeItem* item = treeCtrl->getItemFromKey( k );
		item->setSelected( true );
		
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		

		REGISTER_CLASSINFO_EXTERNAL(TreesWindow);

		Window* mainWindow = Frame::createWindow( classid(TreesWindow) );


		TreeControl* treeCtrl = (TreeControl*)mainWindow->findComponent( "treeCtrl", true );

		treeCtrl->BeforePopupMenu +=
			new ClassProcedure1<Event*,TreesApplication>(this,&TreesApplication::onPopup,"TreesApplication::onPopup");

		TreeModel* tm = treeCtrl->getTreeModel();
		TreeModel::Key k1 = tm->insert( "testA" );
		TreeModel::Key k2 = tm->insert( "testB" );
		TreeModel::Key k3 = tm->insert( "testC" );
		TreeModel::Key k4 = tm->insert( "testD" );
		
		tm->insert( "test1 (p = testA)", k1 );

		HiResClock clock;
		clock.start();
		int i=0;

		TreeModel::Key removeThisKey;

		for (i=0;i<10;i++ ) {
			TreeModel::Key k = tm->insert( "test (p = testB)", k2 );

			for (int j=0;j<100;j++ ) {
				tm->insert( String("test (p = testB/") + k + ") " + j, k );

				if ( i == 6 && j == 5 ) {
					TreeItem* item = treeCtrl->getItemFromKey( k );
					item->expand(true);
				}
			}

			if ( i == 8 ) {
				removeThisKey = k;
				tm->set( k, "Yank this item!" );
			}
		}
		
		for (i=0;i<1000;i++ ) {
			tm->insert( "test (p = testD)", k4 );
		}

		clock.stop();
		double popTime = clock.duration();

		size_t sz = treeCtrl->sizeOf();

		StringUtils::trace( Format("tree mod size %u\n") % sz );


		clock.start();
		TreeItem* item = treeCtrl->getItemFromKey( k3 );
		item->getFont()->setColor( Color::getColor("red") );
		item->getFont()->setBold( true );
		item->getFont()->setName( "Times New Roman" );


		TreeItem* item2 = treeCtrl->insertItem( item, "Hello Dolly!" );
		item2->setImageIndex( 1 );

		MyTreeItem* myItem = new MyTreeItem();
		treeCtrl->insertItem( item, myItem );
		myItem->setCaption( "My Item!" );
		clock.stop();

		double uimods = clock.duration();


		myItem->getParent()->expand( true );


		myItem->setSelected(true);

		sz = treeCtrl->sizeOf();


		TreeItem* item3 = treeCtrl->insertItem( item, "Wolla-Gobbgers!" );
		treeCtrl->removeItem( item3 );
		item3->free();



		tm->remove( removeThisKey );

		//myItem->setParent( item );


		setMainWindow(mainWindow);
		mainWindow->show();
		
		clock.stop();		

		//Dialog::showMessage( Format("treeCtrl size %u bytes, tree mod count: %u\r\npopulation time: %.03f seconds\r\ntime for adding 2 item and retrieval: %.08f seconds\r\nshow form: %.08f seconds") % sz % tm->getCount() % popTime % uimods % clock.duration() );


		TreeListControl* treeCtrl2 = (TreeListControl*)mainWindow->findComponent( "treeCtrl2", true );
		treeCtrl2->showFullRowSelection(true);



		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TreesApplication( argc, argv );

	Application::main();
	
	return 0;
}



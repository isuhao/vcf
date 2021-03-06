//RegExGUI.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/RegExKit/RegExKit.h"
#include "vcf/ApplicationKit/MessageDialog.h"

using namespace VCF;



class RegExGUIWindow : public Window {
public:
	RegExGUIWindow() {
		setCaption( "RegExGUI" );		
	}

	virtual ~RegExGUIWindow(){};

};

_class_rtti_(RegExGUIWindow, "VCF::Window", "RegExGUIWindow")
_class_rtti_end_




class RegExGUIApplication : public Application {
public:
	


	RegExGUIApplication( int argc, char** argv ) : Application(argc, argv),
		host("", ""), lastExpression("") {

		addCallback( new ClassProcedure1<Event*,RegExGUIApplication>
			(this, &RegExGUIApplication::findNext), "RegExGUIApplication::findNext" );

		addCallback( new ClassProcedure1<Event*,RegExGUIApplication>
			(this, &RegExGUIApplication::findPrev), "RegExGUIApplication::findPrev" );

		addCallback( new ClassProcedure1<KeyboardEvent*,RegExGUIApplication>
			(this, &RegExGUIApplication::onKeyDown), "RegExGUIApplication::onKeyDown" );

		addCallback( new ClassProcedure1<Event*,RegExGUIApplication>
			(this, &RegExGUIApplication::reset), "RegExGUIApplication::reset" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(RegExGUIWindow);

		Window* mainWindow = Frame::createWindow( classid(RegExGUIWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();

		data = reinterpret_cast<MultilineTextControl*>
			(findComponent("data", true));

		edt1 = reinterpret_cast<TextControl*>(findComponent("edt1", true));

		nextBtn = reinterpret_cast<CommandButton*>(findComponent("nextbtn", true));
		prevBtn = reinterpret_cast<CommandButton*>(findComponent("prevbtn", true));

		supplyText();

		return result;
	}

	void supplyText() {
		ResourceBundle* bundle = System::getResourceBundle();
		Resource* res = bundle->getResource("Search.txt");
		searchStr = String((char*)(res->getData()), res->getDataSize());
		data->setText(searchStr);
		host.setRangeAsString(searchStr); 
	}

	void findNext(Event* e) {
		String text = edt1->getText();
		if (text == lastExpression) {
			if (it != host.end()) {
				++it;
			}
		} 
		else {
			try { 
				host.changeSearchExpression(text);
				lastExpression = text;
				it = host.begin();
			}
			catch ( BasicException& e ) {
				Dialog::showMessage( e.getMessage() );
				it = host.end();
				return;
			}
		}
		if (it != host.end()) {
			showMatch(it);
		} else {
			--it;
			endSearch();
		}
	}

	void findPrev(Event* e) {
		String text = edt1->getText();
		if (text == lastExpression) {
			if (it != host.begin()) {
				--it;
			} else {
				endSearch(true);
				return;
			}
		} else {
			host.changeSearchExpression(text);
			lastExpression = text;
			it = --host.end();
		}
		if (it != host.end()) {
			showMatch(it);
		} else {
			endSearch(true);
		}
	}

	void onKeyDown(KeyboardEvent* e) {
		VCFChar pressed = e->keyValue;
		if (pressed == '\r') {
			findNext(e);
		}
	}

	void reset(Event* e) {		
		edt1->setText("");
		edt1->repaint();
		lastExpression = "";
		host.changeSearchExpression("");
		data->setSelectionMark(0,0);
		
		nextBtn->setEnabled(true);		
		prevBtn->setEnabled(true);
	}

	void showMatch(const Regex::Iterator& it) {
		data->setSelectionMark(it->getPosAsCount(), it->getText().length());

		nextBtn->setEnabled(true);		
		prevBtn->setEnabled(true);
	}

	void endSearch(bool backwards=false) {
		MessageDialog end;
		end.setMessage("End of text");
		end.setInformation("There are no more matches for this expression");
		end.addActionButton("OK", UIToolkit::mrOK, true);
		end.showModal();
		CommandButton* btn;
		if (!backwards) {
			btn = nextBtn;
		} else {
			btn = prevBtn;
		}
		btn->setEnabled(false);
	}

private:
	Regex::UTF_16LE host;
	Regex::Iterator it;
	String searchStr;
	String lastExpression;
	MultilineTextControl* data;
	TextControl* edt1;
	CommandButton* nextBtn;
	CommandButton* prevBtn;
};


int main(int argc, char *argv[])
{
	Application* app = new RegExGUIApplication( argc, argv );

	Application::main();
	
	return 0;
}



//TextControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/DefaultTextModel.h"
#include "vcf/ApplicationKit/TextPeer.h"

using namespace VCF;

TextControl::TextControl( const bool& multiLineControl ):
	model_(NULL),
	readOnly_(false)
{
	textPeer_ =	UIToolkit::createTextPeer( this, multiLineControl );
	
	if ( NULL == textPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	};


	peer_ = dynamic_cast<ControlPeer*>(textPeer_ );



	setColor(  GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );

	
	peer_->create( this );

	setTextModel( new DefaultTextModel() );


	//if we are a single line control then add a
	//handler for getting the focus so we can
	//select all the text whenever we get the focus
	if ( false == multiLineControl ) {
		FocusGained.addHandler( new FocusEventHandler<TextControl>( this,
																&TextControl::onFocusGained,
																"TextControl::onFocusGained" ) );
	}

	init();
}

TextControl::~TextControl()
{
	if ( NULL != model_ ){
		//model_->release();
		model_ = NULL;
	}
}

void TextControl::init()
{
	setVisible( true );
	setFocused();
	setEnabled( true );
	keepTabbingCharacters_ = false;
	keepReturnCharacter_ = false;
	setCursorID( Cursor::SCT_TEXT );

	setBorder( new Basic3DBorder(true) );
}

void TextControl::paint( GraphicsContext * context )
{
	Border* border = getBorder();

	Rect innerBounds = getClientBounds( false );
	
	context->setColor( getColor() );

	context->rectangle( &innerBounds );

	context->fillPath();
}

void TextControl::setTextModel( TextModel * model )
{
	model_ = model;
	
	setViewModel( dynamic_cast<Model*>(model_) );
}

TextModel* TextControl::getTextModel()
{
	return model_;
}

unsigned long TextControl::getCaretPosition()
{
	unsigned long result = 0;
	result = textPeer_->getCaretPosition();
	return result;

}

void TextControl::setCaretPosition( const unsigned long& caretPos )
{
	
	textPeer_->setCaretPosition( caretPos );
}

void TextControl::setRightMargin( const double & rightMargin )
{
	textPeer_->setRightMargin( rightMargin );
}

void TextControl::setLeftMargin( const double & leftMargin )
{
	textPeer_->setLeftMargin( leftMargin );
}

unsigned long TextControl::getLineCount()
{
	return textPeer_->getLineCount();
}

unsigned long TextControl::getCurrentLinePosition()
{
	return textPeer_->getCurrentLinePosition();
}

double TextControl::getLeftMargin()
{
	return textPeer_->getLeftMargin();
}

double TextControl::getRightMargin()
{
	return textPeer_->getRightMargin();
}

Point* TextControl::getPositionFromCharIndex( const unsigned long& index )
{
	return textPeer_->getPositionFromCharIndex( index );
}

unsigned long TextControl::getCharIndexFromPosition( Point* point )
{
	return textPeer_->getCharIndexFromPosition( point );
}

unsigned long TextControl::getSelectionStart()
{
	return textPeer_->getSelectionStart();
}

unsigned long TextControl::getSelectionCount()
{
	return textPeer_->getSelectionCount();
}

void TextControl::setSelectionMark( const unsigned long& start, const unsigned long& count )
{
	textPeer_->setSelectionMark( start, count );
}

void TextControl::setSelectionFont( Font* font )
{
	textPeer_->setSelectionFont( font );
}

void TextControl::setParagraphAlignment( const TextAlignmentType& alignment )
{
	textPeer_->setParagraphAlignment( alignment );
}

String TextControl::getSelectedText()
{
	String result;

	unsigned long selectionCount = getSelectionCount();

	if ( selectionCount > 0 ) {
		result = model_->getText();
		result = result.substr( getSelectionStart(), selectionCount );
	}

	return result;
}

void TextControl::replaceText( const String& text )
{
	unsigned long selectionStart = getSelectionStart();
	unsigned long selectionCount = getSelectionCount();

	model_->replaceText( selectionStart, selectionCount, text );
}

void TextControl::onFocusGained( FocusEvent* event )
{
	if ( NULL != model_ ) {
		String text = model_->getText();

		setSelectionMark( 0, text.size() );
	}
}

double TextControl::getPreferredHeight()
{
	double result = Control::getPreferredHeight();

	if ( NULL != getFont() ) {
		result = getFont()->getPixelSize() * 1.85;
	}

	return result;
}

void TextControl::handleEvent( Event* event )
{
	switch( event->getType() ) {

		case Control::KEYBOARD_DOWN : {
			/**
			HACK ALERT!
			this is the braindead way - needs to be reworked in the future

			for the future we need to be able to insertText and deleteText from the
			model according to the characters pressed. At first glance this is that
			big of a deal: determine if we have a selection, delete the selected
			text, and then insert the appropriate character. The problem comes in
			determing what causes a delete and what to insert. Normally the only things
			that should cause an delete/insert are the set of characters [a..z,A..Z,0..9],
			back space, space, and delete. This is a valid assumption assuming en/US language
			but for other languages this totally falls down...
			#-------------------------------------------------------------------------------#
			#UN-HACK ALERT!																	#
			#-------------------------------------------------------------------------------#
			JC - I have currently implemented this so that we now add text key press at 
			a time,	or delete text if appropriate.
			*/

			TextModel* model = getTextModel();

			if ( !getReadOnly() ) {
				if ( !(getComponentState() & Component::csDesigning) ) {
					KeyboardEvent* ke = (KeyboardEvent*)event;

					switch ( ke->getVirtualCode() ) {
						case vkDelete : {
							ulong32 pos =  textPeer_->getSelectionStart();

							//Thanks to Marcello to fixing this!!!
							ulong32 size = model->getSize();
							if ( pos <= (size-1) ) {
								ulong32 length = maxVal<ulong32>( 1, textPeer_->getSelectionCount() );							

								// workaround for a '\r\n' sequence: we need to
								// delete '\n' too at the end of the selection
								ulong32 pos2 = pos+length-1;
								if ( pos2 < (size-1)  ) {
									String text = model->getText();
									const VCFChar* textBuffer = text.c_str();
									
									if ( textBuffer[pos2] == '\r' ) {
										if ( textBuffer[pos2+1] == '\n' ) {
											length += 1;
										}
									}
								}

								//Debug diagnostics - JC
								//String text = model->getText();
								//StringUtils::traceWithArgs( "vkDelete [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n", 
								//		text.c_str(), text[pos], text[pos], pos );

								model->deleteText( pos, length );

								//text = model->getText();
								//StringUtils::traceWithArgs( "after vkDelete [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n", 
								//		text.c_str(), text[pos], text[pos], pos );
							}

						}
						break;

						case vkBackSpace : {
							ulong32 pos =  minVal<ulong32>( model->getSize(), textPeer_->getSelectionStart() );
							
							if ( pos > 0 ) {
								pos -= 1;
							}

							
							ulong32 length = maxVal<ulong32>( 1, textPeer_->getSelectionCount() );

							// workaround for a '\r\n' sequence: we need to
							// delete '\r' too at the beginning of the selection
							if ( pos > 0 ) {
								String text = model->getText();
								const VCFChar* textBuffer = text.c_str();
								
								if ( textBuffer[pos] == '\n' ) {
									if ( textBuffer[pos-1] == '\r' ) {
										pos -= 1;
										length += 1;
									}
								}
							}
							
							//Debug diagnostics - JC
							//String text = model->getText();								
							//StringUtils::traceWithArgs( "vkBackSpace [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n", 
							//		text.c_str(), text[pos], text[pos], pos );

							
							model->deleteText( pos, length );
							

							//text = model->getText();
							//StringUtils::traceWithArgs( "after vkBackSpace [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n", 
							//		text.c_str(), text[pos-length], text[pos-length], pos-length );
							
						
						}
						break;

						case vkLeftArrow : 
						case vkRightArrow : 
						case vkPgUp : 
						case vkPgDown : 
						case vkHome : 
						case vkEnd : 
						case vkInsert : 
						case vkAlt : 
						case vkCtrl : 
						case vkEscape : 
						case vkPrintScreen : 
						case vkScrollLock :
						case vkPause : 
						case vkCapsLock : 
						case vkShift : 
						case vkF1 : 							
						case vkF2 : 
						case vkF3 : 
						case vkF4 : 
						case vkF5 : 
						case vkF6 : 
						case vkF7 : 
						case vkF8 : 
						case vkF9 : 
						case vkF10 : 
						case vkF11 : 
						case vkF12 : 
						case vkDownArrow :
						case vkUpArrow : {
							//no-op for these, since we don't want to add/delete text for them
						}
						break;

						/**
						JC - added this to account for tab entry - 
						sometimes you'd end up with a tab character entered when all you 
						wanted was to tab to the next control
						*/
						case vkTab : {
							if ( keepsTabKey() ) {
								//process the tab
								
								if ( !ke->hasShiftKey() && !ke->hasAltKey() && !ke->hasControlKey() ) {
									// we add the 'tab' text in place of the selection

									ulong32 pos =  textPeer_->getCaretPosition();
									String text;
									text += ke->getKeyValue();
									
									//determine if we have selected text. If we 
									//have, then delete the selection and *then*
									//add in the new character(s)
									
									ulong32 length = textPeer_->getSelectionCount();
									if ( length > 0 ) {
										model->deleteText( pos, length );
									}
									
									
									model->insertText( pos, text );
								}
							}
						}
						break;


						/**
						JC - added this to account for tab entry - 
						sometimes you'd end up with a tab character entered when all you 
						wanted was to tab to the next control
						*/
						case vkTab : {
							if ( keepsTabKey() ) {
								//process the tab
								
								if ( !ke->hasShiftKey() && !ke->hasAltKey() && !ke->hasControlKey() ) {
									ulong32 pos =  textPeer_->getCaretPosition();
									String text;
									text += ke->getKeyValue();
									
									//determnine if we have sleected text. If we 
									//have, then delete the selection ant *then*
									//add in the new character(s)
									
									ulong32 length = textPeer_->getSelectionCount();
									if ( length > 0 ) {
										model->deleteText( pos, length );
									}
									
									
									model->insertText( pos, text );
								}
							}
						}
						break;


						case vkEnter : {
							if ( !ke->hasAltKey() && !ke->hasControlKey() ) {
								if ( supportsMultiLinedText() ) {
									ulong32 pos =  textPeer_->getCaretPosition();
									String text = "\n";
									
									ulong32 length = textPeer_->getSelectionCount();
									if ( length > 0 ) {
										model->deleteText( pos, length );
									}

									//StringUtils::traceWithArgs( "adding [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n", 
									//	text.c_str(), text[0], text[0], pos );
									
									model->insertText( pos, text );
								}
							}
						}
						break;

						default : {

							if ( !ke->hasAltKey() && !ke->hasControlKey() ) {
								ulong32 pos =  textPeer_->getCaretPosition();
								String text;
								text += ke->getKeyValue();

								//StringUtils::traceWithArgs( "adding [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n", 
								//	text.c_str(), text[0], text[0], pos );

								//determnine if we have sleected text. If we 
								//have, then delete the selection ant *then*
								//add in the new character(s)

								ulong32 length = textPeer_->getSelectionCount();
								if ( length > 0 ) {
									model->deleteText( pos, length );
								}

								
								model->insertText( pos, text );
							}

						}
						break;
					}
				}
			}

			Control::handleEvent( event );
		}
		break;

		case Control::KEYBOARD_UP : {
			Control::handleEvent( event );
		}
		break;

		case Control::KEYBOARD_PRESSED : {
			Control::handleEvent( event );
		}
		break;

		default : {
			Control::handleEvent( event );
		}
		break;
	}
}


void TextControl::setReadOnly( const bool& val )
{
	readOnly_ = val;
	textPeer_->setReadOnly( readOnly_ );
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2005/01/18 00:21:44  ddiego
*merged in changes from dev for aromans text edit bug
*
<<<<<<< TextControl.cpp
*Revision 1.5  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.4  2004/12/16 04:10:43  ddiego
*fixes for bug 1081652, the actual fix came from Marcello.
*
*Revision 1.3.2.2  2004/12/21 00:25:37  marcelloptr
*comments
*
*Revision 1.3.2.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.4  2004/12/16 04:10:43  ddiego
*fixes for bug 1081652, the actual fix came from Marcello.
*
=======
*Revision 1.3.2.3  2005/01/18 00:15:33  ddiego
*fixed aromans text edit bug
*
*Revision 1.3.2.2  2004/12/21 00:25:37  marcelloptr
*comments
*
*Revision 1.3.2.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.4  2004/12/16 04:10:43  ddiego
*fixes for bug 1081652, the actual fix came from Marcello.
*
>>>>>>> 1.3.2.3
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.7  2004/11/15 05:41:28  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.2.2.6  2004/10/26 02:38:18  ddiego
*fixed a bug in the handling of a backspace char event
*
*Revision 1.2.2.5  2004/10/04 23:47:28  ddiego
*fixed text control char entry bug.
*
*Revision 1.2.2.4  2004/10/03 23:02:29  ddiego
*fixed a text model bug that incorectly handled deleting chars.
*
*Revision 1.2.2.3  2004/10/03 22:47:33  ddiego
*fixed a text model bug that incorectly handled deleting chars.
*
*Revision 1.2.2.2  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.1  2004/09/06 21:30:20  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/15 04:27:14  ddiego
*more updates for edit nc client painting
*
*Revision 1.1.2.3  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.26  2004/04/03 15:48:45  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.24.2.5  2004/03/21 19:44:58  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.24.2.3  2004/03/17 03:22:28  ddiego
*fixed a glitch in setting focus
*
*Revision 1.24.2.2  2004/01/19 23:32:06  ddiego
**** empty log message ***
*
*Revision 1.24.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.24  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.23.2.3  2003/09/09 04:22:41  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.23.2.2  2003/08/17 18:17:53  ddiego
*added some of Marcellos fixes, notably the one to fix CRLF problems in teh
*edit control
*
*Revision 1.23.2.1  2003/08/14 20:30:30  marcelloptr
*bug [788927] TextControl::getSelectedText() return all text if no text selected
*
*Revision 1.23  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.22.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.22.2.1  2003/05/27 04:45:40  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.22  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.21.2.2  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.21.2.1  2003/03/12 03:13:23  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.21  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.20.2.5  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.20.2.4  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.20.2.3  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20.2.2  2002/12/27 23:05:09  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20.2.1  2002/12/25 22:06:36  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.20  2002/11/18 00:46:10  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.19.8.2  2002/11/16 20:31:35  ddiego
*this fixes the following bugs:
*632802 TextControl's setViewModel not called
*639416 ListViewControl's setViewModel not called
*639417 TreeControl's setViewModel not called
*639418 ListBoxControl's setViewModel not called
*639419 ComboBoxControl's setViewModel not called
*639420 TreeListControl's setViewModel not called
*basically just required that setViewModel() get called. Also made changes to
*the TableControl and teh TabbedPages control
*
*Revision 1.19.8.1  2002/11/16 19:37:47  ddiego
*this fixes bug [ 635840 ] Some control eat text events in Design mode.
*All that needed doing was adding an overridden handleEvents() to the TextControl
*and doing some moving around of code in the Win32Edit code.
*
*Revision 1.19  2002/06/24 04:24:49  ddiego
*mods to VCFBuilder
*
*Revision 1.18  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.17.4.2  2002/04/27 15:52:52  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.17.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.17  2002/03/13 01:26:35  ddiego
*fixes to the TreeListControl
*plus fix for bug [ 529012 ] typecombo crash in the ComboBoxControl. Caused
*by not checking a null pointer in the UIToolkits' methods for getting the
*next and previous control
*
*Revision 1.16  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.15  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/



/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/

/* Generated by Together */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/FoundationKit/StringTokenizer.h"


using namespace VCF;

Label::Label():
	CustomControl( false )
{
	
	caption_ = getClassName();	
	setTransparent( true );
	textAlignment_ = taTextLeft;
	textVerticalAlignment_ = tvaTextCenter;
	focusControl_ = NULL;
	wordWrap_ = false;	
	setTabStop( false );
}

void Label::paint( GraphicsContext * context )
{
	CustomControl::paint( context );
	context->setCurrentFont( getFont() );
	double y = 0.0;//getBounds()->getHeight() / 4;
	double x = 0.0;
	
	long drawOptions = GraphicsContext::tdoNone;

	switch ( textAlignment_ ) {
		case taTextLeft : {
			x += 1.0;
			drawOptions |= GraphicsContext::tdoLeftAlign;
		}
		break;

		case taTextCenter : {
			x = maxVal<>( 1.0, (getWidth()/2.0) - (context->getTextWidth( caption_ ) / 2.0) );
			drawOptions |= GraphicsContext::tdoCenterHorzAlign;
		}
		break;

		case taTextRight : {
			x = maxVal<>( 1.0, getWidth() - context->getTextWidth( caption_ ) );
			drawOptions |= GraphicsContext::tdoRightAlign;
		}
		break;
	}

	switch ( textVerticalAlignment_ ) {
		case tvaTextTop : {
			y = 1.0;
			drawOptions |= GraphicsContext::tdoTopAlign;
		}
		break;

		case tvaTextCenter : {
			y = (getHeight()/2.0) - (context->getTextHeight(caption_)/2.0);

			drawOptions |= GraphicsContext::tdoCenterVertAlign;
		}
		break;

		case tvaTextBottom : {
			y = getHeight() - context->getTextHeight(caption_);
			drawOptions |= GraphicsContext::tdoBottomAlign;
		}
		break;
	}
	
	Rect bounds = getClientBounds();

	if ( true == wordWrap_ ) {
		drawOptions |= GraphicsContext::tdoWordWrap;		
	}
	context->textBoundedBy( &bounds, caption_, drawOptions );
}

void Label::setCaption( const String& caption )
{
	VirtualKeyCode keyCode = UIToolkit::findMnemonic( caption );
		
	if ( keyCode != vkUndefined ) {
		AcceleratorKey* newAccelKey = new AcceleratorKey( this, keyCode, kmAlt, NULL, true );
		addAcceleratorKey( newAccelKey );
	}

	caption_ = caption;
	repaint();
}

String Label::getCaption()
{
	return caption_;
}

void Label::setName( const String& name )
{
	CustomControl::setName( name );
	if ( caption_.empty() ) {
		setCaption( name );
	}
}

void Label::setTextAlignment( const TextAlignmentType& textAlignment )
{
	textAlignment_ = textAlignment;
	repaint();
}

void Label::setVerticalAlignment( const TextVerticalAlignment& verticalAlignment )
{
	textVerticalAlignment_ = verticalAlignment;
	repaint();
}

void Label::setFocusControl( Control* focusControl )
{	
	focusControl_ = focusControl;
}

void Label::setWordWrap( const bool& wordWrap )
{
	wordWrap_ = wordWrap;
	repaint();
}

void Label::mnemonicActivate()
{
	if ( NULL != focusControl_ ) {
		focusControl_->setFocused();
	}
	else {
		CustomControl::mnemonicActivate();
	}
}

double Label::getPreferredWidth()
{
	if ( !wordWrap_ ) {
		GraphicsContext* ctx = this->getContext();
		if ( NULL != getParent() ) {
			return ctx->getTextWidth( getCaption() );
		}
	}
	return Control::getPreferredWidth();
}

double Label::getPreferredHeight()
{
	if ( wordWrap_ ) {
		GraphicsContext* ctx = this->getContext();

		double maxHeight = UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );

		if ( NULL != getParent() ) {
			double w = getWidth();
			double lineWidth = 0;
			
			StringTokenizer tok( caption_, " \n\r\t" );
			String currentLine;
			
			while ( tok.hasMoreElements() ) {
				String tmp = tok.nextElement();
				
				lineWidth += ctx->getTextWidth( currentLine + tmp );
				if ( lineWidth < w ) {
					currentLine += tmp;
				}
				else {
					maxHeight += ctx->getTextHeight( currentLine );
					lineWidth = 0;
					currentLine = "";				
				}
			}
		}

		return maxHeight;
	}	
		
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );
}

/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.20  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.18.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.18  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.17.2.5  2003/11/10 01:57:43  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.17.2.4  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.17.2.3  2003/10/07 21:25:49  ddiego
*minor adj to listview to get selected item correctly
*
*Revision 1.17.2.2  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.17.2.1  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.17  2003/08/09 02:56:45  ddiego
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
*Revision 1.16.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.16  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.3  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.15.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.15.2.1  2003/03/12 03:13:14  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.2.3  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.14.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.14.2.1  2002/12/27 23:05:06  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.14  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.13.10.1  2002/09/28 02:37:38  ddiego
*fixed up the radiobox and checkbox, label and header controls to properly
*take advantage of default heights from the UIMetricsManager
*fixed the default height for radioboxes and checkboxes in Win32 so that they are
*10 dialog units high - added the neccessary conversion code from dialog
*units to pixels
*
*Revision 1.13  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.12.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.12  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/








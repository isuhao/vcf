/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.6  2003/08/09 02:56:45  ddiego
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
*Revision 1.5.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.5  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4.2.1  2003/03/12 03:13:04  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.3.20.1  2002/12/30 03:59:26  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Revision 1.3  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/

//Cursor.h
/**
Copyright (c) 2000-2001, Jim Crafton
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
	Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

NB: This software will not save the world. 
*/

#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

Cursor::Cursor( const SystemCursorType& systemCursor )
{
	peer_ = UIToolkit::createCursorPeer( this );
	
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL cursor peer - this is probably not implemented yet") );
	}
	
	peer_->createSystemCursor( systemCursor );
	CursorManager::getCursorManager()->registerCursor( this );
}

Cursor::Cursor( Image* cursorImage, Point* hotSpot )
{
	peer_ = UIToolkit::createCursorPeer( this );

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL cursor peer - this is probably not implemented yet") );
	}
	
	peer_->createFromImage( cursorImage, hotSpot );
	CursorManager::getCursorManager()->registerCursor( this );
}

Cursor::Cursor( const String& cursorName, AbstractApplication* application )
{ 
	peer_ = UIToolkit::createCursorPeer( this );

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL cursor peer - this is probably not implemented yet") );
	}
	
	if ( NULL == application ) {
		peer_->createFromResourceName( cursorName );
	}
	else {
		peer_->createFromResourceName( cursorName, application->getPeer()->getHandleID() );
	}

	CursorManager::getCursorManager()->registerCursor( this );
}

Cursor::~Cursor()
{
	delete peer_;
}

long Cursor::getCursorID()
{
	return peer_->getCursorID();
}

void Cursor::setCursorFromID( const long& cursorID )
{

}

CursorPeer* Cursor::getPeer()
{
	return peer_;
}



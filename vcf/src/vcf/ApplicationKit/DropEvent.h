#if     _MSC_VER > 1000
#pragma once
#endif


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

#ifndef _VCF_DROPEVENT_H__
#define _VCF_DROPEVENT_H__



namespace VCF{
/**
 * Drop event are fired when an object is dropped during a drag drop operation. 
 */
class APPKIT_API DropTargetEvent : public Event {


public:
	
	DropTargetEvent( Object* source, DataObject* data ):
		Event( source ),
		keyMask_(0),
		buttonMask_(0),
		data_(data),
		action_(daNone) {
	 };

	DropTargetEvent( const DropTargetEvent& rhs ):Event(rhs) {
		*this = rhs;
	}
	
	virtual ~DropTargetEvent(){};


	DropTargetEvent& operator=( const DropTargetEvent& rhs ) {
		Event::operator =( rhs );
		
		keyMask_ = rhs.keyMask_;
		buttonMask_ = rhs.buttonMask_;
		data_ = rhs.data_;
		dropPoint_ = rhs.dropPoint_;
		action_ = rhs.action_;

		return *this;
	}


	virtual Object* clone( bool deep=false ) {
		return new DropTargetEvent(*this);
	}


    unsigned long getButtonMask() {
		return buttonMask_;
	}

	void setButtonMask( const unsigned long& buttonMask ) {
		buttonMask_ = buttonMask;
	}

    unsigned long getKeyMask() {
		return keyMask_;
	}

	void setKeyMask( const unsigned long& keyMask ) {
		keyMask_ = keyMask;
	}

    DataObject* getDataObject() {
		return data_;
	}

    Point getDropPoint() {
		return dropPoint_;
	}

	void setDropPoint( const Point& point ) {
		dropPoint_ = point;
	}

	void setActionType( const DragActionType& action ) {
		action_ = action;
	}

	/**
	*get the type of action the event represents
	*/
	DragActionType getAction() {
		return action_;
	}
protected:    
    unsigned long keyMask_;
    unsigned long buttonMask_;
    DataObject * data_;
    Point dropPoint_;
	DragActionType action_;
};




template <class SOURCE_TYPE> 
class DropEventHandler : public EventHandlerInstance<SOURCE_TYPE,DropTargetEvent>  {
public:
	DropEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,DropTargetEvent>::OnEventHandlerMethod handlerMethod, 
		const String& handlerName="") :
				EventHandlerInstance<SOURCE_TYPE,DropTargetEvent>( source, handlerMethod, handlerName ) {
					
	}
};



}





/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:36  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.3  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.5.2.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.5.2.1  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.5  2003/08/09 02:56:43  ddiego
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
*Revision 1.4.2.2  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.4.2.1  2003/05/25 19:07:10  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.4  2003/05/17 20:37:07  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.3  2003/03/23 03:23:46  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.3.2.1  2003/03/12 03:09:53  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.14.1  2002/12/25 22:06:23  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.1  2002/05/01 01:19:50  ddiego
*added remaining new files from switching stuff around
*like the peer classes and some of the drag drop stuff
*
*Revision 1.5  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/



#endif // _VCF_DROPEVENT_H__



#ifndef _VCF_CONTROLEVENT_H__
#define _VCF_CONTROLEVENT_H__
//ControlEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class Control;

/**
*ControlEvent are events generated by changes made to the control.
*Currently there are 3 types, one for controls being resized, one for a
*control's position being changed, and one for the control's parent being
*changed.
*
*@version 1.0
*@author Jim Crafton
*/
class APPLICATIONKIT_API ControlEvent : public Event  {
public:
	ControlEvent( Object* source );

	ControlEvent( Object* source, const ulong32& eventType );

	/**
	*use this constructor for creating CONTROL_SIZED events
	*/
	ControlEvent( Object* source, const Size& newSize );

	/**
	*use this constructor for creating CONTROL_POSITIONED events
	*/
	ControlEvent( Object* source, const Point& newPosition );

	/**
	*use this constructor for creating CONTROL_PARENT_CHANGED events
	*/
	ControlEvent( Object* source, Control* newParent );

	ControlEvent( const ControlEvent& rhs ):Event(rhs) {
		init();
		*this = rhs;
	}

	virtual ~ControlEvent();

	ControlEvent& operator=( const ControlEvent& rhs ) {
		Event::operator =( rhs );

		newSize_ = rhs.newSize_;
		newPosition_ = rhs.newPosition_;
		newParent_ = rhs.newParent_;

		return *this;
	}

	void init();

	virtual Object* clone( bool deep=false ) {
		return new ControlEvent(*this);
	}

	/**
	*returns the new size of the component
	*/
	Size getNewSize(){
		return 	newSize_;
	};

	/**
	*returns the new position of the component
	*/
	Point getNewPosition(){
		return 	newPosition_;
	};

	/**
	*returns the new parent
	*/
	Control* getNewParent(){
		return 	newParent_;
	};

protected:
	Size newSize_;
	Point newPosition_;
	Control* newParent_;
};





/**
*ControlEventHandler
*Handles the following:
*Sized
*Positioned
*ParentChanged
*/
template <class SOURCE_TYPE>
class ControlEventHandler : public EventHandlerInstance<SOURCE_TYPE,ControlEvent> {
public:
	ControlEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ControlEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ControlEvent>( source, handlerMethod, handlerName ) {

	}
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:36  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.8.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8  2003/08/09 02:56:43  ddiego
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
*Revision 1.7.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.7  2003/05/17 20:37:07  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.4  2003/03/23 06:45:59  marcelloptr
*minor fixes
*
*Revision 1.6.22.3  2003/03/23 03:23:46  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.6.22.1  2003/03/12 03:09:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.5  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CONTROLEVENT_H__



#ifndef _VCF_EVENT_H__
#define _VCF_EVENT_H__
//Event.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


namespace VCF{

#define CUSTOM_EVENT_TYPES	500


/**
*The Event class is root object for events in the Framework. Events are defined as any action that is generated
*in response to some change in the system. Moving the mouse, typing on the keyboard, etc are all example of Window
*System events that are generated by the User, but events can also be generated by an objects change in state.
*For example, a text model can fire events if the state of it's text has changed.
*
*@version 1.0
*@author Jim Crafton
*/
class FOUNDATIONKIT_API Event : public Object {

public:

    Event( Object * source);
	Event( Object* source, const unsigned long& eventType );

	Event( const Event& rhs ): Object(rhs) {
		init();
		*this = rhs;
	}

	Event& operator= ( const Event& rhs ) {

		source_ = rhs.source_;
		userData_ = rhs.userData_;
		eventType_ = rhs.eventType_;

		return *this;
	}

	void init();

	/**
	*shows whether or not the event has been consumed.
	*primarily used by the Listener list implementation
	*/
	bool consumed_;

	virtual void consume() { consumed_ = true; }

	bool getConsumed() {
        return consumed_;
    }

	void setConsumed( const bool& isConsumed ){
		consumed_ = isConsumed;
	}

	bool isConsumed() {
		return consumed_;
	}

	/**
	*retrieves the events source, in other words, who actually caused the
	*event to be generated
	*/
    Object* getSource();

	/**
	*gets the type of event. Some events may not put anything useful here, but events
	*associated with Listeners that have multiple methods (like MouseListener) will
	*definitely store a flag here. See the specific event class for the exact event types
	*the event types can be set to
	*/
    unsigned long getType();

	void setType( const unsigned long& type );

	/**
	*gets the time the event was created.
	*/
    time_t getTime();

	/*
	*sets the user data. User data is simply a place to store any sort of user specific info
	*that the programmer wants to attach to the event object. Only used by the specific application,
	*the Framework ignores this.
	*/
	void setUserData( void* userData );

	void* getUserData();

	virtual Object* clone( bool deep=false ) {
		return new Event(*this);
	}
private:
    Object* source_;
	void* userData_;
    unsigned long eventType_;
    time_t time_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.2  2004/04/26 21:58:36  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9.4.1  2004/04/06 17:19:15  ddiego
*minor header changes to better facilitate compiling with
*mingw. Also some minor changes to the devcpp FoundationKit project.
*
*Revision 1.9  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.8  2003/05/17 20:37:07  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.16.4  2003/03/23 06:45:59  marcelloptr
*minor fixes
*
*Revision 1.7.16.3  2003/03/23 03:23:46  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.16.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.7.16.1  2003/03/12 03:09:53  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_EVENT_H__



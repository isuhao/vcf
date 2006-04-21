#ifndef _VCF_VALIDATIONEVENT_H__
#define _VCF_VALIDATIONEVENT_H__
//ValidationEvent.h

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

class APPLICATIONKIT_API ValidationEvent : public VCF::Event {
public:

	ValidationEvent( Object* source );

	ValidationEvent( const ValidationEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~ValidationEvent();

	ValidationEvent& operator=( const ValidationEvent& rhs ) {
		validationSuccessful_ = rhs.validationSuccessful_;
		return *this;
	}

	bool isValidationSuccessful();

	void setValidationSuccessful( const bool& validationSuccessful );

	virtual Object* clone( bool deep=false ) {
		return new ValidationEvent(*this);
	}
private:
	bool validationSuccessful_;
};






/**
*ModelValidationEventHandler
*handles the following:
*onModelValidate
*/
template <class SOURCE_TYPE>
class ModelValidationEventHandler : public EventHandlerInstance<SOURCE_TYPE,ValidationEvent> {
public:
	ModelValidationEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ValidationEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ValidationEvent>( source, handlerMethod, handlerName ) {

	}

};



};


/**
*CVS Log info
*$Log$
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:37  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.9.2.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/08/09 02:56:43  ddiego
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
*Revision 1.8.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.8  2003/05/17 20:37:08  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.4  2003/03/23 06:46:01  marcelloptr
*minor fixes
*
*Revision 1.7.2.3  2003/03/23 03:23:47  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.7.2.1  2003/03/12 03:09:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.2.2  2002/12/27 23:04:35  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6.2.1  2002/12/25 22:06:25  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.6  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.5.16.1  2002/11/04 04:50:17  ddiego
*bug fixes are:
*void Win32MenuItem::clearChildren(), was passing in an incorrect index into DeleteMenu()
*fixed an issue when deleting a project from a workspace. This was crashing due to open
*documents with bad pointers. Closing a project now closes all open documents that are
*associated with the project
*Verified that the new file and new class and new form, and new project and checking the validity of
*entered data.
*Fixed a bug in Win32Dialog where the Frame::allowClose() virtual method was not being
*called.
*Fixed a bug in the Delegate class which would allow multiple additions of the same event handler.
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VALIDATIONEVENT_H__


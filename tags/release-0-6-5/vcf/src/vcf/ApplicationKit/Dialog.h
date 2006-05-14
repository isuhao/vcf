#ifndef _VCF_DIALOG_H__
#define _VCF_DIALOG_H__
//Dialog.h

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

class DialogPeer;
class WindowPeer;

#define DIALOG_CLASSID		"ED88C09A-26AB-11d4-B539-00C04F0196DA"



/**
 * A frame with a close button, and optionally a help and system button as well. The caption is the standard height.
 */
class APPLICATIONKIT_API Dialog : public Frame {
public:

	enum MessageStyle {
		msDefault = 0,
		msError,
		msInfo,
		msWarning
	};

	enum MessageButtons {
		mbOK = 1,
		mbHelp = 2,
		mbYesNo = 4,
		mbYesNoCancel = 8,
		mbOKCancel = 16,
		mbRetryCancel = 32,
		mbAbortRetryIgnore = 64
	};

	Dialog( Control* owner=NULL );

	//Dialog( Frame* owner );

	virtual void setCaption( const String& caption );

	virtual void paint(GraphicsContext * context);

	/**
	*overridden to take into account client bounds
	**/
	//virtual void resizeChildren();

	virtual Rect getClientBounds(const bool& includeBorder=true);

	virtual void setClientBounds( Rect* bounds );

	virtual UIToolkit::ModalReturnType showModal();

	virtual void show();

	virtual void close();

	UIToolkit::ModalReturnType getModalReturnValue() {
		return returnValue_;
	}

	void setModalReturnValue( const UIToolkit::ModalReturnType& returnType ) {
		returnValue_ = returnType;
	}

	static void showMessage( const String& message, const String& caption="" );

	static UIToolkit::ModalReturnType showMessage( const String& message, const String& caption,
											const long& messageButtons = mbOKCancel,
											const MessageStyle& messageStyle=msDefault );

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual bool allowsActivation() {
		return true;
	}

	virtual void setIconImage( Image* icon );

	virtual Image* getIconImage();
	
	virtual bool isActiveFrame();

	Control* getOwner() {
		return owner_;
	}

	/**
	returns true if the dialog's Dialog::showModal() method was called to display
	teh dialog (indicating that a modal event loops is active), other wise
	it returns false, indicating non-modal behaviour.
	*/
	bool isModal() {
		return modal_;
	}

	virtual void keyDown( KeyboardEvent* e );
protected:
    DialogPeer * dialogPeer_;
	WindowPeer * windowPeer_;
	Control* owner_;
	Control* previousFocusedControl_;
	UIToolkit::ModalReturnType returnValue_;
	bool modal_;

	virtual ~Dialog();
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.3.2.1  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.18.4.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.18  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.17.2.5  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.17.2.4  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.17.2.3  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.17.2.2  2003/08/28 21:47:31  ddiego
*added escape reponse...
*
*Revision 1.17.2.1  2003/08/18 19:52:32  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.17  2003/08/09 02:56:42  ddiego
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
*Revision 1.16.2.3  2003/06/13 00:00:31  ddiego
*more xmake fixes for the new version
*bug fixes for bugs
*509004	Opening a modal Dialog causes flicker
*also have tooltips working again
*
*Revision 1.16.2.2  2003/06/09 03:57:14  ddiego
*fixed an issue with tooltip not showing up, and while fixing that found it
*accidentally caused another problem with application focus for the main
*window not being handled correctly. This is now working OK! Now just
*have to get rid of the dialog flicker...
*Also fixed the QTPlayer example. It had some syntax errors from using the older
*event macros (not using Delegates)
*
*Revision 1.16.2.1  2003/05/27 04:45:24  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.16  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.16.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.15.16.1  2003/03/12 03:09:33  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.14.4.1  2002/04/27 15:42:25  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.14  2002/01/30 22:12:47  ddiego
*fixed the internals of default CommandButton::click() method
*closes the dialog without relying on the WM_COMMAND message,
*and responds to  vkEnter keyboards events more correctly, i.e.
*the Doalog will automatically close now when you hit the enter key
*and the button wil set the modal result of the dialogd
*
*Revision 1.13  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DIALOG_H__


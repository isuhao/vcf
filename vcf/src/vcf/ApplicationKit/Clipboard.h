#ifndef _VCF_CLIPBOARD_H__
#define _VCF_CLIPBOARD_H__
//Clipboard.h

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


class DataObject;
class ClipboardPeer;



/**
*The Clipboard represents a common place to put shared
*data between objects and/or between applications.
*The Clipboard maintains one or more ClipboardDataObjects
*that actually hold the data, according to their DataType.
*<p>
*The clipboard is never created directly - this is taken care of
*by the UIToolkit. To access the clipboard you call the
*UIToolkit::getSystemClipboard() method which will return a
*reference to the Clipboard singleton.
*<p>
*In Win32 the Clipboard is implemented with full support for
*COM's IDataObject for actual data transfer, so objects
*that put data into the Clipboard in the VCF can easily share
*the data with other Win32 programs.
*
*@see DataObject
*@see DataType
*@see ClipboardPeer
*@see UIToolkit::getSystemClipboard()
@delegates
	@del Clipboard::ClipboardContentsChanged
	@del Clipboard::ClipboardItemCopied
	@del Clipboard::ClipboardItemPasted
*/
class APPLICATIONKIT_API Clipboard : public Object{
public:

	Clipboard();

	virtual ~Clipboard();

	/**

	@delegate ClipboardContentsChanged is fired when the clipboard contents change
	@event ClipboardEvent
	*/
	DELEGATE(ClipboardContentsChanged)

	/**
	@delegate ClipboardItemCopied
	@event ClipboardEvent
	@eventtype
	*/
	DELEGATE(ClipboardItemCopied)

	/**
	@delegate ClipboardItemPasted
	@event ClipboardEvent
	@eventtype
	*/
	DELEGATE(ClipboardItemPasted)

	/**
	*does the Clipboard have a DataObject that
	*matches the requested dataType
	*@param String the datatype to look for
	*@return bool return true if the Clipboard has the kind of
	*data specified in dataType, otherwise returns false
	*/
	bool hasDataType( const String& dataType );

	/**
	*copies the specified dataObject into the clipboard.
	*The Clipboard takes ownership of the dataObject object
	*passed in which must be created on the heap.
	*@param DataObject the data object to place in the
	*Clipboard
	*<p>
	*For example:
	*<pre>
		Clipboard* clipboard = UIToolkit::getDefaultUIToolkit()->getSystemClipboard();

		String selectedText = "Hello World - here's some clipboard text";
		DataObject* textDataObj = new TextDataObject( selectedText );
		clipboard->copyTo( textDataObj );

	*</pre>
	*@see DataObject
	*/
	void copyTo( DataObject* dataObject );

	/**
	*pastes the data, specified in dataType, from the Clipboard
	*and returns it.
	*@param DataType the type of data to paste from the clipboard
	*@see DataType
	*@return DataObject* the new data from the clipboard or NULL
	*if no data object exists for the specified data type.
	*/
	DataObject* pasteFrom( const String& dataType );

	/**
	*internal VCF use only
	*/
	void internal_deleteDataObject( DataObject* dataObject );

private:
	ClipboardPeer * clipboardPeer_;
};

}


/**
*CVS Log info
*$Log$
*Revision 1.2.2.1  2004/11/10 19:07:32  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.3  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.5.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.5.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.5  2003/08/09 02:56:42  ddiego
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
*Revision 1.4.2.2  2003/06/27 03:10:58  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.4.2.1  2003/05/25 19:07:09  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.4  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:09:20  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.14.2  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.2.14.1  2002/12/25 22:06:14  ddiego
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
*Revision 1.1.2.1  2002/04/27 15:41:49  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.8  2002/02/14 05:04:52  ddiego
*documentation...
*
*Revision 1.7  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CLIPBOARD_H__



#ifndef _VCF_DEFAULTLISTITEM_H__
#define _VCF_DEFAULTLISTITEM_H__
//DefaultListItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__


namespace VCF{

class ListModel;

#define DEFAULTLISTITEM_CLASSID		"ED88C0AC-26AB-11d4-B539-00C04F0196DA"

class APPLICATIONKIT_API DefaultListItem : public ListItem {
public:

	DefaultListItem();

	DefaultListItem( ListModel* model );

	DefaultListItem( ListModel* model, const String& caption );

	virtual ~DefaultListItem();

	void init();

    virtual bool containsPoint( Point * pt );

    virtual unsigned long getIndex();

	virtual void setIndex( const unsigned long& index );

    virtual void* getData();

	virtual void setData( void* data );

	virtual String getCaption();

	virtual void setCaption( const String& caption );

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual bool isSelected();

	virtual void setSelected( const bool& selected );

	virtual long getImageIndex() {
		return imageIndex_;
	}

	virtual void setImageIndex( const long& imageIndex );

	virtual Rect* getBounds() {
		return &bounds_;
	}

	virtual bool canPaint() {
		return true;
	}

	virtual void addSubItem( const String& caption, void* data );

	virtual void addSubItem( ListItem::SubItem* subItem );

	virtual void removeSubItem( const ulong32& index );

	virtual Enumerator<ListItem::SubItem*>* getSubItems();

	virtual ListItem::SubItem* getSubItem( const ulong32& index );

	virtual ulong32 getSubItemCount();

	virtual void subItemChanged( ListItem::SubItem* item );

	virtual void setBounds( Rect* bounds );

	/**
	*not supported
	*/
	virtual long getStateImageIndex(){
		return -1;
	};

	/**
	*not supported
	*/
	virtual void setStateImageIndex( const long& index ){}

private:	
	String caption_;
	void* data_;
	unsigned long index_;
	Rect bounds_;	
	bool selected_;
	long imageIndex_;
	std::vector<SubItem*> subItems_;
	EnumeratorContainer<std::vector<SubItem*>,SubItem*> subItemsContainer_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4.2.1  2006/03/05 02:28:04  ddiego
*updated the Item interface and adjusted the other classes accordingly.
*
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/03/20 04:29:21  ddiego
*added ability to set image lists for list box control.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.1  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
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
*Revision 1.22.4.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.22  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.21.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.21  2003/08/09 02:56:42  ddiego
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
*Revision 1.20.2.1  2003/06/30 02:53:15  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.20  2003/05/17 20:37:02  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.19.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.19.2.1  2003/03/12 03:09:29  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.19  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.18.14.1  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.18  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.17.4.1  2002/04/27 15:42:01  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.17  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTLISTITEM_H__



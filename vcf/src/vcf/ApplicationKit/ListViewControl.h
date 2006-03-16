#ifndef _VCF_LISTVIEWCONTROL_H__
#define _VCF_LISTVIEWCONTROL_H__
//ListViewControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */



#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__

#ifndef _VCF_LISTMODELEVENT_H__
#	include "vcf/ApplicationKit/ListModelEvent.h"
#endif // _VCF_LISTMODELEVENT_H__




#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__

#ifndef _VCF_COLUMNITEM_H__
#	include "vcf/ApplicationKit/ColumnItem.h"
#endif // _VCF_COLUMNITEM_H__

#ifndef _VCF_COLUMNMODELEVENT_H__
#	include "vcf/ApplicationKit/ColumnModelEvent.h"
#endif // _VCF_COLUMNMODELEVENT_H__



namespace VCF {


class ListviewPeer;

class ImageList;




enum ListViewDisplayOptions {
	lvdoDefault = 0,
	lvdoHotTracking = 1,
	lvdoFullRowSelect = 2,
	lvdoGridLines = 4
};




/**
*An enum of icon styles for list views
*/
enum IconStyleType {
	isLargeIcon=0,
	isSmallIcon,
	isList,
	isDetails
};

/**
*An enum of icon alignment types for list views
*/
enum IconAlignType {
	iaNone=0,
	iaTop,
	iaLeft,
	iaAutoArrange
};

static String IconStyleTypeNames[] = { "isLargeIcon",
                                         "isSmallIcon",
										 "isList",
										 "isDetails" };

static String IconAlignTypeNames[] = { "iaNone",
                                         "iaTop",
										 "iaLeft",
										 "iaAutoArrange" };
										 
										 


										 

#define LISTVIEWCONTROL_CLASSID			"ED88C09D-26AB-11d4-B539-00C04F0196DA"


/**
\class ListViewControl ListViewControl.h "vcf/ApplicationKit/ListViewControl.h"
*/
class APPLICATIONKIT_API ListViewControl : public VCF::Control {
public:


	DELEGATE(ItemSelectionChanged);
	DELEGATE(ColumnItemClicked);

	ListViewControl();

	virtual ~ListViewControl();

	enum {
		COLUMN_MOUSE_EVENT_CLICK = Control::CONTROL_EVENTS_LAST + 200
	};

	/* autoresizing added by Marcello */
	enum AutoSizeType {
		lcatAutoSizeNone = -1,
		lcatAutoSizeColumns = -2,
		lcatAutoSizeHeaders = -3,
		lcatAutoSizeColumnsAndHeaders = -4,
	};

	ListModel* getListModel();

	ColumnModel* getColumnModel();

	void setListModel(ListModel * model);

	virtual void paint( GraphicsContext * context );

	virtual ColumnItem* addHeaderColumn( const String& columnName, const double& width=100.0 );

	void addHeaderColumn( ColumnItem* column );

	virtual ColumnItem* insertHeaderColumn( const unsigned long& index, const String& columnName, const double& width=100.0 );

	void insertHeaderColumn( const unsigned long& index, ColumnItem* column );

	void deleteHeaderColumn( const unsigned long& index );

	String getColumnName( const unsigned long& index );

	void setColumnName( const unsigned long& index, const String& columnName );

	double getColumnWidth( const unsigned long& index );

	void setColumnWidth( const unsigned long& index, const double& width, ListViewControl::AutoSizeType type=lcatAutoSizeNone );

	void setColumnsWidth( const double& width, ListViewControl::AutoSizeType type=lcatAutoSizeNone );

	virtual ListItem* addItem( const String& caption, const ulong32 imageIndex=0 );

	void addItem( ListItem* item );

	virtual ListItem* insertItem( const ulong32& index, const String& caption, const ulong32 imageIndex=0 );

	void insertItem( const ulong32& index, ListItem* item );

	IconStyleType getIconStyle();

	void setIconStyle( const IconStyleType& iconStyle );

	bool getAllowsMultiSelect();

	void setAllowsMultiSelect( const bool& allowsMultiSelect );

	IconAlignType getIconAlignment();

	void setIconAlignment( const IconAlignType& iconAlignType );

	bool getAllowLabelEditing();

	void setAllowLabelEditing( const bool& allowLabelEditing );

	void setItemFocused( ListItem* item );

	void init();

	void sort( ItemSort* itemSortFunctor );

	ListItem* isPtOverItem(Point* point);

	ListItem* getFocusedItem();

	ListItem* getSelectedItem();

	/**
	*calling this repeatedly on the same item will toggle the
	*selection state of the item
	*/
	void selectItem( ListItem* item );

	Enumerator<ListItem*>* getSelectedItems();

	void rangeSelect( Rect* selectionRect );

	ImageList* getSmallImageList() {
		return stateImageList_;
	}

	ImageList* getLargeImageList() {
		return largeImageList_;
	}

	ImageList* getStateImageList() {
		return stateImageList_;
	}

	void setLargeImageList( ImageList* imageList );

	void setSmallImageList( ImageList* imageList );

	void setStateImageList( ImageList* imageList );

	Rect getItemImageRect( ListItem* item );

	long getDisplayOptions();

	void setDisplayOptions( const long& displayOptions );

	Rect getItemRect( ListItem* item );

	virtual void handleEvent( Event* event );
protected:
	//Events
	void onItemPaint( ItemEvent* event );

	void onListModelContentsChanged( ListModelEvent* event );

	void onItemAdded( ListModelEvent* event );

	void onItemDeleted( ListModelEvent* event );

	void onListModelEmptied( ModelEvent* event );

	void onColumnItemAdded( ColumnModelEvent* event );

	void onColumnItemDeleted( ColumnModelEvent* event );

	void onColumnItemChanged( ItemEvent* event );

	void onItemSelected( ItemEvent* event );

	ListviewPeer * listviewPeer_;
	ListModel* listModel_;
	ColumnModel* columnModel_;
	IconStyleType iconStyle_;
	ImageList* smallImageList_;
	ImageList* largeImageList_;
	ImageList* stateImageList_;
	ListItem* selectedItem_;

};



};


/**
*CVS Log info
*$Log$
*Revision 1.2.6.3  2006/03/16 03:23:09  ddiego
*fixes some font change notification issues in win32 peers.
*
*Revision 1.2.6.2  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2.6.1  2005/11/21 04:00:51  ddiego
*more osx updates.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/14 04:56:01  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.23.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.23  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.22.2.7  2003/10/07 21:26:05  ddiego
*minor adj to listview to get selected item correctly
*
*Revision 1.22.2.6  2003/09/23 22:17:35  marcelloptr
*updated examples project files dsp and vcproj
*
*Revision 1.22.2.5  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.22.2.4  2003/09/09 19:31:17  marcelloptr
*minor changes and autoresizing of listbox columns
*
*Revision 1.22.2.3  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.22.2.2  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.22.2.1  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.22  2003/08/09 02:56:42  ddiego
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
*Revision 1.21.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.21  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.20.2.1  2003/03/12 03:09:36  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.20  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.19.14.2  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.19.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.19  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.18.4.1  2002/04/27 15:42:42  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.18  2002/02/20 04:07:49  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.17  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LISTVIEWCONTROL_H__



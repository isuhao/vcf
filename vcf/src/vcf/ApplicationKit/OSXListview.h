#ifndef _VCF_OSXLISTVIEW_H__
#define _VCF_OSXLISTVIEW_H__
//OSXListview.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ListviewPeer.h"
namespace VCF {
	class OSXListview;
};

@interface OSXListviewDataSrc : NSObject
{
	VCF::ListModel* model;
}

- (void)setModel:(VCF::ListModel*)aModel;
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView;
- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex;
@end


@interface OSXListviewTableDelegate : NSObject 
{
	VCF::OSXListview* listView;
}
- (void)setListView:(VCF::OSXListview* ) aListView;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
@end

namespace VCF
{

class OSXListview : public OSXControl, public ListviewPeer {
public:
	OSXListview( ListViewControl* listviewControl );

	virtual ~OSXListview();

	virtual void create( Control* owningControl );

	virtual void selectItem( const uint32& index );

	virtual uint32 getSelectedItem();

	virtual void setFocusedItem( const uint32& index );

	virtual uint32 getFocusedItem();

	virtual bool isItemSelected( const uint32& index );

	virtual Rect getItemRect( const uint32& index );	

	virtual Rect getItemImageRect( const uint32& index );

	virtual uint32 hitTest( const Point& point );	

	virtual Enumerator<uint32>* getSelectedItems();

	virtual void rangeSelect( const Rect& selectionRect );	

	virtual bool allowsMultiSelect();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );	

	virtual void setLargeImageList( ImageList* imageList );

	virtual void setSmallImageList( ImageList* imageList );


	virtual bool ensureVisible(const uint32& index, bool partialOK );
	
	virtual void setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type );

	virtual double getColumnWidth( const uint32& index );

	virtual TextAlignmentType getColumnTextAlignment( const uint32& index );

	virtual void setColumnTextAlignment( const uint32& index, const TextAlignmentType& val );

	virtual IconStyleType getIconStyle();

	virtual void setIconStyle( const IconStyleType& iconStyle );

	virtual IconAlignType getIconAlignment();

	virtual void setIconAlignment( const IconAlignType& iconAlignType );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );		

	virtual int32 getDisplayOptions();

	virtual void setDisplayOptions( const int32& displayOptions );

	
protected:	
	ListViewControl* listviewControl_;
	Array<uint32> selectedItems_;
	OSXListviewDataSrc* dataSrc_;
	NSTableView* tableView_;
	OSXListviewTableDelegate* tableDelegate_;
	
	bool allowLabelEditing_;
	
	void onControlModelChanged( Event* e );
	void onListModelChanged( Event* e );
	void onColumnModelAdded( Event* e );
	void onColumnModelRemoved( Event* e );	
	void onColumnModelChanged( Event* e );		
};


};


#endif // _VCF_OSXLISTVIEW_H__

/**
$Id$
*/

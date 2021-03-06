#ifndef _VCF_WIN32TREE_H__
#define _VCF_WIN32TREE_H__
//Win32Tree.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/TreePeer.h"

#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

namespace VCF {

class TreeModelEvent;
class ImageListEvent;

class Win32Tree : public AbstractWin32Component, public TreePeer  {
public:
	Win32Tree( TreeControl* tree );

	virtual ~Win32Tree();

	virtual void create( Control* owningControl );
	
    virtual double getItemIndent();

    virtual void setItemIndent( const double& indent );

	virtual void setStateImageList( ImageList* imageList );

    virtual void setImageList( ImageList* imageList );	

	virtual void setHeaderImageList( ImageList* imageList );

	virtual Win32Object::CreateParams createParams();

	virtual Rect getItemImageRect( const TreeModel::Key& itemKey );

	virtual Rect getItemRect( const TreeModel::Key& itemKey );

	virtual TreeModel::Key hitTest( const Point& pt );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual void enableHeader( const bool& val );

	virtual void setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type );

	virtual double getColumnWidth( const uint32& index );

	virtual TextAlignmentType getColumnTextAlignment( const uint32& index );

	virtual void setColumnTextAlignment( const uint32& index, const TextAlignmentType& val );

	virtual void setDisplayOptions( uint32 displayOptions );

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual void setFont( Font* font );

	virtual void repaint( Rect* repaintRect, const bool& immediately );
private:

	TreeControl* treeControl_;
	std::map<TreeModel::Key,HTREEITEM> treeItems_;
	HIMAGELIST imageListCtrl_;
	HIMAGELIST stateImageListCtrl_;
	HIMAGELIST headerImageListCtrl_;
	GraphicsContext* currentCtx_;
	HWND headerWnd_;
	WNDPROC oldHeaderWndProc_;
	HWND treeWnd_;
	WNDPROC oldTreeWndProc_;

	HFONT oldHeaderFont_;
	bool headerEnabled_;	

	std::vector<RECT> headerRects_;

	bool internalTreeItemMod_;
	void onImageListImageChanged( ImageListEvent* event );
	void onStateImageListImageChanged( ImageListEvent* event );
	void onHeaderImageListImageChanged( ImageListEvent* event );

	void onControlModelChanged( Event* e );
	void onItemExpanded( ItemEvent* e );
	void onItemSelected( ItemEvent* e );
	void onItemStateChanged( ItemEvent* e );
	void onTreeModelChanged( ModelEvent* event );
	void onColumnModelChanged( ModelEvent* event );
	void addTreeItem( TreeModel::Key key, HTREEITEM parent );

	void registerHeaderWndProc();
	static LRESULT CALLBACK HeaderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK TreeWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void drawItem( NMTVCUSTOMDRAW* drawInfo );

	LRESULT treeCustomDraw( NMTVCUSTOMDRAW* drawInfo );
	LRESULT headerCustomDraw( NMCUSTOMDRAW* drawInfo );

	LRESULT treeWndPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

};


#endif // _VCF_WIN32TREE_H__

/**
$Id$
*/

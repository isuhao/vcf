#if     _MSC_VER > 1000
#pragma once
#endif

/**
*CVS Log info
*$Log$
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

#ifndef _VCF_DEFAULTLISTITEM_H__
#define _VCF_DEFAULTLISTITEM_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__


namespace VCF{

#define DEFAULTLISTITEM_CLASSID		"ED88C0AC-26AB-11d4-B539-00C04F0196DA"

class APPKIT_API DefaultListItem : public ListItem {
public:

	DefaultListItem();

	DefaultListItem( Model* model );

	DefaultListItem( Model* model, const String& caption );

	virtual ~DefaultListItem();

	void init();

    virtual bool containsPoint( Point * pt );

	DELEGATE(ItemPaint);
	DELEGATE(ItemChanged);
	DELEGATE(ItemSelected);
	DELEGATE(ItemAdded);
	DELEGATE(ItemDeleted);

	DELEGATE(SubItemChanged);
	DELEGATE(SubItemAdded);
	DELEGATE(SubItemDeleted);

	virtual void addItemPaintHandler( EventHandler* handler ){
		ItemPaint += handler;
	}

	virtual void addItemChangedHandler( EventHandler* handler ){
		ItemChanged += handler;
	}

	virtual void addItemSelectedHandler( EventHandler* handler ){
		ItemSelected += handler;
	}

	virtual void addItemAddedHandler( EventHandler* handler ){
		ItemAdded += handler; 
	}

	virtual void addItemDeletedHandler( EventHandler* handler ){
		ItemDeleted += handler;
	}
    
	virtual void removeItemPaintHandler( EventHandler* handler ){
		ItemPaint -= handler; 
	}

	virtual void removeItemChangedHandler( EventHandler* handler ){
		ItemChanged -= handler; 
	}

	virtual void removeItemSelectedHandler( EventHandler* handler ){
		ItemSelected -= handler; 
	}

	virtual void removeItemAddedHandler( EventHandler* handler ){
		ItemAdded -= handler; 
	}

	virtual void removeItemDeletedHandler( EventHandler* handler ){
		ItemDeleted -= handler; 
	}

	

    virtual unsigned long getIndex();

	virtual void setIndex( const unsigned long& index );

    virtual void* getData();

	virtual void setData( void* data );	

	virtual String getCaption();
	
	virtual void setCaption( const String& caption );

	virtual Model* getModel();

	virtual void setModel( Model* model );

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

	virtual Control* getControl() {
		return owningControl_;
	}


	virtual void setControl( Control* control ) {
		owningControl_ = control;
	}

	virtual bool canPaint() {
		return true;	
	}

	virtual void addSubItemAddedHandler( EventHandler* handler ){
		SubItemAdded += handler;
	}

	virtual void addSubItemDeletedHandler( EventHandler* handler ){
		SubItemDeleted += handler;
	}

	virtual void addSubItemChangedHandler( EventHandler* handler ){
		SubItemChanged += handler;
	}

	virtual void removeSubItemAddedHandler( EventHandler* handler ){
		SubItemAdded -= handler; 
	}

	virtual void removeSubItemDeletedHandler( EventHandler* handler ){
		ItemDeleted -= handler; 
	}

	virtual void removeSubItemChangedHandler( EventHandler* handler ) {
		SubItemChanged -= handler;
	}

	virtual void addSubItem( const String& caption, void* data );

	virtual void addSubItem( ListItem::SubItem* subItem );

	virtual void removeSubItem( const ulong32& index );

	virtual Enumerator<ListItem::SubItem*>* getSubItems();

	virtual ListItem::SubItem* getSubItem( const ulong32& index );

	virtual ulong32 getSubItemCount();

	virtual void subItemChanged( ListItem::SubItem* item );

	virtual long getState(){
		return 0;	
	}

	virtual void setState( const long& state ){}

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

	virtual long getTag() {
		return tag_;
	}

	virtual void setTag( const long& tag ) {
		tag_ = tag;
	}
private:	
	Control* owningControl_;
	String caption_;
	void* data_;
	unsigned long index_;
	Rect bounds_;
	Model* model_;
	bool selected_;
	long imageIndex_;
	long tag_;
	std::vector<SubItem*> subItems_;
	EnumeratorContainer<std::vector<SubItem*>,SubItem*> subItemsContainer_;
};

};

#endif // _VCF_DEFAULTLISTITEM_H__



#if     _MSC_VER > 1000
#pragma once
#endif



#ifndef _VCF_COMBOBOXCONTROL_H__
#define _VCF_COMBOBOXCONTROL_H__

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


#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__

#ifndef _VCF_LISTMODELEVENT_H__
#	include "vcf/ApplicationKit/ListModelEvent.h"
#endif // _VCF_LISTMODELEVENT_H__



namespace VCF  {

class TextControl;

#define COMBOBOXCONTROL_CLASSID		"4A9D66D5-3B26-11d4-B54C-00C04F0196DA"


/**
*The various styles for a ComboBoxControl. Currently there are only 2.
*/
enum ComboBoxStyleType {
	cbsDropDown = 0,
	cbsDropDownWithEdit
};


static String ComboBoxStyleTypeNames[] = { "cbsDropDown", 
                                         "cbsDropDownWithEdit" };



/**
*A combo box control is a control that is used to display a selection from a list of choices
*in a single field. When the down arrow is clicked on a popup list is displayed that shows
*all the possible choices for the control.
*<p>
*The ComboBoxControl uses the ListModel, same abstract model as the ListBoxControl and 
*ListViewControl controls, to store it's presentation data in.

@delegates
	@del ComboBoxControl::SelectionChanged

*/
class APPKIT_API ComboBoxControl : public VCF::CustomControl {
public:

	ComboBoxControl();	

	virtual ~ComboBoxControl();

	void init();

	/**
	@delegate SelectionChanged this is fired when the selection changes in the 
	combo box.
	@event ItemEvent
	@eventtype ITEM_EVENT_SELECTED
	*/
	DELEGATE(SelectionChanged)
	
	/**
	*returns the ListModel currently associated with it.
	*@return ListModel the list model for the control
	*/
	ListModel* getListModel();

	/**
	*sets the ListModel for the Control. If there was a previous ListModel
	*already associated with the control, then the old ListModel's release() method 
	*will be called prior to setting the new ListModel. The control will
	*call the newly set ListModel's addRef() after setting.
	*@param ListModel the new model to set for this control
	*/
	void setListModel(ListModel * model); 

	/**
	*the overriden paint method
	*/
	virtual void paint( GraphicsContext* context );

	
	void onListModelContentsChanged( ListModelEvent* event );

	void onItemAdded( ListModelEvent* event );

	void onItemDeleted( ListModelEvent* event );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void mouseEnter( MouseEvent* event );

	virtual void mouseLeave( MouseEvent* event );

	virtual void keyPressed( KeyboardEvent* event );

	/**
	*returns the currently selected item.
	*@return ListItem the currently selected tiem. If nothing is selected then
	*the return value will be NULL.
	*/
	ListItem* getSelectedItem();

	/**
	*sets the currently selected item. Causes a SelectionChanged
	*event to be fired. 
	@param ListItem the item to be selected
	*/
	void setSelectedItem( ListItem* selectedItem );

	/**
	*sets the currently selected item as specified by the index. 
	*Causes a SelectionChanged event to be fired. 
	@param ulong32 the index of the item to be selected
	*/
	void setSelectedItemIndex( const ulong32& selectedIndex );

	/**
	*returns the combo box style.
	*The style may be cbsDropDown, which means the entry in the combo box field
	*is non editable, or cbsDropDownWithEdit, which means the user can edit the 
	*fields data.
	@return ComboBoxStyleType the current style of the ComboBoxControl
	*/
	ComboBoxStyleType getComboBoxStyle() {
		return comboBoxStyle_;
	}

	/**
	*sets the style of the combo box
	*@param ComboBoxStyleType the new style of the ComboBoxControl
	*/
	void setComboBoxStyle( const ComboBoxStyleType& comboBoxStyle );	

	/**
	*adds a new ListItem. This method simply calls the models ListModel::addItem()
	*method and returns the newly created ListItem. Currently the default implementation
	*creates a DefaultListItem to add.
	*@param String the caption of the new item
	*@param ulong32 th image index of the new item. The default value is 0
	*@return ListItem the newly added item
	*/
	ListItem* addItem( const String& caption, const ulong32 imageIndex=0 );

	/**
	*adds a new ListItem. This method simply calls the models ListModel::addItem()
	*method. 
	*@param ListItem the item top be added to the control's ListModel
	*/
	void addItem( ListItem* item );

	/**
	*sets the drop down count. This is used to specify how many 
	*items are visible in the drop down list before scrollbars 
	*become neccessary
	*@param ulong32 the new drop down count
	*/
	void setDropDownCount( const ulong32& dropDownCount );

	/**
	*returns the current drop down count
	*/
	ulong32 getDropDownCount() {
		return dropDownCount_;
	}

	/**
	*sets the drop down width. This is used to specify the width 
	*of the drop down list if the user prefers it bigger then
	*the ComboBoxControl's width itself
	*@param ulong32 the new drop down witdh
	*/
	void setDropDownWidth( const ulong32& dropDownCount );

	/**
	*returns the current drop down witdh
	*/
	ulong32 getDropDownWidth() {
		return (ulong32)dropDownWidth_;
	}

	/**
	*sets true to allow the drop down list to extend to the full screen height
	*@param bool the new state of drop down list extension 
	*/
	void setDropDownExtendFullScreen( const bool& dropDownExtendFullScreen );

	/**
	*returns true if the drop down list is allowed to extend to the full screen height
	*/
	bool getDropDownExtendFullScreen() {
		return dropDownExtendFullScreen_;
	}

	/**
	*sets if the item has been selected through the drop down list
	*( i.e. manually by the user ) or through calls by source code
	* by using the function setSelectedItem
	*@param bool state telling if selected by the drop down list ( for reset )
	*/
	void setDropDownSelected( const bool& dropDownSelected );

	/**
	*returns the current state telling if the item has been selected by 
	*clicking the drop down list
	*/
	bool getDropDownSelected() {
		return dropDownSelected_;
	}

	/**
	*sets if the autoLookup of typed items is enabled
	*@param bool state telling if the autoLookup is enabled
	*/
	void setAutoLookup( const bool& autoLookup );

	/**
	*returns the current state telling if the autoLookup is enabled
	*/
	bool getAutoLookup() {
		return autoLookup_;
	}

	/**
	*sets if the autoLookup is done ignoring then letter's case
	*@param bool state telling if the autoLookup is done ignoring then letter's case
	*/
	void setAutoLookupIgnoreCase( const bool& ignoreCase );

	/**
	*returns the current state telling if the autoLookup is done ignoring then letter's case
	*/
	bool getAutoLookupIgnoreCase() {
		return autoLookupIgnoreCase_;
	}

	virtual bool keepsArrowKeys() {
		return true;
	}

	void setEnabled( const bool& enabled );

	String getCurrentText();

	virtual void setCurrentText( const String& text );

	Rect getEditBounds();

	virtual double getPreferredHeight();

	virtual void selectItems( const bool& select );

protected:
	void onDropDownLostFocus( WindowEvent* event );
	void closeDropDown( Event* event );
	void onEditKeyPressed( KeyboardEvent* event );
	void onEditReturnKeyPressed( KeyboardEvent* event );

	void onFocusGained( FocusEvent* event );	

	void onPostSelect( ItemEvent* e );
	Window* dropDown_;
	ListModel* listModel_;	
	ListItem* selectedItem_;
	ulong32 selectedIndex_;
	bool arrowPressed_;
	Rect arrowRect_;
	Rect viewRect_;
	bool mouseOver_;
	ComboBoxStyleType comboBoxStyle_;
	TextControl* edit_;
	void updateEditBounds();
	ulong32 dropDownCount_;
	double dropDownWidth_;
	bool dropDownExtendFullScreen_;
	bool dropDownSelected_;
	bool autoLookup_;
	bool autoLookupIgnoreCase_;



	virtual void destroy();
};

};

/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.24.2.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.24  2004/04/03 16:09:30  ddiego
*Found some more merge issues that needing resolving.
*
*Revision 1.23  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.22.2.1  2004/03/21 22:59:34  marcelloptr
*ComboBox fixes, improvements, autoLookup
*
*Revision 1.22  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.21.2.8  2003/12/13 18:19:34  ddiego
**** empty log message ***
*
*Revision 1.21.2.7  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.21.2.6  2003/11/10 01:57:03  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.21.2.5  2003/10/11 14:02:32  ddiego
*fixed a bug in the timing of when selection events are passed to the
*SelectionCHanged delegate on the combobox control. Now the drop
*down list is closed FIRST, and the event posted, then handled
*
*Revision 1.21.2.4  2003/10/11 13:18:55  ddiego
*patched in Marcellos fix for the ComboBox to fix a bug when setting the
*drop count to a large number - great work Marcello!!!
*
*Revision 1.21.2.3  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.21.2.2  2003/09/06 19:45:44  ddiego
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
*Revision 1.21.2.1  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
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
*Revision 1.20.2.1  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.20  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.19.2.2  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.19.2.1  2003/03/12 03:09:21  ddiego
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
*Revision 1.18.2.3  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.18.2.2  2002/12/27 23:04:30  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.18.2.1  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.18  2002/11/18 00:46:07  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.17.10.1  2002/10/14 04:12:23  ddiego
*finalized the code generation for the generic C++ class. This now completes
*task 58649, to define a new Class template. Also made a few changes to the
*ComboBoxCOntrol so that if you setEnabled (val) and the edit box is present
*then the edit box is also enabled or disabled.
*
*Revision 1.17  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.15.4.1  2002/04/27 15:41:54  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.15  2002/03/13 01:26:26  ddiego
*fixes to the TreeListControl
*plus fix for bug [ 529012 ] typecombo crash in the ComboBoxControl. Caused
*by not checking a null pointer in the UIToolkits' methods for getting the
*next and previous control
*
*Revision 1.14  2002/02/17 01:07:14  ddiego
*removed OpenGL stuff to minimize memory impact. It will be in it's own
*module. Also fixed bugs:
*[ #500694 ] Combo text over writing down arrow
*[ #498481 ] pasting into edit control
*
*Revision 1.13  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/



#endif // _VCF_COMBOBOXCONTROL_H__



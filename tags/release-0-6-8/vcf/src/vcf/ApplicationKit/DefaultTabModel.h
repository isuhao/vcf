#ifndef _VCF_DEFAULTTABMODEL_H__
#define _VCF_DEFAULTTABMODEL_H__
//DefaultTabModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABMODEL_H__
#	include "vcf/ApplicationKit/TabModel.h"
#endif // _VCF_TABMODEL_H__

#ifndef _VCF_TABPAGE_H__
#	include "vcf/ApplicationKit/TabPage.h"
#endif // _VCF_TABPAGE_H__


#ifndef _VCF_TABMODELEVENT_H__
#	include "vcf/ApplicationKit/TabModelEvent.h"
#endif // _VCF_TABMODELEVENT_H__


namespace VCF {

#define DEFAULTTABMODEL_CLASSID		"86F02174-3E7F-11d4-8EA7-00207811CFAB"

/**
This class represents a default, basic implementation of
the TabModel class.
@delegates
	@del DefaultTabModel::ModelEmptied
	@del DefaultTabModel::ModelValidate
	@del DefaultTabModel::TabPageAdded
	@del DefaultTabModel::TabPageRemoved
	@del DefaultTabModel::TabPageSelected
*/
class APPLICATIONKIT_API DefaultTabModel : public Model, public TabModel {
public:

	DefaultTabModel();

	virtual ~DefaultTabModel();

	/**
	@delegate ModelEmptied fired when the model's empty() method is
	called.
	@event ModelEvent
	@see empty()
	*/
	DELEGATE(ModelEmptied)

	/**
	@delegate ModelValidate fired when the model's validate() method is called
	@event ValidationEvent
	@see validate()
	*/
	DELEGATE(ModelValidate)


    virtual void addModelValidationHandler( EventHandler* handler ) {
		ModelValidate += handler;
	}

	virtual void removeModelValidationHandler( EventHandler* handler ) {
		ModelValidate -= handler;
	}

	virtual void addModelHandler( EventHandler* handler ) {
		ModelEmptied += handler;
	}

	virtual void removeModelHandler( EventHandler* handler ) {
		ModelEmptied -= handler;
	}

	/**
	@delegate TabPageAdded this is fired when a new tab page item is
	added to the model.
	@event TabModelEvent
	@eventtype TAB_MODEL_EVENT_ITEM_ADDED
	*/
	DELEGATE(TabPageAdded)

	/**
	@delegate
	@event TabModelEvent
	@eventtype TAB_MODEL_EVENT_ITEM_REMOVED
	*/
	DELEGATE(TabPageRemoved)

	/**
	@delegate TabModelEvent - this is fired when a tab page is selected by calling
	the setSelectedPage() method
	@event TabModelEvent
	@eventtype TAB_MODEL_EVENT_ITEM_SELECTED
	@see setSelectedPage()
	*/
	DELEGATE(TabPageSelected)

	virtual void addTabPageAddedHandler( EventHandler* handler ) {
		TabPageAdded += handler;
	}

	virtual void removeTabPageAddedHandler( EventHandler* handler ) {
		TabPageAdded -= handler;
	}

	virtual void addTabPageRemovedHandler( EventHandler* handler ) {
		TabPageRemoved += handler;
	}

	virtual void removeTabPageRemovedHandler( EventHandler* handler ) {
		TabPageRemoved -= handler;
	}

	virtual void addTabPageSelectedHandler( EventHandler* handler ) {
		TabPageSelected += handler;
	}

	virtual void removeTabPageSelectedHandler( EventHandler* handler ) {
		TabPageSelected -= handler;
	}

	virtual void addTabPage( TabPage* page );

	virtual void insertTabPage( const ulong32& index, TabPage* page );

	virtual void deleteTabPage( TabPage* page );

	virtual void deleteTabPage( const ulong32& index );

	virtual void clearTabPages();

	virtual TabPage* getPageAt( const ulong32& index );

	virtual TabPage* getPageFromPageName( const String& pageName );

	virtual ulong32 getItemIndex( TabPage* item );

	virtual TabPage* getSelectedPage();

	virtual void setSelectedPage( TabPage* page );

	virtual void setSelectedPage( const ulong32& index );

	virtual Enumerator<TabPage*>* getPages();

    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate(){};

    /**
     * clears out the model's data
     */
    virtual void empty(){};

	virtual uint32 getPageCount() {
		return pages_.size();
	}

	bool isFirstPage( TabPage* page );

	bool isLastPage( TabPage* page );

	TabPage* nextPage( TabPage* page );

	TabPage* previousPage( TabPage* page );
protected:
	std::vector<TabPage*> pages_;
	EnumeratorContainer<std::vector<TabPage*>, TabPage*> container_;
	void tabPageChange( ItemEvent* e );
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:20  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2005/01/01 20:31:07  ddiego
*made an adjustment to quitting and event loop, and added some changes to the DefaultTabModel.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/19 04:08:52  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.4  2004/07/17 17:56:24  ddiego
*minor mods to the TableControl and the TabbedPages control
*so that drawing updates get drawn better, and we don't have weird missing
*artifacts.
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
*Revision 1.13.2.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.13  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.2.2  2004/02/12 14:39:01  marcelloptr
*added member function getItemIndex
*
*Revision 1.12  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.3  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.11.4.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.11.4.1  2003/08/22 16:34:35  ddiego
*fixed a mistake in the tabbed pages modle and item
*
*Revision 1.11  2003/05/17 20:37:02  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:09:31  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.14.1  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.9  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/04/27 15:42:08  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.8.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTTABMODEL_H__



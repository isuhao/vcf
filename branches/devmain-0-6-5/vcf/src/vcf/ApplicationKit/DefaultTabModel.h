#if     _MSC_VER > 1000
#pragma once
#endif



#ifndef _VCF_DEFAULTTABMODEL_H__
#define _VCF_DEFAULTTABMODEL_H__


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
class APPKIT_API DefaultTabModel : public TabModel {
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
protected:
	std::vector<TabPage*> pages_;
	EnumeratorContainer<std::vector<TabPage*>, TabPage*> container_;
	void tabPageChange( ItemEvent* e );
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
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



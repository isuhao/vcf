#if     _MSC_VER > 1000
#pragma once
#endif


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

#ifndef _VCF_MENUITEM_H__
#define _VCF_MENUITEM_H__




namespace VCF 
{

class MenuItemPeer;

class MenuItemListener;

class Menu;

class AcceleratorKey;

#define MENUITEM_CLASSID		"1E8CBE22-2915-11d4-8E88-00207811CFAB"

class APPKIT_API MenuItem : public Item {
public:


	MenuItem(){
		
	};

	virtual ~MenuItem(){};

	virtual void addMenuItemClickedHandler( EventHandler* handler ) = 0;

	virtual void removeMenuItemClickedHandler( EventHandler* handler ) = 0;

	virtual void addMenuItemUpdateHandler( EventHandler* handler ) = 0;

	virtual void removeMenuItemUpdateHandler( EventHandler* handler ) = 0;	

	virtual Enumerator<MenuItem*>* getChildren() = 0;	

	virtual void addChild( MenuItem* child ) = 0;

	virtual void insertChild( const unsigned long& index, MenuItem* child ) = 0;
	
	virtual void deleteChild( MenuItem* child ) = 0;

	virtual void deleteChild( const unsigned long& index ) = 0;

	virtual void clearChildren() = 0;

	virtual bool isChecked() = 0;

	virtual void setChecked( const bool& checked ) = 0;

	virtual bool hasParent() = 0;

	virtual bool hasChildren() = 0;

	virtual unsigned long getChildCount() = 0;

	/**
	*returns the owner of the menu item. This generally
	is either a MenuBar or a PopupMenu
	*/
	virtual Menu* getMenuOwner() = 0;

	/**
	*sets the Owner for the MenuItem and for all it's children as 
	*well
	*/
	virtual void setMenuOwner( Menu* menuOwner ) = 0;

	virtual MenuItem* getParent() = 0;

	virtual void setParent( MenuItem* parent ) = 0;

	virtual MenuItem* getChildAt( const unsigned long& index ) = 0;

	virtual bool isEnabled() = 0;

	virtual void setEnabled( const bool& enabled ) = 0;

	virtual bool isVisible() = 0;

	virtual void setVisible( const bool& visible ) = 0;

	virtual bool getRadioItem() = 0;

	virtual void setRadioItem( const bool& value ) = 0;

	virtual void setCaption( const String& caption ) = 0;
	
	virtual String getCaption() = 0;

	virtual MenuItemPeer* getPeer() = 0;

	virtual bool isSeparator() = 0;

	virtual void setSeparator( const bool& separator ) = 0;
	
	virtual void click() = 0;

	virtual void update() = 0;

	virtual void setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask ) = 0;

	virtual void addAcceleratorKey( AcceleratorKey* accelerator ) = 0;

	virtual AcceleratorKey* getAccelerator() = 0;
};

};



/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.13.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.13  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.3  2003/10/17 21:22:54  ddiego
*added menu item child count function
*fixed a selection glitch in tree list control
*
*Revision 1.12.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.12.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.12  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.2.2  2002/12/27 23:04:32  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10.2.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.10  2002/11/18 00:46:07  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.9.16.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.9  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/

#endif // _VCF_MENUITEM_H__



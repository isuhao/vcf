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

//DefaultPropertyEditors.h

#ifndef _VCF_DEFAULTPROPERTYEDITORS_H__
#define _VCF_DEFAULTPROPERTYEDITORS_H__

#ifndef _VCF_PANEL_H__
#	include "vcf/ApplicationKit/Panel.h"
#endif // _VCF_PANEL_H__

namespace VCF
{

class Control;

class ItemEvent;




class APPKIT_API IntegerPropertyEditor : public AbstractPropertyEditor {
public:
	IntegerPropertyEditor(){};

	virtual ~IntegerPropertyEditor(){};	

private:
	
};


class APPKIT_API DoublePropertyEditor : public AbstractPropertyEditor {
public:
	DoublePropertyEditor(){};

	virtual ~DoublePropertyEditor(){};	

private:
	
};

class APPKIT_API StringPropertyEditor : public AbstractPropertyEditor {
public:
	StringPropertyEditor(){};

	virtual ~StringPropertyEditor(){};	

private:
	
};


class ComboBoxControl;

class APPKIT_API BoolPropertyEditor : public AbstractPropertyEditor {
public:
	BoolPropertyEditor();

	virtual ~BoolPropertyEditor();	

	virtual bool hasCustomEditor(){
		return true;	
	};

	virtual Control* getCustomEditor();

	void onSelectionChange( ItemEvent* event );
private:
	ComboBoxControl* combo_;
	ItemEventHandler<BoolPropertyEditor>* comboBoxHandler_;
};

class APPKIT_API EnumPropertyEditor : public AbstractPropertyEditor{
public:
	EnumPropertyEditor();

	virtual ~EnumPropertyEditor();
	
	virtual bool hasCustomEditor(){
		return true;	
	};

	virtual Control* getCustomEditor();

	void onSelectionChange( ItemEvent* event );
private:
	ComboBoxControl* combo_;
	ItemEventHandler<EnumPropertyEditor>* comboBoxHandler_;
};



class APPKIT_API ColorPropertyEditor : public AbstractPropertyEditor {
public:
	ColorPropertyEditor();

	virtual ~ColorPropertyEditor();
	
	virtual bool hasCustomEditor(){
		return true;	
	};

	virtual bool canPaintValue(){
		return true;
	}

	virtual void paintValue( GraphicsContext* context, const Rect& bounds );

	virtual Control* getCustomEditor();

	void showColorEditor( VariantData* data );
private:
	
};

class APPKIT_API FontPropertyEditor : public AbstractPropertyEditor {
public:
	FontPropertyEditor();

	virtual ~FontPropertyEditor();
	
	virtual bool hasCustomEditor(){
		return true;	
	};

	virtual bool canPaintValue(){
		return true;
	}

	virtual void paintValue( GraphicsContext* context, const Rect& bounds );

	virtual Control* getCustomEditor();

	void showFontEditor( VariantData* data );
private:
	
};


class APPKIT_API DefaultMenuItemPropertyEditor : public AbstractPropertyEditor {
public:
	DefaultMenuItemPropertyEditor();

	virtual ~DefaultMenuItemPropertyEditor();
	
	virtual bool hasCustomEditor(){
		return true;	
	};	

	virtual Control* getCustomEditor();

	void showDefaultMenuItemEditor( VariantData* data );
private:
	
};

class APPKIT_API DefaultListModelPropertyEditor : public AbstractPropertyEditor {
public:
	DefaultListModelPropertyEditor();

	virtual ~DefaultListModelPropertyEditor();
	
	virtual bool hasCustomEditor(){
		return true;	
	};	

	virtual Control* getCustomEditor();

	void showDefaultListModelEditor( VariantData* data );
private:
	
};




template <class T> class ModalPropertyEditorControl : public Panel {
public:
	typedef void (T::*ShowEditorDialog)( VariantData* data );

	ModalPropertyEditorControl( ShowEditorDialog showEditorMethod, VariantData* data, T* source ){
		showEditorMethod_ = showEditorMethod;
		data_ = data;
		source_ = source;

		CommandButton* btn = new CommandButton();
		
		ButtonEventHandler<ModalPropertyEditorControl>* handler = 
			new ButtonEventHandler<ModalPropertyEditorControl>( this, &ModalPropertyEditorControl<T>::onBtnClick, "ButtonClickHandler"  );
		
		btn->addButtonClickHandler( handler );	

		btn->setBounds( &Rect(0,0,16,16) );
		btn->setCaption( "..." );
		this->add( btn, AlignRight );		
		
		this->setColor( Color::getColor("white") );
		this->setBorder( NULL );
	}

	virtual ~ModalPropertyEditorControl(){};	

	void onBtnClick( ButtonEvent* event ){
		(source_->*showEditorMethod_)( data_ );
	}		
private:
	ShowEditorDialog showEditorMethod_;
	VariantData* data_;
	T* source_;
};


};

/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.17.4.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.17  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.16.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.16  2003/08/09 02:56:42  ddiego
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
*Revision 1.15.2.1  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.15  2003/05/17 20:37:02  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.14.2.1  2003/03/12 03:09:31  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.14.2  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.13.14.1  2002/12/25 22:06:19  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.13  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/04/27 15:42:07  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.12.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.12  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTPROPERTYEDITORS_H__



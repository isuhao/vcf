/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.7.8.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.1  2003/03/12 03:11:08  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
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

// Win32ComboBox.h

#ifndef _VCF_WIN32COMBOBOX_H__
#define _VCF_WIN32COMBOBOX_H__


namespace VCF
{

class ComboBoxControl;

class APPKIT_API Win32ComboBox  : public AbstractWin32Component, public ComboBoxPeer
{
public:
	Win32ComboBox( ComboBoxControl* component );

	virtual ~Win32ComboBox();

	/**
     * returns a ID that identifies this control. On Win32 this corresponds to an HWND. 
     */
    virtual long getHandleID(){
		return AbstractWin32Component::getHandleID();	
	};

    /**
     * returns a text associated with the component. This usually gets used in the Component::getCaption() method. 
     */
    virtual VCF::String getText(){
		return AbstractWin32Component::getText();	
	};

    /**
     * sets the text for the widget 
     */
    virtual void setText( const VCF::String& text ){
		AbstractWin32Component::setText( text );		
	};

    /**
     * sets the bounds for the component. Bounds are specified in the coordinate system of the componenents parent. 
     */
    virtual void setBounds( VCF::Rect* rect );

    /**
     * returns the bounds of the component in the coordinate system of the parent. 
     */
    virtual VCF::Rect* getBounds(){
		return AbstractWin32Component::getBounds();	
	};

    /**
     * shows or hides the component. 
     * This does NOT close the component (if invoked on a frame based component ). 
     */
    virtual void setVisible( const bool& visible ){
		AbstractWin32Component::setVisible( visible );	
	};

    /**
     * returns wether or not the component is currently visible. 
     */
    virtual bool getVisible(){
		return AbstractWin32Component::getVisible();	
	};

    /**
     * returns a bit-masked unsigned long that contains style constants. 
     *  These style constants are defined in the VCF, and must 
     * be translated to the particular windowing system being used. 
     */
    virtual unsigned long getStyleMask(){
		return AbstractWin32Component::getStyleMask();	
	};

    /**
     * sets the current style mask.
     *  Should cause a repaint of the component, if neccessary. 
     */
    virtual void setStyleMask( const unsigned long& styleMask ){
		AbstractWin32Component::setStyleMask( styleMask );	
	};

    /**
     * returns the component that this Peer is attached to. 
     */
    virtual VCF::Control* getControl(){
		return AbstractWin32Component::getControl();	
	};

    /**
     * attahces the Peer to a particular component. This should only be done once. 
     */
    virtual void setControl( VCF::Control* component ){
		AbstractWin32Component::setControl( component );	
	};

    virtual void setParent( VCF::Control* parent ){
		AbstractWin32Component::setParent( parent );	
	};

	virtual VCF::Control* getParent(){
		return AbstractWin32Component::getParent();	
	};

	virtual bool isFocused(){
		return AbstractWin32Component::isFocused();	
	};

	virtual void setFocus( const bool& focused ){
		AbstractWin32Component::setFocus( focused );
	};

	virtual bool isEnabled(){
		return AbstractWin32Component::isEnabled();	
	};

	virtual void setEnabled( const bool& enabled ){
		AbstractWin32Component::setEnabled( enabled );	
	};

	virtual void addItem( ListItem * item );

    virtual void insertItem( const unsigned long& index, ListItem * item );

	virtual void createParams();

	virtual LRESULT handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, WNDPROC defaultWndProc = NULL);

	virtual void setFont( Font* font ){
		AbstractWin32Component::setFont( font );	
	};

	virtual void repaint( Rect* repaintRect=NULL ){
		AbstractWin32Component::repaint(repaintRect);
	};

	virtual void keepMouseEvents(){
		AbstractWin32Component::keepMouseEvents();
	}
	
	virtual void releaseMouseEvents(){
		AbstractWin32Component::releaseMouseEvents();
	};
private:
	
	WNDPROC oldComboBoxWndProc_;
};


};
#endif // _VCF_WIN32COMBOBOX_H__



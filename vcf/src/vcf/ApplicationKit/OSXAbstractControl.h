

#ifndef _VCF_OSXABSTRACTCONTROL_H__
#define _VCF_OSXABSTRACTCONTROL_H__

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




/*


namespace VCF {

class OSXAbstractControl : public Object, public ControlPeer { 
public:

	OSXAbstractControl();

	virtual ~OSXAbstractControl();

	virtual long getHandleID() {
		return (long)controlRef_;
	}

	virtual void create( Control* owningControl );
	
	virtual void destroyControl();
	
    virtual String getText();

    virtual void setText( const String& text );

    virtual void setBounds( Rect* rect );

	virtual bool beginSetBounds( const ulong32& numberOfChildren );

	virtual void endSetBounds();

    virtual Rect getBounds();

    virtual void setVisible( const bool& visible );

    virtual bool getVisible();

    virtual Control* getControl();

    virtual void setControl( Control* component );    

    virtual void setCursor( Cursor* cursor );    
	
	virtual void setParent( Control* parent );

	virtual Control* getParent();

	virtual bool isFocused();

	virtual void setFocused();

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void setFont( Font* font );

	virtual void repaint( Rect* repaintRect=NULL );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();
	
	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );	

	static OSXAbstractControl* getOSXControlFromControlRef( ControlRef controlRef );	

	Rect internal_getBounds() {
		return bounds_;
	}

	void internal_setBounds( const Rect& bounds ) {
		bounds_ = bounds;
	}
protected:
	
	typedef std::map<ControlRef,OSXAbstractControl*> OSXControlMap;

	static void registerOSXControl( OSXAbstractControl* gtkControl );	
	static void unRegisterOSXControl( OSXAbstractControl* gtkControl );	

	static OSXControlMap gtkControlMap;

	OSXAbstractControl* parent_;
	bool enabled_;

	ControlRef controlRef_;
	Control* control_;

	Rect bounds_;

	bool repainted_;

};


}; //end of namespace VCF
*/

/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*/


#endif // _VCF_OSXABSTRACTCONTROL_H__



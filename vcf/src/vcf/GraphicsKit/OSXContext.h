#ifndef _VCF_OSXCONTEXT_H__
#define _VCF_OSXCONTEXT_H__
//OSXContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class GraphicsContext;

class OSXGCRef {
public:
	OSXGCRef(): cgRef(NULL),destroyCGRef(false){}
	
	OSXGCRef( CGContextRef p1, const Rect& p2 ): cgRef(p1),rect(p2),destroyCGRef(false){}
	OSXGCRef( CGContextRef p1, NSRect p2 ): cgRef(p1),destroyCGRef(false){
		rect.left_ = p2.origin.x;
		rect.top_ = p2.origin.y;
		rect.right_ = p2.origin.y + p2.size.width;
		rect.bottom_ = p2.origin.y + p2.size.height;
	}
	CGContextRef cgRef;
	Rect rect;
	
	bool destroyCGRef;
	
	operator CGContextRef() const {
		return cgRef;
	}
};


class OSXContext  : public ContextPeer, public HeapObject {
public:

	
	enum LastPrimitive{
		lpNone, 
		lpMove, 
		lpLine
	};


	OSXContext();
	
	/**
	Creates a new HDC from scratch
	*/
	OSXContext( const uint32& width, const uint32& height );

	/**
	conextID MUST be a pointer to a OSXGCRef instance (which in 
	turn can be on the stack, so long as it has valid values
	*/
	OSXContext( OSHandleID contextID );

	virtual ~OSXContext();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();
	
	virtual OSHandleID getContextID();

	/**
	handle/contextID MUST be a pointer to a OSXGCRef instance (which in 
	turn can be on the stack, so long as it has valid values
	*/
	virtual void setContextID( OSHandleID handle );

	virtual void textAt( const Rect& bounds, const String & text, const int32& drawOptions=0 );

	virtual double getTextWidth( const String& text );

	virtual double getTextHeight( const String& text );

    virtual void rectangle(const double & x1, const double & y1, const double & x2, const double & y2);

	virtual void roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
							 const double & xc, const double & yc);

    virtual void ellipse(const double & x1, const double & y1, const double & x2, const double & y2 );

	virtual void arc(const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
						 const double & y3, const double & x4, const double & y4);

    virtual void polyline(const std::vector<Point>& pts);

    virtual void curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4);

    virtual void lineTo(const double & x, const double & y);
    
  	virtual void closePath();

    virtual void moveTo(const double & x, const double & y);

	void init();

	virtual void setOrigin( const double& x, const double& y );

	virtual Point getOrigin();

	virtual void copyContext( const Rect& sourceRect,
								const Rect& destRect,
								ContextPeer* sourceContext );

	virtual bool isMemoryContext();

	virtual bool prepareForDrawing( int32 drawingOperation );

	virtual void finishedDrawing( int32 drawingOperation );

	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode );
	
	virtual void bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image );

	virtual void checkHandle();

	virtual void releaseHandle();

	virtual bool isXORModeOn();

	virtual void setXORModeOn( const bool& XORModeOn );

	virtual bool isAntiAliasingOn() {
		return antialiasingOn_;
	}
	
	virtual void setAntiAliasingOn( bool antiAliasingOn );
	
	virtual void setTextAlignment( const bool& alignTobaseline );

	virtual bool isTextAlignedToBaseline();

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );
	
	
	
	virtual void drawThemeSelectionRect( Rect* rect, DrawUIState& state );
	
	virtual void drawThemeFocusRect( Rect* rect, DrawUIState& state );

	virtual void drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect=NULL );
	
	virtual void drawThemeButtonFocusRect( Rect* rect );

	virtual void drawThemeCheckboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeRadioButtonRect( Rect* rect, ButtonState& state );
	
	virtual void drawThemeComboboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state );

	virtual void drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state );

	virtual void drawThemeTab( Rect* rect, TabState& state );

	virtual void drawThemeTabPage( Rect* rect, DrawUIState& state );
	
	virtual void drawThemeTabContent( Rect* rect, DrawUIState& state );

	virtual void drawThemeTickMarks( Rect* rect, SliderState& state );

	virtual void drawThemeSlider( Rect* rect, SliderState& state );
	
	virtual void drawThemeProgress( Rect* rect, ProgressState& state );	
	
	virtual void drawThemeImage( Rect* rect, Image* image, DrawUIState& state );

	virtual void drawThemeHeader( Rect* rect, ButtonState& state );

	virtual void drawThemeEdge( Rect* rect, DrawUIState& state, const int32& edgeSides, const int32& edgeStyle );

	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	virtual void drawThemeBackground( Rect* rect, BackgroundState& state );

	virtual void drawThemeMenuItem( Rect* rect, MenuState& state );
	
	virtual void drawThemeMenuItemText( Rect* rect, MenuState& state );

	virtual void drawThemeText( Rect* rect, TextState& state );
	
	virtual void drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex );
	
	virtual void drawThemeBorder( Rect* rect, DrawUIState& state );
	//void setCGContext( CGContextRef cgRef, const Rect& ownerRect  );
	//void setPortFromImage( GrafPtr port, uint32 width, uint32 height );
	
	
	CGContextRef getCGContext() {
		return contextRef_.cgRef;
	}
	
protected:
	OSXGCRef contextRef_;
    uint32 imgWidth_;
    uint32 imgHeight_;
	GraphicsContext* context_;
	int32 currentDrawingOperation_;
	ATSUTextLayout textLayout_;
	VCF::Point origin_;
    bool xorModeOn_;
	LastPrimitive lastPrimitive_;
	VCF::Point lastPrimitiveP1_;
	VCF::Point lastPrimitiveV1_;
	bool antialiasingOn_;




	void atsuDrawTextInBox(	const VCF::Rect& rect, const int32& drawOptions );

	double getLayoutWidth( ATSUTextLayout layout );

	void setLayoutWidth( ATSUTextLayout layout, double width );
	VCF::Size getLayoutDimensions( const String& text );
	
	void endLastPrimitive();
	void finishLastPrimitive(const double & x, const double & y);
};

}; //end of namespace VCF


#endif // _VCF_OSXCONTEXT_H__

/**
$Id$
*/

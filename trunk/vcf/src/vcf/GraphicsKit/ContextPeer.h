#ifndef _VCF_CONTEXTPEER_H__
#define _VCF_CONTEXTPEER_H__
//ContextPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


namespace VCF{

class Path;
class Font;
class Point;
class Image;
class GraphicsContext;
class DrawUIState;
class MenuState;
class ButtonState;
class DisclosureButtonState;
class ProgressState ;
class SliderState;
class ScrollBarState;
class TabState;
class BackgroundState;
class TextState;

/**
\class ContextPeer ContextPeer.h "vcf/GraphicsKit/ContextPeer.h"
*The ContextPeer serves as a platform neutral interface
*for a set of standard drawing methods that should provide
*the following functionality:
*<ul>
*	<li>A base set of 2D drawing primitives, like lines, ellipse,
*		rectangles, etc.
*	<li>The ability to specify line width, line color, and simple line patterns
*	<li>The ability to fill or stroke the various graphics primitives
*	<li>Basic text functions
*	<li>a set of utility methods for drawing common UI shapes, like a
*		selection rectangle, tab, scroll buttons, or a 3D button frame, etc. These may be
*		drawn differently depending on the underlying windowing system
*</ul>
*/
class GRAPHICSKIT_API ContextPeer {
public:

	virtual ~ContextPeer(){};

	virtual void setContext( GraphicsContext* context ) = 0;

	virtual GraphicsContext* getContext() = 0;

	virtual OSHandleID getContextID() = 0;

	virtual void setContextID( OSHandleID contextID ) = 0;

	/**
	this method is called for the peer to initialize any graphics resources
	before calling the following methods:
	<ul>
		<li>textAt</li>
		<li>getTextWidth</li>
		<li>getTextHeight</li>
		<li>rectangle</li>
		<li>ellipse</li>
		<li>arc</li>
		<li>polyline</li>
		<li>curve</li>
		<li>moveTo</li>
		<li>lineTo</li>
	</ul>
	Since the drawing primitives like (rectangle, moveTo, etc) are executed as a series
	of operations by the GraphicsContext, this means that prepareForDrawing() will
	get called as part of the GraphicsContext::fillPath(), GraphicsContext::strokePath(),
	or GraphicsContext::textAtXXX() methods. prepareForDrawing() will be called <i>prior</i>
	to any of the drawing primitive functions in the above list, allowing the peer to initialize
	whatever graphics resources need to be as specified by the GraphicsContext.
	*/
	virtual bool prepareForDrawing( int32 drawingOperation ) = 0;

	virtual void finishedDrawing( int32 drawingOperation ) = 0;

	/**
	*sets the current clipping path to be used for the duration of the Contexts lifetime or
	*until it has been changed
	*/
	virtual void setClippingPath( Path* clippingPath ) = 0;

	virtual void setClippingRect( Rect* clipRect ) = 0;

	/**
	* this is used to determine how to align text
	* when the windowing systems draws it.
	* Currently the choices are 2:
	*  either it is aligned to the top, or in other
	*  words the coordinates specified represent the
	*  top, left position to start rendering the text,
	* or
	*  aligned to the baseline, in which the top,
	*  left coordinates represent the baseline point of
	*  origin. The latter setting is useful when
	*  drawing text whith different font styles.
	*/
	virtual void setTextAlignment( const bool& alignTobaseline ) = 0;

	virtual bool isTextAlignedToBaseline() = 0;

	virtual void textAt( const Rect& bounds, const String & text, const int32& drawOptions=0 ) = 0;

	virtual double getTextWidth( const String& text ) = 0;

	virtual double getTextHeight( const String& text ) = 0;

	virtual void rectangle( const double & x1, const double & y1,
								const double & x2, const double & y2 ) = 0;

	virtual void roundRect( const double & x1, const double & y1,
								const double & x2, const double & y2,
								const double & xc, const double & yc ) = 0;

	virtual void ellipse( const double & x1, const double & y1,
							const double & x2, const double & y2 ) = 0;

	virtual void arc( const double & x1, const double & y1,
						const double & x2, const double & y2,
						const double & x3, const double & y3,
						const double & x4, const double & y4 ) = 0;

    virtual void polyline( const std::vector<Point>& pts ) = 0;

	virtual void curve( const double & x1, const double & y1, const double & x2, const double & y2,
                        const double & x3, const double & y3, const double & x4, const double & y4 ) = 0;

	virtual void moveTo( const double & x, const double & y ) = 0;

	virtual void lineTo( const double & x, const double & y ) = 0;

	virtual void closePath() = 0;

	virtual void setOrigin( const double& x, const double& y ) = 0;

 	virtual Point getOrigin() = 0;

	virtual void copyContext( const Rect& sourceRect,
								const Rect& destRect,
								ContextPeer* sourceContext ) = 0;

	/**
	*is this context Peer in memory or does it associated with a
	*component ?
	*@return bool true if the context is on memory, otherwise false
	*/
	virtual bool isMemoryContext() = 0;

	virtual Image::ImageType getMemoryCtxImageType() = 0;

	virtual void attachToRenderBuffer( agg::rendering_buffer& renderBuffer ) = 0;

	virtual void resizeMemoryContext( const uint32& newWidth, const uint32& newHeight ) = 0;

	virtual bool isAntiAliasingOn() = 0;

	virtual void setAntiAliasingOn( bool antiAliasingOn ) = 0;

	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode ) = 0;

	/**
	"Blits" the image to the underlying graphics context. No attempt is 
	made to transform the image. The image is blitted to the coordinates 
	specified by the x and y arguments, and the image's width and height 
	are used to determine the bounds.
	*/
	virtual void bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image ) = 0;


	virtual void drawThemeSelectionRect( Rect* rect, DrawUIState& state ) = 0;

	/**
	Draws a focus rect, which is an inverted gray dotted line around the rect.
	*/
	virtual void drawThemeFocusRect( Rect* rect, DrawUIState& state ) = 0;

	/**
	Draws a button's background, the border, and its caption.
	*/
	virtual void drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect=NULL ) = 0;

	/**
	Similar to drawThemeFocusRect, but dimension of the focus rect is chosen by the peer.
	*/
	virtual void drawThemeButtonFocusRect( Rect* rect ) = 0;

	virtual void drawThemeCheckboxRect( Rect* rect, ButtonState& state ) = 0;

	virtual void drawThemeRadioButtonRect( Rect* rect, ButtonState& state ) = 0;

	virtual void drawThemeComboboxRect( Rect* rect, ButtonState& state ) = 0;

	virtual void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state ) = 0;

	/**
	Draws a button that is used to open up more details, for example
	the button that opens up a tree node to reveal it's children, that is compliant
	with the native windowing systems default look and feel.
	On Win32 this is usually represented by the "+" and "-" look as found on
	the tree controls, while on OSX it is the little triangles
	*/
	virtual void drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state ) = 0;

	/**
	Draws a tab, the part of the TabbedPages control that acts like a
	little button to activate a page, that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeTab( Rect* rect, TabState& state ) = 0;

	/**
	Draws a tab page - the page on which other controls for the page are
	parented to, that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeTabPage( Rect* rect, DrawUIState& state ) = 0;

	virtual void drawThemeTabContent( Rect* rect, DrawUIState& state ) = 0;

	virtual void drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex ) = 0;

	/**
	Draws a tick mark, like that used for a slider control, that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeTickMarks( Rect* rect, SliderState& state ) = 0;

	/**
	Draws a slider control, like that used for a slider control, that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeSlider( Rect* rect, SliderState& state ) = 0;

	/**
	Draws a progress bar control, that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeProgress( Rect* rect, ProgressState& state ) = 0;

	virtual void drawThemeImage( Rect* rect, Image* image, DrawUIState& state ) = 0;

	/**
	Draws a header control that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeHeader( Rect* rect, ButtonState& state ) = 0;

	/**
	draws edges, useful for separators, that is compliant
	with the native windowing systems default look and feel.
	use a mask or 1 or more values of type ContextPeer::EdgeType
	to indicate which sides of the rect to draw an edge on
	*/
	virtual void drawThemeEdge( Rect* rect, DrawUIState& state, const int32& edgeSides, const int32& edgeStyle ) = 0;

	virtual void drawThemeBorder( Rect* rect, DrawUIState& state ) = 0;

	/**
	Draws a size gripper for resizing a control/window that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state ) = 0;

	/**
	Draws a them compliant background
	*/
	virtual void drawThemeBackground( Rect* rect, BackgroundState& state ) = 0;

	/**
	Draws the background appropriate for a menu item that is compliant
	with the native windowing systems default look and feel.
	This is typically called first by a menu item to give it a standard
	look and feel in it's background before drawing any thing else
	*/
	virtual void drawThemeMenuItem( Rect* rect, MenuState& state ) = 0;

	virtual void drawThemeMenuItemText( Rect* rect, MenuState& state ) = 0;

	virtual void drawThemeText( Rect* rect, TextState& state ) = 0;

};

};


#endif // _VCF_CONTEXTPEER_H__

/**
$Id$
*/

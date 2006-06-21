#ifndef _VCF_XCBGRAPHICSTOOLKIT_H__
#define _VCF_XCBGRAPHICSTOOLKIT_H__


/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF  {

class XCBFontPeer;

/**
*Class XCBGraphicsToolkit documentation
*/
class XCBGraphicsToolkit : public GraphicsToolkit {
public:

	XCBGraphicsToolkit();
	virtual ~XCBGraphicsToolkit();

	static XCBConnection* getConnection();
	static XCBSCREEN*     getScreen();
	static FcPattern* getFontPatternForFont( XCBFontPeer* fontPeer );
protected:
	virtual ContextPeer* internal_createContextPeer( const unsigned long& width, const unsigned long& height );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual FontPeer* internal_createFontPeer( const String& fontName );

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize );

	virtual Image* internal_createImage( const unsigned long& width, const unsigned long& height, const Image::ImageType& imageType );

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType );

	virtual PrintSessionPeer* internal_createPrintSessionPeer();

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer();

	virtual double internal_getDPI( GraphicsContext* context );

	virtual void internal_systemSettingsChanged();

private:
	XCBConnection *connection_;
	XCBSCREEN     *screen_;
	std::map<String,FcPattern*> fontPatternCache_;
};

}; //end of namespace VCF

#endif // _VCF_XCBGRAPHICSTOOLKIT_H__

/**
$Id$
*/


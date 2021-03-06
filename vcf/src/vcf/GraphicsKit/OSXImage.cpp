//OSXImage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

OSXImage::OSXImage():
    AbstractImage(true),//note: we allocate the memory for the ImageBits pixels
    imageCGRef_(0)
{
    init();
}

OSXImage::OSXImage( const uint32& width, const uint32& height ):
    AbstractImage(true),//note: we allocate the memory for the ImageBits pixels
    imageCGRef_(0)
{
    init();
    setSize( width, height );
}

OSXImage::OSXImage( GraphicsContext* context, Rect* rect ):
    AbstractImage(true),//note: we allocate the memory for the ImageBits pixels
    imageCGRef_(0)
{
    init();
    setSize( (uint32)rect->getWidth(), (uint32)rect->getHeight() );
    context_->copyContext( Rect(0,0,getWidth(),getHeight()), *rect, context );
}

OSXImage::OSXImage( CFURLRef url, const String& ext ):
    AbstractImage(true),//note: we allocate the memory for the ImageBits pixels
    imageCGRef_(0)
{

	loadFromURL( url, ext );
}

OSXImage::~OSXImage()
{
    if ( NULL != imageCGRef_ ) {
        CGContextRelease( imageCGRef_ );

        imageCGRef_ = NULL;
    }
}

void OSXImage::init()
{
    SysPixelTypeTraits::setChannelType( flags_, SysPixelTypeTraits::getTraitsChannelType() );
	SysPixelTypeTraits::setChannelSize( flags_, SysPixelTypeTraits::getTraitsChannelSize() );
	SysPixelTypeTraits::setImageType( flags_, SysPixelTypeTraits::getTraitsImageType() );
	SysPixelTypeTraits::setPixelLayoutOrder( flags_, Image::ploRGBA );

    context_ = new GraphicsContext(0);
}

void OSXImage::setAlpha( float val )
{
	uchar alphaVal = (uchar) (val * 255.0);
	
	SysPixelType* bits = (SysPixelType*)dataBuffer_;
	
	uint32 size = getWidth() * getHeight();
	while ( size > 0 ) {
		bits[size-1].a = alphaVal;
		
		size --;
	}
	
	
}

void OSXImage::createBMP()
{
    if ( NULL != imageCGRef_ ) {
        CGContextRelease( imageCGRef_ );
        imageCGRef_ = NULL;
    }

    
    int componentCount = getType();
    int bitsPerPix = getChannelSize() * componentCount;

    int bytesPerRow = (getWidth() * (bitsPerPix/componentCount) * componentCount) / 8;
    uint32 width = getWidth();
    uint32 height = getHeight();

    ::Rect boundsRect;
    boundsRect.left = boundsRect.top = 0;
    boundsRect.right = width;
    boundsRect.bottom = height;

	

    OSStatus err = noErr;
	/*
    err = NewGWorldFromPtr( &newGWorld,
                            k32RGBAPixelFormat,
                            &boundsRect,
                            NULL,
                            NULL,
                            0,
                            (char*)dataBuffer_,
                            bytesPerRow );
							*/
							
	//setAlpha( 0.67 );

    if ( noErr == err ) {
       // uint32 imgSize = width * height * componentCount;
        //CGDataProviderRef provider = CGDataProviderCreateWithData( NULL,
          //                                                          dataBuffer_,
            //                                                        imgSize,
              //                                                      NULL );

        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

        //imageRef_ = CGImageCreate( width,
          //                         height,
            //                       getChannelSize(),
              //                     bitsPerPix,
                //                   bytesPerRow,
                  //                 colorSpace,
                    //               kCGImageAlphaNoneSkipFirst,
                      //             provider,
                        //           NULL,
                          //         FALSE,
                            //       kCGRenderingIntentDefault );
		
		OSXGCRef ref;
		
		imageCGRef_ =
			CGBitmapContextCreate( dataBuffer_,
								width,
								height,
								getChannelSize(),
								bytesPerRow,
								colorSpace,
								kCGImageAlphaPremultipliedLast );
		ref.cgRef = imageCGRef_;
		ref.rect.left_ = 0;
		ref.rect.top_ = 0;
		ref.rect.bottom_ = height;
		ref.rect.right_ = width;
        CGColorSpaceRelease(colorSpace);
        //CGDataProviderRelease(provider);		
		
		OSXContext* peerCtx = (OSXContext*)context_->getPeer();
		peerCtx->setContextID( &ref );
		
    }
    else {
        throw RuntimeException( MAKE_ERROR_MSG_2("OSXImage failed to create a new GWorld!") );
    }
}

CGImageRef OSXImage::createCGImage()
{
	CGImageRef result = 0;
	
	result = CGBitmapContextCreateImage (imageCGRef_);
	
	return result;
}

void OSXImage::setSize( const uint32 & width, const uint32 & height )
{
    AbstractImage::setSize( width, height );
	createBMP();
}

void OSXImage::beginDrawing()
{
	
	
}

void OSXImage::finishedDrawing()
{

}

void OSXImage::loadFromURL( CFURLRef url, const String& ext )
{
	CFRefObject<CFURLRef> urlRef(url);
	CFRefObject<CGDataProviderRef> provider = CGDataProviderCreateWithURL( url );
	String tmp = StringUtils::lowerCase(ext);
	CFRefObject<CGImageRef> urlImage;
	if ( tmp == "png" ) {
		urlImage = CGImageCreateWithPNGDataProvider( provider, NULL, false,  kCGRenderingIntentDefault );														
	}
	else if ( tmp == "jpg" || tmp == "jpeg" ) {
		urlImage = CGImageCreateWithJPEGDataProvider( provider, NULL, false,  kCGRenderingIntentDefault );															
	}
	
	if ( NULL != urlImage ) {
		setSize( CGImageGetWidth(urlImage), CGImageGetHeight(urlImage) );
		

		int componentCount = getType();
		int bitsPerPix = getChannelSize() * componentCount;
		int bytesPerRow = (getWidth() * (bitsPerPix/componentCount) * componentCount) / 8;
		CFRefObject<CGColorSpaceRef> colorSpace = CGColorSpaceCreateDeviceRGB();

		CFRefObject<CGContextRef> imgCtx = CGBitmapContextCreate( dataBuffer_,
														getWidth(),
														getHeight(),
														bitsPerPix,
														bytesPerRow,
														colorSpace,
														kCGImageAlphaNoneSkipFirst );
		
		CGRect r;
		r.origin.x = 0;
		r.origin.x = 0;
		r.size.width = getWidth();
		r.size.height = getHeight();
		CGContextDrawImage( imgCtx, r, urlImage );
	}
}


/**
$Id$
*/

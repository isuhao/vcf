/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 03:40:30  ddiego
*migration towards new directory structure
*
*Revision 1.20  2003/08/09 02:56:45  ddiego
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
*Revision 1.19.2.1  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.19  2003/05/17 20:37:19  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.18.2.3  2003/04/07 03:39:31  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.18.2.2  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.18.2.1  2003/03/12 03:11:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.18  2003/02/26 04:30:45  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.17.8.1  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.17  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.16.6.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.16  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.15.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.15  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.14  2002/01/24 01:46:49  ddiego
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

/* Generated by Together */

#include "vcf/GraphicsKit/GraphicsKit.h"

using namespace VCF;

AbstractImage::AbstractImage( const bool& needsMemAlloc )
{
	imageBits_ = new ImageBits(0,0,needsMemAlloc);
	context_ = NULL;
	isTransparent_ = false;
	width_ = 0;
	height_ = 0;	
}

AbstractImage::~AbstractImage()
{
	delete context_;
	delete imageBits_;
}

void AbstractImage::setSize(const unsigned long & width, const unsigned long & height )
{
	width_ = width;
	height_ = height;
	if ( (width_ > 0) && (height_ > 0) ) {
		imageBits_->allocatePixelMemory( width_, height_ );

		ImageEvent event(this);
		event.setType( IMAGE_EVENT_WIDTH_CHANGED );
		event.setNewWidth( width );
		ImageSizeChanged.fireEvent( &event );

		ImageEvent event2(this);
		event2.setType( IMAGE_EVENT_HEIGHT_CHANGED );
		event2.setNewHeight( height_ );
		ImageSizeChanged.fireEvent( &event2 );
	}
}

unsigned long AbstractImage::getWidth()
{
	return width_;
}


unsigned long AbstractImage::getHeight(){
	return height_;
}

GraphicsContext* AbstractImage::getImageContext()
{
	return context_;
}

ImageBits* AbstractImage::getImageBits()
{
	return imageBits_;
}


void AbstractImage::saveToStream( OutputStream * stream )
{
	long bitDepth = getType() * getChannelSize();

	stream->write( bitDepth );
	
	
	stream->write( (long)height_ );
	stream->write( (long)width_ );		

	char* buffer = (char*)imageBits_->pixels_;
	stream->write( buffer, height_ * width_ * getType() );
	
}

void AbstractImage::loadFromStream( InputStream * stream )
{
	
	long bitDepth;
	stream->read( bitDepth );	

	long height = 0;
	long width = 0;
	stream->read( height );
	stream->read( width );
	setSize( width, height );
	char* buffer = (char*)imageBits_->pixels_;
	stream->read( buffer, height_ * width_ * getType() );
}

Image::ImageType AbstractImage::getType() const 
{
	return ImageBits::Traits::getImageType( flags_ );
}


Image::ImageChannelSize AbstractImage::getChannelSize() const
{
	return ImageBits::Traits::getChannelSize( flags_ );
}	

Image::ImageChannelType AbstractImage::getChannelType() const 
{
	return ImageBits::Traits::getChannelType( flags_ );
}

Image::PixelLayoutOrder AbstractImage::getPixelLayoutOrder() const
{
	return ImageBits::Traits::getPixelLayoutOrder( flags_ );
}

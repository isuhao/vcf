
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
#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"



#define IntToFixed(a)	   ((Fixed)(a) << 16)
#define FixedToInt(a)	   ((int)(a) >> 16)


using namespace VCF;


OSXFont::OSXFont( const String& fontName ):
	fontStyle_(nil),
	attrBold_(FALSE),
	attrItalic_(FALSE),
	attrUnderlined_(FALSE),
    attrFontID_(0)
{
	attrColor_.red = 0;
	attrColor_.green = 0;
	attrColor_.blue = 0;
    attrColor_.alpha = 1.0;
    
	OSStatus err = ATSUCreateStyle (&fontStyle_);
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUCreateStyle failed to create font style!" ) );
	}
	
	attrSize_ = IntToFixed((int)12);
	
	SInt16 iFONDNumber = 0;
    Str255 pStr;
    CopyCStringToPascal( fontName.empty() ? "Arial" : fontName.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
	err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);
	
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed to create font ID instance!" ) );
	}
	
	
	initATSUAttrs();
}
	
OSXFont::OSXFont( const String& fontName, const double& pointSize ):
	fontStyle_(nil),
	attrBold_(FALSE),
	attrItalic_(FALSE),
	attrUnderlined_(FALSE),
    attrFontID_(0)
{
	attrColor_.red = 0;
	attrColor_.green = 0;
	attrColor_.blue = 0;
    attrColor_.alpha = 1.0;
	
	OSStatus err = ATSUCreateStyle (&fontStyle_);
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUCreateStyle failed to create font style!" ) );
	}
	SInt16 iFONDNumber = 0;
    Str255 pStr;
    CopyCStringToPascal( fontName.empty() ? "Arial" : fontName.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
	err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);
	
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed to create font ID instance!" ) );
	}
	
	attrSize_ = IntToFixed((int)pointSize);
	
	initATSUAttrs();
}

void OSXFont::initATSUAttrs()
{
	attrSizes_[OSXFont::attrFontName] = sizeof(ATSUFontID);
	attrSizes_[OSXFont::attrFontSize] = sizeof(Fixed);
	attrSizes_[OSXFont::attrFontBold] = sizeof(Boolean);
	attrSizes_[OSXFont::attrFontItalic] = sizeof(Boolean);
	attrSizes_[OSXFont::attrFontUnderline] = sizeof(Boolean);
	attrSizes_[OSXFont::attrFontColor] = sizeof(ATSURGBAlphaColor);
	
	
	attrValues_[OSXFont::attrFontName] = &attrFontID_;
	attrValues_[OSXFont::attrFontSize] = &attrSize_;
	attrValues_[OSXFont::attrFontBold] = &attrBold_;
	attrValues_[OSXFont::attrFontItalic] = &attrItalic_;
	attrValues_[OSXFont::attrFontUnderline] = &attrUnderlined_;
	attrValues_[OSXFont::attrFontColor] = &attrColor_;
	
	attrTags_[OSXFont::attrFontName] = kATSUFontTag;
	attrTags_[OSXFont::attrFontSize] = kATSUSizeTag;
	attrTags_[OSXFont::attrFontBold] = kATSUQDBoldfaceTag;
	attrTags_[OSXFont::attrFontItalic] = kATSUQDItalicTag;
	attrTags_[OSXFont::attrFontUnderline] = kATSUQDUnderlineTag;
	attrTags_[OSXFont::attrFontColor] = kATSURGBAlphaColorTag;
	
	updateStyleWithAttrs();
}

void OSXFont::updateStyleWithAttrs()
{
	OSStatus err = ATSUSetAttributes (fontStyle_,
											OSXFont::tagCount, 
											attrTags_, 
											attrSizes_, 
											attrValues_);
											
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUSetAttributes failed in updateStyleWithAttrs()") );
	}
}

OSXFont::~OSXFont()
{
	if ( nil != fontStyle_ ) {
		ATSUDisposeStyle( fontStyle_ );
	}
}

void OSXFont::init()
{

}

ulong32 OSXFont::getFontHandleID() 
{
	return (ulong32)fontStyle_;
}

String OSXFont::getName() 
{
	return "FoobarBaz";
}

void OSXFont::setName( const String& name )
{
	SInt16 iFONDNumber = 0;
	Str255 pStr;
    CopyCStringToPascal( name.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
    if ( iFONDNumber != kInvalidFontFamily ) {
        OSStatus err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);
        if ( err != noErr ) {
            throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed - probably due to an invalid font name, or perhaps conversion to a Pascal String failed.") );
        }
    }
	
	updateStyleWithAttrs();
}

void OSXFont::setColor( Color* color )
{
    attrColor_.red = color->getRed();
    attrColor_.green = color->getGreen();
    attrColor_.blue = color->getBlue();
    attrColor_.alpha = 1.0;  
    
    updateStyleWithAttrs();
}

bool OSXFont::isTrueType() 
{
	return true;
}

double OSXFont::getPointSize() 
{
	return (double) FixedToInt(attrSize_);
}

void OSXFont::setPointSize( const double pointSize )
{
	attrSize_ = IntToFixed((int)pointSize);
	
	updateStyleWithAttrs();
}

double OSXFont::getPixelSize() 
{
	return 0.0;
}

void OSXFont::setPixelSize( const double pixelSize )
{

}

void OSXFont::setBold( const bool& bold )
{
	attrBold_ = bold ? TRUE : FALSE;
	
	updateStyleWithAttrs();
}

bool OSXFont::getBold() 
{
	return (attrBold_ == TRUE) ? true : false; 
}

bool OSXFont::getItalic()
{
	return (attrItalic_ == TRUE) ? true : false;
}

void OSXFont::setItalic( const bool& italic )
{
	attrItalic_ = italic ? TRUE : FALSE;
	
	updateStyleWithAttrs();
}

bool OSXFont::getUnderlined() 
{
	return (attrUnderlined_ == TRUE) ? true : false;
}

void OSXFont::setUnderlined( const bool& underlined )
{
	attrUnderlined_ = underlined ? TRUE : FALSE;
	
	updateStyleWithAttrs();
}

bool OSXFont::getStrikeOut()
{
	return false;
}

void OSXFont::setStrikeOut( const bool& strikeout )
{

}

double OSXFont::getShear()
{
	return 0.0;
}

void OSXFont::setShear(const double& shear )
{

}

double OSXFont::getAngle() 
{
	return 0.0;
}

void OSXFont::setAngle( const double& angle )
{

}

void OSXFont::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const double& shear,
								const double& angle, const String& name )
{
	attrBold_ = bold ? TRUE : FALSE;
	attrItalic_ = italic ? TRUE : FALSE;
	attrUnderlined_ = underlined ? TRUE : FALSE;
	
	SInt16 iFONDNumber = 0;
	Str255 pStr;
    CopyCStringToPascal( name.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
	if ( iFONDNumber != kInvalidFontFamily ) {
        OSStatus err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);
        if ( err != noErr ) {
            throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed - probably due to an invalid font name, or perhaps conversion to a Pascal String failed.") );
        }
    }
	
	updateStyleWithAttrs();
}

double OSXFont::getAscent() 
{
	return 0.0;
}

double OSXFont::getDescent()
{
	return 0.0;
}

double OSXFont::getExternalLeading()
{
	return 0.0;
}

double OSXFont::getInternalLeading()
{
	return 0.0;
}

double OSXFont::getHeight()
{
	return 0.0;
}

VCFChar OSXFont::getWordBreakCharacter()
{
	return ' ';
}

VCFChar OSXFont::getFirstCharacter() 
{
	return '\0';
}

VCFChar OSXFont::getLastCharacter()
{
	return '\0';
}

VCF::GlyphCollection* OSXFont::getGlyphCollection( const String& text )
{
	return NULL;
}

bool OSXFont::isEqual( Object* object )
{
	bool result = false;
	OSXFont* fntObj = dynamic_cast<OSXFont*>(object);
	if ( NULL != fntObj ){
		
		if ( (this->attrFontID_ == fntObj->attrFontID_) &&
			 (this->attrBold_ == fntObj->attrBold_) && 
			 (this->attrItalic_ == fntObj->attrItalic_) &&
			 (this->attrUnderlined_ == fntObj->attrUnderlined_) &&
			 (this->attrSize_ == fntObj->attrSize_)  ) {
			result = true;
		}
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.1.2.5  2004/05/31 13:20:58  ddiego
*more osx updates
*
*Revision 1.1.2.4  2004/05/06 03:01:29  ddiego
*checking in OSX updates
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/02/22 06:50:22  ddiego
*more progress with the OSX GraphicsKit - almost done!
*
*Revision 1.1.2.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*/





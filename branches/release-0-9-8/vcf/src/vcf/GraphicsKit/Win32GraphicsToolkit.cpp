//Win32GraphicsToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32GraphicsToolkit.h
#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include <commdlg.h>

#include "vcf/GraphicsKit/PrintSessionPeer.h"
#include "vcf/GraphicsKit/Win32PrintSession.h"
#include "vcf/FoundationKit/ResourceBundle.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/Win32GraphicsResourceBundle.h"

#include "vcf/GraphicsKit/Win32VisualStylesWrapper.h"
#include "vcf/FoundationKit/VFFInputStream.h"


//init singleton
Win32VisualStylesWrapper Win32VisualStylesWrapper::Instance;




using namespace VCF;



class Win32UnitTransformer : public UnitTransformer {
public:
	virtual String transform( const String& s ) {

		const VCFChar* P = s.c_str();
		const VCFChar* start = P;

		String val,unit;

		while ( P-start < s.length() ) {
			if ( *P == '$' ) {
				P++;
				while ( ((*P >= '0') && (*P <= '9')) || ((*P >= 'A') && (*P <= 'F')) || ((*P >= 'a') && (*P <= 'f')) && (P-start < s.length()) ) {
					P++;
				}

				if ( P-start >= s.length() ) {
					return s;
				}

				val.assign( start, ( P - start ) );
				
				unit.assign( P, s.length() - val.length() );

				break;
			}
			else if ( (*P == '-') ||  ((*P >= '0') && (*P <= '9')) ) {
				P++;
				while ( ((*P >= '0') && (*P <= '9')) && (P-start < s.length()) ) {
					P++;
				}

				while ( ((*P >= '0') && (*P <= '9')) || (*P == '.') || (*P == 'e') || (*P == '+') || (*P == '-') && (P-start < s.length()) ) {
					P++;
				}

				if ( P-start >= s.length() ) {
					return s;
				}

				val.assign( start, ( P - start ) );

				unit.assign( P, s.length() - val.length() );

				break;
			}
			P++;
		}
		

		unit = StringUtils::lowerCase(unit);

		if (unit != "px" ) {
			HDC dc = GetDC( ::GetDesktopWindow() );
			
			double dpi = (double)GetDeviceCaps( dc, LOGPIXELSY);
			
			ReleaseDC(::GetDesktopWindow(),dc);
			
			double v = StringUtils::fromStringAsDouble(val);
			
			if (unit == "in" ) {
				val = StringUtils::toString( v * dpi );
			}
			else if (unit == "pt" ) {
				val = StringUtils::toString( (v / 72.0) * dpi );
			}
			else if (unit == "em" ) {
				
			}
			else if (unit == "cm" ) {
				val = StringUtils::toString( (v / 2.54 ) * dpi );
			}
		}

		return val;
	}
};

static Win32UnitTransformer win32Tfrm;


Win32FontManager* Win32FontManager::win32FontMgr = NULL;


Win32GraphicsToolkit::Win32GraphicsToolkit():
	systemFont_(NULL)
{
	Win32FontManager::create();


	loadSystemColors();
	registerImageLoader( "image/bmp", new BMPLoader() );

	initSystemFont();	

	VFFInputStream::setTransformer( &win32Tfrm );
}

Win32GraphicsToolkit::~Win32GraphicsToolkit()
{
	delete systemFont_;
	delete Win32FontManager::getFontManager();
}

void Win32GraphicsToolkit::internal_systemSettingsChanged()
{
	StringUtils::trace( "Win32GraphicsToolkit::internal_systemSettingsChanged()\n" );

	if ( System::isUnicodeEnabled() ) {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTW lf = {0};
		GetObjectW( defGUIFont, sizeof(LOGFONTW), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}
	else {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTA lf = {0};
		GetObjectA( defGUIFont, sizeof(LOGFONTA), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}

	
	systemColorNameMap_->clear();

	std::map<uint32,Color*>::iterator it = systemColors_.begin();
	while ( it != systemColors_.end() ){
		delete it->second;
		it++;
	}
	systemColors_.clear();

	loadSystemColors();
}

void Win32GraphicsToolkit::initSystemFont()
{
	systemFont_ = new Font();

	if ( System::isUnicodeEnabled() ) {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTW lf = {0};
		GetObjectW( defGUIFont, sizeof(LOGFONTW), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}
	else {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTA lf = {0};
		GetObjectA( defGUIFont, sizeof(LOGFONTA), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}


}

ContextPeer* Win32GraphicsToolkit::internal_createContextPeer( OSHandleID contextID )
{
	ContextPeer* result = NULL;

	result = new Win32Context( contextID );

	return result;
}

ContextPeer* Win32GraphicsToolkit::internal_createContextPeer( const uint32& width, const uint32& height )
{
	return new Win32Context( width, height );
}

FontPeer* Win32GraphicsToolkit::internal_createFontPeer( const String& fontName )
{
	return new Win32Font( fontName );
}

FontPeer* Win32GraphicsToolkit::internal_createFontPeer( const String& fontName, const double& pointSize )
{
	return new Win32Font( fontName, pointSize );
}


Image* Win32GraphicsToolkit::internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType )
{
	Image* result = NULL;

	if ( Image::itColor == imageType ) {
		result = new Win32Image( width, height );
	}
	else if ( Image::itGrayscale == imageType ) {
		result = new Win32GrayScaleImage( width, height );
	}

	return result;
}

Image* Win32GraphicsToolkit::internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType )
{
	if ( NULL != context ){
		if ( Image::itColor == imageType ) {
			return new Win32Image( context, rect );
		}
		else if ( Image::itGrayscale == imageType ) {
			return new Win32GrayScaleImage( context, rect );
		}
	}

	return NULL;
}

double Win32GraphicsToolkit::internal_getDPI( GraphicsContext* context )
{
	double result = 0.0;
	if ( NULL == context ) {
		HDC dc = GetDC( ::GetDesktopWindow() );
		result = (double)GetDeviceCaps( dc, LOGPIXELSY);
		ReleaseDC( ::GetDesktopWindow(), dc );
	}
	else {
		result = (double) GetDeviceCaps( (HDC)context->getPeer()->getContextID(), LOGPIXELSY );
	}
	return result;
}

PrintSessionPeer* Win32GraphicsToolkit::internal_createPrintSessionPeer()
{
	return new Win32PrintSession();
}

void Win32GraphicsToolkit::loadSystemColors()
{
	Color* sysColor = NULL;
	sysColor = new Color( ::GetSysColor( COLOR_BTNSHADOW ), Color::cpsABGR );
	systemColors_[SYSCOLOR_SHADOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SHADOW";

	sysColor = new Color( ::GetSysColor( COLOR_3DFACE ), Color::cpsABGR );
	systemColors_[SYSCOLOR_FACE] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_FACE";

	sysColor = new Color( ::GetSysColor( COLOR_3DHILIGHT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_HIGHLIGHT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_HIGHLIGHT";

	sysColor = new Color( ::GetSysColor( COLOR_ACTIVECAPTION ), Color::cpsABGR );
	systemColors_[SYSCOLOR_ACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_CAPTION";

	sysColor = new Color( ::GetSysColor( COLOR_ACTIVEBORDER ), Color::cpsABGR );
	systemColors_[SYSCOLOR_ACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_BORDER";

	sysColor = new Color( ::GetSysColor( COLOR_DESKTOP ), Color::cpsABGR );
	systemColors_[SYSCOLOR_DESKTOP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_DESKTOP";

	sysColor = new Color( ::GetSysColor( COLOR_CAPTIONTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_CAPTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_CAPTION_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_HIGHLIGHT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_SELECTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION";

	sysColor = new Color( ::GetSysColor( COLOR_HIGHLIGHTTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_SELECTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_INACTIVEBORDER ), Color::cpsABGR );
	systemColors_[SYSCOLOR_INACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_BORDER";

	sysColor = new Color( ::GetSysColor( COLOR_INACTIVECAPTION ), Color::cpsABGR );
	systemColors_[SYSCOLOR_INACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_CAPTION";

	sysColor = new Color( ::GetSysColor( COLOR_INFOBK ), Color::cpsABGR );
	systemColors_[SYSCOLOR_TOOLTIP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP";

	sysColor = new Color( ::GetSysColor( COLOR_INFOTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_TOOLTIP_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_MENU ), Color::cpsABGR );
	systemColors_[SYSCOLOR_MENU] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU";

	sysColor = new Color( ::GetSysColor( COLOR_MENUTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_MENU_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_WINDOW ), Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW";

	sysColor = new Color( ::GetSysColor( COLOR_WINDOWTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_WINDOWFRAME ), Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW_FRAME] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_FRAME";

}

GraphicsResourceBundlePeer* Win32GraphicsToolkit::internal_createGraphicsResourceBundlePeer()
{
	return new Win32GraphicsResourceBundle();
}


/**
$Id$
*/

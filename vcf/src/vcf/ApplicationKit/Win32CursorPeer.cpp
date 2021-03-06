//Win32CursorPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32CursorPeer.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32CursorPeer.h"


using namespace VCF;


#define IDC_HAND            MAKEINTRESOURCE(32649)


#define WIDTHBYTES(bits)  (((bits) + 31) / 32 * 4)



Win32CursorPeer::Win32CursorPeer( Cursor* cursor )
{
	isSharedCursor_ = false;
	cursor_ = cursor;
	hCursor_ = NULL;
	cursorID_ = CursorManager::UNREGISTERED_ID;
}

Win32CursorPeer::~Win32CursorPeer()
{
	if ( (NULL != hCursor_) && (false == isSharedCursor_) ) {
		DestroyCursor( hCursor_ );
	}
}

void Win32CursorPeer::createFromResourceName( const String& cursorName, OSHandleID instanceHandle )
{
	HINSTANCE hInst = (HINSTANCE)instanceHandle;
	if ( NULL == hInst ) {
		hInst = GetModuleHandle(NULL);
	}
	isSharedCursor_ = true;
	if ( System::isUnicodeEnabled() ) {
		hCursor_ = LoadCursorW( hInst, cursorName.c_str() );
	}
	else {
		hCursor_ = LoadCursorA( hInst, cursorName.ansi_c_str() );
	}

}

void Win32CursorPeer::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{
	LPCTSTR win32SystemCursor = NULL;
	isSharedCursor_ = true;
	cursorID_ = (int32)systemCursor;
	switch ( systemCursor ) {
		case Cursor::SCT_DEFAULT : {
			win32SystemCursor = IDC_ARROW;
		}
		break;

		case Cursor::SCT_SPLIT_VERT : {
			win32SystemCursor = IDC_SIZEWE;
		}
		break;

		case Cursor::SCT_SPLIT_HORZ : {
			win32SystemCursor = IDC_SIZENS;
		}
		break;

		case Cursor::SCT_SIZE_HORZ : {
			win32SystemCursor = IDC_SIZEWE;
		}
		break;

		case Cursor::SCT_SIZE_VERT : {
			win32SystemCursor = IDC_SIZENS;
		}
		break;

		case Cursor::SCT_SIZE_NE_SW : {
			win32SystemCursor = IDC_SIZENESW;
		}
		break;

		case Cursor::SCT_SIZE_NW_SE : {
			win32SystemCursor = IDC_SIZENWSE;
		}
		break;

		case Cursor::SCT_TEXT : {
			win32SystemCursor = IDC_IBEAM;
		}
		break;

		case Cursor::SCT_HELP : {
			win32SystemCursor = IDC_HELP;
		}
		break;

		case Cursor::SCT_WAIT : {
			win32SystemCursor = IDC_WAIT;
		}
		break;

		case Cursor::SCT_WAITING : {
			win32SystemCursor = IDC_APPSTARTING;
		}
		break;

		case Cursor::SCT_NOWAYHOSER : {
			win32SystemCursor = IDC_NO;
		}
		break;

		case Cursor::SCT_CROSSHAIRS : {
			win32SystemCursor = IDC_CROSS;
		}
		break;

		case Cursor::SCT_POINTING_HAND : {
			win32SystemCursor = IDC_HAND;
		}
		break;


	}

	hCursor_ = LoadCursor(NULL, win32SystemCursor);

}

void Win32CursorPeer::createFromImage( Image* cursorImage, Point* hotSpot )
{
	Win32Image* win32Img = (Win32Image*)cursorImage;
	HBITMAP imgHBMP = win32Img->getBitmap();

	HBITMAP hbmMono = Win32CursorPeer::colorDDBToMonoDDB(imgHBMP, 0, 0, NULL);

	ICONINFO iconInfo;
	memset( &iconInfo, 0, sizeof(ICONINFO) );
	iconInfo.fIcon = FALSE;
	iconInfo.hbmColor = imgHBMP;
	iconInfo.hbmMask = hbmMono;
	iconInfo.xHotspot = (int32)hotSpot->x_;
	iconInfo.yHotspot = (int32)hotSpot->y_;

	hCursor_ = CreateIconIndirect( &iconInfo );

}

WORD Win32CursorPeer::dibNumColors ( void* pv )
{
    int                bits;
    LPBITMAPINFOHEADER lpbi;
    LPBITMAPCOREHEADER lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    // With the BITMAPINFO format headers, the size of the palette is
    // in biClrUsed. In the BITMAPCORE-style headers, it depends on
    // the bits per pixel (2 raised to the power of bits/pixel).

    if (lpbi->biSize != sizeof(BITMAPCOREHEADER))
    {
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else
        bits = lpbc->bcBitCount;

    switch (bits)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		// A 24 bit DIB has no color table
		return 0;
	}
}

WORD Win32CursorPeer::paletteSize( void* pv )
{
    LPBITMAPINFOHEADER lpbi;
    WORD               NumColors;

    lpbi      = (LPBITMAPINFOHEADER)pv;
    NumColors = Win32CursorPeer::dibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return NumColors * sizeof(RGBTRIPLE);
    else
        return NumColors * sizeof(RGBQUAD);
}

HBITMAP Win32CursorPeer::colorDDBToMonoDDB( HBITMAP hbm, DWORD biStyle, WORD biBits, HPALETTE hpal )
{
    BITMAP               bm;
    BITMAPINFOHEADER     bi;
    BITMAPINFOHEADER FAR *lpbi;
    DWORD                dwLen;
    HANDLE               hdib;
    HANDLE               h;
    HDC                  hdc;
    HBITMAP              hbmMono;

    if (!hbm)
        return NULL;

    if (hpal == NULL)
        hpal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

    GetObject(hbm, sizeof(bm), (LPSTR)&bm);

    if (biBits == 0)
        biBits = bm.bmPlanes * bm.bmBitsPixel;

    bi.biSize          = sizeof(BITMAPINFOHEADER);
    bi.biWidth         = bm.bmWidth;
    bi.biHeight        = bm.bmHeight;
    bi.biPlanes        = 1;
    bi.biBitCount      = biBits;
    bi.biCompression   = biStyle;
    bi.biSizeImage     = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed       = 0;
    bi.biClrImportant  = 0;

    dwLen = bi.biSize + Win32CursorPeer::paletteSize(&bi);

    hdc = GetDC(::GetDesktopWindow());
    hpal = SelectPalette(hdc, hpal, FALSE);
    RealizePalette(hdc);

    hdib = GlobalAlloc(GHND, dwLen);

    if (!hdib)
	{
        SelectPalette(hdc, hpal, FALSE);
        ReleaseDC(::GetDesktopWindow(), hdc);
        return NULL;
	}

    lpbi = (BITMAPINFOHEADER *)GlobalLock(hdib);

    *lpbi = bi;

    // Call GetDIBits with a NULL lpBits parameter; it will calculate
    // the biSizeImage field.
    GetDIBits(hdc, hbm, 0, (WORD)bi.biHeight,
        NULL, (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

    bi = *lpbi;
    GlobalUnlock(hdib);

    // If the driver did not fill in the biSizeImage field,
    // calculate it.
    if (bi.biSizeImage == 0)
	{
        bi.biSizeImage = WIDTHBYTES((DWORD)bm.bmWidth * biBits)
            * bm.bmHeight;
        if (biStyle != BI_RGB)
            bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

    // Reallocate the buffer big enough to hold all the bits.
    dwLen = bi.biSize + Win32CursorPeer::paletteSize(&bi) + bi.biSizeImage;
    if ((h = GlobalReAlloc(hdib, dwLen, 0)))
        hdib = h;
    else
	{
        GlobalFree(hdib);
        hdib = NULL;

        SelectPalette(hdc, hpal, FALSE);
        ReleaseDC(::GetDesktopWindow(), hdc);
        return (HBITMAP)hdib;
	}

    // Call GetDIBits with a NON-NULL lpBits parameter, to actually
    // get the bits this time.
    lpbi = (BITMAPINFOHEADER *)GlobalLock(hdib);

    if (GetDIBits(hdc, hbm, 0, (WORD)bi.biHeight,
		(LPSTR)lpbi + (WORD)lpbi->biSize + Win32CursorPeer::paletteSize(lpbi),
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS) == 0)
	{
		GlobalUnlock(hdib);
		hdib = NULL;
		SelectPalette(hdc, hpal, FALSE);
		ReleaseDC(::GetDesktopWindow(), hdc);
		return NULL;
	}

    // Finally, create a monochrome DDB, and put the DIB into it.
    // SetDIBits does smart color conversion.
    hbmMono = CreateBitmap((WORD)lpbi->biWidth, (WORD)lpbi->biHeight,
		1, 1, NULL);
    SetDIBits(hdc, hbmMono, 0, lpbi->biHeight,
		(LPSTR)lpbi + lpbi->biSize + Win32CursorPeer::paletteSize(lpbi),
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

    bi = *lpbi;
    GlobalUnlock(hdib);
    GlobalFree(hdib);

    SelectPalette(hdc, hpal, FALSE);
    ReleaseDC(::GetDesktopWindow(), hdc);
    return hbmMono;

}


/**
$Id$
*/

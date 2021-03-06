//OSXCursorPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXCursorPeer.h"


using namespace VCF;

OSXCursorPeer::OSXCursorPeer( Cursor* cursor ):
	cursorID_(CursorManager::UNREGISTERED_ID),
	cursor_(cursor),
    cursorInst_(nil),
	isSystemCursor_(false)
{
    
}

OSXCursorPeer::~OSXCursorPeer()
{
    if( !isSystemCursor_ ) {
       [cursorInst_ release];
    }
}

void OSXCursorPeer::createFromImage( Image* cursorImage, Point* hotSpot )
{
	if( !isSystemCursor_ && (nil != cursorInst_) ) {
       [cursorInst_ release];
    }
	
	isSystemCursor_ = false;
	cursorID_ = CursorManager::UNREGISTERED_ID;
	NSImage* img = nil;
	NSPoint pt;
	pt.x = hotSpot->x_;
	pt.y = hotSpot->y_;	
	unsigned char* pixPtr = (unsigned char*)cursorImage->getData();
	uint32 sz =  cursorImage->getWidth() * cursorImage->getHeight();
	
	NSData* data = [NSData dataWithBytes:pixPtr length:sz];
	img = [[NSImage alloc] initWithData:data];
	cursorInst_ = [[NSCursor alloc] initWithImage: img hotSpot:pt];
}

void OSXCursorPeer::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{

	cursorID_ = (int32)systemCursor;
	isSystemCursor_ = true;
	switch ( systemCursor ) {
		case Cursor::SCT_DEFAULT : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_SPLIT_VERT : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_SPLIT_HORZ : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_SIZE_HORZ : {
			cursorInst_ = [NSCursor resizeLeftRightCursor];
		}
		break;

		case Cursor::SCT_SIZE_VERT : {
			cursorInst_ = [NSCursor resizeUpDownCursor];
		}
		break;

		case Cursor::SCT_SIZE_NE_SW : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_SIZE_NW_SE : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_TEXT : {
			cursorInst_ = [NSCursor IBeamCursor];
		}
		break;

		case Cursor::SCT_HELP : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_WAIT : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_WAITING : {
//			/cursorID_ = kThemeArrowCursor;    //Wrong mapping
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_NOWAYHOSER : {
			cursorInst_ = [NSCursor arrowCursor];
		}
		break;

		case Cursor::SCT_CROSSHAIRS : {
			cursorInst_ = [NSCursor crosshairCursor];
		}
		break;

		case Cursor::SCT_POINTING_HAND : {
			cursorInst_ = [NSCursor pointingHandCursor];
		}
		break;
	}
}

void OSXCursorPeer::createFromResourceName( const String& cursorName, OSHandleID instanceHandle )
{
	//NSBundle 
}


/**
$Id$
*/

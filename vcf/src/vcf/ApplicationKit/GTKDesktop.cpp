/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/05/17 20:37:32  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.2.1  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKDesktop.h"

using namespace VCF;

GTKDesktop::GTKDesktop( Desktop* desktop )
{

}

GTKDesktop::~GTKDesktop()
{

}


void GTKDesktop::desktopBeginPainting( Rect* clippingRect )
{
	
}

/**
*called after finished painting on the desktop 
*allows for native Windowing system cleanup to happen
*/
void GTKDesktop::desktopEndPainting()
{
	
}

bool GTKDesktop::desktopSupportsVirtualDirectories()
{
	bool result = false;
	
	return result;
}

bool GTKDesktop::desktopHasFileSystemDirectory()
{
	bool result = false;
	
	return result;
}

String GTKDesktop::desktopGetDirectory()
{
	return "";
}

ulong32 GTKDesktop::desktopGetHandleID()
{
	ulong32 result = 0;
	
	result = (ulong32) gdk_get_default_root_window();
	
	return result;
}

ulong32 GTKDesktop::desktopGetGraphicsContextHandleID()
{
	
	return desktopGetHandleID();	
}

void GTKDesktop::desktopSetDesktop( Desktop* desktop )
{
	
}

ulong32 GTKDesktop::desktopGetWidth()
{	
	return gdk_screen_get_width( gdk_screen_get_default() );
}

ulong32 GTKDesktop::desktopGetHeight()
{
	
	return gdk_screen_get_height( gdk_screen_get_default() );
}


Rect GTKDesktop::desktopGetUsableBounds()
{
	Rect result;
	
	result.left_ = 0.0;
	result.top_ = 0.0;
	
	result.right_ = desktopGetWidth();
	result.bottom_ = desktopGetHeight();
	
	return result;
}



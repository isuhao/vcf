/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.16.8.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.16  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.1  2003/03/12 03:12:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.14  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.13.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.13.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.13  2002/01/24 01:46:49  ddiego
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

// Win32ResourceBundle.cpp
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32ResourceBundle.h"


using namespace VCF;


BOOL CALLBACK Win32ResourceBundle_EnumResTypeProc( HMODULE hModule, LPTSTR lpszType, LPARAM lParam );
BOOL CALLBACK Win32ResourceBundle_EnumResNameProc( HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LPARAM lParam );

static bool foundResName = false;
static String foundResType="Hello";

Win32ResourceBundle::Win32ResourceBundle()
{
	appPeer_ = NULL;
}

Win32ResourceBundle::~Win32ResourceBundle()
{
	
}

String Win32ResourceBundle::getString( const String& resourceName )
{	
	String result;
	HRSRC resHandle = NULL;
	if ( System::isUnicodeEnabled() ) {
		resHandle = ::FindResourceW( getResourceInstance(), resourceName.c_str(), String(RT_RCDATA).c_str() );
	}
	else {
		resHandle = ::FindResourceA( getResourceInstance(), resourceName.ansi_c_str(), RT_RCDATA );
	}
	
	if ( NULL != resHandle ){
		HGLOBAL	data = ::LoadResource( NULL, resHandle );
		if ( NULL != data ){
			TCHAR* strData = (TCHAR*)::LockResource( data );
			result = strData;
			::FreeResource( data );
		}
	}
	else {
		//throw exception- resource not found !!!!
	}
	return result;
}

String Win32ResourceBundle::getVFF( const String& resourceName )
{
	String result;
	HRSRC resHandle = NULL;
	if ( System::isUnicodeEnabled() ) {
		resHandle = ::FindResourceW( getResourceInstance(), resourceName.c_str(), L"VFF" );
	}
	else {
		resHandle = ::FindResourceA( getResourceInstance(), resourceName.ansi_c_str(), "VFF" );
	}
	
	if ( NULL != resHandle ){
		HGLOBAL	data = ::LoadResource( NULL, resHandle );
		if ( NULL != data ){
			void* dataPtr = ::LockResource( data );
			TCHAR* strData = (TCHAR*)dataPtr;
			int size = SizeofResource( getResourceInstance(), resHandle );			
			result = strData;
			int resSize = result.size();
			void *tmp = dataPtr;
			/**
			*this is here to properly skip over '\0' characters in the stream
			*/
			while ( resSize < size ){
				tmp = (void*)((char*)dataPtr + resSize + 1);
				strData = (TCHAR*)tmp;
				result += "\n";
				result += strData;
				resSize = result.size();
			}
			::FreeResource( data );
		}
	}
	else {
		//throw exception- resource not found !!!!
	}
	return result;
}

Image* Win32ResourceBundle::getImage( const String& resourceName )
{
	HBITMAP resBMP = NULL;
	if ( System::isUnicodeEnabled() ) {
		resBMP = (HBITMAP)LoadImageW( getResourceInstance(), resourceName.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION ); 
	}
	else {
		resBMP = (HBITMAP)LoadImageA( getResourceInstance(), resourceName.ansi_c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION ); 
	}
	
	//LoadBitmap( getResourceInstance(), resourceName.c_str() );
	if ( NULL != resBMP ){
		return new Win32Image( resBMP );
	}
	else {
		//throw exception- resource not found !!!!
	}
	return NULL;
}

Resource* Win32ResourceBundle::getResource( const String& resourceName )
{
	foundResName = false;
	foundResType = "\0";
	
	::EnumResourceTypes( getResourceInstance(), 
		                 Win32ResourceBundle_EnumResTypeProc,
						 (LPARAM)resourceName.c_str() );
	if ( true == foundResName ){
		HRSRC resHandle = NULL;
		
		if ( System::isUnicodeEnabled() ) {
			resHandle = ::FindResourceW( getResourceInstance(), 
			                              resourceName.c_str(), 
										  foundResType.c_str() );
		}
		else {
			resHandle = ::FindResourceA( getResourceInstance(), 
			                              resourceName.ansi_c_str(), 
										  foundResType.ansi_c_str() );
		}
		
		if ( NULL != resHandle ){
			HGLOBAL	dataHandle = ::LoadResource( NULL, resHandle );
			if ( NULL != dataHandle ){
				void* data = ::LockResource( dataHandle );
				int size = ::SizeofResource( getResourceInstance(), resHandle );
				return new Resource( data, size, resourceName );				
			}
		}
		else {
			//throw exception- resource not found !!!!
		}
	}
	return NULL;
}

BOOL CALLBACK Win32ResourceBundle_EnumResTypeProc( HMODULE hModule, LPTSTR lpszType, LPARAM lParam )
{
	return ::EnumResourceNames( hModule,
		                        lpszType,
								Win32ResourceBundle_EnumResNameProc,
								lParam );
}

BOOL CALLBACK Win32ResourceBundle_EnumResNameProc( HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LPARAM lParam )
{
	BOOL result = TRUE;
	const String resName( (TCHAR*)lParam );
	if ( resName == lpszName ){
		foundResName = true;
		foundResType = lpszType;
		result = FALSE;
	}
	return result;
}

HINSTANCE Win32ResourceBundle::getResourceInstance()
{
	HINSTANCE result = NULL;	
	if ( NULL != this->appPeer_ ) {
		result = (HINSTANCE)appPeer_->getHandleID();
	}
	else {
		//throw exception !!
	}
	return result;
}



#if     _MSC_VER > 1000
#pragma once
#endif


#ifndef _VCF_WIN32HTMLBROWSERSELECTLIB_H__
#define _VCF_WIN32HTMLBROWSERSELECTLIB_H__

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

//Win32HTMLBrowserSelectLib.h

/**
*Helps linking with the right library
*/


#ifdef _LIB_CPLVERNUM
#		undef _LIB_CPLVERNUM
#endif


# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
# endif


#	ifdef _DEBUG
#		define WIN32HTMLBROWSER_DYNLIB		"Win32HTMLBrowser_"_LIB_CPLVERNUM"_d.dll"
#else
#		define WIN32HTMLBROWSER_DYNLIB		"Win32HTMLBrowser_"_LIB_CPLVERNUM".dll"
# endif


#ifdef BUILD_WIN32HTMLBROWSER_LIB
#define WIN32HTMLBROWSERAPI	__declspec(dllexport)
#else
#define WIN32HTMLBROWSERAPI	__declspec(dllimport)
#endif

// does not preload the library if defined
#ifndef RUNTIME_LOADLIBRARY



#ifdef USE_WIN32HTMLBROWSER_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM".lib")
#	endif
#elif USE_WIN32HTMLBROWSER_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static or dynamic link library
#endif // WIN32HTMLBROWSER_LIB

#endif // RUNTIME_LOADLIBRARY



/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.6.2.2  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6.2.1  2004/04/07 21:58:12  marcelloptr
*some changes related to _LIB_CPLVERNUM
*
*Revision 1.6  2004/03/03 09:40:25  augusto_roman
*Added support for the Intel Compiler v7.1.  Mostly added new project files (icl7), plus support in select lib header files.  Also fixed GraphicsToolKit::getAvailableImageTypes
*
*Revision 1.5  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.2  2003/12/17 05:11:56  ddiego
*minors mods, mostly to support chnages to the installer and some
*problems with the html help docs abnd MSDN integration
*
*Revision 1.4.4.1  2003/08/23 02:01:28  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.4  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.8.2  2002/12/27 23:04:41  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2.8.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.2  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/07/02 06:50:01  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*
*/


#endif // _VCF_WIN32HTMLBROWSERSELECTLIB_H__



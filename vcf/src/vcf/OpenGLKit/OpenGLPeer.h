/**
*CVS Log info
*$Log$
*Revision 1.1.2.2  2004/04/29 21:13:58  ddiego
*made a few changes to the new OpenGLKit files, adjusting where the
*CVS log was put, and changed a few cases for the export-import definition
*was used. Also added the two projects to the vcfAllProject workspace
*and added the script generated VC7 and VC71 projects as well.
*
*Revision 1.1.2.1  2004/04/29 15:38:12  pallindo
*Initial attempt at an OpenGLKit
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.8.8.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.10.1  2003/03/23 03:23:49  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.6.12.1  2002/08/06 01:21:01  ddiego
*removed Contextpeer.h because the file name was misspelled, and naturally Win32
*is NOT case sensitive
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
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

#ifndef _VCF_OPENGLPEER_H__
#define _VCF_OPENGLPEER_H__


namespace VCF {

class  OPENGLKIT_API OpenGLPeer {

public:
	OpenGLPeer(){};

	virtual ~OpenGLPeer(){};

	virtual void initGL() = 0;
	virtual void swapBuffers() = 0;

	virtual void makeCurrent() = 0;
};

}; //end of namespace VCF

#endif // _VCF_OPENGLPEER_H__



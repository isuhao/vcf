/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.7.10.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2003/01/08 00:19:45  marcelloptr
*mispellings and newlines at the end of all source files
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



#ifndef _VCF_SCROLLBARPEER_H__
#define _VCF_SCROLLBARPEER_H__




namespace VCF{

class APPKIT_API ScrollbarPeer : public VCF::Interface {
public:    

    virtual double getPosition() = 0;

    virtual void setPosition(const double& position ) = 0;

    virtual void setMax(const double& max ) = 0;

    virtual double getMax() = 0;

    virtual double getMin() = 0;

    virtual void setMin( const double& min ) = 0;

    virtual void getPageSize() = 0;

    virtual void setPageSize() = 0;

    virtual void getOrientation() = 0;

    virtual void setOrientation() = 0;
};

}
#endif // _VCF_SCROLLBARPEER_H__



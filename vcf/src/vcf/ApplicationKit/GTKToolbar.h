
#ifndef _VCF_GTKTOOLBAR_H__
#define _VCF_GTKTOOLBAR_H__




/**
Copyright (c) 2000-2001, Jim Crafton
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
	Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

NB: This software will not save the world.
*/

#ifndef _VCF_TOOLBARPEER_H__
#	include "vcf/ApplicationKit/ToolbarPeer.h"
#endif // _VCF_TOOLBARPEER_H__



namespace VCF  {

class ToolbarItem;
class ImageList;


class GTKToolbar : public AbstractGTKControl, public ToolbarPeer {
public:

	GTKToolbar(Control* control);


	virtual void create( Control* control );

	virtual gboolean handleEvent( GdkEvent* gtkEvent );


	void insertToolbarButton( const ulong32& index, ToolbarItem* item, bool showCaption=false );
	void removeToolbarButton( ToolbarItem* item );
	
	virtual void setImageList( ImageList* imageList );

	virtual void showButtonCaptions( const bool& val );

	virtual void setButtonCaptionPlacementHorizontal( const bool& val );

	virtual void setButtonSize( const Size& buttonSize );
	
protected:
	void onModelChanged( ModelEvent* e );
	bool currentlyModifyingItem_;
	void onImageListImageChanged( ImageListEvent* e );	
};





};



/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.1  2003/11/01 20:39:35  ddiego
*added gtk toolbar - no implementation yet
*
*Revision 1.1.2.1  2003/10/31 05:06:23  ddiego
*added toolbar impl
*
*/


#endif // _VCF_GTKTOOLBAR_H__




#if     _MSC_VER > 1000
#pragma once
#endif


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

// ImageListEvent.h

#ifndef _VCF_IMAGELISTEVENT_H__
#define _VCF_IMAGELISTEVENT_H__



namespace VCF
{


#define IMAGELIST_CONST						1100

#define IMAGELIST_EVENT_WIDTH_CHANGED		CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 1
#define IMAGELIST_EVENT_HEIGHT_CHANGED		CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 2
#define IMAGELIST_EVENT_CREATED				CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 3
#define IMAGELIST_EVENT_DESTROYED			CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 4
#define IMAGELIST_EVENT_ITEM_ADDED			CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 5
#define IMAGELIST_EVENT_ITEM_DELETED		CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 6


class APPKIT_API ImageListEvent : public Event  
{
public:
	
	ImageListEvent( Object * source);

	ImageListEvent( Object* source, const unsigned long& eventType, Image* image=NULL );

	ImageListEvent( const ImageListEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~ImageListEvent();
	

	ImageListEvent& operator=( const ImageListEvent& rhs ) {
		Event::operator =( rhs );

		image_ = rhs.image_;
		imageIndex_ = rhs.imageIndex_;

		return *this;
	}

	Image* getImage() {
		return image_;
	}

	ulong32 getIndexOfImage() {
		return imageIndex_;
	}

	void setIndexOfImage( const ulong32& indexOfImage ) {
		imageIndex_ = indexOfImage;
	}

	virtual Object* clone( bool deep=false ) {
		return new ImageListEvent(*this);
	}
protected:
	Image* image_;
	ulong32 imageIndex_;
};





/**
*ImageListEventHandler
*This handles the following Image List events:
*ImageListSizeChanged
*ImageAdded
*ImageDeleted
*ImageListCreated
*ImageListDestroyed
*ImageListSizeChanged
*/
template <class SOURCE_TYPE> class ImageListEventHandler : public EventHandlerInstance<SOURCE_TYPE,ImageListEvent> {
public:
	ImageListEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ImageListEvent>::OnEventHandlerMethod handlerMethod, 
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ImageListEvent>( source, handlerMethod, handlerName ) {
			
	}
	
	virtual ~ImageListEventHandler(){};
};



};



/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:36  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.8.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8  2003/08/09 02:56:43  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.7.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.7  2003/05/17 20:37:07  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.4  2003/03/23 06:46:00  marcelloptr
*minor fixes
*
*Revision 1.6.22.3  2003/03/23 03:23:46  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.6.22.1  2003/03/12 03:09:55  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/

#endif // _VCF_IMAGELISTEVENT_H__



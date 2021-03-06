#ifndef _VCF_WIN32TEXTPEER_H__
#define _VCF_WIN32TEXTPEER_H__
//Win32TextPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/TextPeer.h"

class TextHost;
class ITextServices;
interface ITextDocument;

namespace VCF {


class Win32TextPeer : public TextPeer {
public:
	Win32TextPeer( const bool& autoWordWrap, const bool& multiLined );

	Win32TextPeer();

	virtual ~Win32TextPeer();

	virtual OSHandleID getTextObjectHandle();

	//storage	
	virtual void insertText( unsigned int start, const String& text );

	virtual void deleteText( unsigned int start, unsigned int length );

	virtual unsigned int getTextLength();

	virtual String getText( unsigned int start, unsigned int length );

	
	//display
	virtual void paint( GraphicsContext* context, const Rect& paintRect );

	virtual void setRightMargin( const double & rightMargin );

	virtual void setLeftMargin( const double & leftMargin );	

	virtual void setTopMargin( const double & topMargin );

	virtual void setBottomMargin( const double & bottomMargin );	

	virtual double getLeftMargin();

	virtual double getRightMargin();

	virtual double getTopMargin();

	virtual double getBottomMargin();	

	virtual uint32 getLineCount();	

	virtual Rect getContentBoundsForWidth(const double& width);

	virtual void getStyle( unsigned int start, unsigned int length, Dictionary& styles );

	virtual void setStyle( unsigned int start, unsigned int length, Dictionary& styles );

	virtual void setDefaultStyle( Dictionary& styles );

protected:

	void initFromRichEdit( HWND hwnd );
	void initHostDefaultStyle( Font* font );

	TextHost* host_;
	ITextServices* textSvcs_;
	ITextDocument* textDocument_;
	Rect margins_;
};



}; // namespace VCF


#endif //_VCF_WIN32TEXTPEER_H__

/**
$Id$
*/

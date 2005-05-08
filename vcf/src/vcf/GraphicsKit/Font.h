#ifndef _VCF_FONT_H__
#define _VCF_FONT_H__
//Font.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */




namespace VCF {

#define DEFAULT_FONT_PT_SIZE	8
#define DEFAULT_FONT_NAME		"Arial"

class FontPeer;
class Locale;
class GraphicsContext;

#define FONT_CLASSID	"C41B2C4C-C95F-4ba2-B844-185C3AFCEF35"

class GRAPHICSKIT_API Font : public Object {

public:


    Font();

	Font( const String& fontName );

	Font( const String& fontName, const double& pointSize );

	Font( const Font& font );

	virtual ~Font();

	Font& operator= (const Font& rhs );

	bool isTrueType() const;

	/**
	*returns the Color the Font will be rendered in
	*/
	Color* getColor() ;


	/**
	*sets the Color to render the Font in
	*/
	void setColor( Color* color );

	/**
	*return the point size of the Font. One point is 1/72 of an inch
	*( or 0.0352552 cm for our more civilized friends !), so to figure
	*out the pixels involved, find out the Pixels per Inch and then apply
	*the following formula
	*<code>
	* (PointSize / 72) * PPI
	*</code>
	*where PPI represents the Pixels Per Inch
	*/
	double getPointSize() const;


	/**
	*sets the point size of the Font
	*/
	void setPointSize( const double& pointSize );

	double getPixelSize() const;
	void setPixelSize( const double& pixelSize );

	void setBold( const bool& bold );
	bool getBold() const;

    bool getItalic() const;
	void setItalic( const bool& italic );

    bool getUnderlined() const;
	void setUnderlined( const bool& underlined );

	bool getStrikeOut() const;
	void setStrikeOut( const bool& strikeout );
	
	String getName() const;

	void setName( const String& name );


	void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut,
								const Color* color, const String& name );

	FontPeer* getFontPeer();

	virtual void copy( Object* source );

	virtual Object* clone( bool deep ) {
		return new Font(*this);
	}

	double getAscent()  const;

	double getDescent()  const;

	double getHeight()  const;

	bool isFixedPitch() const ;
	/**
	Get the locale associated with this font. May be NULL, in which case this
	is whatever the System's default locale is.
	*/
	Locale* getLocale() const  {
		return locale_;
	}

	/**
	Set the locale of this font. This may change the script used by the 
	font when being rendered.
	*/
	void setLocale( Locale* locale );

	/**
	Sets the GraphicsContext for the font. This is used for special cases
	where calculations may need to be determined based on the information
	in the GraphicsContext. For example, the font peer may need information
	from the context peer when making font size calculations, particularly
	during printing.
	*/
	void setGraphicsContext( GraphicsContext* context ) {
		context_ = context;
	}

	/**
	Returns the current graphics context that's associated with this font.
	By default this value will be NULL.
	*/
	GraphicsContext* getGraphicsContext() {
		return context_;
	}
protected:

	FontPeer* peer_;
	Color color_;
	Locale* locale_;
	GraphicsContext* context_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3.2.2  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.3.2.1  2005/02/16 05:09:34  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/24 04:29:58  ddiego
*more printing work, still not yet integrated.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/30 19:17:11  ddiego
*fixed some font issues. got rid of methods that are not implementable on other platforms
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/26 21:58:39  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.2  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.10.4.1  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.10  2003/05/17 20:37:09  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.2.1  2003/03/12 03:10:21  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.2.1  2002/12/27 23:04:37  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.8  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.7.4.3  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.7.4.2  2002/09/28 22:22:35  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.7.4.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.7  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.6.12.2  2002/09/03 05:05:13  ddiego
*fixed some more bugs in getting form building to work again. It now works
*but of course there are new issues, namely reading in nested properties
*in a form file where the properties are objects like:
*font.color.red, so this needs to be fixed in hte VFFInputStream file
*also need to have hte form saved properly
*still miscellaneous crashes but getting closer to an alpha tes state
*
*Revision 1.6.12.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_FONT_H__



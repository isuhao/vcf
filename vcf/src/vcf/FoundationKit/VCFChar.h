#ifndef _VCF_VCFCHAR_H__
#define _VCF_VCFCHAR_H__
//VCFChar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


namespace VCF{

	/*
#ifdef VCF_UNICODE_ENABLED
	typedef wchar_t VCFChar;
#else
	typedef char VCFChar;
#endif
	*/

/**
JC - I added this to make it simple to build on
linux platforms - gcc doesn't like
std::basic_string<unsigned short> on linux, but
doesn't like std::basic_string<wchar_t> on OSX, go figure :(
*/
#ifdef VCF_POSIX
	typedef wchar_t WideChar;
#elif __GNUWIN32__
    typedef wchar_t WideChar;
#else
	typedef unsigned short WideChar;
#endif



	typedef WideChar VCFChar;
};


#ifdef VCF_OSX


namespace std {

template<>
struct char_traits<VCF::WideChar> {
	typedef VCF::WideChar	char_type;
	typedef wint_t		int_type;
	typedef streamoff 	off_type;
	typedef wstreampos 	pos_type;
	typedef mbstate_t 	state_type;

	static void assign( char_type &c1, const char_type &c2 )
	{
		c1 = c2;
	}

	static bool eq( const char_type &c1, const char_type &c2 )
	{
		return c1 == c2;
	}

	static bool lt( const char_type &c1, const char_type &c2 )
	{
		return c1 < c2;
	}

	static int compare( const char_type *s1, const char_type *s2, size_t n )
	{
		size_t i = 0;
		while ( i < n and *s1 == *s2 )
		{
			++i;
			++s1;
			++s2;
		}
		return i >= n ? 0 : *s1 - *s2;
	}

	static size_t length( const char_type *s )
	{
		const char_type		*p = s;
		while ( *p != 0 )
			++p;
		return p - s;
	}

	static const char_type *find( const char_type *s, size_t n, const char_type &a )
	{
		size_t  i = 0;
		while ( i < n and a != *s )
		{
			++i;
			++s;
		}
		return i >= n ? 0 : s;
	}

	static char_type *move( char_type *s1, const char_type *s2, int_type n )
	{
		return (char_type *)memmove( s1, s2, n * sizeof( char_type ) );
	}

	static char_type *copy( char_type *s1, const char_type *s2, size_t n )
	{
		return (char_type *)memcpy( s1, s2, n * sizeof( char_type ) );
	}

	static char_type *assign( char_type *s, size_t n, char_type a )
	{
		size_t  i = 0;
		char_type *p = s;
		while ( i < n )
		{
			*p = a;
			++i;
			++p;
		}
		return s;
	}

	static char_type to_char_type( const int_type &c )
	{
		return char_type( c );
	}

	static int_type to_int_type( const char_type &c )
	{
		return int_type( c );
	}

	static bool eq_int_type( const int_type &c1, const int_type &c2 )
	{
		return c1 == c2;
	}

	static int_type  eof()
	{
		return static_cast<int_type>(EOF);
	}

	static int_type not_eof( const int_type &c )
	{
		return eq_int_type( c, eof() ) ? 0 : c;
	}
};

}; //end of namespace std

#endif


/**
*CVS Log info
*$Log$
*Revision 1.1.2.7  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.5  2004/06/01 04:21:52  ddiego
*fixed a little update mistake
*
*Revision 1.1.2.4  2004/05/31 22:24:52  ddiego
*OSX code for handling focus events
*
*Revision 1.1.2.3  2004/05/16 02:39:09  ddiego
*OSX code updates
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.3  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7.2.2  2004/04/21 02:17:24  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.7.2.1  2004/04/06 17:19:15  ddiego
*minor header changes to better facilitate compiling with
*mingw. Also some minor changes to the devcpp FoundationKit project.
*
*Revision 1.7  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.6.2.2  2004/03/31 03:55:50  ddiego
*fixed link problems with UnicodeString
*
*Revision 1.6.2.1  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.6  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.26.1  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VCFCHAR_H__



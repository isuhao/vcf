#ifndef _VCF_STREAM_H__
#define _VCF_STREAM_H__
//Stream.h

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

/**
*seek types
*/
enum SeekType{
	stSeekFromStart=0,
	stSeekFromRelative,
	stSeekFromEnd
};

/**
*file acess
*/
enum FileStreamAccessType{
	fsDontCare = 0, //same as read/write for now
	fsRead,
	fsWrite,
	fsReadWrite
};

/**
*forward declared, see Persistable.h
*/
class Persistable;



/**
\class Stream Stream.h "vcf/FoundationKit/Stream.h"
Stream interface defines a core set of funcationality for streams
in the Visual Component Framework derived Streams should support "stream chaining",
the ability of the stream constructor to support an incoming stream from
someother stream object. For example:
\code
	MyStream s = new MyStream( new MemStream( new GZIPStream( SomeBigDataObject ) ) );
\endcode
assuming SomeBigDataObject supports Persistable, then the object is read into the
GZIPStream and compressed, the compressed bytes are sent to the Memory stream, and
then this is sent to MyStream.

Streams are meant as alternative to the C++ streams, though in some
cases they may extend the standard C++ stream library.
*
@author Jim Crafton
@version 1.0
*/
class FOUNDATIONKIT_API Stream {
public:

    virtual ~Stream(){};

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom)=0;

	/**
	returns the size of the stream. The size represents the
	number of bytes that have been \b written, or \b read to/from the stream
	*/
    virtual unsigned long getSize() =0;

	/**
	returns a pointer to the buffer that holds the stream memory
	*/
	virtual char* getBuffer() = 0;

	/**
	this is a global offset from the beggining of the stream
	*/
	virtual ulong32 getCurrentSeekPos() = 0;
};

/**
\class InputStream Stream.h "vcf/FoundationKit/Stream.h"
InputStream, basic interface describing the requirements to
support streaming data into a stream. Support for the basic
primitive types is done through the extraction operator( >> ),
as well as providing support for the Persistable interface,
and reading in an arbitrary chunk of memory
*/
class FOUNDATIONKIT_API InputStream : public Stream {
public:

	virtual ~InputStream(){};

	// new introduced by tiziano
	virtual bool isEOS() = 0;

	virtual unsigned long read( unsigned char* bytesToRead, unsigned long sizeOfBytes ) = 0;

	virtual void read( Persistable* persistableObject ) ;

	virtual void read( short& val ) ;

	virtual void read( long& val ) ;

	virtual void read( int& val ) ;

	virtual void read( bool& val ) ;

	virtual void read( char& val ) ;

	virtual void read( float& val ) ;

	virtual void read( double& val ) ;

	virtual void read( String& val ) ;

	InputStream& operator>>( short& val );

	InputStream& operator>>( long& val );

	InputStream& operator>>( int& val );

	InputStream& operator>>( bool& val );

	InputStream& operator>>( char& val );

	InputStream& operator>>( float& val );

	InputStream& operator>>( double& val );

	InputStream& operator>>( String& val );

	InputStream& operator>>( Persistable* val );
};

/**
\class OutputStream Stream.h "vcf/FoundationKit/Stream.h"
OutputStream, basic interface describing the requirements to
support streaming data into a stream. Support for the basic
primitive types is done through the insertion operator( << ),
as well as providing support for the Persistable interface,
and writing out an arbitrary chunk of memory
*/
class FOUNDATIONKIT_API OutputStream : public Stream {
public:
	virtual ~OutputStream(){};

	virtual unsigned long write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes )=0;

	virtual void write( Persistable* persistableObject );

	virtual void write( const short& val );

	virtual void write( const long& val );

	virtual void write( const int& val );

	virtual void write( const bool& val );

	virtual void write( const char& val );

	virtual void write( const float& val );

	virtual void write( const double& val );

	virtual void write( const String& val );

	OutputStream& operator<<( const short& val );

	OutputStream& operator<<( const long& val );

	OutputStream& operator<<( const int& val );

	OutputStream& operator<<( const bool& val );

	OutputStream& operator<<( const char& val );

	OutputStream& operator<<( const float& val );

	OutputStream& operator<<( const double& val );

	OutputStream& operator<<( const String& val );

	OutputStream& operator<<( Persistable* val );
};



};


/**
*CVS Log info
*$Log$
*Revision 1.3.2.2  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.3.2.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.3  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.13.4.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.13  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.12  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.22.2  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.22.1  2003/03/12 03:11:45  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2002/02/28 01:07:09  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.10  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_STREAM_H__



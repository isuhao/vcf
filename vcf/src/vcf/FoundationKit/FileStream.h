#ifndef _VCF_FILESTREAM_H__
#define _VCF_FILESTREAM_H__
//FileStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


namespace VCF  {

class FileStreamPeer;

/**
\class FileStreamBase FileStream.h "vcf/FoundationKit/FileStream.h"
Special file stream that uses native OS calls
for file IO as opposed to the more generic C++ filestream class.
This class uses a FileStreamPeer to do the actual work

@author Jim Crafton
@version 1.0
*/


class FOUNDATIONKIT_API FileStreamBase : public Object {
public:
	FileStreamBase();

	virtual ~FileStreamBase();

	String& getFilename() {
		return filename_;
	};

	/**
	*closes the file stream
	*/
	void close();

	/**
	*opens a file stream
	*/
	void open( const String& filename, FileStreamAccessType accessType );

protected:
	void init();
	FileStreamPeer* fsPeer_;
	String filename_;
	FileStreamAccessType access_;
	ulong32 currentSeekPos_;
};

/**
\class FileInputStream FileStream.h "vcf/FoundationKit/FileStream.h"
*/
class FOUNDATIONKIT_API FileInputStream : public InputStream , public FileStreamBase {
public:
	FileInputStream( File* file );

	FileInputStream( const String& filename );

	virtual ~FileInputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	/**
	returns the size of the stream. The size represents the
	number of bytes that have been <b>read</b> from the stream
	*/
    virtual unsigned long getSize();


	/**
	*returns a pointer to the buffer that holds the stream memory
	*/
	virtual char* getBuffer();

	virtual ulong32 getCurrentSeekPos() ;

	/**
	input
	*/
	virtual unsigned long read( unsigned char* bytesToRead, unsigned long sizeOfBytes );

	/**
	end of stream
	*/
	virtual bool isEOS()  {
		// stub impl.
		return false;
	}

	void open( const String& filename );

protected:

};

/**
\class FileOutputStream FileStream.h "vcf/FoundationKit/FileStream.h"
*/
class FOUNDATIONKIT_API FileOutputStream : public OutputStream , public FileStreamBase {
public:
	FileOutputStream( const String& filename, const bool & append = false );

	FileOutputStream( File* file );

	virtual ~FileOutputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	/**
	*returns the size of the stream. The size represents the
	*number of bytes that have been <b>written</b>, or <b>read</b> to/from the stream
	*/
    virtual unsigned long getSize();


	/**
	*returns a pointer to the buffer that holds the stream memory
	*/
	virtual char* getBuffer();

	virtual ulong32 getCurrentSeekPos() ;

	//output
	virtual unsigned long write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes );

	void open( const String& filename, const bool & append = false );

protected:
};



};


/**
*CVS Log info
*$Log$
*Revision 1.2.6.2  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2.6.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.12.4.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.3  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.11.4.2  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.11.4.1  2003/08/11 19:40:12  marcelloptr
*bugfix [786946] FileOutputStream always erases the file when it opens it
*
*Revision 1.11  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:11:44  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.20.1  2003/01/08 23:51:45  marcelloptr
*forgotten functions in Rect and FileStream
*
*Revision 1.9  2002/02/28 01:07:09  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.8  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_FILESTREAM_H__



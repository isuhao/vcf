#ifndef _VCF_OSXLIBRARYPEER_H__
#define _VCF_OSXLIBRARYPEER_H__
//OSXLibraryPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class OSXLibraryPeer : public LibraryPeer {

public:
	OSXLibraryPeer();

	virtual ~OSXLibraryPeer();

	virtual void load( const String& libraryFilename );

	virtual void* getFunction( const String& functionName );

	virtual void unload();

	virtual OSHandleID getHandleID();
protected:
	/**
	This is either a pointer that dlopen() returned
	or a CFBundleRef
	*/
	void* libHandle_;
	bool handleIsBundle_; 

};

}; //end of namespace VCF


/**
*CVS Log info
 *$Log$
 *Revision 1.3.4.1  2005/11/10 02:02:38  ddiego
 *updated the osx build so that it
 *compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
 *
 *Revision 1.3  2004/12/01 04:31:41  ddiego
 *merged over devmain-0-6-6 code. Marcello did a kick ass job
 *of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
 *that he found. Many, many thanks for this Marcello.
 *
 *Revision 1.2.2.1  2004/10/10 20:42:08  ddiego
 *osx updates
 *
 *Revision 1.2  2004/08/07 02:49:13  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.5  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.3.2.1  2004/04/26 21:58:42  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.3  2004/04/03 15:48:42  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.2.6.1  2004/02/21 03:27:06  ddiego
 *updates for OSX porting
 *
 *Revision 1.2  2003/05/17 20:37:12  ddiego
 *this is the checkin for the 0.6.1 release - represents the merge over from
 *the devmain-0-6-0 branch plus a few minor bug fixes
 *
 *Revision 1.1.2.1  2003/05/15 03:01:01  ddiego
 *added initial osx source( FoundationKit only),
 *plus some fixes to compile under GCC 3.x compilers
 *
 */


#endif // _VCF_OSXLIBRARYPEER_H__


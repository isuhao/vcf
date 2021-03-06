#ifndef _VCF_DIRECTORY_H__
#define _VCF_DIRECTORY_H__
//Directory.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF  {

class FileSearchFilter;


/**
\class Directory Directory.h "vcf/FoundationKit/Directory.h"
A Directory represents a directory in a filesystem.
  and therefore it is a File object with all its features.

In addition they can instantiate a Directory::Finder object
in the moment the user wants them to perform a search into
its files and subdirectories based on a search filter.

The Directory::Finder class has been written to be very performant
even when recursing.

The way to use this class is:
  \code
      String filepath = L"./";

      String filename;
      File* file = NULL;

      Directory dir( FilePath::getExpandedRelativePathName( filepath ) );

      Directory::Finder* finder = dir.findFiles( "*.cpp" );
      finder->setDisplayMode( Directory::Finder::dmFiles );
      while ( finder->nextElement() ) {
        file = finder->getCurrentElement();
        filename = file->getName();

        if ( file->isDirectory() ) {
          printf ( "[%s]\n", filename.ansi_c_str() )
        } else {
          printf ( "%s\n", filename.ansi_c_str() )
        }
      }
      finder->free();
  \endcode

The user is also able to create more than one finder
from the same directory instance. But in order to achieve
that we made the user responsible of freeing the finder.

The statements:
\code
  finder->setMaskFilterFileAttribs( File::faArchive );
  finder->ignoreStat( File::smMaskDateAll );
\endcode
can be used to speed up the search.


It is possible to easily recurse into subdirectories.
The following code will let you to recurse up to 10 levels
while applying a personalized filter.
The filter can be as flexible as desired.
\code
  FilSearchFilterStandard filterFilesObj( L"*.h", L"src/vcf" );

  String filepath = L"./";

  String filename;
  File* file = NULL;

  Directory dir( FilePath::getExpandedRelativePathName( filepath ) );
  Directory::Finder* finder = dir.findFiles( filterFilesObj, filterDirsObj );
  finder->setDisplayMode( Directory::Finder::dmAny );
  finder->setRecursion( true, 10 );
  while ( finder->nextElement() ) {
    file = finder->getCurrentElement();
    filename = file->getName();

    if ( file->isDirectory() ) {
      String st = StringUtils::format( convertUtcToLocal( file->getDateModified() ), L"%d/%m/%Y %H:%M:%S" );
      printf ( "[%d] %s %10s %5s [%s]\n", finder->getRecursionLevel(), st.ansi_c_str(), "", "", filename.ansi_c_str() );
    } else {
      String sz = StringUtils::toString( file->getSize() );
      String st = StringUtils::format( file->getDateModified(), L"%d/%m/%Y %H:%M:%S" );
      String sa = StringUtils::format( "%c%c%c%c%c", file->isArchive()?'a':' ', file->isReadOnly()?'r':' ', 
                                       file->isHidden()?'h':' ', file->isSystem()?'s':' ', file->isExecutable()?'x':' ' );
      printf ( "[%d] %s %10s %s  %s\n", finder->getRecursionLevel(), st.ansi_c_str(), sz.ansi_c_str(), sa.ansi_c_str(), filename.ansi_c_str() );
    }
  }
  finder->free();
\endcode

The statements:
\code
  finder->setDisplayMode( Directory::Finder::dmAny );
  finder->setDisplayOrder( Directory::Finder::dmFiles );
\endcode
can be used to control how the found files are displayed
and their order.

Normally the filenames are displayed in the native format,
but the statement:
\code
  finder->setKeepOSSpecificFormat( true );
\endcode
will let the user to mantain the format specific for the OS.

*/

class FOUNDATIONKIT_API Directory : public File {
public:


	/**	
	A Finder object is used to iterate a
	set of files contained in a Directory object
	that represents the directory.
	Only Directory objects may create a Finder object.
	
	A Finder is similar to an Enumerator but it doesn't 
	follow the exact same pattern. Specifically it doesn't 
	allow you to go "backwards" - you can only reset the
	finder, and then progress to the next element.
	The most import method for iterating the elements in 
	a Finder isntance is the nextElement() function which 
	returns a pointer to an internal File object which is updated
	for each file element.
	
	All the other methods are used to narrow or speed up the search.
	Custom filtering can be done the simple way by specifying
	filter strings, or in a fully flexible way through any
	class derived from FileSearchFilter.
	
	*/
	class FOUNDATIONKIT_API Finder : public Object {
	public:
		enum DisplayMode {
			dmNone  = 0x0,
			dmFiles = 0x1,
			dmDirs  = 0x2,
			dmAny   = dmFiles | dmDirs,
		};

	public:
		virtual ~Finder();

		/**
		Gets the pointer to the last searched element.
		@return the pointer to the last searched element.
		*/
		File* getCurrentElement() const;

		/**
		Advances the finder to the next element in the search.
		@return bool true if we found another element fulfilling
		the conditions set by the user, false otherwise.
		*/
		bool nextElement();

		/**
		Resets the search.
		*/
		void reset();

		/**
		Are there any more elements in this Finder ?
		This function doesn't affect the search in any way.
		@return bool true if the there are more elements yet to search.
		*/
		inline bool hasMoreElements() const {
			return searchHasMoreElements_;
		}

		/**
		Returns the Directory object that created.
		this Finder.
		@return Directory the owning directory for this finder.
		*/
		Directory* getOwningDirectory() {
			return owningDirectory_;
		}

		/**
		set flags for DisplayMode enabled
		It can be set for files ( dmFiles ) or dirs ( dmDirs )
		or both ( dmAny ). If it is set for files, the finder
		will still be able to recurse into subdirectories
		if specified.
		Do not modify the display mode during the search 
		unless you know what you are doing.
		*@param displayMode the display mode
		*/
		void setDisplayMode( DisplayMode displayMode );

		/**
		Tells the current display mode
		@return DisplayMode the current display mode
		*/
		DisplayMode getDisplayMode() const {
			return displayMode_;
		}

		/**
		Set the order used by the Finder for displaying files and directories.
		The possible modes are: to display files first ( dmFiles )
		and then directories; or vice-versa ( dmDirs ) in two search steps;
		or to display both of them, unsorted, in only one search step ( dmAny ).
		@param DisplayMode the display order.
		*/
		void setDisplayOrder( DisplayMode displayOrder );

		/**
		Tells the order used by the Finder for displaying files and directories
		@return DisplayMode the current display order.
		*/
		DisplayMode getDisplayOrder() const {
			return displayOrder_;
		}

		/**
		Sets the Directory::Finder for recursion into subdirectories.
		@param recurse to allow recursion into subdirectories
		@param recursionLevelMax maximum level of subdirectories to recurse into
		( default is -1 so no limit is set, 0 implies no recursion )
		*/
		void setRecursion( const bool& recurse, const int& recursionLevelMax = -1 );

		/**
		Tells if the Finder is set for recursion into suybdirectories
		@return true if recursion is allowed
		*/
		inline bool getRecurse() const {
			return recurse_;
		}

		/**
		Gets the maximum subdirectory level the Finder is allowed to recurse into, 0 means no recursion
		@return the maximum recursion level.
		*/
		inline int getRecursionLevelMax() const {
			return recursionLevelMax_;
		}

		/**
		Sets the maximum subdirectory level up to where the Finder is allowed to recurse into.
		*@param the maximum recursion level. 0 means only current directory. -1 means no limits.
		*/
		inline void setRecursionLevelMax( const int& recursionLevelMax ) {
			recursionLevelMax_ = recursionLevelMax;
		}

		/**
		Gets the current subdirectory level where the Finder is currently recursing into, 0 is 
		the root level of the search.
		*@return the maximum recursion level.
		*/
		inline int getRecursionLevel() const {
			return recursionLevel_;
		}

		/**
		Not meant for general consumption. This is meant for implementors only.
		Don't call this method, or world wide evils will be unleashed that even
		Lara Croft will be powerless to stop.
		*/
		inline void internal_updateToActiveFinder() {
			recursionLevel_ = rootSearchFinder_->activeFinder_->recursionLevel_;
			relativePathToRootSearch_ = rootSearchFinder_->activeFinder_->relativePathToRootSearch_;
		}


		/**
		Gets the relative path of the file to the directory where the search started
		@return the relative path to the root of the search.
		*/
		inline String getRelativePathToRootSearch() const {
			return relativePathToRootSearch_;
		}

		inline void setRelativePathToRootSearch( const String& val ) {
			relativePathToRootSearch_ = val;
		}

		/**
		sets the search filter used with files by this Finder.
		@param the search filter object used to filter the files
		*/
		inline void setSearchFilterFileObject( FileSearchFilter* searchFilterFileObject, const bool& ownFilterFileObject = false ) {
			searchFilterFileObject_ = searchFilterFileObject;
			ownFilterFileObject_ = ownFilterFileObject;
		}

		/**
		Returns the search filter used with files by this Finder.
		@return FileSearchFilter the search filter object for files used by this Finder
		*/
		inline FileSearchFilter* getSearchFilterFileObject() const {
			return searchFilterFileObject_;
		}

		/**
		Set the file attributes mask used to limit the search for files ( not directories ).
		@param maskFilterFileAttribs the file attributes mask for files
		*/
		inline void setMaskFilterFileAttribs( File::FileAttributes maskFilterFileAttribs ) {
			maskFilterFileAttribs_ = maskFilterFileAttribs;
		}

		/**
		Gets the file attributes mask used to limit the search for files ( not directories ).
		@return the file attributes mask for files
		*/
		inline File::FileAttributes getMaskFilterFileAttribs() const {
			return maskFilterFileAttribs_;
		}

		/**
		Sets the mask for the informations we want to extract from a file.
		This filter is meant to increase the performance, but be careful:
		this speed up the search significantly, but then if later you'll 
		frequently need of the infos you choosed to exclude, then the 
		performance will end up to be worse.
		@param StatMask the mask
		*/
		inline void setStatMask( uint32 statMask ) {
			statMask_ = statMask;
			if ( recurse_ ) {
				// we make sure we have directory informations
				//if ( (uint32&)statMask_ |= File::smAttributes ) {
				if ( statMask_ |= File::smAttributes ) {
				}
			}
		}

		/**
		Gets the mask for the informations we want to extract from a file
		*@return the mask
		*/
		inline uint32 getStatMask() const {
			return statMask_;
		}

		/**
		Sets the mask for the informations we just don't care about.
		@param StatMask the mask of infos we want to ignore
		@see setStatMask
		*/
		inline void ignoreStat( uint32 ignoreMask ) {
			uint32 statMask = File::smMaskAll & ~ignoreMask;
			setStatMask( statMask );
		}

		/**
		*stets the Finder for showing the local time of
		*any file found. By default it shows the UTC time.
		*@param bool true to show the local time of files, 
		*false to show the UTC time of files.
		*/
		inline void setShowLocalTime( const bool& showLocalTime ) {
			showLocalTime_ = showLocalTime;
		}

		/**
		*tells if the Finder is set for showing the local time 
		*of any file found, or UTC time instead.
		*@return true if it shows the local time of files, 
		*false if it shows the UTC time of files.
		*/
		inline bool getShowLocalTime() {
			return showLocalTime_;
		}

		/**
		* set the finder to always return filenames in the OS specific format
		*@param bool true if we keep the format OS specific, 
		* false if we keep the native format instead
		*/
		inline void setKeepOSSpecificFormat( const bool& keepOSSpecificFormat = true ) {
			keepOSSpecificFormat_ = keepOSSpecificFormat;
		}

		/**
		* tells if we keep currently keep the filenames format OS specific
		*@return bool the current choice
		*/
		inline bool getKeepOSSpecificFormat() const {
			return keepOSSpecificFormat_;
		}

		/**
		* enables/disable the visibility of some special directories during the search
		* Under Windows these are indicated with dots ( '.' and '..' )
		*@param allowSpecialDirs
		*/
		virtual void setAllowSpecialDirs( const bool& allowSpecialDirs ) {
			allowSpecialDirs_ = allowSpecialDirs;
		}

		/**
		* tells if the search is enabled for retrieving some special directories 
		* Under Windows these are indicated with dots ( '.' and '..' )
		* but they could be others under different OS
		*@return bool true if visible to the search
		*/
		inline bool getAllowSpecialDirs() const {
			return allowSpecialDirs_;
		}

		inline File& getFileInfo() {
			return fileInfos_;
		}

		inline const File& getFileInfo() const {
			return fileInfos_;
		}
		

		inline DisplayMode getCurrentDisplayOrder() const {
			return displayOrderCurrent_;
		}

		inline void setCurrentDisplayOrder( const DisplayMode& mode ) {
			displayOrderCurrent_ = mode;
		}

		inline bool canRecurseDown() const {
			return (-1 == rootSearchFinder_->recursionLevelMax_ ||
				recursionLevel_ < rootSearchFinder_->recursionLevelMax_) ? true : false;
		}

		inline void setCurrentElement( File* file ) {
			currentElement_ = file;
			searchHasMoreElements_ = ( NULL != currentElement_ );
		}							

		
		void setParentFinder( Finder* finder, const String& relPath, const int& previousRecursionLevel );

		void goDownDir( File* file );
		void goUpDir( File* file );

		void continueSearch( File* file );
	public:
		friend class Directory;

	protected:
		// the Finder ctor. Only Directory or its derived can create this object.
		Finder( Directory* directoryToSearch, FileSearchFilter* filterFileObject = NULL, const bool& ownFilterFileObject = false );

	protected:
		// the File object gathering informations about the file currently retrieved by the search
		File  fileInfos_;

		/**
		the directory File owning this finder
		*/
		Directory* owningDirectory_;

		FileSearchFilter* searchFilterFileObject_;
		bool ownFilterFileObject_;
		File::FileAttributes maskFilterFileAttribs_;
		uint32 statMask_;
		/**
		The current element retrieved by the search
		*/
		File* currentElement_;

		/**
		Simply used to know if we have more elements
		*/
		bool searchHasMoreElements_;

		/**
		The display mode requested by the user
		*/
		DisplayMode displayMode_;

		/**
		The display order requested by the user
		*/
		DisplayMode displayOrder_;

		/**
		The display order currently in use
		*/
		DisplayMode displayOrderCurrent_;

		bool allowSpecialDirs_;
		bool showLocalTime_;
		bool keepOSSpecificFormat_;


		/* recursion support */
	
		bool recurse_;


		/**
		the relative path to where the search started, while in the 
		current subdirectories
		*/
		String relativePathToRootSearch_;

		/**
		The followings are pointers to finders used to manage the 
		search along the directory tree.
		Each finder node has its child and parent finders.
		For performance and simplicity reasons and in order 
		to avoid useless copying of informations it is convenient to
		keep a pointer to the active finder representing the search 
		in the current subdirectory. The rootSearchFinder_ is treated 
		differently then the others as it is the finder at the root of 
		the search and the only one always accessible to the user in 
		the search loop.
		*/

		/**
		The main finder. The same finder accessible to the user during all the search loop.
		*/
		Finder* rootSearchFinder_;									

		/**
		pointer to the finder currently active in the search
		*/
		Finder* activeFinder_;
		/**
		Pointer to finder used to manage the search along the directory tree
		*/
		Finder* childFinder_;
		/**
		Pointer to finder used to manage the search along the directory tree
		*/
		Finder* parentFinder_;

		/**
		memory finders' management. This vector is allocated only in the main 
		finder rootSearchFinder_
		*/
		std::vector<Directory*>* subdirs_; 
		std::vector<Finder*>* subfinders_; 
		/**
		current recursion level
		*/
		int recursionLevel_;

		/**
		max allowed recursion level
		*/
		int recursionLevelMax_;

		/**
		for recursion: when we complete the search by dir and we want to 
		search the files or viceversa.
		*/
		bool goSearchAgain_;

	}; // Directory::Finder



	Directory( const String& fileName = "" );

	Directory( const FilePath& filePath );

	virtual ~Directory();

	/**
	* sets the name of the Directory
	* and creates the peer if it does not exists yet
	* It makes sure the name is a well formed directory name
	* i.e. with the 'DirectorySeparator' at the end
	*@param fileName the name
	*/
	virtual void setName( const String& fileName );

	/**
	* Creates, initializes and returns a Finder object to perform a 
	* directory/files search.
	*@param String a filter string for a simple filtering of the file names.
	*@param String a filter string for a simple filtering of the path names.
	*These two strings are internally represented by
	*an instance of FileSearchFilterStandard.
	*@throw BasicException if the filename is not a full path name.
	*/
	Finder* findFiles( const String& filterFile = L"", const String& filterDir = L"" );

	/**
	* Creates, initializes and returns a Finder object to perform a directory/files search.
	*@param FileSearchFilter a filter object to filter the search for files and/or subdirectories.
	* Use NULL to disable any filtering on files or subdirectories.
	*@param bool ownFilterFileObject true if you want the Finder to be responsible for its deletion
	* Please use false when the filter object is allocated on the stack.
	*@throw BasicException if the filename is not a full path name.
	*/
	Finder* findFiles( FileSearchFilter* filterFileObject, const bool& ownFilterFileObject = false );

public:

	//Finder* finder_;
};





///////////////////////////////////////////////////////////////////////////////
// FileSearchFilter 

/**
\class FileSearchFilter Directory.h "vcf/FoundationKit/Directory.h"
FileSearchFilter is an abstract class for any user defined Filter object
working with the Directory::Finder
*/

class FOUNDATIONKIT_API FileSearchFilter {
public:
	virtual ~FileSearchFilter(){};

	/**
	* the filtering function of the object, called by the Directory::Finder during the search
	* @param File* the pointer to the File object and its informations retrieved by the Finder,
	* file can also represent a directory on the file system.
	* @param Directory* the pointer to the object representing the subdirectory containing file.
	* @param Finder* the pointer to the active Directory::Finder* object performing the search 
	* when the call to this function is made.
	* The user is allowed to assume that all these arguments are never NULL.
	* @return File* the passed argument File* itself if filter is passed, but
	* <B>it must return NULL if File dind't pass the filter</B>
	*/
	virtual File* passSearchFilter( const File* file, const Directory* subdir, const Directory::Finder* finder ) = 0;

	virtual String toString()  const { return L""; };
};

/**
\class FileSearchFilterStandard Directory.h "vcf/FoundationKit/Directory.h"
FileSearchFilterStandard is the predefined Filter object
used for simple searches.
*/

class FOUNDATIONKIT_API FileSearchFilterStandard : public FileSearchFilter {
public:

	/**
	  the constructor
	  @param String the filter list for files.
	  @param String the filter list for subdirectories.
	  The items in these list are separated by separator, 
	  which is the ';' character by default.
	  The wildcard character '*' is accepted, 
	  as in the implementation of FilePath::wildCharsMatchName()
	  A specification like "*.vpl" does not implies that we are excluding directories
	  from the search. Please use setDisplayMode( Directory::Finder::dmFiles ) for this.
	  @param String the separator between items in filterFileList and filterDirList.
	  @param fileAttributes the file attributes of the files we want to retrieve.
	*/
	FileSearchFilterStandard(  const String& basenameFilterList, const String& pathnameFilterList = L"", const String& separator = L";" );

	virtual ~FileSearchFilterStandard(){};

	virtual File* passSearchFilter( const File* file, const Directory* subdir, const Directory::Finder* finder );

	/**
	build the filter starting from the filter string 
	@param String the filter string for files.
	@param String the filter string for subdirectories.
	*/
	void buildSearchFilters( const String& basenameFilterList, const String& pathnameFilterList = L"", const String& separator = L";" );

	virtual String toString()  const {
		return ( basenameFilterList_ + " in " + pathnameFilterList_ );
	};

public:
	String basenameFilterList_;
	String pathnameFilterList_;
	std::vector<String> searchFiltersBasename_;
	std::vector<String> searchFiltersPathname_;
	std::vector<String>::iterator searchFilterIterator_;
	String separator_;
};






///////////////////////////////////////////////////////////////////////////////
// inlines

inline void Directory::setName( const String& fileName ) {
	File::setName( FilePath::makeDirectoryName( fileName ) );
}


}; //end of namespace VCF


#endif // _VCF_DIRECTORY_H__

/**
$Id$
*/

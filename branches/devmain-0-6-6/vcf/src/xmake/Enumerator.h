/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.1  2004/04/28 04:07:36  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/05/17 20:38:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.10.2  2003/03/23 03:24:13  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.10.1  2003/03/12 03:13:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2002/09/12 03:26:12  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.12.1  2002/07/16 15:52:48  ddiego
*mods to xmake to separate it into a lib file and
*command line program. This means there is now a
*separate libXmake for using in other programs
*also moved all the xmake classes into their
*own xmake namespace.
*Changes made to the makefile as well as a new
*dsp for the libXmake
*
*Revision 1.2  2002/03/15 16:33:22  ddiego
*gcc compile fixes
*
*Revision 1.1  2002/02/25 05:01:53  ddiego
*added the xmake project
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
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

/* Generated by Together */
//Enumerator.h

#ifndef _ENUMERATOR_H__
#define _ENUMERATOR_H__

#include <algorithm>

#ifndef NULL
#define NULL 0
#endif


namespace xmake {

/**
 * This is a template class that provides an interface for 
 * iterating through a collection, and provides a standard set of methods. 
 * Either multiply inherited by classes that want to public expose a single set of children,
 *or as  a returned object for safe enumeration of data collections.
 */

template <class COLLECTION_TYPE> class  Enumerator{
public:
	Enumerator(){
		supportsEditing_ = false;
	};

	virtual ~Enumerator(){};
	
	/**
	*indicates whether there are any more children to enumerate
	*through
	*@param bool specifies whether the enumeration should be forwards
	*or backwards. The default value is true for enumerating forwards.
	*@return bool true if there are any elements left to enumerate,
	*otherwise returns false.
	*/
	virtual bool hasMoreElements(const bool& backward=false)=0;
	
	/**
	*returns the next element in the enumeration. Moves the internal
	*iterator forward
	*@return COLLECTION_TYPE returns a COLLECTION_TYPE value of whatever type
	*was specified in the template argument to the Enumerator
	*/
	virtual COLLECTION_TYPE nextElement()=0;
	
	/**
	*returns the previous element in the enumeration. Moves the internal
	*iterator backward
	*@return COLLECTION_TYPE returns a COLLECTION_TYPE value of whatever type
	*was specified in the template argument to the Enumerator
	*/
	virtual COLLECTION_TYPE prevElement()=0;
	
	/**
	*Resets the Enumerator's internal iterator back to the beginning (or end, 
	*if backward is true).
	*@param bool specifies which direction to reset to
	*/
	virtual void reset(const bool& backward=false)=0;	

	/**
	*Currently not used. Will allow editing of the Enumerator in the 
	*future, in which case this will return whether or not this instance
	*of the enumerator allows adding or removing of elements
	*@return bool true if the enumerator allows editing, otherwise false.
	*/
	bool supportsEditing(){
		return supportsEditing_;
	};
protected:
	bool supportsEditing_;
};



/**
*EnumeratorContainer is based on some COLLECTION class that represents a collection
*class of some sort, i.e. std::vector<>, std::list, et al.
*The internal implementation counts on the collection having a common interface to 
*STL's collection classes.
*The collection must support forward and reverse iterators
*The COLLECTION type specifies the full collection associated with 
*the enumerator. FOr example, an enumerator container of Object* using 
*a std::vector as it's collection would like this:
*<pre>
*	EnumeratorContainer<std::vector<Object*>,Object*> objectVecEnumerator;
*</pre>
*The COLLECTION_TYPE represents the type of an individual element in the enumerator.
*Passing in a reference to the collection variable in the contstructor will automatically 
*set up the internal iterator, nothing further need be done. Alternatively, you may
*call the initContainer() method with a reference to the collection
*/
template <class COLLECTION, class COLLECTION_TYPE> class  EnumeratorContainer : public Enumerator<COLLECTION_TYPE>{
public:
	
	EnumeratorContainer( COLLECTION &container ){
		container_ = &container;
		this->reset();
		supportsEditing_ = true;
	};

	EnumeratorContainer(){
		supportsEditing_ = true;
	};

	virtual ~EnumeratorContainer(){};

	/**
	*Initializes the container with a reference to an
	*existing collection
	*/
	virtual void initContainer( COLLECTION &container ){
		container_ = &container;
		this->reset();	
	};

	virtual bool hasMoreElements(const bool& backward=false){
		bool result = false;
		if ( true == backward ){
			result = containerIterator_ != container_->begin();
		}
		else{
			result = containerIterator_ != container_->end();
		}
		return result;
	};

	virtual COLLECTION_TYPE nextElement(){
		if (containerIterator_ != container_->end() ){			
			return *containerIterator_++;
		}
		else {
			return *container_->end();
		}
	};

	virtual COLLECTION_TYPE prevElement(){
		if (containerIterator_ != container_->begin() ){			
			return *--containerIterator_;
		}		
		else {
			return *container_->end();
		}
	};

	virtual void reset(const bool& backward=false){
		if ( true != backward ){
			containerIterator_ = container_->begin();
		}
		else {
			containerIterator_ = container_->end();			
		}
	};

	/**
	*returns a pointer to the Enumerator interface of this
	*container. Automatically resets the collection before 
	*returning the pointer.
	*@return Enumerator<COLLECTION_TYPE> a pointer to the 
	*collection as an Enumerator interface.
	*/
	virtual Enumerator<COLLECTION_TYPE>* getEnumerator(){
		this->reset();
		return (Enumerator<COLLECTION_TYPE>*)this;
	};
private:
	typename COLLECTION::iterator containerIterator_;	
	COLLECTION* container_;
};

/**
*EnumeratorMapContainer is based on some COLLECTION class that represents 
*an  associative collection of some sort, i.e. std::map<>
*The internal implementation counts on the collection having a common interface to 
*STL's collection classes.
*The collection must support forward and reverse iterators
*The COLLECTION type specifies the full collection associated with 
*the enumerator. FOr example, an enumerator container of Object* using 
*a std::map as it's collection would like this:
*<pre>
*	EnumeratorMapContainer<std::map<String,Object*>,Object*> objectMapEnumerator;
*</pre>
*The COLLECTION_TYPE represents the type of an individual element in the enumerator.
*In EnumeratorMapContainer the enumeration will only return the value of the maps
*pair, not the key.
*/
template <class COLLECTION, class COLLECTION_TYPE> class  EnumeratorMapContainer : public Enumerator<COLLECTION_TYPE>{
public:
	EnumeratorMapContainer( COLLECTION &container ){
		container_ = &container;
		this->reset();
	};

	EnumeratorMapContainer(){};

	virtual ~EnumeratorMapContainer(){};

	virtual void initContainer( COLLECTION &container ){
		container_ = &container;
		this->reset();	
	};

	virtual Enumerator<COLLECTION_TYPE>* getEnumerator(){
		this->reset();
		return (Enumerator<COLLECTION_TYPE>*)this;
	};

	virtual bool hasMoreElements(const bool& backward=false){
		bool result = false;
		if ( true == backward ){
			result = containerIterator_ != container_->begin();
		}
		else{
			result = containerIterator_ != container_->end();
		}
		return result;
	};

	virtual COLLECTION_TYPE nextElement(){
		if (containerIterator_ != container_->end() ){
			COLLECTION_TYPE result = containerIterator_->second;
			containerIterator_ ++;
			return result;
		}
		else {
			return NULL;
		}
	};

	virtual COLLECTION_TYPE prevElement(){
		if (containerIterator_ != container_->begin() ){
			COLLECTION_TYPE result = containerIterator_->second;
			containerIterator_ --;
			return result;
		}
		else {
			return NULL;
		}
	};

	virtual void reset(const bool& backward=false){
		if ( true != backward ){
			containerIterator_ = container_->begin();
		}
		else {
			containerIterator_ = (container_->end());			
		}
	};

private:
	typename COLLECTION::iterator containerIterator_;	
	COLLECTION* container_;
};

};//end of namespace xmake


#endif //_ENUMERATOR_H__



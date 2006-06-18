#ifndef _VCF_OBJECT_H__
#define _VCF_OBJECT_H__
//Object.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{


class Class;
class Mutex;

#define OBJECT_CLASSID		"ED88C099-26AB-11d4-B539-00C04F0196DA"

/**
\class Object Object.h "vcf/FoundationKit/Object.h"
Base class for the entire Visual Component Framework.
New as of July 5,2001, Object will also support
refcounting for those who need this kind of support.
There are several places in the ApplicationKit that will need to make use
of this fairly soon.

Also Object supports a new technique for destroying Object derived instances.
In general, in C++, when creating a destroying an object instance on the heap (free-store)
you would use the operator delete() function. This is being phased out in the VCF
for a variety of reasons, in favor of a different scheme.
Destroying the memory now happens in two ways: The first is the equivalent of the operator delete()
call. This involves calling the objects free() method, which will call the virtual destroy() method
before calling operator delete() on itself;
The second way an object can be destroyed is if it's refcount drops to 0, at which point the object's
free() method will be invoked. Calling the object's release() method decrements the reference count
on the object.
By default if an object is created on the heap via new, and no one addref()'s it, then a
single call to the release() method will free up it's memory.

Object::destroy() is a virtual method, where common shared cleanup may take place. Because this
is called before the delete() method, it is still safe to call virtual methods and have them
execute correctly (in C++ virtual calls inside of a constructor or destructor are not allowed
and if made then the behaviour is undefined).

Classes which are heap based (such as all of the UI classes that derive from Component) should
define their destructor as having protected access. In addition the majority of the cleanup code
should be placed in the overridden Object::destroy() method as opposed to the class destructor.
Anything that requires method calls to other object or the class itself (particularly if the method
is a virtual one) should be moved to the

Semantics of the addRef/release usage are as follows:
An object's refcount indicates "ownership " of the object. In other words, the "owner" of the
object is responsible for releasing it's hold on the object, thus decrementing the objects
refcount, which, when reduced to 0, causes the object to be deleted. This is also known as
a strong reference to an object, as opposed to a weak reference where the "owner" doesn't
claim any responsibility over the object.

Note that this whole scheme is aimed at heap based objects. Many objects that are created on the stack
do not need this. For example, common utility objects like Rect or Point do not need this - they
can be created on the stack.
*/
class FOUNDATIONKIT_API Object {
public:
	Object();

	virtual ~Object();

	/**
	This is going to be removed from the bext release
	@deprecated
	*/
	void init();

	/**
	Call this method to free up the memory of the class
	for heap based objects. Use this instead of calling the 
	operator delete. For example:
	\code
	Mutex*  m = new Mutex();
	m->free();
	\endcode
	This will ensure that the destroy() method is called 
	\em before calling operator delete which allows a 
	deriving class to override the destroy methods and safely
	call virtual methods from within it.
	*/
	void free();

	/**
	*increments the reference count of the object
	@param Object* the optional owner of the new referenced object
	for use in future, more sophisticated refcounting schemes
	@return unsigned long the current reference count of the object
	*/
	virtual unsigned long addRef(Object* owner=NULL);

	/**
	decrements the reference count of the object
	@param Object* the optional owner of the new referenced object
	for use in future, more sophisticated refcounting schemes
	when the refCount_ drops to 0 the object is destroyed
	*/
	virtual unsigned long release(Object* owner=NULL);

	/**
	returns the number of outstanding references for this object
	*/
	unsigned long getRefCount(){
		return refCount_;
	}

    /**
    returns a string representation of the object
     */
    virtual String toString();

    /**
    returns the class name of the object.
    */
    String getClassName();

	/**
	This determines if object is equal to this
	the equivalent of operator ==()
	*/
	virtual bool isEqual( Object* object ) const {
		return ( object == this );
	};

	/**
	Copies the data from source to this object.
	This is the equivalent of operator=()
	*/
	virtual void copy( Object* source ) {};

	/**
	Makes a complete clone of this object.
	A typical implementation might be:
	\code
	virtual Object* clone( bool deep ) {
		return new MyObject( this );
	}
	\endcode
	In which the implementer simply creates a new instance on the heap
	and calls the copy constructor.
	Objects which support cloning <b>should</b> also have a copy
	constructor defined as well.

	@param bool deep if deep is true then any object instances
	that this object owns should probably be cloned as well, with
	full new copies made. Otherwise it would be acceptable to simply
	copy the pointer values. The default value is for deep cloning to
	be false.
	@return Object a new instance that should be an copy of this. If
	the object doesn't support cloning the return will value will be NULL.
	*/
	virtual Object* clone( bool deep=false ) {
		return NULL;
	};

	/**
	returns the RTTI Class instance associated object
	of this type
	*/
	Class* getClass() ;

	/**
	returns a hash value that represents the object instance
	*/
	virtual unsigned long hash();

	/**
	Ptr is a smart pointer class for use with refcounted objects.
	This class should <b><i>NEVER</i></b> be created on the heap,
	instead create instances on the stack.
	*/
	template <class OBJECT_TYPE> class Ptr {
	public:
		Ptr(){
			ptr_ = NULL;
		}

		/**
		constructor for the Ptr passing in a
		new instance of an OBJECT_TYPE
		*/
		Ptr( OBJECT_TYPE* o ){
			ptr_ = o;
		}

		/**
		allows access to the underlying pointer
		*/
		OBJECT_TYPE* operator ->() {
			return ptr_;
		}

		/**
		conversion operator
		@return OBJECT_TYPE returns the underlying pointer
		*/
		operator OBJECT_TYPE* () {
			return ptr_;
		}

		/**
		equality operator.
		Compares the object passed in with the internal
		object.
		*@param OBJECT_TYPE the object to compare with. Current
		comparison is only a simple pointer comparison. This may
		become more sophisticated.
		*/
		bool operator ==( OBJECT_TYPE* object ) const	{
			return 	ptr_ == object;
		}

		/**
		assignment operator.
		assigns a new object value to the Ptr instance.
		*/
		Ptr& operator= ( OBJECT_TYPE* o ) {
			ptr_ = o;
			return *this;
		}

		bool operator !()	{
			return (NULL == ptr_ ) ? true: false;
		}

		OBJECT_TYPE& operator *() {
			return *ptr_;
		}

		OBJECT_TYPE** operator &( ) {
			return &ptr_;
		}

		virtual ~Ptr(){
			if ( NULL != ptr_ ){
				ptr_->release();
			}
		}
	private:
		OBJECT_TYPE* ptr_;
	};


	/**
	indicates whether or not debug memory should be tracked. Note
	that debug memory is tracked <b>only</b> in debug builds
	(meaning the VCF has been compiled with the _DEBUG symbol
	defined). Memory tracking is turned off for release builds.
	@param bool if this is true, then memory will be tracked, and when
	the FoundationKit::terminate() is called, the system will
	check how many outstanding objects (i.e. any class instance that
	derives from VCF::Object directly or indirectly) there are.
	It will then perform a diagnostic dump, displaying the memory
	address and the class name of the object instance
	*/
	static void trackDebugMemory( const bool& trackMemory );

	/**
	returns whether or not debug memory tracking is on
	@return bool true if debug memory tracking is turned on, otherwise
	false
	*/
	static bool isDebugMemoryTracked();

	/**
	returns the total number of objects currently allocated. Only
	meaningful for _DEBUG builds with memory tracking turned on.
	@return ulong32 if debug memory tracking is turned on, and the
	_DEBUG symbol is defined, then this value will be the total count
	of object instances that are currently allocated. For any other
	conditions it will return 0.
	*/
	static ulong32 objectAllocationCount();
#ifdef _VCF_DEBUG_NEW
	public:

	static Mutex* accessMutex_;

	static void dumpDebugInfo();

	//we're gonna declare operator new here so we can track
	//VCF related memory leaks
	void* operator new( size_t allocationSize );

	void operator delete( void* objectPointer );

	void* operator new( size_t allocationSize, void* p ) {
		return ::operator new(  allocationSize, p );
	}

#if !defined(VCF_GCC) && !defined(VCF_BCC)
	void operator delete( void* objectPointer, void* p ) {
		::operator delete( objectPointer, p );
	}
#endif


	protected:

	class DebugInfo {
	public:
		DebugInfo() : objectAllocationSize_(0), objAddress_(0) {

		}
		size_t objectAllocationSize_;
		unsigned long objAddress_;
	};

	static std::map<unsigned long,DebugInfo> debugAllocationMap;
	static bool trackingDebugMemory;

#endif //_VCF_DEBUG_NEW

protected:
	/**
	called by the free() method. Should be overriden
	and any clean up code performed here
	*/
	virtual void destroy();

	unsigned long refCount_;
private:

};

};


#endif // _VCF_OBJECT_H__

/**
$Id$
*/
//Object.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */
#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

#ifdef USE_VCF_NEW
std::list<void*> Object::allocatedObjects;
#endif

Object::Object()
{
	//initialized to zero
	//so a release after creating this object
	//will automaitically free it
	refCount_ = 0;

}

Object::~Object()
{

}

void Object::init()
{

}

void Object::destroy()
{

}

void Object::free()
{
	refCount_ = 0;

	destroy();

	delete this;
}

unsigned long Object::addRef(Object* owner)
{
	refCount_ ++;

	return refCount_;
}

unsigned long Object::release(Object* owner)
{
	if ( refCount_ > 0 ) {
		refCount_ --;
	}

	if ( 0 == refCount_ )  {
		free();
		return 0;
	}

	return refCount_;
}

Class* Object::getClass()
{

	Class* result = ClassRegistry::getClass( this );
	if ( NULL != result ){
		result->setSource( this );
	}
	return result;
}

String Object::getClassName()
{
	String result = "";
	Class* clazz = this->getClass();
	if ( NULL != clazz ){
		result = clazz->getClassName();
	}
	else {
#ifdef VCF_RTTI
		result = StringUtils::getClassNameFromTypeInfo( typeid(*this) );
#endif
	}

	return result;
}

String Object::toString()
{
	String result = "";
	char info[256];
	sprintf( info, "%s @ %p, refcount: %d",
		     this->getClassName().c_str(), this, (int)refCount_ );
	result += info;
	return result;
}

unsigned long Object::hash()
{
	return (unsigned long)this;
}


void Object::trackDebugMemory( const bool& trackMemory )
{
#ifdef _VCF_DEBUG_NEW
	Object::trackingDebugMemory = trackMemory;
#endif //_VCF_DEBUG_NEW
}


bool Object::isDebugMemoryTracked()
{
#ifdef _VCF_DEBUG_NEW
	return Object::trackingDebugMemory;
#else
	return false;
#endif //_VCF_DEBUG_NEW
}


#ifdef _VCF_DEBUG_NEW

Mutex* Object::accessMutex_ = NULL;

bool Object::trackingDebugMemory = true;

std::map<unsigned long,Object::DebugInfo> Object::debugAllocationMap;



void * Object::operator new( size_t allocationSize )
{

	void *newPtr = ::operator new( allocationSize );
	if ( true == Object::trackingDebugMemory ) {
		if( newPtr != 0 ){
			if ( NULL != Object::accessMutex_ ) {
				Object::accessMutex_->lock();
			}

			DebugInfo info;
			info.objAddress_ = (unsigned long)newPtr;
			info.objectAllocationSize_ = allocationSize;
			Object::debugAllocationMap[info.objAddress_] = info;

			if ( NULL != Object::accessMutex_ ) {
				Object::accessMutex_->unlock();
			}
		}
	}

    return newPtr;
}

void Object::operator delete( void *objectPointer )
{
	if ( true == Object::trackingDebugMemory ) {
		if ( NULL != Object::accessMutex_ ) {
			Object::accessMutex_->lock();
		}

		std::map<unsigned long,Object::DebugInfo>::iterator found;
		found = Object::debugAllocationMap.find( (unsigned long)objectPointer );
		if ( found != Object::debugAllocationMap.end() ) {

			Object::debugAllocationMap.erase( found );
		}

		if ( NULL != Object::accessMutex_ ) {
			Object::accessMutex_->unlock();
		}
	}

	::operator delete ( objectPointer );
}

void Object::dumpDebugInfo()
{
	if ( true == Object::trackingDebugMemory ) {
		if ( !Object::debugAllocationMap.empty() ) {
			StringUtils::trace( "Oops there are objects still left. Dumping memory info...\n" );
			StringUtils::traceWithArgs( "There are %d objects still left over that did not get deleted\n",
				Object::debugAllocationMap.size() );

			std::map<unsigned long,Object::DebugInfo>::const_iterator it = Object::debugAllocationMap.begin();
			while ( it != Object::debugAllocationMap.end ()  ) {
				const DebugInfo& info = it->second;
				String className = "unknown";

				try {
					Object* o = (Object*)info.objAddress_;
					className = StringUtils::getClassNameFromTypeInfo( typeid(*o) );
				}
				catch ( ... ) {
					className = "unknown<exception occured retreiving class name>";
				}

				StringUtils::traceWithArgs( "\tObject (type: %S) @ %p, allocated size of %d bytes\n",
												className.c_str(), info.objAddress_, info.objectAllocationSize_ );


				it ++;
			}

			Object::debugAllocationMap.clear();

			StringUtils::trace( "Finished Object::dumpDebugInfo()\n" );
		}
	}
	else {
		StringUtils::trace( "There is no debug memory information to track because Object::trackingDebugMemory is false \n" );
		StringUtils::trace( "If you would like to track memory, call Object::trackDebugMemory( true ) before initFoundationKit() \n" );
	}
}

#endif //_VCF_DEBUG_NEW

ulong32 Object::objectAllocationCount()
{
#ifdef _VCF_DEBUG_NEW
	std::map<unsigned long,Object::DebugInfo>::const_iterator it = Object::debugAllocationMap.begin();
	ulong32 totmem = 0;
	while ( it != Object::debugAllocationMap.end ()  ) {
		const DebugInfo& info = it->second;

		totmem += info.objectAllocationSize_;

		it ++;
	}
	StringUtils::traceWithArgs( "Total memory allocated: %d bytes\n", totmem );

	return Object::debugAllocationMap.size();
#endif
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.1.2.3  2004/05/03 03:44:53  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.19  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.18.2.4  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.18.2.3  2003/09/19 21:24:06  ddiego
*small changes
*
*Revision 1.18.2.2  2003/09/16 02:41:40  ddiego
*added a small fix for adding a mutex to prevent multithreaded programs from
*crashing in debug mode.
*
*Revision 1.18.2.1  2003/08/28 21:46:56  ddiego
*added escape reponse...
*
*Revision 1.18  2003/08/09 02:56:45  ddiego
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
*Revision 1.17.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.17.2.1  2003/06/13 03:06:40  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.17  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.3  2003/05/15 03:01:03  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.16.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.16.2.1  2003/03/12 03:13:16  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.8.2  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.15.8.1  2003/01/04 06:12:27  ddiego
*fixed a crash in X11GraphicsToolkit - an error in how colors were being freed
*added support for titles, getting the focus control, and grabbing the mouse !
*
*Revision 1.15  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.14.6.1  2002/07/31 04:52:50  ddiego
*fixed up some code for correctly jumping to the correct part of the editor when
*you click on a class or class member. Also fixed some bugs that happened cause
*class object where not being addded correctly to the Project
*Added a change to Object so that Object::toString dumps out the refcount in it's
*default implementation.
*Fixed an issue with the focus not being routed to the editor correctly on double clicks
*of the WorkspaceTree. This may be an under  the hood implementation error of the
*VCF or just how Win32 works, not really sure, but hte solution was to post the event
*and tehn set the focus...rather odd..
*
*Revision 1.14  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.13.4.3  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.13.4.2  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.13.4.1  2002/03/20 21:53:02  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.13  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/



//OSXSystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/OSXLocalePeer.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/OSXResourceBundle.h"
#include "vcf/FoundationKit/OSXLibraryPeer.h"
#include "vcf/FoundationKit/RunLoopPeer.h"
#include "vcf/FoundationKit/OSXRunLoopPeer.h"
#include "vcf/FoundationKit/OSXRunLoopTimerPeer.h"
#include "vcf/FoundationKit/OSXRunLoopSourcePeer.h"
#include "vcf/FoundationKit/ThreadManagerPeer.h"
#include "vcf/FoundationKit/OSXThreadManagerPeer.h"

using namespace VCF;

OSXSystemToolkit::OSXSystemToolkit()
{
}

OSXSystemToolkit::~OSXSystemToolkit()
{
}

ProcessPeer* OSXSystemToolkit::internal_createProcessPeer( Process* process )
{
	ProcessPeer* result = NULL;

	result = new OSXProcessPeer();

	return result;
}

ThreadPeer* OSXSystemToolkit::internal_createThreadPeer( Thread* thread, bool mainThread )
{
	return new OSXThread( thread, mainThread );
}

ThreadManagerPeer* OSXSystemToolkit::internal_createThreadManagerPeer()
{
	return new OSXThreadManagerPeer();
}

RunLoopPeer* OSXSystemToolkit::internal_createRunLoopPeer( RunLoop* runLoop )
{
	return new OSXRunLoopPeer( runLoop );
}

RunLoopTimerPeer* OSXSystemToolkit::internal_createRunLoopTimerPeer( RunLoopTimer* timer )
{
    return new OSXRunLoopTimerPeer( timer );
}

RunLoopSourcePeer* OSXSystemToolkit::internal_createRunLoopSourcePeer( RunLoopSource* source )
{
    return new OSXRunLoopSourcePeer( source );
}
		
SystemPeer* OSXSystemToolkit::internal_createSystemPeer()
{
	return new OSXSystemPeer();
}

SemaphorePeer* OSXSystemToolkit::internal_createSemaphorePeer( int32 initialCount, int32 maxCount )
{
	return new OSXSemaphore( initialCount, maxCount );
}

RegistryPeer* OSXSystemToolkit::internal_createRegistryPeer( Registry* registry )
{
	return NULL;//new LinuxRegistry();
}

MutexPeer* OSXSystemToolkit::internal_createMutexPeer( Mutex* mutex )
{
	return new OSXMutex(  );
}

ConditionPeer* OSXSystemToolkit::internal_createConditionPeer( Condition* condition )
{
	return new OSXConditionPeer(condition);
}

LibraryPeer* OSXSystemToolkit::internal_createLibraryPeer( Library* library )
{
	return new OSXLibraryPeer();
}

FilePeer* OSXSystemToolkit::internal_createFilePeer( File* file )
{
	return new OSXFilePeer( file );
}

FileStreamPeer* OSXSystemToolkit::internal_createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType )
{
	return new OSXFileStream( filename, accessType );
}

FileStreamPeer* OSXSystemToolkit::internal_createFileStreamPeer( File* file )
{
	return new OSXFileStream( file );
}

ProcessIORedirectionPeer* OSXSystemToolkit::internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{

	//result->setProcess( process );
	return 	NULL;//result;
}

LocalePeer* OSXSystemToolkit::internal_createLocalePeer()
{
    return new OSXLocalePeer();
}

ResourceBundlePeer* OSXSystemToolkit::internal_createResourceBundlePeer()
{
	return new OSXResourceBundle();
}


/**
$Id$
*/

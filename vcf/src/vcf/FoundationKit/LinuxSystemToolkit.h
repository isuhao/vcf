#ifndef _VCF_LINUXSYSTEMTOOLKIT_H__
#define _VCF_LINUXSYSTEMTOOLKIT_H__
//LinuxSystemToolkit.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class LinuxSystemToolkit : public SystemToolkit
{
public:

	LinuxSystemToolkit();

	virtual ~LinuxSystemToolkit();

	/**
	*creates a new ProcessPeer instance
	*/
	virtual ProcessPeer* internal_createProcessPeer( Process* process );

	virtual ProcessIORedirectionPeer*
	internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process );
	/**
	*creates a new ThreadPeer instance
	*/
	virtual ThreadPeer* internal_createThreadPeer( Thread* thread, bool mainThread );

	virtual RunLoopPeer* internal_createRunLoopPeer( RunLoop* runLoop );
	virtual RunLoopTimerPeer* internal_createRunLoopTimerPeer( RunLoopTimer* timer );
	virtual RunLoopSourcePeer* internal_createRunLoopSourcePeer( RunLoopSource* source );

    virtual ThreadManagerPeer* internal_createThreadManagerPeer();


	/**
	*creates a new system peer
	*/
	virtual SystemPeer* internal_createSystemPeer();

	virtual SemaphorePeer* internal_createSemaphorePeer( int32 initialCount,
	                                                     int32 maxCount );

	virtual RegistryPeer* internal_createRegistryPeer( Registry* registry );

	virtual MutexPeer* internal_createMutexPeer( Mutex* mutex );

	virtual ConditionPeer* internal_createConditionPeer( Condition* condition );

	virtual LibraryPeer* internal_createLibraryPeer( Library* library );

	virtual FilePeer* internal_createFilePeer( File* file );

	virtual FileStreamPeer*
	internal_createFileStreamPeer( const String& filename,
	                               const FileStreamAccessType& accessType );

	virtual FileStreamPeer* internal_createFileStreamPeer( File* file );

	virtual LocalePeer* internal_createLocalePeer();

	virtual ResourceBundlePeer* internal_createResourceBundlePeer();
};

}

#endif // _VCF_LINUXSYSTEMTOOLKIT_H__

/**
$Id$
*/

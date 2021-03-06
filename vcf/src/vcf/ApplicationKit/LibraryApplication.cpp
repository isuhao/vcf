//LibraryApplication.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//LibraryApplication.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"
#include "vcf/ApplicationKit/ApplicationResourceBundle.h"
#include "vcf/ApplicationKit/DocumentManager.h"

VCF::Map<VCF::String,VCF::LibraryApplication*> VCF::LibraryApplication::namedLibraryAppMap;


using namespace VCF;



LibraryApplication::LibraryApplication():
	resourceBundle_(NULL)
{
	ApplicationKit::init(0, NULL);



	applicationPeer_ = UIToolkit::createApplicationPeer();
	applicationPeer_->setApplication( this );

/*
#if defined( VCF_WIN ) && defined ( VCF_MSC )
	//load the BlacBox error trapper
	try {
		Library lib( L"BlackBox.dll" );
	}
	catch (...) {
		StringUtils::trace( "Unable to load the BlackBox error detection library\n" );
	}
#endif
	*/
}

LibraryApplication::~LibraryApplication()
{
	if ( NULL != resourceBundle_ ) {
		delete resourceBundle_;
	}
	resourceBundle_ = NULL;

	delete applicationPeer_;
	applicationPeer_ = NULL;

	ApplicationKit::terminate();
}

void LibraryApplication::setName( const String& name )
{
	Component::setName( name );

	std::map<String,LibraryApplication*>::iterator found = 	LibraryApplication::namedLibraryAppMap.find( getName() );
	if ( found != LibraryApplication::namedLibraryAppMap.end() ) {
		LibraryApplication::namedLibraryAppMap[ getName() ] = this;
	}
}

GraphicsResourceBundle* LibraryApplication::getResourceBundle()
{
	if ( NULL == resourceBundle_ ) {
		//create it on demand
		resourceBundle_ = new ApplicationResourceBundle(this);
	}

	return resourceBundle_;
}

Enumerator<VCF::LibraryApplication*>* LibraryApplication::getRegisteredLibraries()
{
	return LibraryApplication::namedLibraryAppMap.getEnumerator();
}

void LibraryApplication::registerLibrary( VCF::LibraryApplication* libraryApp )
{
	LibraryApplication::namedLibraryAppMap[ libraryApp->getName() ] = libraryApp;

	DocumentManager* mgr = DocumentManager::getDocumentManager();
	if ( NULL != mgr ) {
		mgr->initFromApp( libraryApp );
	}
}


void LibraryApplication::unRegisterLibrary( VCF::LibraryApplication* libraryApp )
{
	std::map<String,LibraryApplication*>::iterator found = 	LibraryApplication::namedLibraryAppMap.find( libraryApp->getName() );
	if ( found != LibraryApplication::namedLibraryAppMap.end() ) {
		LibraryApplication::namedLibraryAppMap.erase( found );
	}
}

VCF::LibraryApplication* LibraryApplication::getRegisteredLibraryApplication( const String& libName )
{
	VCF::LibraryApplication* result = NULL;

	std::map<String,LibraryApplication*>::iterator found = 	LibraryApplication::namedLibraryAppMap.find( libName );
	if ( found != LibraryApplication::namedLibraryAppMap.end() ) {
		result = found->second;
	}

	return result;
}


GraphicsResourceBundle* LibraryApplication::getResourceBundle( const String& libName )
{
	GraphicsResourceBundle* result = NULL;
	LibraryApplication* libApp = LibraryApplication::getRegisteredLibraryApplication( libName );
	if ( NULL != libApp ) {
		result = libApp->getResourceBundle();
	}

	return result;
}

void LibraryApplication::load( VCF::LibraryApplication* libraryApp )
{

}

void LibraryApplication::unload( VCF::LibraryApplication* libraryApp )
{

}

void LibraryApplication::initLibraryRegistrar()
{
	
}

void LibraryApplication::clearLibraryRegistrar()
{
	LibraryApplication::namedLibraryAppMap.clear();
}


/**
$Id$
*/

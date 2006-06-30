//CommonFileSaveDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */
#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

CommonFileSaveDialog::CommonFileSaveDialog( Control* owner, const String& startDir )
{
	peer_ = UIToolkit::createCommonFileSaveDialogPeer( owner );
	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL CommonFileDialogPeer, UIToolkit::createCommonFileSaveDialogPeer() is probably not implemented correctly") );		 
	}

	if ( startDir.size() > 0 ){
		setDirectory( startDir );
	}

	setTitle( "Save" );
}

CommonFileSaveDialog::~CommonFileSaveDialog()
{
	delete peer_;
}


bool CommonFileSaveDialog::execute()
{
	return peer_->execute();
}


/**
$Id$
*/

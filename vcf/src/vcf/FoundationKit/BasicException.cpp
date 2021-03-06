//BasicException.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


BasicException::BasicException(const String & message)
{
	message_ = message;
	//JC - I commented this out - I am not sure want to FORCE 
	//this kind of output? It can clutter up the command line.
	//System::println( "Exception: " + message_ );
}

BasicException::BasicException( const VCF::String & message, const int lineNumber )
{
	message_ = message;
#ifdef _DEBUG
	char txt[256];
	sprintf( txt, "\nerror at line number %d", lineNumber );
	message_ += txt;
#endif

	//JC - I commented this out - I am not sure want to FORCE 
	//this kind of output? It can clutter up the command line.
	//System::println( "Exception: " + message_ );
	
}

String BasicException::getMessage() const
{
	return message_;
}

void BasicException::setMessage( const VCF::String& message )
{
	message_ = message;
}


/**
$Id$
*/

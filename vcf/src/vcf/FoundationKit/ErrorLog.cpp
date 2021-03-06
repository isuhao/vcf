//ErrorLog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ErrorLog.h

#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


ErrorLog::ErrorLog( const String& ouputFilename ):
	outputFileName_(ouputFilename)
{
	if ( outputFileName_.empty() ) {
		outputFileName_ = "errorLog.log";
	}

	System::setErrorLog( this );

    try {
        fs.reset(new FileOutputStream( outputFileName_ ));
        tos.reset(new TextOutputStream(fs.get()));
    }
	catch (...) {
		throw FileIOError( MAKE_ERROR_MSG_2("Unknown Exception accessing the log file: \"" + outputFileName_ + "\"") );
	}
}

ErrorLog::~ErrorLog()
{
	System::setErrorLog( NULL );
}

void ErrorLog::toLog( const String& text )
{
	try {
		tos->write( text );
	}
	catch ( BasicException& e ) {
		throw e;
	}
	catch (...) {
		throw FileIOError( MAKE_ERROR_MSG_2("Unknown Exception accessing the log file: \"" + outputFileName_ + "\"") );
	}

}


/**
$Id$
*/

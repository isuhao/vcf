//BasicOutputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

namespace VCF {


BasicOutputStream::BasicOutputStream()
{
	init();
}

BasicOutputStream::~BasicOutputStream()
{

}

BasicOutputStream::BasicOutputStream( OutputStream* outStream )
{
	init();
	outputStream_ = outStream;
}

void BasicOutputStream::init()
{
	outputStream_ = NULL;
}

void BasicOutputStream::clear()
{
	outStream_.clear();
}

void BasicOutputStream::seek(const uint64& offset, const SeekType& offsetFrom)
{
	if ( NULL != outputStream_ ) {
		outputStream_->seek( offset, offsetFrom );
	}

	switch ( offsetFrom ) {
		case stSeekFromStart: {
			outStream_.setSeekPos( offset );
		}
		break;

		case stSeekFromEnd: {
			outStream_.setSeekPos( outStream_.getSize() - offset );
		}
		break;

		case stSeekForwards: {
			outStream_.setSeekPos( outStream_.getSeekPos() + offset );
		}
		break;

		case stSeekBackwards: {
			outStream_.setSeekPos( outStream_.getSeekPos() - offset );
		}
		break;
	}
}

uint64 BasicOutputStream::getSize()
{
	return outStream_.getSize();
}

uchar* BasicOutputStream::getBuffer()
{
	if ( NULL != outputStream_ ){
		return outputStream_->getBuffer();
	}

	return outStream_.getBuffer();
}

uint64 BasicOutputStream::write( const unsigned char* bytesToRead, uint64 sizeOfBytes )
{
	uint64 result = 0;
	result = outStream_.write( bytesToRead, sizeOfBytes );
	if ( NULL != outputStream_ ){
		result = outputStream_->write( bytesToRead, sizeOfBytes );
	}

	return result;
}


uint64 BasicOutputStream::getCurrentSeekPos()
{
	if ( NULL != outputStream_ ) {
		return outputStream_->getCurrentSeekPos();
	}
	return outStream_.getSeekPos();
}




};

/**
$Id$
*/

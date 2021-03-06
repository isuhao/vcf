////ZipKit.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "unzip.h"


#pragma comment(lib,"ZLib_vc6_sd.lib")


#define ZIPFILE		"C:\\Documents and Settings\\jcrafton\\My Documents\\bloomberg-mydocs.zip"

using namespace VCF;


class ZipInputStream : public InputStream {
public:
	ZipInputStream( InputStream* inStream );

	virtual ~ZipInputStream();

	virtual void seek(const uint64& offset, const SeekType& offsetFrom);

	virtual uint64 getSize();

	virtual uchar* getBuffer();

	virtual uint64 getCurrentSeekPos() ;

	virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes );

	virtual bool isEOS();
	
	InputStream* inputStream_;
	z_stream zstream_;
	CharMemStream<> uncompressedData_;
	unsigned char zipTmpData_[256];
	uint64 seekPos_;

};




class ZipOutputStream : public OutputStream {
public:

	enum {
		DataSize = 256
	};

	ZipOutputStream();
	ZipOutputStream( OutputStream* outStream );

	virtual ~ZipOutputStream();

	virtual void seek(const uint64& offset, const SeekType& offsetFrom);

	virtual uint64 getSize();

	virtual uchar* getBuffer();

	virtual uint64 getCurrentSeekPos();

	virtual uint64 write( const unsigned char* bytesToRead, uint64 sizeOfBytes );
	
	z_stream zstream_;
	CharMemStream<DataSize> compressedData_;
	unsigned char zipTmpData_[DataSize];

	void flush();
};










ZipInputStream::ZipInputStream( InputStream* inStream ):
	inputStream_(inStream),
	seekPos_(0)
{
	memset(&zstream_,0,sizeof(zstream_));
	if ( Z_OK != inflateInit( &zstream_ ) ) {
		//throw exception!!!
	}
}

ZipInputStream::~ZipInputStream()
{
	inflateEnd( &zstream_ );
}

void ZipInputStream::seek(const uint64& offset, const SeekType& offsetFrom)
{

}

uint64 ZipInputStream::getSize()
{
	 
	return inputStream_->getSize();
}

uchar* ZipInputStream::getBuffer()
{
	return uncompressedData_.getBuffer();
}

uint64 ZipInputStream::getCurrentSeekPos() 
{
	return seekPos_;
}

uint64 ZipInputStream::read( unsigned char* bytesToRead, uint64 sizeOfBytes )
{
	uint64 result = 0;
	//unsigned char* tmp = bytesToRead;

	if ( sizeOfBytes < uncompressedData_.getSeekPos() + seekPos_ ) {
		uint64 oldSeek = uncompressedData_.getSeekPos();
		uncompressedData_.setSeekPos( seekPos_ );

		result = uncompressedData_.read( bytesToRead, sizeOfBytes );
		seekPos_ += result;

		uncompressedData_.setSeekPos( oldSeek );
	}
	else {
		int res = 0;
		while ( result < sizeOfBytes && res != Z_STREAM_END) {
			unsigned char tmpBuf[256];
			memset(tmpBuf,0,sizeof(tmpBuf));
			
			uint64 readIn = inputStream_->read( &zipTmpData_[0], sizeof(zipTmpData_) );

			if ( readIn == 0 ) {
				break;
			}
			zstream_.next_in = zipTmpData_;
			zstream_.avail_in = readIn;


			do {
				zstream_.avail_out = sizeof(tmpBuf);
				zstream_.next_out = tmpBuf;

				res = inflate( &zstream_, Z_SYNC_FLUSH );



				VCF_ASSERT(res != Z_STREAM_ERROR);

				switch (res) {
					case Z_NEED_DICT: {
						res = Z_DATA_ERROR;     
					} //and fall through 

					case Z_DATA_ERROR:
					case Z_MEM_ERROR: {
						inflateEnd( &zstream_ );
						throw RuntimeException( "Error with zip stream, either a Z_DATA_ERROR or Z_MEM_ERROR occurred" );
						//out of while loop...
					}

					case Z_STREAM_END : {

					}
				}				
					
				uint64 have = sizeof(tmpBuf) - zstream_.avail_out;
				uncompressedData_.write( &tmpBuf[0], have );
				
				
				result +=  minVal<>(have,sizeOfBytes);
				
				//memcpy( tmp, &tmpBuf[0], have );
				
				//seekPos_ += have;
				
				//tmp += have;
				
			} while ( zstream_.avail_out == 0 && res != Z_STREAM_END);
		}

		inflateEnd( &zstream_ );

		uint64 oldSeek = uncompressedData_.getSeekPos();
		uncompressedData_.setSeekPos( seekPos_ );

		result = uncompressedData_.read( bytesToRead, sizeOfBytes );
		seekPos_ += result;

		uncompressedData_.setSeekPos( oldSeek );
	}


	return result;
}

bool ZipInputStream::isEOS()
{
	bool result = true;
	return result;
}












ZipOutputStream::ZipOutputStream()
{
	memset(&zstream_,0,sizeof(zstream_));
	memset(&zipTmpData_,1,sizeof(zipTmpData_));

	if ( Z_OK != deflateInit( &zstream_, Z_DEFAULT_COMPRESSION ) ) {
		//throw exception!!!
	}
}



ZipOutputStream::ZipOutputStream( OutputStream* outStream )
{
	memset(&zstream_,0,sizeof(zstream_));
	memset(&zipTmpData_,1,sizeof(zipTmpData_));

	if ( Z_OK != deflateInit( &zstream_, Z_DEFAULT_COMPRESSION ) ) {
		//throw exception!!!
	}
}

ZipOutputStream::~ZipOutputStream()
{
	deflateEnd( &zstream_ );
}

void ZipOutputStream::seek(const uint64& offset, const SeekType& offsetFrom)
{

}

uint64 ZipOutputStream::getSize()
{	
	uint64 result = compressedData_.getSize();

	return result;
}


uchar* ZipOutputStream::getBuffer()
{
	return compressedData_.getBuffer();
}

uint64 ZipOutputStream::getCurrentSeekPos()
{	
	uint64 result = 0;

	return result;
}


uint64 ZipOutputStream::write( const unsigned char* bytesToRead, uint64 sizeOfBytes )
{	
	uint64 result = 0;

	//unsigned char* tmpCopy = new unsigned char[sizeOfBytes];
	//memcpy(tmpCopy,bytesToRead,sizeOfBytes);



	zstream_.next_in = (unsigned char*)bytesToRead;
	zstream_.avail_in = sizeOfBytes;

	
	do {		
		if ( NULL == zstream_.next_out ) {
			zstream_.avail_out = sizeof(zipTmpData_);
			zstream_.next_out = zipTmpData_;
		}
		

		int res= deflate(&zstream_, Z_NO_FLUSH);
		if ( Z_STREAM_ERROR == res ) {
			//throw exception!
		}


		result += (sizeof(zipTmpData_) - zstream_.avail_out);

		if ( 0 == zstream_.avail_out ) {
			flush();
		}

	} while ( zstream_.avail_out == 0 );


	flush();

	//delete [] tmpCopy;

	return result;
}

void ZipOutputStream::flush()
{
	deflate(&zstream_, Z_FINISH);
	compressedData_.write( zipTmpData_, (sizeof(zipTmpData_) - zstream_.avail_out) );

	zstream_.next_out = NULL;
	zstream_.avail_out = 0;
}



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	

	{/*
		String data = "Hello how are you, this is some compressed text!";
		
		ZipOutputStream zos;
		
		//unsigned char tmp[300];
		//zos.write( tmp, sizeof(tmp) );
		//zos.flush();
		
		TextOutputStream tos(&zos);
		
		String str1 = "Part 1";
		String str2 = "Part 2";
		tos.write( str1 );
		
		tos.write( str2 );
		
		zos.flush();
		
		
		BasicInputStream bis( zos.getBuffer(), zos.getSize() );
		ZipInputStream zis(&bis);
		
		TextInputStream tis(&zis);
		
		String s;
		tis.read(s);
		tis.read(s);
		*/
	}
	

	{
		File f("spetz.txt", File::ofRead);
		uint64 fsize = f.getSize();

		uchar* bytes = new uchar[fsize + 256];
		memset(bytes,0,fsize + 256);

		FileInputStream* fis = f.getInputStream();
		fis->read( bytes, fsize );



		GenericMemoryBuffer<uchar> buf;

		uchar* tmp = bytes;
		buf.write( tmp, 256 );
		tmp += 256;
		buf.write( tmp, 256 );


		
		ZipOutputStream zos;
		zos.write( bytes, fsize );
		//zos.flush();


		BasicInputStream bis( zos.getBuffer(), zos.getSize() );
	

		ZipInputStream zis(&bis);
		

		uchar* bytes2 = new uchar[fsize + 256];

		uint64 rd = zis.read( bytes2, fsize );

		for ( size_t i=0;i<fsize;i++ ) {
			if ( bytes[i] != bytes2[i] ) {
				break;
			}
		}

		int res = memcmp( bytes, bytes2, fsize );


		delete fis;
		delete [] bytes;
		delete [] bytes2;
		
	}


	FoundationKit::terminate();
	return 0;
}



//VCFString.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/TextCodec.h"

#include <cwchar>

using namespace VCF;




UnicodeString::AnsiStringMap UnicodeString::allocatedAnsiStrings;


UnicodeString::UnicodeString(const std::string& rhs)
{
	UnicodeString::transformAnsiToUnicode( rhs.c_str(), rhs.size(), data_ );
}

UnicodeString::UnicodeString(const UnicodeString::AnsiChar* string )
{
	UnicodeString::transformAnsiToUnicode( string, strlen(string), data_ );
}

UnicodeString::UnicodeString(const UnicodeString::UniChar* string ):
	data_(string)
{

}


UnicodeString::UnicodeString(const UnicodeString::AnsiChar* string, UnicodeString::size_type stringLength )
{
	UnicodeString::transformAnsiToUnicode( string, stringLength, data_ );
}

UnicodeString::UnicodeString(const UnicodeString::UniChar* string, UnicodeString::size_type stringLength ):
	data_(string,stringLength)
{
}

UnicodeString::UnicodeString( size_type n, UnicodeString::AnsiChar c ):
	data_( n, UnicodeString::transformAnsiCharToUnicodeChar(c) )
{

}

UnicodeString::UnicodeString( size_type n, UnicodeString::UniChar c ):
	data_(n, c)
{

}


#ifdef VCF_OSX
UnicodeString::UnicodeString(const wchar_t* string )
{
    //!!!!!!!!!!!!!!!!!!MAJOR HACK ALERT!!!!!!!!!!!!!!!
    //Because *&^$%'n Apple doesn't provide wcslen we have to do this here - completely 
    //*&^#$%% LAME!!!!!! :(
    int strLength = 0;
    const wchar_t* P = string;
    while ( *P != 0 ) {        
        strLength ++;
        P++;
        
        if ( strLength >= 10000 ) { //arbitrarily stop after 10,000 characters? Lame as HELLL
            break;
        }
    }
     
    if ( *P == 0 ) {
        strLength ++;
    }
    
    
    int size = strLength;

	if ( !(size > 0) ) {
		throw RuntimeException( "size < 0 wcstombs() failed" );
	}

	UnicodeString::AnsiChar* tmp = new UnicodeString::AnsiChar[size+1];

	if ( wcstombs( tmp, string, strLength ) > 0 ) {
		tmp[size] = 0;
        UnicodeString::transformAnsiToUnicode( tmp, size, data_ );
	}

    delete [] tmp;
	tmp = NULL;
}
#endif


UnicodeString::~UnicodeString()
{
	garbageCollectAnsiStrings();
}

void UnicodeString::transformAnsiToUnicode( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength, UnicodeString::StringData& newStr )
{
	if ( stringLength == 0 ) {
		newStr.erase(0,newStr.size());
	}
	else {
	#ifdef VCF_WIN32
		int size = MultiByteToWideChar( CP_ACP, 0, str, stringLength, NULL, 0 );

		if ( !(size > 0) ) {
			throw RuntimeException( L"size > 0 MultiByteToWideChar() failed in UnicodeString::transformAnsiToUnicode()" );
		}

		UniChar* tmp = new UniChar[size];


		int err = MultiByteToWideChar( CP_ACP, 0, str, stringLength, (LPWSTR)tmp, size );
		if ( 0 == err ) {
			err = GetLastError();
		}

		newStr.assign( tmp, size );


		delete [] tmp;
    #elif VCF_OSX
        CFStringRef cfStr = 
            CFStringCreateWithCString( NULL, str, CFStringGetSystemEncoding() );
        
        int size = CFStringGetLength( cfStr );
        if ( !(size > 0) ) {
			throw RuntimeException( L"size <= 0 CFStringCreateWithCString() failed in UnicodeString::transformAnsiToUnicode()" );
		}

	   UniChar* unicodeText = new UniChar[size+1];
        CFRange range = {0,size};	
        CFStringGetCharacters(cfStr,range,unicodeText);
        unicodeText[size] = 0;     
        newStr.assign( unicodeText, size );   
        delete [] unicodeText;


	#elif VCF_POSIX
		int size = mbstowcs (NULL, str, stringLength );
		if ( !(size > 0) ) {
			throw RuntimeException( L"size < 0 mbstowcs() failed in UnicodeString::transformAnsiToUnicode()" );
		}
        
        
		UniChar* tmp = new UniChar[size];

		int err = mbstowcs( tmp, str, stringLength );
		if ( err > 0 ) {
			newStr.assign( tmp, size );
		}

		delete [] tmp;
	#endif
	}
}

UnicodeString::UniChar UnicodeString::transformAnsiCharToUnicodeChar( UnicodeString::AnsiChar c )
{
	UnicodeString::UniChar result = 0;

#ifdef VCF_WIN32
	int err = MultiByteToWideChar( CP_ACP, 0, &c, 1, (LPWSTR)&result, 1 );

	if ( !(err > 0) ) {
		throw RuntimeException( L"size > 0 MultiByteToWideChar() failed" );
	}

#elif VCF_OSX
    
    char str[2] = {c,0};
    CFStringRef cfStr = 
            CFStringCreateWithCString( NULL, str, CFStringGetSystemEncoding() );
        
    int size = CFStringGetLength( cfStr );
    if ( !(size > 0) ) {
        throw RuntimeException( L"size <= 0 CFStringCreateWithCString() failed in UnicodeString::transformAnsiToUnicode()" );
    }

    UniChar unicodeText[2];
    CFRange range = {0,2};	
    CFStringGetCharacters(cfStr,range,unicodeText);
    result = unicodeText[0];   
    
#elif VCF_POSIX
	UnicodeString::UniChar tmp[2] = {0,0};
	int err = mbstowcs( tmp, &c, 1 );
	result = tmp[0];
#endif

	return result;
}

UnicodeString::AnsiChar* UnicodeString::transformUnicodeToAnsi( const UnicodeString& str )
{
	UnicodeString::AnsiChar* result= NULL;
	int size = 0;
	int strLength = str.data_.size();

#ifdef VCF_WIN32

	if ( str.empty() ) {
		strLength = 1;
	}

	size = ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)str.data_.c_str(), strLength,
							NULL, 0, NULL, NULL );


	if ( !(size > 0) ) {
		throw RuntimeException( L"size > 0 WideCharToMultiByte() failed" );
	}

	result = new UnicodeString::AnsiChar[size+1];

	if (  0 == ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)str.data_.c_str(), strLength,
									result, size, NULL, NULL ) ) {
		//WideCharToMultiByte failed
		delete [] result;
		result = NULL;
	}
	else {
		result[size] = 0;
	}

#elif VCF_OSX    
    if ( str.length() > 0 ) {
        CFTextString tmp;
        tmp = str;
        CFRange r = {0,tmp.length()};
        CFIndex size2 = 0;
        CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false, NULL, 0, &size2 );
        
        if ( !(size2 > 0) ) {
            throw RuntimeException( L"size <= 0 CFStringGetBytes() failed" );
        } 
        
        result = new UnicodeString::AnsiChar[size2+1];
        
        if (  0 == ::CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false, 
                                        result, size2, &size2 ) ) {
            //CFStringGetBytes failed
            delete [] result;
            result = NULL;
        }
        else {
            result[size2] = 0;
        }
    }

#elif VCF_POSIX
	size = wcstombs( NULL, str.data_.c_str(), strLength );

	if ( !(size > 0) ) {
		throw RuntimeException( L"size < 0 wcstombs() failed" );
	}

	result = new UnicodeString::AnsiChar[size+1];

	if ( 0 <= wcstombs( result, str.data_.c_str(), strLength ) ) {
		delete [] result;
		result = NULL;
	}
	else {
		result[size] = 0;
	}
#endif
	return result;
}

const UnicodeString::AnsiChar* UnicodeString::decode_ansi( TextCodec* codec ) const
{
	UnicodeString::AnsiChar* result = NULL;
	ulong32 size = codec->convertToAnsiString( *this, NULL, 0 );
	if ( size > 0 ) {
		result = new UnicodeString::AnsiChar[size+1];
		codec->convertToAnsiString( *this, result, size );
		internal_registerAnsiStringForGarbageCollection( result );
	}

	return result;
}

UnicodeString UnicodeString::decode( TextCodec* codec ) const
{
	return codec->convertToUnicodeString( *this );
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString::AnsiChar* str, UnicodeString::size_type n )
{
	*this = codec->convertToUnicodeString( str, n );
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString& str )
{
	*this = codec->convertToUnicodeString( str );
}



void UnicodeString::garbageCollectAnsiStrings()
{
	if ( UnicodeString::allocatedAnsiStrings.empty() ) {
		return;
	}

	std::pair<UnicodeString::AnsiStringMap::iterator, UnicodeString::AnsiStringMap::iterator> range =
		UnicodeString::allocatedAnsiStrings.equal_range( this );

	std::vector<UnicodeString::AnsiStringMap::iterator> removeList;
	UnicodeString::AnsiStringMap::iterator it = range.first;
	while ( it != range.second ) {
		delete [] it->second;
		removeList.push_back( it );

		it ++;
	}

	std::vector<UnicodeString::AnsiStringMap::iterator>::iterator removeIt = removeList.begin();
	while ( removeIt != removeList.end() ) {
		UnicodeString::allocatedAnsiStrings.erase( *removeIt );
		removeIt ++;
	}
}

void UnicodeString::internal_registerAnsiStringForGarbageCollection( AnsiChar* str ) const
{
	UnicodeString::allocatedAnsiStrings.insert( AnsiStringMapEntry( this, str ) );
}


bool UnicodeString::operator ==( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ == tmp.data_;
}

bool UnicodeString::operator !=( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ != tmp.data_;
}

bool UnicodeString::operator >( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ > tmp.data_;
}

bool UnicodeString::operator >=( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ >= tmp.data_;
}

bool UnicodeString::operator <( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ < tmp.data_;
}

bool UnicodeString::operator <=( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ <= tmp.data_;
}


UnicodeString& UnicodeString::operator=(const UnicodeString::AnsiChar *s)
{
	 UnicodeString::transformAnsiToUnicode( s, strlen(s), data_ );

	return *this;
}

UnicodeString& UnicodeString::operator=(UnicodeString::AnsiChar c)
{
	data_ = UnicodeString::transformAnsiCharToUnicodeChar( c  );
	return *this;
}

const UnicodeString::AnsiChar* UnicodeString::ansi_c_str() const
{
	UnicodeString::AnsiChar* result = UnicodeString::transformUnicodeToAnsi( *this );

	internal_registerAnsiStringForGarbageCollection( result );

	return result;
}

UnicodeString& UnicodeString::operator+=(UnicodeString::AnsiChar c)
{
	data_ += UnicodeString::transformAnsiCharToUnicodeChar( c  );
	return *this;
}

UnicodeString& UnicodeString::operator+=(AnsiChar* rhs )
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	data_ += tmp.data_;

	return *this;
}

/*
UnicodeString UnicodeString::operator+( const AnsiChar& rhs )
{
	UnicodeString result;
	result = data_ + UnicodeString::transformAnsiCharToUnicodeChar( c  );
	return result;
}

UnicodeString UnicodeString::operator+( const AnsiChar* rhs )
{
	UnicodeString result;
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );

	result = data_ + tmp;
	return result;
}
*/

UnicodeString& UnicodeString::append(const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.append( tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::append(const UnicodeString::AnsiChar *s)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	data_.append( tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::append( size_type n, UnicodeString::AnsiChar c)
{
	data_.append( n, UnicodeString::transformAnsiCharToUnicodeChar( c  ) );

	return *this;
}

UnicodeString& UnicodeString::assign(const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.assign( tmp.data_ );
	return *this;
}

UnicodeString& UnicodeString::assign(const UnicodeString::AnsiChar *s)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	data_.assign( tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::assign( size_type n, UnicodeString::AnsiChar c)
{
	data_.assign( n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );

	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.insert( p0, tmp.data_ );
	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, const UnicodeString::AnsiChar *s)
{

	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	data_.insert( p0, tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.insert( p0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );

	return *this;
}

UnicodeString::iterator UnicodeString::insert(UnicodeString::iterator it, UnicodeString::AnsiChar c)
{
	data_.insert( it, UnicodeString::transformAnsiCharToUnicodeChar( c ) );

	return begin();
}

void UnicodeString::insert(UnicodeString::iterator it, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.insert( it, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	data_.replace( p0, n0, tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	data_.replace( p0, n0, tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{

	data_.replace( p0, n0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	data_.replace( first0, last0, tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, const UnicodeString::AnsiChar *s)
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	data_.replace( first0, last0, tmp.data_ );

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.replace( first0, last0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );

	return *this;
}

UnicodeString::size_type UnicodeString::copy(UnicodeString::AnsiChar *s, UnicodeString::size_type n, UnicodeString::size_type pos) const
{

	UnicodeString::AnsiChar* copyStr = UnicodeString::transformUnicodeToAnsi( *this );

	UnicodeString::size_type result = minVal<UnicodeString::size_type>( strlen(copyStr+pos), n );

	memcpy( s, copyStr+pos, result );


	delete [] copyStr;


	return result;
}

UnicodeString::size_type UnicodeString::find(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.rfind( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.rfind( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.rfind( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_first_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_first_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_first_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_last_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_last_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_last_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_first_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_first_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_first_not_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_last_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_last_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_last_not_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

int UnicodeString::compare(const UnicodeString::AnsiChar *s) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.compare( tmp.data_ ) ;
}

int UnicodeString::compare(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.compare( p0, n0, tmp.data_ ) ;
}

int UnicodeString::compare(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s, UnicodeString::size_type pos) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s+pos, strlen(s+pos), tmp.data_ );

	return data_.compare( p0, n0, tmp.data_ ) ;
}


/**
*CVS Log info
*$Log$
*Revision 1.1.2.5  2004/05/03 03:44:53  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.1.2.4  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.1.2.3  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.1  2004/04/21 02:17:27  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.2  2004/04/03 15:48:50  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.6  2004/03/29 15:22:00  ddiego
*some minor fixes
*
*Revision 1.1.2.5  2004/03/26 01:38:11  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.1.2.4  2004/03/21 16:03:10  ddiego
*minor change to VCFString to properly allocate a buffer
*unicode xfrm
*
*Revision 1.1.2.3  2004/03/02 03:46:26  ddiego
*some minor fixes for GCC. Still having a problem with GCC on linux, linking, and wide strings. I don't know which I hate more, GCC or MSVC6. Sigh... :(
*
*Revision 1.1.2.2  2004/02/16 05:34:05  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.1.2.1  2004/02/16 04:00:49  ddiego
*added some missing files for locales
*
*/



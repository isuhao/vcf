#ifndef _VCF_MIMETYPE_H__
#define _VCF_MIMETYPE_H__
//MIMEType.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class MIMEType MIMEType.h "vcf/FoundationKit/MIMEType.h"
Specification for this MIME Types may be found at
RFC 2045 http://www.faqs.org/rfcs/rfc2045.html.
This is a simple class that makes it easy to deal with 
strings that signify mime-type information.
*/
class FOUNDATIONKIT_API MIMEType {
public:
	typedef std::pair<String,String> Parameter;

	MIMEType();

	MIMEType( const String& data );

	MIMEType( const String& type, const String& subType );

	MIMEType( const String& type, const String& subType, const std::vector<Parameter>& parameters );



	operator String () const {
		return data_;
	}

	MIMEType& operator=( const String& rhs ) {
		data_ = rhs;
		return *this;
	}

	MIMEType& operator=( const FilePath& rhs ) {
		setFromFileName( rhs );
		return *this;
	}

	bool operator==( const MIMEType& rhs ) const {
		return compare( rhs );
	}

	bool operator!=( const MIMEType& rhs ) const {
		return !compare( rhs );
	}

	/**
	returns true if the mimetype is empty, or has no data. 
	If this returns true, then any of the data retreival 
	functions (getType(), getSubType()) will return empty
	strings ("") or no data.
	*/
	bool isEmpty() const {
		return data_.empty();
	}


	void setFromFileName( const String& fileName ) {
		setFromFileName( FilePath(fileName) );
	}


	String getType() const;

	String getSubType() const;

	std::vector<Parameter> getParameters() const;


	bool isTextType() const;

	bool isImageType() const;

	bool isAudioType() const;

	bool isVideoType() const;

	bool isApplicationType() const;


	static void registerExtension( const String& extension, const String& mimeType );

protected:
	static std::map<String,String> registeredFileExtensions;

	void setFromFileName( const FilePath& fileName );
	String data_;

	bool compare( const MIMEType& rhs ) const;

	static String canonicalValue( const String& value );
};




};


#endif // _VCF_MIMETYPE_H__

/**
$Id$
*/

/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.1  2004/04/21 02:17:24  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.3  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.2  2003/09/02 02:11:13  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.2.2.1  2003/08/27 20:11:33  ddiego
*adjustments to how hte DataObject class work and copy/paste
*
*Revision 1.2  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.3  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.1.2.2  2003/06/27 03:10:59  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.1.2.1  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.4  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:13:01  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.14.1  2003/01/08 00:19:58  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.2  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.1  2002/04/27 15:52:39  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.8.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/

/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/

/* Generated by Together */
#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;

/*
DataObject::DataObject( const char* dataToInitWith,  
										 const unsigned long& dataSize, 
										 const String& dataType )
{
	dataSize_ = dataSize;
	rawData_ = new char[ dataSize_ ];
	memcpy( rawData_, dataToInitWith, dataSize_ );
	
	init();	

	addSupportedDataType( dataType );
}
*/
DataObject::DataObject()
{	
	init();
}

DataObject::~DataObject()
{
	std::map<String,Persistable*>::iterator it = dataMap_.begin();
	while ( it != dataMap_.end() ) {
		delete it->second;
		it ++;
	}

	dataMap_.clear();
}

void DataObject::init()
{

}

void DataObject::addSupportedDataType( const String& dataType, Persistable* dataRepresentation )
{
	std::vector<String>::iterator found = std::find( types_.begin(), types_.end(), dataType );
	if ( found == types_.end() ) {
		types_.push_back( dataType );
	}

	if ( NULL != dataRepresentation ) {
		dataMap_[dataType] = dataRepresentation;
	}
}

bool DataObject::isTypeSupported( const String& dataType )
{
	bool result = false;
	
	std::vector<String>::iterator found = std::find( types_.begin(), types_.end(), dataType );
	if ( found != types_.end() ) {
		result = true;
	}

	return result;
}

bool DataObject::saveToStream( const String& dataType, OutputStream * stream )
{
	std::map<String,Persistable*>::iterator found = dataMap_.find( dataType );
	if ( found != dataMap_.end() ) {
		stream->write( found->second );
	}
	else {
		return false;
	}

	return true;
}

bool DataObject::loadFromStream( const String& dataType, InputStream * stream )
{
	std::map<String,Persistable*>::iterator found = dataMap_.find( dataType );
	if ( found != dataMap_.end() ) {
		stream->read( found->second );
	}
	else {
		return false;
	}

	return true;
}

Enumerator<String>* DataObject::getSupportedDataTypes()
{
	typesContainer_.initContainer( types_ );
	return typesContainer_.getEnumerator();	
}




TextDataObject::TextDataObject( const String& text ):
	DataObject()
{

	AnsiString tmp = text;
	BinaryPersistable* data = new BinaryPersistable( NULL, tmp.size()+1 );
	tmp.copy( (char*)data->getData(), tmp.size() );	
	data->getData()[tmp.size()] = 0;

	text_ = text;
	addSupportedDataType( STRING_DATA_TYPE, data );
}

TextDataObject::~TextDataObject()
{

}

String TextDataObject::getTextData()
{
	return text_;
}




ImageDataObject::ImageDataObject( Image* image ):
	DataObject()
{
	image_ = NULL;

	addSupportedDataType( IMAGE_DATA_TYPE, dynamic_cast<Persistable*>(image) );
}

ImageDataObject::~ImageDataObject()
{
	
}

Image* ImageDataObject::getImageData()
{
	if ( NULL == image_ ) {
		std::map<String,Persistable*>::iterator found = dataMap_.find( IMAGE_DATA_TYPE );
		if ( found != dataMap_.end() ) {
			image_ = dynamic_cast<Image*>( found->second );
		}
	}
	return image_;
}



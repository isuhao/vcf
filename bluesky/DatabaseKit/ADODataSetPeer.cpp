//ADODataSetPeer.cpp
#include "DatabaseKit.h"
#include "ADODataSetPeer.h"
#include "vcf/ApplicationKit/Win32HResult.h"



#define COM_PTR(ifc) \
namespace comet { \
template<> struct comtype<ifc> { \
	static const IID& uuid() { \
        static const IID iid = IID_##ifc; \
        return iid; \
	} \
    typedef nil base;\
};\
};\
typedef comet::com_ptr<ifc> ifc##Ptr;\
\




using namespace VCF;
using namespace comet;
using namespace comet::ADODB;





ADODataSetPeer::ADODataSetPeer():
	dataSet_(NULL)
{

	//Note that we are initializing COM with the 
	//COINIT_APARTMENTTHREADED flag here. This may
	//make multi-threaded support problematic. See
	//the MSDN docs for CoInitializeEx
	if( FAILED(::CoInitializeEx(0,COINIT_APARTMENTTHREADED)) ) {  
		throw DatabaseError("Unable to initialize COM for ADO data set");
	}

	
}

ADODataSetPeer::~ADODataSetPeer()
{
	dbConnection_ = NULL;

	::CoUninitialize();
}


AnsiString ADODataSetPeer::generateSQL()
{
	VCF_ASSERT( NULL != dataSet_ );

	AnsiString result;

	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified, unable to generate SQL statement!");
	}

	std::vector<DataField*>& fields = dataSet_->getFieldsArray();

	if ( fields.empty() ) {
		throw DatabaseError("No Fields in data set, unable to generate SQL statement!");
	}	

	result += "select ";
	for ( size_t i=0;i<fields.size();i++ ) {
		DataField* field = fields[i];
		if ( i > 0 ) {
			result += ", ";
		}
		result += field->getName();
	}

	result += " from ";

	result += tableName;


	result += ";";


	return result;
}

void ADODataSetPeer::open()
{
	VCF_ASSERT( NULL != dataSet_ );

	initFieldDefinitions();

	try {
		if ( dataSet_->getDefaultFields() ) {
			dataSet_->createFields();
		}

		_ConnectionPtr connection = getConnection();

		AnsiString sql = generateSQL();
		bstr_t bstrSql = sql.c_str();
		variant_t cnVar = connection;


		currentRecordSet_ = NULL; //pitch the old record set...

		currentRecordSet_ = Recordset::create();
		
		currentRecordSet_->Open( bstrSql.in(), cnVar, adOpenStatic, adLockReadOnly, adCmdText );

		currentRecordSet_->MoveFirst();
	}
	catch ( BasicException& ) {
		
	}
}


comet::ADODB::_ConnectionPtr ADODataSetPeer::getConnection()
{
	if ( dbConnection_.is_null() ) {
		dbConnection_ = Connection::create();
		
		String dbName = getDatabaseName();
		
		if ( dbName.empty() ) {
			throw DatabaseError("No Database Name specified!");
		}

		String provider = getProvider();
		
		if ( provider.empty() ) {
			throw DatabaseError("No Provider specified!");
		}

		

		bstr_t connectionStr;
		connectionStr += "Provider=";
		connectionStr += provider;
		connectionStr += ";";

		connectionStr += "Data Source=";
		connectionStr += dbName;
		connectionStr += ";";
		connectionStr += "Persist Security Info=False";

		dbConnection_->Open( connectionStr.in() );		
	}

	return dbConnection_;
}

void ADODataSetPeer::close()
{
	_ConnectionPtr connect = getConnection();

	currentRecordSet_ = NULL; //pitch the old record set...

	connect->Close();
}

void ADODataSetPeer::addFieldDef( FieldPtr& field, size_t fieldIndex )
{
	VCF_ASSERT( NULL != dataSet_ );

	FieldDefinitions& fieldDefs = dataSet_->getFieldDefinitions();

	String colName = AnsiString(field->GetName());
	String fieldName = colName;
	String name = fieldName;
	int i = 1;
	while ( fieldDefs.indexOf( name ) >= 0 ) {
		name = Format("%s%d") % fieldName % i;
		i++;
	}

	fieldName = name;	


	DataFieldType dataType = dftUnknown;
	DataTypeEnum type = field->GetType();
	switch ( type ) {
		case adInteger : {
			dataType = dftInteger;
		}
		break;

		case adChar : {
			dataType = dftString;
		}
		break;

		case adBSTR : {
			dataType = dftString;
		}
		break;

		case adWChar : case adVarWChar : {
			dataType = dftString;
		}
		break;
	}


	if ( dataType != dftUnknown ) {
		FieldDefinition fieldDef;
		fieldDef.name = fieldName;
		fieldDef.dataType = dataType;
		fieldDef.fieldNumber = fieldIndex;

		fieldDef.size = field->GetDefinedSize();


		switch ( fieldDef.dataType ) {
			case dftString : {
				fieldDef.size = 0;
			}
			break;
		}

		fieldDefs.add( fieldDef );
	}

}

void ADODataSetPeer::initFieldDefinitions()
{
	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified!");
	}
	
	_ConnectionPtr connect = getConnection();

	VCF_ASSERT( NULL != dataSet_ );

	FieldDefinitions& fieldDefs = dataSet_->getFieldDefinitions();

	fieldDefs.clear();


	_RecordsetPtr rs = Recordset::create();

	bstr_t tn = tableName.c_str();
	variant_t cnVar = connect;

	try {
		//rs->CacheSize = 100;

		rs->Open( tn.in(), cnVar, adOpenForwardOnly, adLockReadOnly, adCmdTable );		

		FieldsPtr fields = rs->GetFields();

		if ( !fields.is_null() ) {
			variant_t index;
			for (int i = 0; i < (int)fields->GetCount(); i++) {
				index = i;
				addFieldDef( fields->GetItem( index ), (size_t)i );
			}
		}

		rs->Close();
	}
	catch ( std::exception& e ) {
		throw DatabaseError(Format("Error initializing fields from ADO database!\nError: %s") % e.what() );
	}	
}

void ADODataSetPeer::first()
{
	currentRecordSet_->MoveFirst();
	
}
	
size_t ADODataSetPeer::calculateRecordSize() 
{
	size_t result = 0;

	try {
		FieldsPtr fields = currentRecordSet_->GetFields();

		if ( !fields.is_null() ) {
			variant_t index;
			for (int i = 0; i < (int)fields->GetCount(); i++) {
				index = i;
				FieldPtr field = fields->GetItem( index );

				result += field->GetActualSize();
			}
		}
	}
	catch ( std::exception& ) {
		
	}

	return result;
}

GetResultType ADODataSetPeer::getRecord( DataSet::Record* record, GetRecordMode mode )
{
	GetResultType result = grFailed;	

	VCF_ASSERT( NULL != dataSet_ );


	if ( currentRecordSet_->GetEOF() ) {
		
		//eof_ = true;
		result = grFailed;
	}
	else {
		size_t bufferOffset = 0;

		int res = 0;	

		size_t currentSz = calculateRecordSize();

		record->setSize( currentSz );

		FieldsPtr rsFields = currentRecordSet_->GetFields();

		variant_t fldIndex;

		std::vector<DataField*>& fields = dataSet_->getFieldsArray();

		for ( size_t i=0;i<fields.size();i++ ) {
			DataField* field = fields[i];

			fldIndex = (int)i;
			FieldPtr adoField = rsFields->GetItem( fldIndex );

			variant_t fieldVal = adoField->GetValue();


			size_t as = adoField->GetActualSize();

			switch ( field->getDataType() ) {
				case dftString : {
					bstr_t s = fieldVal;
					AnsiString as = s.s_str();
					const char* text = as.c_str();
					int txtSz = as.size();
					memcpy( &record->buffer[bufferOffset], text, txtSz );				

					field->setSize( adoField->GetActualSize() );

					bufferOffset += field->getSize();
				}
				break;

				case dftUnicodeString : {
					
				}
				break;

				case dftFloat : {
					double res = fieldVal;
					memcpy( &record->buffer[bufferOffset], &res, sizeof(res) );

					bufferOffset += field->getSize();
				}
				break;
				
				case dftWord : case dftSmallint : case dftInteger : {
					int res = fieldVal;

					memcpy( &record->buffer[bufferOffset], &res, sizeof(res) );

					bufferOffset += field->getSize();
				}
				break;
			}
		}

		VCF_ASSERT( bufferOffset == record->size );

		switch ( mode ) {
			case grmCurrent : {

			}
			break;

			case grmNext : {
				try {
					currentRecordSet_->MoveNext();
					result = grOK;
					bool eof = currentRecordSet_->GetEOF();
					if ( eof ) {
						result = grEOF;
					}
				}
				catch ( std::exception& e ) {
					result = grFailed;
				}
			}
			break;
		}
	}

	return result;
}


DataSet::Record* ADODataSetPeer::allocateRecordData()
{
	DataSet::Record* result = NULL;

	result = new DataSet::Record();

	return result;
}


String ADODataSetPeer::getTableName()
{
	VCF_ASSERT( NULL != dataSet_ );
	return dataSet_->getParam( "tablename" );
}

void ADODataSetPeer::setTableName( const String& val )
{
	VCF_ASSERT( NULL != dataSet_ );
	dataSet_->setParam( "tablename", val );
}

String ADODataSetPeer::getDatabaseName()
{
	VCF_ASSERT( NULL != dataSet_ );
	return dataSet_->getParam( "databasename" );
}

void ADODataSetPeer::setDatabaseName( const String& val )
{
	VCF_ASSERT( NULL != dataSet_ );
	dataSet_->setParam( "databasename", val );
}

String ADODataSetPeer::getProvider()
{
	VCF_ASSERT( NULL != dataSet_ );
	return dataSet_->getParam( "provider" );
}

void ADODataSetPeer::setProvider( const String& val )
{
	VCF_ASSERT( NULL != dataSet_ );
	dataSet_->setParam( "provider", val );
}


bool ADODataSetPeer::isCursorOpen()
{
	return !currentRecordSet_.is_null();
}

bool ADODataSetPeer::getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize )
{
	VCF_ASSERT( NULL != dataSet_ );

	size_t activeRecordIndex = dataSet_->getActiveRecordIndex();
	VCF_ASSERT( activeRecordIndex != DataSet::NoRecPos );


	bool result = false;

	size_t bufferOffset = 0;

	std::vector<DataField*>& fields = dataSet_->getFieldsArray();
	DataSet::RecordsArray& records = dataSet_->getRecords();


	for ( size_t i=0;i<fields.size();i++ ) {
		DataField* aField = fields[i];		

		if ( field->getFieldNumber() == i ) {
			DataSet::Record* record = records[ activeRecordIndex ];

			if ( (NULL != buffer) && (bufferSize > 0 ) ) {
				size_t len = minVal<>( bufferSize, (size_t)field->getSize() );
				memcpy( buffer, &record->buffer[bufferOffset], len );
				
				if ( dftString == field->getDataType() ) {
					buffer[len-1] = 0;
				}
			}

			//we need to determine if the data actually has any "content",
			//in other words is it NULL. For the moment we'll loop
			//through all the bytes and see if they are all zeroed out.
			//this is potentiall kind of stupid, so maybe there is a better
			//way???
			if ( dftString == field->getDataType() ) {
				for (int i=0;i<field->getSize();i++ ) {
					if ( record->buffer[bufferOffset+i] > 0 ) {
						result = true;
						break;
					}
				}
			}
			else {
				result= true;
			}
			
			break;
		}
		
		bufferOffset += aField->getSize();
	}

	return result;
}

void ADODataSetPeer::setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize )
{
	VCF_ASSERT( NULL != field );
	VCF_ASSERT( NULL != dataSet_ );

	size_t activeRecordIndex = dataSet_->getActiveRecordIndex();

	DataSetState state = dataSet_->getState();
	
	if ( !(state & dssEdit) ) {
		throw DatabaseError( "This data set is not in editing mode." );
	}

	
	if ( NULL != field ) {
		if ( (state & dssSetKey) && ((field->getFieldNumber() < 0) /*add index checks here|| ()*/) ) {
			throw DatabaseError( "This field is not editable." );
		}		

		std::vector<DataField*>& fields = dataSet_->getFieldsArray();
		DataSet::RecordsArray& records = dataSet_->getRecords();

		DataSet::Record* record = records[ activeRecordIndex ];

		size_t bufferOffset = 0;
		for ( size_t i=0;i<fields.size();i++ ) {
			DataField* aField = fields[i];

			if ( aField == field ) {

				field->validate( buffer, bufferSize );

				if ( !( (state == dssCalcFields) || (state == dssFilter) ) ) {
					Event e(field,deFieldChange);
					e.setUserData(this);
					dataSet_->handleDataEvent(&e);
				}
				break;
			}
		}
	}
}

void ADODataSetPeer::post()
{
	VCF_ASSERT( NULL != dataSet_ );

	DataSetState state = dataSet_->getState();
	if ( dssEdit == state ) {

		size_t activeRecordIndex = dataSet_->getActiveRecordIndex();
		std::vector<DataField*>& fields = dataSet_->getFieldsArray();
		
		DataSet::RecordsArray& records = dataSet_->getRecords();

		DataSet::Record* record = records[ activeRecordIndex ];

		size_t bufferOffset = 0;

		int res = 0;

		FieldsPtr rsFields = updateRecordSet_->GetFields();
		variant_t fldIndex;

		try {

			for ( size_t i=0;i<fields.size();i++ ) {
				DataField* field = fields[i];
				fldIndex = (int)i;
				FieldPtr adoField = rsFields->GetItem( fldIndex );


				switch ( field->getDataType() ) {
					case dftString : {
						const char* text = (const char*)&record->buffer[bufferOffset];

						bstr_t bstrTxt;
						
						variant_t fieldVal;

						fieldVal = adoField->GetValue();
						bstrTxt = fieldVal;

						bstrTxt = text;
						fieldVal = bstrTxt;

						adoField->PutValue( fieldVal );

					}
					break;

					case dftFloat : {
						double val = 0;
						memcpy( &val, &record->buffer[bufferOffset], field->getSize() );
						
					}
					break;

					case dftWord : case dftSmallint : case dftInteger : {
						int val = 0;
						memcpy( &val, &record->buffer[bufferOffset], field->getSize() );
						
					}
					break;
				}

		//		if ( res != SQLITE_OK ) {
		//			throw DatabaseError( Format("Error writing to field \"%s\". Error returned was %s.") );
		//		}
				bufferOffset += field->getSize();
			}

			VCF_ASSERT( bufferOffset == record->size );

		
			updateRecordSet_->Update();

			updateRecordSet_->Close();
			updateRecordSet_ = NULL;
		}
		catch ( const com_error& e ) {
			StringUtils::trace(Format("COM error: %s\n") % e.what() );
		}

	}
}

void ADODataSetPeer::refresh()
{

}

void ADODataSetPeer::edit()
{
	VCF_ASSERT( NULL != dataSet_ );

	comet::ADODB::_ConnectionPtr connection = getConnection();

	AnsiString sql = generateSQL();
		
	updateRecordSet_ = Recordset::create(); //pitch the old record set...

	variant_t cnVar = connection;
	bstr_t bstrSql = sql.c_str();

	try {
		long currentPos = currentRecordSet_->GetAbsolutePosition();

		updateRecordSet_->Open( bstrSql.in(), cnVar, adOpenStatic, adLockBatchOptimistic, adCmdText );
	
		updateRecordSet_->Move( currentPos );
	}
	catch ( std::exception& e ) {
		throw DatabaseError(Format("Error initializing update recordset from ADO database!\nError: %s") % e.what() );
	}
	

	updateWhereClause_ = "WHERE ";
	std::vector<DataField*>& fields = dataSet_->getFieldsArray();

	std::vector<DataField*>::iterator it = fields.begin();
	while ( it != fields.end() ) {
		DataField* field = *it;

		if ( !field->isBinaryType() ) {

			if ( it != fields.begin() ) {
				updateWhereClause_ += " AND ";
			}	
			
			
			updateWhereClause_ += field->getName() + " = ";
			
			if ( field->isStringType() ) {
				updateWhereClause_ += "'";
			}

			updateWhereClause_ += field->getAsString();

			if ( field->isStringType() ) {
				updateWhereClause_ += "'";
			}
		}

		++it;
	}
}

void ADODataSetPeer::initNewRecord( DataSet::Record* record )
{

}

void ADODataSetPeer::deleteRecord()
{

}

void ADODataSetPeer::cancel()
{

}

void ADODataSetPeer::setDataSet( DataSet* dataSet )
{
	bool needsProvider = NULL == dataSet_ ? true : false;
	dataSet_ = dataSet;

	if ( needsProvider ) {
		setProvider( "Microsoft.Jet.OLEDB.4.0" );
	}
}
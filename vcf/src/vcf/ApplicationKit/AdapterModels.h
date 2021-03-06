#ifndef _VCF_ADAPTERMODELS_H__
#define _VCF_ADAPTERMODELS_H__
//AdapterModels.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_DICTIONARY_H__
	#include "vcf/FoundationKit/Dictionary.h"
#endif  //_VCF_DICTIONARY_H__


#ifndef _VCF_STRINGTOKENIZER_H__
	#include "vcf/FoundationKit/StringTokenizer.h"
#endif  //_VCF_STRINGTOKENIZER_H__



#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__


namespace VCF {


class APPLICATIONKIT_API ObjectModel : public Model {
public:
	ObjectModel():source_(NULL),useFields_(false),dictionarySrc_(NULL){}

	virtual bool isEmpty() {
		
		return NULL != source_;
	}

	Object* getSource() {
		return source_;
	}

	void setSource( Object* val ) {
		source_ = val;

		dictionarySrc_ = dynamic_cast<Dictionary*>(val);		

		ModelEvent e(this,MODEL_CHANGED);
		changed(&e);
	}


	bool useFields() {
		return useFields_;
	}	

	void setUseFields( const bool& val ) {
		useFields_ = val;
	}


	virtual ValidationResult validate() {
		ValidationResult result;
		result.valid = true;

		if ( NULL != source_ ) {
			Class* clazz = source_->getClass();
			if ( NULL != clazz ) {
				if ( useFields_ ) {

				}
				else {
					Enumerator<Property*>* props = clazz->getProperties();
					
					while ( props->hasMoreElements() ) {
						Property* prop = props->nextElement();
						if ( !prop->isCollection() ) {
							
							VariantData* v = prop->get();
							ValidationResult vr = Model::validate( prop->getDisplayName(), *v );
							
							if ( !vr ) {
								result.addFailedRules( vr.getFailedRules() );
								
								if ( !result.error.empty() ) {
									result.error += "\n";
								}
								result.error += vr.error;
								result.key = vr.key;
								result.value = vr.value;
							}
							result.valid &= vr.valid;
							
							
						}
					}
				}
			}
			else if ( NULL != dictionarySrc_ ) {
				Dictionary::Enumerator* enumerator = dictionarySrc_->getEnumerator();
				while ( enumerator->hasMoreElements() ) {
					Dictionary::pair p = enumerator->nextElement();
					
					ValidationResult vr = Model::validate( p.first, p.second );
						
					if ( !vr ) {
						result.addFailedRules( vr.getFailedRules() );
						
						if ( !result.error.empty() ) {
							result.error += "\n";
						}
						result.error += vr.error;
						result.key = vr.key;
						result.value = vr.value;
					}
					result.valid &= vr.valid;
				}
			}
		}

		return result;
	}

	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() ) { 
		if ( NULL != source_ ) {
			Class* clazz = source_->getClass();
			if ( NULL != clazz ) {
				String propertyName = key;

				if ( useFields_ ) {
					Field* field = clazz->getField( propertyName );
					if ( NULL != field ) {						
						ValidationResult v = Model::validate( key, value );
						if ( v || (updateFlags_ & muAllowsInvalidData) ) {
							try {
								field->set( &v.value );
								changedKeyValue( key, v.value );
							}
							catch (BasicException& e) {
								StringUtils::trace( Format("Unable to set field {%s} to value {%s}\n\tException: %s\n") % key.toString() % value.toString() % e.getMessage() );
							}
						}
					}
				}
				else {
					Property* property = clazz->getProperty( propertyName );
					if ( NULL != property ) {					
						ValidationResult v = Model::validate( key, value );
						if ( v || (updateFlags_ & muAllowsInvalidData) ) {
							try {
								property->set( &v.value );
								changedKeyValue( key, v.value );
							}
							catch (BasicException& e) {
								StringUtils::trace( Format("Unable to set property {%s} to value {%s}\n\tException: %s\n") % key.toString() % value.toString() % e.getMessage() );
							}
						}
					}
				}
			}
			else if ( NULL != dictionarySrc_ ) {
				String propertyName = key;
				ValidationResult v = Model::validate( key, value );
				if ( v || (updateFlags_ & muAllowsInvalidData) ) {
					try {
						(*dictionarySrc_)[ key ] = v.value;
						changedKeyValue( key, v.value );
					}
					catch (BasicException& e) {
						StringUtils::trace( Format("Unable to set property {%s} to value {%s}\n\tException: %s\n") % key.toString() % value.toString() % e.getMessage() );
					}
				}
			}
		}
	}

	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		if ( NULL != source_ ) {
			Class* clazz = source_->getClass();
			if ( NULL != clazz ) {
				String propertyName = key;
				if ( useFields_ ) {
					Field* field = clazz->getField( propertyName );
					if ( NULL != field ) {
						VariantData* v = field->get();
						return *v;
					}
				}
				else {
					Property* property = clazz->getProperty( propertyName );
					if ( NULL != property ) {					
						VariantData* v = property->get();
						if ( NULL != v ) {
							return *v;
						}
					}	
				}
			}
			else if ( NULL != dictionarySrc_ ) {
				String propertyName = key;
				return dictionarySrc_->get(propertyName); 
			}
		}

		return VariantData::null();
	}


protected:
	Object* source_;
	Dictionary* dictionarySrc_;
	bool useFields_;
};












template <typename Type>
class  ArrayModel : public ListModel {
public:
	typedef Type DataType;

	ArrayModel(): enumData_(NULL){}

	ArrayModel( const std::vector<DataType>& rhs): enumData_(NULL){
		//data_ = rhs;
	}

	ArrayModel( DataType* arrayPtr, const uint32& arrayLength ): enumData_(NULL){
		data_.resize(arrayLength);
		for ( uint32 i=0;i<arrayLength;i++ ) {
			data_[i] = arrayPtr[i];
		}
	}

	virtual ~ArrayModel() {
		if ( NULL != enumData_ ) {
			delete enumData_;
		}
	}

	virtual void empty() {

		ListModelEvent itemEvent( this, lmeItemRemoved );

		_typename_ std::vector<DataType>::iterator it = data_.begin();
		
		while ( it != data_.end() ) {
			itemEvent.item = NULL;
			itemEvent.index = it - data_.begin();
			ItemRemoved( &itemEvent );
			++it;
		}
		data_.clear();
		if ( NULL != enumData_ ) {
			delete enumData_;
			enumData_ = NULL;
		}


		ListModelEvent event( this, lmeContentsDeleted );
		ModelChanged( &event );
	}

	virtual VariantData get( const uint32& index ) {
		return VariantData( data_[ index ] );
	}

	virtual uint32 getIndexOf( const VariantData& item ) {
		uint32 result = IndexNotFound;

		Type val = item;
		_typename_ Array<DataType>::iterator found = std::find( data_.begin(), data_.end(), val );
		if ( found != data_.end() ) {
			result = found - data_.begin();
		}
		return result;
	}

	virtual bool getItems( std::vector<VariantData>& items ) {
		items.resize( data_.size() );
		
		_typename_ Array<DataType>::iterator it1 = data_.begin();
		std::vector<VariantData>::iterator it2 = items.begin();
		while ( it1 != data_.end() ) {
			*it2 = *it1;
			++it2;
			++it1;
		}

		
		return !items.empty();
	}

	virtual Enumerator<VariantData>* getItems() {
		if ( NULL == enumData_ ) {
			enumData_ = new Array<VariantData>();
		}

		if ( enumData_->size() != data_.size() ) {
			enumData_->resize( data_.size() );
		}
		
		_typename_ Array<DataType>::iterator it1 = data_.begin();
		Array<VariantData>::iterator it2 = enumData_->begin();
		while ( it1 != data_.end() ) {
			*it2 = *it1;
			++it2;
			++it1;
		}

		return enumData_->getEnumerator();
	}

	virtual bool verifyRange( const uint32& start, const uint32& end ) {
		bool result = false;

		if ( end < data_.size() ) {
			result = true;
		}

		return result;
	}

	virtual bool getRange( const uint32& start, const uint32& end, std::vector<VariantData>& items ) {
		items.resize( (end - start) + 1 );
		for (uint32 i=start;i<=end;i++ ) {
			items[i-start] = data_[i];
		}
		return !items.empty();
	}
	virtual uint32 getCount() {
		return data_.size();
	}

	ArrayModel& operator=( const Array<DataType>& rhs ) {
		data_ = rhs;
		ModelEvent e(this,MODEL_CHANGED);
		changed(&e);
		return *this;
	}

	ArrayModel& operator=(  const std::vector<DataType>& rhs ) {
		
		data_.assign( rhs.begin(), rhs.end() );

		ModelEvent e(this,MODEL_CHANGED);
		changed(&e);
		return *this;
	}

	operator const std::vector<DataType>& () const {
		return data_;
	}


	DataType operator[] (const uint32& index ) const {
		return data_[index];
	}

protected:
	Array<DataType> data_;
	Array<VariantData>* enumData_;

	virtual bool doInsert( const uint32 & index, const VariantData& item ) {
		data_.insert( data_.begin() + index, (Type)item );
		return true;
	}

	virtual bool doRemove( const uint32 & index ) {
		_typename_ Array<DataType>::iterator found = data_.begin() + index;		
		if ( found != data_.end() ) {
			VariantData v = *found;
			data_.erase( found );	
			
			notifyRemove( index, v );
			
			if ( v.type == pdObject && shouldDeleteVarObjects() ) {
				Object* obj = v;
				if ( NULL != obj ) {
					deleteVariantObject( obj );
				}
			}
			
			
			return true;
		}
		
		return false;
	}

	virtual bool doSet( const uint32& index, const VariantData& item ) {
		size_t missing = 0;
		if ( (index+1) > data_.size() ) {
			missing = (index+1) - data_.size();
		}
		
		if ( missing > 0 ) {
			data_.resize( missing + data_.size() );
		}	
		
		data_[index] = (DataType)item;
		
		if ( missing > 0 ) {
			VariantData v;
			for (size_t i=index;i<data_.size();i++ ) {
				v = data_[i];
				notifyAdded( i, v );
			}
		}
		
		return true;
	}
};














class APPLICATIONKIT_API ObjectListModel : public SimpleListModel {
public:

	ObjectListModel() : SimpleListModel(), 
						objectsAsDictionaries_(false){};

	virtual ~ObjectListModel(){};


	virtual String getAsString( const uint32& index )	{
		VCF_ASSERT( index < data_.size() );
		
		Object* o = data_[ index ];
				
		if ( initProperties(o) ) {
			if ( objectsAsDictionaries_ ) {
				Dictionary* dict = (Dictionary*)o;
				Dictionary::pair p = dict->first();
				return p.second.toString();
			}
			else {
				Property* prop = properties_[(uint32)-1];
				if ( NULL != prop ) {
					VariantData v = *prop->get( o );
					return v.toString();
				}
			}
		}

		return SimpleListModel::getAsString(index);
	}

	virtual VariantData getSubItem( const uint32& index, const uint32& subItemIndex ) {		
		Object* o = data_[ index ];
				
		if ( initProperties(o) ) {		
			if ( objectsAsDictionaries_ ) {
				Dictionary* dict = (Dictionary*)o;
				Dictionary::Enumerator* enumerator = dict->getEnumerator();
				uint32 i = -1;
				while ( enumerator->hasMoreElements() ) {
					Dictionary::pair p = enumerator->nextElement();
					if ( subItemIndex == i ) {
						return p.second;
					}
					i++;
				}
			}
			else {
				Property* prop = properties_[subItemIndex];
				if ( NULL != prop ) {
					VariantData v = *prop->get( o );
					return v;
				}
			}
		}
		
		return VariantData::null();
	}

	virtual uint32 getSubItemsCount( const uint32& index ) {
		if ( objectsAsDictionaries_ ) {
			Object* o = data_[ index ];
			Dictionary* dict = (Dictionary*)o;

			return dict->size() - 1;
		}

		return properties_.size()-1;
	}

	virtual bool getSubItems( const uint32& index, std::vector<VariantData>& items ) {
		
		Object* o = data_[ index ];
		if ( initProperties(o) ) {
			if ( objectsAsDictionaries_ ) {
				Dictionary* dict = (Dictionary*)o;
				Dictionary::Enumerator* enumerator = dict->getEnumerator();
				uint32 i = -1;
				while ( enumerator->hasMoreElements() ) {
					Dictionary::pair p = enumerator->nextElement();
					if ( i >= 0 ) {
						items.push_back( p.second );
					}
					i++;
				}

			}
			else {
				std::map<uint32,Property*>::iterator it = properties_.begin();
				++it;
				while ( it != properties_.end() ) {				
					Property* prop = it->second;
					VariantData v = *prop->get( o );
					items.push_back( v );
					++it;
				}
			}
		}

		return !items.empty();
	}

	String getIgnorePropertyNames() {
		String result;

		for (size_t i=0;i<ignorePropNames_.size();i++ ) {
			if ( i > 0 ) {
				result += L";";
			}
			result += ignorePropNames_[i];
		}
		return result;
	}

	void setIgnorePropertyNames( const String& val ) {
		StringTokenizer tok(val,";");
		ignorePropNames_.clear();
		tok.getElements( ignorePropNames_ );
	}
protected:
	std::map<uint32,Property*> properties_;
	std::vector<String> ignorePropNames_;
	bool objectsAsDictionaries_;	

	bool initProperties(Object* o) {
		if ( NULL != o ) {
			objectsAsDictionaries_ = false;

			Class* clazz = o->getClass();
			if ( NULL != clazz ) {
				if ( properties_.empty() ) {
					Enumerator<Property*>* props = clazz->getProperties();
					uint32 index = (uint32)-1;
					while ( props->hasMoreElements() ) {
						Property* prop = props->nextElement();
						if ( !prop->isCollection() ) {
							
							if (  ignorePropNames_.end() == std::find( ignorePropNames_.begin(), ignorePropNames_.end(), prop->getName() ) ){
								properties_[index] = prop;						
								index ++;
							}
						}
					}
				}				
			}
			else if ( dynamic_cast<Dictionary*>(o) ) {
				//Dictionary is a special case here
				properties_.clear();
				objectsAsDictionaries_ = true;				
			}
		}

		return !properties_.empty() || objectsAsDictionaries_;
	}

	virtual bool doInsertSubItem( const uint32& index, const uint32 & subItemIndex, const VariantData& value ) {
		return false;
	}

	virtual bool doRemoveSubItem( const uint32& index, const uint32 & subItemIndex ) { return false; }

	virtual bool doSetSubItem( const uint32& index, const uint32& subItemIndex, const VariantData& value ) {
		Object* o = data_[ index ];
				
		if ( initProperties(o) ) {				
			Property* prop = properties_[subItemIndex];
			if ( NULL != prop ) {
				VariantData v(value);
				prop->set( o, &v );
				return true;
			}
		}

		return false;
	}
};



class APPLICATIONKIT_API DictionaryListModel : public ListModel {
public:
	DictionaryListModel() : ListModel(),dictionary_(NULL) {}

	Dictionary* getDictionary() {
		return dictionary_;
	}

	void setDictionary( Dictionary* val ) {
		dictionary_ = val;

		if ( NULL != dictionary_ ) {
			getItems( dictArray_ );	
			
			ModelEvent e(this,MODEL_CHANGED);
			changed(&e);
		}
	}


	virtual bool isEmpty() {
		
		if ( NULL != dictionary_ ) {
			return dictionary_->empty();
		}

		return false;
	}

	virtual void empty() {
		if ( NULL != dictionary_ ) {
			dictionary_->clear();
		}

		dictArray_.clear();
	}

	virtual VariantData get( const uint32& index ) {
		if ( NULL != dictionary_ ) {
			uint32 i = 0;
			Dictionary::Enumerator* items = dictionary_->getEnumerator();
			while ( items->hasMoreElements() ) {
				Dictionary::pair item = items->nextElement();

				if ( index == i ) {
					return item.first;
				}
				++i;
			}
		}

		return VariantData::null();
	}

	virtual uint32 getIndexOf( const VariantData& item ) {
		uint32 result = 0;
		Dictionary::Enumerator* items = dictionary_->getEnumerator();
		while ( items->hasMoreElements() ) {
			Dictionary::pair data = items->nextElement();
			
			if ( data.second == item ) {
				return result;
			}

			result++;
		}
		
		return ListModel::InvalidIndex;
	}

	virtual bool getItems( std::vector<VariantData>& arrayOfItems ) {

		Dictionary::Enumerator* items = dictionary_->getEnumerator();
		while ( items->hasMoreElements() ) {
			Dictionary::pair data = items->nextElement();
			arrayOfItems.push_back( data.second );
		}

		return !arrayOfItems.empty();
	}

	virtual Enumerator<VariantData>* getItems() {
		return dictArray_.getEnumerator();
	}

	virtual bool getRange( const uint32& start, const uint32& end, std::vector<VariantData>& items ) {
		return false;
	}

	virtual bool verifyRange( const uint32& start, const uint32& end ) {
		return false;
	}

	virtual uint32 getCount() {
		if ( NULL != dictionary_ ) {
			return dictionary_->size();
		}
		return 0;
	}

	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		if ( NULL != dictionary_ ) {
			return (*dictionary_)[ key.toString() ];
		}

		return VariantData::null();
	}

	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() )  {
		if ( NULL != dictionary_ ) {
			(*dictionary_)[ key.toString() ] = value;
			changedKeyValue( key, value );
		}		
	}

protected:	
	virtual bool doInsert( const uint32 & index, const VariantData& item ) {
		return true;
	}

	virtual bool doRemove( const uint32 & index ) {
		if ( NULL != dictionary_ ) {
			uint32 i = 0;
			Dictionary::Enumerator* items = dictionary_->getEnumerator();
			while ( items->hasMoreElements() ) {
				Dictionary::pair item = items->nextElement();

				if ( index == i ) {
					dictionary_->remove( item.first );
					return true;
				}
				++i;
			}
		}

		return false;
	}

	virtual bool doSet( const uint32& index, const VariantData& val ) {
		if ( NULL != dictionary_ ) {
			uint32 i = 0;
			Dictionary::Enumerator* items = dictionary_->getEnumerator();
			while ( items->hasMoreElements() ) {
				Dictionary::pair item = items->nextElement();

				if ( index == i ) {
					item.second = val;
					return true;
				}
				++i;
			}
		}

		return false;
	}


	Dictionary* dictionary_;
	Array<VariantData> dictArray_;
};


class APPLICATIONKIT_API DictionaryModel : public Model {
public:
	DictionaryModel():Model(){}

	DictionaryModel( const Dictionary& dict):Model(){ 
		data_ = dict;
	}

	virtual ~DictionaryModel() {
		if ( shouldDeleteVarObjects() ) {
			data_.setOwnsObjectValues(true);
		}
	}


	VariantData& operator[](const String& key) { 
		return  data_[key];
	}

	VariantData operator[](const String& key) const {  
		return  data_[key];
	}


	virtual bool isEmpty() {
		return data_.empty();
	}

	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		String strKey = key;
		return data_[ strKey ];
	}

	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() )  {
		String strKey = key;
		data_[ strKey ] = value;
		changedKeyValue( key, value );
	}


	Dictionary* getDictionary(){
		return &data_;
	}
protected:
	Dictionary data_;
};









class APPLICATIONKIT_API ObjectColumnModel : public ColumnModel {
public:
	ObjectColumnModel():source_(NULL), listModel_(NULL){
		addCallback( new ClassProcedure1<Event*,ObjectColumnModel>(this, &ObjectColumnModel::onListModelChanged), "ObjectColumnModel::onListModelChanged" );		
	}

	Class* getSource() {
		return source_;
	}

	void setSource( Class* val ) {
		if ( source_ != val ) {
			source_ = val;
			
			empty();

			if ( NULL != source_ ) {
				Enumerator<Property*>* props = source_->getProperties();
				while ( props->hasMoreElements() ) {
					Property* prop = props->nextElement();
					if ( !prop->isCollection() ) {
						if (  ignorePropNames_.end() == std::find( ignorePropNames_.begin(), ignorePropNames_.end(), prop->getName() ) ){
							add( prop->getDisplayName() );
						}

						
					}
				}
			}
		}
	}

	ListModel* getListModel() {
		return listModel_;
	}

	void setListModel( ListModel* val ) {
		if ( listModel_ != val ) {
			listModel_ = val;

			if ( NULL != listModel_ ) {
				listModel_->ModelChanged += getCallback( "ObjectColumnModel::onListModelChanged" );

				if ( !listModel_->isEmpty() ) {
					VariantData v = listModel_->get(0);
					if ( v.type == pdObject ) {
						Object* o = v;
						setSource( o->getClass() );
					}
				}
			}
			else {
				empty();
			}
		}
	}

	String getIgnorePropertyNames() {
		String result;

		for (size_t i=0;i<ignorePropNames_.size();i++ ) {
			if ( i > 0 ) {
				result += L";";
			}
			result += ignorePropNames_[i];
		}
		return result;
	}

	void setIgnorePropertyNames( const String& val ) {
		StringTokenizer tok(val, L";");
		ignorePropNames_.clear();
		tok.getElements( ignorePropNames_ );
	}
protected:
	Class* source_;
	ListModel* listModel_;
	std::vector<String> ignorePropNames_;

	void onListModelChanged( Event* e ) {		
		if ( !listModel_->isEmpty() ) {
			VariantData v = listModel_->get(0);
			if ( v.type == pdObject ) {
				Object* o = v;
				setSource( o->getClass() );
			}
		}
	}
};






class APPLICATIONKIT_API DictionaryColumnModel : public ColumnModel {
public:
	DictionaryColumnModel():source_(NULL), listModel_(NULL){
		addCallback( new ClassProcedure1<Event*,DictionaryColumnModel>(this, &DictionaryColumnModel::onListModelChanged), "DictionaryColumnModel::onListModelChanged" );
	}

	Dictionary* getSource() {
		return source_;
	}

	void setSource( Dictionary* val ) {
		if ( source_ != val ) {
			source_ = val;
			
			empty();

			if ( NULL != source_ ) {
				Dictionary::Enumerator* props = source_->getEnumerator();
				while ( props->hasMoreElements() ) {
					DictionaryEnumerator::PairType prop = props->nextElement();
					add( prop.first );						
				}
			}
		}
	}

	ListModel* getListModel() {
		return listModel_;
	}

	void setListModel( ListModel* val ) {
		if ( listModel_ != val ) {
			listModel_ = val;

			if ( NULL != listModel_ ) {
				listModel_->ModelChanged += getCallback( "DictionaryColumnModel::onListModelChanged" );

				if ( !listModel_->isEmpty() ) {
					VariantData v = listModel_->get(0);
					if ( v.type == pdObject ) {
						Object* o = v;
						setSource( (Dictionary*)o );
					}
				}
			}
			else {
				empty();
			}
		}
	}	
protected:
	Dictionary* source_;
	ListModel* listModel_;

	void onListModelChanged( Event* e ) {		
		if ( !listModel_->isEmpty() ) {
			VariantData v = listModel_->get(0);
			if ( v.type == pdObject ) {
				Object* o = v;
				setSource( (Dictionary*)o );
			}
		}
	}
};



class APPLICATIONKIT_API ValueModel : public Model {
public:
	ValueModel():value_(VariantData::null()){}
	virtual ~ValueModel(){}


	virtual bool isEmpty() {
		
		return value_.isNull();
	}

	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() ) { 
		value_ = value;
		changedKeyValue( key, value );
	}

	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		return value_;
	}
protected:
	VariantData value_;
};



template <typename Type>
class APPLICATIONKIT_API TypeModel : public Model {
public:
	typedef Type ValueType;

	TypeModel():value_(ValueType()){}
	virtual ~TypeModel(){}

	virtual bool isEmpty() {		
		return false;
	}

	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() ) { 
		internal_set(value);
	}

	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		return value_;
	}

	inline TypeModel& operator=( const ValueType& rhs ) {
		internal_set(rhs);
		return *this;
	}

	inline operator ValueType() const {
		return value_;
	}

	inline bool operator== ( const ValueType& rhs ) const {
		return value_ == rhs;
	}

protected:

	inline void internal_set( const ValueType& rhs, const VariantData& key=VariantData::null() ) {
		value_ = rhs;
		changedKeyValue( key, value_ );
	}

	ValueType value_;
};

class APPLICATIONKIT_API BoolModel : public TypeModel<bool> {
public:
	BoolModel(){}
	virtual ~BoolModel(){}

	inline BoolModel& operator=( const bool& rhs ) {
		internal_set(rhs);
		return *this;
	}
};


class APPLICATIONKIT_API IntModel : public TypeModel<int64> {
public:
	IntModel(){}
	virtual ~IntModel(){}
	inline IntModel& operator=( const int64& rhs ) {
		internal_set(rhs);
		return *this;
	}
};


class APPLICATIONKIT_API DoubleModel : public TypeModel<double> {
public:
	DoubleModel(){}
	virtual ~DoubleModel(){}
	inline DoubleModel& operator=( const double& rhs ) {
		internal_set(rhs);
		return *this;
	}
};


class APPLICATIONKIT_API StringModel : public TypeModel<String> {
public:
	StringModel(){}
	virtual ~StringModel(){}
	inline StringModel& operator=( const String& rhs ) {
		internal_set(rhs);
		return *this;
	}
};


class APPLICATIONKIT_API StringListModel : public ArrayModel<String> {
public:
	StringListModel(){}
	virtual ~StringListModel(){}

	StringListModel& operator=( const std::vector<String>& rhs ) {		
		ArrayModel<String>::operator =(rhs);
		return *this;
	}
};

	
};


#endif //_VCF_ADAPTERMODELS_H__
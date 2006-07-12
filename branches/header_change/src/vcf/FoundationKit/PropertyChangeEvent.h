#ifndef _VCF_PROPERTYCHANGEEVENT_H__
#define _VCF_PROPERTYCHANGEEVENT_H__
//PropertyChangeEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class VariantData;

/**
\class PropertyChangeEvent PropertyChangeEvent.h "vcf/FoundationKit/PropertyChangeEvent.h"
*Property change event's are used whenever a propertys value changes
*/
class FOUNDATIONKIT_API PropertyChangeEvent : public Event
{
public:
	PropertyChangeEvent( Object * source, VariantData* changeValue, VariantData* originalValue );

	PropertyChangeEvent( const PropertyChangeEvent& rhs ) :Event(rhs) {
		*this = rhs;
	}

	virtual ~PropertyChangeEvent();

	PropertyChangeEvent& operator=( const PropertyChangeEvent& rhs ) {
		Event::operator =( rhs );

		changeValue_ = rhs.changeValue_;
		originalValue_ = rhs.originalValue_;

		return *this;
	}
	/**
	*returns the VariantData that represents the new value
	*/
	VariantData* getChangeValue();

	/**
	*returns a VariantData that represents the original value
	*before the change
	*/
	VariantData* getOriginalValue();

	virtual Object* clone( bool deep=false ) {
		return new PropertyChangeEvent(*this);
	}

private:
	VariantData* changeValue_;
	VariantData* originalValue_;
};




/**
\class PropertyChangeEventHandler PropertyChangeEvent.h "vcf/FoundationKit/PropertyChangeEvent.h"
*Classes implmenting this interface <b><i>MUST</i></b> throw PropertyChangeException
*if they do not want the change to be processed.
*/
template <class SOURCE_TYPE>
class PropertyChangeEventHandler : public EventHandlerInstance<SOURCE_TYPE,PropertyChangeEvent> {
public:
	PropertyChangeEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,PropertyChangeEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,PropertyChangeEvent>( source, handlerMethod, handlerName ) {

	}
};


};


#endif // _VCF_PROPERTYCHANGEEVENT_H__

/**
$Id$
*/

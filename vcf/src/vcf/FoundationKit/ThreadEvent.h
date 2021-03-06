#ifndef _VCF_THREADEVENT_H__
#define _VCF_THREADEVENT_H__
//ThreadEvent.h

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
\class ThreadEvent ThreadEvent.h "vcf/FoundationKit/ThreadEvent.h"
*/
class FOUNDATIONKIT_API ThreadEvent : public Event{
public:
	ThreadEvent( Object* source ):Event( source ){};

	ThreadEvent( Object* source, const uint32& eventType ): Event( source, eventType ){};

	virtual ~ThreadEvent(){};

	virtual Object* clone( bool deep=false ) const {
		return new ThreadEvent(*this);
	}

};


typedef Delegate1<ThreadEvent*> ThreadDelegate;
typedef ThreadDelegate::ProcedureType ThreadHandler;

}; //end of namespace VCF


#endif // _VCF_THREADEVENT_H__

/**
$Id$
*/

#ifndef _VCF_WINDOWEVENT_H__
#define _VCF_WINDOWEVENT_H__
//WindowEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


namespace VCF{

#define WINDOW_CONST					600

#define WINDOW_EVENT_RESTORE			CUSTOM_EVENT_TYPES + WINDOW_CONST + 1
#define WINDOW_EVENT_MAXIMIZE			CUSTOM_EVENT_TYPES + WINDOW_CONST + 2
#define WINDOW_EVENT_MINIMIZE			CUSTOM_EVENT_TYPES + WINDOW_CONST + 3

/**
\class WindowEvent WindowEvent.h "vcf/ApplicationKit/WindowEvent.h"  
*/
class APPLICATIONKIT_API WindowEvent : public VCF::Event {
public:
	WindowEvent( Object* source ): Event(source) {}

	WindowEvent( Object* source, const uint32& eventType ):
		Event(source,eventType) {}

	virtual ~WindowEvent(){};

	virtual Object* clone( bool deep=false ) {
		return new WindowEvent(*this);
	}
private:

};




/**
WindowDelegate
handles the following:
\li onWindowRestore
\li onWindowMaximize
\li onWindowMinimize
*/
typedef Delegate1<WindowEvent*> WindowDelegate; 
typedef WindowDelegate::ProcedureType WindowHandler;


};


#endif // _VCF_WINDOWEVENT_H__

/**
$Id$
*/

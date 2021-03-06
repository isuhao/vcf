#ifndef _VCF_RUNNABLE_H__
#define _VCF_RUNNABLE_H__
//Runnable.h

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

/**
\class Runnable Runnable.h "vcf/FoundationKit/Runnable.h"
A class that represents a
single executable task.
The Runnable class indicates that it
may be "run' (hence the run() method)
and stopped (hence the "stop" ) method.
*/
class FOUNDATIONKIT_API Runnable {
public:
	virtual ~Runnable(){};

	/**
	Executes the runnable code.
	@return returns true is the execution was suvvessful,
	or false if not.
	*/
    virtual bool run() = 0;

	/**
	stops the task from running. Should allow the
	implementer to gracefully finish whatever they
	were doing and exit the run() method as soon as
	possible.
	*/
	virtual void stop() = 0;
};

}


#endif // _VCF_RUNNABLE_H__

/**
$Id$
*/

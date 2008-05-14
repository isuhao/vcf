#ifndef _VCF_PRINTABLE_H__
#define _VCF_PRINTABLE_H__
//Printable.h

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
\class Printable Printable.h "vcf/GraphicsKit/Printable.h"
*/

class GRAPHICSKIT_API Printable {
public:
	virtual ~Printable(){};
	
    virtual PrintContext* getPrintContext() = 0;
};

};


#endif // _VCF_PRINTABLE_H__

/**
$Id$
*/

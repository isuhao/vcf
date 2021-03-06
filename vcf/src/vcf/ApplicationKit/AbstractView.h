#ifndef _VCF_ABSTRACTVIEW_H__
#define _VCF_ABSTRACTVIEW_H__
//AbstractView.h

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
\class AbstractView AbstractView.h "vcf/ApplicationKit/AbstractView.h"
Basic implementation of a view. Serves as a starting point for
your own specific implementation. Implements the basic view methods 
like get/setViewModel(), get/setViewControl, etc.
Implementers of a view should probably derive from this class
as opposed to arbitrarily reimplementing the functions. This means 
that only function you'll really need to implement is the paintView()
method.
*/
class APPLICATIONKIT_API AbstractView : public View {
public:
	AbstractView( Control* viewControl=NULL){
		viewControl_ = viewControl;
		viewModel_ = NULL;
	}

	virtual ~AbstractView();

	virtual Model* getViewModel(){
		return viewModel_;
	}

	virtual void setViewModel( Model* viewModel );


	virtual Control* getViewControl(){
		return viewControl_;
	}

	virtual void setViewControl( Control* viewControl ){
		viewControl_ = viewControl;
	}

	virtual void paintView( GraphicsContext* context );

	virtual void updateView( Model* updatedModel );
protected:
	Model* viewModel_;
	Control* viewControl_;

};


};


#endif // _VCF_ABSTRACTVIEW_H__

/**
$Id$
*/

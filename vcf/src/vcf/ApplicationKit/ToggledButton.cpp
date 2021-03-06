//ToggledButton.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ToggledButton.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ToggledButton.h"
#include "vcf/ApplicationKit/Action.h"

using namespace VCF;


ToggledButton::ToggledButton():
	CustomControl( true )
{
	captionAlignment_ = taTextLeft;
	checked_ = false;
}

ToggledButton::~ToggledButton()
{

}

bool ToggledButton::isChecked()
{
	Model* model  = getViewModel();
	if ( NULL != model ) {
		VariantData v = model->getValue( getModelKey() );
		if ( v.type == pdBool ) {
			return v;
		}
	}
	return checked_;
}

void ToggledButton::updateView( Model* updatedModel )
{
	VariantData v = updatedModel->getValue( getModelKey() );
	if ( v.type == pdBool ) {
		if ( checked_ != (bool)v ) {
			checked_ = v;
			repaint();
		}
	}
}

void ToggledButton::setChecked( const bool& checked )
{
	if ( checked_ != checked ) {
		checked_ = checked;
		Model* model  = getViewModel();
		if ( NULL != model ) {
			VariantData v = checked_;
			
			model->setValue( v, getModelKey() );
		}	
		
		repaint();
	}
}

void ToggledButton::setName( const String& name )
{
	CustomControl::setName( name );
	if ( caption_.empty() ) {
		setCaption( name );
	}
}

void ToggledButton::setCaption( const String& caption )
{
	caption_ = caption;
	repaint();
}

void ToggledButton::setCaptionAlignment( const TextAlignmentType& alignment )
{
	captionAlignment_ = alignment;
	repaint();
}

void ToggledButton::mouseDown( MouseEvent* event )
{
	CustomControl::mouseDown( event );
	if ( event->hasLeftButton() ) {
		keepMouseEvents();
		setChecked( !checked_ );
	}
}

void ToggledButton::mouseMove( MouseEvent* event )
{
	CustomControl::mouseMove( event );
}

void ToggledButton::mouseUp( MouseEvent* event )
{
	CustomControl::mouseUp( event );
	releaseMouseEvents();

	if ( event->hasLeftButton() ) {
		Rect r( 0, 0,getWidth(), getHeight() );
		if ( false == r.containsPt( event->getPoint() ) ) {
			setChecked( !checked_ );
		}
		else {
			click();
		}
	}
}

void ToggledButton::click()
{
	ButtonEvent event( this, 0 );

	Action* action = getAction();
	if ( NULL != action ) {
		action->perform( &event );
	}
	else {
		ButtonClicked( &event );
	}
}


/**
$Id$
*/

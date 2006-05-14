//CheckBoxControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/CheckBoxControl.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;

CheckBoxControl::CheckBoxControl()
{
	setVisible( true );	
}

CheckBoxControl::~CheckBoxControl()
{

}

double CheckBoxControl::getPreferredHeight()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtCheckBoxHeight );
}

double CheckBoxControl::getPreferredWidth()
{
	return 100;
}

void CheckBoxControl::paint( GraphicsContext* context )
{
	ToggledButton::paint( context );

	Rect r = getClientBounds();
	
	ButtonState buttonState;
	buttonState.setActive( isActive() );
	buttonState.setEnabled( isEnabled() );
	//buttonState.setPressed( checked_ );
	buttonState.setToggled( checked_ );
	buttonState.setFocused( isFocused() && buttonState.isActive() );

	if ( getUseLocaleStrings() ) {
		buttonState.buttonCaption_ = System::getCurrentThreadLocale()->translate( caption_ );
	}
	else {
		buttonState.buttonCaption_ = caption_;
	}

	
	context->drawThemeCheckboxRect( &r, buttonState );
}


/**
$Id$
*/
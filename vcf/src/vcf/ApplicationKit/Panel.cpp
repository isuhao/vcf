//Panel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Panel.h"


using namespace VCF;

Panel::Panel()
{
	init();
}

Panel::~Panel()
{

}

void Panel::init()
{
	setBorder( new Basic3DBorder() );
	setBorderSize( 0 );
}

void Panel::paint( GraphicsContext * context )
{
	ControlContainer::paint( context );
}

void Panel::setCaption( const String& caption )
{
	caption_ = caption;
}

String Panel::getCaption()
{
	return caption_;
}


/**
$Id$
*/

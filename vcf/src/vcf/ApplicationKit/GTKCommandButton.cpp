/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.2  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.3  2003/07/14 22:52:53  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*Revision 1.1.2.2  2003/07/13 03:45:11  ddiego
*Added further fixes for the GTK port. Now have the event handling working
*correctly, and fixed an issue with too many repaint messages being sent
*which caused 100% CPU utilization.
*
*Revision 1.1.2.1  2003/07/10 04:55:16  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*/

/**
Copyright (c) 2000-2001, Jim Crafton
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
	Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

NB: This software will not save the world.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/AbstractGTKControl.h"
#include "vcf/ApplicationKit/GTKCommandButton.h"
#include "vcf/ApplicationKit/CommandButton.h"


using namespace VCF;




GTKCommandButton::GTKCommandButton( CommandButton* component )
{
	control_ = (Control*)component;
	commandButton_ = component;
	gtkButton_ = NULL;
}

GTKCommandButton::~GTKCommandButton()
{

}



void GTKCommandButton::create( Control* owningControl )
{
	GTKGraphicsToolkit* grafToolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();	
	GTKUIToolkit* toolkit = (GTKUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();

	wndHandle_ = gtk_button_new_with_label ("");

	

	if ( NULL == wndHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("gtk_button_new_with_label() failed") );
	}

	gtkButton_ = GTK_BUTTON( wndHandle_ );

	gtk_container_add( GTK_CONTAINER( toolkit->getDefaultParent() ), wndHandle_ );	

	gtk_widget_show ( wndHandle_ );

	g_signal_connect (G_OBJECT (gtkButton_), "clicked",
		      G_CALLBACK (GTKCommandButton::gtkButtonClicked), (gpointer) this);

	AbstractGTKControl::registerGTKControl( this );	
}


Image* GTKCommandButton::getImage()
{
	return NULL;
}


void GTKCommandButton::setImage( Image* image )
{

}


ulong32 GTKCommandButton::getState()
{
	return 0;
}


void GTKCommandButton::setState( const ulong32& state )
{

}

void GTKCommandButton::gtkButtonClicked( GtkButton* button,  gpointer data )
{
	GTKCommandButton* thisPtr = (GTKCommandButton*)data;
	thisPtr->commandButton_->click();
}

String GTKCommandButton::getText()
{
	String result;

	result = gtk_button_get_label(gtkButton_);
	return result;
}

void GTKCommandButton::setText( const String& text )
{
	gtk_button_set_label( gtkButton_, text.c_str() );
}

gboolean GTKCommandButton::handleEvent( GdkEvent* gtkEvent )
{	
	GTKUIToolkit* toolkit = reinterpret_cast<GTKUIToolkit*>(UIToolkit::internal_getDefaultUIToolkit());
	
	gboolean result = FALSE;

	switch ( gtkEvent->type ) {
		
		case GDK_EXPOSE : {
			AbstractGTKControl::handleEvent( gtkEvent );
			
			return FALSE;
		}
		break;
		
		case GDK_BUTTON_PRESS : case GDK_2BUTTON_PRESS : case GDK_3BUTTON_PRESS : {
			result = AbstractGTKControl::handleEvent( gtkEvent );
		}
		break;

		default : {			
			result = AbstractGTKControl::handleEvent( gtkEvent );
		}
		break;
	}

	return result;	
}

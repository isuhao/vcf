//Frame.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Containers.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;

Frame* Frame::currentActiveFrame = NULL;



Frame::State::State()
{
	
}


void Frame::State::applyState( Frame* frame )
{
	frame->setBounds( &bounds_ );
	frame->setVisible( visible_ );
	Window* window = dynamic_cast<Window*>( frame );
	if ( NULL != window ) {
		switch ( displayState_ ) {
			case Frame::State::fdsMaximized : {
				window->setMaximized( true );
			}
			break;

			case Frame::State::fdsMinimized : {
				window->setMinimized( true );
			}
			break;
		}
	}
}

void Frame::State::initState( Frame* frame )
{
	bounds_ = frame->getBounds();
	visible_ = frame->getVisible();
	displayState_ = Frame::State::fdsNormal;

	Window* window = dynamic_cast<Window*>( frame );
	if ( NULL != window ) {
		if ( window->isMaximized() ) {
			displayState_ = Frame::State::fdsMaximized;
		}
		else if ( window->isMinimized() ) {
			displayState_ = Frame::State::fdsMinimized;
		}
	}
}

void Frame::State::loadFromStream( InputStream* stream )
{
	stream->read( static_cast<Persistable*>(&bounds_) );
	stream->read( visible_ );
	long state;
	stream->read( state );
	displayState_ = (Frame::State::FrameDisplayState)state;
}

void Frame::State::saveToStream( OutputStream* stream )
{
	stream->write( &bounds_ );
	stream->write( visible_ );
	stream->write( displayState_ );
}




Frame::Frame():
	frameStyle_(fstSizeable),
	isTopmostFrame_(false),
	useColorForBackground_(false),
	allowFrameAsChildControl_(false)
{
	setContainerDelegate( this );
	setContainer( new StandardContainer() );	
}

Frame::~Frame()
{

}

void Frame::destroy()
{
	if ( Frame::currentActiveFrame == this ) {
		Frame::currentActiveFrame = NULL;
	}

	Control::destroy();
}

void Frame::paint( GraphicsContext * context )
{
	if ( NULL != getView() ) {
		getView()->paintView( context );
	}
	else {	

		Rect innerBounds = getClientBounds(false);
/*
		if ( NULL != border ){
			border->paint( this, context );
			Rect tmpBounds = border->getClientRect( &innerBounds, this );
			innerBounds = tmpBounds;
			innerBounds.inflate( -1, -1 );
		}
		*/

		
		
		if ( useColorForBackground_ ) {
			context->setColor( getColor() );
		
			context->rectangle( innerBounds.left_, innerBounds.top_, innerBounds.right_, innerBounds.bottom_ );
		
			context->fillPath();		
		}
		else {	
			BackgroundState bkg;
			bkg.setEnabled( isEnabled() );
			bkg.setActive( (this == Frame::getActiveFrame()) && isActiveFrame() );
			bkg.colorType_ = SYSCOLOR_WINDOW;	
			
			context->drawThemeBackground( &innerBounds, bkg );
		}
		


		context->setCurrentFont( getFont() );

		Scrollable* scrollable = getScrollable();
		if ( scrollable ) {
			Rect viewBounds = context->getViewableBounds();

			Point origin = context->getOrigin();

			adjustViewableBoundsAndOriginForScrollable( context, viewBounds, origin );

			context->setOrigin( origin );

			context->setViewableBounds( viewBounds );
		}
	}

	paintChildren( context );
}

void Frame::show()
{	
	setVisible( true );
	repaint();

	activate();
}

void Frame::hide()
{
	setVisible( false );
}

void Frame::setCaption( const String& caption )
{
	caption_ = caption;
}

String Frame::getCaption()
{
	return caption_;
}

bool Frame::isFrameTopmost()
{
	return isTopmostFrame_;
}

void Frame::setFrameTopmost( const bool& isTopmost )
{
	isTopmostFrame_ = isTopmost;
}


void Frame::setIsActive( const bool& active )
{


}

void Frame::activate()
{
	if ( false == allowsActivation() ) {
		return;
	}

	if ( this->isDesigning() ) {
		return;
	}
	

	if ( this != Frame::currentActiveFrame ) {

		
		Frame* oldActiveFrame = Frame::currentActiveFrame;

		Frame::currentActiveFrame = this;


		if ( (NULL != oldActiveFrame) && (this != oldActiveFrame) ) {

			
			if ( oldActiveFrame->getComponentState() == Component::csNormal ) {
				
				VCF::WindowEvent event( oldActiveFrame, Frame::ACTIVATION_EVENT );

				//StringUtils::trace( Format( "oldActiveFrame->FrameActivation.fireEvent, this[%s]@ %s\n" ) %
				//					oldActiveFrame->getClassName() % oldActiveFrame->toString() );

				oldActiveFrame->FrameActivation.fireEvent( &event );
			}
		}

		if ( getComponentState() == Component::csNormal ) {
			
			VCF::WindowEvent event( this, Frame::ACTIVATION_EVENT );
			FrameActivation.fireEvent( &event );
		}
	}
}

bool Frame::isActive()
{
	return (this == Frame::currentActiveFrame) && (isActiveFrame());
}

Frame* Frame::getActiveFrame()
{
	/*
	StringUtils::trace( Format( "Frame::getActiveFrame(): %p\n" ) % Frame::currentActiveFrame );
	Control* c = Control::getCurrentFocusedControl();
	StringUtils::trace( Format( "Control::getCurrentFocusedControl(): %p\n" ) % c );

	if ( NULL == Frame::currentActiveFrame ) {
		Frame::currentActiveFrame = c->getParentFrame();
	}
	*/
	return Frame::currentActiveFrame;
}

void Frame::internal_setActiveFrame( Frame* activeFrame )
{
	Frame::currentActiveFrame = activeFrame;
}

void Frame::afterCreate( ComponentEvent* event )
{
	Control::afterCreate( event );	
}

bool Frame::allowClose()
{
	bool result = false;
	FrameEvent event( this, CLOSING_EVENT );
	FrameClosing.fireEvent( &event );
	result = event.isOkToClose();

	return result;
}

Dialog* Frame::createDialog( Class* dialogClazz, ResourceBundle* resBundle )
{
	Dialog* result = NULL;

	result = (Dialog*)Component::createComponentFromResources( dialogClazz, classid(VCF::Dialog), resBundle );

	return result;
}

Window* Frame::createWindow( Class* windowClazz, ResourceBundle* resBundle )
{
	Window* result = NULL;

	result = (Window*)Component::createComponentFromResources( windowClazz, classid(VCF::Window), resBundle );

	return result;
}


/**
$Id$
*/
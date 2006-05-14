//Action.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"


using namespace VCF;


Action::Action():
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( Component* owner ):
	Component(owner),
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( const String& name, Component* owner ):
	Component(name, owner),
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( const String& name ):
	Component(name),
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::~Action()
{

}


void Action::update()
{
	ActionEvent event( this, Action::UpdateEvent );

	// let the application to set the desired state for the ActionEvent.
	Update.fireEvent( &event );


	std::vector<Component*>::iterator it = targets_.begin();

	while ( it != targets_.end() ) {
		(*it)->handleEvent( &event );
		it ++;
	}

	if ( NULL != currentAccelerator_ ) {
		currentAccelerator_->setEnabled( event.isEnabled() );
	}
}

void Action::perform( Event* event )
{
	if ( NULL != event ) {
		Performed.fireEvent( event );
	}
	else {
		ActionEvent e( this, Action::ActionPerformedEvent );
		Performed.fireEvent( &e );
	}
}

void Action::addTarget( Component* target )
{
	std::vector<Component*>::iterator found = std::find( targets_.begin(), targets_.end(), target );
	//don't allow duplicate entries
	if ( found == targets_.end() ) {
		targets_.push_back( target );
		target->setAction( this );
	}
}

void Action::removeTarget( Component* target )
{
	std::vector<Component*>::iterator found = std::find( targets_.begin(), targets_.end(), target );

	if ( found != targets_.end() ) {
		targets_.erase( found );
	}
}

Enumerator<Component*>* Action::getTargets()
{
	return targetsContainer_.getEnumerator();
}

unsigned long Action::getTargetCount()
{
	return targets_.size();
}

EventHandler* Action::getAcceleratorEventHandler()
{
	EventHandler* result = getEventHandler( "Action::onAccelerator" );
	if ( NULL == result ) {
		result = 
			new KeyboardEventHandler<Action>( this, &Action::onAccelerator, "Action::onAccelerator" );
	}

	return result;
}


void Action::setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask )
{
	
	EventHandler* eventHandler = getAcceleratorEventHandler();

	AcceleratorKey* newAccelKey = new AcceleratorKey( this, keyCode, modifierMask, eventHandler );

	setAcceleratorKey( newAccelKey );
}

void Action::setAcceleratorKey( AcceleratorKey* accelerator )
{
	//remove the old if present
	if ( NULL != currentAccelerator_ ) {
		UIToolkit::removeAccelerator( (VirtualKeyCode)currentAccelerator_->getKeyCode(),
																currentAccelerator_->getModifierMask(), this );
	}

	currentAccelerator_ = accelerator;

	if ( NULL != currentAccelerator_ ) {
		UIToolkit::registerAccelerator( currentAccelerator_ );
	}

	std::vector<Component*>::iterator it = targets_.begin();

	Event event(this, Action::AcceleratorChanged );

	while ( it != targets_.end() ) {
		(*it)->handleEvent( &event );
		it ++;
	}
}

AcceleratorKey* Action::getAccelerator()
{
	return currentAccelerator_;
}

void Action::onAccelerator( KeyboardEvent* e )
{
	perform();
}


/**
$Id$
*/
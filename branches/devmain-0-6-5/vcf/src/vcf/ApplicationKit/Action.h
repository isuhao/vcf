#if     _MSC_VER > 1000
#pragma once
#endif


#ifndef _VCF_ACTION_H__
#define _VCF_ACTION_H__

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


namespace VCF {


/**
<p>
The Action class is used to represent an "action" that gets performed because of 
some event from the UI, such as clicking a menu item or button. An Action also
allows you to consolidate multiple event handlers for menu items, buttons, etc,
and their associated code to update their UI state in relation to the application's
state. An Action has one or more targets that get notified for update events. Any of
these targets can also cause the action to be executed or "performed". 
<p>An example
of how this might be useful:
Consider an application that has three UI elements, a button, a toolbar item,
and a menu item. Clicking the menu item, toolbar item, or button all cause
some change of state in the application. Without using actions, you would have to
write 3 individual event handlers for the "click" events of the menu item,
button, and toolbar item, as well as separate ui updating code. If you use an 
action, you simply add all three items as targets to the action, and then write 
a single handler that's attached to the action's Performed delegate, and another 
event handler that is attached to the action's Update delegate. The framework then takes
care of the rest, and clicking the button, menu item, or toolbar item will all cause 
event handler attached to the action's Performed delegate to get called, and each
UI element will in turn be updated as specified by event handler attached to the 
action's Update delegate.

@delegates
	@del Update
	@del Performed
*/
class APPKIT_API Action : public Component {
public: 
	Action();

	Action( Component* owner );

	Action( const String& name, Component* owner );

	Action( const String& name );

	virtual ~Action();

	enum {
		UpdateEvent = 40521,
		ActionPerformedEvent = 40511
	};

	/** 
	@delegate Update this is fired when the action's update() method is called.
	@event	ActionEvent
	@eventtype Action::UpdateEvent
	@see update()
	*/
	DELEGATE(Update);	

	/**
	@delegate Performed this is fired when the action's perform()
	method is called.
	@event ActionEvent
	@eventtype Action::ActionPerformedEvent
	@see perform()
	*/
	DELEGATE(Performed);	

	/**
	This is called by a target (or the framework itself) to tell the action to fire off an 
	update event to all the actions targets.
	*/
	void update();

	/**
	This is called to execute the action. An action performed event will be fired off 
	to all the event handlers attached to the Performed delegate.
	*/
	void perform( Event* event=NULL );

	/**
	adds a target to the action
	*/
	void addTarget( Component* target );

	/**
	removes a target from the action.
	*/
	void removeTarget( Component* target );

	/**
	returns an enumerator of all the targets currently attached to this 
	action.
	*/
	Enumerator<Component*>* getTargets();

	/**
	returns a count of the number of targets attached to this action.
	*/
	unsigned long getTargetCount();

protected:
	std::vector<Component*> targets_;
	EnumeratorContainer<std::vector<Component*>,Component*> targetsContainer_;
};




};


/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.3  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.1.2.2  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.1.2.1  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*/



#endif // _VCF_ACTION_H__




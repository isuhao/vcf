#ifndef _VCF_COMPONENT_H__
#define _VCF_COMPONENT_H__
//Component.h

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

class Rect;
class InvalidPeer;
class Color;
class Border;
class Action;


#define COMPONENT_CLASSID		"ED88C09B-26AB-11d4-B539-00C04F0196DA"




/**
The base class for all objects within the Visual Component Framework
that wish to manipulated dynamically within the an IDE. All UI controls
are descended from this class.
<p>
Some of the services that are provided are as follows:
<ul>
<li>provides methods for registering components into logical
 	groups, that can then be displayed with an IDE
<li>provides the ability to own other components
<li>the ability to be manipulated by the IDE UI designer
<li>methods for uniquely identifying each instance, either
 	by name or by a numerical tag.
</ul>
</p>
<p>
The component itself is a <b>non</b> visual object, thus it can be used
as a base class for a wide variety of things, in addition to serving as
a base class for UI controls. The Component by itself is an abstract class
and should never be created by itself, instead you should be created derived
instances of classes derived from Component.

@delegates
	@del Component::ComponentCreated
	@del Component::ComponentDeleted
	@del Component::ComponentAdded
	@del Component::ComponentRemoved
	@del Component::ComponentLoaded
	@del Component::ComponentSaved
 */
class APPLICATIONKIT_API Component : public ObjectWithEvents { //, public Persistable{
protected:
	/**
	*The constructor and destructor is hidden - this is an abstract class and should NEVER
	*be instantiated directly
	*/
	Component();

	Component( Component* owner );

	Component( const String& name, Component* owner );

	Component( const String& name );

	/**
	*This is protected - you should call free, or release to destroy the component
	*/
	virtual ~Component();
public:

	enum ComponentEvents{
		COMPONENT_CREATED = 0,
		COMPONENT_DELETED,
		COMPONENT_NEEDS_UPDATING,
		COMPONENT_ADDED,
		COMPONENT_REMOVED,
		COMPONENT_LOADED,
		COMPONENT_SAVED,
		COMPONENT_EVENTS_LAST
	};


	/**
	*The ComponentState enum represents the current
	*state of the component. Some states will prevent
	*the Component from responding to events, for example,
	*a Control with it state set to CS_DESIGNING, will <b><i>not</i></b>
	*respond to certain UI events, while a Control with it's
	*state set to CS_DESTROYING, will not respond to any
	*pending UI events.
	*/
	enum ComponentState {
		csUnknown=0,
		/**
		csLoading and csReading are mutually exclusive - you can't be read AND writing at the
		same time
		*/
		csLoading = 0x1000,
		csSaving = 0x2000,
		csCreated = 1,
		csDesigning = 0x100,
		csNormal = 3,
		csDestroying = 4
	};

	/**
	*generic handler method for events. All UI events
	*are sent here and then dispatched accordingly to a
	*more specific event handler. If an Application class
	*is present, then it is given a chance to "see" the event
	*first before delegating it to the Component.
	*<p>
	*All events are dispatched by their type so it is important
	*to correctly identify the event objects type if you would
	*like it to me dispatched correctly.
	*@param Event based on the value returned by
	*Event::getType(), the method will call the
	*appropriate component method, like afterCreate(), beforeDestroy(), etc
	*/
	virtual void handleEvent( Event* event );

	/**
	@delegate ComponentCreated this is called when the component is created. This
	may be <i>after</i> the call to operator new to create the component instance.
	@event ComponentEvent
	@eventtype Component::COMPONENT_CREATED
	*/
	DELEGATE(ComponentCreated)

	/**
	@delegate ComponentDeleted this is fired when the component is being destroyed.
	Handlers attached to this delegate may safely call virtual methods of the component
	as the component's destructor has not yet been called.
	@event ComponentEvent
	@eventtype Component::COMPONENT_CREATED
	*/
	DELEGATE(ComponentDeleted)

	/**
	@delegate ComponentAdded this is fired when a new child component is added
	to this component.
	@event ComponentEvent
	@eventtype Component::COMPONENT_ADDED
	*/
	DELEGATE(ComponentAdded)

	/**
	@delegate ComponentRemoved this is fired when child component is removed
	from this component.
	@event ComponentEvent
	@eventtype Component::COMPONENT_REMOVED
	*/
	DELEGATE(ComponentRemoved)

	/**
	@delegate ComponentLoaded this is fired when child component is done being
	loaded from some InputStream.
	@event ComponentEvent
	@eventtype Component::COMPONENT_LOADED
	*/
	DELEGATE(ComponentLoaded)

	/**
	@delegate ComponentSaved this is fired when child component is removed
	from this component.
	@event ComponentEvent
	@eventtype Component::COMPONENT_SAVED
	*/
	DELEGATE(ComponentSaved)


	/**
	This is called to make sure the csLoading bit is set in the component
	state. Called by streams that read in a component object
	*/
	void loading();

	/**
	This is called to make sure the csSaving bit is set in the component
	state. Called by streams that write out a component object
	*/
	void saving();

	/**
	Fires an event to the ComponentLoaded delegate. The csLoading bit is removed
	from the component's state.
	*/
	void loaded();

	/**
	Fires an event to the ComponentSaved delegate. The csSaving bit is removed
	from the component's state.
	*/
	void saved();

	/**
	*The name of the component. While technically the name
	*can be any character sequence, it is preferred if the
	*name follow C++ variable name rules, i.e. must start
	*with a character of [a..z] or [A..Z], followed by any
	*sequence of characters in the set [a..z,A..Z,0..9,_].
	*The name of the component should be unique.
	*@return String the name of the component.
	*/
    virtual String getName();

	/**
	*sets the name of the component. For naming conventions/rules
	*please see getName().
	*/
    virtual void setName( const String& name );

	/**
	*called just prior to completely destroying the component
	*and it's associated memory.
	*/
    virtual void beforeDestroy( ComponentEvent* event );

	/**
	*after the component has been created/instantiated
	*the afterCreate() method is called. Special initializations
	*may then happen here.
	*/
	virtual void afterCreate( ComponentEvent* event );


	/**
	*returns the current state of the component.
	*Some states will prevent the Component from responding
	*to events, for example, a Control with it's state set to
	*CS_DESIGNING, will <b><i>not</i></b> respond to certain
	*UI events, while a Control with it's state set to
	*CS_DESTROYING, will not respond to any pending UI events.
	*/
	ulong32 getComponentState();

	/**
	queries the component state to check if it's
	set to csNormal or not.
	@return bool true if component state is csNormal, otherwise false
	*/
	bool isNormal() const ;

	/**
	queries the component state to check if it's
	set to csDestroying or not.
	@return bool true if component state is csDestroying, otherwise false
	*/
	bool isDestroying() const ;

	/**
	queries the component state to check if it's csLoading bit is set or not.
	@return bool true if component state includes csLoading, otherwise false
	*/
	bool isLoading() const ;

	/**
	queries the component state to check if it's csSaving bit is set or not.
	@return bool true if component state includes csSaving otherwise false
	*/
	bool isSaving() const ;

	/**
	queries the component state to check if it's csDesigning bit is set or not.
	@return bool true if component state includes csDesigning otherwise false
	*/
	bool isDesigning() const ;

	/**
	queries the component state to check if it's
	set to csCreated or not.
	@return bool true if component state is csCreated, otherwise false
	*/
	bool isCreated() const;




	/**
	*Sets the component's state
	*/
	void setComponentState( const ulong32& componentState );

	/**
	convenience fundtions for setting the component state
	*/
	void setCreated();
	void setNormal();
	void setDestroying();
	void setDesigning( const bool& designing );

	/**
	*adds a component to this component. Components may contain
	*one or more child, or owned, components. When the component is destroyed,
	*all owned components are destroyed as well. This is entirely independent
	*from the Container interface's add() method. This provides a convenient
	*way to clean up memory of components added on the heap. For
	*example, a Window may have a popup menu that is created during initialization.
	*By adding the popup menu (which is derived from Component), the popup
	*menu will be destroyed automatically for you once the Window is
	*destroyed. The implementation checks to prevent multiple adds of the
	*same component instance in the internal list.
	*/
	virtual void addComponent( Component* component );

	/**
	*removes the component.
	*/
	virtual void removeComponent( Component* component );

	/**
	*returns an enumeration of all the component's that this
	*component currently owns.
	*/
	virtual Enumerator<Component*>* getComponents();

	/**
	*returns the number of components owned by this component
	*/
	virtual unsigned long getComponentCount();

	/**
	*finds a particular component as specified by the componentName
	*parameter within the list of owned components.
	*@param String the name of the component to look for
	*@return Component a pointer to the Component with a matching
	*name to componentName. If no match is found or the component has
	*no owned components, the return value is NULL.
	*/
	Component* findComponent( const String& componentName );


	/**
	*Used to bind a variable to a component by attempting to bind the variable
	*passed in to the component in the variablePtr parameter to the component
	*instance with the same name as the variableName parameter. This functions
	*looks at all the owned components first, then checks to see if the Container
	*interface is supported, and if so, it checks all the child controls of the
	*container.
	*@param Component* a pointer to a Component pointer variable
	*@param String the name of the component to find
	*@return bool true if the component is found, otherwise false
	*/
	bool bindVariable( Component** variablePtr, const String& variableName );

	/**
	*returns the Component's tag value. A Tag is borrowed from the
	*NeXTStep idea of tags. A unique number is automatically associated
	*with the component when it is created, but can be changed by the programmer.
	*The following info is lifted directly from the NeXTSTEP docs.
	*"Tags are integers that you use in your code to identify objects.
	*They offer a convenient alternative to such methods of object identification
	*as fetching an object's title.  (What if the object't title changes while the
	*application is running, or the object has no title?)"
	*@return long the tag value of the Component
	*/
	long getTag() {
		return tag_;
	}

	/**
	*Sets the tag value
	*@param long - represents the new value of the component's tag will be set to.
	*/
	void setTag( const long& tag ) {
		tag_ = tag;
	}

	Component* getOwner() {
		return owner_;
	}


	Action* getAction() {
		return action_;
	}

	void setAction( Action* action );

	void addToUpdateTimer();
	void removeFromUpdateTimer();

	/**
	Allows the user to control whether or not the component should 
	attempt to translate the text of a specific component. This is typically 
	used in derived control classes paint() methods, which would check this value
	before calling System::getCurrentThreadLocale()->translate() to 
	translate the text to a specific locale sensitive value. Setting this
	value will also set it for any child components.
	@param bool A boolean value that indicates whether or not a  
	lookup should be made based on the current thread's locale to
	translate any text that needs displaying. A value of true means the
	lookup should take place, a value of false means the lookup should be 
	ignored.
	@see Locale
	@see System::getCurrentThreadLocale
	*/
	void setUseLocaleStrings( const bool& val );

	/**
	Returns a value indicating whether or not the component will attempt 
	to translate any text using the current thread's locale. By
	default, this is true.
	@return bool A boolean value that indicates whether or not a  
	lookup will be made based on the current thread's locale to
	translate any text that needs displaying. A value of true means the
	lookup will take place, a value of false means the lookup will be 
	ignored.

	*/
	bool getUseLocaleStrings() {
		return useLocaleStrings_;
	}

	/**
	*registers a component in the system component map. The map is organized into
	a series of keys called categories, with 1 or more entries in each category.
	The UIToolkit registers the default ApplicationKit components, and other developers may
	use this to extend the list with their own components.
	*/
	static bool registerComponent( const String& componentClassName, const String& category );

	/**
	*Used by IDE's to list the various Component classes for a given category. Each Class pointer
	*that is contained in the Enumerator guarantees the ability to create an instance
	*of the component it represents.
	*/
	static Enumerator<Class*>* getComponentClassesForCategory( const String& category );

	/**
	*returns a list of all the known, registered, component categories. These in turn
	*may be used to gather the classes for each category with a call to the getComponentClassesForCategory()
	*static method.
	*@see Component::getComponentClassesForCategory()
	*/
	static Enumerator<String>* getRegisteredComponentCategories();

	/**
	*
	*/
	static void initComponentRegistrar();

	static void clearRegistedComponents();

protected:
	Component* owner_;
	ulong32 componentState_;
    String name_;
	long tag_;
	Action* action_;
	std::vector<Component*> components_;
	EnumeratorContainer<std::vector<Component*>, Component*> componentContainer_;
	
	bool useLocaleStrings_;


	/**
	*a map of component classes to categorys
	*/
	static std::map<String,std::vector<Class*>*>* registeredComponentMap;
	static std::vector<String>* registeredCategory;
	static EnumeratorContainer<std::vector<String>,String>* registeredCategoryContainer;
	static EnumeratorContainer<std::vector<Class*>,Class*>* registeredCompContainer;



	virtual void destroy();
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.4  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/06/05 02:57:09  ddiego
*fixed a syntax mistake that tinkham pointed out.The problem was that the findComponent() method was incorrectly declared.
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.27.2.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.27  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.26  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.24.2.2  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.24.2.1  2004/01/15 05:35:03  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.24.2.2  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.24.2.1  2004/01/15 05:35:03  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.24  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.23.4.8  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.23.4.7  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.23.4.6  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.23.4.5  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.23.4.4  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.23.4.3  2003/09/06 19:45:44  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.23.4.2  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.23.4.1  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.23  2003/05/17 20:37:01  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.22.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.22.2.1  2003/03/12 03:09:23  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.22  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.21.14.3  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.21.14.2  2003/01/08 00:19:42  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.21.14.1  2002/12/25 22:06:16  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.21  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.20.4.1  2002/04/27 15:41:54  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.20  2002/02/20 04:07:49  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.19  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COMPONENT_H__



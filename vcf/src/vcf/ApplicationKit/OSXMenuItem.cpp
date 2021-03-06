//OSXMenuItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXMenuItem.h"




using namespace VCF;


//uint32 OSXMenuItem::globalMenuItemID = 0;
/*
String OSXGenerateCaption( MenuItem* item, OSXMenuItem* peer, String caption )
{
	String acceleratorText;
	VCF::AcceleratorKey* accelerator = item->getAccelerator();
	//generate accelerator text if we are not owner drawn
	if ( !item->canPaint() && (NULL != accelerator) ) {
		
		if ( accelerator->hasCtrlKey() ) {			
			acceleratorText += "Ctrl";
		}

		if ( accelerator->hasShiftKey() ) {
			if ( !acceleratorText.empty() ) {
				acceleratorText += "+";
			}
			acceleratorText += "Shift";
		}

		if ( accelerator->hasAltKey() ) {
			if ( !acceleratorText.empty() ) {
				acceleratorText += "+";
			}
			acceleratorText += "Alt";
		}

		if ( !acceleratorText.empty() ) {
			acceleratorText += "+";
		}

		acceleratorText += StringUtils::translateVKCodeToString( (VirtualKeyCode)accelerator->getKeyCode() );		
	}

	if ( !acceleratorText.empty() ) {
		caption = caption + "\t" + acceleratorText;
	}
	
	UIPolicyManager* pm = UIToolkit::getUIPolicyManager();
	caption = pm->transformMnemonicValues( caption );

	return caption;
}
*/



OSXMenuItem::OSXMenuItem( MenuItem* item ):
	itemID_(0),
	menuItem_(item),
	itemAdded_(false),
	nsMenuItem_(nil)
{
	nsMenuItem_ = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
}

OSXMenuItem::OSXMenuItem():
	itemID_(0),
	menuItem_(NULL),
	itemAdded_(false),
	nsMenuItem_(nil)
{
	nsMenuItem_ = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
}

OSXMenuItem::~OSXMenuItem()
{
	[nsMenuItem_ release];
}

bool OSXMenuItem::isMenuItemRoot( MenuItem* item )
{
	bool result = false;
		
	if ( NULL != item ) {
		MenuItem* parent = item->getParent();
		Menu* menuOwner = item->getMenuOwner();
		if ( NULL == menuOwner ) {
			while ( parent != NULL ) {
				menuOwner = parent->getMenuOwner();
				if ( NULL != menuOwner ) {
					break;
				}
				parent = parent->getParent();
			}
			parent = item->getParent();
		}
		
		if ( NULL != menuOwner ) {
			result = (menuOwner->getRootMenuItem() == item);
		}
		else if ( NULL == parent ) {
			result = true;
		}
	}
	return result;
}
	
bool OSXMenuItem::isParentMenuItemRoot( MenuItem* item )
{
	bool result = false;
		
	if ( NULL != item ) {
		MenuItem* parent = item->getParent();
		Menu* menuOwner = item->getMenuOwner();
		if ( NULL == menuOwner ) {
			while ( parent != NULL ) {
				menuOwner = parent->getMenuOwner();
				if ( NULL != menuOwner ) {
					break;
				}
				parent = parent->getParent();
			}
			parent = item->getParent();
		}
		
		if ( NULL != menuOwner ) {
			result = (menuOwner->getRootMenuItem() == parent);
		}
		else  if ( NULL != parent ) {
			if ( NULL == parent->getParent() ) {
				result = true;
			}
		}
	}
	return result;
}


bool OSXMenuItem::isMenuItemRoot()
{
	
	return OSXMenuItem::isMenuItemRoot( menuItem_ );
}

bool OSXMenuItem::isParentMenuItemRoot()
{
	return OSXMenuItem::isParentMenuItemRoot( menuItem_ );
}

void OSXMenuItem::addChild( MenuItem* child )
{
	uint32 index = child->getIndex();// maxVal<uint32>( menuItem_->getChildCount()-1, 0 );
	
	insertChild( index, child );
}

void OSXMenuItem::fixChildren( MenuItem* child )
{
	if ( child->hasChildren() ) {
		Enumerator<MenuItem*>* children = child->getChildren();
		while ( children->hasMoreElements() ) {
			MenuItem* item = children->nextElement();
			OSXMenuItem* itemPeer = (OSXMenuItem*) item->getPeer();
			if ( false == itemPeer->itemAdded_ ) {
				item->setMenuOwner( child->getMenuOwner() );
				OSXMenuItem* peer = (OSXMenuItem*) child->getPeer();
				peer->addChild( item );
			}
		}
	}
}

void OSXMenuItem::insertChild( const uint32& index, MenuItem* child )
{
	child->setIndex( index );
	
	NSMenu* subMenu = nil;
	if ( ![nsMenuItem_ hasSubmenu] ) {
		subMenu = [[NSMenu alloc] initWithTitle:@""];
		[nsMenuItem_ setSubmenu:subMenu];
	}
	NSMenuItem* item = (NSMenuItem*) child->getPeer()->getHandleID();
	
	CFTextString title( child->getCaption() );
	
	[item setTitle:title];
	
	[subMenu insertItem:item atIndex:index];
	
	//CFTextString tmp( OSXGenerateCaption( child, (OSXMenuItem*)child->getPeer(), child->getCaption() ) );
	//is this child a top level menu item?
	
	/*
	if ( OSXMenuItem::isParentMenuItemRoot( child ) ) {
		OSXMenuItem* peer = (OSXMenuItem*)child->getPeer();		
		MenuRef handle = (MenuRef) peer->getHandleID();
		if ( NULL != handle ) {
			InsertMenu( handle, peer->itemID_ );
			SetMenuTitleWithCFString( handle, tmp );
			itemAdded_ = true;
		}
		else {
			//we should get picked up later
			return;
		}
	}
	else {
		OSXMenuItem* peer = (OSXMenuItem*)child->getPeer();		
		MenuRef handle = 0;		
		
		if ( menuItem_->hasChildren() && (!isParentMenuItemRoot()) ) {
			OSXMenuItem* parentPeer = (OSXMenuItem*)menuItem_->getParent()->getPeer();
			MenuRef parentRef = (MenuRef) parentPeer->getHandleID();
			int index = menuItem_->getIndex();
			
			GetMenuItemHierarchicalMenu( parentRef, index, &handle );
			if ( NULL == handle ) {		
				handle = (MenuRef) getHandleID();
				
				//apparently the menu index is 1 based! Go figure!
				OSStatus err = SetMenuItemHierarchicalMenu( parentRef, index+1, handle );
				if ( err != noErr ) {
					printf( "Error with SetMenuItemHierarchicalMenu(): %d\n", err );
				}
			}
		}
		else {
			handle = (MenuRef) getHandleID();
		}
		
		MenuItemIndex childIndex = index;
		InsertMenuItemTextWithCFString( handle, tmp, childIndex, 0, peer->itemID_ );	
		itemAdded_ = true;
		
					
		SetMenuCommandProperty( handle, peer->itemID_, 
							VCF_PROPERTY_CREATOR, 
							OSXMenuItem::propertyTag,
							sizeof(child), 
							&child );		
	}
	*/
	/**
	check to see if we have children that have not yet been added
	*/
	fixChildren( child );
}

void OSXMenuItem::deleteChild( MenuItem* child )
{
	int index = child->getIndex();
/*
	OSXMenuItem* peer = (OSXMenuItem*)child->getPeer();
	MenuRef handle = (MenuRef) getHandleID();	
	
	if ( child->hasChildren() ) {
		DeleteMenu( peer->itemID_ );
	}
	DeleteMenuItem( handle, index + 1 );
	*/
}

void OSXMenuItem::deleteChild( const uint32& index )
{
	MenuItem* child = menuItem_->getChildAt(index);
	deleteChild( child );
}

void OSXMenuItem::clearChildren()
{
	//MenuRef handle = (MenuRef) getHandleID();	
	int start = 1;
	//DeleteMenuItems( handle, 1,	menuItem_->getChildCount() );
}

bool OSXMenuItem::isChecked()
{
	bool result = false;
	/*
	MenuItem* parent = menuItem_->getParent();
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getHandleID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = 0;
	GetItemMark( parentHandle, index, &markChar );
	if ( checkMark == markChar ) {
		result = true;
	}
	*/
	return result;
}

void OSXMenuItem::setChecked( const bool& checked )
{
	if ( menuItem_->hasChildren() ) {
		return;
	}
	/*
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getHandleID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = checked ? checkMark : 0;
	SetItemMark( parentHandle, index, markChar );
	*/
}

bool OSXMenuItem::hasParent()
{
	return false;
}

MenuItem* OSXMenuItem::getParent()
{
	return menuItem_->getParent();
}

MenuItem* OSXMenuItem::getChildAt( const uint32& index )
{
	return NULL;
}

bool OSXMenuItem::isEnabled()
{
/*
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getHandleID();
	
	int index = menuItem_->getIndex()+1;
	*/
	return false; // IsMenuItemEnabled( parentHandle, index ) ? true : false;
}

void OSXMenuItem::setEnabled( const bool& enabled )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	/*
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getHandleID();
	
	int index = menuItem_->getIndex()+1;
	if ( enabled ) {
		EnableMenuItem( parentHandle, index );
	}
	else {
		DisableMenuItem( parentHandle, index );
	}
	*/	
}

bool OSXMenuItem::isVisible()
{
	return true;
}

void OSXMenuItem::setVisible( const bool& visible )
{
	int index = menuItem_->getIndex();
	if ( visible ){

	}
	else {
		//RemoveMenu( itemHandle_, index, MF_BYPOSITION );
	}
}

bool OSXMenuItem::getRadioItem()
{
	bool result = false;
	/*
	MenuItem* parent = menuItem_->getParent();
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getHandleID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = 0;
	GetItemMark( parentHandle, index, &markChar );
	if ( diamondMark == markChar ) {
		result = true;
	}
	*/
	return result;
}

void OSXMenuItem::setRadioItem( const bool& value )
{	
	if ( menuItem_->hasChildren() || menuItem_->isSeparator() ) {
		return;
	}
	/*
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getHandleID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = value ? diamondMark : 0;
	SetItemMark( parentHandle, index, markChar );
	*/
}

void OSXMenuItem::setMenuItem( MenuItem* item )
{
	menuItem_ = item;
}




void OSXMenuItem::setCaption( const String& caption )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	/*
	int index = menuItem_->getIndex();
	
	MenuItem* parent = menuItem_->getParent();
	
	if ( NULL != parent ) {
		CFTextString tmp( OSXGenerateCaption( menuItem_, this, caption ) );
		
		if ( isParentMenuItemRoot() ) {
			MenuRef handle = (MenuRef) getHandleID();		
			if ( NULL != handle ) {		
				SetMenuTitleWithCFString( handle, tmp );
			}
		}
		else {
			OSXMenuItem* peer = (OSXMenuItem*)parent->getPeer();
			MenuRef ref = (MenuRef) peer->getHandleID();
			
			SetMenuItemTextWithCFString( ref, index + 1, tmp );
		}
	}
	*/
}

OSHandleID OSXMenuItem::getHandleID()
{
/*
	if ( isMenuItemRoot() ) {
		printf( "the menu item is the root item!\n" );
		return 0;
	}
	
	if ( NULL != menuItem_ ){		
		Menu* menuOwner = menuItem_->getMenuOwner();
		//find our owner
		if ( NULL == menuOwner ){
			MenuItem* parent = menuItem_->getParent();
			while ( parent != NULL ) {
				menuOwner = parent->getMenuOwner();
				if ( NULL != menuOwner ) {
					break;
				}
				parent = parent->getParent();
			}
		}
		
		if ( (NULL == itemHandle_) && (NULL != menuOwner)  ){
			PopupMenu* popupOwner = dynamic_cast<PopupMenu*>( menuOwner );
			if ( NULL != popupOwner ){
				//itemHandle_ = ::CreatePopupMenu();
				//We need to create a popup menu - i.e. a context menu!
				
			}
			else {
				MenuBar* menuBarOwner = dynamic_cast<MenuBar*>( menuOwner );
				
				//At this point we either have a menu bar, because we are top level 
				//items, 
				//or..
				//We don't, which means we are nested hierarchical menu items
				
				if ( NULL != menuBarOwner ){
					if ( isParentMenuItemRoot() ) {
						CreateNewMenu( itemID_,0,&itemHandle_);
						CFTextString tmp( menuItem_->getCaption() );
						SetMenuTitleWithCFString( itemHandle_, tmp );
					}
					else {						
						OSStatus err = CreateNewMenu( itemID_,0,&itemHandle_);						
						if ( noErr != err ) {
							printf( "CreateNewMenu failed. err: %d\n", err );
						}
						CFTextString tmp( menuItem_->getCaption() );
						SetMenuTitleWithCFString( itemHandle_, tmp );
					}
					
					SetMenuCommandProperty( itemHandle_, 0, 
							VCF_PROPERTY_CREATOR, 
							OSXMenuItem::propertyTag,
							sizeof(menuItem_), 
							&menuItem_ );
				}
				else {
					throw RuntimeException(MAKE_ERROR_MSG("Unknown or Invalid Menu Item owner"), __LINE__);
				}
			}

			if ( menuItem_->hasChildren() && NULL == itemHandle_  ){
				throw RuntimeException(MAKE_ERROR_MSG("Error allocation Resources for Menu Item Peer. CreateNewMenu failed."), __LINE__);
			}
		}
	}
	*/
	return (OSHandleID)nsMenuItem_;
}


void OSXMenuItem::setAsSeparator( const bool& isSeperator )
{
	int index = menuItem_->getIndex()+1;
	NSMenu* menu = [nsMenuItem_ menu];
	
	if ( isSeperator ) {
		
		if ( nil != nsMenuItem_ && menu ) {
			[menu removeItem:nsMenuItem_];
			[nsMenuItem_ release];
		}
		
		nsMenuItem_ = [NSMenuItem separatorItem];
		[menu insertItem:nsMenuItem_ atIndex:index];
	}
	else {
		if ( nil != nsMenuItem_ && menu ) {
			[menu removeItem:nsMenuItem_];
		}
		
		nsMenuItem_ = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
		[menu insertItem:nsMenuItem_ atIndex:index];		
	}
}

void OSXMenuItem::setAcceleratorKey( AcceleratorKey* accelerator )
{
	NSString* key = nil; 
	switch ( accelerator->getKeyCode() ) {
		
	}
}


/**
$Id$
*/

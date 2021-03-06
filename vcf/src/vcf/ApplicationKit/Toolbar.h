#ifndef _VCF_TOOLBAR_H__
#define _VCF_TOOLBAR_H__
//Toolbar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif






namespace VCF{

class ToolbarButton;

class ToolbarDock;


class ToolbarPeer;

#define TOOLBARITEM_CLASSID		"257ad8c4-dc5d-4d4a-b4fa-be668a550c5b"
/**
\class ToolbarItem Toolbar.h "vcf/ApplicationKit/Toolbar.h" 
*/
class APPLICATIONKIT_API ToolbarItem : public Item, public Button {
public:

	ToolbarItem();
	virtual ~ToolbarItem();

	enum {
		tbCaptionChanged = 200431,
		tbTooltipChanged,
		tbSelected,
		tbDimensionsChanged,
		tbAdded,
		tbRemoved,
		tbStateChanged,
		tbImageIndexChanged,
		tbStateImageIndexChanged,
		tbIndexChanged,
		tbItemControlAdded,
		tbItemClicked,
		tbItemUpdate,
		tbGroupChanged,
		tbCheckChanged
	};

	enum ToolbarItemState {
		tisNone = 0,
		tisSeparator = 0x01,
		tisSelected = 0x10,
		tisPressed = 0x20,
		tisEnabled = 0x40,
		tisGrouped = 0x100,
		tisChecked = 0x200,
		tisDropDown = 0x400
	};

	
	DELEGATE(ButtonDelegate,ItemClicked);

	DELEGATE(EventDelegate,ItemUpdate);

	virtual void click();

	virtual void setDefault( const bool& defaultButton ) {}

	virtual bool isDefault(){
		return false;
	};

    virtual bool containsPoint( Point * pt );

	virtual void setBounds( Rect* bounds );
	
	virtual int32 getStateImageIndex() {
		return imageStateIndex_;
	}

	virtual void setStateImageIndex( const int32& index );

    virtual uint32 getIndex();

	virtual int32 getImageIndex() {
		return imageIndex_;
	}

	virtual void setImageIndex( const int32& imageIndex );

	virtual void setIndex( const uint32& index ) ;
	
	virtual void setDisplayState( const int32& state );
	
	virtual void paint( GraphicsContext* context, Rect* paintRect ) {};

	virtual bool isSelected() ;

	virtual void setSelected( const bool& selected );

	void setWidth( const double& val );

	double getWidth();

	String getCaption() {
		return caption_;
	}

	void setCaption( const String& val );

	String getTooltip() {
		if ( getUseLocaleStrings() ) {
			return System::getCurrentThreadLocale()->translate( tooltip_ );
		}
		return tooltip_;
	}

	void setTooltip( const String& val );

	void setAsSeparator( const bool& val=true );

	bool isSeparator() {
		return getDisplayState() == tisSeparator;	
	}

	void setPressed( const bool& val );

	bool isPressed() {
		return getDisplayState() & ToolbarItem::tisPressed ? true : false;
	}


	void setIsDropDown( const bool& val );

	bool isDropDown() {
		return getDisplayState() & ToolbarItem::tisDropDown ? true : false;
	}

	

	void setItemControl( Control* control );

	Control* getItemControl() {
		return itemControl_;
	}

	bool isEnabled();

	void setEnabled( const bool& val );

	/**
	Utility method - not meant for public use
	*/
	void internal_setBounds( const Rect& bounds ); //Parameter made const for ANSI compliance - ACH

	void setGrouped( const bool& val );

	bool isGrouped();

	void setChecked( const bool& val );

	bool isChecked();

	virtual bool updateAction();

	virtual void handleEvent( Event* event );

	
protected:
	Control* itemControl_;	
	int32 imageStateIndex_;
	String caption_;
	String tooltip_;
};


class APPLICATIONKIT_API ToolbarSeparator : public ToolbarItem {
public:

	ToolbarSeparator();
	virtual ~ToolbarSeparator(){}
};


class ToolbarModel;

/**
\class ToolbarModelEvent Toolbar.h "vcf/ApplicationKit/Toolbar.h" 
*/
class APPLICATIONKIT_API ToolbarModelEvent : public ModelEvent {
public:

	ToolbarModelEvent( Object* source, uint32 type ): ModelEvent(source,type),item_(NULL) {

	}

	ToolbarModel* getToolbarModel() {
		return (ToolbarModel*)getSource();
	}


	ToolbarItem* getItem() {
		return item_;
	}

	void setItem( ToolbarItem* item ) {
		item_ = item;
	}

	ToolbarItem* item_;
};



/**
\class ToolbarItem Toolbar.h "vcf/ApplicationKit/Toolbar.h" 
*/
class APPLICATIONKIT_API ToolbarModel : public Model {
public:
	ToolbarModel();

	virtual ~ToolbarModel();

	void addItem( ToolbarItem* item );
	void insertItem( ToolbarItem* item, const uint32& index );
	void removeItem( ToolbarItem* item );


	void itemChanged( const uint32& eventType, ToolbarItem* item );

	uint32 getItemIndex( ToolbarItem* item );
	void setItemIndex( ToolbarItem* item, const uint32& newIndex );

	ToolbarItem* getItemAtIndex( const uint32& index ) {
		return toolbarItems_[index];
	}

	Enumerator<ToolbarItem*>* getToolbarItems() {
		return itemsContainer_.getEnumerator();
	}
protected:
	std::vector<ToolbarItem*> toolbarItems_;
	EnumeratorContainer<std::vector<ToolbarItem*>,ToolbarItem*> itemsContainer_;
};










#define TOOLBAR_CLASSID		"D8B85915-BCE1-44e3-8FBB-3B43427F99F1"

/**
\class Toolbar Toolbar.h "vcf/ApplicationKit/Toolbar.h" 
A class for adding toolbars to your window. A toolbar has a 
series of buttons (each represented by a ToolbarItem). 
 */
class APPLICATIONKIT_API Toolbar : public Control {
public:

	Toolbar();

	virtual ~Toolbar();

	ToolbarModel* getToolbarModel() {
		return (ToolbarModel*)getViewModel();
	}	

	ToolbarItem* addToolBarButton( const String& caption ) {
		ToolbarItem* item = new ToolbarItem();
		item->setCaption( caption );
		getToolbarModel()->addItem( item );
		return item;
	}


	ImageList* getImageList() {
		return imageList_;
	}

	void setImageList( ImageList* imageList );

	

	void setShowButtonCaptions( const bool& val );

	bool getShowButtonCaptions() {
		return showButtonCaptions_;
	}

	Size getButtonSize() {
		return buttonSize_;
	}

	void setButtonSize( const Size& buttonSize );

	double getButtonWidth() {
		return buttonSize_.width_;
	}

	void setButtonWidth( const double& val ) {
		Size sz = buttonSize_;
		sz.width_ = val;
		setButtonSize( sz );
	}

	double getButtonHeight() {
		return buttonSize_.height_;
	}

	void setButtonHeight( const double& val ) {
		Size sz = buttonSize_;
		sz.height_ = val;
		setButtonSize( sz );
	}


	void setButtonCaptionsHorizontal( const bool& val );

	bool getButtonCaptionsHorizontal() {
		return buttonCaptionsHorizontal_;
	}

	void setEnableAutoResize( const bool& val );
	bool isAutoResizeEnabled();

	void setVertical( const bool& val ); 
	bool isVertical();

	void setWrapButtons( const bool& val ); 
	bool isWrapButtons();

	void handleEvent( Event* event );

	virtual void paint( GraphicsContext* context );
protected:
	ToolbarPeer* toolbarPeer_;
	ImageList* imageList_;
	bool showButtonCaptions_;
	bool buttonCaptionsHorizontal_;
	Size buttonSize_;


public:
	/**
	*inner class used by the Toolbar to create a Floating
	*toolbar window when the Toolbar is dragged out of it's dock.
	*/
	class FloatingToolbar : public Window {
	public:
		FloatingToolbar();

		virtual ~FloatingToolbar();
	protected:
	private:
	};

};

};


#endif // _VCF_TOOLBAR_H__

/**
$Id$
*/

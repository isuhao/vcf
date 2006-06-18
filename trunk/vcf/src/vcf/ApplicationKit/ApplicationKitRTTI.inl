//ApplicationKitRTTI.inl

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
this declares all the RTTI for the ApplicationKit's classes.
This was created to improved compile times
*/

#include "vcf/ApplicationKit/EtchedBorder.h"
#include "vcf/ApplicationKit/ColorEtchedBorder.h"
#include "vcf/ApplicationKit/TitledBorder.h"
#include "vcf/ApplicationKit/MessageDialog.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"
#include "vcf/ApplicationKit/SystemTray.h"
#include "vcf/ApplicationKit/ColumnLayoutContainer.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"


namespace VCF {

/**
*A string array for the controls alignement types
*/
static String AlignmentTypeNames[] = { "AlignNone",
                                         "AlignTop",
										 "AlignLeft",
										 "AlignRight",
										 "AlignBottom",
										 "AlignClient" };
										 
										 

/**
*an array of Anchor type names
*/
static String AnchorTypeNames[] = { "AnchorNone",
                                         "AnchorTop",
										 "AnchorLeft",
										 "AnchorBottom",
										 "AnchorRight" };
										 
										 
										 

static unsigned long AnchorTypeValues[] = { AnchorNone,
                                         AnchorTop,
										 AnchorLeft,
										 AnchorBottom,
										 AnchorRight };	



static String TextAlignmentTypeNames[] = { "taTextLeft",
                                         "taTextCenter",
										 "taTextRight" };
										 




_class_rtti_(ImageList, "VCF::Component", IMAGELIST_CLASSID )
_property_object_( Color, "transparentColor", getTransparentColor, setTransparentColor, "" );
_event_("VCF::ImageListEventHandler", VCF::ImageListEvent, SizeChanged );
_event_("VCF::ImageListEventHandler", VCF::ImageListEvent, ImageAdded );
_event_("VCF::ImageListEventHandler", VCF::ImageListEvent, ImageDeleted );
_class_rtti_end_


_class_abstract_rtti_(Border, "VCF::Component", BORDER_CLASSID)
_class_rtti_end_

_class_rtti_(Basic3DBorder, "VCF::Border", BASIC3DBORDER_CLASSID)
_property_( bool, "inverted", isInverted, setInverted, "" );
_class_rtti_end_


_class_rtti_(EtchedBorder, "VCF::Border", ETCHEDBORDER_CLASSID)
_property_( long, "sidesToPaint", getSidesToPaint, setSidesToPaint, "" );
_property_( long, "edgeStyle", getEdgeStyle, setEdgeStyle, "" );
_class_rtti_end_



_class_rtti_(ColorEtchedBorder, "VCF::EtchedBorder", COLORETCHEDBORDER_CLASSID)
_property_object_( Color, "highlight", getHighlight, setHighlight, "" );
_property_object_( Color, "shadow", getShadow, setShadow, "" );
_class_rtti_end_


_class_rtti_(Light3DBorder, "VCF::Border", LIGHT3DBORDER_CLASSID)
_property_( bool, "inverted", isInverted, setInverted, "" );
_class_rtti_end_

_class_rtti_(TitledBorder, "VCF::Border", TITLEDBORDER_CLASSID)
_property_( long, "sidesToPaint", getSidesToPaint, setSidesToPaint, "" );
_property_object_( Font, "font", getFont, setFont, "" );
_property_( String, "caption", getCaption, setCaption, "" );
_class_rtti_end_


_class_abstract_rtti_(Container, "VCF::Component", CONTAINER_CLASSID)
_class_rtti_end_

_class_abstract_rtti_(AbstractContainer, "VCF::Container", ABSTRACTCONTAINER_CLASSID)
_class_rtti_end_

_class_rtti_(StandardContainer, "VCF::AbstractContainer", STANDARDCONTAINER_CLASSID)
_property_( double, "bottomBorderHeight", getBottomBorderHeight, setBottomBorderHeight, "" );
_property_( double, "topBorderHeight", getTopBorderHeight, setTopBorderHeight, "" );
_property_( double, "rightBorderWidth", getRightBorderWidth, setRightBorderWidth, "" );
_property_( double, "leftBorderWidth", getLeftBorderWidth, setLeftBorderWidth, "" );
_class_rtti_end_

_class_rtti_(ColumnLayoutContainer, "VCF::StandardContainer", COLUMNLAYOUTCONTAINER_CLASSID)
_class_rtti_end_

_class_rtti_(HorizontalLayoutContainer, "VCF::StandardContainer", HORIZONTALLAYOUTCONTAINER_CLASSID)
_class_rtti_end_
/*
_class_abstract_rtti_(AbstractListModel, "VCF::AbstractListModel", "VCF::ListModel", ABSTRACTLISTMODEL_CLASSID)
_event_( "VCF::ModelEventHandler", AbstractListModel, VCF::ModelEvent, ModelEmptied )
_event_( "VCF::ModelValidationEventHandler", AbstractListModel, VCF::ValidationEvent, ModelValidate )
_event_( "VCF::ListModelEventHandler", AbstractListModel, VCF::ListModelEvent, ContentsChanged )
_event_( "VCF::ListModelEventHandler", AbstractListModel, VCF::ListModelEvent, ItemAdded )
_event_( "VCF::ListModelEventHandler", AbstractListModel, VCF::ListModelEvent, ItemDeleted )
_class_rtti_end_
*/

_class_abstract_rtti_(Model, "VCF::Component", MODEL_CLASSID)
_event_( "VCF::ModelEventHandler", VCF::ModelEvent, ModelChanged )
_event_( "VCF::ModelValidationEventHandler", VCF::ValidationEvent, ModelValidate )
_class_rtti_end_

_class_abstract_rtti_(AbstractModel, "VCF::Model", ABSTRACTMODEL_CLASSID)

_class_rtti_end_

/*
_class_abstract_rtti_(TextModel, "VCF::TextModel", "VCF::Model", TEXTMODEL_CLASSID)
_abstract_event_("VCF::TextModelEventHandler", TextModel, VCF::TextEvent, TextModelChanged )
_class_rtti_end_
*/

_class_abstract_rtti_(ColumnItem, "VCF::Item", COLUMNITEM_CLASSID)
_class_rtti_end_




_class_abstract_rtti_(ColumnModel, "VCF::Model", COLUMNMODEL_CLASSID)
_abstract_event_( "VCF::ColumnModelEventHandler", VCF::ColumnModelEvent, ContentsChanged )
_abstract_event_( "VCF::ColumnModelEventHandler", VCF::ColumnModelEvent, ItemAdded )
_abstract_event_( "VCF::ColumnModelEventHandler", VCF::ColumnModelEvent, ItemDeleted )
_class_rtti_end_

_class_abstract_rtti_(Component, "VCF::Object", COMPONENT_CLASSID)
_property_( long, "tag", getTag, setTag, "" );
_property_( String, "name", getName, setName, "" );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentCreated );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentDestroyed );
_class_rtti_end_


_class_abstract_rtti_(Control,  "VCF::Component", CONTROL_CLASSID);
_property_( double, "left", getLeft, setLeft, "" );
_property_( double, "top", getTop, setTop, "" );
_property_( double, "right", getRight, setRight, "" );
_property_( double, "bottom", getBottom, setBottom, "" );
_property_( bool, "visible", getVisible, setVisible, "" );
_property_( double, "width", getWidth, setWidth, "" );
_property_( double, "height", getHeight, setHeight, "" );
_property_( bool, "enabled", isEnabled, setEnabled, "" );
_property_( bool, "doubleBuffered", isDoubleBuffered, setDoubleBuffered, "" );
_property_( bool, "useParentFont", useParentFont, setUseParentFont, "" );
_property_( bool, "autoStartDragDrop", getAutoStartDragDrop, setAutoStartDragDrop, "" );
_property_( bool, "tabStop", getTabStop, setTabStop, "" );
_property_( long, "tabOrder", getTabOrder, setTabOrder, "" );
_property_( String, "whatThisHelpString", getWhatThisHelpString, setWhatThisHelpString, "" );
_property_( String, "toolTipText", getToolTipText, setToolTipText, "" );
_property_object_( Border, "border", getBorder, setBorder, "" );
_property_object_( Color, "color", getColor, setColor, "" );
_property_object_( Font, "font", getFont, setFont, "" );
_property_object_( PopupMenu, "popupMenu", getPopupMenu, setPopupMenu, "" );
_property_object_( Container, "container", getContainer, setContainer, "" );
_property_enum_labeled_( AlignmentType, "alignment", getAlignment, setAlignment,
					   AlignNone, AlignClient, 6, AlignmentTypeNames, "");

_property_enumset_( VCF::AnchorTypes, "anchor", getAnchor, setAnchor, 5, AnchorTypeValues, AnchorTypeNames, ""  );

_property_typedef_( long, "cursor", getCursorID, setCursorID, "VCF::Cursor::SystemCursorType", "" );

_event_("VCF::ControlEventHandler",  VCF::ControlEvent, ControlSized );
_event_("VCF::ControlEventHandler", VCF::ControlEvent, ControlPositioned );
_event_("VCF::ControlEventHandler", VCF::ControlEvent, ControlParentChanged );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, MouseDoubleClicked );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, MouseClicked );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, MouseMove );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, MouseUp );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, MouseDown );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, MouseEnter );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, MouseLeave );
_event_("VCF::KeyboardEventHandler", VCF::KeyboardEvent, KeyPressed  );
_event_("VCF::KeyboardEventHandler", VCF::KeyboardEvent, KeyDown  );
_event_("VCF::KeyboardEventHandler", VCF::KeyboardEvent, KeyUp  );
_event_("VCF::WhatsThisHelpEventHandler", VCF::WhatsThisHelpEvent, ControlHelpRequested );
_event_("VCF::HelpEventHandler", VCF::HelpEvent, HelpRequested );
_event_("VCF::FocusEventHandler", VCF::FocusEvent, FocusLost  );
_event_("VCF::FocusEventHandler", VCF::FocusEvent, FocusGained );

_event_("VCF::ToolTipEventHandler", VCF::ToolTipEvent, ToolTipRequested  );
_event_("VCF::ToolTipEventHandler", VCF::ToolTipEvent, ToolTip  );

_class_rtti_end_


_class_abstract_rtti_(Document, "VCF::AbstractModel", DOCUMENT_CLASSID)
_class_rtti_end_


_class_abstract_rtti_(Frame, "VCF::Control", FRAME_CLASSID )
_property_( String, "caption", getCaption, setCaption, "" );
_property_( bool, "isTopmost", isFrameTopmost, setFrameTopmost, "" );
_property_( bool, "useColorForBackground", getUseColorForBackground, setUseColorForBackground, "" );
_property_enum_labeled_( FrameStyleType, "frameStyle", getFrameStyle, setFrameStyle,
					   fstSizeable, fstToolbarBorderFixed, 6, FrameStyleTypeNames, "");
_event_("VCF::FrameEventHandler", FrameEvent, FrameClosing)
_event_("VCF::WindowEventHandler", WindowEvent, FrameClose )
_event_("VCF::WindowEventHandler", WindowEvent, FrameActivation )
_class_rtti_end_




_class_abstract_rtti_(Item, "VCF::Object", ITEM_CLASSID)
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemPaint );
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemChanged );
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemAdded );
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemDeleted );
_class_rtti_end_


_class_abstract_rtti_(ListItem, "VCF::Item", LISTITEM_CLASSID)
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, SubItemChanged );
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, SubItemAdded );
_abstract_event_("VCF::ItemEventHandler", VCF::ItemEvent, SubItemDeleted );
_property_( String, "name", getCaption, setCaption, "" )
_class_rtti_end_


/*
_class_abstract_rtti_(ListModel, "VCF::ListModel", "VCF::Model", LISTMODEL_CLASSID)
OBJECT_COLLECTION_PROPERTY(ListItem*, "items", ListModel::getItems, ListModel::addItem, ListModel::insertItem, ListModel::deleteItem, ListModel::deleteItemAtIndex )
_abstract_event_( "VCF::ListModelEventHandler", ListModel, VCF::ListModelEvent, ContentsChanged )
_abstract_event_( "VCF::ListModelEventHandler", ListModel, VCF::ListModelEvent, ItemAdded )
_abstract_event_( "VCF::ListModelEventHandler", ListModel, VCF::ListModelEvent, ItemDeleted )
_class_rtti_end_
*/


_class_abstract_rtti_(MenuItem, "VCF::Item", MENUITEM_CLASSID)
_abstract_event_( "VCF::MenuItemEventHandler", VCF::MenuItemEvent, MenuItemClicked )
_abstract_event_( "VCF::MenuItemEventHandler", VCF::MenuItemEvent, MenuItemUpdate )
_property_( String, "caption", getCaption, setCaption, "" )
_class_rtti_end_




/* 
JC - Note that we should change this to RTTI as an interface!!!
_class_abstract_rtti_(TabModel, "VCF::TabModel", "VCF::Model", TABMODEL_CLASSID )
_abstract_event_("VCF::TabModelEventHandler", TabModel, VCF::TabModelEvent, TabPageAdded)
_abstract_event_("VCF::TabModelEventHandler", TabModel, VCF::TabModelEvent, TabPageRemoved)
_abstract_event_("VCF::TabModelEventHandler", TabModel, VCF::TabModelEvent, TabPageSelected)
_class_rtti_end_(TabModel)
*/


_class_abstract_rtti_(TabPage, "VCF::Item", TABPAGE_CLASSID)
_class_rtti_end_


_class_abstract_rtti_(TableCellItem, "VCF::Item", TABLECELLITEM_CLASSID)
_class_rtti_end_

_class_abstract_rtti_(TableItemEditor, "VCF::Object", TABLEITEMEDITOR_CLASSID)
_event_("VCF::ItemEditorEventHandler", VCF::ItemEditorEvent, CellItemChanged )
_event_("VCF::ItemEditorEventHandler", VCF::ItemEditorEvent, CellItemValidateChange )
_class_rtti_end_


/*
_class_abstract_rtti_(TableModel, "VCF::TableModel", "VCF::AbstractModel", TABLEMODEL_CLASSID )
_event_( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableCellAdded )
_event_( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableCellDeleted )
_event_( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableRowsAdded )
_event_( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableRowsDeleted )
_event_( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableColumnsAdded )
_event_( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableColumnsDeleted )
_class_rtti_end_(TableModel);
*/




_class_abstract_rtti_(ToggledButton, "VCF::CustomControl", TOGGLEDBUTTON_CLASSID)
_property_(bool, "checked", isChecked, setChecked, "");
_property_(String, "caption", getCaption, setCaption, "");
_event_( "VCF::ButtonEventHandler", VCF::ButtonEvent, ButtonClicked )
_class_rtti_end_



_class_abstract_rtti_(TreeItem, "VCF::Item", TREEITEM_CLASSID)
_property_( String, "name", getCaption, setCaption, "" )
_class_rtti_end_


/*
_class_abstract_rtti_(TreeModel, "VCF::TreeModel", "VCF::Model", TREEMODEL_CLASSID)
//	_property_object_( TreeItem, "root", TreeModel::getRoot, TreeModel::setRoot );
_abstract_event_( "VCF::TreeModelEventHandler", TreeModel, VCF::TreeModelEvent, RootNodeChanged )
_abstract_event_( "VCF::TreeModelEventHandler", TreeModel, VCF::TreeModelEvent, NodeAdded )
_abstract_event_( "VCF::TreeModelEventHandler", TreeModel, VCF::TreeModelEvent, NodeDeleted )
_class_rtti_end_
*/


/**
-------------------------------------------------------------------------------
*/

/*
_class_rtti_(AbstractTreeModel, "VCF::AbstractTreeModel", "VCF::TreeModel", ABSTRACTTREEMODEL_CLASSID)
_event_( "VCF::ModelEventHandler", AbstractTreeModel, VCF::ModelEvent, ModelEmptied )
_event_( "VCF::ModelValidationEventHandler", AbstractTreeModel, VCF::ValidationEvent, ModelValidate )
_event_( "VCF::TreeModelEventHandler", AbstractTreeModel, VCF::TreeModelEvent, RootNodeChanged )
_event_( "VCF::TreeModelEventHandler", AbstractTreeModel, VCF::TreeModelEvent, NodeAdded )
_event_( "VCF::TreeModelEventHandler", AbstractTreeModel, VCF::TreeModelEvent, NodeDeleted )
_class_rtti_end_
*/


_class_rtti_(CheckBoxControl, "VCF::ToggledButton", CHECKBOXCONTROL_CLASSID )
_class_rtti_end_


_class_rtti_(ComboBoxControl, "VCF::CustomControl", COMBOBOXCONTROL_CLASSID )
_event_("ItemEventHandler", VCF::ItemEvent, SelectionChanged )
_class_rtti_end_


_class_rtti_(CommandButton, "VCF::Control", COMMANDBUTTON_CLASSID)
_property_( String, "caption", getCaption, setCaption, "" );
_property_enum_labeled_( ButtonCommandType, "commandType", getCommandType, setCommandType,
					   BC_NONE, BC_MAYBE, 6, ButtonCommandTypeNames, "");
_event_( "VCF::ButtonEventHandler", VCF::ButtonEvent, ButtonClicked )
_class_rtti_end_


_class_rtti_(ControlContainer, "VCF::CustomControl", CONTROLCONTAINER_CLASSID)
_property_(double, "bottomBorderHeight", getBottomBorderHeight, setBottomBorderHeight, "");
_property_(double, "topBorderHeight", getTopBorderHeight, setTopBorderHeight, "");
_property_(double, "rightBorderWidth", getRightBorderWidth, setRightBorderWidth, "");
_property_(double, "leftBorderWidth", getLeftBorderWidth, setLeftBorderWidth, "");
_property_(double, "borderSize", getBorderSize, setBorderSize, "");
_class_rtti_end_


_class_rtti_(CustomControl, "VCF::Control", CUSTOMCONTROL_CLASSID )
_property_( bool, "transparent", isTransparent, setTransparent, "" );
_property_( bool, "useColorForBackground", getUseColorForBackground, setUseColorForBackground, "" );
_class_rtti_end_


_class_rtti_(DefaultColumnItem, "VCF::ColumnItem", DEFAULTCOLUMNITEM_CLASSID)
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemPaint );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemChanged );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemAdded );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemDeleted );
_class_rtti_end_

_class_rtti_(DefaultColumnModel, "VCF::ColumnModel", DEFAULTCOLUMNMODEL_CLASSID)
_event_( "VCF::ColumnModelEventHandler",  VCF::ColumnModelEvent, ContentsChanged )
_event_( "VCF::ColumnModelEventHandler",  VCF::ColumnModelEvent, ItemAdded )
_event_( "VCF::ColumnModelEventHandler",  VCF::ColumnModelEvent, ItemDeleted )
_class_rtti_end_

_class_rtti_(DefaultMenuItem, "VCF::MenuItem", DEFAULTMENUITEM_CLASSID)
_event_( "VCF::MenuItemEventHandler", VCF::MenuItemEvent, MenuItemClicked )
_event_( "VCF::MenuItemEventHandler", VCF::MenuItemEvent, MenuItemUpdate )
_class_rtti_end_


_class_rtti_(DefaultListItem, "VCF::ListItem", DEFAULTLISTITEM_CLASSID)
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemPaint );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemChanged );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemAdded );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemDeleted );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, SubItemChanged );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, SubItemAdded );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, SubItemDeleted );
_class_rtti_end_


_class_rtti_(DefaultListModel, "VCF::AbstractModel", DEFAULTLISTMODEL_CLASSID)
_class_rtti_end_


_class_rtti_(DefaultTabModel, "VCF::AbstractModel", DEFAULTTABMODEL_CLASSID )
	_event_("VCF::TabModelEventHandler", VCF::TabModelEvent, TabPageAdded )
	_event_("VCF::TabModelEventHandler", VCF::TabModelEvent, TabPageRemoved )
	_event_("VCF::TabModelEventHandler", VCF::TabModelEvent, TabPageSelected )
	_event_( "VCF::ModelEventHandler", VCF::ModelEvent, ModelEmptied )
	_event_( "VCF::ModelValidationEventHandler", VCF::ValidationEvent, ModelValidate )
_class_rtti_end_


_class_rtti_(DefaultTabPage, "VCF::TabPage", DEFAULTTABPAGE_CLASSID)
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemPaint );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemChanged );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemAdded );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemDeleted );

_class_rtti_end_


_class_rtti_(DefaultTableCellItem, "VCF::TableCellItem", DEFAULTTABLECELLITEM_CLASSID)
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemPaint );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemChanged );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemAdded );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemDeleted );

_class_rtti_end_


_class_rtti_(DefaultTableModel, "VCF::AbstractModel", DEFAULTTABLEMODEL_CLASSID )
	_event_( "VCF::TableModelEventHandler", VCF::TableModelEvent, TableCellAdded )
	_event_( "VCF::TableModelEventHandler", VCF::TableModelEvent, TableCellDeleted )
	_event_( "VCF::TableModelEventHandler", VCF::TableModelEvent, TableRowsAdded )
	_event_( "VCF::TableModelEventHandler", VCF::TableModelEvent, TableRowsDeleted )
	_event_( "VCF::TableModelEventHandler", VCF::TableModelEvent, TableColumnsAdded )
	_event_( "VCF::TableModelEventHandler", VCF::TableModelEvent, TableColumnsDeleted )
_class_rtti_end_


_class_rtti_(DefaultTextModel, "VCF::AbstractModel", DEFAULTTEXTMODEL_CLASSID)
	_event_("VCF::TextModelEventHandler", VCF::TextEvent, TextModelChanged )
_class_rtti_end_


_class_rtti_(DefaultTreeItem, "VCF::TreeItem", DEFAULTTREEITEM_CLASSID)
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemPaint );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemChanged );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemAdded );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemDeleted );
_class_rtti_end_


_class_rtti_(DefaultTreeModel, "VCF::AbstractModel", DEFAULTTREEMODEL_CLASSID)
	_event_( "VCF::TreeModelEventHandler", VCF::TreeModelEvent, RootNodeChanged )
	_event_( "VCF::TreeModelEventHandler", VCF::TreeModelEvent, NodeAdded )
	_event_( "VCF::TreeModelEventHandler", VCF::TreeModelEvent, NodeDeleted )
_class_rtti_end_


_class_rtti_(Dialog, "VCF::Frame", DIALOG_CLASSID )
_class_rtti_end_


_class_rtti_(HeaderControl, "VCF::CustomControl", HEADERCONTROL_CLASSID)
	_property_object_( ColumnModel, "columnModel", getColumnModel, setColumnModel, "" );
	_event_("VCF::MouseEventHandler", VCF::MouseEvent, ColumnItemClicked );
	_event_("VCF::ItemEventHandler", VCF::ItemEvent, ColumnWidthChanged );
_class_rtti_end_



_class_rtti_(ImageControl, "VCF::CustomControl", IMAGECONTROL_CLASSID)
_property_object_( Image, "image", getImage, setImage, "" );
_property_(bool, "transparent", getTransparent, setTransparent, "");
//this is a typedef property registration, which allows a normal type, like a string, to 
//become defined with a different type name.
_property_typedef_( String, "filename", getFilename, setFilename, "VCF::ImageFilenameString", "" );
_class_rtti_end_



_class_rtti_(Label, "VCF::CustomControl", LABEL_CLASSID )
_property_( String, "caption", getCaption, setCaption, "" );
_property_enum_labeled_( TextAlignmentType, "textAlignment", getTextAlignment, setTextAlignment,
					   taTextLeft, taTextRight, 3, TextAlignmentTypeNames, "");
_property_enum_labeled_( TextVerticalAlignment, "verticalAlignment", getVerticalAlignment, setVerticalAlignment,
					   tvaTextTop, tvaTextBottom, 3, TextVerticalAlignmentNames, "");

_property_object_( Control, "focusControl", getFocusControl, setFocusControl, "" );

_property_( bool, "wordWrap", getWordWrap, setWordWrap, "" );

_class_rtti_end_



_class_rtti_(ListBoxControl, "VCF::CustomControl", LISTBOXCONTROL_CLASSID )
_property_( double, "defaultItemHeight", getDefaultItemHeight, setDefaultItemHeight, "" );
_property_( bool, "allowsMultiSelect", getAllowsMultiSelect, setAllowsMultiSelect, "" );
_property_object_( ListModel, "listModel", getListModel, setListModel, "" );
_class_rtti_end_



_class_rtti_(ListViewControl, "VCF::Control", LISTVIEWCONTROL_CLASSID )
_property_enum_labeled_( IconStyleType, "iconStyle", getIconStyle, setIconStyle,
					   isLargeIcon, isDetails, 4, IconStyleTypeNames, "");
_property_enum_labeled_( IconAlignType, "iconAlignment", getIconAlignment, setIconAlignment,
					   iaNone, iaAutoArrange, 4, IconAlignTypeNames, "");
_property_object_( ListModel, "listModel", getListModel, setListModel, "" );
_property_object_ro_( ColumnModel, "columnModel", getColumnModel, "" );

_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelectionChanged );
_event_("VCF::MouseEventHandler", VCF::MouseEvent, ColumnItemClicked );

_class_rtti_end_


_class_rtti_(Menu, "VCF::Component", MENU_CLASSID )
_property_object_( MenuItem, "rootMenuItem", getRootMenuItem, setRootMenuItem, "" );
_class_rtti_end_




_class_rtti_(MenuBar, "VCF::Menu", MENUBAR_CLASSID )
_class_rtti_end_


_class_rtti_( MessageDialog, "VCF::Dialog", MESSAGEDIALOG_CLASSID )
_class_rtti_end_


_class_rtti_(MultilineTextControl, "VCF::TextControl", MULTILINETEXTCONTROL_CLASSID)
_class_rtti_end_

/*
_class_rtti_(OpenGLControl, "VCF::OpenGLControl", "VCF::CustomControl", OPENGLCONTROL_CLASSID )
_class_rtti_end_(OpenGLControl)
*/

_class_rtti_(Panel, "VCF::ControlContainer", PANEL_CLASSID )
_class_rtti_end_


_class_rtti_(PopupMenu, "VCF::Menu", POPUPMENU_CLASSID )
_class_rtti_end_


_class_rtti_(PushButton, "VCF::Object", PUSHBUTTON_CLASSID)
_class_rtti_end_


_class_rtti_(RadioButtonControl, "VCF::ToggledButton", RADIOBUTTONCONTROL_CLASSID )
_property_( long, "groupID", getGroupID, setGroupID, "" );
_class_rtti_end_



_class_rtti_(ScrollbarManager, "VCF::Component", SCROLLBARMANAGER_CLASSID)
_property_object_( Control, "target", getTarget, setTarget, "" );
_property_( double, "virtualViewHeight", getVirtualViewHeight, setVirtualViewHeight, "" );
_property_( double, "virtualViewWidth", getVirtualViewWidth, setVirtualViewWidth, "" );
_property_( double, "verticalPosition", getVerticalPosition, setVerticalPosition, "" );
_property_( double, "horizontalPosition", getHorizontalPosition, setHorizontalPosition, "" );
_property_( double, "verticalTopScrollSpace", getVerticalTopScrollSpace, setVerticalTopScrollSpace, "" );
_property_( double, "verticalBottomScrollSpace", getVerticalBottomScrollSpace, setVerticalBottomScrollSpace, "" );
_property_( double, "horizontalLeftScrollSpace", getHorizontalLeftScrollSpace, setHorizontalLeftScrollSpace, "" );
_property_( double, "horizontalRightScrollSpace", getHorizontalRightScrollSpace, setHorizontalRightScrollSpace, "" );
_property_( bool, "hasVerticalScrollbar", hasVerticalScrollBar, setHasVerticalScrollbar, "" );
_property_( bool, "hasHorizontalScrollbar", hasHorizontalScrollBar, setHasHorizontalScrollbar, "" );
_class_rtti_end_



_class_rtti_(Splitter, "VCF::CustomControl", SPLITTER_CLASSID)
//_property_(bool,"updateAttachedControl",Splitter::getUpdateAttachedControl, Splitter::setUpdateAttachedControl,"")
_class_rtti_end_


_class_rtti_(StatusBar, "VCF::ControlContainer", STATUSBAR_CLASSID)
_class_rtti_end_


_class_rtti_(TabbedPages, "VCF::CustomControl", TABBEDPAGES_CLASSID );
_class_rtti_end_



_class_rtti_(TableControl, "VCF::CustomControl", TABLECONTROL_CLASSID );
_class_rtti_end_



_class_rtti_(TextControl, "VCF::Control", TEXTCONTROL_CLASSID )
_class_rtti_end_


_class_rtti_(TimerComponent, "VCF::Component", TIMERCOMPONENT_CLASSID)
_property_( bool, "active",isActive, setActivated, "" );
_property_( long, "timeoutInterval", getTimeoutInterval, setTimeoutInterval, "" );
_event_("VCF::TimerEventHandler", VCF::TimerEvent, TimerActivated );
_event_("VCF::TimerEventHandler", VCF::TimerEvent, TimerDeactivated );
_event_("VCF::TimerEventHandler", VCF::TimerEvent, TimerPulse );
_class_rtti_end_


_class_rtti_(Toolbar, "VCF::Control", TOOLBAR_CLASSID);
_class_rtti_end_



_class_rtti_(ToolbarDock, "VCF::CustomControl", TOOLBARDOCK_CLASSID);
_property_enum_labeled_( ToolbarDockSide, "dockSide", getDockSide, setDockSide,
					   tdsTop, tdsBottom, 4, ToolbarDockSideNames, "");

_property_enum_labeled_( ToolbarBackgroundStyle, "backgroundStyle", getBackgroundStyle, setBackgroundStyle,
					   tbksNone, tbksStretch, 3, ToolbarBackgroundStyleNames, "");

_property_object_( Image, "background", getBackground, setBackground, "" );

_property_( bool, "usingBackground", isUsingBackground, setUsingBackground, "" );
_property_( bool, "allowsDragging", allowsDragging, setAllowsDragging, "" );

_class_rtti_end_



_class_rtti_(TreeControl, "VCF::Control", TREECONTROL_CLASSID )
_property_object_( TreeModel, "treeModel", getTreeModel, setTreeModel, "" );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemExpanded );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemStateChangeRequested );
_class_rtti_end_



_class_rtti_(TreeListControl, "VCF::CustomControl", TREELISTCONTROL_CLASSID )
_property_object_( TreeModel, "treeModel", getTreeModel, setTreeModel, "" );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemSelected );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemExpanded );
_event_("VCF::ItemEventHandler", VCF::ItemEvent, ItemStateChangeRequested );
_class_rtti_end_

/*
_class_rtti_(UIApplication, "UIApplication", "Application", UIAPPLICATION_CLASSID)
_class_rtti_end_(UIApplication)
*/


_class_rtti_(Window, "VCF::Frame", WINDOW_CLASSID )
_property_object_( MenuBar, "menuBar", getMenuBar, setMenuBar, "" );
_event_("VCF::WindowEventHandler", VCF::WindowEvent, WindowRestore )
_event_("VCF::WindowEventHandler", VCF::WindowEvent, WindowMaximize )
_event_("VCF::WindowEventHandler", VCF::WindowEvent, WindowMinimize )
_class_rtti_end_



_class_rtti_(ProgressControl, "VCF::CustomControl", PROGRESSCONTROL_CLASSID )
_property_( double, "minValue", getMinValue, setMinValue, "" );
_property_( double, "maxValue", getMaxValue, setMaxValue, "" );
_property_( double, "position", getPosition, setPosition, "" );
_property_( bool, "displayProgressText", getDisplayProgressText, setDisplayProgressText, "" );
_property_( bool, "useProgressFormatString", getUseProgressFormatString, setUseProgressFormatString, "" );
_property_( double, "stepItIncrement", getStepItIncrement, setStepItIncrement, "" );
_property_object_( Color, "progressBarColor", getProgressBarColor, setProgressBarColor, "" );
_property_object_( Color, "progressTextColor", getProgressTextColor, setProgressTextColor, "" );
_property_enum_labeled_( ProgressControl::ProgressAlignment, "displayAlignment", getDisplayAlignment, setDisplayAlignment,
					   ProgressControl::paVertical, ProgressControl::paHorizontal, 
					   2, ProgressAlignmentNames, "");

_class_rtti_end_


_class_rtti_(SliderControl, "VCF::CustomControl", SLIDERCONTROL_CLASSID )
_property_enum_labeled_( SliderControl::DisplayOrientation, "displayOrientation", getDisplayOrientation, setDisplayOrientation,
					   SliderControl::doHorizontal, SliderControl::doVertical, 2, ProgressAlignmentNames, "");
_property_( double, "minValue", getMinValue, setMinValue, "" );
_property_( double, "maxValue", getMaxValue, setMaxValue, "" );
_property_( double, "position", getPosition, setPosition, "" );
_property_( bool, "tickMarks", hasTickMarks, setHasTickMarks, "" );
_property_( long, "tickFrequency", getTickFrequency, setTickFrequency, "" );
_property_( double, "stepIncrement", getStepIncrement, setStepIncrement, "" );
_property_( double, "stepIncrement", getPageIncrement, setPageIncrement, "" );
_class_rtti_end_


_class_rtti_(SystemTray, "VCF::Component", SYSTEMTRAY_CLASSID )
	_event_("VCF::GenericEventHandler", VCF::Event, TrayIconChanged )
	_property_object_( PopupMenu, "popupMenu", getPopupMenu, setPopupMenu, "" );
	_property_( String, "tooltipText", getTooltipText, setTooltipText, "" );
_class_rtti_end_



//property editors!



#define ABSTRACTPROPERTYEDITOR_CLASSID	"e7bfe231-713e-4d32-b32f-fb8eecb4cf84"

_class_abstract_rtti_(AbstractPropertyEditor, "VCF::ObjectWithEvents", ABSTRACTPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define IMAGEPROPERTYEDITOR_CLASSID "c1ab05f9-ee5c-4e1d-a535-94a8f475fc81"

_class_rtti_(ImagePropertyEditor, "VCF::AbstractPropertyEditor", IMAGEPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define IMAGEFILENAMEPROPERTYEDITOR_CLASSID "4a519d27-c486-4501-8591-552f56609c00"

_class_rtti_(ImageFilenamePropertyEditor, "VCF::AbstractPropertyEditor", IMAGEFILENAMEPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define INTEGERPROPERTYEDITOR_CLASSID "4ab9c999-16e2-45b0-b586-0ff1c2dc6c6f"

_class_rtti_(IntegerPropertyEditor, "VCF::AbstractPropertyEditor", INTEGERPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define DOUBLEPROPERTYEDITOR_CLASSID "7f34bc88-c020-48fb-80a0-20d6d512fbfc"

_class_rtti_(DoublePropertyEditor, "VCF::AbstractPropertyEditor", DOUBLEPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define STRINGPROPERTYEDITOR_CLASSID "7039e0b6-17fd-4317-8749-d662822744ea"

_class_rtti_(StringPropertyEditor, "VCF::AbstractPropertyEditor", STRINGPROPERTYEDITOR_CLASSID)
_class_rtti_end_



#define BOOLPROPERTYEDITOR_CLASSID "cd440a0d-9f08-4c48-8185-b8cb2c6f7ef9"

_class_rtti_(BoolPropertyEditor, "VCF::AbstractPropertyEditor", BOOLPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define ENUMPROPERTYEDITOR_CLASSID "2221d216-6c19-4e7f-82a0-07c6b018ead6"

_class_rtti_(EnumPropertyEditor, "VCF::AbstractPropertyEditor", ENUMPROPERTYEDITOR_CLASSID)
_class_rtti_end_



#define ENUMSETPROPERTYEDITOR_CLASSID "7503b6d1-fe95-4167-9430-41e2d583bbdb"

_class_rtti_(EnumSetPropertyEditor, "VCF::AbstractPropertyEditor", ENUMSETPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define CURSORPROPERTYEDITOR_CLASSID "145181bc-70d6-47cb-9dc4-163540e82cf3"

_class_rtti_(CursorPropertyEditor, "VCF::AbstractPropertyEditor", CURSORPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define COLORPROPERTYEDITOR_CLASSID "5f7c1d05-78da-4e6b-b22b-fc290e5207e4"

_class_rtti_(ColorPropertyEditor, "VCF::AbstractPropertyEditor", COLORPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define FONTPROPERTYEDITOR_CLASSID "192e8624-94c6-46fb-8092-16ee2cb6fb27"

_class_rtti_(FontPropertyEditor, "VCF::AbstractPropertyEditor", FONTPROPERTYEDITOR_CLASSID)
_class_rtti_end_



#define DEFAULTMENUITEMPROPERTYEDITOR_CLASSID "b4cf4ef4-f135-4a23-8237-486144e5ba06"

_class_rtti_(DefaultMenuItemPropertyEditor, "VCF::AbstractPropertyEditor", DEFAULTMENUITEMPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define DEFAULTLISTMODELPROPERTYEDITOR_CLASSID "9f39a5a5-9910-4ae2-a6b3-c6ff38682283"

_class_rtti_(DefaultListModelPropertyEditor, "VCF::AbstractPropertyEditor", DEFAULTLISTMODELPROPERTYEDITOR_CLASSID)
_class_rtti_end_




};


/**
$Id$
*/
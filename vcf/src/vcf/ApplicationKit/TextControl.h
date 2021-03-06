#ifndef _VCF_TEXTCONTROL_H__
#define _VCF_TEXTCONTROL_H__
//TextControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TEXTMODEL_H__
#	include "vcf/ApplicationKit/TextModel.h"
#endif // _VCF_TEXTMODEL_H__



namespace VCF {


class TextEditPeer;
class Dictionary;
class InputValidator;


enum TextValidationStyle {	
	tvsOnKeyEvent,
	tvsOnFocusChange,
	tvsOnEnterKey

};



static String TextValidationStyleNames[] = { "tvsOnKeyEvent",
                                         "tvsOnFocusChange",
										 "tvsOnEnterKey" };


#define TEXTCONTROL_CLASSID			"ED88C09E-26AB-11d4-B539-00C04F0196DA"
/**
\class TextControl TextControl.h "vcf/ApplicationKit/TextControl.h"
The base class for presenting text to the user. The text can be 
plain text, or styled text, i.e. text with multiple styles.

The TextControl is only for editing or presenting a single line of text.
For editing multiple lines of text, please see the MultilineTextControl.

All text controls contain a TextModel, that stores the actual text 
data.
@see MultilineTextControl
@see TextModel
*/
class APPLICATIONKIT_API TextControl : public Control {
public:

	enum TextInputState {
		tisWaitingForInput = 0,
		tisProcessing = 0x01,
		tisInputValidated = 0x02,
		tisInputValidationFailed = 0x04,
	};

	DELEGATE(TextModelDelegate,SelectionChanged);

	TextControl( const bool& multiLineControl=false );
	virtual ~TextControl();

	void init();

	virtual void updateView( Model* updatedModel );


	virtual void paint( GraphicsContext * context );

	void setTextModel( TextModel * model );

	TextModel* getTextModel();


	virtual void modelChanged( Model* oldModel, Model* newModel );


	String getText();

	void setText( const String& val );

	uint32 getCaretPosition() ;

	void setCaretPosition( const uint32& caretPos );

	void setRightMargin( const double & rightMargin );

	void setLeftMargin( const double & leftMargin );

	uint32 getLineCount();

	uint32 getCurrentLinePosition();

	double getLeftMargin();

	double getRightMargin();

	Point* getPositionFromCharIndex( const uint32& index );

	uint32 getCharIndexFromPosition( Point* point );

	/**
	*returns the zero based index that indicates where the current selection begins.
	*It may be the same index that getCaretPosition() returns
	*/
	uint32 getSelectionStart();

	/**
	gives the number of characters selected.
	@return uint32, the number of characters selected, a return value
	of 0 indicates that no characters are currently selected.
	*/
	uint32 getSelectionCount();

	void setSelectionMark( const uint32& start, const uint32& count );

	void selectAll();

	void getStyle( unsigned int start, unsigned int length, Dictionary& styles );

	void setStyle( unsigned int start, unsigned int length, Dictionary& styles );

	void setDefaultStyle( Dictionary& styles );

	String getSelectedText();

	void replaceSelectedText( const String& text );
	
	virtual double getPreferredHeight();

	virtual void handleEvent( Event* event );

	bool isReadOnly() {
		return readOnly_;
	}

	void setReadOnly( const bool& val );

	virtual bool supportsMultiLinedText() {
		return false;
	}

	/**
	Call this function to disable the standard, built-in,
	accelerator's that make sure the platforms standard 
	shortcut's for cut, copy, paste, undo, and redo get
	handled by the underlying platform. You may choose
	to turn these off if your use of a text control
	provides more advanced cut/copy/paste/undo/redo support.
	If you're using the DocView arcichtecture you'll
	almost certainly want to turn them off.
	*/
	void disableStandardAccelerators();

	/**
	Call this function to enable the standard, built-in,
	accelerator's that make sure the platforms standard 
	shortcut's for cut, copy, paste, undo, and redo get
	handled by the underlying platform.
	By default these are enabled for every text control.
	*/
	void enableStandardAccelerators();

	/**
	Cuts the selection and places it in the clipboard.
	This uses the standard cut implementation provided by the
	underlying windowing platform. 
	*/
	void cut();

	/**
	Copies the selection and places it in the clipboard.
	This uses the standard copy implementation provided by the
	underlying windowing platform. 
	*/
	void copy();

	/**
	Pastes the contents of the clipboard into the text control.
	This uses the standard paste implementation provided by the
	underlying windowing platform. 
	*/
	void paste();

	/**
	Returns a bool to indicate whether or not an undo operation can be
	performed. 
	@return bool true if an an undo operation can be performed. This 
	indicates that a call to undo() will succeed. Returns false to 
	indicate no undo is possible and any calls to undo() will
	be no-ops.
	*/
	bool canUndo();

	/**
	Returns a bool to indicate whether or not a redo operation can be
	performed. 
	@return bool true if an a redo operation can be performed. This 
	indicates that a call to redo() will succeed. Returns false to 
	indicate no redo is possible and any calls to redo() will
	be no-ops.
	*/
	bool canRedo();

	/**
	Undoes the last operation.
	This uses the standard undo implementation provided by the
	underlying windowing platform. 
	*/
	void undo();

	/**
	Redoes the last operation.
	This uses the standard redo implementation provided by the
	underlying windowing platform. 
	*/
	void redo();

	/**
	This toggles word wrapping. If you turn off word wrapping
	the scroll bars will show up autmatically (if they are needed).
	If you turn on word wrapping the scroll bars will disapear.
	*/
	void setTextWrapping( const bool& val );

	bool getTextWrapping();

	virtual bool generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue );

	TextValidationStyle getValidationStyle() {
		return validationStyle_;
	}

	void setValidationStyle( const TextValidationStyle& val ) {
		validationStyle_ = val;
	}

	bool isWaitingForInput() {
		return inputState_ == tisWaitingForInput ? true : false;
	}

	bool isProcessingInput() {
		return inputState_ & tisProcessing ? true : false;
	}

	bool didInputValidate() {
		return inputState_ & tisInputValidated ? true : false;
	}

	bool didInputValidationFail() {
		return inputState_ & tisInputValidationFailed ? true : false;
	}

	InputValidator* getInputValidator() {
		return inputValidator_;
	}

	void setInputValidator( InputValidator* val );

	void internal_processKeyDown( KeyboardEvent* ke );
	void internal_processKeyPress( KeyboardEvent* ke );
protected:
	/**
	handlers of some standard accelerator events.
	*/
	void undoAccelerator( Event* e );
	void redoAccelerator( Event* e );
	void cutAccelerator( Event* e );
	void copyAccelerator( Event* e );
	void pasteAccelerator( Event* e );
	void selectAllAccelerator( Event* e );

	/**
	handler called when the control is getting the focus.
	By default it is added only to a single line control,
	so we can select all the text whenever we get the focus.
	*/
	virtual void gotFocus( FocusEvent* event );

	void onModelValidationFailed( Event* e );
	void onModelValidated( Event* e );



	TextEditPeer * textPeer_;
	bool readOnly_;
	TextValidationStyle validationStyle_;
	int inputState_;
	InputValidator* inputValidator_;
};

}; // namespace VCF


#endif // _VCF_TEXTCONTROL_H__

/**
$Id$
*/

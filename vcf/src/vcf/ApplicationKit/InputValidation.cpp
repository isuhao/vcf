//InputValidation.cpp
/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/TextModel.h"
#include "vcf/ApplicationKit/TextPeer.h"
#include "vcf/ApplicationKit/InputValidation.h"

using namespace VCF;


InputValidator::InputValidator():
	Component(),
	inputControl_(NULL),
	flags_(0)
{

}


void InputValidator::handleEvent( Event* e )
{
	Component::handleEvent(e);
	if ( isDesigning() ) {
		return;
	}


	switch ( e->getType() ) {
		case Control::KEYBOARD_DOWN : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;

		case Control::KEYBOARD_PRESSED : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;

		case Control::KEYBOARD_UP : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;
	}
}


void InputValidator::setInputControl( TextControl* val )
{
	if ( val != inputControl_ ) {
		inputControl_ = val;
		if ( NULL != inputControl_ ) {
			inputControl_->setInputValidator( this );
		}
	}
}

void InputValidator::setFlags( const uint32& flags )
{
	if ( flags != flags_ ) {
		flags_ = flags;
		resetText();
	}	
}

bool InputValidator::modifyFlags( uint32 flagToAdd, uint32 flagToRemove )
{
	uint32 tmpFlags = (flags_ & ~flagToRemove) | flagToAdd;

	if (flags_ == tmpFlags)
		return false;

	flags_ = tmpFlags;
	resetText();
	return true;
}

void InputValidator::resetText()
{
	if ( !isDesigning() && NULL != inputControl_ ) {
		String s = getValidText();
		if ( s != inputControl_->getText() ) {
			inputControl_->setText( s );
		}
	}
}

void InputValidator::setAndReplaceSelection( uint32 start, uint32 count, const String& val, int incrementStart, bool forcePeer )
{
	inputControl_->setSelectionMark( start, maxVal<uint32>(count,1) );
	inputControl_->replaceSelectedText( val );

	if ( forcePeer ) {
		inputControl_->getPeer()->setText( inputControl_->getText() );
	}

	if ( incrementStart > 0 ) {
		inputControl_->setSelectionMark( start+incrementStart, 0 );
	}
}

void InputValidator::setAndReplaceSelection( uint32 start, uint32 count, const VCFChar& val, int incrementStart, bool forcePeer )
{
	setAndReplaceSelection( start, count, String(1,val), incrementStart, forcePeer );
}

AlphaNumericValidator::AlphaNumericValidator():
	maxChars_(0),
	invalidChars_("%'*\"+?><:\\")
{
	addCallback( new ClassProcedure1<Event*,AlphaNumericValidator>(this, &AlphaNumericValidator::changeMaxCharacters), "AlphaNumericValidator::changeMaxCharacters" );
	addCallback( new ClassProcedure1<Event*,AlphaNumericValidator>(this, &AlphaNumericValidator::changeInvalidCharacters), "AlphaNumericValidator::changeInvalidCharacters" );
}


String AlphaNumericValidator::getValidText()
{
	String result;

	if ( NULL != inputControl_ ) {
		result = inputControl_->getText();
		if ( !result.empty() ) {
			result = result.substr( 0, minVal(maxChars_ , result.size()) );

			// Remove any invalid characters from the control's text

			for (int pos = result.size() - 1; pos >= 0; pos--)
			{
				if ( invalidChars_.find(result[pos]) != String::npos ) {
					result = result.substr(0, pos) + result.substr(pos + 1,result.size()-(pos + 1));
				}
			}
		}
	}

	return result;
}

void AlphaNumericValidator::changeMaxCharacters( Event* e)
{
	Model* model = dynamic_cast<Model*>(e->getSource());

	if ( model ) {
		String s = model->getValueAsString();
		if ( !s.empty() ) {
			setMaxCharacters( StringUtils::fromStringAsUInt(s) );
		}
	}
}

void AlphaNumericValidator::changeInvalidCharacters( Event* e)
{
	Model* model = dynamic_cast<Model*>(e->getSource());

	if ( model ) {
		String s = model->getValueAsString();
		this->setInvalidCharacters( s );
	}
}

void AlphaNumericValidator::handleEvent( Event* e )
{
	InputValidator::handleEvent(e);
	if ( isDesigning() ) {
		return;
	}


	switch ( e->getType() ) {
		case Control::KEYBOARD_DOWN : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;

		case Control::KEYBOARD_PRESSED : {
			KeyboardEvent* ke = (KeyboardEvent*)e;

			if ( this->inputControl_->isReadOnly() ) {
				return;
			}

			if ( !invalidChars_.empty() ) {
				// Check if the character is invalid
				if (invalidChars_.find( ke->keyValue ) != String::npos ) {
					InvalidInputEvent e(this);					
					e.invalidChar = ke->keyValue;

					InvalidInput(&e);

					ke->ignoreKeystroke = true;

					return;
				}
			}


			String text = inputControl_->getText();
			if ( text.length() == maxChars_ && maxChars_ && iswprint(ke->keyValue)) {
				
				size_t start = inputControl_->getSelectionStart();
				
				if ( start < maxChars_ && allowCharacter(ke->keyValue) ) {
					inputControl_->setSelectionMark( start, 1 );
					inputControl_->replaceSelectedText( String( 1, ke->keyValue) );
					inputControl_->setSelectionMark( start+1, 0 );
				}

				ke->ignoreKeystroke = true;
				return;
			}

			if ( !this->allowCharacter( ke->keyValue ) ) {
				ke->ignoreKeystroke = true;
			}
		}
		break;

		case Control::KEYBOARD_UP : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;
	}
}

void AlphaNumericValidator::setInvalidCharacters( const String& val )
{
	if ( val != invalidChars_ ) {
		invalidChars_ = val;
		this->resetText();
	}
}

void AlphaNumericValidator::setMaxCharacters( const size_t& val )
{
	if ( val != maxChars_ ) {
		maxChars_ = val;
		this->resetText();
	}
}


int vcf_iswdigit( VCFChar c )
{
	return ::iswdigit(c);
}

int vcf_iswprint( VCFChar c )
{
	return ::iswprint(c);
}

MaskedValidator::MaskedValidator()
{
	symbols_.push_back(Symbol('#', vcf_iswdigit));
	
	addCallback( new ClassProcedure1<Event*,MaskedValidator>(this, &MaskedValidator::changeMask), "MaskedValidator::changeMask" );
}

void MaskedValidator::changeMask( Event* e )
{
	Model* model = dynamic_cast<Model*>(e->getSource());

	if ( model ) {
		String s = model->getValueAsString();
		
		setMask( s );		
	}
}

String MaskedValidator::getValidText()
{
	String result;

	String text = inputControl_->getText();
	size_t maskLen = mask_.length();
	
	// If the mask is empty, allow anything
	if (!maskLen)
		return text;
	
	// Accomodate the text to the mask as much as possible
	size_t maskPos = 0;
	size_t len = text.length();


	for (size_t pos = 0; pos < len; pos++, maskPos++) {
		VCFChar c = text[pos];
		VCFChar cMask = static_cast<VCFChar>(maskPos < maskLen ? mask_[maskPos] : 0);

		// If we've reached the end of the mask, break
		if (!cMask)
			break;

		// Match the character to any of the symbols
		int iSymbol = 0; 
		size_t nSymbolCount = symbols_.size();
		for (; iSymbol < nSymbolCount; iSymbol++)
		{
			const Symbol& symbol = symbols_[iSymbol];

			// Find the symbol that applies for the given character
			if (cMask != symbol || !symbol.validate(c))
				continue;

			// Try to add matching characters in the mask until a different symbol is reached
			for (; maskPos < maskLen; maskPos++)
			{
				cMask = mask_[maskPos];
				if (cMask == symbol)
				{
					result += symbol.convert(c);
					break;
				} 
				else
				{
					int iSymbol2 = 0;
					for (; iSymbol2 < nSymbolCount; iSymbol2++)
					{
						if (cMask == symbols_[iSymbol2])
						{
							result += symbol.convert(c);
							break;
						}
					}

					if (iSymbol2 < nSymbolCount)
						break;

					result += cMask;
				}
			}

			break;
		}

		// If the character was not matched to a symbol, stop
		if (iSymbol == nSymbolCount)
		{
			if (c == cMask)
			{
				// Match the character to any of the symbols
				for (iSymbol = 0; iSymbol < nSymbolCount; iSymbol++)
				{
					if (cMask == symbols_[iSymbol])
						break;
				}

				if (iSymbol == nSymbolCount)
				{
					result += c;
					continue;
				}
			}

			break;
		}
	}

	return result;
}

void MaskedValidator::handleEvent( Event* e )
{
	InputValidator::handleEvent(e);
	if ( isDesigning() ) {
		return;
	}


	switch ( e->getType() ) {
		case Control::KEYBOARD_DOWN : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
			switch ( ke->virtualKeyCode )	{
				case vkDelete : {
					// If deleting make sure it's the last character or that
					// the selection goes all the way to the end of the text

					size_t nStart = inputControl_->getSelectionStart();
					size_t nEnd = nStart + inputControl_->getSelectionCount();					

					String text = inputControl_->getText();
					size_t nLen = text.length();

					if (nEnd != nLen) {
						if (!(nEnd == nStart && nEnd == nLen - 1)) {
							ke->ignoreKeystroke = true;
							return;
						}
					}
					break;
				}
			}

		}
		break;

		case Control::KEYBOARD_PRESSED : {
			KeyboardEvent* ke = (KeyboardEvent*)e;

			ke->ignoreKeystroke = true;

			// Check to see if it's read only
			if ( inputControl_->isReadOnly() ) {				
				return;
			}

			

			// If the mask is empty, allow anything
			int nMaskLen = mask_.length();
			if (!nMaskLen) {
				if ( allowCharacter(ke->keyValue) ) {
					ke->ignoreKeystroke = false;
				}
				return;
			}

			// Check that we haven't gone past the mask's length
			int nStart = 0;
			int nEnd = 0;
			nStart = inputControl_->getSelectionStart();
			nEnd = nStart + inputControl_->getSelectionCount();


			if (nStart >= nMaskLen && ke->virtualKeyCode != vkBackSpace) {				
				return;
			}

			String text = inputControl_->getText();
			int nLen = text.length();

			// Check for a non-printable character (such as Ctrl+C)
			if (!vcf_iswprint(ke->keyValue)) {
				if (ke->virtualKeyCode == vkBackSpace && nStart != nLen) {
					ke->ignoreKeystroke = true;
					//inputControl_->SendMessage(WM_KEYDOWN, VK_LEFT); // move the cursor left					
					return;
				}
				
				// Allow backspace only if the cursor is all the way to the right
				if (!allowCharacter(ke->keyValue)) {
					ke->ignoreKeystroke = true;
				}
				return;				
			}

			VCFChar cMask = mask_[nStart];

			// Check if the mask's character matches with any of the symbols in the array.
			int iSymbol = 0;
			int nSymbolCount = symbols_.size();
			for (; iSymbol < nSymbolCount; iSymbol++)
			{
				const Symbol& symbol = symbols_[iSymbol];
				if (cMask == symbol) {
					if (symbol.validate(ke->keyValue) && allowCharacter( ke->keyValue ) ) {
						nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
						
						inputControl_->setSelectionMark( nStart, maxVal(nEnd-nStart,1) );
						inputControl_->replaceSelectedText( String(1,symbol.convert(ke->keyValue)) );
						inputControl_->getPeer()->setText( inputControl_->getText() );
						inputControl_->setSelectionMark( nStart+1, 0 );
					}

					ke->ignoreKeystroke = true;
					return;
				}
			}

			// Check if it's the same character as the mask.
			if ( cMask == ke->keyValue && allowCharacter(ke->keyValue) ) 	{
				nEnd = (nEnd == nLen ? nEnd : (nStart + 1));

				inputControl_->setSelectionMark( nStart, nEnd-nStart );
				inputControl_->replaceSelectedText( String(1,ke->keyValue) );
				inputControl_->getPeer()->setText( inputControl_->getText() );
				inputControl_->setSelectionMark( nStart+1, 0 );

				ke->ignoreKeystroke = true;

				return;
			}

			// Concatenate all the mask symbols
			String strSymbols;
			for (iSymbol = 0; iSymbol < nSymbolCount; iSymbol++) {
				strSymbols += symbols_[iSymbol];
			}

			// If it's a valid character, find the next symbol on the mask and add any non-mask characters in between.
			for (iSymbol = 0; iSymbol < nSymbolCount; iSymbol++) {
				const Symbol& symbol = symbols_[iSymbol];

				// See if the character is valid for any other symbols
				if ( !symbol.validate(ke->keyValue) ) {
					continue;
				}

				// Find the position of the next symbol 
				String maskPortion = mask_.substr(nStart,mask_.size()-nStart);
				size_t nMaskPos = maskPortion.find_first_of(strSymbols);
					
				// Enter the character if there isn't another symbol before it
				if ( nMaskPos != String::npos && maskPortion[nMaskPos] == symbol && allowCharacter(ke->keyValue) ) {
					inputControl_->setSelectionMark( nStart, (nStart + nMaskPos)-nStart );
					inputControl_->replaceSelectedText( maskPortion.substr(0,nMaskPos) );
					inputControl_->getPeer()->setText( inputControl_->getText() );

					inputControl_->setSelectionMark( nStart+1, 0 );
					
					handleEvent( ke );
					return;
				}
			}


		}
		break;

		case Control::KEYBOARD_UP : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;		
	}
}

void MaskedValidator::setMask( const String& val )
{
	if ( val != this->mask_ ) {
		mask_ = val;
		resetText();
	}
}

String MaskedValidator::getNumericText()
{
	String result;

	String tmp = this->inputControl_->getText();

	

	size_t length = tmp.length();

	for (size_t pos = 0;pos < length; pos++) {
		
		VCFChar c = tmp[pos];

		if (vcf_iswdigit(c)) {
			result += c;
		}
	}


	return result;
}



NumericValidator::NumericValidator():
	InputValidator(),
	maxWholeDigits_(9),
	maxDecimalPlaces_(4),
	negativeSign_(L"-"),
	decimalPoint_(L"."),
	groupSeparator_(L","),
	digitsInGroup_(0),	
	min_(VCF_MIN_NUMBER),
	max_(VCF_MAX_NUMBER),
	adjustingSeparators_(false)
{
	Locale* locale = System::getCurrentThreadLocale();	
	negativeSign_ = locale->getCurrencyNegativeSign();
	decimalPoint_ = locale->getNumberDecimalPoint();
	groupSeparator_ = locale->getNumberThousandsSeparator();
	
	addCallback( new ClassProcedure1<Event*,NumericValidator>(this, &NumericValidator::changeMask), "NumericValidator::changeMask" );
	addCallback( new ClassProcedure1<Event*,NumericValidator>(this, &NumericValidator::changeAllowNegative), "NumericValidator::changeAllowNegative" );
	addCallback( new ClassProcedure1<Event*,NumericValidator>(this, &NumericValidator::changeMaxWholeDigits), "NumericValidator::changeMaxWholeDigits" );
	addCallback( new ClassProcedure1<Event*,NumericValidator>(this, &NumericValidator::changeMaxDecimalPlaces), "NumericValidator::changeMaxDecimalPlaces" );
}

void NumericValidator::changeMask( Event* e )
{
	Model* model = dynamic_cast<Model*>(e->getSource());

	if ( model ) {
		String s = model->getValueAsString();
		
		setMask( s );		
	}
}

void NumericValidator::changeAllowNegative( Event* e )
{
	Model* model = dynamic_cast<Model*>(e->getSource());

	if ( model ) {
		VariantData v = model->getValue();
		
		this->setAllowNegative( v );
	}
}

void NumericValidator::changeMaxWholeDigits( Event* e )
{
	Model* model = dynamic_cast<Model*>(e->getSource());

	if ( model ) {
		VariantData v = model->getValue();
		
		this->setMaxWholeDigits( v );
	}
}

void NumericValidator::changeMaxDecimalPlaces( Event* e )
{
	Model* model = dynamic_cast<Model*>(e->getSource());

	if ( model ) {
		String s = model->getValueAsString();
		if ( !s.empty() ) {
			setMaxDecimalPlaces( StringUtils::fromStringAsUInt(s) );
		}
	}
}

String NumericValidator::getValidText()
{
	String result;
	String text = inputControl_->getText();	
	bool isNegative = false;

	// Remove any invalid characters from the number
	int iPos = 0;
	int nDecimalPos = -1;
	int nNewLen = 0;
	int nLen = text.length();
	for (; iPos < nLen; iPos++)
	{
		String c(1,text[iPos]);

		// Check for a negative sign
		if (c == negativeSign_ && isNegativeAllowed()) {
			isNegative = true;
		}

		// Check for a digit
		else if ( ::vcf_iswdigit(c[0]) ) {
			// Make sure it doesn't go beyond the limits
			if (nDecimalPos < 0 && nNewLen == maxWholeDigits_) {
				continue;
			}

			if (nDecimalPos >= 0 && nNewLen > nDecimalPos + maxDecimalPlaces_) {
				break;
			}

			result += c;
			nNewLen++;
		}
		// Check for a decimal point
		else if (c == decimalPoint_ && nDecimalPos < 0)
		{
			if (maxDecimalPlaces_ == 0)
				break;

			result += c;
			nDecimalPos = nNewLen;
			nNewLen++;
		}
	}
	
	// Check if we need to pad the number with zeros after the decimal point
	if (maxDecimalPlaces_ > 0 && nNewLen > 0 &&
		((flags_ & nvfPadWithZerosAfterDecimalWhenTextChanges) ||
		(!adjustingSeparators_ && (flags_ & nvfPadWithZerosAfterDecimalWhenTextIsSet)))) {

		if (nDecimalPos < 0) 	{
			if (nNewLen == 0 || result == L"-")	{
				result = L"0";
				nNewLen = 1;
			}
			result += decimalPoint_;
			nDecimalPos = nNewLen++;
		}

		NumericValidator::insertZeros(result, -1, maxDecimalPlaces_ - (nNewLen - nDecimalPos - 1));
	}

	// Insert the negative sign if it's there
	if (isNegative) {
		result = result.insert(0, negativeSign_);
	}

	return getSeparatedText(result);
}

void NumericValidator::handleEvent( Event* e )
{
	InputValidator::handleEvent(e);
	if ( isDesigning() ) {
		return;
	}


	switch ( e->getType() ) {
		case Control::KEYBOARD_DOWN : {
			needsAdjusting_ = false;
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;

		case Control::KEYBOARD_PRESSED : {			

			KeyboardEvent* ke = (KeyboardEvent*)e;
			// Check to see if it's read only
			if (inputControl_->isReadOnly()) {
				return;
			}
			
			ke->ignoreKeystroke = true;

			String keyValStr(1,ke->keyValue);

			size_t nStart = inputControl_->getSelectionStart();
			size_t nEnd = nStart + inputControl_->getSelectionCount();

			String text = inputControl_->getText();
			String numericText = getNumericText(text);
			size_t nDecimalPos = text.find(decimalPoint_);
			size_t nNumericDecimalPos = numericText.find(decimalPoint_);
			size_t nLen = text.length();
			size_t nNumericLen = numericText.length();
			size_t nPrefixLen = prefix_.length();
			int nSepCount = getGroupSeparatorCount(text);
			bool needAdjustment = false;

			// Check if we're in the prefix's location
			if ( nStart < nPrefixLen && ::vcf_iswprint( ke->keyValue ) ) {
				VCFChar cPrefix = prefix_[nStart];

				// Check if it's the same character as the prefix.
				if (cPrefix == ke->keyValue && allowCharacter(ke->keyValue)) {
					if (nLen > nStart) {
						nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
						setAndReplaceSelection( nStart, nEnd-nStart, ke->keyValue );

						//inputControl_->SetSel(nStart, nEnd);
						//inputControl_->ReplaceSel(String(ke->keyValue), TRUE);						
					}
					else {
						ke->ignoreKeystroke = false;
					}
				}
				// If it's a part of the number, enter the prefix
				else if (( ::vcf_iswdigit(ke->keyValue) || keyValStr == negativeSign_ || keyValStr == decimalPoint_) && allowCharacter(ke->keyValue)) {
					nEnd = (nEnd == nLen ? nEnd : (nPrefixLen));
					//inputControl_->SetSel(nStart, nEnd);
				//	inputControl_->ReplaceSel(prefix_.Mid(nStart), TRUE);
					setAndReplaceSelection( nStart, nEnd-nStart, prefix_.substr(nStart,prefix_.size()-nStart), 1, true );


					handleEvent(ke);
					//NumericBehavior::_OnChar(uChar, nRepCnt, nFlags);
				}
				
				return;
			}

			// Check if it's a negative sign
			if (keyValStr == negativeSign_ && isNegativeAllowed()) {
				// If it's at the beginning, determine if it should overwritten
				if (nStart == nPrefixLen)
				{
					if (!numericText.empty() && numericText[0] == negativeSign_[0] && allowCharacter(ke->keyValue)) {
						nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
						//inputControl_->SetSel(nStart, nEnd);
						//inputControl_->ReplaceSel(String(negativeSign_), TRUE);
						setAndReplaceSelection( nStart, nEnd-nStart, negativeSign_ );
						return;
					}
				}
				// If we're not at the beginning, toggle the sign
				else if (allowCharacter(ke->keyValue))
				{
					if (numericText[0] == negativeSign_[0]) {
						//inputControl_->SetSel(nPrefixLen, nPrefixLen + 1);
						//inputControl_->ReplaceSel(_T(""), TRUE);
						//inputControl_->SetSel(nStart - 1, nEnd - 1);

						setAndReplaceSelection( nPrefixLen, 1, L"", 0 );
						inputControl_->setSelectionMark( nStart - 1, (nEnd - 1) - (nStart - 1) );
					}
					else {
						setAndReplaceSelection( nPrefixLen, 0, negativeSign_, 0 );
						inputControl_->setSelectionMark( nStart + 1, (nEnd + 1) - (nStart + 1) );

						//inputControl_->SetSel(nPrefixLen, nPrefixLen);
						//inputControl_->ReplaceSel(String(negativeSign_), TRUE);
						//inputControl_->SetSel(nStart + 1, nEnd + 1);
					}

					return;
				}
			}

			// Check if it's a decimal point (only one is allowed).
			else if (keyValStr == decimalPoint_ && maxDecimalPlaces_ > 0) {
				if (nDecimalPos != String::npos) {
					// Check if we're replacing the decimal point
					if (nDecimalPos >= nStart && nDecimalPos < nEnd) {
						needAdjustment = true;
					}
					else {	// Otherwise, put the caret on it
						if (allowCharacter(ke->keyValue)) {
//							inputControl_->SetSel(nDecimalPos + 1, nDecimalPos + 1);
							inputControl_->setSelectionMark( nDecimalPos + 1, 0 );
						}						
						return;
					}
				}
				else {
					needAdjustment = true;
				}
			}

			// Check if it's a digit
			else if ( vcf_iswdigit(ke->keyValue) ) {
				// Check if we're on the right of the decimal point.
				if (nDecimalPos != String::npos && nDecimalPos < nStart) {
					if ( numericText.substr(nNumericDecimalPos + 1,numericText.length()-(nNumericDecimalPos + 1)).length() 
							== maxDecimalPlaces_ ) {

						if (nStart <= nDecimalPos + maxDecimalPlaces_ && allowCharacter(ke->keyValue)) {
							nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
							//inputControl_->SetSel(nStart, nEnd);
							//inputControl_->ReplaceSel(String(ke->keyValue), TRUE);
							setAndReplaceSelection( nStart, nEnd-nStart, ke->keyValue );
						}

						return;
					}
				}

				// We're on the left side of the decimal point
				else  {
					bool isNegative = (!numericText.empty() && String(1,numericText[0]) == negativeSign_);

					// Make sure we can still enter digits.
					if (nStart == maxWholeDigits_ + isNegative + nSepCount + nPrefixLen) {
						if (flags_ & nvfAddDecimalAfterMaxWholeDigits && maxDecimalPlaces_ > 0) {
							nEnd = (nEnd == nLen ? nEnd : (nStart + 2));
							//inputControl_->SetSel(nStart, nEnd);
							//inputControl_->ReplaceSel(String(decimalPoint_) + ke->keyValue, TRUE);
							String s = decimalPoint_;
							s+= ke->keyValue;
							setAndReplaceSelection( nStart, nEnd-nStart, s );
						}
						return;
					}

					if ( numericText.substr(0, nNumericDecimalPos != String::npos ? nNumericDecimalPos : nNumericLen).length() == maxWholeDigits_ + isNegative ) {
						if ( allowCharacter(ke->keyValue) ) {
							if (text[nStart] == groupSeparator_[0]) {
								nStart++;
							}

							nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
							//inputControl_->SetSel(nStart, nEnd);
							//inputControl_->ReplaceSel(String(ke->keyValue), TRUE);
							setAndReplaceSelection( nStart, nEnd-nStart, ke->keyValue );
						}
						return;
					}

					needAdjustment = true;
				}
			}

			// Check if it's a non-printable character, such as Backspace or Ctrl+C
			else if ( !vcf_iswprint(ke->keyValue) ) {
				needAdjustment = true;
			}
			else {
				return;
			}

			// Check if the character should be entered
			if (!allowCharacter(ke->keyValue)) {
				ke->ignoreKeystroke = true;
				return;
			}
			
			ke->ignoreKeystroke = false;
			inputControl_->internal_processKeyPress( ke );
			ke->dontProcessKeystroke = true;

			needsAdjusting_ = false;
			//Behavior::_OnChar(uChar, nRepCnt, nFlags);

			// If the decimal point was added/removed or a separator needs adding/removing, adjust the text
			if ( needAdjustment ) {
				needsAdjusting_ = true;
				adjustSeparators(nSepCount);
			}

		}
		break;

		case Control::FOCUS_LOST : {
			
			// Check if the value is empty and we don't want to touch it
			String originalText = getNumericText(inputControl_->getText());
			String text = originalText;
			size_t nLen = text.length();

			// If desired, remove any extra leading zeros but always leave one in front of the decimal point
			if (flags_ & nvfOnKillFocus_RemoveExtraLeadingZeros && nLen > 0) {
				bool bIsNegative = (String(1,text[0]) == negativeSign_);
				if (bIsNegative) {
					text = text.erase(0,1);
				}

				text = StringUtils::trimLeft( text, '0' );

				if ( text.empty() || String(1,text[0]) == decimalPoint_ ) {
					text = text.insert(0, "0");
				}

				if (bIsNegative) {
					text = text.insert(0, negativeSign_);
				}
			}
			else if (!(flags_ & nvfOnKillFocus_Max) || (nLen == 0 && flags_ & nvfOnKillFocus_DontPadWithZerosIfEmpty)) {
				return;
			}

			size_t nDecimalPos = text.find(decimalPoint_);

			// Check if we need to pad the number with zeros after the decimal point
			if (flags_ & nvfOnKillFocus_PadWithZerosAfterDecimal && maxDecimalPlaces_ > 0) {
				if (nDecimalPos == String::npos) {
					if (nLen == 0 || text == "-") {
						text = "0";
						nLen = 1;
					}
					text += decimalPoint_;
					nDecimalPos = nLen++;
				}

				NumericValidator::insertZeros(text, -1, maxDecimalPlaces_ - (nLen - nDecimalPos - 1));
			}

			// Check if we need to pad the number with zeros before the decimal point
			if (flags_ & nvfOnKillFocus_PadWithZerosBeforeDecimal && maxWholeDigits_ > 0)
			{
				if (nDecimalPos == String::npos) {
					nDecimalPos = nLen;
				}

				if (nLen && text[0] == '-') {
					nDecimalPos--;
				}

				NumericValidator::insertZeros(text, (nLen ? text[0] == '-' : -1), maxWholeDigits_ - nDecimalPos);
			}

			if (text != originalText) {
				//SelectionSaver selection = m_pEdit;	// remember the current selection 
				uint32 selStart = this->inputControl_->getSelectionStart();
				uint32 selCount = this->inputControl_->getSelectionCount();
				
				inputControl_->setText( text );

				inputControl_->setSelectionMark( selStart, selCount );
			}

		}
		break;
	}
}

void NumericValidator::setDoubleAndTrim( const double& val, bool bTrimTrailingZeros ) 
{
	inputControl_->setText( getDoubleText(val, bTrimTrailingZeros) );
}

void NumericValidator::setDouble( const double& val)
{
	setDoubleAndTrim(val,false);
}

double NumericValidator::getDouble()
{
	Locale* locale = System::getCurrentThreadLocale();

	double result = 0.0;
	
	if ( NULL != inputControl_ ) {
		result = locale->toDouble( this->getNumericText( inputControl_->getText() ) );
	}

	return result;
}

void NumericValidator::setInt( const int& val )
{
	Locale* locale = System::getCurrentThreadLocale();
	
	inputControl_->setText( locale->toString(val) );
}

int NumericValidator::getInt()
{
	Locale* locale = System::getCurrentThreadLocale();
	if ( NULL != inputControl_ ) {
		return locale->toInt( this->getNumericText( inputControl_->getText() ) );
	}
	return 0;
}

void NumericValidator::setMaxWholeDigits( const int& val )
{
	VCF_ASSERT(val != 0);

	int tmp = val;
	// If nMaxWholeDigits is negative, don't allow negatives
	bool allowNegative = (tmp >= 0);
	if (tmp < 0)
		tmp = -tmp;
		
	if (maxWholeDigits_ == tmp && isNegativeAllowed() == allowNegative)
		return;

	maxWholeDigits_ = tmp;
	if (!modifyFlags(allowNegative ? 0 : nvfCannotBeNegative, allowNegative ? nvfCannotBeNegative : 0))
		this->resetText();
}


void NumericValidator::setMaxDecimalPlaces( const size_t& val )
{
	VCF_ASSERT(val >= 0);
	if (maxDecimalPlaces_ == val)
		return;

	maxDecimalPlaces_ = val;
	resetText();
}

void NumericValidator::setAllowNegative( const bool& val )
{
	modifyFlags(val ? 0 : nvfCannotBeNegative, val ? nvfCannotBeNegative : 0);
}

bool NumericValidator::isNegativeAllowed()
{
	return !(flags_ & nvfCannotBeNegative);
}

void NumericValidator::setDigitsInGroup( const size_t& val )
{
	VCF_ASSERT(val >= 0);
	if (digitsInGroup_ == val)
		return;

	digitsInGroup_ = val;
	resetText();
}


void NumericValidator::setSeparators( const String& decimalChar, const String& groupChar )
{
	VCF_ASSERT(!decimalChar.empty());
	VCF_ASSERT(!groupChar.empty());

	// If nothing's changing, leave
	if (decimalPoint_ == decimalChar && groupSeparator_ == groupChar)
		return;

	// Set them
	decimalPoint_ = decimalChar;
	groupSeparator_ = groupChar;

	// Ensure they're not the same
	if (decimalPoint_ == groupSeparator_) {
		groupSeparator_ = (decimalPoint_ == L"," ? L"." : L",");
	}

	resetText();
}

void NumericValidator::getSeparators( String& decimalChar, String& groupChar )
{
	decimalChar = decimalPoint_;
	groupChar = groupSeparator_;
}

void NumericValidator::setDecimalSeparator( const String& val )
{
	if ( decimalPoint_ == val ) {
		return;
	}

	decimalPoint_ = val;

	// Ensure they're not the same
	if (decimalPoint_ == groupSeparator_) {
		groupSeparator_ = (decimalPoint_ == L"," ? L"." : L",");
	}

	resetText();
}

void NumericValidator::setGroupSeparator( const String& val )
{
	if ( groupSeparator_ == val ) {
		return;
	}

	groupSeparator_ = val;

	// Ensure they're not the same
	if (decimalPoint_ == groupSeparator_) {
		groupSeparator_ = (decimalPoint_ == L"," ? L"." : L",");
	}

	resetText();
}

void NumericValidator::setPrefix(const String& val )
{
	if (prefix_ == val)
		return;

	prefix_ = val;
	resetText();
}	


void NumericValidator::setMask(const String& mask)
{
	int nDecimalPos = -1;
	int nLen = mask.length();

	maxWholeDigits_ = 0;
	maxDecimalPlaces_ = 0;
	digitsInGroup_ = 0;
	flags_ = (flags_ & ~nvfCannotBeNegative);  // allow it to be negative
	prefix_ = L"";

	for (int iPos = nLen - 1; iPos >= 0; iPos--) {
		VCFChar c = mask[iPos];
		String s(1,c);

		if (c == '#') {
			if (nDecimalPos >= 0) {
				maxWholeDigits_++;
			}
			else {
				maxDecimalPlaces_++;
			}
		}
		else if ((c == '.' || s == decimalPoint_) && nDecimalPos < 0) {
			nDecimalPos = iPos;
			decimalPoint_ = s;
		}
		else if (c == ',' || s == groupSeparator_) {
			if (!digitsInGroup_) {
				digitsInGroup_ = (((nDecimalPos >= 0) ? nDecimalPos : nLen) - iPos) - 1;
				groupSeparator_ = s;
			}
		}
		else
		{
			prefix_ = mask.substr(0, iPos + 1);
			break;
		}
	}

	if (nDecimalPos < 0) {
		maxWholeDigits_ = maxDecimalPlaces_;
		maxDecimalPlaces_ = 0;
	}

	VCF_ASSERT(maxWholeDigits_ > 0);	// must have at least one digit on left side of decimal point
	resetText();
}

String NumericValidator::getSeparatedText(const String& text)
{
	String numericText = getNumericText(text);
	String result = numericText;
	
	// Retrieve the number without the decimal point
	size_t nDecimalPos = numericText.find(decimalPoint_);
	if (nDecimalPos != String::npos) {
		result = result.substr(0,nDecimalPos);
	}

	if (digitsInGroup_ > 0) {
		size_t nLen = result.length();
		int isNegative = (!result.empty() && String(1,result[0]) == negativeSign_);

		// Loop in reverse and stick the separator every m_nDigitsInGroup digits.
		for (int iPos = nLen - (digitsInGroup_ + 1); iPos >= isNegative; iPos -= digitsInGroup_) {
			result = result.substr(0,iPos + 1) + groupSeparator_ + result.substr(iPos + 1, result.length()-(iPos+1));
		}
	}

	// Prepend the prefix, if the number is not empty.
	if (!result.empty() || (nDecimalPos != String::npos))
	{
		result = prefix_ + result;

		if (nDecimalPos != String::npos) {
			result += numericText.substr(nDecimalPos,numericText.length()-nDecimalPos);
		}
	}

	return result;
}

int NumericValidator::getGroupSeparatorCount(const String& text)
{
	int result = 0;

	size_t iPos = 0;
	size_t nLen = text.length();
	for (; iPos < nLen; iPos++)	{
		if ( String(1,text[iPos]) == groupSeparator_ ) {
			result++;
		}
	}

	return result;
}

String NumericValidator::getNumericText(const String& text, bool useMathSymbols )
{
	String result;
	bool isNegative = false;
	bool hasDecimalPoint = false;

	for (int iPos = 0, nLen = text.length(); iPos < nLen; iPos++)
	{
		String c(1,text[iPos]);

		if ( ::vcf_iswdigit(c[0]) ) {
			result += c;
		}
		else if ( c == negativeSign_ ) {
			isNegative = true;
		}
		else if (c == decimalPoint_ && !hasDecimalPoint) {
			hasDecimalPoint = true;
			result += (useMathSymbols ? L"." : decimalPoint_);
		}
	}

	// Add the negative sign to the front of the number
	if (isNegative) {
		result = result.insert(0, useMathSymbols ? L"-" : negativeSign_);
	}


	return result;
}

String NumericValidator::getDoubleText(double val, bool bTrimTrailingZeros )
{
	Locale* locale = System::getCurrentThreadLocale();
	
	String result = locale->toString(val);

	//if (decimalPoint_ != L".") {
	//	result.Replace('.', decimalPoint_);
	//}

	if (bTrimTrailingZeros) {
		result = StringUtils::trimRight(result,'0');
		result = StringUtils::trimRight(result,decimalPoint_[0]);
	}

	return result;
}

void NumericValidator::adjustSeparators(int currentSeparatorCount)
{
	uint32 selStart = this->inputControl_->getSelectionStart();
	uint32 selCount = this->inputControl_->getSelectionCount();

	adjustingSeparators_ = true;

	String text = getValidText();

	if ( text != inputControl_->getText() ) {
		inputControl_->setText( text );
		inputControl_->getPeer()->setText( text );
	}

	// Adjust the current selection if separators were added/removed
	int nNewSeparatorCount = getGroupSeparatorCount(text);
	if ( currentSeparatorCount != nNewSeparatorCount && selStart > prefix_.length() ) {
		selStart += (nNewSeparatorCount - currentSeparatorCount);
	}

	adjustingSeparators_ = false;


	inputControl_->setSelectionMark( selStart, selCount );
}

void NumericValidator::insertZeros(String& text, int pos, int count)
{
	if (pos < 0 && count > 0) {
		pos = text.length();
	}

	for (int zero = 0; zero < count; zero++) {
		text = text.insert(pos, "0");
	}
}

void NumericValidator::showErrorMessage()
{

}

void NumericValidator::adjustWithinRange()
{
		// Check if it's already within the range
	if (isValid()) {
		return;
	}

	// If it's empty, set it a valid number
	if ( inputControl_->getText().empty() ) {
		inputControl_->setText(L" ");
	}
	else {
		resetText();
	}

	// Make it fall within the range
	double value = getDouble();
    if ( value < min_ ) { 
		setDouble(min_);
	}
    else if ( value > max_ ) {
		setDouble(max_);
	}
}


String NumericValidator::getMask()
{
	String result;

	size_t iDigit = 0;
	for (; iDigit < maxWholeDigits_; iDigit++)
		result += "0";

	if (maxDecimalPlaces_) {
		result += decimalPoint_;
	}

	for (iDigit = 0; iDigit < maxDecimalPlaces_; iDigit++)
		result += '0';

	result = getSeparatedText(result);

	for (size_t iPos = 0, nLen = result.length(); iPos < nLen; iPos++) 	{
		if (result[iPos] == '0') {
#ifdef USE_STRINGPOOL
			result = result.set(iPos,'#');
#else
			result[iPos] = '#';
#endif
		}
	}	

	return result;
}

void NumericValidator::setRange( double minNum, double maxNum )
{
	VCF_ASSERT(minNum <= maxNum);

	min_ = minNum;
	max_ = maxNum;

	resetText();
}

void NumericValidator::getRange( double& minNum, double& maxNum)
{
	minNum = min_;
	maxNum = max_;
}

void NumericValidator::setMax( const double& val )
{
	if ( max_ != val ) {

		VCF_ASSERT(min_ <= val);

		max_ = val;

		resetText();
	}
}


void NumericValidator::setMin( const double& val )
{
	if ( min_ != val ) {

		VCF_ASSERT(val <= max_);

		min_ = val;

		resetText();
	}
}


bool NumericValidator::isValid()
{
	double value = getDouble();
	return (value >= min_ && value <= max_);
}	

bool NumericValidator::checkIfValid( bool showErrorIfNotValid )
{
	if ( !this->inputControl_->isEnabled() ) {
		return true;
	}

	bool result = isValid();

	if (!result && showErrorIfNotValid) {
		showErrorMessage();
		inputControl_->setFocused();
	}
	
	return result;
}


CurrencyValidator::CurrencyValidator():
	NumericValidator()
{
	digitsInGroup_ = 3;
	maxDecimalPlaces_ = 2;
	prefix_ = L"$";
	flags_ |= nvfPadWithZerosAfterDecimalWhenTextIsSet | 
				nvfOnKillFocus_RemoveExtraLeadingZeros | 
				nvfOnKillFocus_PadWithZerosAfterDecimal | 
				nvfOnKillFocus_DontPadWithZerosIfEmpty;

	Locale* locale = System::getCurrentThreadLocale();
	prefix_ = locale->getCurrencySymbol();
	maxDecimalPlaces_ = locale->getCurrencyFractionalDigits();
	groupSeparator_ = locale->getCurrencyThousandsSeparator();
	decimalPoint_ = locale->getCurrencyDecimalPoint();

	//String s = locale->getC
	//digitsInGroup_
}

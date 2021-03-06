//Win32Button.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Button.h"
#include "vcf/ApplicationKit/CommandButton.h"

using namespace VCF;


Win32Button::Win32Button( CommandButton* component ):
	AbstractWin32Component( component ),
	commandButton_(component)
{

}

Win32Button::~Win32Button()
{

}

void Win32Button::create( Control* owningControl )
{
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className = getClassName();

	CreateParams params = createParams();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
		                             L"BUTTON",
									 windowCaption_.c_str(),
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( params.second,
		                             "BUTTON",
									 windowCaption_.ansi_c_str(),
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandleA(NULL),
									 NULL );
	}



	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );
		subclassWindow();
		registerForFontChanges();
	}
	else {
		//throw exception
	}

	setCreated( true );
}

Win32Object::CreateParams Win32Button::createParams()
{
	Win32Object::CreateParams result;
	result.first = WS_VISIBLE | WS_CHILD | BS_OWNERDRAW;
	result.second = 0;

	return result;
}

Image* Win32Button::getImage()
{
	return NULL;
}


void Win32Button::setImage( Image* image )
{

}

ButtonState Win32Button::getState()
{
	return state_;
}


bool Win32Button::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;

	switch ( message ) {
		
		case WM_PAINT:{
			//check to see if the font needs updating
		}
		break;

		case WM_ERASEBKGND:{
			wndProcResult = TRUE;
			result = true;
		}
		break;

		case WM_DRAWITEM:{
			DRAWITEMSTRUCT* drawItem = (DRAWITEMSTRUCT*)lParam;

			state_.setFocused( (drawItem->itemState & ODS_FOCUS) || peerControl_->isFocused() );
			state_.setEnabled( !(drawItem->itemState & ODS_DISABLED) );
			state_.setPressed( drawItem->itemState & ODS_SELECTED );

			CommandButton* button = (CommandButton*)peerControl_;
			button->setIsPressed( drawItem->itemState & ODS_SELECTED ? true : false );

			
			if ( peerControl_->isDoubleBuffered() ){

				Rect tmp(drawItem->rcItem.left, drawItem->rcItem.top, drawItem->rcItem.right, drawItem->rcItem.bottom);

				this->prepForDoubleBufferPaint( drawItem->hDC, tmp );

				int dcState = ::SaveDC( drawItem->hDC );
				
				HDC memDC = (HDC)memCtx_->getPeer()->getContextID();

				//clear the memdc
				Control* parent = peerControl_->getParent();
				Color* bkColor = parent->getColor();
				HBRUSH bkBr = CreateSolidBrush( RGB( bkColor->getRed()*255.0, bkColor->getGreen()*255.0, bkColor->getBlue()*255.0 ) );
				FillRect( memDC, &drawItem->rcItem, bkBr );
				DeleteObject( bkBr );


				//::SetViewportOrgEx( memDC, -drawItem->rcItem.left, -drawItem->rcItem.top, NULL );

				memCtx_->setOrigin( -drawItem->rcItem.left, -drawItem->rcItem.top );


				
				//ctx->getPeer()->setContextID( (OSHandleID)memDC_ );

				//((ControlGraphicsContext*)ctx)->setOwningControl( NULL );

				peerControl_->internal_beforePaint( memCtx_ );

				peerControl_->paint( memCtx_ );

				peerControl_->internal_afterPaint( memCtx_ );


				//((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );

				memCtx_->setOrigin( -drawItem->rcItem.left, -drawItem->rcItem.top );

				//::SetViewportOrgEx( memDC, -drawItem->rcItem.left, -drawItem->rcItem.top, NULL );

				int err = ::BitBlt( drawItem->hDC, drawItem->rcItem.left, drawItem->rcItem.top,
									drawItem->rcItem.right - drawItem->rcItem.left,
									drawItem->rcItem.bottom - drawItem->rcItem.top,
									 memDC, drawItem->rcItem.left, drawItem->rcItem.top, SRCCOPY );

				
				::RestoreDC ( drawItem->hDC, dcState );

				if ( err == FALSE ) {
					err = GetLastError();
					StringUtils::trace( Format("error in BitBlt during drawing of double buffered Comp: error code=%d\n") %
						err );
				}
			}
			else {
				ControlGraphicsContext ctrlCtx(peerControl_);
				
				ctrlCtx.getPeer()->setContextID( (OSHandleID)drawItem->hDC );

				peerControl_->internal_beforePaint( &ctrlCtx );

				peerControl_->paint( &ctrlCtx );

				peerControl_->internal_afterPaint( &ctrlCtx );
			}
			wndProcResult = TRUE;
			result = true;
		}
		break;

		case WM_NCCALCSIZE: {
			wndProcResult = handleNCCalcSize( wParam, lParam );
			result = true;
		}
		break;

		case WM_NCPAINT: {	

			wndProcResult = handleNCPaint( wParam, lParam );
			return true;
		}
		break;

		case BN_CLICKED :{

			if ( peerControl_->isDesigning() ) {
				wndProcResult = 0;
				result = true;
			}
			else {
				commandButton_->click();
			}
		}
		break;
		

		case WM_COMMAND: {			
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );			
		}

		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

		}
	}
	return result;
}


/**
$Id$
*/

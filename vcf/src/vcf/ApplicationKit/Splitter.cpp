//Splitter.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Splitter.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Splitter.h"


using namespace VCF;


Splitter::Splitter( const AlignmentType& alignment/*=AlignLeft*/ ):
	CustomControl(true)
{
	init();
	setAlignment( alignment );
}

void Splitter::init()
{
	attachedControl_ = NULL;
	//setCursorID( (int32)Cursor::SCT_SPLIT_VERT );
	//setAlignment( AlignLeft );
	dragPoint_.x_ = 0.0;
	dragPoint_.y_ = 0.0;
	attachedControlAlt_ = NULL;
	outmostControl_ = NULL;
	deltaRestore_ = 0.0;
	deltaRestoreAlt_ = 0.0;
	minimumWidth_ = 5.0;
	dblClickEnabled_ = true;

	setWidth( getPreferredWidth() );
	setHeight( getPreferredHeight() );
	setAllowsFocus( false );
	setTabStop( false );
}

Splitter::~Splitter()
{

}

void Splitter::setAlignment( const AlignmentType& alignment )
{
	Control::setAlignment( alignment );
	if ( AlignTop == alignment || AlignBottom == alignment ) {
		this->setCursorID( (int32)Cursor::SCT_SPLIT_HORZ );
	} else {
		this->setCursorID( (int32)Cursor::SCT_SPLIT_VERT );
	}
}

void Splitter::setMinimumWidth( const double& _minimumWidth )
{
	// if 0 then resizeChidrenUsingBounds would make the control disapperar
	minimumWidth_ = VCF::maxVal<double>( 0.5, _minimumWidth );
}

double Splitter::getMinimumWidth()
{
	return minimumWidth_;
}

void Splitter::mouseDown( MouseEvent* e )
{
 	Container* container = getParent()->getContainer();
	if ( NULL == container ) {
		return;
	}

	Enumerator<Control*>* children = NULL;
	Control* child = NULL;

	CustomControl::mouseDown( e );
	keepMouseEvents();
	dragPoint_ = *(e->getPoint());
	Point tmp = dragPoint_;
	switch ( this->getAlignment() ) {
		case AlignLeft : {
			tmp.x_ = this->getLeft() - 1.0;
		}
		break;

		case AlignTop : {
			tmp.y_ = this->getTop() - 1.0;
		}
		break;

		case AlignRight : {
			tmp.x_ = this->getLeft() + this->getWidth() + 1.0;
		}
		break;

		case AlignBottom : {
			tmp.y_ = this->getTop() + this->getHeight() + 1.0;
		}
		break;
	}


	this->attachedControl_ = NULL;
	children = container->getChildren();
	while ( children->hasMoreElements() ) {
		child = children->nextElement();
		if ( true == (child->getBounds().containsPt( &tmp )) ) {
			this->attachedControl_ = child;
			//StringUtils::traceWithArgs( "attachedControl_.toolTip_: \"%s\"\r\n", child->getToolTipText().c_str() );
			break;
		}
	}

	//if ( e->hasShiftKey() )
	//{
		tmp = dragPoint_;
		switch ( this->getAlignment() ) {
			case AlignLeft : {
				tmp.x_ = this->getLeft() + this->getWidth() + 1.0;
			}
			break;

			case AlignTop : {
				tmp.y_ = this->getTop() + this->getHeight() + 1.0;
			}
			break;

			case AlignRight : {
				tmp.x_ = this->getLeft() - 1.0;
			}
			break;

			case AlignBottom : {
				tmp.y_ = this->getTop() - 1.0;
			}
			break;
		}
		this->attachedControlAlt_ = NULL;
		children = container->getChildren();
		while ( children->hasMoreElements() ) {
			child = children->nextElement();
			if ( true == (child->getBounds().containsPt( &tmp )) ) {
				this->attachedControlAlt_ = child;
				//StringUtils::traceWithArgs( "attachedControlAlt_.toolTip_: \"%s\"\r\n", child->getToolTipText().c_str() );
				break;
			}
		}
	//}
}

void Splitter::mouseMove( MouseEvent* e )
{
	CustomControl::mouseMove( e );
	if ( e->hasLeftButton() ) {
		updateAttachedControl( *e->getPoint(), e->hasShiftKey() );
	}
}

void Splitter::mouseUp( MouseEvent* e )
{
	//StringUtils::trace( "mouseUp\r\n" );

	CustomControl::mouseUp( e );
	this->releaseMouseEvents();

	updateAttachedControl( *e->getPoint(), e->hasShiftKey() );
}

void Splitter::mouseDblClick( MouseEvent* e )
{
	if ( !dblClickEnabled_ ) {
		return;
	}

	//StringUtils::trace( "mouseDblClick\r\n" );

	CustomControl::mouseDblClick( e );
	if ( e->hasLeftButton() ) {
		updateAttachedControlJump( *e->getPoint(), e->hasShiftKey() );
	}
}

void Splitter::updateAttachedControl( Point& pt, const bool& shiftAll/*=false*/ )
{
	Rect parentBounds = getParent()->getBounds();

	double parentWidth = parentBounds.getWidth()-1;
	double parentHeight = parentBounds.getHeight()-1;

 	Container* container = getParent()->getContainer();
	if ( NULL == container ) {
		return;
	}

	Control* controlLast = (dynamic_cast<StandardContainer*>(container))->getControlInAlignmentList( this->getAlignment(), false );
	if ( NULL == controlLast ) {
		return;
	}

	bool shouldResize = true;
	double delta, deltaAlt, width, widthMax, newWidth, widthAlt, newWidthAlt;

	switch ( this->getAlignment() ) {
		case AlignLeft : {
			delta = pt.x_ - dragPoint_.x_;
			if ( 0 < delta && controlLast->getWidth() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getWidth() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				Rect attachedCtrlBounds = attachedControl_->getBounds();
				width = attachedCtrlBounds.getWidth();
				widthMax = parentWidth - attachedCtrlBounds.getLeft() - minimumWidth_ - this->getWidth();
				newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
						widthAlt = attachedCtrlAltBounds.getWidth();
						widthMax = attachedCtrlAltBounds.getRight() - minimumWidth_ - this->getWidth();
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							Rect boundsAlt = attachedCtrlAltBounds;
							boundsAlt.setLeft( attachedCtrlAltBounds.getLeft() - deltaAlt );
							boundsAlt.setWidth( newWidthAlt );
							//StringUtils::trace( Format( "Splitter:ctrlAlt : [false] %s\n" ) % attachedControlAlt_->getToolTipText() );
							attachedControlAlt_->setBounds( &boundsAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newWidthAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						Rect bounds = attachedControl_->getBounds();
						bounds.setWidth( newWidth );
						//StringUtils::trace( Format( "Splitter: ctrl : [false] %s\n" ) % attachedControlAlt_->getToolTipText() );
						attachedControl_->setBounds( &bounds );
						//StringUtils::traceWithArgs( "updateAttachedControl newWidth: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

		case AlignTop : {
			delta = pt.y_ - dragPoint_.y_;
			if ( 0 < delta && controlLast->getHeight() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getHeight() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				Rect attachedCtrlBounds = attachedControl_->getBounds();
				width = attachedCtrlBounds.getHeight();
				widthMax = parentHeight - attachedCtrlBounds.getTop() - minimumWidth_ - this->getHeight();
				newWidth = VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
						widthAlt = attachedCtrlAltBounds.getHeight();
						widthMax = attachedCtrlAltBounds.getBottom() - minimumWidth_ - this->getHeight();
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							Rect boundsAlt = attachedCtrlAltBounds;
							boundsAlt.setTop( attachedCtrlAltBounds.getTop() - deltaAlt );
							boundsAlt.setHeight( newWidthAlt );
							attachedControlAlt_->setBounds( &boundsAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newHeightAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						Rect bounds = attachedControl_->getBounds();
						bounds.setHeight( newWidth );
						attachedControl_->setBounds( &bounds );
						//StringUtils::traceWithArgs( "updateAttachedControl newHeight: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

		case AlignRight : {
			//delta_ = dragPoint_.x_ - pt.x_;
			delta = -(pt.x_ - dragPoint_.x_);
			if ( 0 < delta && controlLast->getWidth() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getWidth() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				Rect attachedCtrlBounds = attachedControl_->getBounds();
				width = attachedCtrlBounds.getWidth();
				widthMax = attachedCtrlBounds.getRight() - minimumWidth_ - this->getWidth();	//2ch
				newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
						widthAlt = attachedCtrlAltBounds.getWidth();
						widthMax = parentWidth - attachedCtrlAltBounds.getLeft() - minimumWidth_ - this->getWidth();	//2ch
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							Rect boundsAlt = attachedCtrlAltBounds;
							boundsAlt.setRight( attachedCtrlAltBounds.getRight() - deltaAlt );	//2ch
							boundsAlt.setWidth( newWidthAlt );
							attachedControlAlt_->setBounds( &boundsAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newWidthAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						Rect bounds = attachedControl_->getBounds();
						bounds.setWidth( newWidth );
						attachedControl_->setBounds( &bounds );
						//StringUtils::traceWithArgs( "updateAttachedControl newWidth: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

		case AlignBottom : {
			//delta_ = dragPoint_.y_ - pt.y_;
			delta = -(pt.y_ - dragPoint_.y_);
			if ( 0 < delta && controlLast->getHeight() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getHeight() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				Rect attachedCtrlBounds = attachedControl_->getBounds();
				width = attachedCtrlBounds.getHeight();
				widthMax = attachedCtrlBounds.getBottom() - minimumWidth_ - this->getHeight();	//2ch
				newWidth = VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
						widthAlt = attachedCtrlAltBounds.getHeight();
						widthMax = parentHeight - attachedCtrlAltBounds.getTop() - minimumWidth_ - this->getHeight();	//2ch
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							Rect boundsAlt = attachedCtrlAltBounds;
							boundsAlt.setBottom( attachedCtrlAltBounds.getBottom() - deltaAlt );	//2ch
							boundsAlt.setHeight( newWidthAlt );
							attachedControlAlt_->setBounds( &boundsAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newHeightAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						Rect bounds = attachedControl_->getBounds();
						bounds.setHeight( newWidth );
						attachedControl_->setBounds( &bounds );
						//StringUtils::traceWithArgs( "updateAttachedControl newHeight: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

	}

	//StringUtils::trace( Format( "Splitter: calling resizeChildren( NULL )\n" ) );
	if ( NULL != attachedControlAlt_ ) {
		attachedControlAlt_->repaintNow();
	}
	if ( NULL != attachedControl_ ) {
		attachedControl_->repaintNow();
	}
	container->resizeChildren( NULL );
	getParent()->repaintNow();
}

void Splitter::updateAttachedControlJump( Point& pt, const bool& shiftAll )
{
	//if ( !dblClickEnabled_ ) {
	//	return;
	//}

	Rect parentBounds = getParent()->getBounds();

	double parentWidth = parentBounds.getWidth()-1;
	double parentHeight = parentBounds.getHeight()-1;
	double width, widthMax;
	double newWidth = 0.0;

	switch ( this->getAlignment() ) {
		case AlignLeft : {
			if ( shiftAll )
			{
				if ( NULL != attachedControl_ ) {
					Rect attachedCtrlBounds = attachedControl_->getBounds();
					width = attachedCtrlBounds.getWidth();// - minimumWidth_ - this->getWidth();
					widthMax = parentWidth - attachedCtrlBounds.getLeft() - minimumWidth_ - this->getWidth();
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.x_ += deltaRestore_;
					} else {
						pt.x_ -= newWidth - minimumWidth_;
						deltaRestore_ = newWidth - minimumWidth_;
					}
				}
			}
			else
			{
				if ( NULL != attachedControlAlt_ ) {
					Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
					width = attachedCtrlAltBounds.getWidth() - minimumWidth_ - this->getWidth();
					widthMax = attachedCtrlAltBounds.getRight() - minimumWidth_ - this->getWidth();
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.x_ -= deltaRestore_;
					} else {
						pt.x_ += newWidth;
						deltaRestore_ = newWidth /*+ minimumWidth_ + this->getWidth()*/;
					}
				}
			}
			//StringUtils::traceWithArgs( "mouseDblClick delta_: %3.1f\r\n" ,delta_ );
		}
		break;

		case AlignTop : {
			if ( shiftAll )
			{
				if ( NULL != attachedControl_ ) {
					Rect attachedCtrlBounds = attachedControl_->getBounds();
					width = attachedCtrlBounds.getHeight();
					widthMax = parentHeight - attachedCtrlBounds.getTop();// - minimumWidth_ - this->getHeight();
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.y_ += deltaRestore_;
					} else {
						pt.y_ -= newWidth - minimumWidth_;
						deltaRestore_ = newWidth - minimumWidth_;
					}
				}
			}
			else
			{
				if ( NULL != attachedControlAlt_ ) {
					Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
					width = attachedCtrlAltBounds.getHeight() - minimumWidth_ - this->getHeight();
					widthMax = attachedCtrlAltBounds.getBottom() - minimumWidth_ - this->getHeight();
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.y_ -= deltaRestore_;
					} else {
						pt.y_ += newWidth;
						deltaRestore_ = newWidth /*+ minimumWidth_ + this->getWidth()*/;
					}
				}
			}
		}
		break;

		case AlignRight : {
			if ( shiftAll )
			{
				if ( NULL != attachedControl_ ) {
					Rect attachedCtrlBounds = attachedControl_->getBounds();
					width = attachedCtrlBounds.getWidth();// - minimumWidth_ - this->getWidth();
					widthMax = attachedCtrlBounds.getRight() - minimumWidth_ - this->getWidth();
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.x_ -= deltaRestore_;
					} else {
						pt.x_ += newWidth - minimumWidth_;
						deltaRestore_ = newWidth - minimumWidth_;
					}
				}
			}
			else
			{
				if ( NULL != attachedControlAlt_ ) {
					Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
					width = attachedCtrlAltBounds.getWidth() - minimumWidth_ - this->getWidth();
					widthMax = parentWidth - attachedCtrlAltBounds.getLeft() - minimumWidth_ - this->getWidth();
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.x_ += deltaRestore_;
					} else {
						pt.x_ -= newWidth;
						deltaRestore_ = newWidth;
					}
				}
			}
		}
		break;

		case AlignBottom : {
			if ( shiftAll )
			{
				if ( NULL != attachedControl_ ) {
					Rect attachedCtrlBounds = attachedControl_->getBounds();
					width = attachedCtrlBounds.getHeight();// - minimumWidth_ - this->getHeight();	//2ch
					widthMax = attachedCtrlBounds.getBottom() - minimumWidth_ - this->getHeight();	//2ch
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.y_ -= deltaRestore_;
					} else {
						pt.y_ += newWidth - minimumWidth_;
						deltaRestore_ = newWidth - minimumWidth_;
					}
				}
			}
			else
			{
				if ( NULL != attachedControlAlt_ ) {
					Rect attachedCtrlAltBounds = attachedControlAlt_->getBounds();
					width = attachedCtrlAltBounds.getHeight() - minimumWidth_ - this->getHeight();	//2ch
					widthMax = parentWidth - attachedCtrlAltBounds.getTop() - minimumWidth_ - this->getHeight();	//2ch
					newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
					if ( newWidth == minimumWidth_ ) {
						pt.y_ += deltaRestore_;
					} else {
						pt.y_ -= newWidth;
						deltaRestore_ = newWidth;
					}
				}
			}
		}
		break;

	}

	updateAttachedControl( pt, shiftAll );
}

void Splitter::paint( GraphicsContext* ctx )
{
	CustomControl::paint( ctx );
	Rect r( 0, 0, getWidth(), getHeight() );
	bdr_.paint( &r, ctx );
}

double Splitter::getPreferredHeight()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtSeparatorHeight ) * 3;
}

double Splitter::getPreferredWidth()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtSeparatorHeight ) * 3;
}


/**
$Id$
*/


#ifndef _VCF_COLUMNLAYOUTCONTAINER_H__
#define _VCF_COLUMNLAYOUTCONTAINER_H__

namespace VCF {


class ColumnLayoutContainer : public StandardContainer {
public:
	ColumnLayoutContainer(): columnCount_(0) {
		UIMetricsManager* metricsMgr = UIToolkit::getUIMetricsManager();
		setBorderWidth( metricsMgr->getPreferredSpacingFor(UIMetricsManager::stWindowBorderDelta) );
		 
	}

	enum {
		ColumnWidthResize = -1
	};


	virtual void resizeChildren( Control* control ) {
		Rect clientBounds = controlContainer_->getClientBounds();
		
		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_, 
								clientBounds.top_ + topBorderHeight_, 
								clientBounds.right_ - rightBorderWidth_, 
								clientBounds.bottom_ - bottomBorderHeight_ );

		int col = 0;

		int width = clientBounds.getWidth();
		Rect controlBounds = clientBounds;
		
		std::vector<int> rows;
		double maxHeight = 0;
		std::vector<Control*>::iterator it = controls_.begin();
		
		int row = 0;
		rows.push_back( maxHeight );

		while ( it != controls_.end() ) {
			maxHeight = maxVal<>(maxHeight,(*it)->getHeight());
			
			if ( col >= columnCount_ ) {
				col = 0;
				row ++;
				rows.push_back( maxHeight );
			}
			else {
				rows[row] = maxHeight;
			}

			col ++;

			it ++;
		}

		
		row = 0;
		col = 0;
		it = controls_.begin();
		while ( it != controls_.end() ) {
			if ( ((columnCount_-1) == col) && 
					(ColumnWidthResize == columnWidths_[col]) ) {

				controlBounds.right_ = clientBounds.right_;
			}
			else{
				controlBounds.right_ = controlBounds.left_ + columnWidths_[col];
			}
			
			controlBounds.bottom_ = controlBounds.top_ + rows[row];

			(*it)->setBounds( &controlBounds );


			controlBounds.left_ = controlBounds.right_;
			controlBounds.left_ += 
					UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlHorizontalSpacing);				

			col ++;
			if ( col >= columnCount_ ) {
				controlBounds.top_ = controlBounds.bottom_;
				controlBounds.top_ += 
					UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlVerticalSpacing);				


				controlBounds.left_ = clientBounds.left_;
				controlBounds.right_ = clientBounds.left_;

				col = 0;
				row ++;
			}
			it ++;
		}
	}

	void setColumnCount( int val ) {
		columnCount_ = val;
		columnWidths_.resize(columnCount_,ColumnLayoutContainer::ColumnWidthResize);
	}

	void setColumnWidth( int col, int val ) {
		columnWidths_[col] = val;
	}


	int columnCount_ ;
	std::vector<int> columnWidths_;
	
};


};




#endif // _VCF_COLUMNLAYOUTCONTAINER_H__





#ifndef _VCF_POINT_H__
#define _VCF_POINT_H__
//Point.h

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

/**
*represents a 2 dimensional coordinate (x and y)
and stores the data as doubles, for maximum precision.
*/
class GRAPHICSKIT_API Point: public Object {
public:
	/**
	*the x coordinate of the point - specifies horizontal values
	*/
	double x_;

	/**
	*the y coordinate of the point - specifies vertical values
	*/
	double y_;

public:
	Point(const double & x, const double & y);

	Point();

	Point( const Point& pt ) : Object(pt), x_(pt.x_), y_(pt.y_) {};

	// assignment operator
	Point& operator = ( const Point& pt ) {
		x_ = pt.x_;
		y_ = pt.y_;
		return *this;
	}

	/**
	*initializes the point to zero
	*/
	void init();

	/**
	* gets a reference to this Rect instance itself.
	*to be used as conversion operator without introducing ambiguity between operators
	*/
	Point& getPoint( void );

	/**
	*sets the point value from another point
	*/
	void setPoint( const Point& point );

	/**
	*tells if the point has both zero coordinates
	*/
	bool isNull() const;

	/**
	*initializes the point to zero coordinates
	*/
	void setNull();

	/**
	*translates a point by a delta in x and and the same delta in y
	*/
	Point& offset( const double& _offset );

	/**
	*translates a point by a delta in x and and a delta in y
	*/
	Point& offset( const double& offsetX, const double& offsetY );

	/**
	*translates a point by a delta in x and and a delta in y 
	* indicated as a point for clarity of use
	*/
	Point& offset( const Point& offsetPt );

	/**
	*determines if this Point instance has x and y coordinates 
	* within a given tolerance range.
	*@param double x coordinate
	*@param double y coordinate
	*@param double the tolerance to use
	*@return true if the x and y coordinates are with the tolerance, otherwise false.
	*/
	bool closeTo( const double& x, const double& y, const double& tolerance=1.0 );

	/**
	*determines if this Point instance is close to a specified point
	* within a given tolerance range.
	*/
	bool closeTo( const Point& pt, const double& tolerance=1.0 );

	/**
	*determines if this Point instance is in the rectangle 
	*having its opposite corners as specified by two given points.
	*If this point is on the top or on the left border of the described 
	*rectangle, it is considered inside the rectangle.
	*/
	bool isInBetween ( const Point& pt1, const Point& pt2 ) const;

	/**
	*determines if this Point instance is in the rectangle 
	*having its opposite corners as specified by two given points.
	*If this point is on the top or on the left border of the described 
	*rectangle, it is <b>not</b> considered inside the rectangle.
	*/
	bool isInBetweenOpen ( const Point& pt1, const Point& pt2 ) const;

	/**
	*determines if this Point instance is in the rectangle 
	*having its opposite corners as specified by two given points.
	*If this point is on the top or on the left border of the described 
	*rectangle, it <b>is</b> considered inside the rectangle.
	*/
	bool isInBetweenClose ( const Point& pt1, const Point& pt2 ) const;

	// comparison operators
	bool operator == ( const Point& pointToCompare ) const;
	bool operator != ( const Point& pointToCompare ) const;
	bool operator <= ( const Point& pointToCompare ) const ;
	bool operator < ( const Point& pointToCompare ) const ;
	bool operator >= ( const Point& pointToCompare ) const ;
	bool operator > ( const Point& pointToCompare ) const ;

	// unary operators
	Point& operator+= ( const Point& pt );
	Point& operator-= ( const Point& pt );
	Point& operator*= ( const Point& pt );
	Point& operator/= ( const Point& pt );

	// binary operators
	Point operator+ ( const Point& pt ) const ;
	Point operator- ( const Point& pt ) const ;
	Point operator* ( const Point& pt ) const ;
	Point operator/ ( const Point& pt ) const ;

	// unary scalar operators
	Point& operator+= ( const double d );
	Point& operator-= ( const double d );
	Point& operator*= ( const double d );
	Point& operator/= ( const double d );

	// binary scalar operators
	Point operator+ ( const double d ) const ;
	Point operator- ( const double d ) const ;
	Point operator* ( const double d ) const ;
	Point operator/ ( const double d ) const ;

	/**
	*returns a String giving the infos about this Point instance.
	*/
	virtual String toString() const;
};

///////////////////////////////////////////////////////////////////////////////
// inline

inline Point::Point( const double & x, const double & y ) {
	x_ = x;
	y_ = y;
}

inline Point::Point() {
	x_ = 0.0;
	y_ = 0.0;
}

inline void Point::init() {
	x_ = 0.0;
	y_ = 0.0;
}

inline Point& Point::getPoint( void ) {
	return *this;
}

inline void Point::setPoint( const Point& point ) {
	x_ = point.x_;
	y_ = point.y_;
}

inline bool Point::isNull() const {
	return (x_ == 0) && (y_ == 0);
}

inline void Point::setNull() {
	x_ = 0;
	y_ = 0;
}

inline Point& Point::offset( const double& _offset ) {
	return this->operator+= ( _offset );
}

inline Point& Point::offset( const double& _offsetX, const double& _offsetY ) {
	x_ += _offsetX;
	y_ += _offsetY;
}

inline Point& Point::offset( const Point& offsetPt ) {
	return this->operator+= ( offsetPt );
}

// comparison
inline bool Point::closeTo( const double& x, const double& y, const double& tolerance ) const {
	return ( ( ::fabs(x_ - x) <= tolerance) && (::fabs(y_ - y) <= tolerance ) );
}

inline bool Point::closeTo( const Point& pt, const double& tolerance ) const {
	return closeTo( pt.x_, pt.y_, tolerance );
}

inline bool Point::isInBetween ( const Point& pt1, const Point& pt2 ) const {
	return ( pt1 <= *this && *this< pt2 );
};

inline bool Point::isInBetweenOpen ( const Point& pt1, const Point& pt2 ) const {
	return ( pt1 < *this && *this< pt2 );
};

inline bool Point::isInBetweenClose ( const Point& pt1, const Point& pt2 ) const {
	return ( pt1 <= *this && *this<= pt2 );
};

// comparison operators
inline bool Point::operator == ( const Point& pointToCompare ) const {
	return ( (this->x_ == pointToCompare.x_) && (this->y_ == pointToCompare.y_) );
};

inline bool Point::operator != ( const Point& pointToCompare ) const {
	return  ( (this->x_ != pointToCompare.x_) || (this->y_ != pointToCompare.y_) );
};

inline bool Point::operator <= ( const Point& pointToCompare ) const {
	return ( (this->x_ <= pointToCompare.x_) &&
	         (this->y_ <= pointToCompare.y_) );
};

inline bool Point::operator < ( const Point& pointToCompare ) const {
	return ( (this->x_ < pointToCompare.x_) &&
	         (this->y_ < pointToCompare.y_) );
};

inline bool Point::operator >= ( const Point& pointToCompare ) const {
	return ( (this->x_ >= pointToCompare.x_) &&
	         (this->y_ > pointToCompare.y_) );
};

inline bool Point::operator > ( const Point& pointToCompare ) const {
	return ( (this->x_ > pointToCompare.x_) &&
	         (this->y_ > pointToCompare.y_) );
};

// unary operators
inline Point& Point::operator+= ( const Point& pt ) {
	x_ += pt.x_;
	y_ += pt.y_;
	return *this;
}

inline Point& Point::operator-= ( const Point& pt ) {
	x_ -= pt.x_;
	y_ -= pt.y_;
	return *this;
}

inline Point& Point::operator*= ( const Point& pt ) {
	x_ *= pt.x_;
	y_ *= pt.y_;
	return *this;
}

inline Point& Point::operator/= ( const Point& pt ) {
	x_ /= pt.x_;
	y_ /= pt.y_;
	return *this;
}

// binary operators
inline Point Point::operator+(const Point& pt) const {
	Point ps = *this;
	ps += pt;
	return ps;
}

inline Point Point::operator-(const Point& pt) const {
	Point ps = *this;
	ps -= pt;
	return ps;
}

inline Point Point::operator*(const Point& pt) const {
	Point ps = *this;
	ps *= pt;
	return ps;
}

inline Point Point::operator/(const Point& pt) const {
	Point ps = *this;
	ps /= pt;
	return ps;
}

// unary scalar operators
inline Point& Point::operator+= ( const double d ) {
	x_ += d;
	y_ += d;
	return *this;
}

inline Point& Point::operator-= ( const double d ) {
	x_ -= d;
	y_ -= d;
	return *this;
}

inline Point& Point::operator*= ( const double d ) {
	x_ *= d;
	y_ *= d;
	return *this;
}

inline Point& Point::operator/= ( const double d ) {
	x_ /= d;
	y_ /= d;
	return *this;
}

// binary scalar operators
inline Point Point::operator+(const double d) const {
	Point ps = *this;
	ps += d;
	return ps;
}

inline Point Point::operator-(const double d) const {
	Point ps = *this;
	ps -= d;
	return ps;
}

inline Point Point::operator*(const double d) const {
	Point ps = *this;
	ps *= d;
	return ps;
}

inline Point Point::operator/(const double d) const {
	Point ps = *this;
	ps /= d;
	return ps;
}

}; // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2.2.2  2004/10/26 06:12:16  marcelloptr
*bugfix [1045603] forgotten const in Point and Rect; better formatting and documentation
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.12.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.2.1  2003/10/28 04:06:10  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.11  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.10.2.1  2003/05/30 04:13:10  ddiego
*added the commandLine class
*changed the intialization functions for the FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.10  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.2.1  2003/03/12 03:09:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.14.2  2002/12/28 21:50:46  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.8.14.1  2002/11/28 05:12:04  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.8  2002/03/31 19:54:33  ddiego
*fixed a release bug in the TreeListControl
*made sure that saving the state of a Frame works correctly
*
*Revision 1.7  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_POINT_H__



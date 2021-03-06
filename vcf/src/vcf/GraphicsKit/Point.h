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




#define POINT_CLASSID	"ddf5376d-a6da-44c0-81b8-c852c3309f3e"

namespace VCF{

/**
\class Point Point.h "vcf/GraphicsKit/Point.h"
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
	bool closeTo( const double& x, const double& y, const double& tolerance=1.0 ) const;

	/**
	*determines if this Point instance is close to a specified point
	* within a given tolerance range.
	*/
	bool closeTo( const Point& pt, const double& tolerance=1.0 ) const;

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


	double getX() {
		return x_;
	}

	void setX( const double& val ) {
		x_ = val;
	}

	double getY() {
		return y_;
	}

	void setY( const double& val ) {
		y_ = val;
	}
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
	return (*this);
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


#endif // _VCF_POINT_H__

/**
$Id$
*/

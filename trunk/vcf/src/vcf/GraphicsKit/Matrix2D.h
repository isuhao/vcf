#ifndef _VCF_MATRIX2D_H__
#define _VCF_MATRIX2D_H__
//Matrix2D.h

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
\class Matrix2D Matrix2D.h "vcf/GraphicsKit/Matrix2D.h"
The Matrix2D is used for transforming 2D shapes or images. This class is 
intended to represent an affine matrix made up of a 3X3 array of doubles.
@see GraphicsContext
@see Path
*/
class GRAPHICSKIT_API Matrix2D : public Object {
public:
	/**
	Use the values of these enums to
	reference a value of the matrix
	*/
	enum MatrixElementIndex{
		/**
		references element at 0,0 in matrix
		*/
		mei00 = 0,

		/**
		references element at 0,1 in matrix
		*/
		mei01 = 1,

		/**
		references element at 0,2 in matrix
		*/
		mei02 = 2,

		/**
		references element at 1,0 in matrix
		*/
		mei10 = 3,

		/**
		references element at 1,1 in matrix
		*/
		mei11 = 4,

		/**
		references element at 1,2 in matrix
		*/
		mei12 = 5,

		/**
		references element at 2,0 in matrix
		*/
		mei20 = 6,

		/**
		references element at 2,1 in matrix
		*/
		mei21 = 7,

		/**
		references element at 2,2 in matrix
		*/
		mei22 = 8
	};


	Matrix2D();

	Matrix2D ( const Matrix2D& matrix );

	virtual ~Matrix2D();

	/**
	*transposes the matrix
	*@param Matrix2D dest the matrix that is transposed by this
	*matrix.
	*/
    void transpose( Matrix2D* dest );

	/**
	*creates a reflection matrix
	*@param bool reflectX whether or not to reflect on the X axis
	*@param bool reflectY whether or not to reflect on the Y axis
	*/
    void reflect( const bool& reflectX, const bool& reflectY );

	/**
	*creates a rotation matrix
	*@param double the angle of the newly created rotation matrix
	*from 0.0..360.0
	*/
    void rotate( const double& theta );

	/**
	*creates a shear matrix
	*@param double shearX the amount to shear along the X axis ranges in degrees
	*from 0.0...360.0
	*@param double shearY the amount to shear along the Y axis ranges in degrees
	*from 0.0...360.0
	*/
    void shear( const double& shearX, const double& shearY );

	/**
	*creates a scale matrix
	*<code>
	*|0|scaleX|0|
	*|scaleY|0|0|
	*|0|0|1|
	*</code>
	*@param double scaleX the amount of scaling to apply along the x axis
	*@param double scaleY the amount of scaling to apply along the Y axis
	*/
    void scale( const double& scaleX, const double& scaleY );

	/**
	*Creates an identity matrix
	*<code>
	*|1|0|0|
	*|0|1|0|
	*|0|0|1|
	*</code>
	*/
    void identity();

	/**
	*multiply m1 X m2 and store the result in the current instance
	*@return Matrix2D a pointer to the current instance
	*/
    Matrix2D* multiply( Matrix2D* m1, Matrix2D* m2 );

	/**
	*creates a translation matrix
	*@param double transX the amount to translate along the X axis
	*@param double transY the amount to translate along the Y axis
	*/
    void translate( const double& transX, const double& transY );

	/**
	*inverts the current matrix
	*/
	void invert();

	Point* apply( Point* point );

	/**
	*is the current matrix instance equal to the object passed in ?
	*where hopefully the object is a pointer to a Matrix2D instance.
	@return  bool true if the two Matrix2D's matrix_ data is equal in
	*value, otherwise false
	*/
	virtual bool isEqual( Object* object )const;

	/**
	*copy the data in the Matrix2D source into the current
	*instance.
	*/
	virtual void copy( Object* source );


	Matrix2D& operator= ( const Matrix2D& matrix );

	bool operator == ( const Matrix2D& matrix )const;

	/**
	*subscript operator overload for conveniently accessing the matrix
	*elements. Access is provided by using the #defines above, where M_00
	*represents the double value at matrix_[0][0], and M_01 represents
	*the double value at matrix_[0][1], and so forth.
	*/
	double& operator[]( MatrixElementIndex index );

	double operator[]( MatrixElementIndex index ) const;

protected:

	double matrix_[3][3];

private:

};

};


#endif // _VCF_MATRIX2D_H__

/**
$Id$
*/
#ifndef _VCF_BASIC3DBORDER_H__
#define _VCF_BASIC3DBORDER_H__
//Basic3DBorder.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{


#define BASIC3DBORDER_CLASSID			"3126B222-2819-11d4-B53A-00C04F0196DA"

/**
*Draws a basic 3D border around a component. The border is 2 pixels thick
*
*@version 1.0
*@author Jim Crafton
*/
class APPLICATIONKIT_API Basic3DBorder : public Border {

public:


	Basic3DBorder();

	virtual ~Basic3DBorder();

	/**
	*Paint the border on context
	*/
	virtual void paint( Control* control, GraphicsContext* context );

	virtual void paint( Rect* bounds, GraphicsContext* context );

	/**
	*returns a client rect in which contained components may live.
	*Thus if a particular implementation required a 3 pixel
	*border at the edges to draw itself, then it would retrieve the
	*component's border and then reduce it by 3 pixels. This new
	*value is the available area that the component could use to
	*place child components
	*
	*@param Control* - component that the border belongs to
	*
	*@return Rect* the client rectangle
	*/
	virtual Rect getClientRect( Control* component );

	void setInverted( const bool& inverted ) {
		inverted_ = inverted;
	}
protected:

private:
	bool inverted_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.1.2.4  2004/07/07 22:31:37  dougtinkham
*added inversion to give border a sunken appearrance.
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:38  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8  2003/05/17 20:37:09  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.2.1  2002/12/27 23:04:35  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.5.10.1  2002/10/01 20:34:58  ddiego
*borders
*
*Revision 1.5  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_BASIC3DBORDER_H__



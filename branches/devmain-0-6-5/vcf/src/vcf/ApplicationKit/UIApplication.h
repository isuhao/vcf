/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.26.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.3  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/

//UIApplication.h

#ifndef _VCF_UIAPPLICATION_H__
#define _VCF_UIAPPLICATION_H__



#define UIAPPLICATION_CLASSID		"ec9764b9-cb25-4c3b-9ac7-eeea0cf3b26f"


namespace VCF  {

/**
*Class UIApplication documentation
*/
class UIApplication : public Application { 
public:
	
	BEGIN_CLASSINFO(UIApplication, "UIApplication", "Application", UIAPPLICATION_CLASSID)
	END_CLASSINFO(UIApplication)
	
	UIApplication();

	virtual ~UIApplication();

protected:

private:
};


}; //end of namespace VCF

#endif // _VCF_UIAPPLICATION_H__



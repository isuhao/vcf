#ifndef _VCF_OSXAPPLICATIONPEER_H__
#define _VCF_OSXAPPLICATIONPEER_H__
//OSXApplicationPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

/**

*/
class OSXApplicationPeer : public Object, public ApplicationPeer  {
public:
	OSXApplicationPeer();

	virtual ~OSXApplicationPeer();

	virtual bool initApp();

	virtual void terminateApp();

	virtual VCF::AbstractApplication* getApplication() {
		return app_;
	}

	virtual void setApplication( VCF::AbstractApplication* application );

	virtual ResourceBundle* getResourceBundle();

	virtual String getFileName();

	virtual OSHandleID getHandleID();

	virtual void setHandleID( OSHandleID handleID );
protected:
	VCF::AbstractApplication* app_;
	OSHandleID handleID_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2.4.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*/


#endif // _VCF_OSXAPPLICATIONPEER_H__


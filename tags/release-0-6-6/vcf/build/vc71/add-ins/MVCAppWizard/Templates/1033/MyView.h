#ifndef _[!output UPPER_CASE_PROJECT_NAME]VIEW_H__
#define _[!output UPPER_CASE_PROJECT_NAME]VIEW_H__


#define [!output UPPER_CASE_PROJECT_NAME]VIEW_CLASSID		"[!output VIEW_UUID]"


/**
class [!output PROJECT_NAME]View documentation
*/
class [!output PROJECT_NAME]View : public VCF::Object, public VCF::AbstractView {
public: 
	BEGIN_CLASSINFO( [!output PROJECT_NAME]View, "[!output PROJECT_NAME]View", "VCF::Object", [!output UPPER_CASE_PROJECT_NAME]VIEW_CLASSID )
	END_CLASSINFO( [!output PROJECT_NAME]View )
	[!output PROJECT_NAME]View();

	virtual ~[!output PROJECT_NAME]View();


	virtual void paintView( VCF::GraphicsContext* ctx );
protected:

};



#endif //_[!output UPPER_CASE_PROJECT_NAME]VIEW_H__




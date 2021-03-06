#ifndef _VCF_WIN32DRAGDROPPEER_H__
#define _VCF_WIN32DRAGDROPPEER_H__
//Win32DragDropPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_COMDATAOBJECT_H__
#	include "vcf/ApplicationKit/Win32COMDataObject.h"
#endif // _VCF_COMDATAOBJECT_H__


namespace VCF {

class Win32DragDropPeer : public DragDropPeer, public Object
{
public:

	Win32DragDropPeer();
	virtual ~Win32DragDropPeer();

    virtual DragActionType startDragDrop( DataObject* data );

	virtual DragSource* getDragSource();

	virtual void setDragSource( VCF::DragSource*  dragSource );

	void setActionType( const DragActionType& actionType );

	class COMDragSource : public IDropSource {
	public:
		COMDragSource(Win32DragDropPeer* owningPeer):owningPeer_(owningPeer){};

		virtual ~COMDragSource() {};

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObj) {
			if ( iid == IID_IUnknown ) {
				*ppvObj = (IUnknown*)(this);
				((IUnknown*)(*ppvObj))->AddRef();
				return S_OK;
			}
			else if ( iid == IID_IDropSource ) {
				*ppvObj = (IDropSource*)(this);
				((IUnknown*)(*ppvObj))->AddRef();
				return S_OK;
			}
			return E_NOINTERFACE;
		}

		virtual ULONG STDMETHODCALLTYPE AddRef(void) {

			return 1;
		}

		virtual ULONG STDMETHODCALLTYPE Release(void) {


			return 1;
		}

		//COM CALLS
		STDMETHOD(QueryContinueDrag)( BOOL fEscapePressed, DWORD grfKeyState ) {
			return owningPeer_->QueryContinueDrag( fEscapePressed, grfKeyState );
		}

		STDMETHOD(GiveFeedback)( DWORD dwEffect ) {
			return owningPeer_->GiveFeedback( dwEffect );
		}


	private:
		Win32DragDropPeer * owningPeer_;
	};
protected:

	friend class COMDragSource;
	HRESULT GiveFeedback( DWORD dwEffect );

	HRESULT QueryContinueDrag( BOOL fEscapePressed, DWORD grfKeyState );

    VCFCOM::COMDataObject * dataObj_;

	COMDragSource* comDragSrc_;

	VCF::DragSource * dragSrc_;

	VCF::DataObject * clipDataObj_;

	DWORD dragDropEffect_;

	DragActionType actionType_;
};

};


#endif // _VCF_WIN32DRAGDROPPEER_H__

/**
$Id$
*/

#ifndef _VCF_DEFAULTTREEMODEL_H__
#define _VCF_DEFAULTTREEMODEL_H__
//DefaultTreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




#ifndef _VCF_ABSTRACTMODEL_H__
#	include "vcf/ApplicationKit/AbstractModel.h"
#endif // _VCF_ABSTRACTMODEL_H__


#ifndef _VCF_ABSTRACTTREEMODEL_H__
#include "vcf/ApplicationKit/AbstractTreeModel.h"
#endif //_VCF_ABSTRACTTREEMODEL_H__



namespace VCF{

#define DEFAULTTREEMODEL_CLASSID		"3126B226-2819-11d4-B53A-00C04F0196DA"

class APPLICATIONKIT_API DefaultTreeModel : public AbstractModel, public AbstractTreeModel {
public:
	/**
	@delegate RootNodeChanged
	@event
	*/
	DELEGATE(RootNodeChanged)

	/**
	@delegate NodeAdded
	@event
	*/
	DELEGATE(NodeAdded)

	/**
	@delegate NodeDeleted
	@event
	*/
	DELEGATE(NodeDeleted)

	virtual void addTreeRootNodeChangedHandler( EventHandler* handler ) {
		RootNodeChanged += handler;
	}

	virtual void removeTreeRootNodeChangedHandler( EventHandler* handler ) {
		RootNodeChanged -= handler;
	}

	virtual void addTreeNodeAddedHandler( EventHandler* handler ) {
		NodeAdded += handler;
	}

	virtual void removeTreeNodeAddedHandler( EventHandler* handler ) {
		NodeAdded -= handler;
	}

	virtual void addTreeNodeDeletedHandler( EventHandler* handler ) {
		NodeDeleted += handler;
	}

	virtual void removeTreeNodeDeletedHandler( EventHandler* handler ) {
		NodeDeleted -= handler;
	}

	DefaultTreeModel();

	virtual ~DefaultTreeModel();

	void init();

	virtual void empty() {
		AbstractTreeModel::empty();

		AbstractModel::empty();
	}

    virtual void insertNodeItem(TreeItem * node, TreeItem * nodeToInsertAfter);

    virtual void deleteNodeItem(TreeItem * nodeToDelete);

    virtual void addNodeItem( TreeItem * node, TreeItem * nodeParent=NULL );

protected:

	virtual void onItemPaint( ItemEvent* event );

    virtual void onItemChanged( ItemEvent* event );

    virtual void onItemSelected( ItemEvent* event );

	virtual void onItemAdded( ItemEvent* event );

	virtual void onItemDeleted( ItemEvent* event );

	
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/10/05 03:15:23  kiklop74
*Additional changes in tree model
*
*Revision 1.2.2.2  2004/10/05 02:48:22  kiklop74
*Added needed changes that will enable Borland compiler to compile RTTI for ApplicationKit
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.10  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.16.1  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/04/27 15:42:17  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTTREEMODEL_H__



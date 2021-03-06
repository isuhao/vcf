//DefaultTreeModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTreeModel.h"


using namespace VCF;

DefaultTreeModel::DefaultTreeModel():
	lastKey_(0)
{

}

DefaultTreeModel::~DefaultTreeModel()
{

}


void DefaultTreeModel::empty()
{
	DataMap::iterator it = data_.begin();
	if ( shouldDeleteVarObjects() ) {
		while ( it != data_.end() ) {
			TreeValRef& ref = it->second;		
			if ( ref.data.type == pdObject ) {
				Object* obj = ref.data;
				if ( NULL != obj ) {
					deleteVariantObject( obj );
				}
			}
			++it;
		}
	}

	data_.clear();
	hierarchy_.clear();

	TreeModelEvent event( this, TreeModel::ContentsDeleted );
	ModelChanged( &event );
	lastKey_ = 0;
}

void DefaultTreeModel::insertRef( TreeValRef& ref, TreeModel::Key parentKey )
{
	//find the parent, and hook up the 
	//new tree ref's parent pointer to 
	//the parent ref, if it exists
	DataMap::iterator found = data_.find( parentKey );
	if ( found != data_.end() ) {
		TreeValRef& tvr = found->second;		
		ref.parent = &tvr;
	}	

	//hook up the prev and next pointers
	HierarchyRange range = hierarchy_.equal_range( parentKey );

	bool rangeValid = false;
	//go to the last element in the range, if the
	//the range is valid
	if ( range.first != range.second ) {
		rangeValid = true;
		range.first = range.second;
		range.first --;
	}
	
	data_[ ref.key ] = ref;
	
	found = data_.find( ref.key );
	TreeValRef& ref2 = found->second;
	
	if ( rangeValid ) {
		TreeModel::Key childKey = range.first->second;		
		found = data_.find( childKey );
		if ( found != data_.end() ) {
			TreeValRef& r = found->second;
			
			r.nextSibling = &ref2;
			
			ref2.prevSibling = &r;
		}
	}
	
	
	hierarchy_.insert( HierarchyValue(parentKey,ref2.key) );
}

TreeModel::Key DefaultTreeModel::doInsert( const VariantData& value, const TreeModel::Key& parentKey )
{
	TreeModel::Key result;

	lastKey_ ++;

	TreeValRef ref;
	ref.key = lastKey_;
	ref.data = value;


	result = lastKey_;

	insertRef( ref, parentKey );

	return result;
}

TreeModel::Key DefaultTreeModel::removeFromHierarchy( TreeModel::Key key )
{
	TreeModel::Key result(TreeModel::InvalidKey);

	DataMap::iterator found = data_.find( key );
	if ( found != data_.end() ) {
		
		TreeValRef& ref = found->second;
		
		if ( ref.prevSibling ) {
			ref.prevSibling->nextSibling = ref.nextSibling;
		}
		if ( ref.nextSibling ) {
			ref.nextSibling->prevSibling = ref.prevSibling;
		}
				
		HierarchyRange range = hierarchy_.equal_range( key );
		//yank children
		while ( range.first != range.second ) {
			TreeModel::Key k = range.first->second; //store the child key
			//increment here, BEFORE we recurse. 
			//this moves us to the next iterator. If 
			//we did this AFTER the call to removeFromHierarchy()
			//then the iterator would be bad (since it 
			//pointed to the just erased item
			++range.first; 
			removeFromHierarchy( k );	
		}
		

		//thanks to Fraggle for fixing this!!
		TreeModel::Key parentKey = (NULL != ref.parent) ? ref.parent->key : TreeModel::RootKey;
		range = hierarchy_.equal_range( parentKey );
		while ( range.first != range.second && range.first->second != key ) {
			++range.first;
		}

		if ( range.first->first == parentKey && range.first->second == key ) {
			hierarchy_.erase( range.first );
		}

		result = parentKey;		
		
		notifyItemRemoved( ref.key, parentKey );

		data_.erase( found );
	}

	return result;
}

TreeModel::Key DefaultTreeModel::doRemove( const TreeModel::Key& key )
{
	return removeFromHierarchy( key );
}

VariantData DefaultTreeModel::get( const TreeModel::Key& key )
{
	VariantData result = VariantData::null();

	DataMap::iterator found = data_.find( key );
	if ( found != data_.end() ) {
		result = found->second.data;
	}

	return result;
}


bool DefaultTreeModel::doSet( const TreeModel::Key& key, const VariantData& value )
{
	bool result = false;
	DataMap::iterator found = data_.find( key );
	if ( found != data_.end() ) {
		result = true;
		found->second.data = value;
	}

	return result;
}

TreeModel::Key DefaultTreeModel::doMove( const TreeModel::Key& srcKey, const TreeModel::Key& destParentKey )
{
	TreeModel::Key result = TreeModel::InvalidKey;

	DataMap::iterator found = data_.find( srcKey );
	if ( found != data_.end() ) {
		
		TreeValRef& ref = found->second;
		
		if ( ref.prevSibling ) {
			ref.prevSibling->nextSibling = ref.nextSibling;
		}
		if ( ref.nextSibling ) {
			ref.nextSibling->prevSibling = ref.prevSibling;
		}
		
		if ( ref.parent ) {
			HierarchyRange range = hierarchy_.equal_range( ref.parent->key );
			
			while ( range.first != range.second ) {
				if ( range.first->second == srcKey ) {
					hierarchy_.erase( range.first );
					break;
				}				
				++range.first;				
			}
		}

		insertRef( ref, destParentKey );

		result = ref.key;		
	}

	return result;
}

bool DefaultTreeModel::doClearChildren( const Key& key )
{
	bool result = false;
	std::vector<TreeModel::Key> children;
	if ( getChildren( key, children ) ) {
		std::vector<TreeModel::Key>::iterator it = children.begin();
		while ( it != children.end() ) {
			removeFromHierarchy( *it );	
			++it;
		}

		result = true;
	}

	return result;
}

bool DefaultTreeModel::getChildren(const TreeModel::Key& key, std::vector<TreeModel::Key>& children )
{
	HierarchyRange range = hierarchy_.equal_range( key );	
	while ( range.first != range.second ) {		
		children.push_back( range.first->second );
		++range.first;
	}

	return !children.empty();
}

TreeModel::Key DefaultTreeModel::getParent( const TreeModel::Key& key )
{
	TreeModel::Key result = TreeModel::InvalidKey;

	DataMap::iterator found = data_.find( key );
	if ( found != data_.end() ) {

		TreeValRef& ref = found->second;

		if ( ref.parent ) {
			result = ref.parent->key;
		}
	}

	return result;
}	

TreeModel::Key DefaultTreeModel::getNextSibling( const TreeModel::Key& key )
{
	TreeModel::Key result(TreeModel::InvalidKey);

	DataMap::iterator found = data_.find( key );
	if ( found != data_.end() ) {

		TreeValRef& ref = found->second;

		if ( ref.nextSibling ) {
			result = ref.nextSibling->key;
		}
	}

	return result;
}


TreeModel::Key DefaultTreeModel::getPrevSibling( const TreeModel::Key& key )
{
	TreeModel::Key result(TreeModel::InvalidKey);

	DataMap::iterator found = data_.find( key );
	if ( found != data_.end() ) {

		TreeValRef& ref = found->second;

		if ( ref.prevSibling ) {
			result = ref.prevSibling->key;
		}
	}

	return result;
}

TreeModel::Key DefaultTreeModel::getFirstChild( const Key& key )
{
	TreeModel::Key result(TreeModel::InvalidKey);

	HierarchyRange range = hierarchy_.equal_range( key );	
	if ( range.first != range.second ) {
		
		DataMap::iterator found = data_.find( range.first->second );
		if ( found != data_.end() ) {			
			TreeValRef& ref = found->second;	
			
			result = ref.key;			
		}
	}

	return result;
}

bool DefaultTreeModel::isLeaf( const TreeModel::Key& key )
{
	HierarchyMap::iterator found = hierarchy_.find( key );
	return !(found != hierarchy_.end());
}

uint32 DefaultTreeModel::getCount()
{
	return data_.size();
}

uint32 DefaultTreeModel::getChildCount( const TreeModel::Key& key )
{
	uint32 result = 0;
	HierarchyRange range = hierarchy_.equal_range( key );	
	while ( range.first != range.second ) {
		result++;
		++range.first;
	}
	return result;
}


uint64 DefaultTreeModel::sizeOf() const
{
	uint64 result = 0;

	result += sizeof(DefaultTreeModel);

	DataMap::const_iterator it = data_.begin();
	while ( it != data_.end() ) {
		result += sizeof(it->first);
		result += sizeof(it->second);
		result += it->second.data.sizeOf();

		++it;
	}

	HierarchyMap::const_iterator it2 = hierarchy_.begin();
	while ( it2 != hierarchy_.end() ) {
		result += sizeof(it2->first);
		result += sizeof(it2->second);
		++it2;
	}


	return result;
}

/**
$Id$
*/


//ListModel.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ListModel.h"
#include "vcf/FoundationKit/ThreadManager.h"
#include "vcf/ApplicationKit/TimerEvent.h"

using namespace VCF;


void ListModel::setCurrentIndex( const uint32& val ) 
{
	if ( val != currentIndex_ ) {
		ListModelEvent event( this, lmeCurrentIndexChanged );
		currentIndex_ = val;		

		event.index = currentIndex_;
		ModelChanged( &event );
	}
}

void ListModel::asyncInsertRange( ListModel::AsyncInsertEvent* e )
{
	insertRange( e->index, e->items );
}

void ListModel::asyncChange( TimerEvent* e )
{
	TimerComponent* tc = (TimerComponent*)e->getSource();
	tc->setActivated(false);

	ListModelEvent event( this, lmeItemAdded );
	ModelChanged( &event );	
	
	StringUtils::trace( Format("ListModel::asyncChange called with %u items\n") % getCount() );
}

void ListModel::insertRange( const uint32 & index, const std::vector<VariantData>& items )
{
	std::vector<VariantData>::const_iterator it = items.begin();
	

	uint32 idx = index;
	while ( it != items.end() ) {
		if ( !doInsert( idx, *it ) ) {
			return;
		}
		idx++;

		++it;
	}

	if ( !ThreadManager::isCurrentThreadMainThread() ) {
		TimerComponent* tc = (TimerComponent*)this->findComponent( "modTimer" );
		if ( NULL == tc ) {
			tc = new TimerComponent("modTimer", this);
			tc->setTimeoutInterval( 500 );
			tc->TimerPulse += 
				new ClassProcedure1<TimerEvent*,ListModel>(this,&ListModel::asyncChange);

		}
		tc->setActivated(false); //turn off prev 

		tc->setActivated(true);
		
	}
	else {
		ListModelEvent event( this, lmeItemAdded );
		ModelChanged( &event );
	}
}

void ListModel::insert( const uint32 & index, const VariantData& item )
{
	if ( doInsert( index, item ) ) {
		
		ListModelEvent event( this, lmeItemAdded );
		event.item = (VariantData*) &item;
		event.index = index;
		ItemAdded( &event );
		
		event.setType( lmeItemAdded );
		ModelChanged( &event );
	}
}

void ListModel::remove( const uint32& index )
{
	if ( index != ListModel::InvalidIndex ) {
		if ( doRemove( index ) ) {
		
		}
	}
}

void ListModel::set( const uint32& index, const VariantData& item )
{
	if ( doSet( index, item ) ) {
		ListModelEvent itemEvent( this, lmeItemChanged );
		itemEvent.item = (VariantData*)&item;
		itemEvent.index = index;

		VariantData k = index;
		itemEvent.key = &k;
		itemEvent.value = &item;

		ModelChanged( &itemEvent );
	}
}

void ListModel::insertSubItem( const uint32& index, const uint32 & subItemIndex, const VariantData& value )
{	
	if ( doInsertSubItem( index, subItemIndex, value ) ) {
		ListModelEvent itemEvent( this, lmeSubItemAdded );
		itemEvent.item = (VariantData*) &value;
		itemEvent.index = index;
		itemEvent.subIndex = subItemIndex;

		VariantData k = index;
		itemEvent.key = &k;
		itemEvent.value = &value;

		ModelChanged( &itemEvent );
	}
}

void ListModel::removeSubItem( const uint32& index, const uint32 & subItemIndex )
{
	if ( doRemoveSubItem( index, subItemIndex ) ) {
		
	}
}

void ListModel::setSubItem( const uint32& index, const uint32& subItemIndex, const VariantData& value )
{
	if ( doSetSubItem( index, subItemIndex, value ) ) {
		ListModelEvent itemEvent( this, lmeSubItemChanged );
		itemEvent.item = (VariantData*)&value;
		itemEvent.index = index;
		itemEvent.subIndex = subItemIndex;
		ModelChanged( &itemEvent );
	}
}

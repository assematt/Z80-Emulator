#include "TManager.h"

namespace TInternals
{
	TManager::TManager() :
		mAliveElement(0),
		mNewElement(0),
		TComponentArray(this)
	{
	
	}
	
// 	void TManager::AddEntity(TEntity::TEntityPtr Entity)
// 	{
// 		// If the array of entity is full append the new one at the end
// 		if (mNewElement == mEntityContainer.size())
// 		{
// 			
// 
// 			mEntityContainer.push_back(std::move(Entity));
// 		}
// 		// Otherwise put the entity in the first available slot
// 		else
// 		{
// 			mEntityContainer[mNewElement] = std::move(Entity);
// 		}
// 	
// 		// Increment the number of new entity
// 		++mNewElement;
// 	}
// 	
// 	void TManager::RemoveEntity(std::size_t Index)
// 	{
// 		// Set the entity as dead so we can remove in the next refresh 
// 		mEntityContainer[Index]->Kill();
// 	}
	
	void TManager::Update()
	{
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{
			mComponents[Counter]->Update();
		}
	}
	
	void TManager::Refresh()
	{
		// Call the function that sort the entity container
		SortEntityContainer();

	
		// Refresh the alive entities
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{
			mComponents[Counter]->Refresh();
		}
	}
	
	void TManager::SortEntityContainer()
	{
		// 
		mAliveElement = mNewElement;
	
		// Refresh the entity array only if there are more than one alive entity
		if (mNewElement < 2)
		{
			return;
		}
	
		// Get the index of the first and last element in the array
		std::size_t FrontIndex = 0, BackIndex = mNewElement - 1;
	
		// Sort the array
		while (FrontIndex < BackIndex)
		{
			// if the front iterator state is alive we are sure the there is no swapping to do so after incrementing the front index we can skip to the next iteration
			if (mComponents[FrontIndex]->IsAlive())
			{
				++FrontIndex;
	
				continue;
			}
	
			// If we made to this point it means that the front iterator is dead so we may have a swap if the back iterator is alive
			if (mComponents[BackIndex]->IsAlive())
			{
				std::swap(mComponents[FrontIndex], mComponents[BackIndex]);
	
				++FrontIndex;
			}
	
			// Decrement the back index
			--BackIndex;
	
			// At this point we are sure that at least an entity when from being alive to dead so we decrease that alive element counter
			--mNewElement;
		}
	}
	
}

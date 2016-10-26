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
		ComputeAliveEntities();

		// Call the function that sort the entity container
		SortEntityContainer();

	
		// Refresh the alive entities
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{
			mComponents[Counter]->Refresh();
		}
	}
	
	void TManager::ComputeAliveEntities()
	{
		mAliveElement = 0;

		for (auto& Entity : mComponents)
		{
			if (Entity->IsAlive())
			{
				++mAliveElement;
			}
		}
	}

	void TManager::SortEntityContainer()
	{
		std::sort(mComponents.begin(), mComponents.end(), [](const TEntity::TEntityPtr& Left, const TEntity::TEntityPtr& Right) {
			return (Left->IsAlive() && !Right->IsAlive());
		});
	}
	
}

#pragma once

#include <vector>
#include <array>
#include "TEntity.h"

namespace TInternals
{
	class TManager : public TComponentArray<TEntity, TManager, TEntity::TEntityID>
	{
	public:
		//using TEntityContainer = std::vector<TEntity::TEntityPtr>;
		//using TEntityIDContainer = std::array<TEntity::TEntityID, 32>;
	
		TManager();
	
		/// Function that add an entity to the array
		//void AddEntity(TEntity::TEntityPtr Entity);
	
// 		template <typename... TArgs>
// 		void AddEntity(TArgs&&... mArgs)
// 		{
// 			// Creates a temp pointer that holds the value that we are gonna to insert in the array
// 			TEntity::TEntityPtr TempPtr = TEntity::MakeEntity(std::forward<TArgs>(mArgs)...);
// 	
// 			// Use the other function to add the entity
// 			AddEntity(std::move(TempPtr));
// 		}
	
		/// Function to remove an entity
		//void RemoveEntity(std::size_t Index);
	
		/// Updates every entity in the container
		void Update();
	
		/// Refreshes every entity in the container
		void Refresh();
	
	private:
		/// Sort the entity container by putting the dead entity at the back of the array end the alive one at the beginning
		void SortEntityContainer();
	
	private:
		//TEntityContainer mEntityContainer;
		//TEntityIDContainer mEntityIDContainer;
		int mAliveElement;
		int mNewElement;
	};
}
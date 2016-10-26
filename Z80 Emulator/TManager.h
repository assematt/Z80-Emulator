#pragma once

#include <vector>
#include <array>
#include "TEntity.h"

namespace TInternals
{
	class TManager : public TComponentArray<TEntity, TManager, TEntity::TEntityID>
	{
	public:	
		TManager();
	
		/// Updates every entity in the container
		void Update();
	
		/// Refreshes every entity in the container
		void Refresh();
	
	private:
		/// Get the number of alive entities
		void ComputeAliveEntities();

		/// Sort the entity container by putting the dead entity at the back of the array end the alive one at the beginning
		void SortEntityContainer();
	
	private:
		int mAliveElement;
		int mNewElement;
	};
}
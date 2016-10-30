#pragma once

#include <SFML/System/Time.hpp>
#include <vector>
#include <array>
#include "TEntity.h"
#include "TGraphicEntity.h"
#include "TGuiWindow.h"

namespace nne
{
	class TManager : public TComponentArray<TEntity, TManager, TEntity::TEntityID>
	{
	public:	
		TManager();

		/// Singleton Access
		static TManager& GetInstance();
	
		/// Updates every entity in the container
		void Update(const sf::Time& ElapsedTime);
	
		/// Refreshes every entity in the container
		void Refresh(const sf::Time& ElapsedTime);

		/// Draw all the entities in the container
		void Draw();

		/// Helper function for c++11 foreach use
		std::vector<TEntity::TEntityPtr>::iterator begin();
		std::vector<TEntity::TEntityPtr>::iterator end();

		/// Subscript operator to access an entity by index
		TEntity::TEntityPtr& operator[] (const int Index);
		const TEntity::TEntityPtr& operator[] (const int Index) const;
	
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
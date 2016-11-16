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
		static TManager& getInstance();
	
		/// updates every entity in the container
		void update(const sf::Time& ElapsedTime);
	
		/// refreshes every entity in the container
		void refresh(const sf::Time& ElapsedTime);

		/// draw all the entities in the container
		void draw();

		/// Helper function for c++11 foreach use
		std::vector<TEntity::TEntityPtr>::iterator begin();
		std::vector<TEntity::TEntityPtr>::iterator end();

		/// Subscript operator to access an entity by index
		TEntity::TEntityPtr& operator[] (const int Index);
		const TEntity::TEntityPtr& operator[] (const int Index) const;
	
	private:
		/// Get the number of alive entities
		void computeAliveEntities();

		/// Sort the entity container by putting the dead entity at the back of the array end the alive one at the beginning
		void sortEntityContainer();
	
	private:
		int mAliveElement;
		int mNewElement;
	};
}
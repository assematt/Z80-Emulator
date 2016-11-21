#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "TUtility.h"
#include "TEntity.h"
#include "TDrawableComponent.h"

namespace nne
{
	
	class TManager
	{
	public:	

		TManager();

		/// Function to add an entity to the manager
		void addEntity(TEntity::TEntityPtr& Entity, const std::string& EntityKey);

		/// Function to remove an entity to the manager
		void removeEntity(const TEntity::TEntityID& IDToRemove);

		/// Get an entity by ID, return nullptr if the entity isn't found
		TEntity::TEntityPtr& getEntityByID(const TEntity::TEntityID& IDToSearch);

		/// Get an entity by type, return nullptr if the entity isn't found
		TEntity::TEntityPtr& getEntityByKey(const std::string& EntityKey);

		void draw(sf::RenderTarget& Target);

		/// Function to init all the entity in the array
		void initEntities();

		/// updates every entity in the container
		void update(const sf::Time& ElapsedTime);

		/// refreshes every entity in the container
		void refresh(const sf::Time& ElapsedTime);

		/// Return an element specified by the Index
		TEntity::TEntityPtr& operator[] (const std::size_t& Index);
		const TEntity::TEntityPtr& operator[] (const std::size_t& Index) const;

	private:

		/// Return the position in the vector of the ID we specified, return the vector size if we don't find anything
		std::size_t getEntityPos(const TEntity::TEntityID& IDToSearch);

	protected:
		std::vector<TEntity::TEntityPtr> mEntityVector;
		std::size_t mAliveElement;
	};
}
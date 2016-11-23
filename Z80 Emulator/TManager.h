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
		void addEntity(TEntity::EntityPtr& Entity, const std::string& EntityKey, TSceneManager* SceneManager = nullptr);

		/// Function to remove an entity to the manager
		void removeEntity(const TEntity::EntityID& IDToRemove);

		/// Get an entity by ID, return nullptr if the entity isn't found
		TEntity::EntityPtr& getEntityByID(const TEntity::EntityID& IDToSearch);

		/// Get an entity by type, return nullptr if the entity isn't found
		TEntity::EntityPtr& getEntityByKey(const std::string& EntityKey);

		void draw(sf::RenderTarget& Target);

		/// Function to init all the entity in the array
		void initEntities();

		/// updates every entity in the container
		void update(const sf::Time& ElapsedTime);

		/// refreshes every entity in the container
		void refresh(const sf::Time& ElapsedTime);

		/// Return an element specified by the Index
		TEntity::EntityPtr& operator[] (const std::size_t& Index);
		const TEntity::EntityPtr& operator[] (const std::size_t& Index) const;

	private:

		/// Return the position in the vector of the ID we specified, return the vector size if we don't find anything
		std::size_t getEntityPos(const TEntity::EntityID& IDToSearch);

	protected:
		std::vector<TEntity::EntityPtr> mEntityVector;
		std::size_t mAliveElement;
	};
}
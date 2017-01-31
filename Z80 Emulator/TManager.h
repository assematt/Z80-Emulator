#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <algorithm>
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

		using EntityVector = std::vector<TEntity::EntityPtr>;
		using EntityIterator = EntityVector::iterator;
		using EntityConstIterator = EntityVector::const_iterator;

		const std::size_t NotFound = std::numeric_limits<std::size_t>::max();

		TManager();

		/// Function to add an entity to the manager
		void addEntity(TEntity::EntityPtr& Entity, const std::string& EntityKey, IScene* CurrentScene = nullptr);

		/// Function to remove an entity to the manager
		void removeEntity(const TEntity::EntityID& IDToRemove);

		/// Get an entity by ID, return nullptr if the entity isn't found
		TEntity::EntityPtr& getEntityByID(const TEntity::EntityID& IDToSearch);

		/// Get an entity by type, return nullptr if the entity isn't found
		TEntity::EntityPtr& getEntityByKey(const std::string& EntityKey);

		/// Process sf::Event's events and change the widget states accordingly and fires the widgets event
		void processEvents(const sf::Event& Event, const sf::RenderWindow& EventWindow);
		void processEvents(const sf::Event& Event, const sf::RenderWindow& EventWindow, const sf::RenderTarget& EventCanvas);

		/// Function to init all the entity in the array (useful in bulk creation of multiple entity)
		void initEntities();

		/// function to init the last added entity in the array (in case 
		void initLastEntity();

		/// updates every entity in the container
		void update(const sf::Time& ElapsedTime);

		/// refreshes every entity in the container
		void refresh(const sf::Time& ElapsedTime);

		/// Get the number of alive entities in the array
		const std::size_t& getAliveEntities() const;

		/// Get the number of all the entities in the array
		std::size_t getTotalEntities() const;

		/// Helper function for for-each style loop
		EntityIterator begin();
		EntityIterator end();

		/// Return an element specified by the Index
		TEntity::EntityPtr& operator[] (const std::size_t& Index);
		const TEntity::EntityPtr& operator[] (const std::size_t& Index) const;

	private:

		/// Return the position in the vector of the ID we specified, return the vector size if we don't find anything
		std::size_t getEntityPos(const TEntity::EntityID& IDToSearch);

		void addSorted(TEntity::EntityPtr& Entity);

	protected:
		std::vector<TEntity::EntityPtr> mEntityVector;
		std::size_t mAliveElement;
	};
}
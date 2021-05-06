#include "TManager.h"

#include <SFML/Window/Mouse.hpp>

#include "TWireComponent.h"
#include "TEventComponent.h"
#include "TStateComponent.h"
#include "TPackageComponent.h"

namespace nne
{
	
	TManager::TManager() :
		mAliveElement(0)
	{

	}

	void TManager::addEntity(TEntity::EntityPtr& Entity, const std::string& EntityKey, IScene* CurrentScene /*= nullptr*/)
	{
		Entity->mParent = this;
		Entity->mID = static_cast<TEntity::EntityID>(nne::idgenerator::GenerateByString::getUniqueID(EntityKey));
		Entity->mParentScene = CurrentScene;

		mEntityVector.push_back({ Entity });
	}

	void TManager::removeEntity(const TEntity::EntityID& IDToRemove)
	{
		// Get the position of the element to remove
		auto EntityPos = getEntityPos(IDToRemove);

		// If we can find the entity in the array return early
		if (EntityPos == NotFound)
			return;

		// Remove the element from the array by swapping it with the last valid element and popping back
		std::swap(mEntityVector[EntityPos], mEntityVector.back());
		mEntityVector.pop_back();
	}

	TEntity::EntityPtr& TManager::getEntityByID(const TEntity::EntityID& IDToSearch)
	{
		// Get the position of the element to remove
		auto EntityPos = getEntityPos(IDToSearch);
		
		// If we couldn't find the entity return an empty pointer
		if (EntityPos == NotFound)
			return TEntity::EntityPtr(nullptr);

		return mEntityVector[EntityPos];
	}

	TEntity::EntityPtr& TManager::getEntityByKey(const std::string& EntityKey)
	{
		return getEntityByID(nne::idgenerator::GenerateByString::getUniqueID(EntityKey));
	}

	void TManager::processEvents(const sf::Event& Event, const sf::RenderWindow& EventWindow)
	{
		processEvents(Event, EventWindow, EventWindow);
	}

	void TManager::processEvents(const sf::Event& Event, const sf::RenderWindow& EventWindow, const sf::RenderTarget& EventCanvas)
	{
		// Loop all the widget until we find an object to fire an event on
		// We loop in revers order (since we want to check the widget with the highest ZIndex first)
		for (auto& EntityIterator = mEntityVector.rbegin(); EntityIterator != mEntityVector.rend(); ++EntityIterator)
		{
			// First get a ref to the TEntity inside the reverse iterator
			auto& Entity = **EntityIterator;

			// If the widget doesn't allow input or doesn't have an TEventComponent skip this loop cycle
			if (!Entity.isAlive() || !Entity.hasComponent<tcomponents::TEventComponent>())
				continue;

			// Get a ref to the TEventComponent
			auto& EventComponent = Entity.getComponent<tcomponents::TEventComponent>();

			// Get a ref to the TStateComponent
			auto& StateComponent = Entity.getComponent<tcomponents::TStateComponent>();

			// Get the bound of that object
			auto& EntityBound = Entity.getComponent<TDrawableComponent>().getGlobalBounds();

			if (Entity.hasComponent<TPackageComponent>())
			{
				EntityBound = Entity.getComponent<TPackageComponent>().getGlobalBound(true);
			}
			
			// Establish if the mouse it's above the widget
			auto MousePos = EventCanvas.mapPixelToCoords(sf::Mouse::getPosition(EventWindow) - sf::Vector2i(300, 50));
			bool IsInsideWidget = Entity.hasComponent<TWireComponent>() ? Entity.getComponent<TWireComponent>().checkMouseOverWire(MousePos) : EntityBound.contains(MousePos);

			// Make sure the update the position of the mouse
			EventComponent.setMousePosition(MousePos);

			// If the mouse it's not on the widget reset the widget state to Normal and skip the rest of the loop
			if (!IsInsideWidget)
			{
				StateComponent.changeState(tcomponents::TStateComponent::NORMAL);

				continue;
			}

			// Handle mouse move event
			!IsInsideWidget ? StateComponent.changeState(tcomponents::TStateComponent::NORMAL) : StateComponent.changeState(tcomponents::TStateComponent::HOVER);

			// Handle mouse press event
			if (Event.type == sf::Event::MouseButtonPressed)
			{
				// Change the Widget state
				StateComponent.changeState(tcomponents::TStateComponent::CLICKED);

				// Fire the click event
#if ENTITY_SYSTEM == NNE
				EventComponent.fireEvent(tcomponents::events::onClick, &Entity, Event);

				// Mouse down event
				EventComponent.fireEvent(tcomponents::events::onMouseDown, &Entity, Event);
#endif
			}
			// Handle mouse up event
			else if (Event.type == sf::Event::MouseButtonReleased)
			{
				// Change the Widget state
				StateComponent.changeState(tcomponents::TStateComponent::CLICKED);

				// Mouse down event
#if ENTITY_SYSTEM == NNE
				EventComponent.fireEvent(tcomponents::events::onMouseUp, &Entity, Event);
#endif				
			}
			// Handle the mouse wheel event
			else if (Event.type == sf::Event::MouseWheelScrolled)
			{
				// Mouse wheel event
#if ENTITY_SYSTEM == NNE
				EventComponent.fireEvent(tcomponents::events::onMouseWheel, &Entity, Event);
#endif

				// If the delta it's more than 0 we scrolled the wheel up, otherwise we scrolled down and call the appropriate event's
#if ENTITY_SYSTEM == NNE
				Event.mouseWheelScroll.delta > 0.f ? EventComponent.fireEvent(tcomponents::events::onMouseWheelUp, &Entity, Event) : EventComponent.fireEvent(tcomponents::events::onMouseWheelDown, &Entity, Event);
#endif
			}
			// Handle key press event
			else if (Event.type == sf::Event::KeyPressed)
			{
				// Key press event
#if ENTITY_SYSTEM == NNE
				EventComponent.fireEvent(tcomponents::events::onKeyPress, &Entity, Event);
#endif
			}
			// Mouse move event
			else
			{
				// Mouse mouse event
#if ENTITY_SYSTEM == NNE
				EventComponent.fireEvent(tcomponents::events::onMouseMove, &Entity, Event);
#endif
			}
		}
	}

	void TManager::initEntities()
	{
		while (mAliveElement < mEntityVector.size())
			mEntityVector[mAliveElement++]->init();
	}

	void TManager::initLastEntity()
	{
		mEntityVector.back()->init();

		mAliveElement++;
	}

	void TManager::update(const sf::Time& ElapsedTime)
	{
		for (std::size_t Index = 0; Index < mAliveElement; ++Index)
			mEntityVector[Index]->update(ElapsedTime);
	}

	void TManager::refresh(const sf::Time& ElapsedTime)
	{
		auto VectorSize = mEntityVector.size();
		mAliveElement = VectorSize;

		for (std::size_t Index = 0; Index < VectorSize; ++Index)
		{
			mEntityVector[Index]->refresh(ElapsedTime);

			if (!mEntityVector[Index]->isAlive())
				--mAliveElement;
		}
	}

	const std::size_t& TManager::getAliveEntities() const
	{
		return mAliveElement;
	}

	std::size_t TManager::getTotalEntities() const
	{
		return mEntityVector.size();
	}

	TManager::EntityIterator TManager::begin()
	{
		return mEntityVector.begin();
	}

	TManager::EntityIterator TManager::end()
	{
		return mEntityVector.end();
	}

	const TEntity::EntityPtr& TManager::operator[](const std::size_t& Index) const
	{
		return mEntityVector[Index];
	}

	TEntity::EntityPtr& TManager::operator[](const std::size_t& Index)
	{
		return mEntityVector[Index];
	}

	std::size_t TManager::getEntityPos(const TEntity::EntityID& IDToSearch)
	{
		if (mEntityVector.size() == 0)
			return NotFound;

		auto VectorSize = mEntityVector.size();
		std::size_t EntityPos = 0;

		// Iterate trough the vector until we find what we are looking for
		while (mEntityVector[EntityPos]->getEntityID() != IDToSearch && ++EntityPos < VectorSize);

		return EntityPos == mEntityVector.size() ? NotFound : EntityPos;
	}

	void TManager::addSorted(TEntity::EntityPtr& Entity)
	{
// 		// If the manager is empty simply add the entity
// 		if (mEntityVector.empty())
// 		{
// 			mEntityVector.push_back({ Entity });
// 
// 			return;
// 		}
// 
// 		// Get the entity size
// 		auto VectorSize = mEntityVector.size();
// 		std::size_t InsertionPos = 0;
// 
// 		// Get the value to compare
// 		auto CompareValue = Entity->getComponentAsPtr<TDrawableComponent>()->getZIndex();
// 
// 		// Find the insert position
// 		while (CompareValue > mEntityVector[InsertionPos]->getComponentAsPtr<TDrawableComponent>()->getZIndex() && ++InsertionPos < VectorSize);
// 
// 		// Shift all the element right of the insertion position to the right
// 		// but first make sure we have enough space for one more element by adding an empty object
// 		mEntityVector.emplace_back();
// 
// 		for (std::size_t Index = VectorSize; Index > InsertionPos; --Index)
// 		{
// 			mEntityVector[Index] = std::move(mEntityVector[Index - 1]);
// 		}
// 
// 		// Put the element in the right place
// 		mEntityVector[InsertionPos] = std::move(Entity);
	}

}

#include "TEventComponent.h"

namespace nne
{
	namespace tcomponents
	{

		TEventComponent::TEventComponent() :
			mMousePos(0.f, 0.f)
		{
		}

		void TEventComponent::init()
		{
		}

		void TEventComponent::update(REFRESH_UPDATE_PARAMETER)
		{
		}

		void TEventComponent::refresh(REFRESH_UPDATE_PARAMETER)
		{
		}

		const events::TEventSlot& TEventComponent::attachEvent(const events::List& EventType, const events::TEvent& EventToAttach)
		{
			// Insert the event in his slot and get a pair of the inserted iterator and whatever it's valid or not
			auto NewIt = mEventsList.emplace(EventType, EventToAttach);

			// If we added the element in the array return the iterator to the currently added element otherwise return end()
			return NewIt.second ? NewIt.first : mEventsList.end();
		}

		void TEventComponent::detachEvent(const events::List& EventType)
		{
			mEventsList.erase(EventType);
		}

#if ENTITY_SYSTEM == NNE
		void TEventComponent::fireEvent(const events::List& EventToFire, const TEntity* Sender, const sf::Event& EventData)
#else
		void TEventComponent::fireEvent(const events::List& EventToFire, const ecs::_TEntity* Sender, const sf::Event& EventData)
#endif
		{
			auto It = mEventsList.find(EventToFire);

			if (It != mEventsList.end())
			{
				It->second(Sender, EventData);
			}
		}

		void TEventComponent::setMousePosition(const sf::Vector2f& NewPos)
		{
			mMousePos = NewPos;
		}

		void TEventComponent::setMousePosition(const float& X, const float& Y)
		{
			mMousePos.x = X;
			mMousePos.y = Y;
		}

		const sf::Vector2f& TEventComponent::getMousePosition() const
		{
			return mMousePos;
		}

	}
}
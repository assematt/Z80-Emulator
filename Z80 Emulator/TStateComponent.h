#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "IComponent.h"
#include "TEntity.h"
#include "TWidget.h"

namespace nne
{
	namespace tcomponents
	{
	
		class TStateComponent : public nne::IComponent
		{
		public:

			enum TState : unsigned char
			{
				NORMAL,
				HOVER,
				SELECTED,
				CLICKED,
				DISABLED,

				NUMBER_OF_STATE
			};
			
			void init() override {}

			void update(const sf::Time& ElapsedTime) override {}

			void refresh(const sf::Time& ElapsedTime) override {}

			/// Change component internal state
			void changeState(const TState& NewState)
			{
				mState = NewState;
			}

			/// Get the current state of the component
			const TState& getState() const
			{
				return mState;
			}

		private:
			TState				mState;
		};

	}
}
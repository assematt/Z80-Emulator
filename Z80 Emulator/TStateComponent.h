#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include INCLUDE_COMPONENT_CLASS
#include INCLUDE_ENTITY_CLASS
#include "TWidget.h"

namespace nne
{
	namespace tcomponents
	{
	
		class TStateComponent : BASE_COMPONENT_CLASS
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

			void update(REFRESH_UPDATE_PARAMETER) override {}

			void refresh(REFRESH_UPDATE_PARAMETER) override {}

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
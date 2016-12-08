#pragma once

#include <functional>
#include <array>

namespace nne
{
	namespace tgui
	{
		class TStateManager
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

			TStateManager() :
				mPreviousState(TState::NORMAL),
				mCurrentState(TState::NORMAL)
			{
			}

			const TState& getCurrentState()
			{
				return mCurrentState;
			}

			const TState& getPreviousState()
			{
				return mPreviousState;
			}

		protected:
			/// When the widget change state
			virtual void onStateNormal() {}
			virtual void onStateHover() {}
			virtual void onStateSelected() {}
			virtual void onStateClicked() {}
			virtual void onStateDisabled() {}

			void changeState(const TState& NewState)
			{
				mPreviousState = mCurrentState;

				mCurrentState = NewState;
			}

		private:
			TState mCurrentState;
			TState mPreviousState;

			std::array<std::function<void()>, TState::NUMBER_OF_STATE> mStateSlots;
		};
	}
}
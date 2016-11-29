#pragma once

#include <SFML/Config.hpp>

namespace nne
{
	namespace tgui
	{
		struct TWidgetState 
		{
			/// Widget states
 			enum class States : sf::Uint8 
			{
				NORMAL,
				CLICKED,
				HOVER,
				SELECTED,
				DISABLED,
			};

			/// Default constructor
			TWidgetState();

			/// Callback function that get called everytime the widget changes state
			virtual void onNormalState() = 0;
			virtual void onClickedState() = 0;
			virtual void onHoverState() = 0;
			virtual void onSelectedState() = 0;
			virtual void onDisabledState() = 0;

			/// Get/Set the state of the widget
			void setWidgetState(const States& WidgetState);
			const States& getWidgetState() const;

		private:
			States mWidgetState;
		};
	}
}
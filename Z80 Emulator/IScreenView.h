#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <future>
#include <vector>

#include "TGuiWidget.h"
#include "TWidgetsVector.h"

namespace nne
{
	namespace tgui
	{
		class TGuiManager;

		class IScreenView : public TWidgetsVector
		{
		public:
			using UniquePtr = std::unique_ptr<IScreenView>;
			using SharedPtr = std::shared_ptr<IScreenView>;
			using ScreenID = std::size_t;

			IScreenView();
			virtual ~IScreenView() = default;

			/// Virtual function that it's used by derived class to internally setup the menu
			virtual void init() = 0;

			/// Handle the event passed by the GuiManager
			void handleEvent(const sf::Event& Event);

			/// updates every widget in the container
			void update(const sf::Time& ElapsedTime);

			/// refreshes every widget in the container
			void refresh(const sf::Time& ElapsedTime);

			/// draw all the widgets in the container
			void draw();

		protected:
			bool checkMouseIsInWidget(const sf::FloatRect& WidgetBound, const sf::Vector2i Mouse);
			
		protected:
			TGuiManager*	mParentManager;

			friend class TGuiManager;
		};
	}
}

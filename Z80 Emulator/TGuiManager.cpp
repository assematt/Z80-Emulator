#include "TGuiManager.h"

#include <SFML/Window/Mouse.hpp>

namespace nne
{
	namespace tgui
	{

		TGuiManager::TGuiManager() :
			mLastAddedPosition(0),
			mNextScene(IScene::Same)
		{
		}

		void TGuiManager::removeWidget(const TWidget::ID& WidgetID)
		{
			auto WidgetToRemove = getWidgetPos(WidgetID);

			mWidgetsContainer.erase(mWidgetsContainer.begin() + WidgetToRemove);
		}

		TWidget::Ptr TGuiManager::getWidget(const TWidget::ID& WidgetID) const
		{
			for (auto& Widget : mWidgetsContainer)
				if (Widget->getID() == WidgetID)
					return Widget;

			// If we got to this point return an empty pointer
			return TWidget::Ptr();
		}

		TWidget::Ptr TGuiManager::getWidget(const std::string& WidgetName) const
		{
			for (auto& Widget : mWidgetsContainer)
				if (Widget->getName() == WidgetName)
					return Widget;

			// If we got to this point return an empty pointer
			return TWidget::Ptr();
		}

		std::size_t TGuiManager::getWidgetPos(const TWidget::ID& WidgetID) const
		{
			std::size_t WidgetPos = 0;

			while (mWidgetsContainer[WidgetPos]->getID() != WidgetID && ++WidgetPos < mWidgetsContainer.size());

			return WidgetPos;
		}

		std::size_t TGuiManager::getWidgetPos(const std::string& WidgetName) const
		{
			std::size_t WidgetPos = 0;

			while (mWidgetsContainer[WidgetPos]->getName() != WidgetName && ++WidgetPos < mWidgetsContainer.size());

			return WidgetPos;
		}

		const TWidget::Ptr& TGuiManager::getLastAdded()
		{
			return mWidgetsContainer[mLastAddedPosition];
		}

		const TWidget::Ptr& TGuiManager::getFrontWidget()
		{
			return mWidgetsContainer.back();
		}

		const TWidget::Ptr& TGuiManager::getBackWidget()
		{
			return mWidgetsContainer.front();
		}

		std::vector<TWidget::Ptr>::iterator TGuiManager::begin()
		{
			return mWidgetsContainer.begin();
		}

		std::vector<TWidget::Ptr>::iterator TGuiManager::end()
		{
			return mWidgetsContainer.end();
		}

		std::vector<TWidget::Ptr>::const_iterator TGuiManager::cbegin()
		{
			return mWidgetsContainer.cbegin();
		}

		std::vector<TWidget::Ptr>::const_iterator TGuiManager::cend()
		{
			return mWidgetsContainer.cend();
		}

		std::vector<TWidget::Ptr>::reverse_iterator TGuiManager::rbegin()
		{
			return mWidgetsContainer.rbegin();
		}

		std::vector<TWidget::Ptr>::reverse_iterator TGuiManager::rend()
		{
			return mWidgetsContainer.rend();
		}

		std::vector<TWidget::Ptr>::const_reverse_iterator TGuiManager::crbegin()
		{
			return mWidgetsContainer.crbegin();
		}

		std::vector<TWidget::Ptr>::const_reverse_iterator TGuiManager::crend()
		{
			return mWidgetsContainer.crend();
		}

		TWidget::Ptr& TGuiManager::operator[](const int Index)
		{
			return mWidgetsContainer[Index];
		}

		const TWidget::Ptr& TGuiManager::operator[](const int Index) const
		{
			return mWidgetsContainer[Index];
		}

		void TGuiManager::update(const sf::Time& ElapsedTime)
		{
			auto WidgetsNumber = mWidgetsContainer.size();
			for (auto Index = 0u; Index < WidgetsNumber; ++Index)
			{
				mWidgetsContainer[Index]->update(ElapsedTime);

				if (!mWidgetsContainer[Index]->isAlive())
				{
					mWidgetsContainer.erase(mWidgetsContainer.begin() + Index);
					mWidgetsZIndex.erase(mWidgetsZIndex.begin() + Index);

					--WidgetsNumber;
					--Index;
				}
			}
		}

		nne::IScene::ID TGuiManager::processEvents(const sf::Event& Event, const sf::RenderWindow& EventWindow)
		{
			// Loop all the widget until we find an object to fire an event on
			// We loop in revers order (since we want to check the widget with the highest ZIndex first)
			bool EventFound = false;

			auto WidgetsNumber = mWidgetsContainer.size();

			while (WidgetsNumber-- > 0)
			{
				// First get a ref to the shared_ptr<TWidget> inside the reverse iterator
				//auto& Widget = **WidgetIterator;
				auto& Widget = *mWidgetsContainer[WidgetsNumber];

				// By default reset the state of the widget
				Widget.resetState();

				// If the widget doesn't allow input skip this loop cycle
				if (!Widget.isEnabled() || !Widget.isVisible() || EventFound)
					continue;

				// Get the bound of that object
				auto& WidgetBound = Widget.getGlobalBound();

				// Establish if the mouse it's above the widget
				auto MousePos = EventWindow.mapPixelToCoords(sf::Mouse::getPosition(EventWindow));
				bool IsInsideWidget = WidgetBound.contains(MousePos);

				// If the mouse it's not on the widget skip the rest of the loop
 				if (!IsInsideWidget)
					continue;

				// See if the widget is toggle able
				const bool& IsToggleable = Widget.isToggleable();

				// See if the widget is enabled
				const bool& IsEnabled = Widget.isEnabled();

				// See if the widget is selected
				const bool& IsSelected = Widget.isSelected();

				// See if the widget is being hovered
				const bool& IsHovered = Widget.isHovered();

				// Handle mouse press event
				if (Event.type == sf::Event::MouseButtonPressed)
				{
					// Change the Widget state
					//Widget.changeState(TWidget::CLICKED);

					// Fire the click event
					Widget.fireEvent(events::onClick, &Widget, Event);

					// Mouse down event
					Widget.fireEvent(events::onMouseDown, &Widget, Event);

					EventFound = true;
				}
				// Handle mouse up event
				else if (Event.type == sf::Event::MouseButtonReleased)
				{
					// Change the Widget state
					Widget.changeState(TWidget::CLICKED);

					// Mouse down event
					Widget.fireEvent(events::onMouseUp, &Widget, Event);

					EventFound = true;
				}
				// Handle the mouse wheel event
				else if (Event.type == sf::Event::MouseWheelScrolled)
				{
					// Mouse wheel event
					Widget.fireEvent(events::onMouseWheel, &Widget, Event);

					// If the delta it's more than 0 we scrolled the wheel up, otherwise we scrolled down and call the appropriate event's
					Event.mouseWheelScroll.delta > 0.f ? Widget.fireEvent(events::onMouseWheelUp, &Widget, Event) : Widget.fireEvent(events::onMouseWheelDown, &Widget, Event);

					EventFound = true;
				}
				// Handle key press event
				else if (Event.type == sf::Event::KeyPressed)
				{
					// Key press event
					Widget.fireEvent(events::onKeyPress, &Widget, Event);

					EventFound = true;
				}
				// Mouse move event
				else
				{
					// Mouse mouve event
					Widget.fireEvent(events::onMouseMove, &Widget, Event);

					Widget.changeState(TWidget::HOVER);

					EventFound = true;
				}
			}

			return mNextScene;
		}

		void TGuiManager::changeScene(const IScene::ID& NewScene) const
		{
			mNextScene = NewScene;
		}

	}
}
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
			for (auto& Widget : mWidgetsContainer)
				Widget->update(ElapsedTime);
		}

		nne::IScene::ID TGuiManager::processEvents(const sf::Event& Event, const sf::RenderWindow& EventWindow)
		{
			// By default we return the same scene
			//mNextScene = IScene::Same;

			// Loop all the widget until we find an object to fire an event on
			// We loop in revers order (since we want to check the widget with the highest ZIndex first)
			bool EventFire = false;
			for (auto& WidgetIterator = rbegin(); WidgetIterator != rend(); ++WidgetIterator)
			{
				// First get a ref to the shared_ptr<TWidget> inside the reverse iterator
				auto& Widget = **WidgetIterator;

				// If the widget doesn't allow input skip this loop cycle
				if (!Widget.isEnabled())
					continue;

				// Get the bound of that object
				auto& WidgetBound = Widget.getGlobalBound();

				// Establish if the mouse it's above the widget
				bool IsInsideWidget = WidgetBound.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(EventWindow)));

				// See if the widget is toggle able
				const bool& IsToggleable = Widget.isToggleable();

				// See if the widget is enabled
				const bool& IsEnabled = Widget.isEnabled();

				// See if the widget is selected
				const bool& IsSelected = Widget.isSelected();

				// See if the widget is being hovered
				const bool& IsHovered = Widget.isHovered();

				// Handle mouse move event
				!IsInsideWidget ? Widget.changeState(TWidget::NORMAL) : Widget.changeState(TWidget::HOVER);

				// Handle mouse press event
				if (Event.type == sf::Event::MouseButtonPressed)

					if (!IsInsideWidget)
					{
						Widget.changeState(TWidget::NORMAL);
					}
					else
					{
						Widget.changeState(TWidget::CLICKED);

						Widget.fireEvent(events::CLICKED, &Widget, Event);
					}

					//!IsInsideWidget ? Widget.changeState(TWidget::NORMAL) : Widget.changeState(TWidget::CLICKED);

			}

			return mNextScene;
		}

		void TGuiManager::changeScene(const IScene::ID& NewScene) const
		{
			mNextScene = NewScene;
		}

	}
}
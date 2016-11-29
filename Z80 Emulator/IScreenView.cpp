#include "IScreenView.h"
#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{

		IScreenView::IScreenView() :
			mParentManager(nullptr)
		{
		}

		void IScreenView::handleEvent(const sf::Event& Event)
		{
			// We iterate through all the widget until we fire an event
			bool EventFired = false;

			// Iterate over all the widget to check for event
			for (auto& WidgetIterator = rbegin(); WidgetIterator != rend() && !EventFired; ++WidgetIterator)
			{
				// Get a ref to the widget the widget from the render struct
				auto& Widget = *WidgetIterator;

				// Skip the all event handling for this widget if it doesn't accept input
				if (!Widget->isInputEnabled())
					continue;

				// Check the mouse events only if the mouse is over a widget
				if (checkMouseIsInWidget(Widget->getGlobalBounds(), { Event.mouseButton.x, Event.mouseButton.y }))
				{
					
					/*
					EVENT TO IMPLEMENT
					_OnMouseEnter,
					_OnMouseLeave,
					*/

					switch (Event.type)
					{
						// If we clicked on the widget
						case sf::Event::MouseButtonPressed:
						{
							// Raise the signal
							Widget->raiseSignal(tevent::_OnMouseClick, Event.mouseButton);

							// Raise the signal
							Widget->raiseSignal(tevent::_OnMouseDown, Event.mouseButton);

							// We fired an event so we can exit the loop
							EventFired = true;
						} break;

						// If we moved the mouse over the widget
						case sf::Event::MouseMoved:
						{
							// Raise the signal
							Widget->raiseSignal(tevent::_OnMouseMove, Event.mouseButton);

							// We fired an event so we can exit the loop
							EventFired = true;
						} break;

						// If we moved the mouse over the widget
						case sf::Event::MouseButtonReleased:
						{
							// Raise the signal
							Widget->raiseSignal(tevent::_OnMouseUp, Event.mouseButton);

							// We fired an event so we can exit the loop
							EventFired = true;
						} break;
					}
				}
			}
		}

		void IScreenView::update(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : (*this))
				Widget->update(ElapsedTime);
		}

		void IScreenView::refresh(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : (*this))
				Widget->refresh(ElapsedTime);
		}

		void IScreenView::draw()
		{
			for (auto& Widget : (*this))
				mParentManager->getRenderingWindow().draw(Widget->getComponent<TDrawableComponent>());
		}

		bool IScreenView::checkMouseIsInWidget(const sf::FloatRect& WidgetBound, const sf::Vector2i Mouse)
		{
			return WidgetBound.contains(static_cast<sf::Vector2f>(Mouse));
		}

	}
}



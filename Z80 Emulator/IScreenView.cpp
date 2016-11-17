#include "IScreenView.h"
#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{

		IScreenView::IScreenView() :
			mParentManager(nullptr),
			mPosition({.0f, .0f})
		{
		}

		void IScreenView::handleEvent(const sf::Event& Event)
		{
			// We iterate through all the widget until we fire an event
			bool EventFired = false;

			// Iterate over all the widget to check for event
			for (auto& WidgetIterator = mWidgetsContainer.rbegin(); WidgetIterator != mWidgetsContainer.rend() && !EventFired; ++WidgetIterator)
			{
				// Get a ref to the widget the widget from the render struct
				auto& Widget = WidgetIterator->GetWidget();

				if (Event.type == sf::Event::MouseButtonPressed && Widget->isInputEnabled() && checkMouseClick(Widget->getGlobalBounds(), { Event.mouseButton.x, Event.mouseButton.y }))
				{
					// Raise the signal
					Widget->raiseSignal(tevent::_OnMouseClick, Event.mouseButton);

					// We fired an event so we can exit the loop
					EventFired = true;
				}
			}
		}

		void IScreenView::removeWidget(std::size_t Index)
		{
			mWidgetsContainer.erase(mWidgetsContainer.begin() + Index);
		}

		const TGuiWidget::UniquePtr& IScreenView::getWidget(const std::size_t Index) const
		{
			return mWidgetsContainer[Index].mWidget;
		}

		void IScreenView::update(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget.mWidget->update(ElapsedTime);
			}
		}

		void IScreenView::refresh(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget.mWidget->refresh(ElapsedTime);
			}
		}

		void IScreenView::draw()
		{
			for (auto& WidgetIterator : mWidgetsContainer)
			{
				mParentManager->getRenderingWindow().draw(*WidgetIterator.GetWidget()->getComponentAsPtr<TDrawableComponent>());
			}
		}

		void IScreenView::addLoadingScreen(std::unique_ptr<ILoadingScreen>& LoadingScreen)
		{
			mLoadingScreen = std::move(LoadingScreen);
		}

		std::vector<IScreenView::TWdigetRenderStrcut>::iterator IScreenView::begin()
		{
			return mWidgetsContainer.begin();
		}

		std::vector<IScreenView::TWdigetRenderStrcut>::iterator IScreenView::end()
		{
			return mWidgetsContainer.end();
		}

		TGuiWidget::UniquePtr& IScreenView::operator[](const int Index)
		{
			return mWidgetsContainer[Index].mWidget;
		}

		const TGuiWidget::UniquePtr& IScreenView::operator[](const int Index) const
		{
			return mWidgetsContainer[Index].mWidget;
		}

		const sf::Vector2f IScreenView::getReferencePointPosition(TReferencePoint RefPoint /*= TReferencePoint::CENTER*/)
		{
			sf::Vector2f& WindowSize = static_cast<sf::Vector2f>(mParentManager->getRenderingWindow().getSize());

			switch (RefPoint)
			{
			case nne::tgui::TReferencePoint::LEFT_TOP:
				return { 0.f, 0.f };
			case nne::tgui::TReferencePoint::CENTER_TOP:
				return { WindowSize.x / 2, 0.f };
			case nne::tgui::TReferencePoint::RIGHT_TOP:
				return { WindowSize.x, 0.f };

			case nne::tgui::TReferencePoint::LEFT_CENTER:
				return { 0.f, WindowSize.y / 2 };
			case nne::tgui::TReferencePoint::CENTER:
				return { WindowSize.x / 2, WindowSize.y / 2 };
			case nne::tgui::TReferencePoint::RIGHT_CENTER:
				return { 0.f, WindowSize.y / 2 };

			case nne::tgui::TReferencePoint::LEFT_BOTTOM:
				return { 0.f, WindowSize.y };
			case nne::tgui::TReferencePoint::CENTER_BOTTOM:
				return { WindowSize.x / 2, WindowSize.y };
			case nne::tgui::TReferencePoint::RIGHT_BOTTOM:
				return { WindowSize.x, WindowSize.y };
			}
		}

		bool IScreenView::checkMouseClick(const sf::FloatRect& WidgetBound, const sf::Vector2i Mouse)
		{
			return WidgetBound.contains(static_cast<sf::Vector2f>(Mouse));
		}

		std::unique_ptr<nne::tgui::ILoadingScreen>& IScreenView::getLoadingScreen()
		{
			return mLoadingScreen;
		}

	}
}



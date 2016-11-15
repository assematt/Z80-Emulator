#include "IScreenView.h"

namespace nne
{
	namespace tgui
	{

		IScreenView::IScreenView() :
			mLoadingScreen(nullptr),
			mParentManager(nullptr),
			mPosition({.0f, .0f})
		{
		}

		void IScreenView::HandleEvent(const sf::Event& Event)
		{
			// We iterate through all the widget until we fire an event
			bool EventFired = false;

			// Iterate over all the widget to check for event
			for (auto& WidgetIterator = mWidgetsContainer.rbegin(); WidgetIterator != mWidgetsContainer.rend() && !EventFired; ++WidgetIterator)
			{
				// Get a ref to the widget the widget from the render struct
				auto& Widget = WidgetIterator->GetWidget();

				if (Event.type == sf::Event::MouseButtonPressed && Widget->IsInputEnabled() && CheckMouseClick(Widget->GetWidgetBound(), { Event.mouseButton.x, Event.mouseButton.y }))
				{
					// Raise the signal
					Widget->RaiseSignal(tevent::_OnMouseClick, Event.mouseButton);

					// We fired an event so we can exit the loop
					EventFired = true;
				}
			}
		}

		void IScreenView::RemoveWidget(std::size_t Index)
		{
			mWidgetsContainer.erase(mWidgetsContainer.begin() + Index);
		}

		const TGuiWidget::UniquePtr& IScreenView::GetWidget(const std::size_t Index) const
		{
			return mWidgetsContainer[Index].mWidget;
		}

		void IScreenView::SetLoadingScreen(std::unique_ptr<ILoadingScreen>& LoadingScreen)
		{
			mLoadingScreen = std::move(LoadingScreen);
		}

		std::unique_ptr<nne::ILoadingScreen>& IScreenView::GetLoadingScreen()
{
			return mLoadingScreen;
		}

		void IScreenView::Update(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget.mWidget->Update(ElapsedTime);
			}
		}

		void IScreenView::Refresh(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget.mWidget->Refresh(ElapsedTime);
			}
		}

		void IScreenView::Draw()
		{
			for (auto& Widget : mWidgetsContainer)
			{
				TGuiWindow::GetInstance().draw(*Widget.mWidget);
			}
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

		const sf::Vector2f IScreenView::GetReferencePointPosition(TReferencePoint RefPoint /*= TReferencePoint::CENTER*/)
		{
			sf::Vector2f& WindowSize = static_cast<sf::Vector2f>(TGuiWindow::GetInstance().getSize());

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

		bool IScreenView::CheckMouseClick(const sf::FloatRect& WidgetBound, const sf::Vector2i Mouse)
		{
			return WidgetBound.contains(static_cast<sf::Vector2f>(Mouse));
		}

	}
}



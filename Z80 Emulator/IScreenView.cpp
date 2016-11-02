#include "IScreenView.h"

namespace nne
{
	namespace tgui
	{

		void IScreenView::RemoveWidget(std::size_t Index)
		{
			mWidgetsContainer.erase(mWidgetsContainer.begin() + Index);
		}

		const TGuiWidget::UniquePtr& IScreenView::GetWidget(const std::size_t Index) const
		{
			return mWidgetsContainer[Index];
		}

		void IScreenView::Update(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget->Update(ElapsedTime);
			}
		}

		void IScreenView::Refresh(const sf::Time& ElapsedTime)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget->Refresh(ElapsedTime);
			}
		}

		void IScreenView::Draw()
		{
			for (auto& Widget : mWidgetsContainer)
			{
				TGuiWindow::GetInstance().draw(*Widget);
			}
		}

		std::vector<TGuiWidget::UniquePtr>::iterator IScreenView::begin()
		{
			return mWidgetsContainer.begin();
		}

		std::vector<TGuiWidget::UniquePtr>::iterator IScreenView::end()
		{
			return mWidgetsContainer.end();
		}

		TGuiWidget::UniquePtr& IScreenView::operator[](const int Index)
		{
			return mWidgetsContainer[Index];
		}

		const TGuiWidget::UniquePtr& IScreenView::operator[](const int Index) const
		{
			return mWidgetsContainer[Index];
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

		bool IScreenView::CheckMouseClick(TGuiWidget::UniquePtr& Widget, const sf::Vector2i Mouse)
		{
			auto& WidgetPosition = Widget->GetComponentAsPtr<TTransformable>()->GetPosition();
			auto& WidgetSize = Widget->GetComponentAsPtr<TTransformable>()->GetSize();

			sf::FloatRect WidgetCoordinate(WidgetPosition, static_cast<sf::Vector2f>(WidgetSize));

			return WidgetCoordinate.contains(static_cast<sf::Vector2f>(Mouse));
		}

	}
}



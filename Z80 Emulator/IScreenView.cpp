#include "IScreenView.h"

namespace nne
{
	namespace tgui
	{
		void IScreenView::AddWidget(TGuiWidget::UniquePtr& Widget)
		{
			mWidgetsContainer.push_back(std::move(Widget));
		}

		void IScreenView::RemoveWidget(std::size_t Index)
		{
			mWidgetsContainer.erase(mWidgetsContainer.begin() + Index);
		}

		const TGuiWidget::UniquePtr& IScreenView::GetWidget(const std::size_t Index) const
		{
			return mWidgetsContainer[Index];
		}

		void IScreenView::Update(sf::Time& ElapsedTime)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget->Update(ElapsedTime);
			}
		}

		void IScreenView::Refresh(sf::Time& ElapsedTime)
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

		void IScreenView::SetPosition(sf::Vector2f& NewPosition, TReferencePoint RefPoint /*= TReferencePoint::CENTER*/)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget->GetComponentAsPtr<TTransformable>()->Move(NewPosition);
			}
		}

		void IScreenView::SetPosition(float NewPositionX, float NewPositionY, TReferencePoint RefPoint /*= TReferencePoint::CENTER*/)
		{
			for (auto& Widget : mWidgetsContainer)
			{
				Widget->GetComponentAsPtr<TTransformable>()->Move(NewPositionX, NewPositionY);
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

		bool IScreenView::CheckMouseClick(TGuiWidget::UniquePtr& Widget, const sf::Vector2i Mouse)
		{
			auto& WidgetPosition = Widget->GetComponentAsPtr<TTransformable>()->GetPosition();
			auto& WidgetSize = Widget->GetComponentAsPtr<TTransformable>()->GetSize();

			sf::FloatRect WidgetCoordinate(WidgetPosition, static_cast<sf::Vector2f>(WidgetSize));

			return WidgetCoordinate.contains(static_cast<sf::Vector2f>(Mouse));
		}

	}
}



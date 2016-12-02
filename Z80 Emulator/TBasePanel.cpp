#include "TBasePanel.h"

namespace nne
{
	namespace tgui
	{
		
		TBasePanel::TBasePanel():
			mRotation(0),
			mPosition(0.f, 0.f),
			mScale(1.f, 1.f)
		{
		}

		void TBasePanel::removeWidget(std::size_t Index)
		{
			// Swap the element to remove with the last element
			std::swap(mChildWidget[Index], mChildWidget.back());

			// remove the last element
			mChildWidget.pop_back();
		}

		void TBasePanel::setPosition(const sf::Vector2f& Position)
		{
			mPosition = Position;

			for (auto Child : mChildWidget)
				Child->getComponentAsPtr<TDrawableComponent>()->move(Position);
		}

		void TBasePanel::setRotation(const float& Angle)
		{
			mRotation = Angle;

			for (auto Child : mChildWidget)
				Child->getComponentAsPtr<TDrawableComponent>()->rotate(Angle);
		}

		void TBasePanel::setScale(const sf::Vector2f& Factors)
		{
			mScale = Factors;

			for (auto Child : mChildWidget)
				Child->getComponentAsPtr<TDrawableComponent>()->scale(Factors);
		}

		void TBasePanel::setOrigin(const sf::Vector2f& Origin)
		{
			for (auto Child : mChildWidget)
				Child->getComponentAsPtr<TDrawableComponent>()->setOrigin(Origin);
		}

		void TBasePanel::move(const sf::Vector2f& Offset)
		{
			for (auto Child : mChildWidget)
				Child->getComponentAsPtr<TDrawableComponent>()->move(Offset);
		}

		void TBasePanel::rotate(const float& Angle)
		{
			for (auto Child : mChildWidget)
				Child->getComponentAsPtr<TDrawableComponent>()->rotate(Angle);
		}

		void TBasePanel::scale(const sf::Vector2f& Factor)
		{
			for (auto Child : mChildWidget)
				Child->getComponentAsPtr<TDrawableComponent>()->scale(Factor);
		}
		
		void TBasePanel::updateChildWidgetTransformation()
		{
			move(mPosition);
			rotate(mRotation);
			scale(mScale);
		}

	}
}
#pragma once

#include "IComponent.h"
#include "TWidget.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{
		
		class TBasePanel
		{
		public:
		
			using UniquePtr = std::unique_ptr<TBasePanel>;
			using SharedPtr = std::shared_ptr<TBasePanel>;

			TBasePanel();

			template <class T>
			void addWidget(T* Widget);

			/// Function to remove a widget
			void removeWidget(std::size_t Index);

			/// Set the position for the widgets managed by this panel 
			void setPosition(const sf::Vector2f& Position);

			/// Set the rotation for the widgets managed by this panel
			void setRotation(const float& Angle);

			/// Set the scale for the widgets managed by this panel
			void setScale(const sf::Vector2f& Factors);

			/// Set the origin for the widgets managed by this panel
			void setOrigin(const sf::Vector2f& Origin);
			
			/// Move the widgets managed by this panel
			void move(const sf::Vector2f& Offset);

			/// Rotate the widgets managed by this panel
			void rotate(const float& Angle);

			/// Scale the widgets managed by this panel
			void scale(const sf::Vector2f& Factor);

			/// Update the widget transformation
			void updateChildWidgetTransformation();
			
		private:
			float					mRotation;
			sf::Vector2f			mPosition;
			sf::Vector2f			mScale;
			std::vector<TWidget*>	mChildWidget;
		};

		template <class T>
		void nne::tgui::TBasePanel::addWidget(T* Widget)
		{
			// Set the parent and position value
			Widget->mParentPanel = this;
			Widget->mParentPanelPosition = mChildWidget.size();

			Widget->getComponentAsPtr<TDrawableComponent>()->move(mPosition);
			Widget->getComponentAsPtr<TDrawableComponent>()->rotate(mRotation);
			Widget->getComponentAsPtr<TDrawableComponent>()->scale(mScale);

			mChildWidget.push_back(Widget);
		}

	}
}
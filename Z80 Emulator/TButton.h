#pragma once

#include <SFML/Graphics/Text.hpp>
#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TButton : public TWidget
		{
		public:
			using Ptr = std::shared_ptr<TButton>;

			const sf::Color NormalColor = { 0, 35, 64 };
			const sf::Color HoverColor = { 0, 28, 52 };
			const sf::Color ClickedColor = { 0, 21, 38 };
			const sf::Color SelectedColorColor = { 0, 70, 128 };
			const sf::Color DisabledColorColor = { 19, 19, 19 };

			TButton();

			/// Set some of the widget properties
			void setCharacterSize(const std::size_t& CharacterSize);
			std::size_t getCharacterSize();

			void setCaption(const sf::String& Caption);
			const sf::String& getCaption() const;

			void setColor(const sf::Color& Color);
			const sf::Color& getColor() const;

			void setPadding(const sf::Vector2u& Padding);
			const sf::Vector2u& getPadding() const;

		protected:
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;


			virtual void onStateNormal() override;


			virtual void onStateHover() override;


			virtual void onStateSelected() override;


			virtual void onStateClicked() override;


			virtual void onStateDisabled() override;

		private:
			/// Get the size of the displayed text string
			sf::Vector2f getTextSize();

		private:
			sf::Text		mText;
			sf::Vector2u	mTextPadding;
		};
	}
}
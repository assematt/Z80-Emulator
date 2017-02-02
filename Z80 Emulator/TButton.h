#pragma once

#include <SFML/Graphics/Text.hpp>
#include "TComplexText.h"
#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TButton : public TWidget
		{
		public:
			using Ptr = std::shared_ptr<TButton>;

			const sf::Color NormalColor = { 0, 21, 38 };
			const sf::Color HoverColor = { 0, 28, 52 }/*{ 0, 28, 52 }*/;
			const sf::Color ClickedColor = { 0, 105, 191 }/*{ 0, 21, 38 }*/;
			const sf::Color SelectedColorColor = { 0, 35, 64 }/*{ 0, 70, 128 }*/;
			const sf::Color DisabledColorColor = { 19, 19, 19 };

			TButton();
			virtual ~TButton() = default;

			/// Set some of the widget properties
			void setCharacterSize(const std::size_t& CharacterSize);
			std::size_t getCharacterSize();

			void setCaption(const sf::String& Caption);
			const sf::String& getCaption() const;

			void setFillColor(const sf::Color& Color, const bool& OverrideOtherColor = true);
			const sf::Color& getFillColor() const;

			void setPadding(const sf::Vector2u& Padding);
			const sf::Vector2u& getPadding() const;

		protected:
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
			
			/// Update the button looks
			virtual void update(const sf::Time& ElapsedTime) override;

		private:
			/// Get the size of the displayed text string
			sf::Vector2f getTextSize(const bool& IncludePadding = false);

		protected:
			TComplexText	mText;
			sf::Vector2u	mTextPadding;
		};
	}
}
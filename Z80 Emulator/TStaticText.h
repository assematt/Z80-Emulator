#pragma once

#include <SFML/Graphics/Text.hpp>
#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TStaticText : public TWidget
		{
		public:

			using Ptr = std::shared_ptr<TStaticText>;

			TStaticText();

			/// Set some of the widget properties
			void setCharacterSize(const std::size_t& CharacterSize);
			std::size_t getCharacterSize();

			void setCaption(const sf::String& Caption);
			const sf::String& getCaption() const;

			void setColor(const sf::Color& Color);
			const sf::Color& getColor() const;

		protected:
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

		private:
			sf::Text	mText;
		};
	}
}
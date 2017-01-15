#pragma once

#include <SFML/Graphics/Text.hpp>
#include "TButton.h"
#include "TTextComponent.h"

namespace nne
{
	namespace tgui
	{
		class TMenuButton : public TButton
		{
		public:
			using Ptr = std::shared_ptr<TMenuButton>;

			const sf::Color NormalColor = { 0, 35, 64 };
			const sf::Color HoverColor = { 0, 28, 52 };
			const sf::Color ClickedColor = { 0, 21, 38 };
			const sf::Color SelectedColorColor = { 0, 70, 128 };
			const sf::Color DisabledColorColor = { 19, 19, 19 };

			/// Set the fill color of one single character text
			void setCharacterFillColor(const sf::Color& Color, const std::size_t CharacterPos);

			/// Set the outline color of one single character text
			void setCharacterOutlineColor(const sf::Color& Color, const std::size_t CharacterPos);

			/// Set the strike-through fill color
			void setStrikeThroughFillColor(const sf::Color& Color);

			/// Set the strike-through outline color
			void setStrikeThroughOutlineColor(const sf::Color& Color);
						
		protected:

			/// Refresh the look of the widget
			virtual void update(const sf::Time& ElapsedTime) override;

		};
	}
}
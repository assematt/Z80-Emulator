#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TButton.h"

namespace nne
{
	namespace tgui
	{
		class TImageButton : public TButton
		{
		public:
			using Ptr = std::shared_ptr<TImageButton>;

			const sf::Color NormalColor = { 0, 35, 64 };
			const sf::Color HoverColor = { 0, 70, 128 };
			const sf::Color ClickedColor = { 0, 105, 191 };
			const sf::Color SelectedColorColor = { 0, 105, 191 };
			const sf::Color DisabledColorColor = { 19, 19, 19 };
			
			/// Add a small image in the desired position (by default {0.f, 0.f})
			void addImage(const sf::Texture& Image, const sf::Vector2f& ImagePosition = sf::Vector2f());

		protected:

			/// Refresh the look of the widget
			virtual void update(const sf::Time& ElapsedTime) override;

			/// Draw the widget
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

		private:
			sf::Sprite mButtonImage;
		};
	}
}
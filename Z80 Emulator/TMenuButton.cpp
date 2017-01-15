#include "TMenuButton.h"

namespace nne
{
	namespace tgui
	{
		
		void TMenuButton::setCharacterFillColor(const sf::Color& Color, const std::size_t CharacterPos)
		{
			mText.setCharacterFillColor(Color, CharacterPos);
		}

		void TMenuButton::setCharacterOutlineColor(const sf::Color& Color, const std::size_t CharacterPos)
		{
			mText.setCharacterOutlineColor(Color, CharacterPos);
		}

		void TMenuButton::setStrikeThroughFillColor(const sf::Color& Color)
		{
			mText.setStrikeThroughFillColor(Color);
		}

		void TMenuButton::setStrikeThroughOutlineColor(const sf::Color& Color)
		{
			mText.setStrikeThroughOutlineColor(Color);
		}

		void TMenuButton::update(const sf::Time& ElapsedTime)
		{
			// Get the current widget state
			const auto& State = getState();

			switch (State)
			{
			case TWidget::NORMAL:
			{
				TWidget::setColor(sf::Color::Transparent);
				TButton::setFillColor(sf::Color::White, false);
			} break;
			case TWidget::HOVER:
			{
				TWidget::setColor(sf::Color::Transparent);
				TButton::setFillColor(sf::Color::Black, false);
			} break;
			case TWidget::SELECTED:
			{
				TWidget::setColor({ 0, 170, 0 });
			} break;
			case TWidget::CLICKED:
			{
				TWidget::setColor({ 0, 170, 0 });
			} break;
			case TWidget::DISABLED:
			{
				TWidget::setColor(sf::Color::Transparent);
				TButton::setFillColor({ 150u, 150u, 150u }, false);
			} break;
			}
		}


	}
}
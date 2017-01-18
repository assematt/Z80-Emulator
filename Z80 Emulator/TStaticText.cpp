#include "TStaticText.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{

		TStaticText::TStaticText()
		{
			/// Set the font
			mText.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mText.setFillColor({ 170, 170, 170 });
		}

		void TStaticText::setCharacterSize(const std::size_t& CharacterSize)
		{
			mText.setCharacterSize(CharacterSize);
		}

		std::size_t TStaticText::getCharacterSize()
		{
			return mText.getCharacterSize();
		}

		void TStaticText::setCaption(const sf::String& Caption)
		{
			mText.setString(Caption);
		}

		const sf::String& TStaticText::getCaption() const
		{
			return mText.getString();
		}

		void TStaticText::setColor(const sf::Color& Color)
		{
			mText.setFillColor(Color);
		}

		const sf::Color& TStaticText::getColor() const
		{
			return mText.getFillColor();
		}

		void TStaticText::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			// draw the base class
			TWidget::draw(Target, States);

			// Apply the widget transform
			States.transform *= getParentTransform();

			// draw this widget
			Target.draw(mText, States);
		}

	}
}
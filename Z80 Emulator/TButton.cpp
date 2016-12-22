#include "TButton.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{

		TButton::TButton() :
			mTextPadding(0u, 0u)
		{
			/// Set the font
			mText.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mText.setPosition(static_cast<sf::Vector2f>(mTextPadding));

			TWidget::setColor(NormalColor);
		}

		void TButton::setCharacterSize(const std::size_t& CharacterSize)
		{
			mText.setCharacterSize(CharacterSize);
		}

		std::size_t TButton::getCharacterSize()
		{
			return mText.getCharacterSize();
		}

		void TButton::setCaption(const sf::String& Caption)
		{
			mText.setString(Caption);

			TWidget::setSize({ static_cast<unsigned int>(getTextSize().x) + mTextPadding.x * 2u, 50u });
		}

		const sf::String& TButton::getCaption() const
		{
			return mText.getString();
		}

		void TButton::setColor(const sf::Color& Color)
		{
			mText.setFillColor(Color);
		}

		const sf::Color& TButton::getColor() const
		{
			return mText.getFillColor();
		}

		void TButton::setPadding(const sf::Vector2u& Padding)
		{
			mTextPadding = Padding;

			mText.setPosition(static_cast<sf::Vector2f>(mTextPadding));
		}

		const sf::Vector2u& TButton::getPadding() const
		{
			return mTextPadding;
		}

		void TButton::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			// draw the base class
			TWidget::draw(Target, States);

			// Apply this widget transform
			States.transform *= getTransform();

			// Apply the parent widget transform if we have one
			if (getParent())
				States.transform *= getParentTransform();

			// draw this widget
			Target.draw(mText, States);
		}

		void TButton::onStateNormal()
		{
			TWidget::setColor(NormalColor);

			changeState(TStateManager::NORMAL);
		}

		void TButton::onStateHover()
		{
			TWidget::setColor(HoverColor);

			changeState(TStateManager::HOVER);
		}

		void TButton::onStateSelected()
		{
			TWidget::setColor(SelectedColorColor);

			changeState(TStateManager::SELECTED);
		}

		void TButton::onStateClicked()
		{
			TWidget::setColor(ClickedColor);
			
			changeState(TStateManager::CLICKED);
		}

		void TButton::onStateDisabled()
		{
			TWidget::setColor(DisabledColorColor);

			changeState(TStateManager::DISABLED);
		}

		sf::Vector2f TButton::getTextSize()
		{
			// Bounding box
			auto& TextBound = mText.getLocalBounds();

			return{ TextBound.width - TextBound.left, TextBound.height - TextBound.top };
		}

	}
}
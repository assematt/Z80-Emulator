#include "TButton.h"
#include "TCacheManager.h"

#include <SFML/OpenGL.hpp>

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

			TWidget::setSize({ static_cast<sf::Uint32>(getTextSize(true).x), 50u });
		}

		std::size_t TButton::getCharacterSize()
		{
			return mText.getCharacterSize();
		}

		void TButton::setCaption(const sf::String& Caption)
		{
			mText.setString(Caption);

			TWidget::setSize({ static_cast<sf::Uint32>(getTextSize(true).x), 50u });
		}

		const sf::String& TButton::getCaption() const
		{
			return mText.getString();
		}

		void TButton::setFillColor(const sf::Color& Color, const bool& OverrideOtherColor /*= true*/)
		{
			mText.setFillColor(Color, OverrideOtherColor);
		}

		const sf::Color& TButton::getFillColor() const
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
			// Skip the rendering if we are not showing the widget
			if (!isVisible())
				return;
			
			// draw the base class
			TWidget::draw(Target, States);

			// Apply the widget transform
			States.transform *= getParentTransform();

			// draw this widget
			Target.draw(mText, States);
		}

		void TButton::update(const sf::Time& ElapsedTime)
		{
			mText.setOpacity(TWidget::getOpacity());

			// Get the current widget state
			const auto& State = getState();

			switch (State)
			{
				case TWidget::NORMAL:
				{
					TWidget::setColor(NormalColor);
				} break;
				case TWidget::HOVER:
				{
					TWidget::setColor(HoverColor);
				} break;
				case TWidget::SELECTED:
				{
					TWidget::setColor(SelectedColorColor);
				} break;
				case TWidget::CLICKED:
				{
					TWidget::setColor(ClickedColor);
				} break;
				case TWidget::DISABLED:
				{
					TWidget::setColor(DisabledColorColor);
				} break;
			}
		}

		sf::Vector2f TButton::getTextSize(const bool& IncludePadding /*= false*/)
		{
			// Bounding box
			auto& TextBound = mText.getLocalBounds();

			sf::Vector2f TextSize = { TextBound.width - TextBound.left, TextBound.height - TextBound.top };

			return IncludePadding ? (TextSize + sf::Vector2f(mTextPadding.x * 2.f + 3.f, 0.f)) : TextSize;
		}

	}
}
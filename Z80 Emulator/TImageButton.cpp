#include "TImageButton.h"

namespace nne
{
	namespace tgui
	{

		void TImageButton::addImage(const sf::Texture& Image, const sf::Vector2f& ImagePosition /*= sf::Vector2f()*/)
		{
			mButtonImage.setTexture(Image);
			mButtonImage.setPosition(ImagePosition);
		}

		void TImageButton::update(const sf::Time& ElapsedTime)
		{
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
				
				if (TWidget::isToggleable())
				{
					if (TWidget::isSelected())
					{
						TWidget::changeState(TWidget::NORMAL);
						TWidget::setSelected(false);
					}
					else
					{
						TWidget::changeState(TWidget::SELECTED);
						TWidget::setSelected(true);
					}
				}
					
			} break;
			case TWidget::DISABLED:
			{
				TWidget::setColor(DisabledColorColor);
			} break;
			}
		}

		void TImageButton::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			// Skip the rendering if we are not showing the widget
			if (!isVisible() || (mParent && !mParent->isVisible()))
				return;

			TWidget::draw(Target, States);

			// Apply the widget transform
			States.transform *= getParentTransform();

			// draw this widget
			Target.draw(mButtonImage, States);
			Target.draw(mText, States);

			//TButton::draw(Target, States);
		}

	}
}
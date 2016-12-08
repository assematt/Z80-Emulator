#include "TImage.h"

namespace nne
{
	namespace tgui
	{

		TImage::TImage()
		{

		}

		void TImage::setImage(const sf::Texture& Image)
		{
			TWidget::setTexture(&Image);
		}

		const sf::Texture& TImage::GetImage() const
		{
			return *TWidget::getTexture();
		}

		void TImage::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			TWidget::draw(Target, States);
		}

	}
}
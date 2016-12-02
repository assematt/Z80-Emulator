#include "TImage.h"
#include "TDrawableComponent.h"

namespace nne
{
	namespace tgui
	{
		tgui::TImage::TImage()
		{
			init();
		}

		void tgui::TImage::init()
		{
			addComponent<TDrawableComponent>();
			initComponents();
		}

		void tgui::TImage::SetImage(const sf::Texture& Image)
		{
			getComponentAsPtr<TDrawableComponent>()->setTexture(Image);
		}

		const sf::Texture& tgui::TImage::GetImage() const
		{
			return getComponentAsPtr<TDrawableComponent>()->getTexture();
		}

		void TImage::setSize(const sf::Vector2u& Size)
		{
			getComponentAsPtr<TDrawableComponent>()->setSize(Size);
		}

		sf::Vector2u TImage::getSize()
		{
			return getComponentAsPtr<TDrawableComponent>()->getSize();
		}

		void TImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(getComponent<TDrawableComponent>(), states);
		}
	}
}
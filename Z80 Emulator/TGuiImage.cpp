#include "TGuiImage.h"

namespace nne
{
	namespace tgui
	{
		tgui::TGuiImage::TGuiImage()
		{
			init();
		}

		void tgui::TGuiImage::init()
		{
			addComponent<TDrawableComponent>();
			initComponents();
		}

		void tgui::TGuiImage::SetImage(const sf::Texture& Image)
		{
			getComponentAsPtr<TDrawableComponent>()->setTexture(Image);
		}

		const sf::Texture& tgui::TGuiImage::GetImage() const
		{
			return getComponentAsPtr<TDrawableComponent>()->getTexture();
		}

		void TGuiImage::setSize(const sf::Vector2u& Size)
		{
			getComponentAsPtr<TDrawableComponent>()->setSize(Size);
		}

		sf::Vector2u TGuiImage::getSize()
{
			return getComponentAsPtr<TDrawableComponent>()->getSize();
		}

		void TGuiImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
		}
	}
}
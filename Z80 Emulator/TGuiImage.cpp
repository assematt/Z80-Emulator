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

		void tgui::TGuiImage::refresh(const sf::Time& ElapsedTime)
		{
			TGuiWidget::refresh(ElapsedTime);
		}

		void tgui::TGuiImage::update(const sf::Time& ElapsedTime)
		{
			TGuiWidget::update(ElapsedTime);
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

		const sf::Vector2u& TGuiImage::getSize() const
		{
			return getComponentAsPtr<TDrawableComponent>()->getSize();
		}

		void TGuiImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
		}
	}
}
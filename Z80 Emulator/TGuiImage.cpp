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
			addComponent<TTransformable>();
			addComponent<TdrawableVector>();
			addComponent<TSprite>();
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
			getComponentAsPtr<TSprite>()->setTexture(Image);
		}

		const sf::Texture& tgui::TGuiImage::GetImage() const
		{
			return getComponentAsPtr<TSprite>()->getTexture();
		}

		void TGuiImage::setSize(const sf::Vector2u& Size)
		{
			getComponentAsPtr<TSprite>()->setSize(Size);
		}

		const sf::Vector2u& TGuiImage::getSize() const
		{
			return getComponentAsPtr<TSprite>()->getSize();
		}

		void TGuiImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= this->getComponentAsPtr<TTransformable>()->getTransform();

			auto& drawablesComponent = *getComponentAsPtr<TdrawableVector>();

			for (std::size_t Index = 0; Index < drawablesComponent.getVectorSize(); ++Index)
			{
				states.texture = drawablesComponent[Index].getTexture();
				target.draw(drawablesComponent[Index].getVertexArray(), states);
			}
		}
	}
}
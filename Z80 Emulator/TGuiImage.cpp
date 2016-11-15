#include "TGuiImage.h"

namespace nne
{
	namespace tgui
	{
		tgui::TGuiImage::TGuiImage()
		{
			Init();
		}

		void tgui::TGuiImage::Init()
		{
			AddComponent<TTransformable>();
			AddComponent<TDrawableVector>();
			AddComponent<TSprite>();
			InitComponents();
		}

		void tgui::TGuiImage::Refresh(const sf::Time& ElapsedTime)
		{
			TGuiWidget::Refresh(ElapsedTime);
		}

		void tgui::TGuiImage::Update(const sf::Time& ElapsedTime)
		{
			TGuiWidget::Update(ElapsedTime);
		}

		void tgui::TGuiImage::SetImage(const sf::Texture& Image)
		{
			GetComponentAsPtr<TSprite>()->SetTexture(Image);
		}

		const sf::Texture& tgui::TGuiImage::GetImage() const
		{
			return GetComponentAsPtr<TSprite>()->GetTexture();
		}

		void TGuiImage::SetSize(const sf::Vector2u& Size)
		{
			GetComponentAsPtr<TSprite>()->SetSize(Size);
		}

		const sf::Vector2u& TGuiImage::GetSize() const
		{
			return GetComponentAsPtr<TSprite>()->GetSize();
		}

		void TGuiImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= this->GetComponentAsPtr<TTransformable>()->GetTransform();

			auto& DrawablesComponent = *GetComponentAsPtr<TDrawableVector>();

			for (std::size_t Index = 0; Index < DrawablesComponent.GetVectorSize(); ++Index)
			{
				states.texture = DrawablesComponent[Index].GetTexture();
				target.draw(DrawablesComponent[Index].GetVertexArray(), states);
			}
		}
	}
}
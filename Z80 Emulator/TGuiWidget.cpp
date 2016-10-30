#include "TGuiWidget.h"

namespace nne
{
	namespace tgui
	{
		TGuiWidget::TGuiWidget()
		{
			Init();
		}

		void TGuiWidget::Init()
		{
			AddComponent<TTexture>();
			AddComponent<TTransformable>();
			AddComponent<TFont>();
			GetComponentAsPtr<TTexture>()->LoadTextureFromFile("resources/images/font.png");
			InitComponents();
		}

		void TGuiWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= this->GetComponentAsPtr<TTransformable>()->GetTransform();

			states.texture = &this->GetComponentAsPtr<TTexture>()->GetTexture();

			target.draw(this->GetComponentAsPtr<TTexture>()->GetVertexArray(), states);
		}
	}
}


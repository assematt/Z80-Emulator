#include "TGuiButton.h"

namespace nne
{
	namespace tgui
	{

		TGuiButton::TGuiButton()
		{
			Init();
		}

		void TGuiButton::Init()
		{
			AddComponent<TTransformable>();
			AddComponent<TFont>();
			AddComponent<TText>();
			InitComponents();

			GetComponentAsPtr<TFont>()->LoadFromFile("resources/fonts/font.ttf");
			//GetComponentAsPtr<_TFont>()->LoadFromFile("resources/images/font.png", false);
			GetComponentAsPtr<TText>()->SetString("Ciccio");
		}

		void TGuiButton::Refresh(const sf::Time& ElapsedTime)
		{
			TGuiWidget::Refresh(ElapsedTime);
		}

		void TGuiButton::Update(const sf::Time& ElapsedTime)
		{
			TGuiWidget::Update(ElapsedTime);
		}

		void TGuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			// Get a ref to the text component and font component
			auto& Text = *this->GetComponentAsPtr<TText>();
			auto& Font = *this->GetComponentAsPtr<TFont>();

			// Set the right transformation matrix
			states.transform *= this->GetComponentAsPtr<TTransformable>()->GetTransform();

			// If we are rendering a custom font
			if (Font.GetFontType() == TFont::TFontType::CUSTOM)
			{
				states.texture = Font.GetFontTexture(Text.GetCharacterSize());

				target.draw(Font.GetFontVertexArray(), states);
			}
			else
			{
				target.draw(Text.GetDrawableText(), states);
			}
		}

	}
}
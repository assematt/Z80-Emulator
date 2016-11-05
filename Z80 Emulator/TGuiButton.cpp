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

			TCacheManager::GetInstance().AddResource(nne::TResourceLoader<nne::TFont>(nne::TFontLoader("resources/fonts/font.ttf"), "font_1"));
			*GetComponentAsPtr<TFont>() = TCacheManager::GetInstance().GetResource<nne::TFont>("font_1");

			GetComponentAsPtr<TText>()->SetString(GetName());
		}

		void TGuiButton::Refresh(const sf::Time& ElapsedTime)
		{
			TGuiWidget::Refresh(ElapsedTime);
		}

		void TGuiButton::Update(const sf::Time& ElapsedTime)
		{
			TGuiWidget::Update(ElapsedTime);
		}

		void TGuiButton::SetCaption(const std::string& WidgetName)
		{
			GetComponentAsPtr<TText>()->SetString(WidgetName);
		}

		const std::string& TGuiButton::GetCaption() const
		{
			return GetComponentAsPtr<TText>()->GetString();
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
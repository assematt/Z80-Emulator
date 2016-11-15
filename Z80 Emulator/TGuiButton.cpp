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
			AddComponent<TDrawableVector>();
			AddComponent<TText>();
			InitComponents();
			
			GetComponentAsPtr<TText>()->SetFont(TCacheManager::GetInstance().GetResource<sf::Font>("font_1"));
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
			states.transform *= this->GetComponentAsPtr<TTransformable>()->GetTransform();

			auto& DrawablesComponent = *GetComponentAsPtr<TDrawableVector>();
			auto& TextComponent = *GetComponentAsPtr<TText>();

			for (std::size_t Index = 0; Index < DrawablesComponent.GetVectorSize(); ++Index)
			{
				states.texture = TextComponent.GetTexture();
				target.draw(DrawablesComponent[Index].GetVertexArray(), states);
			}
		}

	}
}
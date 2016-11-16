#include "TGuiButton.h"

namespace nne
{
	namespace tgui
	{

		TGuiButton::TGuiButton()
		{
			init();
		}

		void TGuiButton::init()
		{
			addComponent<TTransformable>();
			addComponent<TdrawableVector>();
			addComponent<TText>();
			initComponents();
			
			getComponentAsPtr<TText>()->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			getComponentAsPtr<TText>()->setString(getName());
		}

		void TGuiButton::refresh(const sf::Time& ElapsedTime)
		{
			TGuiWidget::refresh(ElapsedTime);
		}

		void TGuiButton::update(const sf::Time& ElapsedTime)
		{
			TGuiWidget::update(ElapsedTime);
		}

		void TGuiButton::SetCaption(const std::string& WidgetName)
		{
			getComponentAsPtr<TText>()->setString(WidgetName);
		}

		const std::string& TGuiButton::GetCaption() const
		{
			return getComponentAsPtr<TText>()->getString();
		}

		void TGuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= this->getComponentAsPtr<TTransformable>()->getTransform();

			auto& drawablesComponent = *getComponentAsPtr<TdrawableVector>();
			auto& TextComponent = *getComponentAsPtr<TText>();

			for (std::size_t Index = 0; Index < drawablesComponent.getVectorSize(); ++Index)
			{
				states.texture = TextComponent.getTexture();
				target.draw(drawablesComponent[Index].getVertexArray(), states);
			}
		}

	}
}
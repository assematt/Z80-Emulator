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
			addComponent<TDrawableComponent>();
			addComponent<TTextComponent>();
			initComponents();
			
			getComponentAsPtr<TTextComponent>()->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			getComponentAsPtr<TTextComponent>()->setString(getName());
		}

		void TGuiButton::SetCaption(const std::string& WidgetName)
		{
			getComponentAsPtr<TTextComponent>()->setString(WidgetName);
		}

		const std::string& TGuiButton::GetCaption() const
		{
			return getComponentAsPtr<TTextComponent>()->getString();
		}

		void TGuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
		}

	}
}
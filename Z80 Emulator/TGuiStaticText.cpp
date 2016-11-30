#include "TGuiStaticText.h"
#include "TGuiWidget.h"

namespace nne
{
	namespace tgui
	{

		TGuiStaticText::TGuiStaticText()
		{
			init();
		}

		void TGuiStaticText::init()
		{
			addComponent<TDrawableComponent>();
			addComponent<TTextComponent>();
			initComponents();

			getComponentAsPtr<TTextComponent>()->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			getComponentAsPtr<TTextComponent>()->setFillColor({170, 170, 170});
			disableInput();
		}

		void TGuiStaticText::SetCaption(const std::string& WidgetName)
		{
			getComponentAsPtr<TTextComponent>()->setString(WidgetName);
		}

		const std::string& TGuiStaticText::GetCaption() const
		{
			return getComponentAsPtr<TTextComponent>()->getString();
		}

		void TGuiStaticText::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
		}

	}
}
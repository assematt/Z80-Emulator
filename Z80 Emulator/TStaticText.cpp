#include "TStaticText.h"
#include "TWidget.h"

namespace nne
{
	namespace tgui
	{

		TStaticText::TStaticText()
		{
			init();
		}

		void TStaticText::init()
		{
			addComponent<TDrawableComponent>();
			addComponent<TTextComponent>();
			initComponents();

			getComponentAsPtr<TTextComponent>()->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			getComponentAsPtr<TTextComponent>()->setFillColor({170, 170, 170});
			disableInput();
		}

		void TStaticText::SetCaption(const std::string& WidgetName)
		{
			getComponentAsPtr<TTextComponent>()->setString(WidgetName);
		}

		const std::string& TStaticText::GetCaption() const
		{
			return getComponentAsPtr<TTextComponent>()->getString();
		}

		void TStaticText::setCharacterSize(const std::size_t& CharacterSize)
		{
			getComponentAsPtr<TTextComponent>()->setCharacterSize(CharacterSize);
		}

		const std::size_t& TStaticText::getCharacterSize()
		{
			return getComponentAsPtr<TTextComponent>()->getCharacterSize();
		}

		void TStaticText::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
		}

	}
}
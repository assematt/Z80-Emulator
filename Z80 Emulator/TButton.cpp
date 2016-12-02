#include "TButton.h"

namespace nne
{
	namespace tgui
	{

		TButton::TButton()
		{
			init();
		}

		void TButton::init()
		{
			addComponent<TDrawableComponent>();
			addComponent<TTextComponent>();
			initComponents();
			
			getComponentAsPtr<TTextComponent>()->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			getComponentAsPtr<TTextComponent>()->setString(getName());
		}

		void TButton::SetCaption(const std::string& WidgetName)
		{
			getComponentAsPtr<TTextComponent>()->setString(WidgetName);
		}

		const std::string& TButton::GetCaption() const
		{
			return getComponentAsPtr<TTextComponent>()->getString();
		}

		void TButton::setCharacterSize(const std::size_t& CharacterSize)
		{
			getComponentAsPtr<TTextComponent>()->setCharacterSize(CharacterSize);
		}

		const std::size_t& TButton::getCharacterSize()
		{
			return getComponentAsPtr<TTextComponent>()->getCharacterSize();
		}
		
		void TButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
		}

	}
}
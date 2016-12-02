#include "TPanel.h"

namespace nne
{
	namespace tgui
	{

		TPanel::TPanel()
		{
			init();
		}

		void TPanel::init()
		{
			addComponent<TDrawableComponent>();
			initComponents();
		}

		void TPanel::setColor(const sf::Color& Color)
		{
			getComponentAsPtr<TDrawableComponent>()->setColor(Color);
		}

		void TPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(getComponent<TDrawableComponent>(), states);
		}

	}
}
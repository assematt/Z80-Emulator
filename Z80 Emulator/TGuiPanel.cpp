#include "TGuiPanel.h"

namespace nne
{
	namespace tgui
	{

		TGuiPanel::TGuiPanel()
		{
			init();
		}

		void TGuiPanel::init()
		{
			addComponent<TDrawableComponent>();
			initComponents();
		}

		void TGuiPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
		}

	}
}
#include "TContainer.h"
#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
		
		void TContainer::addWidget(TWidget* Widget)
		{
			// Add the widget to this one by 
			Widget->setParent(this);
		}

		void TContainer::removeWidget(const TWidget::ID& WidgetToRemove)
		{
			getManager().getWidget(WidgetToRemove)->setParent(nullptr);
		}

		void TContainer::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			TWidget::draw(Target, States);
		}

	}
}
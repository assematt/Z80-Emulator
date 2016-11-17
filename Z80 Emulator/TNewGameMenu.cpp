#include "TNewGameMenu.h"

namespace nne
{
	namespace tgui
	{
		void TNewGameMenu::setup(nne::tgui::TGuiManager* GuiManager)
		{
			mParentManager = GuiManager;

			/// Add a loading screen everytime we choose to display this menu
			mLoadingScreen = std::make_unique<TNewGameLoadingScreen>();
			mLoadingScreen->setup(GuiManager);
		}

		void TNewGameMenu::handleEvent(sf::Event& Event)
		{

		}
	}
}


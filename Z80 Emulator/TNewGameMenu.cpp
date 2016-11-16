#include "TNewGameMenu.h"

namespace nne
{
	namespace tgui
	{
		void TNewGameMenu::setup()
		{
// 			tgui::TGuiButton::UniquePtr Loaded = std::make_unique<tgui::TGuiButton>();
// 			Loaded->setPosition(GetReferencePointPosition());
// 			Loaded->SetName("NEW_GAME_MENU_LOADED");
// 			Loaded->SetCaption("NEW GAME MENU LOADED");
// 			this->AddWidget(Loaded);


			/// Add a loading screen everytime we choose to display this menu
			mLoadingScreen = std::make_unique<TNewGameLoadingScreen>();

			mLoadingScreen->setup();
		}

		void TNewGameMenu::handleEvent(sf::Event& Event)
		{

		}
	}
}


#include "TNewGameMenu.h"

namespace nne
{
	namespace tgui
	{
		void TNewGameMenu::Setup()
		{
			tgui::TGuiButton::UniquePtr Loaded = std::make_unique<tgui::TGuiButton>();
			Loaded->SetPosition(GetReferencePointPosition());
			Loaded->SetName("NEW_GAME_MENU_LOADED");
			Loaded->SetCaption("NEW GAME MENU LOADED");
			this->AddWidget(Loaded);


			/// Add a loading screen everytime we choose to display this menu
			mLoadingScreen = std::make_unique<TNewGameLoadingScreen>();

			mLoadingScreen->Setup();
		}

		void TNewGameMenu::HandleEvent(sf::Event& Event)
		{

		}
	}
}


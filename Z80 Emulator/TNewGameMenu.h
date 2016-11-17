#pragma once

#include "IScreenView.h"
#include "TGuiManager.h"
#include "TNewGameLoadingScreen.h"

namespace nne
{
	namespace tgui
	{
		class TNewGameMenu : public nne::tgui::IScreenView
		{
		public:
			virtual void setup(nne::tgui::TGuiManager* GuiManager);

			void handleEvent(sf::Event& Event);

		};
	}
}
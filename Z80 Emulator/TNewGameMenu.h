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
			virtual void Setup();

			void HandleEvent(sf::Event& Event);

		};
	}
}
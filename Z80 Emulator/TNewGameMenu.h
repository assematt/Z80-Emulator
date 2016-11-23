#pragma once

#include "IScreenView.h"
#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
		class TNewGameMenu : public nne::tgui::IScreenView
		{
		public:
			virtual void init();

			void handleEvent(sf::Event& Event);

		};
	}
}
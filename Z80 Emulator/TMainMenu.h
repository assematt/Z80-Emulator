#pragma once

#include "IScreenView.h"
#include "TGuiManager.h"
#include "TGuiWindow.h"
#include "TGuiButton.h"
#include "TGuiImage.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{
		class TMainMenu : public nne::tgui::IScreenView
		{
		public:
			virtual void setup();
			
			void onNewGameButtonClick(const sf::Event::MouseButtonEvent& Button);
		};
	}
}
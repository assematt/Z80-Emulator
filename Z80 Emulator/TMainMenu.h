#pragma once

#include "IScreenView.h"
#include "TGuiManager.h"
#include "TGuiButton.h"

namespace nne
{
	namespace tgui
	{
		class TMainMenu : public nne::tgui::IScreenView
		{
		public:
			virtual void Setup();

			void HandleEvent(sf::Event& Event);

			void Display();

			void OnNewGameButtonClick(int X, int Y);
			void OnInstructionButtonClick(int X, int Y);
			void OnInfoButtonClick(int X, int Y);
			void OnExitButtonClick(int X, int Y);
		};
	}
}
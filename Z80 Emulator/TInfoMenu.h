#pragma once

#include "IScreenView.h"
#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
		class TInfoMenu : public nne::tgui::IScreenView
		{
		public:
			virtual void Setup();

			void HandleEvent(sf::Event& Event);

			void Display();
		};
	}
}
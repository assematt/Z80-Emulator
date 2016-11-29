#pragma once

#include "IScreenView.h"

namespace nne
{
	namespace tgui
	{
		class TGuiTestMenu : public nne::tgui::IScreenView
		{
		public:
			virtual void init();

			void onTestButtonClick(const sf::Event::MouseButtonEvent& Button);
		};
	}
}

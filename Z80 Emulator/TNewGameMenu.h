#pragma once

#include "IScreenView.h"
#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
		class TNewGameMenu : public IScreenView
		{
		public:
			virtual void init();

			void handleEvent(sf::Event& Event);


			virtual void refresh(const sf::Time& ElapsedTime) override;

		};
	}
}
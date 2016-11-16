#pragma once

#include "ILoadingScreen.h"
#include "IScreenView.h"
#include "TGuiButton.h"
#include "TGuiImage.h"

namespace nne
{
	namespace tgui
	{
		class TNewGameLoadingScreen : public ILoadingScreen, public tgui::IScreenView
		{
		public:

			void setup() final;

			virtual void loading(std::atomic_bool& IsLoading) override;

			virtual void handleEvent(sf::Event& Event);
			
		private:
		};
	}
}
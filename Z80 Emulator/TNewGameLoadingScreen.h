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

			void Setup() final;

			virtual void Loading(std::atomic_bool& IsLoading) override;

			virtual void HandleEvent(sf::Event& Event);
			
		private:
		};
	}
}
#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <iostream>

#include "TRandom.h"
#include "TManager.h"

#include "IScreenView.h"
#include "TMainMenu.h"
#include "TNewGameMenu.h"

namespace nne
{
	namespace tgui
	{
		class TGuiManager
		{
		public:
			TGuiManager();

			void Setup();

			void ProcessEvents(sf::Event& EventToProcess);

			void AddMenu(IScreenView::UniquePtr& Menu);

			void ChangeMenu(std::size_t NextMenu);

			void Refresh(const sf::Time& ElapsedTime);

			void Update(const sf::Time& ElapsedTime);

			void Draw();

		private:
			bool mIsRunning;
			std::size_t mCurrentViewIndex;
			std::size_t mPreviousViewIndex;
			std::vector<IScreenView::UniquePtr> mScreens;
		};
	}
}
#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <future>
#include <vector>

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

			void setup();

			void processEvents(sf::Event& EventToProcess);

			void addMenu(IScreenView::UniquePtr& Menu);

			void changeMenu(std::size_t NextMenu);

			void refresh(const sf::Time& ElapsedTime);

			void update(const sf::Time& ElapsedTime);

			void draw();

		private:
			void ExecuteLoadingScreen();

		private:
			bool mIsRunning;
			std::atomic_bool mIsloading;
			std::future<void> mLoadingStatus;
			std::size_t mCurrentViewIndex;
			std::size_t mPreviousViewIndex;
			std::thread mLoadingThread;
			std::vector<IScreenView::UniquePtr> mScreens;
		};
	}
}
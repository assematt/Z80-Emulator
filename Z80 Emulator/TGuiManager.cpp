#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
		TGuiManager::TGuiManager() :
			mCurrentViewIndex(1),
			mIsloading(false)
		{
		}

		void TGuiManager::setup()
		{
			// Create a main menu
			TMainMenu::UniquePtr MainMenuMenu = std::make_unique<TMainMenu>();
			MainMenuMenu->setup();
			addMenu(MainMenuMenu);

			// Create an info menu
			TNewGameMenu::UniquePtr InfoMenu = std::make_unique<TNewGameMenu>();
			InfoMenu->setup();
			addMenu(InfoMenu);
		}

		void TGuiManager::changeMenu(std::size_t NextMenu)
		{
			///  Keep in memory the last viewed screen
			mPreviousViewIndex = mCurrentViewIndex;

			/// Set the new screen to display, if this screen doesn't exist goes back to the main menu
			mCurrentViewIndex = mCurrentViewIndex == mScreens.size() ? 0 : NextMenu;
			
			/// Check if the screen we want to load needs a loading screen to load data
			if (mScreens[mCurrentViewIndex]->getLoadingScreen() != nullptr)
			{
				mLoadingStatus = std::async(std::launch::async, &TNewGameLoadingScreen::loading, dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->getLoadingScreen().get()), std::ref(mIsloading));

				mIsloading = true;
				//ExecuteLoadingScreen();
			}				
			
		}

		void TGuiManager::refresh(const sf::Time& ElapsedTime)
		{
			/// Skip the refresh cycle if we are loading something
			if (mIsloading)
			{
				auto& LoadingScreen = *dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->getLoadingScreen().get());

				LoadingScreen.refresh(ElapsedTime);
				return;
			}


			mScreens[mCurrentViewIndex]->refresh(ElapsedTime);
		}

		void TGuiManager::update(const sf::Time& ElapsedTime)
		{
			/// Skip the update cycle if we are loading something
			if (mIsloading)
			{
				auto& LoadingScreen = *dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->getLoadingScreen().get());

				LoadingScreen.update(ElapsedTime);
				return;
			}

			mScreens[mCurrentViewIndex]->update(ElapsedTime);
		}

		void TGuiManager::draw()
		{
			/// Skip the draw cycle if we are loading something
			if (mIsloading)
			{

				auto& LoadingScreen = *dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->getLoadingScreen().get());

				LoadingScreen.draw();
				return;
			}

			mScreens[mCurrentViewIndex]->draw();
		}

		void TGuiManager::ExecuteLoadingScreen()
		{
			std::async(std::launch::async, &TNewGameLoadingScreen::loading, dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->getLoadingScreen().get()), std::ref(mIsloading));
		}

		void TGuiManager::processEvents(sf::Event& EventToProcess)
		{
			mScreens[mCurrentViewIndex]->handleEvent(EventToProcess);

			/*if (EventToProcess.type == sf::Event::MouseButtonPressed)
			{
			ChangeMenu(TODO);
			}*/
		}

		void TGuiManager::addMenu(IScreenView::UniquePtr& Menu)
		{
			Menu->mParentManager = this;
			mScreens.push_back(std::move(Menu));
		}

	}
}


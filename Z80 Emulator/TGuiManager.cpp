#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
		TGuiManager::TGuiManager() :
			mCurrentViewIndex(0),
			mIsloading(false)
		{
		}

		void TGuiManager::setup(std::shared_ptr<sf::RenderWindow> RenderWindow)
		{
			mRenderWindow = RenderWindow;

			// Create a main menu
			tgui::TMainMenu::UniquePtr MainMenuMenu = std::make_unique<tgui::TMainMenu>();
			MainMenuMenu->setup(this);
			addMenu(MainMenuMenu);

			// Create an info menu
			tgui::TNewGameMenu::UniquePtr InfoMenu = std::make_unique<tgui::TNewGameMenu>();
			InfoMenu->setup(this);
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

		sf::RenderWindow& TGuiManager::getRenderingWindow() const
		{
			return *mRenderWindow;
		}

		void TGuiManager::processEvents(sf::Event& EventToProcess)
		{
			mScreens[mCurrentViewIndex]->handleEvent(EventToProcess);
		}

		void TGuiManager::addMenu(IScreenView::UniquePtr& Menu)
		{
			mScreens.push_back(std::move(Menu));
		}

	}
}


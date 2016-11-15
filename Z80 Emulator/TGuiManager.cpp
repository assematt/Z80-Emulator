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

		void TGuiManager::Setup()
		{
			// Create a main menu
			TMainMenu::UniquePtr MainMenuMenu = std::make_unique<TMainMenu>();
			MainMenuMenu->Setup();
			AddMenu(MainMenuMenu);

			// Create an info menu
			TNewGameMenu::UniquePtr InfoMenu = std::make_unique<TNewGameMenu>();
			InfoMenu->Setup();
			AddMenu(InfoMenu);
		}

		void TGuiManager::ChangeMenu(std::size_t NextMenu)
		{
			///  Keep in memory the last viewed screen
			mPreviousViewIndex = mCurrentViewIndex;

			/// Set the new screen to display, if this screen doesn't exist goes back to the main menu
			mCurrentViewIndex = mCurrentViewIndex == mScreens.size() ? 0 : NextMenu;
			
			/// Check if the screen we want to load needs a loading screen to load data
			if (mScreens[mCurrentViewIndex]->GetLoadingScreen() != nullptr)
			{
				mLoadingStatus = std::async(std::launch::async, &TNewGameLoadingScreen::Loading, dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->GetLoadingScreen().get()), std::ref(mIsloading));

				mIsloading = true;
				//ExecuteLoadingScreen();
			}				
			
		}

		void TGuiManager::Refresh(const sf::Time& ElapsedTime)
		{
			/// Skip the refresh cycle if we are loading something
			if (mIsloading)
			{
				auto& LoadingScreen = *dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->GetLoadingScreen().get());

				LoadingScreen.Refresh(ElapsedTime);
				return;
			}


			mScreens[mCurrentViewIndex]->Refresh(ElapsedTime);
		}

		void TGuiManager::Update(const sf::Time& ElapsedTime)
		{
			/// Skip the update cycle if we are loading something
			if (mIsloading)
			{
				auto& LoadingScreen = *dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->GetLoadingScreen().get());

				LoadingScreen.Update(ElapsedTime);
				return;
			}

			mScreens[mCurrentViewIndex]->Update(ElapsedTime);
		}

		void TGuiManager::Draw()
		{
			/// Skip the draw cycle if we are loading something
			if (mIsloading)
			{

				auto& LoadingScreen = *dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->GetLoadingScreen().get());

				LoadingScreen.Draw();
				return;
			}

			mScreens[mCurrentViewIndex]->Draw();
		}

		void TGuiManager::ExecuteLoadingScreen()
		{
			std::async(std::launch::async, &TNewGameLoadingScreen::Loading, dynamic_cast<TNewGameLoadingScreen*>(mScreens[mCurrentViewIndex]->GetLoadingScreen().get()), std::ref(mIsloading));
		}

		void TGuiManager::ProcessEvents(sf::Event& EventToProcess)
		{
			mScreens[mCurrentViewIndex]->HandleEvent(EventToProcess);

			/*if (EventToProcess.type == sf::Event::MouseButtonPressed)
			{
			ChangeMenu(TODO);
			}*/
		}

		void TGuiManager::AddMenu(IScreenView::UniquePtr& Menu)
		{
			Menu->mParentManager = this;
			mScreens.push_back(std::move(Menu));
		}

	}
}


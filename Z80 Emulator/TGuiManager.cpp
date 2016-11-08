#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
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

		TGuiManager::TGuiManager() :
			mCurrentViewIndex(1)
		{
		}

		void TGuiManager::ChangeMenu(std::size_t NextMenu)
		{
			mPreviousViewIndex = mCurrentViewIndex;

			mCurrentViewIndex = NextMenu;

			if (mCurrentViewIndex == mScreens.size())
			{
				mCurrentViewIndex = 0;
			}
		}

		void TGuiManager::Refresh(const sf::Time& ElapsedTime)
		{
			mScreens[mCurrentViewIndex]->Refresh(ElapsedTime);
		}

		void TGuiManager::Update(const sf::Time& ElapsedTime)
		{
			mScreens[mCurrentViewIndex]->Update(ElapsedTime);
		}

		void TGuiManager::Draw()
		{
			mScreens[mCurrentViewIndex]->Draw();
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


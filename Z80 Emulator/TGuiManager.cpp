#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{
		TGuiManager::TGuiManager() :
			mCurrentViewIndex(0),
			mRenderWindow(nullptr)
		{
		}

		void TGuiManager::initMenus(sf::RenderWindow& RenderWindow, TSceneManager& SceneManager)
		{
			mRenderWindow = &RenderWindow;
			mSceneManager = &SceneManager;

			for (auto& Screen : mScreens)
				Screen->init();
		}

		void TGuiManager::changeMenu(std::size_t NextMenu)
		{
			///  Keep in memory the last viewed screen
			mPreviousViewIndex = mCurrentViewIndex;

			/// Set the new screen to display, if this screen doesn't exist goes back to the main menu
			mCurrentViewIndex = mCurrentViewIndex == mScreens.size() ? 0 : NextMenu;		}

		void TGuiManager::refresh(const sf::Time& ElapsedTime)
		{
			mScreens[mCurrentViewIndex]->refresh(ElapsedTime);
		}

		void TGuiManager::update(const sf::Time& ElapsedTime)
		{
			mScreens[mCurrentViewIndex]->update(ElapsedTime);
		}

		void TGuiManager::draw()
		{
			mScreens[mCurrentViewIndex]->draw();
		}

		const sf::Vector2f TGuiManager::getReferencePointPosition(TReferencePoint RefPoint /*= TReferencePoint::CENTER*/)
		{
			sf::Vector2f& WindowSize = static_cast<sf::Vector2f>(mRenderWindow->getSize());

			switch (RefPoint)
			{
			case nne::tgui::TReferencePoint::LEFT_TOP:
				return{ 0.f, 0.f };
			case nne::tgui::TReferencePoint::CENTER_TOP:
				return{ WindowSize.x / 2, 0.f };
			case nne::tgui::TReferencePoint::RIGHT_TOP:
				return{ WindowSize.x, 0.f };

			case nne::tgui::TReferencePoint::LEFT_CENTER:
				return{ 0.f, WindowSize.y / 2 };
			case nne::tgui::TReferencePoint::CENTER:
				return{ WindowSize.x / 2, WindowSize.y / 2 };
			case nne::tgui::TReferencePoint::RIGHT_CENTER:
				return{ 0.f, WindowSize.y / 2 };

			case nne::tgui::TReferencePoint::LEFT_BOTTOM:
				return{ 0.f, WindowSize.y };
			case nne::tgui::TReferencePoint::CENTER_BOTTOM:
				return{ WindowSize.x / 2, WindowSize.y };
			case nne::tgui::TReferencePoint::RIGHT_BOTTOM:
				return{ WindowSize.x, WindowSize.y };
			}
		}

		sf::RenderWindow& TGuiManager::getRenderingWindow() const
		{
			return *mRenderWindow;
		}

		nne::TSceneManager* TGuiManager::getSceneManager()
		{
			return mSceneManager;
		}

		void TGuiManager::setup(sf::RenderWindow& RenderTarget)
		{
			mRenderWindow = &RenderTarget;
		}

		void TGuiManager::processEvents(sf::Event& EventToProcess)
		{
			mScreens[mCurrentViewIndex]->handleEvent(EventToProcess);
		}

		void TGuiManager::addMenu(IScreenView::UniquePtr& Menu)
		{
			Menu->mParentManager = this;

			mScreens.push_back(std::move(Menu));
		}

	}
}


#include "TNewGameLoadingScreen.h"
#include "TLoadingScreenMenu.h"

namespace nne
{
	void TNewGameLoadingScreen::loading(std::atomic_bool& IsLoading)
	{
		sf::sleep(sf::seconds(5.f));

		IsLoading = false;
	}

	void TNewGameLoadingScreen::init()
	{
		//auto TempPtr = ;

		// Create a loading screen
		//mAppGui.addMenu(std::unique_ptr<tgui::IScreenView>(new tgui::TLoadingScreenMenu()));

		// Init all the menus
		mAppGui.initMenus(*mRenderSurface, *mParent);
	}

	nne::IScene::ID& TNewGameLoadingScreen::run(const sf::Time& ElapsedTime)
	{
		IScene::ID SelectedID = eventLoop();

		refresh(ElapsedTime);

		update(ElapsedTime);

		draw();

		return SelectedID == Same ? mID : SelectedID;
	}

	nne::IScene::ID TNewGameLoadingScreen::eventLoop()
	{
		while (mRenderSurface->pollEvent(mAppEvent))
		{
			mAppGui.processEvents(mAppEvent);

			if (mAppEvent.type == sf::Event::Closed)
				mRenderSurface->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderSurface->close();
		}

		return IScene::Same;
	}

	void TNewGameLoadingScreen::refresh(sf::Time ElapsedTime)
	{
		mAppGui.refresh(ElapsedTime);
	}

	void TNewGameLoadingScreen::update(sf::Time ElapsedTime)
	{
		mAppGui.update(ElapsedTime);
	}

	void TNewGameLoadingScreen::draw()
	{
		// Clear the back buffered window
		mRenderSurface->clear();

		// Render the GUI
		mAppGui.draw();

		// Display the back buffered window
		mRenderSurface->display();
	}

}
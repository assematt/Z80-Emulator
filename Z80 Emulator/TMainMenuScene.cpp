#include "TMainMenuScene.h"
#include "TMainMenu.h"

namespace nne
{

	void TMainMenuScene::init()
	{
		// First setup the GUI
		mAppGui.setup(*mRenderSurface);

		// Create a main menu
		mAppGui.addMenu(std::unique_ptr<tgui::IScreenView>(new tgui::TMainMenu));

		// Init all the menus
		mAppGui.initMenus(*mParent);
	}

	nne::IScene::ID TMainMenuScene::eventLoop()
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

	void TMainMenuScene::refresh(sf::Time ElapsedTime)
	{
		mAppGui.refresh(ElapsedTime);
	}

	void TMainMenuScene::update(sf::Time ElapsedTime)
	{
		mAppGui.update(ElapsedTime);
	}

	void TMainMenuScene::draw()
	{
		// Clear the back buffered window
		mRenderSurface->clear();

		// Render the GUI
		mAppGui.draw();

		// Display the back buffered window
		mRenderSurface->display();
	}

}
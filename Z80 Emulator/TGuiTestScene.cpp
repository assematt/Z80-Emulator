#include "TGuiTestScene.h"
#include "TGuiTestMenu.h"

namespace nne
{

	void TGuiTestScene::init()
	{
		// First setup the GUI
		mAppGui.setup(*mRenderSurface);

		// Create a main menu
		mAppGui.addMenu(std::unique_ptr<tgui::IScreenView>(new tgui::TGuiTestMenu));

		// Init all the menus
		mAppGui.initMenus(*mRenderSurface, *mParent);
	}

	nne::IScene::ID TGuiTestScene::eventLoop()
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

	void TGuiTestScene::refresh(sf::Time ElapsedTime)
	{
		mAppGui.refresh(ElapsedTime);
	}

	void TGuiTestScene::update(sf::Time ElapsedTime)
	{
		mAppGui.update(ElapsedTime);
	}

	void TGuiTestScene::draw()
	{
		// Clear the back buffered window
		mRenderSurface->clear();

		// Render the GUI
		mAppGui.draw();

		// Display the back buffered window
		mRenderSurface->display();
	}

}
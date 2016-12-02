#include "TGuiTestScene.h"

#include <SFML/OpenGL.hpp>

#include "TGuiTestMenu.h"

namespace nne
{

	void TGuiTestScene::init()
	{
		// First setup the GUI
		mAppGui.setup(*mRenderWindow);

		// Create a main menu
		mAppGui.addMenu(std::unique_ptr<tgui::IScreenView>(new tgui::TGuiTestMenu));

		// Init all the menus
		mAppGui.initMenus(*mParent);
	}

	nne::IScene::ID TGuiTestScene::eventLoop()
	{
		while (mRenderWindow->pollEvent(mAppEvent))
		{
			mAppGui.processEvents(mAppEvent);

			if (mAppEvent.type == sf::Event::Closed)
				mRenderWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.code == sf::Keyboard::W)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.code == sf::Keyboard::F)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
		mRenderWindow->clear();		

		// Render the GUI
		mAppGui.draw();

		// Display the back buffered window
		mRenderWindow->display();
	}

}
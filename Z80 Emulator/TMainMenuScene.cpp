#include "TMainMenuScene.h"
#include "TMainMenu.h"

namespace nne
{

	void TMainMenuScene::init()
	{
		tgui::TMainMenu::Ptr MainMenu = std::make_shared<tgui::TMainMenu>("MAIN_MENU");
		MainMenu->setSize(mRenderWindow->getSize());
		MainMenu->init(&mGuiManager);
		mGuiManager.addWidget(MainMenu);
	}

	nne::IScene::ID TMainMenuScene::eventLoop()
	{
		nne::IScene::ID NewSceneID = IScene::Same;

		while (mRenderWindow->pollEvent(mAppEvent))
		{
			NewSceneID = mGuiManager.processEvents(mAppEvent, *mRenderWindow);

			if (mAppEvent.type == sf::Event::Closed)
				mRenderWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderWindow->close();

			if (NewSceneID == IScene::Exit)
				mRenderWindow->close();
		}

		return NewSceneID;
	}

	void TMainMenuScene::refresh(const sf::Time& ElapsedTime)
	{		
	}

	void TMainMenuScene::update(const sf::Time& ElapsedTime)
	{
		mGuiManager.update(ElapsedTime);
	}

	void TMainMenuScene::draw()
	{
		// Clear the back buffered window
		mRenderWindow->clear();

		// Renders the Gui
		for (auto& Widget : mGuiManager)
			mRenderWindow->draw(*Widget);

		// Display the back buffered window
		mRenderWindow->display();
	}

}
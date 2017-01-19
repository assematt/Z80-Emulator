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

		//mGuiManager.addWidget<tgui::TMainMenu>("MAIN_MENU", 0);
		//mGuiManager.addWidget<tgui::TMainMenu>(std::string("MAIN_MENU"), 0u);
		//auto MainMenu = mGuiManager.getWidget<tgui::TMainMenu>("MAIN_MENU");
		//MainMenu->init(&mGuiManager);
		//MainMenu->setSize(mRenderWindow->getSize());

		//Menu->setSize(mRenderWindow->getSize());
		//std::dynamic_pointer_cast<tgui::TMainMenu>(Menu)->init(&mGuiManager);
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

	void TMainMenuScene::refresh(sf::Time ElapsedTime)
	{		
	}

	void TMainMenuScene::update(sf::Time ElapsedTime)
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
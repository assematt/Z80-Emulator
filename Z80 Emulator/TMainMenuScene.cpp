#include "TMainMenuScene.h"
#include "TMainMenu.h"

namespace nne
{

	void TMainMenuScene::init()
	{
// 		tgui::TMainMenu::Ptr Menu = std::make_shared<tgui::TMainMenu>();
// 		Menu->setSize(mRenderWindow->getSize());
// 		Menu->init(&mGuiManager);
// 		mGuiManager.addWidget(std::move(Menu));

		mGuiManager.addWidget<tgui::TMainMenu>();
		auto& Menu = mGuiManager.getLastAdded();
		Menu->setSize(mRenderWindow->getSize());
		std::dynamic_pointer_cast<tgui::TMainMenu>(Menu)->init(&mGuiManager);
	}

	nne::IScene::ID TMainMenuScene::eventLoop()
	{
		while (mRenderWindow->pollEvent(mAppEvent))
		{
			mGuiManager.processEvents(mAppEvent, *mRenderWindow);

			if (mAppEvent.type == sf::Event::Closed)
				mRenderWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderWindow->close();
		}

		return IScene::Same;
	}

	void TMainMenuScene::refresh(sf::Time ElapsedTime)
	{
	}

	void TMainMenuScene::update(sf::Time ElapsedTime)
	{
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
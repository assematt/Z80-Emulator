#include "TNewGameScene.h"
#include "TNewGameMenu.h"
#include "TLogicBoardComponent.h"

#define ENABLE TRUE

namespace nne
{

	void TNewGameScene::init()
	{
#if ENABLE == TRUE
		// Create a Z80 and RAM entity
		mLogicEntity.addEntity(TFactory::makeZ80(), "Z80");
		mLogicEntity.addEntity(TFactory::makeRam(), "Ram");
		mLogicEntity.initEntities();

		// Get the Z80 and the ram entity
		auto Z80 = mLogicEntity.getEntityByKey("Z80");
		auto Ram = mLogicEntity.getEntityByKey("Ram");

		Z80->getComponentAsPtr<tcomponents::TZ80Component>()->connectRam(Ram);
		if (!Z80->getComponentAsPtr<tcomponents::TZ80Component>()->loadProgram("resources/programs/SUB.A01"))
		{
			std::cout << "Error! Could not open the file" << std::endl;

			// Something went bad :(
			return;
		}
		
		// Create some graphic entity
		mGraphicEntity.addEntity(TFactory::makeLogicBoard(), "LogicBoard", mParent);
		mGraphicEntity.addEntity(TFactory::makeChip(Z80.get()), "Z80Chip", mParent);
		mGraphicEntity.addEntity(TFactory::makeChip(Ram.get()), "RamChip", mParent);
		mGraphicEntity.addEntity(TFactory::makeConductiveTrack(), "ConductiveRack", mParent);
		mGraphicEntity.initEntities();

		// Create a Z80 chip and set some property
		auto& Z80Chip = mGraphicEntity.getEntityByKey("Z80Chip");
		Z80Chip->getComponentAsPtr<TDrawableComponent>()->setPosition(250.f, 100.f);
		Z80Chip->getComponentAsPtr<TDrawableComponent>()->setScale(.5f, .5f);
		
		// Create a RAM chip and set some property
		auto& RamChip = mGraphicEntity.getEntityByKey("RamChip");
		RamChip->getComponentAsPtr<TDrawableComponent>()->setPosition(900.f, 100.f);
		RamChip->getComponentAsPtr<TDrawableComponent>()->setScale(.5f, .5f);

		// Create a sample track and set some property
		auto& ConductiveRack = mGraphicEntity.getEntityByKey("ConductiveRack");

		// Create the logic board who will contain all the chip and set some property
		mLogicBoard = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TLogicBoardComponent>();
		mGraphicEntity.getEntityByKey("LogicBoard")->getComponent<TDrawableComponent>().setPosition({ 320.f, 70.f });
	
		mLogicBoard->placeChip(Z80Chip.get());
		mLogicBoard->placeChip(RamChip.get());
		mLogicBoard->placeTrack(ConductiveRack.get());
		mLogicBoard->setSelectedTrack(ConductiveRack->getComponentAsPtr<TConductiveTracks>());

// 		mGraphicEntity.addEntity(TFactory::makeLogicBoard(), "LogicBoard", mParent);
// 		mGraphicEntity.getEntityByKey("LogicBoard")->getComponent<TDrawableComponent>().setPosition({ 320.f, 70.f });
// 		mGraphicEntity.initEntities();

#endif // DISABLE == TRUE

		// First setup the GUI
		mAppGui.setup(*mRenderWindow);

		// Create a main menu
		mAppGui.addMenu(std::unique_ptr<tgui::IScreenView>(new tgui::TNewGameMenu));

		// Init all the menus
		mAppGui.initMenus(*mParent);
	}

	nne::IScene::ID TNewGameScene::eventLoop()
	{
		while (mRenderWindow->pollEvent(mAppEvent))
		{
			mAppGui.processEvents(mAppEvent);

			if (mAppEvent.type == sf::Event::Closed)
				mRenderWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderWindow->close();

			// See if we are trying to place a new track
			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.code == sf::Keyboard::T)
				addConductiveTrack();
		}

		return IScene::Same;
	}

	void TNewGameScene::refresh(sf::Time ElapsedTime)
	{
#if ENABLE == TRUE
		mLogicEntity.refresh(ElapsedTime);

		mGraphicEntity.refresh(ElapsedTime);

		// If we 
		if (mAppEvent.type == sf::Event::MouseButtonPressed && mAppEvent.mouseButton.button == sf::Mouse::Left)
		{
			// get a pointer to the selected chip
			auto CurrentChipPtr = mLogicBoard->getSelectedChip();
			auto FormerChipPtr = mLogicBoard->getFormerSelectedChip();

			// get a pointer to the selected track
			auto CurrentTrackPtr = mLogicBoard->getSelectedTrack();

			// Forward declare the value to old the selected pin
			std::size_t SelectedPin = TChipComponent::None;

			// Check if the mouse is pressed and we selected a chip
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && CurrentChipPtr && CurrentTrackPtr && (SelectedPin = CurrentChipPtr->getSelectedPin()) != TChipComponent::None)
			{
				// Get the selected pin bound
				auto& Bound = CurrentChipPtr->getPinGlobalBounds(SelectedPin);

				// Place the point if we just selected one chip
				if (!FormerChipPtr)
				{
					CurrentTrackPtr->placePoint({ Bound.left + Bound.width, Bound.top + (Bound.height / 2) });
				}
				else
				{
					CurrentTrackPtr->endTrack({ Bound.left, Bound.top + (Bound.height / 2) });
				}
			}
		}
#endif // ENABLE == TRUE
	
		// Refresh the UI
		mAppGui.refresh(ElapsedTime);
	}

	void TNewGameScene::update(sf::Time ElapsedTime)
	{
#ifdef ENABLE == TRUE
		mLogicEntity.update(ElapsedTime);

		mGraphicEntity.update(ElapsedTime);
#endif // ENABLE == TRUE

		// Update the UI
		mAppGui.update(ElapsedTime);
	}

	void TNewGameScene::draw()
	{
		// Clear the back buffered window
		mRenderWindow->clear({ 1, 47, 83 });

		// Render all the entity in the the entity manager
#ifdef ENABLE == TRUE
		mGraphicEntity.draw(*mRenderWindow);
#endif // ENABLE == TRUE

		// Draw the ui
		mAppGui.draw();

		// Display the back buffered window
		mRenderWindow->display();
	}

	void TNewGameScene::addConductiveTrack()
	{
		// Create a conductive track entity and add it to the manger
		mGraphicEntity.addEntity(TFactory::makeConductiveTrack(), "ConductiveTrack_" + std::to_string(mTrackCounter++), mParent);

		// Retrieve the newly added entity
		mTempTrack = mGraphicEntity.getEntityByKey("ConductiveTrack_" + std::to_string(mTrackCounter - 1));

		// Init the newly added track
		mTempTrack->init();

		// And adds it to the logic board
		mLogicBoard->placeTrack(mTempTrack.get());

		// And set it as the active track
		mLogicBoard->deselectTrack(true);
		mLogicBoard->deselectChip(true);
		mLogicBoard->setSelectedTrack(mTempTrack->getComponentAsPtr<TConductiveTracks>());
	}

}
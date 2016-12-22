#include "TNewGameScene.h"
#include "TLogicBoardComponent.h"
#include "TGridComponent.h"
#include "TNewGameMenu.h"
#include "TStaticText.h"
#include "TZ80Component.h"
#include "TPinComponent.h"

namespace nne
{

	TNewGameScene::TNewGameScene() :
		IScene::IScene(),
		mInsertionMethod(TInsertionMethod::NONE),
		mTrackCounter(0)
	{
	}

	void TNewGameScene::init()
	{
		// Create a Z80 and RAM entity
		mLogicEntity.addEntity(TFactory::makeZ80(), "Z80");
		mLogicEntity.addEntity(TFactory::makeRam(), "Ram");
		mLogicEntity.initEntities();

		// Get the Z80 and the ram entity
		auto Z80 = mLogicEntity.getEntityByKey("Z80");
		auto Ram = mLogicEntity.getEntityByKey("Ram");

		Z80->getComponentAsPtr<tcomponents::TZ80Component>()->connectRam(Ram);
		if (!Z80->getComponentAsPtr<tcomponents::TZ80Component>()->loadProgram("resources/programs/INC.A01"))
		{
			std::cout << "Error! Could not open the file" << std::endl;

			// Something went bad :(
			return;
		}

		// Create some graphic entity
		mGraphicEntity.addEntity(TFactory::makeLogicBoard(), "LogicBoard", this);
		mGraphicEntity.addEntity(TFactory::makeChip(Z80.get()), "Z80Chip", this);
		mGraphicEntity.addEntity(TFactory::makeChip(Ram.get()), "RamChip", this);
		mGraphicEntity.initEntities();

		// Get the grid component
		mGridComponent = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TGridComponent>();
		mGridComponent->setCellSize({ 23.f, 23.f });
		mGridComponent->setSize({ 1570.f, 980.f });
		mGridComponent->setView(mRenderSurface.getView());

		// Create a Z80 chip and set some property
		auto Z80Chip = mGraphicEntity.getEntityByKey("Z80Chip");
		Z80Chip->getComponentAsPtr<TDrawableComponent>()->setPosition(mGridComponent->transformCellCoords({ 10, 5 }) + sf::Vector2f(0.f, -1.f));

		// Create a RAM chip and set some property
		auto RamChip = mGraphicEntity.getEntityByKey("RamChip");
		RamChip->getComponentAsPtr<TDrawableComponent>()->setPosition(mGridComponent->transformCellCoords({ 30, 5 }) + sf::Vector2f(0.f, -1.f));

		// Create basic connection
		/*{
		// Gets the pin component
		auto& Z80PinComponent = Z80Chip->getComponent<TChipComponent>();
		auto& RamPinComponent = RamChip->getComponent<TChipComponent>();

		// Create the data bus connection
		auto Z80D0Bound = Z80PinComponent.getPinGlobalBounds(13),
		Z80D1Bound = Z80PinComponent.getPinGlobalBounds(14),
		Z80D2Bound = Z80PinComponent.getPinGlobalBounds(11),
		Z80D3Bound = Z80PinComponent.getPinGlobalBounds(7),
		Z80D4Bound = Z80PinComponent.getPinGlobalBounds(6),
		Z80D5Bound = Z80PinComponent.getPinGlobalBounds(8),
		Z80D6Bound = Z80PinComponent.getPinGlobalBounds(9),
		Z80D7Bound = Z80PinComponent.getPinGlobalBounds(12);

		auto RamD0Bound = RamPinComponent.getPinGlobalBounds(10),
		RamD1Bound = RamPinComponent.getPinGlobalBounds(11),
		RamD2Bound = RamPinComponent.getPinGlobalBounds(12),
		RamD3Bound = RamPinComponent.getPinGlobalBounds(14),
		RamD4Bound = RamPinComponent.getPinGlobalBounds(15),
		RamD5Bound = RamPinComponent.getPinGlobalBounds(16),
		RamD6Bound = RamPinComponent.getPinGlobalBounds(17),
		RamD7Bound = RamPinComponent.getPinGlobalBounds(18);

		// Create 8 single track
		for (mTrackCounter = 0; mTrackCounter < 8; ++mTrackCounter)
		{
		mGraphicEntity.addEntity(TFactory::makeConductiveTrack(), "conductive_track_D" + std::to_string(mTrackCounter), this);
		mGraphicEntity.initLastEntity();
		}

		// Retrieve those track
		auto&	ConductiveTrack0 = mGraphicEntity.getEntityByKey("conductive_track_D0")->getComponent<TConductiveTracks>(),
		ConductiveTrack1 = mGraphicEntity.getEntityByKey("conductive_track_D1")->getComponent<TConductiveTracks>(),
		ConductiveTrack2 = mGraphicEntity.getEntityByKey("conductive_track_D2")->getComponent<TConductiveTracks>(),
		ConductiveTrack3 = mGraphicEntity.getEntityByKey("conductive_track_D3")->getComponent<TConductiveTracks>(),
		ConductiveTrack4 = mGraphicEntity.getEntityByKey("conductive_track_D4")->getComponent<TConductiveTracks>(),
		ConductiveTrack5 = mGraphicEntity.getEntityByKey("conductive_track_D5")->getComponent<TConductiveTracks>(),
		ConductiveTrack6 = mGraphicEntity.getEntityByKey("conductive_track_D6")->getComponent<TConductiveTracks>(),
		ConductiveTrack7 = mGraphicEntity.getEntityByKey("conductive_track_D7")->getComponent<TConductiveTracks>();

		ConductiveTrack0.placePoint({ Z80D0Bound.left + Z80D0Bound.width, Z80D0Bound.top + (Z80D0Bound.height / 2) });
		ConductiveTrack0.placePoint(sf::Vector2f(Z80D0Bound.left + Z80D0Bound.width, Z80D0Bound.top + (Z80D0Bound.height / 2)) - sf::Vector2f(100.f, 0.f));
		ConductiveTrack0.placePoint(sf::Vector2f(Z80D0Bound.left + Z80D0Bound.width, Z80D0Bound.top + (Z80D0Bound.height / 2)) - sf::Vector2f(100.f, 0.f) + sf::Vector2f(0, 300.f));
		ConductiveTrack0.placePoint(sf::Vector2f(Z80D0Bound.left + Z80D0Bound.width, Z80D0Bound.top + (Z80D0Bound.height / 2)) - sf::Vector2f(100.f, 0.f) + sf::Vector2f(0, 300.f) + sf::Vector2f(800.f, 0.f));
		mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TLogicBoardComponent>()->placeTrack(&ConductiveTrack0);
		}*/

		// Create the logic board who will contain all the chip and set some property
		mLogicBoard = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TLogicBoardComponent>();
		mLogicBoard->placeChip(Z80Chip.get());
		mLogicBoard->placeChip(RamChip.get());
		
		mRenderSurface.create(mRenderWindow->getSize().x - 300u, mRenderWindow->getSize().y - 50u);
		mRenderSurface.move(300.f, 50.f);

		mGuiManager.addWidget<tgui::TNewGameMenu>();
		mGuiManager.getLastAdded();
		std::dynamic_pointer_cast<tgui::TNewGameMenu>(mGuiManager.getLastAdded())->init(&mGuiManager);
	}

	nne::IScene::ID TNewGameScene::eventLoop()
	{
		while (mRenderWindow->pollEvent(mAppEvent))
		{
			mGuiManager.processEvents(mAppEvent, *mRenderWindow);

			if (mAppEvent.type == sf::Event::Closed)
				mRenderWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderWindow->close();
						
			// If we scrolled the mouse wheel
			if (mAppEvent.type == sf::Event::MouseWheelScrolled)
			{
				if (mAppEvent.mouseWheelScroll.delta < 0)
				{
					mRenderSurface.setZoomView(1.5f);
					mGridComponent->forceRefresh();
				}
				else
				{
					mRenderSurface.setZoomView(0.5f);
					mGridComponent->forceRefresh();
				}
			}

			// If we pressed a keyboard key
			if (mAppEvent.type == sf::Event::KeyPressed)
			{
				switch (mAppEvent.key.code)
				{
					// See if we are trying to place a new track
					case sf::Keyboard::T:
						addConductiveTrack();
						break;

					// Reset the insertion method
					case sf::Keyboard::R:
						mInsertionMethod = TInsertionMethod::NONE;
						break;

					// Reset the CPU
					case sf::Keyboard::M:
						mLogicEntity.getEntityByKey("Z80")->getComponentAsPtr<tcomponents::TZ80Component>()->reset();
						break;

					// Pause CPU execution
					case sf::Keyboard::K:
						mLogicEntity.getEntityByKey("Z80")->getComponentAsPtr<tcomponents::TZ80Component>()->pauseExecution();
						break;

					// Resume CPU execution
					case sf::Keyboard::J:
						mLogicEntity.getEntityByKey("Z80")->getComponentAsPtr<tcomponents::TZ80Component>()->resumeExecution();
						break;

					// Restart CPU execution
					case sf::Keyboard::L:
						mLogicEntity.getEntityByKey("Z80")->getComponentAsPtr<tcomponents::TZ80Component>()->restartExecution();
						break;
				
					// Zoom in
					case sf::Keyboard::Add:
					{
						mRenderSurface.setZoomView(0.5f);
						mGridComponent->forceRefresh();
					}break;

					// Zoom out
					case sf::Keyboard::Subtract:
					{
						mRenderSurface.setZoomView(1.5f);
						mGridComponent->forceRefresh();
					}break;

					// Move view left (0)
					case sf::Keyboard::Left:
					{
						mRenderSurface.moveView(0);
						mGridComponent->forceRefresh();
					}break;
					case sf::Keyboard::A:
					{
						mRenderSurface.moveView(1);
						mGridComponent->forceRefresh();
					}break;

					// Move view right (1)
					case sf::Keyboard::Right:
					{
						mRenderSurface.moveView(1);
						mGridComponent->forceRefresh();
					}break;
					case sf::Keyboard::D:
					{
						mRenderSurface.moveView(0);
						mGridComponent->forceRefresh();
					}break;

					// Move view left (2)
					case sf::Keyboard::Down:
					{
						mRenderSurface.moveView(2);
						mGridComponent->forceRefresh();
					}break;
					case sf::Keyboard::S:
					{
						mRenderSurface.moveView(3);
						mGridComponent->forceRefresh();
					}break;

					// Move view right (3)
					case sf::Keyboard::Up:
					{
						mRenderSurface.moveView(3);
						mGridComponent->forceRefresh();
					}break;
					case sf::Keyboard::W:
					{
						mRenderSurface.moveView(2);
						mGridComponent->forceRefresh();
					}break;
				}
			}

			if (mAppEvent.type == sf::Event::KeyReleased && mAppEvent.key.code == sf::Keyboard::P)
			{
				// get a pointer to the selected track
				auto CurrentTrackPtr = mLogicBoard->getSelectedTrack();
				
				if (CurrentTrackPtr)
					CurrentTrackPtr->toggleDraw();
			}

			// IF we moved the mouse
			if (mAppEvent.type == sf::Event::MouseMoved)
			{
				// get a pointer to the selected track
				auto CurrentTrackPtr = mLogicBoard->getSelectedTrack();

				if (CurrentTrackPtr)
				{
					auto MousePos = static_cast<sf::Vector2i>(convertMouseCoordinate(sf::Mouse::getPosition(*mRenderWindow)));
					auto GridCoord = mGridComponent->mouseCoordsToWindowCellCoords(MousePos);
					auto CellPos = mGridComponent->transformCellCoords(GridCoord);

					CurrentTrackPtr->placePointTemp(CellPos);
				}
			}

			// If we have release the mouse after a click
			if (mAppEvent.type == sf::Event::MouseButtonReleased)
			{
				// get a pointer to the selected track
				auto CurrentTrackPtr = mLogicBoard->getSelectedTrack();

				// If we have selected a track
				if (CurrentTrackPtr)
				{
					CurrentTrackPtr->confirmPoints();

					// get a pointer to the selected chip
					auto CurrentChipPtr = mLogicBoard->getSelectedChip();
					auto FormerChipPtr = mLogicBoard->getFormerSelectedChip();

					// If we have drawn a track between 2 chips, exit track drawing mode, and deselect the currently selected chips and track
					if (CurrentChipPtr && FormerChipPtr)
					{
						// Stop the drawing mode
						CurrentTrackPtr->toggleDraw();

						// Connect the pins
						auto& PinNumber1 = CurrentChipPtr->getSelectedPinNumber();
						auto& PinNumber2 = FormerChipPtr->getSelectedPinNumber();

						auto& SelectedPin1 = CurrentChipPtr->getSelectedPin();
						auto& SelectedPin2 = FormerChipPtr->getSelectedPin();
						tcomponents::TPinComponentUtility::connectPins(SelectedPin1, SelectedPin2);

						// Reset the chip's pin selected status
						CurrentChipPtr->deselectPin();
						FormerChipPtr->deselectPin();

						// Deselect the chip and track from the logic board
						mLogicBoard->deselectChip(true);
						mLogicBoard->deselectTrack(true);
					}
				}

			}

			updateDebugInfo();
		}

		return IScene::Same;
	}

	void TNewGameScene::refresh(sf::Time ElapsedTime)
	{
		// Deselect the eventually selected chip
		//mLogicBoard->deselectChip(true);

		mLogicEntity.refresh(ElapsedTime);

		mGraphicEntity.refresh(ElapsedTime);

		// If we pressed the mouse
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// get a pointer to the selected chip
			auto CurrentChipPtr = mLogicBoard->getSelectedChip();
			auto FormerChipPtr = mLogicBoard->getFormerSelectedChip();

			// get a pointer to the selected track
			auto CurrentTrackPtr = mLogicBoard->getSelectedTrack();

			// If we are trying to place a track
			if (mInsertionMethod == TInsertionMethod::TRACK)
			{
				// Forward declare the SelectedPin variable
				std::size_t SelectedPin;

				// If we clicked on top of a pin gets is bound to better place the track
				if (CurrentChipPtr && (SelectedPin = CurrentChipPtr->getSelectedPin()) != TChipComponent::None)
				{
					auto& Bound = CurrentChipPtr->getPinGlobalBounds(SelectedPin);

					CurrentTrackPtr->placePoint({ Bound.left + Bound.width, Bound.top + (Bound.height / 2) });
				}
				// Otherwise place it where we clicked on the mouse
				else
				{
					// Get the adjusted mouse position
					auto AdjustedMouseCoo = convertMouseCoordinate(sf::Mouse::getPosition(*mRenderWindow));

					CurrentTrackPtr->placePoint(AdjustedMouseCoo);
				}
			}
		}*/

		// If we 
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && false)
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
		}*/
	}

	void TNewGameScene::update(sf::Time ElapsedTime)
	{
		mLogicEntity.update(ElapsedTime);

		mGraphicEntity.update(ElapsedTime);
	}

	void TNewGameScene::draw()
	{
		// Clear the render surface
		mRenderWindow->clear({ 1, 47, 83 });
		mRenderSurface.clear({ 1, 47, 83 });

		// Renders the entity
		for (auto& GraphicsEntity : mGraphicEntity)
			mRenderSurface.draw(GraphicsEntity->getComponent<TDrawableComponent>());

		// Renders the gui
		for (auto& Widget : mGuiManager)
			mRenderWindow->draw(*Widget);
		
		// Apply the RenderSurface onto the rendering window
		mRenderSurface.render(mRenderWindow);

		// Display the window
		mRenderWindow->display();
	}

	void TNewGameScene::addConductiveTrack()
	{
		// Create a conductive track entity and add it to the manger
		mGraphicEntity.addEntity(TFactory::makeConductiveTrack(), "ConductiveTrack_" + std::to_string(mTrackCounter++), this);

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

		// Change the insertion method
		mInsertionMethod = TInsertionMethod::TRACK;
	}

	sf::Vector2f TNewGameScene::convertMouseCoordinate(sf::Vector2i MouseCoordinate)
	{
		// Since the render surface it's smaller then the render window and offsetted to the right and bottom
		// we need to transform the mouse coordinate from the sf::RenderWindow to the actual sf::RenderSurface
		// We do this by removing the offset of the sf::RenderSurface to the mouse coordinate
		MouseCoordinate -= static_cast<sf::Vector2i>(mRenderSurface.getPosition());

		// Return the mapped coordinate 
		return mRenderSurface.mapPixelToCoords(MouseCoordinate);
	}

	void TNewGameScene::updateDebugInfo()
	{
		auto XStaticText = mGuiManager.getWidgetWithCast<tgui::TStaticText>("XVALUE_TEXT");
		auto YStaticText = mGuiManager.getWidgetWithCast<tgui::TStaticText>("YVALUE_TEXT"); 
		auto ZStaticText = mGuiManager.getWidgetWithCast<tgui::TStaticText>("ZINDEX_TEXT");

		auto& MousePos = sf::Mouse::getPosition(*mRenderWindow);
		auto& RenderSurfacePos = static_cast<sf::Vector2i>(mRenderSurface.getPosition());
		auto ZoomLevel = static_cast<sf::Uint32>(mRenderSurface.getZoomView() * 100);

		if (MousePos.x >= RenderSurfacePos.x && MousePos.y >= RenderSurfacePos.y)
		{
			XStaticText->setCaption("X:" + std::to_string(MousePos.x - RenderSurfacePos.x));
			YStaticText->setCaption("Y:" + std::to_string(MousePos.y - RenderSurfacePos.y));
			ZStaticText->setCaption("Z:" + std::to_string(ZoomLevel) + "%");
		}
	}

}
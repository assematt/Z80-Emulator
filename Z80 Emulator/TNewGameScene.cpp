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
		mWireCounter(0),
		mChipCounter(0),
		mBusCounter(0),
		mDrawingFromBusToChip(false)
	{
	}

	void TNewGameScene::init()
	{
		// Create some graphic entity
		mGraphicEntity.addEntity(TFactory::makeLogicBoard(), "LogicBoard", this);
		mGraphicEntity.initEntities();

		// Get the grid component
		mGridComponent = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TGridComponent>();
		mGridComponent->setCellSize({ 23.f, 23.f });
		mGridComponent->setSize({ 1570.f, 980.f });
		mGridComponent->setView(mRenderSurface.getView());
		
		// Create the logic board who will contain all the chip and set some property
		mLogicBoard = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TLogicBoardComponent>();
		
		// Create a surface where to render all our graphic entities
		mRenderSurface.create(mRenderWindow->getSize().x - 300u, mRenderWindow->getSize().y - 50u);
		mRenderSurface.setPosition(300.f, 50.f);

		// Init the GUI
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
					// See if we are trying to place a new wire
					case sf::Keyboard::T:
					{
						addWire();
					}break;

					// See if we are trying to place a new bus
					case sf::Keyboard::Y:
					{
						addBus();
					}break;

					// See if we are trying to place a LED
					case sf::Keyboard::H:
					{
						addChip("LED");
					}break;

					// See if we are trying to place a z80
					case sf::Keyboard::G:
					{
						addChip("Z80");
					}break;

					// See if we are trying to place a ram
					case sf::Keyboard::F:
					{
						addChip("RAM");
					}break;
					
					// See if we are trying to load a program
					case sf::Keyboard::V:
					{
						// Get the Z80 and the ram entity
						auto Z80 = mGraphicEntity.getEntityByKey("Z80");
						auto Ram = mGraphicEntity.getEntityByKey("Ram");

						// Se if both the CPU and the RAM are placed into the logic board
						if (Z80 && Ram)
						{
							Z80->getComponentAsPtr<tcomponents::TZ80Component>()->connectRam(Ram);
							if (!Z80->getComponentAsPtr<tcomponents::TZ80Component>()->loadProgram("resources/programs/INC.A01"))
								std::cout << "Error! Could not open the file" << std::endl;
						}
						
					}break;

					// Reset the insertion method
					case sf::Keyboard::R:
						mInsertionMethod = TInsertionMethod::NONE;
						break;

					// Reset the CPU
					case sf::Keyboard::M:
					{
						auto Z80 = mGraphicEntity.getEntityByKey("Z80");

						if (Z80)
							Z80->getComponentAsPtr<tcomponents::TZ80Component>()->reset();
					}break;

					// Pause CPU execution
					case sf::Keyboard::K:
					{
						auto Z80 = mGraphicEntity.getEntityByKey("Z80");

						if (Z80)
							Z80->getComponentAsPtr<tcomponents::TZ80Component>()->pauseExecution();
					}break;

					// Resume CPU execution
					case sf::Keyboard::J:
					{
						auto Z80 = mGraphicEntity.getEntityByKey("Z80");

						if (Z80)
							Z80->getComponentAsPtr<tcomponents::TZ80Component>()->resumeExecution();
					}break;

					// Restart CPU execution
					case sf::Keyboard::L:
					{
						auto Z80 = mGraphicEntity.getEntityByKey("Z80");

						if (Z80)
							Z80->getComponentAsPtr<tcomponents::TZ80Component>()->restartExecution();
					}break;
				
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

					// Toggle conductive wire
					case sf::Keyboard::P:
					{
						// get a pointer to the selected wire
						auto CurrentWire = mLogicBoard->getSelectedWire();

						if (CurrentWire)
							CurrentWire->toggleDraw();
					}break;
				}
			}

			// IF we moved the mouse
			if (mAppEvent.type == sf::Event::MouseMoved)
			{
				// Get the mouse coordinate and transform them to make them stick to the grid
				auto MousePos = static_cast<sf::Vector2i>(convertMouseCoordinate(sf::Mouse::getPosition(*mRenderWindow)));
				auto GridCoord = mGridComponent->mouseCoordsToWindowCellCoords(MousePos);
				auto CellPos = mGridComponent->transformCellCoords(GridCoord);

				switch (mInsertionMethod)
				{
					// If we are using the chip tool
					case TInsertionMethod::CHIP:
					{
						// get a pointer to the selected wire
						auto CurrentChip = mLogicBoard->getSelectedChip();

						if (CurrentChip && !CurrentChip->isPlaced())
						{
							mTempChip->getComponentAsPtr<TDrawableComponent>()->setPosition(CellPos);

							/// Does the collision check
							mLogicBoard->checkCollisions(CurrentChip);
						}
					}break;

					// If we are using the wire tool
					case TInsertionMethod::WIRE:
					{
						// get a pointer to the selected wire
						auto CurrentWire = mLogicBoard->getSelectedWire();

						if (CurrentWire)
							CurrentWire->placePointTemp(CellPos);
					}break;

					// If we are using the bus tool
					case TInsertionMethod::BUS:	
					{
						// get a pointer to the selected wire
						auto CurrentBus = mLogicBoard->getSelectedBus();

						if (CurrentBus)
							CurrentBus->placePointTemp(CellPos);
					}break;

					// If we are not using any tool
					case TInsertionMethod::NONE:
						break;
				}
			}

			// If we have release the mouse after a left click
			if (mAppEvent.type == sf::Event::MouseButtonReleased && mAppEvent.mouseButton.button == sf::Mouse::Left)
			{

				switch (mInsertionMethod)
				{
					// If we are using the chip tool
					case TInsertionMethod::CHIP:
					{
						// get a pointer to the selected wire
						auto CurrentChip = mLogicBoard->getSelectedChip();

						if (CurrentChip && !CurrentChip->isPlaced() && CurrentChip->isValid())
						{
							CurrentChip->setPlacedStatus(true);
						}
					}break;

					// If we are using the wire tool
					case TInsertionMethod::WIRE:
					{
						// get a pointer to the selected wire
						auto CurrentWire = mLogicBoard->getSelectedWire();

						// If we have selected a wire
						if (CurrentWire)
						{
							CurrentWire->confirmPoints();

							// get a pointer to the selected chip
							auto CurrentChip = mLogicBoard->getSelectedChip();

							// get a pointer to the former selected chip
							auto FormerChip = mLogicBoard->getFormerSelectedChip();

							// get a pointer to the selected bus
							auto CurrentBus = mLogicBoard->getSelectedBus();

							// Establish if we are drawing from a bus to chip or vice-versa
							if (CurrentChip && !CurrentBus)
								mDrawingFromBusToChip = false;
							else if (!CurrentChip && CurrentBus)
								mDrawingFromBusToChip = true;

							// If we have drawn a wire between 2 chips, exit wire drawing mode, and deselect the currently selected chips and wire
							if (CurrentChip && FormerChip)
							{
								// Stop the drawing mode
								CurrentWire->toggleDraw();

								// Connect the pins
								tcomponents::TPinComponentUtility::connectPins(CurrentChip->getSelectedPin(), FormerChip->getSelectedPin());

								// Reset the chip's pin selected status
								CurrentChip->deselectPin();
								FormerChip->deselectPin();

								// Deselect the chip/wire/bus from the logic board
								mLogicBoard->deselectEverything();

								// Start the drawing of a new wire
								addWire();
							}

							// If we have draw a wire between a chip and a bus, exit wire drawing mode, and deselect the currently selected chips and wire
							if (CurrentChip && CurrentBus)
							{
								// Stop the drawing mode
								CurrentWire->toggleDraw();
								
								// Connect the pin to the bus as an entry wire
								if (mDrawingFromBusToChip)
									CurrentBus->connectExitWire(CurrentChip->getSelectedPin());
								else
									CurrentBus->connectEntryWire(CurrentChip->getSelectedPin());

								// Reset the chip's pin selected status
								CurrentChip->deselectPin();

								// Deselect the chip/wire/bus from the logic board
								mLogicBoard->deselectEverything();

								// Start the drawing of a new wire
								addWire();
							}
						
						}
					}break;

					// If we are using the bus tool
					case TInsertionMethod::BUS:
					{
						// get a pointer to the selected bus
						auto CurrentBus = mLogicBoard->getSelectedBus();

						// If we have selected a bus
						if (CurrentBus)
							CurrentBus->confirmPoints();

						// Start the drawing of a new bus
						//addBus();
					}break;

					// If we are not using any tool
					case TInsertionMethod::NONE:
					{
						mLogicBoard->deselectEverything();
					}break;
				}
			}

			// If we have release the mouse after a right click
			if (mAppEvent.type == sf::Event::MouseButtonReleased && mAppEvent.mouseButton.button == sf::Mouse::Right)
			{

				switch (mInsertionMethod)
				{
					case TInsertionMethod::WIRE:
					{
						// get a pointer to the selected wire
						auto CurrentWire = mLogicBoard->getSelectedWire();
						
						// If we have a valid wire selected we stop the drawing and deselect it
						if (CurrentWire)
						{
							CurrentWire->toggleDraw();
							mLogicBoard->deselectWire();
						}
					}break;

					case TInsertionMethod::BUS:
					{
						// get a pointer to the selected bus
						auto CurrentBus = mLogicBoard->getSelectedBus();
						if (CurrentBus)
						{
							CurrentBus->toggleDraw();
							mLogicBoard->deselectBus();
						}
					}

				}
			}

			updateDebugInfo();
		}

		return IScene::Same;
	}

	void TNewGameScene::refresh(sf::Time ElapsedTime)
	{
		mGraphicEntity.refresh(ElapsedTime);
	}

	void TNewGameScene::update(sf::Time ElapsedTime)
	{
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

		// Renders the GUI
		for (auto& Widget : mGuiManager)
			mRenderWindow->draw(*Widget);
		
		// Apply the RenderSurface onto the rendering window
		mRenderSurface.render(mRenderWindow);

		// Display the window
		mRenderWindow->display();
	}

	void TNewGameScene::addWire()
	{
		// Create a wire entity and add it to the manger
		mGraphicEntity.addEntity(TFactory::makeWire(), "Wire_" + std::to_string(mWireCounter++), this);

		// Retrieve the newly added entity
		mTempWire = mGraphicEntity.getEntityByKey("Wire_" + std::to_string(mWireCounter - 1));

		// Init the newly added wire
		mTempWire->init();

		// And adds it to the logic board
		mLogicBoard->placeWire(mTempWire.get());

		// And set it as the active wire
		mLogicBoard->deselectEverything();
		mLogicBoard->setSelectedWire(mTempWire->getComponentAsPtr<TWireComponent>());

		// Allow to draw the wire
		mLogicBoard->getSelectedWire()->toggleDraw();

		// Change the insertion method
		mInsertionMethod = TInsertionMethod::WIRE;
	}

	void TNewGameScene::addBus()
	{
		// Create a conductive bus entity and add it to the manger
		mGraphicEntity.addEntity(TFactory::makeBus(), "Bus_" + std::to_string(mBusCounter++), this);

		// Retrieve the newly added entity
		mTempBus = mGraphicEntity.getEntityByKey("Bus_" + std::to_string(mBusCounter - 1));

		// Init the newly added bus
		mTempBus->init();

		// And adds it to the logic board
		mLogicBoard->placeBus(mTempBus.get());

		// And set it as the active bus
		mLogicBoard->deselectEverything();
		mLogicBoard->setSelectedBus(mTempBus->getComponentAsPtr<TBusComponent>());

		// Allow to draw the bus
		mLogicBoard->getSelectedBus()->toggleDraw();

		// Change the insertion method
		mInsertionMethod = TInsertionMethod::BUS;
	}

	void TNewGameScene::addChip(const std::string& ChipToAdd)
	{
		std::to_string(mChipCounter++);

		// If we are creating a z80 chip and we didn't do it before
		if (ChipToAdd == "Z80" && !mGraphicEntity.getEntityByKey("Z80"))
		{
			// Create a graphic z80 chip
			mGraphicEntity.addEntity(TFactory::makeZ80(), "Z80", this);

			// Get newly create z80 graphic entity and initialize it
			auto Z80Chip = mGraphicEntity.getEntityByKey("Z80");
			Z80Chip->init();
			Z80Chip->getComponent<TChipComponent>().setPlacedStatus(false);
			
			// And adds it to the logic board
			mLogicBoard->placeChip(Z80Chip.get());

			// And set it as the active chip
			mLogicBoard->deselectEverything();
			mLogicBoard->setSelectedChip(Z80Chip->getComponentAsPtr<TChipComponent>());

			mTempChip = Z80Chip;

			// Change the insertion method
			mInsertionMethod = TInsertionMethod::CHIP;
		}
		// If we are creating a RAM chip
		else if (ChipToAdd == "RAM" && !mGraphicEntity.getEntityByKey("Ram"))
		{
			// Create a graphic z80 chip
			mGraphicEntity.addEntity(TFactory::makeRam(), "Ram", this);

			// Get newly create z80 graphic entity and initialize it
			auto RamChip = mGraphicEntity.getEntityByKey("Ram");
			RamChip->init();
			RamChip->getComponent<TChipComponent>().setPlacedStatus(false);

			// And adds it to the logic board
			mLogicBoard->placeChip(RamChip.get());

			// And set it as the active chip
			mLogicBoard->deselectEverything();
			mLogicBoard->setSelectedChip(RamChip->getComponentAsPtr<TChipComponent>());

			mTempChip = RamChip;

			// Change the insertion method
			mInsertionMethod = TInsertionMethod::CHIP;
		}
		// If we are creating a LED
		else if (ChipToAdd == "LED")
		{
			// Create a graphic z80 chip
			mGraphicEntity.addEntity(TFactory::makeLed(), "LED_" + std::to_string(mChipCounter++), this);

			// Get newly create z80 graphic entity and initialize it
			auto RamChip = mGraphicEntity.getEntityByKey("LED_" + std::to_string(mChipCounter - 1));
			RamChip->init();
			RamChip->getComponent<TChipComponent>().setPlacedStatus(false);

			// And adds it to the logic board
			mLogicBoard->placeChip(RamChip.get());

			// And set it as the active chip
			mLogicBoard->deselectEverything();
			mLogicBoard->setSelectedChip(RamChip->getComponentAsPtr<TChipComponent>());

			mTempChip = RamChip;

			// Change the insertion method
			mInsertionMethod = TInsertionMethod::CHIP;
		}
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
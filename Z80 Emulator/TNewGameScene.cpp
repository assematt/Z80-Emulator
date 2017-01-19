#include "TNewGameScene.h"
#include "TLogicBoardComponent.h"
#include "TGridComponent.h"
#include "TNewGameMenu.h"
#include "TStaticText.h"
#include "TZ80Component.h"
#include "TPinComponent.h"
#include "TEventComponent.h"
#include "TDialogWindow.h"

namespace nne
{

	TNewGameScene::TNewGameScene() :
		IScene::IScene(),
		mWireCounter(0),
		mChipCounter(0),
		mBusCounter(0),
		mDrawingFromBusToChip(false),
		mRenderCanvas(nullptr)
	{
	}

	void TNewGameScene::init()
	{
		// Get the size of the renderWIndow
		auto WindowSize = mRenderWindow->getSize();

		// Create some graphic entity
		mGraphicEntity.addEntity(TFactory::makeLogicBoard(), "LogicBoard", this);
		mGraphicEntity.initEntities();

		// Create the logic board who will contain all the chip and set some property
		mLogicBoard = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TLogicBoardComponent>();

		// Init the GUI
		tgui::TNewGameMenu::Ptr NewGameMenu = std::make_shared<tgui::TNewGameMenu>("NEW_GAME_MENU");		
		NewGameMenu->setSize(WindowSize);
		NewGameMenu->init(&mGuiManager);
		mGuiManager.addWidget(NewGameMenu);

		// Cache the render-canvas and attach the render surface to it
		mRenderCanvas = mGuiManager.getWidget<tgui::TRenderCanvas>("RENDER_CANVAS").get();

		// Get the grid component and set some property
		mGridComponent = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TGridComponent>();
		mGridComponent->setCellSize({ 23.f, 23.f });
		mGridComponent->setSize(static_cast<sf::Vector2f>(mRenderCanvas->getSize()));

		// Set the view of the grid component to be the one of the render canvas
		mGridComponent->setView(mRenderCanvas->getView());

		// Set-up some GUI event for the left side tools
		mGuiManager.getWidget("INSERT_CHIP_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			auto& ChipList = *mGuiManager.getWidget("CHIP_LIST_PANEL");

			// If we are displaying the chip list close it
			if (ChipList.isVisible())
			{
				ChipList.setVisible(false);

				mGuiManager.getWidget("INSERT_WIRE_BUTTON")->move(0.f, -210.f);
				mGuiManager.getWidget("INSERT_BUS_BUTTON")->move(0.f, -210.f);
			}
			// Otherwise show it
			else
			{
				ChipList.setVisible(true);

				mGuiManager.getWidget("INSERT_WIRE_BUTTON")->move(0.f, 210.f);
				mGuiManager.getWidget("INSERT_BUS_BUTTON")->move(0.f, 210.f);
			}
		});
		mGuiManager.getWidget("INSERT_WIRE_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addWire();
		});
		mGuiManager.getWidget("INSERT_BUS_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addBus();
		});
		
		// Set-up some GUI event for the button that create components
		mGuiManager.getWidget("INSERT_CPU_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {

			// Look for a z80 entity in the entities vector
			auto Z80Temp = mGraphicEntity.getEntityByKey("Z80");

			// If we don't find it add it to the entity vector
			if (!Z80Temp)
			{
				addChip("Z80");
			}
			// Otherwise if it already exit and we already have placed one display and error message
			else if (Z80Temp->getComponent<TChipComponent>().isPlaced())
			{
				tgui::TDialogWindow::Ptr TempWindow = std::make_shared<tgui::TDialogWindow>(mGuiManager);
				TempWindow->setName("TEMP_DIALOG_WINDOW");
				TempWindow->setTitleString("Error!");
				TempWindow->setMessageString("You can only place down one z80 CPU!");
				mGuiManager.addWidget(TempWindow, 10);
				mGuiManager.getWidget<tgui::TDialogWindow>("TEMP_DIALOG_WINDOW")->show(*mRenderWindow, tgui::TReferencePoint::CENTER);
			}

		});
		mGuiManager.getWidget("INSERT_RAM_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			// Look for a z80 entity in the entities vector
			auto RamTemp = mGraphicEntity.getEntityByKey("RAM");

			// If we don't find it add it to the entity vector
			if (!RamTemp)
			{
				addChip("RAM");
			}
			// Otherwise if it already exit and we already have placed one display and error message
			else if (RamTemp->getComponent<TChipComponent>().isPlaced())
			{
				tgui::TDialogWindow::Ptr TempWindow = std::make_shared<tgui::TDialogWindow>(mGuiManager);
				TempWindow->setName("TEMP_DIALOG_WINDOW");
				TempWindow->setTitleString("Error!");
				TempWindow->setMessageString("You can only place down one RAM!");
				mGuiManager.addWidget(TempWindow, 10);
				mGuiManager.getWidget<tgui::TDialogWindow>("TEMP_DIALOG_WINDOW")->show(*mRenderWindow, tgui::TReferencePoint::CENTER);
			}
		});
		mGuiManager.getWidget("INSERT_NAND_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addChip("NAND");
		});
		mGuiManager.getWidget("INSERT_LED_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addChip("LED");
		});
		mGuiManager.getWidget("INSERT_POWER_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addChip("VCC");
		});
		mGuiManager.getWidget("INSERT_GROUND_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addChip("GND");
		});

		// Set-up some GUI event to the RenderCanvas
		mRenderCanvas->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			EventData.mouseButton.button == sf::Mouse::Left ? handleLeftMouseUpEvent() : handleRightMouseUpEvent();
		});
		mRenderCanvas->attachEvent(tgui::events::onMouseMove, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			handleMouseMoveEvent(sf::Vector2f(EventData.mouseMove.x - 300, EventData.mouseMove.y - 50));

			updateDebugInfo();
		});
		mRenderCanvas->attachEvent(tgui::events::onMouseWheelUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			mRenderCanvas->zoomOut();
			mGridComponent->forceRefresh();

			updateDebugInfo();
		});
		mRenderCanvas->attachEvent(tgui::events::onMouseWheelDown, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			mRenderCanvas->zoomIn();
			mGridComponent->forceRefresh();

			updateDebugInfo();
		});

		// Key pressed event
		mRenderCanvas->attachEvent(tgui::events::onKeyPress, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			handleKeyboardInputs(EventData.key.code);
		});
	}

	nne::IScene::ID TNewGameScene::eventLoop()
	{
		nne::IScene::ID NewSceneID = IScene::Same;

		while (mRenderWindow->pollEvent(mAppEvent))
		{
			// Process the UI event
			NewSceneID = mGuiManager.processEvents(mAppEvent, *mRenderWindow);
			mGraphicEntity.processEvents(mAppEvent, *mRenderWindow, *mRenderCanvas);

			if (mAppEvent.type == sf::Event::Closed)
				mRenderWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderWindow->close();
		}

		return NewSceneID;
	}

	void TNewGameScene::handleMouseMoveEvent(const sf::Vector2f& MousePos)
	{
		// Get the mouse coordinate and transform them to make them stick to the grid		
		auto MousePosAdj = mRenderCanvas->mapPixelToCoords(static_cast<sf::Vector2i>(MousePos));
		auto GridCoord = mGridComponent->mouseCoordsToWindowCellCoords(static_cast<sf::Vector2i>(MousePosAdj));
		auto CellPos = mGridComponent->transformCellCoords(GridCoord);

		auto& InsertionMethod = mLogicBoard->getInsertionMethod();

		switch (InsertionMethod)
		{
			// If we are using the chip tool
			case TLogicBoardComponent::TInsertionMethod::CHIP:
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
			case TLogicBoardComponent::TInsertionMethod::WIRE:
			{
				// get a pointer to the selected wire
				auto CurrentWire = mLogicBoard->getSelectedWire();

				if (CurrentWire)
					CurrentWire->placePointTemp(CellPos);
			}break;

			// If we are using the bus tool
			case TLogicBoardComponent::TInsertionMethod::BUS:
			{
				// get a pointer to the selected wire
				auto CurrentBus = mLogicBoard->getSelectedBus();

				if (CurrentBus)
					CurrentBus->placePointTemp(CellPos);
			}break;

			// If we are not using any tool
			case TLogicBoardComponent::TInsertionMethod::NONE:
				break;
		}
	}

	void TNewGameScene::handleRightMouseUpEvent()
	{
		auto& InsertionMethod = mLogicBoard->getInsertionMethod();

		switch (InsertionMethod)
		{
			// Stop the chip tool
			case TLogicBoardComponent::TInsertionMethod::CHIP:
			{
				// Remove temporary Entity
				removeTemporaryEntity();
			}break;

			// Stop the wire tool
			case TLogicBoardComponent::TInsertionMethod::WIRE:
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

			// Stop the bus tool
			case TLogicBoardComponent::TInsertionMethod::BUS:
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

	void TNewGameScene::handleLeftMouseUpEvent()
	{
		auto& InsertionMethod = mLogicBoard->getInsertionMethod();

		switch (InsertionMethod)
		{
			// If we are using the chip tool
			case TLogicBoardComponent::TInsertionMethod::CHIP:
			{
				// get a pointer to the selected wire
				auto CurrentChip = mLogicBoard->getSelectedChip();

				if (CurrentChip && !CurrentChip->isPlaced() && CurrentChip->isValid())
				{
					CurrentChip->setPlacedStatus(true);

					mLogicBoard->setInsertionMethod(TLogicBoardComponent::TInsertionMethod::NONE);
					mLogicBoard->deselectEverything();
				}
			}break;

			// If we are using the wire tool
			case TLogicBoardComponent::TInsertionMethod::WIRE:
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
						TPinComponentUtility::connectPins(CurrentChip->getSelectedPin(), FormerChip->getSelectedPin());

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
			case TLogicBoardComponent::TInsertionMethod::BUS:
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
			case TLogicBoardComponent::TInsertionMethod::NONE:
			{
				//mLogicBoard->deselectEverything();
			}break;
		}
	}

	void TNewGameScene::handleKeyboardInputs(const sf::Keyboard::Key& KeyCode)
	{
		switch (KeyCode)
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

			// See if we are trying to place a NAND Chip
			case sf::Keyboard::Numpad4:
			{
				addChip("NAND");
			}break;

			// If we are trying to place a VCC
			case sf::Keyboard::Numpad1:
			{
				addChip("VCC");
			}break;

			// If we are trying to place a GND
			case sf::Keyboard::Numpad2:
			{
				addChip("GND");
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
				mRenderCanvas->zoomIn();
				mGridComponent->forceRefresh();
				updateDebugInfo();
			}break;

			// Zoom out
			case sf::Keyboard::Subtract:
			{
				mRenderCanvas->zoomOut();
				mGridComponent->forceRefresh();
				updateDebugInfo();
			}break;

			// Move view left (0)
			case sf::Keyboard::Left:
			{
				mRenderCanvas->moveView({ -100.f, 0.f });
				mGridComponent->forceRefresh();
			}break;
			case sf::Keyboard::A:
			{
				mRenderCanvas->moveView({ -100.f, 0.f });
				mGridComponent->forceRefresh();
			}break;

			// Move view right (1)
			case sf::Keyboard::Right:
			{
				mRenderCanvas->moveView({ 100.f, 0.f });
				mGridComponent->forceRefresh();
			}break;
			case sf::Keyboard::D:
			{
				mRenderCanvas->moveView({ 100.f, 0.f });
				mGridComponent->forceRefresh();
			}break;

			// Move view Down (2)
			case sf::Keyboard::Down:
			{
				mRenderCanvas->moveView({ 0.f, 100.f });
				mGridComponent->forceRefresh();
			}break;
			case sf::Keyboard::S:
			{
				mRenderCanvas->moveView({ 0.f, 100.f });
				mGridComponent->forceRefresh();
			}break;

			// Move view up (3)
			case sf::Keyboard::Up:
			{
				mRenderCanvas->moveView({ 0.f, -100.f });
				mGridComponent->forceRefresh();
			}break;
			case sf::Keyboard::W:
			{
				mRenderCanvas->moveView({ 0.f, -100.f });
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

	void TNewGameScene::refresh(sf::Time ElapsedTime)
	{
		mGraphicEntity.refresh(ElapsedTime);
	}

	void TNewGameScene::update(sf::Time ElapsedTime)
	{
		mGuiManager.update(ElapsedTime);

		mGraphicEntity.update(ElapsedTime);
	}

	void TNewGameScene::draw()
	{
		// Clear the render surface
		mRenderWindow->clear({ 0u, 0u, 0u });
		mRenderCanvas->clear({ 1, 47, 83 });
		
		// Draw the entity on the GUI canvas as opposed of the sf::RenderWindow
		for (auto& GraphicsEntity : mGraphicEntity)
			mRenderCanvas->drawEntity(GraphicsEntity->getComponent<TDrawableComponent>());

		// Flip the mRenderCanvas black-buffer
		mRenderCanvas->render();

		// Renders the GUI
		for (auto& Widget : mGuiManager)
			mRenderWindow->draw(*Widget);

		// Display the window
		mRenderWindow->display();
	}

	void TNewGameScene::addWire()
	{
		// Remove temporary Entity
		removeTemporaryEntity();

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
		mLogicBoard->setInsertionMethod(TLogicBoardComponent::TInsertionMethod::WIRE);
	}

	void TNewGameScene::addBus()
	{
		// Remove temporary Entity
		removeTemporaryEntity();

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
		mLogicBoard->setInsertionMethod(TLogicBoardComponent::TInsertionMethod::BUS);
	}

	void TNewGameScene::addChip(const std::string& ChipToAdd)
	{
		// Remove temporary Entity
		removeTemporaryEntity();

		std::function<TEntity::EntityPtr()> FactoryFunction;
		std::string	NewChipID;

		// If we are creating a z80 chip and we didn't do it before
		if (ChipToAdd == "Z80")
		{
			FactoryFunction = TFactory::makeZ80;
			NewChipID = "Z80";
		}
		// If we are creating a RAM chip
		else if (ChipToAdd == "RAM")
		{
			FactoryFunction = TFactory::makeRam;
			NewChipID = "Ram";
		}
		// If we are creating a NAND chip
		else if (ChipToAdd == "NAND")
		{
			FactoryFunction = TFactory::makeNandChip;
			NewChipID = "NAND_" + std::to_string(mChipCounter++);
		}
		// If we are creating a LED
		else if (ChipToAdd == "LED")
		{
			FactoryFunction = TFactory::makeLed;
			NewChipID = "LED_" + std::to_string(mChipCounter++);
		}
		// If we are creating a VCC
		else if (ChipToAdd == "VCC")
		{
			FactoryFunction = std::bind(TFactory::makePowerConnector, TPowerComponent::Type::POWER);
			NewChipID = "VCC_" + std::to_string(mChipCounter++);
		}
		// If we are creating a GND
		else if (ChipToAdd == "GND")
		{
			FactoryFunction = std::bind(TFactory::makePowerConnector, TPowerComponent::Type::GROUND);
			NewChipID = "GND_" + std::to_string(mChipCounter++);
		}

		// Create a new graphic chip
		mGraphicEntity.addEntity(FactoryFunction(), NewChipID, this);

		// Get the newly added CHIP
		auto NewChip = mGraphicEntity.getEntityByKey(NewChipID);
		NewChip->init();
		NewChip->getComponent<TChipComponent>().setPlacedStatus(false);

		// And adds it to the logic board
		mLogicBoard->placeChip(NewChip.get());

		// And set it as the active chip
		mLogicBoard->deselectEverything();
		mLogicBoard->setSelectedChip(NewChip->getComponentAsPtr<TChipComponent>());
		
		// Cache a shared_ptr to the newly added entity
		mTempChip = NewChip;

		// Change the insertion method
		mLogicBoard->setInsertionMethod(TLogicBoardComponent::TInsertionMethod::CHIP);
}

	void TNewGameScene::removeTemporaryEntity()
	{
		// Bus part
		// If we were trying to place another wire but we haven't placed any point or only  before trying to add a new one point
		// Remove that wire from the logic board and delete the entity associated with it
		if (mTempBus && mTempBus->getComponent<TBusComponent>().isDrawing())
		{
			// Make sure we reset the state of the selected bus
			mLogicBoard->deselectBus(true);

			// Remove the chip from the logic board
			mLogicBoard->removeBus(mTempBus.get());

			// Remove the entity
			mGraphicEntity.removeEntity(mTempBus->getEntityID());

			// Reset the state of the temp shared_ptr to make sure we kill all the entity instances
			mTempBus.reset();
		}

		// Wire part
		// If we were trying to place another wire but we haven't placed any point or only  before trying to add a new one point
		// Remove that wire from the logic board and delete the entity associated with it
		if (mTempWire && mTempWire->getComponent<TWireComponent>().isDrawing())
		{
			// Make sure we reset the state of the selected wire
			mLogicBoard->deselectWire(true);

			// Remove the chip from the logic board
			mLogicBoard->removeWire(mTempWire.get());

			// Remove the entity
			mGraphicEntity.removeEntity(mTempWire->getEntityID());

			// Reset the state of the temp shared_ptr to make sure we kill all the entity instances
			mTempWire.reset();
		}
	
		// Chip part
		// If we were trying to place another component before trying to add a new one
		// Remove that component from the logic board and delete the entity associated with it
		if (mTempChip)
		{
			// Make sure we reset the state of the selected chip
			mLogicBoard->deselectChip(true);

			if (!mTempChip->getComponent<TChipComponent>().isPlaced())
			{
				// Remove the chip from the logic board
				mLogicBoard->removeChip(mTempChip.get());

				// Remove the entity
				mGraphicEntity.removeEntity(mTempChip->getEntityID());

				// Reset the state of the temp shared_ptr to make sure we kill all the entity instances
				mTempChip.reset();
			}
		}
	}
	
	void TNewGameScene::updateDebugInfo()
	{
		auto XStaticText = mGuiManager.getWidget<tgui::TStaticText>("XVALUE_TEXT");
		auto YStaticText = mGuiManager.getWidget<tgui::TStaticText>("YVALUE_TEXT"); 
		auto ZStaticText = mGuiManager.getWidget<tgui::TStaticText>("ZINDEX_TEXT");

		auto MousePos = mRenderCanvas->mapCoordsToPixel(getMousePosition());
		MousePos -= {300, 50};
		auto ZoomLevel = static_cast<sf::Uint32>(mRenderCanvas->getZoomFactor() * 100);

		XStaticText->setCaption("X:" + std::to_string(static_cast<sf::Int32>(MousePos.x)));
		YStaticText->setCaption("Y:" + std::to_string(static_cast<sf::Int32>(MousePos.y)));
		ZStaticText->setCaption("Z:" + std::to_string(ZoomLevel) + "%");
	}

}
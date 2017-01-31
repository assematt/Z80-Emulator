#include "TNewGameScene.h"

#include "TEntity.h"
#include "TLogicBoardComponent.h"
#include "TWireComponent.h"
#include "TGridComponent.h"
#include "TNewGameMenu.h"
#include "TStaticText.h"
#include "TZ80Component.h"
#include "TPinComponent.h"
#include "TEventComponent.h"
#include "TDialogWindow.h"
#include "TDebugWindow.h"
#include "TCodeEditor.h"

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

		// Set-up some GUI event for the header
		mGuiManager.getWidget("PCB_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {

			auto& LeftToolsPanel = mGuiManager.getWidget("LEFT_TOOLS_PANEL");

			if (!LeftToolsPanel->isVisible())
			{
				LeftToolsPanel->setVisible(true);
				mGuiManager.getWidget("CODE_PANEL")->setVisible(false);
			}

			mGuiManager.getWidget("PCB_BUTTON")->setSelected(true);
			mGuiManager.getWidget("CODE_BUTTON")->setSelected(false);
		});
		mGuiManager.getWidget("CODE_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {

			auto& CodePanel = mGuiManager.getWidget("CODE_PANEL");

			if (!CodePanel->isVisible())
			{
				CodePanel->setVisible(true);
				mGuiManager.getWidget("LEFT_TOOLS_PANEL")->setVisible(false);
			}

			mGuiManager.getWidget("PCB_BUTTON")->setSelected(false);
			mGuiManager.getWidget("CODE_BUTTON")->setSelected(true);
		});

		// Set-up some GUI event for the left side tools
		mGuiManager.getWidget("INSERT_CHIP_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			auto& ChipList = *mGuiManager.getWidget("CHIP_LIST_PANEL");

			float ChipListHeight = ChipList.getSize().y;

			// If we are displaying the chip list close it
			if (ChipList.isVisible())
			{
				ChipList.setVisible(false);

				mGuiManager.getWidget("INSERT_WIRE_BUTTON")->move(0.f, -ChipListHeight);
				mGuiManager.getWidget("INSERT_BUS_BUTTON")->move(0.f, -ChipListHeight);
			}
			// Otherwise show it
			else
			{
				ChipList.setVisible(true);

				mGuiManager.getWidget("INSERT_WIRE_BUTTON")->move(0.f, ChipListHeight);
				mGuiManager.getWidget("INSERT_BUS_BUTTON")->move(0.f, ChipListHeight);
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
			EventData.mouseButton.button == sf::Mouse::Left ? handleLeftMouseUpEvent(sf::Vector2f(EventData.mouseButton.x - 300.f, EventData.mouseButton.y - 50.f)) : handleRightMouseUpEvent();
		});
		mRenderCanvas->attachEvent(tgui::events::onMouseMove, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			handleMouseMoveEvent(sf::Vector2f(EventData.mouseMove.x - 300.f, EventData.mouseMove.y - 50.f));

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

		auto& InsertionMethod = mLogicBoard.getInsertionMethod();

		switch (InsertionMethod)
		{
			// If we are using the chip tool
			case TBoard::TInsertionMethod::CHIP:
			{
				// get a pointer to the selected wire
				auto CurrentChip = mLogicBoard.getSelectedComponent<TChipComponent>();

				if (CurrentChip && !CurrentChip->isPlaced())
				{
					mTempChip->getComponentAsPtr<TDrawableComponent>()->setPosition(CellPos);

					/// Does the collision check
					mLogicBoard.checkCollisions(CurrentChip);
				}
			}break;

			// If we are using the wire tool
			case TBoard::TInsertionMethod::WIRE:
			{
				// get a pointer to the selected wire
				auto CurrentWire = mLogicBoard.getSelectedComponent<TWireComponent>();

				if (CurrentWire)
					CurrentWire->placePointTemp(CellPos);
			}break;

			// If we are using the bus tool
			case TBoard::TInsertionMethod::BUS:
			{
				// get a pointer to the selected wire
				auto CurrentBus = mLogicBoard.getSelectedComponent<TBusComponent>();

				if (CurrentBus)
					CurrentBus->placePointTemp(CellPos);
			}break;

			// If we are not using any tool
			case TBoard::TInsertionMethod::NONE:
				break;
		}
	}

	void TNewGameScene::handleRightMouseUpEvent()
	{
		if (mLogicBoard.getInsertionMethod() != TBoard::TInsertionMethod::NONE)
			removeTemporaryEntity();
	}

	void TNewGameScene::handleLeftMouseUpEvent(const sf::Vector2f& MousePos)
	{
		// Get the mouse coordinate and transform them to make them stick to the grid		
		auto MousePosAdj = mRenderCanvas->mapPixelToCoords(static_cast<sf::Vector2i>(MousePos));
		auto GridCoord = mGridComponent->mouseCoordsToWindowCellCoords(static_cast<sf::Vector2i>(MousePosAdj));
		auto CellPos = mGridComponent->transformCellCoords(GridCoord);

		auto& InsertionMethod = mLogicBoard.getInsertionMethod();

		switch (InsertionMethod)
		{
			// If we are using the chip tool
			case TBoard::TInsertionMethod::CHIP:
			{
				// get a pointer to the selected wire
				//auto CurrentChip = mLogicBoard->getSelectedChip();
				auto CurrentChip = mLogicBoard.getSelectedComponent<TChipComponent>();

				if (CurrentChip && !CurrentChip->isPlaced() && CurrentChip->isValid())
				{
					CurrentChip->setPlacedStatus(true);
					
					mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::NONE);
					mLogicBoard.deselectEverything();
				}
			}break;

			// If we are using the wire tool
			case TBoard::TInsertionMethod::WIRE:
			{
				// Get the WireComponent of the entity we are inserting
				auto& InsertingWire = mTempWire->getComponent<TWireComponent>();

				InsertingWire.confirmPoints();

				// get a pointer to the selected chip
				auto CurrentSelectedChip = mLogicBoard.getSelectedComponent<TChipComponent>();

				// get a pointer to the former selected chip
				auto FormerSelectedChip = mLogicBoard.getFormerSelectedComponent<TChipComponent>();

				// get a pointer to the selected bus
				auto SelectedBus = mLogicBoard.getSelectedComponent<TBusComponent>();

				// Get a pointer to the selected wire
				auto SelectedWire = mLogicBoard.getSelectedComponent<TWireComponent>();

				// Get a pointer to the selected wire
				auto FormerSelectedWire = mLogicBoard.getFormerSelectedComponent<TWireComponent>();

				// Establish if we are drawing from a bus to chip or vice-versa
				if (CurrentSelectedChip && !SelectedBus)
					mDrawingFromBusToChip = false;
				else if (!CurrentSelectedChip && SelectedBus)
					mDrawingFromBusToChip = true;

				// If we are trying to draw a wire between A wire and something else that we don't know yet
				if (SelectedWire && (SelectedWire != &InsertingWire) && !CurrentSelectedChip && !FormerSelectedChip && !SelectedBus)
				{
					// Place the junction
					InsertingWire.placeJunction(CellPos);

					// Make sure we reset the selected wire at the one we are inserting
					mLogicBoard.setSelectedComponent<TWireComponent>(SelectedWire);
					mLogicBoard.setSelectedComponent<TWireComponent>(&InsertingWire);
				}
				// If we are trying to draw a wire between another wire and a chip
				else if (SelectedWire && (SelectedWire == &InsertingWire) && FormerSelectedWire && CurrentSelectedChip && !FormerSelectedChip)
				{
					// Stop the drawing mode
					InsertingWire.toggleDraw();
										
					for (auto Pin : FormerSelectedWire->getPinList())
					{
						TPinComponentUtility::connectPins(CurrentSelectedChip->getSelectedPin(), *Pin);
						InsertingWire.connectPins(CurrentSelectedChip->getSelectedPin(), *Pin);
					}

					// Reset the chip's pin selected status
					CurrentSelectedChip->deselectPin();

					// Deselect the chip/wire/bus from the logic board
					mLogicBoard.deselectEverything();

					// Start the drawing of a new wire
					addWire();
				}
				// If we have drawn a wire between a chip and another wire
				else if (CurrentSelectedChip && SelectedWire && (SelectedWire != &InsertingWire))
				{
					// Stop the drawing mode
					InsertingWire.toggleDraw();

					InsertingWire.placeJunction(CellPos);

					// Connect the pins
					for (auto Pin : SelectedWire->getPinList())
					{
						TPinComponentUtility::connectPins(CurrentSelectedChip->getSelectedPin(), *Pin);
						InsertingWire.connectPins(CurrentSelectedChip->getSelectedPin(), *Pin);
					}

					// Reset the chip's pin selected status
					CurrentSelectedChip->deselectPin();

					// Deselect the chip/wire/bus from the logic board
					mLogicBoard.deselectEverything();
					
					// Start the drawing of a new wire
					addWire();
				}

				// If we have drawn a wire between 2 chips, exit wire drawing mode, and deselect the currently selected chips and wire
				else if (CurrentSelectedChip && FormerSelectedChip)
				{
					// Stop the drawing mode
					InsertingWire.toggleDraw();

					// Connect the pins
					TPinComponentUtility::connectPins(CurrentSelectedChip->getSelectedPin(), FormerSelectedChip->getSelectedPin());
					InsertingWire.connectPins(CurrentSelectedChip->getSelectedPin(), FormerSelectedChip->getSelectedPin());

					// Reset the chip's pin selected status
					CurrentSelectedChip->deselectPin();
					FormerSelectedChip->deselectPin();

					// Deselect the chip/wire/bus from the logic board
					mLogicBoard.deselectEverything();

					// Start the drawing of a new wire
					addWire();
				}

				// If we have draw a wire between a chip and a bus, exit wire drawing mode, and deselect the currently selected chips and wire
				else if (CurrentSelectedChip && SelectedBus)
				{
					// Stop the drawing mode
					InsertingWire.toggleDraw();

					// Connect the pin to the bus as an entry wire
					if (mDrawingFromBusToChip)
						SelectedBus->connectExitWire(CurrentSelectedChip->getSelectedPin());
					else
						SelectedBus->connectEntryWire(CurrentSelectedChip->getSelectedPin());

					// Reset the chip's pin selected status
					CurrentSelectedChip->deselectPin();

					// Deselect the chip/wire/bus from the logic board
					mLogicBoard.deselectEverything();

					// Start the drawing of a new wire
					addWire();
				}
				
			}break;

			// If we are using the bus tool
			case TBoard::TInsertionMethod::BUS:
			{
				// get a pointer to the selected bus
				auto CurrentBus = mLogicBoard.getSelectedComponent<TBusComponent>();

				// If we have selected a bus
				if (CurrentBus)
					CurrentBus->confirmPoints();
			}break;

			// If we are not using any tool
			case TBoard::TInsertionMethod::NONE:
			{
			}break;
		}
	}

	void TNewGameScene::handleKeyboardInputs(const sf::Keyboard::Key& KeyCode)
	{
		switch (KeyCode)
		{
			// Select the NONE tool
			case sf::Keyboard::R:
			{
				removeTemporaryEntity();

				mLogicBoard.deselectEverything();
				mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::NONE);
			} break;

			// Save the current board
			case sf::Keyboard::Q:
			{
				if (mLogicBoard.saveBoard("resources/boards/test_board.brd"))
					::MessageBoxA(NULL, "The file was successfully saved", "Success!", MB_ICONEXCLAMATION | MB_OK);
				else
					::MessageBoxA(NULL, "The file couldn't be saved", "Error!", MB_ICONERROR | MB_OK);
			} break;
			// Load a board
			case sf::Keyboard::Z:
			{
				if (mLogicBoard.loadBoard("resources/boards/test_board.brd", mLogicBoard, mGraphicEntity, this))
					::MessageBoxA(NULL, "The file was successfully loaded", "Success!", MB_ICONEXCLAMATION | MB_OK);
				else
					::MessageBoxA(NULL, "The file couldn't be loaded", "Error!", MB_ICONERROR | MB_OK);

				mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::NONE);

				// Get the number of loaded entities
				mEntityCounter = mGraphicEntity.getTotalEntities();
			} break;

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
				auto Z80Entity = mGraphicEntity.getEntityByKey("Z80");
				auto RamEntity = mGraphicEntity.getEntityByKey("RAM");

				// Se if both the CPU and the RAM are placed into the logic board
				if (Z80Entity && RamEntity)
				{
					auto& Z80 = Z80Entity->getComponent<tcomponents::TZ80Component>();
					Z80.connectRam(RamEntity);
					if (!Z80.loadProgram("resources/programs/SUB.A01"))
					{
						std::cout << "Error! Could not open the file" << std::endl;
					}
					else
					{
						auto& CodeEditor = mGuiManager.getWidget<tgui::TCodeEditor>("CODE_EDITOR");

						CodeEditor->attachZ80(Z80);

						//CodeEditor->attachSourceCode(Z80.getProgram());
						//CodeEditor->attachProgramCounter(Z80.getRegisterCointainer().programCounter());
					}
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

		// Update the debugger value
		auto Z80Entity = mGraphicEntity.getEntityByKey("Z80");

		if (Z80Entity)
		{
			auto& Z80 = Z80Entity->getComponent<tcomponents::TZ80Component>();

			mGuiManager.getWidget<tgui::TDebugWindow>("REGISTER_DEBUGGER")->setDebugText(formatZ80Registers(Z80));

			mGuiManager.getWidget<tgui::TDebugWindow>("FLAGS_DEBUGGER")->setDebugText(formatZ80Flags(Z80));
		}
		
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

		++mEntityCounter;

		// Create a wire entity and add it to the manger
		mGraphicEntity.addEntity(TFactory::makeWire(), "Wire_" + std::to_string(mEntityCounter), this);

		// Retrieve the newly added entity
		mTempWire = mGraphicEntity.getEntityByKey("Wire_" + std::to_string(mEntityCounter));

		// Init the newly added wire
		mTempWire->init();

		// Set the used board
		mTempWire->getComponent<TLogicBoardComponent>().setBoard(mLogicBoard);

		mTempWire->getComponent<TEventComponent>().attachEvent(tcomponents::events::onMouseUp, [&](const TEntity* Sender, const sf::Event& EventData){

			if (mLogicBoard.getInsertionMethod() == TBoard::TInsertionMethod::NONE)
			{
				// Get the wire ID
				auto WireID = Sender->getComponent<TWireComponent>().getComponentID();

				// Get the wire connections
				auto WireConnections = Sender->getComponent<TWireComponent>().getPinList();

				// Dialog title
				std::string DialogTitle = "Wire ID: " + std::to_string(WireID);

				// Dialog message
				std::string DialogMessage = WireConnections.empty() ? "Connections not set" : "";
				for (auto& Pin : WireConnections)
					DialogMessage += "Connection PIN id: " + std::to_string(Pin->getPinID()) + "\n";

				::MessageBoxA(NULL, DialogMessage.c_str(), DialogTitle.c_str(), MB_OK);
			}

		});

		// And adds it to the logic board
		mLogicBoard.placeComponent<TWireComponent>(mTempWire);

		// And set it as the active wire
		mLogicBoard.deselectEverything();
		mLogicBoard.setSelectedComponent<TWireComponent>(mTempWire);

		// Allow to draw the wire
		mLogicBoard.getSelectedComponent<TWireComponent>()->toggleDraw();

		// Change the insertion method
		mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::WIRE);

	}

	void TNewGameScene::addBus()
	{
		// Remove temporary Entity
		removeTemporaryEntity();

		++mEntityCounter;

		// Create a conductive bus entity and add it to the manger
		mGraphicEntity.addEntity(TFactory::makeBus(), "Bus_" + std::to_string(mEntityCounter), this);

		// Retrieve the newly added entity
		mTempBus = mGraphicEntity.getEntityByKey("Bus_" + std::to_string(mEntityCounter));

		// Init the newly added bus
		mTempBus->init();

		// Set the used board
		mTempBus->getComponent<TLogicBoardComponent>().setBoard(mLogicBoard);

		// And adds it to the logic board
		mLogicBoard.placeComponent<TBusComponent>(mTempBus);

		// And set it as the active bus
		mLogicBoard.deselectEverything();
		mLogicBoard.setSelectedComponent<TBusComponent>(mTempBus);

		// Allow to draw the bus
		mLogicBoard.getSelectedComponent<TBusComponent>()->toggleDraw();

		// Change the insertion method
		mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::BUS);
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
			NewChipID = "RAM";
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
		mTempChip = mGraphicEntity.getEntityByKey(NewChipID);
		mTempChip->init();
		mTempChip->getComponent<TChipComponent>().setPlacedStatus(false);
		mTempChip->getComponent<TChipComponent>().setChipName(NewChipID);
		
		// Set the used board
		mTempChip->getComponent<TLogicBoardComponent>().setBoard(mLogicBoard);

		// And adds it to the logic board
		mLogicBoard.placeComponent<TChipComponent>(mTempChip);

		// And set it as the active chip
		mLogicBoard.deselectEverything();
		mLogicBoard.setSelectedComponent<TChipComponent>(mTempChip);

		// Change the insertion method
		mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::CHIP);
}

	void TNewGameScene::removeTemporaryEntity()
	{
		// Bus part
		// If we were trying to place another wire but we haven't placed any point or only  before trying to add a new one point
		// Remove that wire from the logic board and delete the entity associated with it
		if (mTempBus && mTempBus->getComponent<TBusComponent>().isDrawing())
		{
			// Make sure we reset the state of the selected bus
			mLogicBoard.deselectComponent<TBusComponent>(true);

			// Remove the chip from the logic board
			mLogicBoard.removeComponent<TBusComponent>(mTempBus);

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
			mLogicBoard.deselectComponent<TWireComponent>(true);

			// Remove the chip from the logic board
			mLogicBoard.removeComponent<TWireComponent>(mTempWire);

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
			mLogicBoard.deselectComponent<TChipComponent>(true);

			if (!mTempChip->getComponent<TChipComponent>().isPlaced())
			{
				// Remove the chip from the logic board
				mLogicBoard.removeComponent<TChipComponent>(mTempChip);

				// Remove the entity
				mGraphicEntity.removeEntity(mTempChip->getEntityID());

				// Reset the state of the temp shared_ptr to make sure we kill all the entity instances
				mTempChip.reset();
			}
		}
	}
	
	std::string TNewGameScene::formatZ80Registers(const TZ80Component& Z80)
	{
		auto& Registers = Z80.getRegisterCointainer();

		// Normal 16 bit registers
		auto AF = Registers.getRegister<T16BitRegister>(TRegisterType::AF).getInternalValue();
		auto BC = Registers.getRegister<T16BitRegister>(TRegisterType::BC).getInternalValue();
		auto DE = Registers.getRegister<T16BitRegister>(TRegisterType::DE).getInternalValue();
		auto HL = Registers.getRegister<T16BitRegister>(TRegisterType::HL).getInternalValue();

		// Alternate 16 bit registers
		auto AFAlt = Registers.getRegister<T16BitRegister>(TRegisterType::ALTAF).getInternalValue();
		auto BCAlt = Registers.getRegister<T16BitRegister>(TRegisterType::ALTBC).getInternalValue();
		auto DEAlt = Registers.getRegister<T16BitRegister>(TRegisterType::ALTDE).getInternalValue();
		auto HLAlt = Registers.getRegister<T16BitRegister>(TRegisterType::ALTHL).getInternalValue();

		// PC and SP register
		auto SP = Registers.getRegister<T16BitRegister>(TRegisterType::SP).getInternalValue();
		auto PC = Registers.getRegister<T16BitRegister>(TRegisterType::PC).getInternalValue();

		// Index register
		auto IX = Registers.getRegister<T16BitRegister>(TRegisterType::IX).getInternalValue();
		auto IY = Registers.getRegister<T16BitRegister>(TRegisterType::IY).getInternalValue();

		// I and R register
		auto I = Registers.getRegister<T8BitRegister>(TRegisterType::I).getInternalValue();
		auto R = Registers.getRegister<T8BitRegister>(TRegisterType::R).getInternalValue();

		// Normal 8 bit registers
		auto A = Registers.getRegister<T8BitRegister>(TRegisterType::A).getInternalValue();
		auto B = Registers.getRegister<T8BitRegister>(TRegisterType::B).getInternalValue();
		auto C = Registers.getRegister<T8BitRegister>(TRegisterType::C).getInternalValue();
		auto D = Registers.getRegister<T8BitRegister>(TRegisterType::D).getInternalValue();
		auto E = Registers.getRegister<T8BitRegister>(TRegisterType::E).getInternalValue();
		auto F = Registers.getRegister<T8BitRegister>(TRegisterType::F).getInternalValue();
		auto H = Registers.getRegister<T8BitRegister>(TRegisterType::H).getInternalValue();
		auto L = Registers.getRegister<T8BitRegister>(TRegisterType::L).getInternalValue();

		char FormattedCode[250];

		sprintf_s(FormattedCode, "AF:%04XH  AF':%04XH\nBC:%04XH  BC':%04XH\nDE:%04XH  DE':%04XH\nHL:%04XH  HL':%04XH\nIX:%04XH   IY:%04XH\n I:%02XH      R:%02XH\nSP:%04XH   PC:%04XH\n\nA:%02XH  B:%02XH  C:%02XH \nD:%02XH  E:%02XH  F:%02XH \nH:%02XH  L:%02XH",
			AF, AFAlt, BC, BCAlt, DE, DEAlt, HL, HLAlt,
			IX, IY,
			I, R,
			SP, PC,
			A, B, C, D, E, F, H, L);

		return std::string(FormattedCode);
	}

	std::string TNewGameScene::formatZ80Flags(const TZ80Component& Z80)
	{
		// Flag register
		auto F = Z80.getRegisterCointainer().flags();

		/*
		C = 0,	  // 0b00000001
		N = 1,	  // 0b00000010
		P_V = 2, // 0b00000100
		H = 4,	 // 0b00010000
		Z = 6,	  // 0b01000000
		S = 7,	  // 0b10000000
		*/

		char FormattedCode[100];

		sprintf_s(FormattedCode, "CARRY [%u]  ZERO  [%u]\nSIGN  [%u]  P/O   [%u]\nHALFC [%u]  SUBS  [%u]",
			TUtility::getBit(F, 0), TUtility::getBit(F, 6), TUtility::getBit(F, 7), TUtility::getBit(F, 2), TUtility::getBit(F, 4), TUtility::getBit(F, 1));

		return std::string(FormattedCode);
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
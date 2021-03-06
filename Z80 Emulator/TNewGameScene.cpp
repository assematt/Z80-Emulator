#include "TNewGameScene.h"

#include <functional>

#include INCLUDE_ENTITY_CLASS
#include "TCodeEditor.h"
#include "TStaticText.h"
#include "TNewGameMenu.h"
#include "TDebugWindow.h"
#include "TZ80Component.h"
#include "TPinComponent.h"
#include "TDialogWindow.h"
#include "TWireComponent.h"
#include "TGridComponent.h"
#include "TEventComponent.h"
#include "TPackageComponent.h"
#include "TLogicBoardComponent.h"

#include <ECS/_TManager.h>

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

#if ENTITY_SYSTEM == USE_ECS
		// Add all the component systems
		TFactory::fillManagerWithSystems(mGraphicEntity);
#endif

		// Create some graphic entity
#if ENTITY_SYSTEM == NNE
		mGraphicEntity.addEntity(TFactory::makeLogicBoard(), "LogicBoard", this);
#else
		mGraphicEntity.addEntity(TFactory::makeLogicBoard(mGraphicEntity, ecs::utility::getStringID<ecs::_TEntity::ID>("LogicBoard")));
#endif
		mGraphicEntity.initEntities();

		// Init the GUI
		tgui::TNewGameMenu::Ptr NewGameMenu = std::make_shared<tgui::TNewGameMenu>("NEW_GAME_MENU");		
		NewGameMenu->setSize(WindowSize);
		NewGameMenu->init(&mGuiManager);
		mGuiManager.addWidget(NewGameMenu);

		// Cache the render-canvas and attach the render surface to it
		mRenderCanvas = mGuiManager.getWidget<tgui::TRenderCanvas>("RENDER_CANVAS").get();

		// Get the grid component and set some property
#if ENTITY_SYSTEM == NNE
		mGridComponent = mGraphicEntity.getEntityByKey("LogicBoard")->getComponentAsPtr<TGridComponent>();
#else
		mGridComponent = &(*mGraphicEntity.getEntity("LogicBoard")->getComponent<TGridComponent>());
#endif
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
				mGuiManager.getWidget("DELETE_BUTTON")->move(0.f, -ChipListHeight);
			}
			// Otherwise show it
			else
			{
				ChipList.setVisible(true);

				mGuiManager.getWidget("INSERT_WIRE_BUTTON")->move(0.f, ChipListHeight);
				mGuiManager.getWidget("INSERT_BUS_BUTTON")->move(0.f, ChipListHeight);
				mGuiManager.getWidget("DELETE_BUTTON")->move(0.f, ChipListHeight);
			}
		});
		mGuiManager.getWidget("INSERT_WIRE_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addWire();
		});
		mGuiManager.getWidget("INSERT_BUS_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addBus();
		});
		mGuiManager.getWidget("DELETE_BUTTON")->attachEvent(tgui::events::onClick, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			// Remove temporary Entity
			removeTemporaryEntity();

			// Change the insertion method
			mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::REMOVE);
		});
		
		// Set-up some GUI event for the button that create components
		mGuiManager.getWidget("INSERT_CPU_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {

			// Look for a z80 entity in the entities vector
#if ENTITY_SYSTEM == NNE
			auto Z80Temp = mGraphicEntity.getEntityByKey("Z80");
#else
			auto Z80Temp = mGraphicEntity.getEntity("Z80");
#endif

			// If we don't find it add it to the entity vector
			if (!Z80Temp)
			{
				addChip("Z80");
			}
			// Otherwise if it already exit and we already have placed one display and error message
#if ENTITY_SYSTEM == NNE
			else if (Z80Temp->getComponent<TChipComponent>().isPlaced())
#else
			else if (Z80Temp->getComponent<TChipComponent>()->isPlaced())
#endif
			{
				tgui::TDialogWindow::Ptr TempWindow = std::make_shared<tgui::TDialogWindow>(mGuiManager);
				TempWindow->setName("TEMP_DIALOG_WINDOW");
				TempWindow->setTitleString("Error!");
				TempWindow->setMessageString("You can only place down one z80 CPU!");
				mGuiManager.addWidget(TempWindow, 10);
				mGuiManager.getWidget<tgui::TDialogWindow>("TEMP_DIALOG_WINDOW")->show(*mRenderWindow, tgui::TReferencePoint::CENTER);
			}

		});
		mGuiManager.getWidget("INSERT_RAM_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			// Look for a z80 entity in the entities vector
#if ENTITY_SYSTEM == NNE
			auto RamTemp = mGraphicEntity.getEntityByKey("RAM");
#else
			auto RamTemp = mGraphicEntity.getEntity("RAM");
#endif

			// If we don't find it add it to the entity vector
			if (!RamTemp)
			{
				addChip("RAM");
			}
			// Otherwise if it already exit and we already have placed one display and error message
#if ENTITY_SYSTEM == NNE
			else if (RamTemp->getComponent<TChipComponent>().isPlaced())
#else
			else if (RamTemp->getComponent<TChipComponent>()->isPlaced())
#endif
			{
				tgui::TDialogWindow::Ptr TempWindow = std::make_shared<tgui::TDialogWindow>(mGuiManager);
				TempWindow->setName("TEMP_DIALOG_WINDOW");
				TempWindow->setTitleString("Error!");
				TempWindow->setMessageString("You can only place down one RAM!");
				mGuiManager.addWidget(TempWindow, 10);
				mGuiManager.getWidget<tgui::TDialogWindow>("TEMP_DIALOG_WINDOW")->show(*mRenderWindow, tgui::TReferencePoint::CENTER);
			}
		});
		mGuiManager.getWidget("INSERT_NAND_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addChip("NAND");
		});
		mGuiManager.getWidget("INSERT_LED_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addChip("LED");
		});
		mGuiManager.getWidget("INSERT_POWER_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
			addChip("VCC");
		});
		mGuiManager.getWidget("INSERT_GROUND_BUTTON")->attachEvent(tgui::events::onMouseUp, [&](const tgui::TWidget* Sender, const sf::Event& EventData) {
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
#if ENTITY_SYSTEM == NNE
			mGraphicEntity.processEvents(mAppEvent, *mRenderWindow, *mRenderCanvas);
#endif

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
		auto CellPos = mGridComponent->convertCoordinate(*mRenderCanvas, MousePos);

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
#if ENTITY_SYSTEM == NNE
					mTempChip->getComponentAsPtr<TDrawableComponent>()->setPosition(CellPos);
#else
					mTempChip->getComponent<TDrawableComponent>()->setPosition(CellPos);
#endif
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
				{
					auto& ChipVector = mLogicBoard.getComponentVector<TChipComponent>();
					sf::FloatRect PinBound = {};
					auto Hovering = false;

					for (auto Chip : ChipVector)
					{
#if ENTITY_SYSTEM == NNE
						auto& PinComponent = Chip->getParent()->getComponent<TPinComponent>();
#else
						auto& PinComponent = (*Chip->getParent().getComponent<TPinComponent>());
#endif
						auto PinNumber = PinComponent.getPinList().size();
						for (auto Index = 0u; Index < PinNumber && !Hovering; ++Index)
						{
							PinBound = PinComponent.getPinGlobalBounds(Index);
							if (PinBound.contains(MousePosAdj))
								Hovering = true;
						}
					}

					// If we are hovering over a pin out the initial point at the center of the hovered pin
					if (Hovering)
					{
						// Compute the where to position the first wire point in an horizontally oriented PIN
						sf::Vector2f WireTempPos = { PinBound.left + PinBound.width / 2.f, PinBound.top + PinBound.height / 2.f };

						// Adjust his coordinate if it's placed vertically
						if (PinBound.width < PinBound.height)
							WireTempPos -= { 1.f, 1.f };

						CurrentWire->placePointTemp(WireTempPos);
					}
					else
					{
						CurrentWire->placePointTemp(CellPos);
					}
				}
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
		auto CellPos = mGridComponent->convertCoordinate(*mRenderCanvas, MousePos);

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
#if ENTITY_SYSTEM == NNE
				auto InsertingWire = mTempWire->getComponentAsPtr<TWireComponent>();
#else
				auto& InsertingWire = mTempWire->getComponent<TWireComponent>();
#endif
				
				// Confirm the point added so far in the wire sf::VertexArray as definitive
				InsertingWire->confirmPoints();

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
#if ENTITY_SYSTEM == NNE
				if (SelectedWire && (SelectedWire != InsertingWire) && !CurrentSelectedChip && !FormerSelectedChip && !SelectedBus)
#else
				if (SelectedWire && (SelectedWire != &(*InsertingWire)) && !CurrentSelectedChip && !FormerSelectedChip && !SelectedBus)
#endif
				{
					// Place the junction
					InsertingWire->placeJunction(CellPos, SelectedWire);

					// Make sure we reset the selected wire at the one we are inserting
					mLogicBoard.setSelectedComponent<TWireComponent>(SelectedWire);
					
#if ENTITY_SYSTEM == NNE
					mLogicBoard.setSelectedComponent<TWireComponent>(InsertingWire);
#else
					mLogicBoard.setSelectedComponent<TWireComponent>(&(*InsertingWire));
#endif
				}
				
				// If we are trying to draw a wire between another wire and a chip
#if ENTITY_SYSTEM == NNE
				else if (SelectedWire && (SelectedWire == InsertingWire) && FormerSelectedWire && CurrentSelectedChip && !FormerSelectedChip)
#else
				else if (SelectedWire && (SelectedWire == &(*InsertingWire)) && FormerSelectedWire && CurrentSelectedChip && !FormerSelectedChip)
#endif
				{
					// Stop the drawing mode
					InsertingWire->toggleDraw();

					// Add the PIN connection from the chip and wire (and perform the eventual connectPins(...) function between this pin
					// And other pins connected to the wire)
					InsertingWire->connectPin(CurrentSelectedChip->getSelectedPin());

					// Connect the wire (and perform the eventual connectPins(...) function between this pin
					// And other pins connected to the wire)
					InsertingWire->connectWire(FormerSelectedWire);
										
					// Reset the chip's pin selected status
					CurrentSelectedChip->deselectPin();

					// Deselect the chip/wire/bus from the logic board
					mLogicBoard.deselectEverything();

					// Start the drawing of a new wire
					addWire();
				}

				// If we have drawn a wire between a chip and another wire
#if ENTITY_SYSTEM == NNE
				else if (CurrentSelectedChip && SelectedWire && (SelectedWire != InsertingWire))
#else
				else if (CurrentSelectedChip && SelectedWire && (SelectedWire != &(*InsertingWire)))
#endif
				{
					// Stop the drawing mode
					InsertingWire->toggleDraw();

					// Add a junction
					InsertingWire->placeJunction(CellPos, SelectedWire);
										
					// Add the PIN connection from the chip and wire (and perform the eventual connectPins(...) function between this pin
					// And other pins connected to the wire)
					InsertingWire->connectPin(CurrentSelectedChip->getSelectedPin());

					// Connect the wire (and perform the eventual connectPins(...) function between this pin
					// And other pins connected to the wire)
					InsertingWire->connectWire(SelectedWire);

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
					InsertingWire->toggleDraw();
					
					// Add the 2 pin from the chip to the wire (who will perform the connectPins(...) function between the 2 pin)
					InsertingWire->connectPins(CurrentSelectedChip->getSelectedPin(), FormerSelectedChip->getSelectedPin());

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
					InsertingWire->toggleDraw();

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

			// If we are using the delete tool
			case TBoard::TInsertionMethod::REMOVE:
			{
				auto LastSelectedComponent = mLogicBoard.getLastSelectedItem(MousePos);

				if (LastSelectedComponent.second == "CHIP" && LastSelectedComponent.first)
				{
					removeChip(dynamic_cast<TChipComponent*>(LastSelectedComponent.first));
				}
				else if (LastSelectedComponent.second == "WIRE" && LastSelectedComponent.first)
				{
					removeWire(dynamic_cast<TWireComponent*>(LastSelectedComponent.first));
				}
				else if (LastSelectedComponent.second == "BUS" && LastSelectedComponent.first)
				{
					removeBus(dynamic_cast<TBusComponent*>(LastSelectedComponent.first));
				}
			} break;

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
				// Display an error message if something goes wrong
				if (!mLogicBoard.loadBoard("resources/boards/test_board.brd", mLogicBoard, mGraphicEntity, this))
				{
					::MessageBoxA(NULL, "The file couldn't be loaded", "Error!", MB_ICONERROR | MB_OK);
					return;
				}

				// Display a success message if everything goes well
				::MessageBoxA(NULL, "The file was successfully loaded", "Success!", MB_ICONEXCLAMATION | MB_OK);

				// Set the new insertion method
				mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::NONE);

				// Get the Z80 and the ram entity
#if ENTITY_SYSTEM == NNE
				auto Z80Entity = mGraphicEntity.getEntityByKey("Z80");
				auto RamEntity = mGraphicEntity.getEntityByKey("RAM");
#else
				auto& Z80Entity = mGraphicEntity.getEntity("Z80");
				auto& RamEntity = mGraphicEntity.getEntity("RAM");
#endif

				// Se if both the CPU and the RAM are placed into the logic board
				if (Z80Entity && RamEntity)
				{
#if ENTITY_SYSTEM == NNE
					auto Z80 = Z80Entity->getComponentAsPtr<tcomponents::TZ80Component>();

					Z80->connectRam(RamEntity);
					if (!Z80->loadProgram("resources/programs/SUB.A01"))
					{
						std::cout << "Error! Could not open the file" << std::endl;
					}
					else
					{
						auto& CodeEditor = mGuiManager.getWidget<tgui::TCodeEditor>("CODE_EDITOR");

						CodeEditor->attachZ80(*Z80);
					}
#else
					auto& Z80 = Z80Entity->getComponent<tcomponents::TZ80Component>();

					Z80->connectRam(RamEntity);
					if (!Z80->loadProgram("resources/programs/SUB.A01"))
					{
						std::cout << "Error! Could not open the file" << std::endl;
					}
					else
					{
						auto& CodeEditor = mGuiManager.getWidget<tgui::TCodeEditor>("CODE_EDITOR");

						CodeEditor->attachZ80(*Z80);
					}
#endif
				}

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
#if ENTITY_SYSTEM == NNE
				auto Z80Entity = mGraphicEntity.getEntityByKey("Z80");
				auto RamEntity = mGraphicEntity.getEntityByKey("RAM");
#else
				auto& Z80Entity = mGraphicEntity.getEntity("Z80");
				auto& RamEntity = mGraphicEntity.getEntity("RAM");
#endif

				// Se if both the CPU and the RAM are placed into the logic board
				if (Z80Entity && RamEntity)
				{
#if ENTITY_SYSTEM == NNE
					auto Z80 = Z80Entity->getComponentAsPtr<tcomponents::TZ80Component>();
					Z80->connectRam(RamEntity);
					if (!Z80->loadProgram("resources/programs/SUB.A01"))
					{
						std::cout << "Error! Could not open the file" << std::endl;
					}
					else
					{
						auto& CodeEditor = mGuiManager.getWidget<tgui::TCodeEditor>("CODE_EDITOR");
						CodeEditor->attachZ80(*Z80);
					}
#else
					auto& Z80 = Z80Entity->getComponent<tcomponents::TZ80Component>();
					Z80->connectRam(RamEntity);
					if (!Z80->loadProgram("resources/programs/SUB.A01"))
					{
						std::cout << "Error! Could not open the file" << std::endl;
					}
					else
					{
						auto& CodeEditor = mGuiManager.getWidget<tgui::TCodeEditor>("CODE_EDITOR");
						CodeEditor->attachZ80(*Z80);
					}
#endif
				}
			}break;
						
			// Reset the CPU
			case sf::Keyboard::M:
			{
#if ENTITY_SYSTEM == NNE
				auto Z80 = mGraphicEntity.getEntityByKey("Z80");

				if (Z80)
					Z80->getComponentAsPtr<tcomponents::TZ80Component>()->reset();
#else
				auto Z80 = mGraphicEntity.getEntity("Z80");

				if (Z80)
					Z80->getComponent<tcomponents::TZ80Component>()->reset();
#endif
			}break;

			// Pause CPU execution
			case sf::Keyboard::K:
			{
#if ENTITY_SYSTEM == NNE
				auto Z80 = mGraphicEntity.getEntityByKey("Z80");

				if (Z80)
					Z80->getComponentAsPtr<tcomponents::TZ80Component>()->pauseExecution();
#else
				auto Z80 = mGraphicEntity.getEntity("Z80");

				if (Z80)
					Z80->getComponent<tcomponents::TZ80Component>()->pauseExecution();
#endif
			}break;

			// Resume CPU execution
			case sf::Keyboard::J:
			{
#if ENTITY_SYSTEM == NNE
				auto Z80 = mGraphicEntity.getEntityByKey("Z80");

				if (Z80)
					Z80->getComponentAsPtr<tcomponents::TZ80Component>()->resumeExecution();
#else
				auto Z80 = mGraphicEntity.getEntity("Z80");

				if (Z80)
					Z80->getComponent<tcomponents::TZ80Component>()->resumeExecution();
#endif
			}break;

			// Restart CPU execution
			case sf::Keyboard::L:
			{
#if ENTITY_SYSTEM == NNE
				auto Z80 = mGraphicEntity.getEntityByKey("Z80");

				if (Z80)
					Z80->getComponentAsPtr<tcomponents::TZ80Component>()->restartExecution();
#else
				auto Z80 = mGraphicEntity.getEntity("Z80");

				if (Z80)
					Z80->getComponent<tcomponents::TZ80Component>()->restartExecution();
#endif
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

	void TNewGameScene::refresh(const sf::Time& ElapsedTime)
	{
#if ENTITY_SYSTEM == NNE
		mGraphicEntity.refresh(ElapsedTime);
#else
		mGraphicEntity.refresh(ElapsedTime.asSeconds());
#endif
	}

	void TNewGameScene::update(const sf::Time& ElapsedTime)
	{
		mGuiManager.update(ElapsedTime);

#if ENTITY_SYSTEM == NNE
		mGraphicEntity.update(ElapsedTime);
#else
		mGraphicEntity.update(ElapsedTime.asSeconds());
#endif

		// Update the debugger value
#if ENTITY_SYSTEM == NNE
		auto Z80Entity = mGraphicEntity.getEntityByKey("Z80");
#else
		auto Z80Entity = mGraphicEntity.getEntity("Z80");
#endif

		if (Z80Entity)
		{
#if ENTITY_SYSTEM == NNE
			auto& Z80 = Z80Entity->getComponent<tcomponents::TZ80Component>();

			mGuiManager.getWidget<tgui::TDebugWindow>("REGISTER_DEBUGGER")->setDebugText(formatZ80Registers(Z80));

			mGuiManager.getWidget<tgui::TDebugWindow>("FLAGS_DEBUGGER")->setDebugText(formatZ80Flags(Z80));
#else
			auto& Z80 = Z80Entity->getComponent<tcomponents::TZ80Component>();

			mGuiManager.getWidget<tgui::TDebugWindow>("REGISTER_DEBUGGER")->setDebugText(formatZ80Registers(*Z80));

			mGuiManager.getWidget<tgui::TDebugWindow>("FLAGS_DEBUGGER")->setDebugText(formatZ80Flags(*Z80));
#endif
		}
		
	}

	void TNewGameScene::draw()
	{
		// Clear the render surface
		mRenderWindow->clear({ 0u, 0u, 0u });
		mRenderCanvas->clear({ 1, 47, 83 });
		
		// Draw the entity on the GUI canvas as opposed of the sf::RenderWindow
#if ENTITY_SYSTEM == NNE
		for (auto& GraphicsEntity : mGraphicEntity)
			mRenderCanvas->drawEntity(GraphicsEntity->getComponent<TDrawableComponent>());
#else
		auto& GraphicSystem = mGraphicEntity.getSystem<TDrawableComponent>();
		for (auto& GraphicsComponent : GraphicSystem)
			mRenderCanvas->drawEntity(GraphicsComponent);
#endif

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

		// Increment the entity counter
		++mEntityCounter;

		// Wire name
		std::string WireName = "Wire_" + std::to_string(mEntityCounter);

		// Create a wire entity and add it to the manger
#if ENTITY_SYSTEM == NNE
		mGraphicEntity.addEntity(TFactory::makeWire(), WireName, this);

		// Retrieve the newly added entity
		mTempWire = mGraphicEntity.getEntityByKey(WireName);
#else
		mTempWire = mGraphicEntity.addEntity(WireName);
#endif		

		// Init the newly added wire
		mTempWire->init();

		// Set the used board
#if ENTITY_SYSTEM == NNE
		mTempWire->getComponent<TLogicBoardComponent>().setBoard(mLogicBoard);
#else
		mTempWire->getComponent<TLogicBoardComponent>()->setBoard(mLogicBoard);
#endif

#if ENTITY_SYSTEM == NNE
		mTempWire->getComponent<TEventComponent>().attachEvent(tcomponents::events::onMouseUp, [&](const TEntity* Sender, const sf::Event& EventData) {
#else
		mTempWire->getComponent<TEventComponent>()->attachEvent(tcomponents::events::onMouseUp, [&](const ecs::_TEntity* Sender, const sf::Event& EventData) {
#endif
			if (mLogicBoard.getInsertionMethod() == TBoard::TInsertionMethod::NONE)
			{
#if ENTITY_SYSTEM == NNE
				// Get the wire ID
				auto WireID = Sender->getComponent<TWireComponent>().getComponentID();

				// Get the wire connections
				auto WireConnections = Sender->getComponent<TWireComponent>().getConnectedPins();
#else
				// Get the wire ID
				auto& WireComponent = Sender->getComponent<TWireComponent>();
				auto& WireID = WireComponent->getID();

				// Get the wire connections
				auto WireConnections = WireComponent->getConnectedPins();
#endif

				// Dialog title
				std::string DialogTitle = "Wire ID: " + std::to_string(WireID);

				// Dialog message
				std::string DialogMessage = WireConnections.empty() ? "Connections not set" : "";
				for (auto& Pin : WireConnections)
					DialogMessage += "Connection PIN ID: " + std::to_string(Pin->getPinID()) + "\n";

				::MessageBoxA(NULL, DialogMessage.c_str(), DialogTitle.c_str(), MB_OK);
			}

		});

		// And adds it to the logic board
		mLogicBoard.placeComponent<TWireComponent>(mTempWire);

		// And set it as the active wire
		mLogicBoard.deselectEverything();
		mLogicBoard.setSelectedComponent<TWireComponent>(mTempWire);

		// Set wire name
#if ENTITY_SYSTEM == NNE
		mTempWire->getComponent<TWireComponent>().setWireName(WireName);
#else
		mTempWire->getComponent<TWireComponent>()->setWireName(WireName);
#endif

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
#if ENTITY_SYSTEM == NNE
		mGraphicEntity.addEntity(TFactory::makeBus(), "Bus_" + std::to_string(mEntityCounter), this);

		// Retrieve the newly added entity
		mTempBus = mGraphicEntity.getEntityByKey("Bus_" + std::to_string(mEntityCounter));
#else
		mTempBus = mGraphicEntity.addEntity("Bus_" + std::to_string(mEntityCounter));
#endif

		// Init the newly added bus
		mTempBus->init();

		// Set the used board
#if ENTITY_SYSTEM == NNE
		mTempBus->getComponent<TLogicBoardComponent>().setBoard(mLogicBoard);
#else
		mTempBus->getComponent<TLogicBoardComponent>()->setBoard(mLogicBoard);
#endif

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

#if ENTITY_SYSTEM == NNE
		std::function<ENTITY_PTR()> FactoryFunction;
#endif
		std::string	NewChipID;
		ENTITY_PTR	EntityToAdd;
		TPackageComponent::TPackageType PackageType = TPackageComponent::TPackageType::DIP;

		// If we are creating a z80 chip and we didn't do it before
		if (ChipToAdd == "Z80")
		{
			NewChipID = "Z80";
#if ENTITY_SYSTEM == NNE
			FactoryFunction = TFactory::makeZ80;
#else
			EntityToAdd = TFactory::makeZ80(mGraphicEntity, ecs::utility::getStringID<ecs::_TEntity::ID>(NewChipID));
#endif
		}
		// If we are creating a RAM chip
		else if (ChipToAdd == "RAM")
		{
			NewChipID = "RAM";
#if ENTITY_SYSTEM == NNE
			FactoryFunction = TFactory::makeRam;
#else
			EntityToAdd = TFactory::makeRam(mGraphicEntity, ecs::utility::getStringID<ecs::_TEntity::ID>(NewChipID));
#endif
		}
		// If we are creating a NAND chip
		else if (ChipToAdd == "NAND")
		{
			NewChipID = "NAND_" + std::to_string(mChipCounter++);
#if ENTITY_SYSTEM == NNE
			FactoryFunction = TFactory::makeNandChip;
#else
			EntityToAdd = TFactory::makeNandChip(mGraphicEntity, ecs::utility::getStringID<ecs::_TEntity::ID>(NewChipID));
#endif
		}
		// If we are creating a LED
		else if (ChipToAdd == "LED")
		{
			NewChipID = "LED_" + std::to_string(mChipCounter++);
#if ENTITY_SYSTEM == NNE
			FactoryFunction = TFactory::makeLed;
#else
			EntityToAdd = TFactory::makeLed(mGraphicEntity, ecs::utility::getStringID<ecs::_TEntity::ID>(NewChipID));
#endif
			PackageType = TPackageComponent::TPackageType::LED;
		}
		// If we are creating a VCC
		else if (ChipToAdd == "VCC")
		{
			NewChipID = "VCC_" + std::to_string(mChipCounter++);
#if ENTITY_SYSTEM == NNE
			FactoryFunction = std::bind(TFactory::makePowerConnector, TPowerComponent::Type::POWER);
#else
			EntityToAdd = TFactory::makePowerConnector(mGraphicEntity, ecs::utility::getStringID<ecs::_TEntity::ID>(NewChipID), TPowerComponent::Type::POWER);
#endif
			PackageType = TPackageComponent::TPackageType::POWER_CONNECTOR;
		}
		// If we are creating a GND
		else if (ChipToAdd == "GND")
		{
			NewChipID = "GND_" + std::to_string(mChipCounter++);
#if ENTITY_SYSTEM == NNE
			FactoryFunction = std::bind(TFactory::makePowerConnector, TPowerComponent::Type::GROUND);
#else
			EntityToAdd = TFactory::makePowerConnector(mGraphicEntity, ecs::utility::getStringID<ecs::_TEntity::ID>(NewChipID), TPowerComponent::Type::GROUND);
#endif
			PackageType = TPackageComponent::TPackageType::POWER_CONNECTOR;
		}

		// Create a new graphic chip
#if ENTITY_SYSTEM == NNE
		mGraphicEntity.addEntity(FactoryFunction(), NewChipID, this);

		// Get the newly added CHIP
		mTempChip = mGraphicEntity.getEntityByKey(NewChipID);
#else
		mTempChip = mGraphicEntity.addEntity(std::move(EntityToAdd));
#endif
		
		mTempChip->init();
#if ENTITY_SYSTEM == NNE
		mTempChip->getComponent<TChipComponent>().setPlacedStatus(false);

		// Set the type of the package used for the component
		mTempChip->getComponent<TPackageComponent>().setPackageType(PackageType);

		// Set the chip name
		mTempChip->getComponent<TChipComponent>().setChipName(NewChipID);

		if (PackageType == TPackageComponent::TPackageType::DIP)
			mTempChip->getComponent<TPackageComponent>().updateChipName();
				
		// Set the used board
		mTempChip->getComponent<TLogicBoardComponent>().setBoard(mLogicBoard);
#else
		mTempChip->getComponent<TChipComponent>()->setPlacedStatus(false);

		// Set the type of the package used for the component
		mTempChip->getComponent<TPackageComponent>()->setPackageType(PackageType);

		// Set the chip name
		mTempChip->getComponent<TChipComponent>()->setChipName(NewChipID);

		if (PackageType == TPackageComponent::TPackageType::DIP)
			mTempChip->getComponent<TPackageComponent>()->updateChipName();

		// Set the used board
		mTempChip->getComponent<TLogicBoardComponent>()->setBoard(mLogicBoard);
#endif

		// And adds it to the logic board
		mLogicBoard.placeComponent<TChipComponent>(mTempChip);

#if ENTITY_SYSTEM == NNE
		mTempChip->getComponent<TEventComponent>().attachEvent(tcomponents::events::onMouseUp, [&](const TEntity* Sender, const sf::Event& EventData) {
#else
		mTempChip->getComponent<TEventComponent>()->attachEvent(tcomponents::events::onMouseUp, [&](const ecs::_TEntity* Sender, const sf::Event& EventData) {
#endif

			if (mLogicBoard.getInsertionMethod() != TBoard::TInsertionMethod::NONE)
				return;

#if ENTITY_SYSTEM == NNE
			auto& SelectedPin = Sender->getComponent<TPinComponent>().getSelectedPin();
#else
			auto& SelectedPin = Sender->getComponent<TPinComponent>()->getSelectedPin();
#endif

			if (SelectedPin != TPin::NotFound)
			{
				// Message 
				std::string Message =
					"Pin ID:   " + std::to_string(SelectedPin.getPinID()) + "\n" +
					"Pin Mode: " + std::to_string(static_cast<int>(SelectedPin.mPinMode)) + "\n" +
					"Pin Name: " + SelectedPin.mPinName + "\n" +
					"Pin Numb: " + std::to_string(SelectedPin.mPinNumber) + "\n" +
					"Pin GNum: " + std::to_string(SelectedPin.mPinGroupNumber) + "\n" +
					"Pin GrID: " + std::to_string(SelectedPin.mPinGroupID) + "\n" +
					"-------------" + "\n";

				for (auto& Pin : SelectedPin.getPinConnections())
					Message += "Connection ID: " + std::to_string(Pin->getPinID()) + "\n";

				::MessageBoxA(NULL, Message.c_str(), "PinSelected", MB_OK);
			}
			
		});

		// And set it as the active chip
		mLogicBoard.deselectEverything();
		mLogicBoard.setSelectedComponent<TChipComponent>(mTempChip);

		// Change the insertion method
		mLogicBoard.setInsertionMethod(TBoard::TInsertionMethod::CHIP);
}

	void TNewGameScene::removeWire(TWireComponent* Wire)
	{
		// Get the parent entity
		auto ParentEntity = Wire->getParent();

		// Get the pins connected to the wire
		auto& PinList = Wire->getConnectedPins();

		// Disconnect all the pin

		// If this wire has some other wires connected to it
		if (Wire->hasConnectedWires())
		{
			// For all the pin in the wire to remove it
			for (auto& LeftPin : Wire->getConnectedPins())
				for (auto ConnectedWire : Wire->getConnectedWires())
					for (auto& RightPin : ConnectedWire->getConnectedPins())
					{
						/// FUTURE FIX
						/*for (auto ConnectedPin : RightPin->getPinConnections())
							TPinComponentUtility::detachPins(*LeftPin, *ConnectedPin);*/
						
						TPinComponentUtility::detachPins(*LeftPin, *RightPin);
					}
		}

		// If we have 2 pin connected to this wire
		if (Wire->getConnectedPins().size() > 1)
		{
			// Get the iterator to the first element
			auto It = Wire->getConnectedPins().begin();

			// Get the value of the left pin
			auto LeftPin = *(It);

			// Get the value of the second pin
			auto RightPin = *(++It);

			TPinComponentUtility::detachPins(*LeftPin, *RightPin);
		}
		
		Wire->disconnectWire();
				
		// Remove the wire from the logic board
		mLogicBoard.removeComponent(Wire);

		// Remove the wire parent entity from the entity manager
#if ENTITY_SYSTEM == NNE
		mGraphicEntity.removeEntity(ParentEntity->getEntityID());
#else
		mGraphicEntity.removeEntity(ParentEntity.getID());
#endif

		// Success message
		::MessageBox(NULL, "The wire was successfully removed it!", "Removed!", MB_OK);
	}

	void TNewGameScene::removeBus(TBusComponent* Bus)
	{

	}

	void TNewGameScene::removeChip(TChipComponent* Chip)
	{
		// Get the parent entity
		auto ParentEntity = Chip->getParent();

		// Get a ref to the TPinComponent
#if ENTITY_SYSTEM == NNE
		auto& PinComponent = ParentEntity->getComponent<TPinComponent>();

		// Detach all the pins
		for (auto& Pin : PinComponent.getPinList())
			Pin.detachPin();
#else
		auto& PinComponent = ParentEntity.getComponent<TPinComponent>();

		// Detach all the pins
		for (auto& Pin : PinComponent->getPinList())
			Pin.detachPin();
#endif

		// Remove the wire from the logic board
		mLogicBoard.removeComponent(Chip);

		// Remove the wire parent entity from the entity manager
#if ENTITY_SYSTEM == NNE
		mGraphicEntity.removeEntity(ParentEntity->getEntityID());
#else
		mGraphicEntity.removeEntity(ParentEntity.getID());
#endif

		::MessageBoxA(NULL, "Chip removed!", "Bye bye!", MB_OK);
	}

	void TNewGameScene::removeTemporaryEntity()
	{
		// Bus part
		// If we were trying to place another wire but we haven't placed any point or only  before trying to add a new one point
		// Remove that wire from the logic board and delete the entity associated with it
#if ENTITY_SYSTEM == NNE
		if (mTempBus && mTempBus->getComponent<TBusComponent>().isDrawing())
#else
		if (mTempBus && mTempBus->getComponent<TBusComponent>()->isDrawing())
#endif
		{
			// Make sure we reset the state of the selected bus
			mLogicBoard.deselectComponent<TBusComponent>(true);

			// Remove the chip from the logic board
			mLogicBoard.removeComponent<TBusComponent>(mTempBus);

			// Remove the entity
#if ENTITY_SYSTEM == NNE
			mGraphicEntity.removeEntity(mTempBus->getEntityID());
#else
			mGraphicEntity.removeEntity(mTempBus->getID());
#endif

			// Reset the state of the temp shared_ptr to make sure we kill all the entity instances
			mTempBus.reset();
		}

		// Wire part
		// If we were trying to place another wire but we haven't placed any point or only  before trying to add a new one point
		// Remove that wire from the logic board and delete the entity associated with it
#if ENTITY_SYSTEM == NNE
		if (mTempWire && mTempWire->getComponent<TWireComponent>().isDrawing())
#else
		if (mTempWire && mTempWire->getComponent<TWireComponent>()->isDrawing())
#endif
		{
			// Make sure we reset the state of the selected wire
			mLogicBoard.deselectComponent<TWireComponent>(true);

			// Remove the chip from the logic board
			mLogicBoard.removeComponent<TWireComponent>(mTempWire);

			// Remove the entity
#if ENTITY_SYSTEM == NNE
			mGraphicEntity.removeEntity(mTempWire->getEntityID());
#else
			mGraphicEntity.removeEntity(mTempWire->getID());
#endif

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

#if ENTITY_SYSTEM == NNE
			if (!mTempChip->getComponent<TChipComponent>().isPlaced())
			{
				// Remove the chip from the logic board
				mLogicBoard.removeComponent<TChipComponent>(mTempChip);

				// Remove the entity
				mGraphicEntity.removeEntity(mTempChip->getEntityID());

				// Reset the state of the temp shared_ptr to make sure we kill all the entity instances
				mTempChip.reset();
			}
#else
			if (!mTempChip->getComponent<TChipComponent>()->isPlaced())
			{
				// Remove the chip from the logic board
				mLogicBoard.removeComponent<TChipComponent>(mTempChip);

				// Remove the entity
				mGraphicEntity.removeEntity(mTempChip->getID());

				// Reset the state of the temp shared_ptr to make sure we kill all the entity instances
				mTempChip.reset();
			}
#endif
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

		// Convert the mouse coordinate
		auto CellPos = mGridComponent->convertCoordinate(*mRenderCanvas, getMousePosition());

		// Normalize the zoom level
		auto ZoomLevel = static_cast<sf::Uint32>(mRenderCanvas->getZoomFactor() * 100);

		XStaticText->setCaption("X:" + std::to_string(static_cast<sf::Int32>(CellPos.x)));
		YStaticText->setCaption("Y:" + std::to_string(static_cast<sf::Int32>(CellPos.y)));
		ZStaticText->setCaption("Z:" + std::to_string(ZoomLevel) + "%");
	}

}
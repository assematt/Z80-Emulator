#include "TNewGameMenu.h"

#include <Windows.h>

#include "TDialogWindow.h"
#include "TRenderCanvas.h"
#include "TCacheManager.h"
#include "TImageButton.h"
#include "TGuiManager.h"
#include "TStaticText.h"
#include "TButton.h"

namespace nne
{
	namespace tgui
	{

		TNewGameMenu::TNewGameMenu(const std::string& MenuName /*= "NEW_GAME_MENU"*/)
		{
			TWidget::TWidget(MenuName);
		}

		void TNewGameMenu::init(TGuiManager* GuiManager)
		{
			// Menu property
			this->setColor({ 0, 0, 170 });
			this->enableInput(false);

			// Menu size
			auto MenuSize = getSize();

		#pragma region TOP PANEL
			// Top panel
			TContainer::Ptr HeaderPanel = std::make_shared<TContainer>();
			HeaderPanel->setName("HEADER_PANEL");
			//HeaderPanel->setPosition(mParentManager->getReferencePointPosition(TReferencePoint::LEFT_TOP));
			HeaderPanel->setPosition({ 0.f, 0.f });
			//HeaderPanel->setSize({ RenderingWindow.getSize().x, 50u });
			HeaderPanel->setSize({ MenuSize.x, 50u });
			HeaderPanel->setColor({ 0, 21, 38 });

			#pragma region PCB AND CODE BUTTON
			// PCB button
			TButton::Ptr PCBButton = std::make_shared<TButton>();
			PCBButton->setZIndex(3);
			PCBButton->setPadding({ 20u, 10u });
			PCBButton->setName("PCB_BUTTON");
			PCBButton->setCaption("PCB");
			PCBButton->setCharacterSize(24);
			PCBButton->setPosition({ 0.f, 0.f });
			HeaderPanel->addWidget(PCBButton.get());

			// Code button
			TButton::Ptr CodeButton = std::make_shared<TButton>();
			CodeButton->setZIndex(3);
			CodeButton->setPadding({ 20u, 10u });
			CodeButton->setName("CODE_BUTTON");
			CodeButton->setCaption("CODE");
			CodeButton->setCharacterSize(24);
			CodeButton->setPosition({ static_cast<float>(PCBButton->getSize().x), 0.f });
			HeaderPanel->addWidget(CodeButton.get());
#pragma endregion

			#pragma region MAIN MENU
			// File button
			TButton::Ptr FileButton = std::make_shared<TButton>();
			FileButton->setZIndex(3);
			FileButton->setPadding({ 12u, 16u });
			FileButton->setName("FILE_BUTTON");
			FileButton->setCaption("FILE");
			FileButton->setCharacterSize(16);
			FileButton->setPosition({ 325.f, 0.f });
			HeaderPanel->addWidget(FileButton.get());

			// Edit button
			TButton::Ptr EditButton = std::make_shared<TButton>();
			EditButton->setZIndex(3);
			EditButton->setPadding({ 12u, 16u });
			EditButton->setName("EDIT_BUTTON");
			EditButton->setCaption("EDIT");
			EditButton->setCharacterSize(16);
			EditButton->setPosition({ FileButton->getPosition().x + FileButton->getSize().x, 0.f });
			HeaderPanel->addWidget(EditButton.get());

			// Options button
			TButton::Ptr OptionsButton = std::make_shared<TButton>();
			OptionsButton->setZIndex(3);
			OptionsButton->setPadding({ 12u, 16u });
			OptionsButton->setName("OPTIONS_BUTTON");
			OptionsButton->setCaption("OPTIONS");
			OptionsButton->setCharacterSize(16);
			OptionsButton->setPosition({ EditButton->getPosition().x + EditButton->getSize().x, 0.f });
			HeaderPanel->addWidget(OptionsButton.get());

			// Help button
			TButton::Ptr HelpButton = std::make_shared<TButton>();
			HelpButton->setZIndex(3);
			HelpButton->setPadding({ 12u, 16u });
			HelpButton->setName("HELP_BUTTON");
			HelpButton->setCaption("HELP");
			HelpButton->setCharacterSize(16);
			HelpButton->setPosition({ OptionsButton->getPosition().x + OptionsButton->getSize().x, 0.f });
			HeaderPanel->addWidget(HelpButton.get());
#pragma endregion

			#pragma region DEBUG TEXT
			// Z Index
			TStaticText::Ptr ZIndexButton = std::make_shared<TStaticText>();
			//ZIndexButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-243.f, 16.f) });
			ZIndexButton->setPosition({ sf::Vector2f(MenuSize.x, 0.f) + sf::Vector2f(-243.f, 16.f) });
			ZIndexButton->setZIndex(3);
			ZIndexButton->setName("ZINDEX_TEXT");
			ZIndexButton->setCaption("Z:100%");
			ZIndexButton->setCharacterSize(16);
			HeaderPanel->addWidget(ZIndexButton.get());

			// X Value
			TStaticText::Ptr XValueButton = std::make_shared<TStaticText>();
			//XValueButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-162.f, 16.f) });
			XValueButton->setPosition({ sf::Vector2f(MenuSize.x, 0.f) + sf::Vector2f(-162.f, 16.f) });
			XValueButton->setZIndex(3);
			XValueButton->setName("XVALUE_TEXT");
			XValueButton->setCaption("X: 0");
			XValueButton->setCharacterSize(16);
			HeaderPanel->addWidget(XValueButton.get());

			// Y Value
			TStaticText::Ptr YValueButton = std::make_shared<TStaticText>();
			//YValueButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-81.f, 16.f) });
			YValueButton->setPosition({ sf::Vector2f(MenuSize.x, 0.f) + sf::Vector2f(-81.f, 16.f) });
			YValueButton->setZIndex(3);
			YValueButton->setName("YVALUE_TEXT");
			YValueButton->setCaption("Y: 0");
			YValueButton->setCharacterSize(16);
			HeaderPanel->addWidget(YValueButton.get());
#pragma endregion

#pragma endregion

		#pragma region LEFT TOOLS
			// Left tools panel
			TContainer::Ptr LeftToolsPanel = std::make_shared<TContainer>();
			LeftToolsPanel->setName("HEADER_PANEL");
			LeftToolsPanel->setPosition(sf::Vector2f(0, 50.f));
			LeftToolsPanel->setSize({ 300u, MenuSize.y - HeaderPanel->getSize().y });
			LeftToolsPanel->setColor({ 0, 35, 64 });

			#pragma region TOOLS LIST
			// Insert chip button
			TImageButton::Ptr InsertChipButton = std::make_shared<TImageButton>();
			InsertChipButton->setZIndex(3);
			InsertChipButton->setName("INSERT_CHIP_BUTTON");
			InsertChipButton->setCaption("INSERT CHIP");
			InsertChipButton->setCharacterSize(14);
			InsertChipButton->setSize({ 300, 35 });
			InsertChipButton->setPosition({ 0.f, 20.f });
			InsertChipButton->setPadding({ 54u, 9u });
			InsertChipButton->setToggleable(true);
			InsertChipButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("chip_btn"), { 20.f, 5.f });
			LeftToolsPanel->addWidget(InsertChipButton.get());

			#pragma region CHIP LIST
			// CHIP LIST PANEL
			TContainer::Ptr ChipListPanel = std::make_shared<TContainer>();
			ChipListPanel->setName("CHIP_LIST_PANEL");
			ChipListPanel->move({ 0.f, 55.f });
			ChipListPanel->setSize({ 300u, 210u });
			ChipListPanel->setColor({ 0, 105, 191 });
			ChipListPanel->setVisible(false);
			LeftToolsPanel->addWidget(ChipListPanel.get());

			// Insert CPU button
			#pragma region CPU BUTTON
			TImageButton::Ptr InsertCpuButton = std::make_shared<TImageButton>();
			InsertCpuButton->setZIndex(3);
			InsertCpuButton->setName("INSERT_CPU_BUTTON");
			InsertCpuButton->setCaption("INSERT CPU");
			InsertCpuButton->setCharacterSize(14);
			InsertCpuButton->setSize({ 300, 35 });
			InsertCpuButton->move({ 0.f, 0.f });
			InsertCpuButton->setPadding({ 54u, 9u });
			InsertCpuButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("cpu_btn"), { 20.f, 5.f });
			ChipListPanel->addWidget(InsertCpuButton.get());
			#pragma endregion			

			// Insert RAM button
			#pragma region RAM BUTTON
			TImageButton::Ptr InsertRamButton = std::make_shared<TImageButton>();
			InsertRamButton->setZIndex(3);
			InsertRamButton->setName("INSERT_RAM_BUTTON");
			InsertRamButton->setCaption("INSERT RAM");
			InsertRamButton->setCharacterSize(14);
			InsertRamButton->setSize({ 300, 35 });
			InsertRamButton->move({ 0.f, 35.f });
			InsertRamButton->setPadding({ 54u, 9u });
			InsertRamButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("ram_btn"), { 20.f, 5.f });
			ChipListPanel->addWidget(InsertRamButton.get());
			#pragma endregion

			// Insert NAND button
			#pragma region NAND BUTTON
			TImageButton::Ptr InsertNandButton = std::make_shared<TImageButton>();
			InsertNandButton->setZIndex(3);
			InsertNandButton->setName("INSERT_NAND_BUTTON");
			InsertNandButton->setCaption("INSERT NAND");
			InsertNandButton->setCharacterSize(14);
			InsertNandButton->setSize({ 300, 35 });
			InsertNandButton->move({ 0.f, 70.f });
			InsertNandButton->setPadding({ 54u, 9u });
			InsertNandButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("nand_btn"), { 20.f, 5.f });
			ChipListPanel->addWidget(InsertNandButton.get());
			#pragma endregion

			// Insert LED button
			#pragma region LED BUTTON
			TImageButton::Ptr InsertLedButton = std::make_shared<TImageButton>();
			InsertLedButton->setZIndex(3);
			InsertLedButton->setName("INSERT_LED_BUTTON");
			InsertLedButton->setCaption("INSERT LED");
			InsertLedButton->setCharacterSize(14);
			InsertLedButton->setSize({ 300, 35 });
			InsertLedButton->move({ 0.f, 105.f });
			InsertLedButton->setPadding({ 54u, 9u });
			InsertLedButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("led_btn"), { 20.f, 5.f });
			ChipListPanel->addWidget(InsertLedButton.get());
			#pragma endregion

			// Insert GROUND button
			#pragma region GROUND BUTTON
			TImageButton::Ptr InsertGroundButton = std::make_shared<TImageButton>();
			InsertGroundButton->setZIndex(3);
			InsertGroundButton->setName("INSERT_GROUND_BUTTON");
			InsertGroundButton->setCaption("INSERT GROUND");
			InsertGroundButton->setCharacterSize(14);
			InsertGroundButton->setSize({ 300, 35 });
			InsertGroundButton->move({ 0.f, 140.f });
			InsertGroundButton->setPadding({ 54u, 9u });
			InsertGroundButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("ground_btn"), { 20.f, 12.f });
			ChipListPanel->addWidget(InsertGroundButton.get());
			#pragma endregion

			// Insert POWER button
			#pragma region POWER BUTTON
			TImageButton::Ptr InsertPowerButton = std::make_shared<TImageButton>();
			InsertPowerButton->setZIndex(3);
			InsertPowerButton->setName("INSERT_POWER_BUTTON");
			InsertPowerButton->setCaption("INSERT POWER");
			InsertPowerButton->setCharacterSize(14);
			InsertPowerButton->setSize({ 300, 35 });
			InsertPowerButton->move({ 0.f, 175.f });
			InsertPowerButton->setPadding({ 54u, 9u });
			InsertPowerButton->setToggleable(true);
			InsertPowerButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("power_btn"), { 20.f, 5.f });
			ChipListPanel->addWidget(InsertPowerButton.get());
			#pragma endregion

			// Insert wire button
			TImageButton::Ptr InsertWireButton = std::make_shared<TImageButton>();
			InsertWireButton->setZIndex(3);
			InsertWireButton->setName("INSERT_WIRE_BUTTON");
			InsertWireButton->setCaption("INSERT WIRE");
			InsertWireButton->setCharacterSize(14);
			InsertWireButton->setSize({ 300, 35 });
			InsertWireButton->setPosition({ 0.f, 55.f });
			InsertWireButton->setPadding({ 54u, 9u });
			InsertWireButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("track_btn"), { 20.f, 5.f });
			LeftToolsPanel->addWidget(InsertWireButton.get());

			// Insert bus button
			TImageButton::Ptr InsertBusButton = std::make_shared<TImageButton>();
			InsertBusButton->setZIndex(3);
			InsertBusButton->setName("INSERT_BUS_BUTTON");
			InsertBusButton->setCaption("INSERT BUS");
			InsertBusButton->setCharacterSize(14);
			InsertBusButton->setSize({ 300, 35 });
			InsertBusButton->setPosition({ 0.f, 90.f });
			InsertBusButton->setPadding({ 54u, 9u });
			InsertBusButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("bus_btn"), { 21.f, 4.f });
			LeftToolsPanel->addWidget(InsertBusButton.get());
#pragma endregion

	#pragma endregion

			// Add the RenderCanvas widget
			TRenderCanvas::Ptr Canvas = std::make_shared<TRenderCanvas>();
			Canvas->setName("RENDER_CANVAS");
			Canvas->create(MenuSize.x - LeftToolsPanel->getSize().x, MenuSize.y - HeaderPanel->getSize().y);
			Canvas->setSize(MenuSize.x - LeftToolsPanel->getSize().x, MenuSize.y - HeaderPanel->getSize().y);
			Canvas->setPosition(LeftToolsPanel->getSize().x, HeaderPanel->getSize().y);
			
			// Adds the widgets to the menu
			GuiManager->addWidget(HeaderPanel, 2);
			GuiManager->addWidget(PCBButton, 3);
			GuiManager->addWidget(CodeButton, 3);

			GuiManager->addWidget(FileButton, 3);
			GuiManager->addWidget(EditButton, 3);
			GuiManager->addWidget(OptionsButton, 3);
			GuiManager->addWidget(HelpButton, 3);

			GuiManager->addWidget(ZIndexButton, 3);
			GuiManager->addWidget(XValueButton, 3);
			GuiManager->addWidget(YValueButton, 3);

			GuiManager->addWidget(LeftToolsPanel, 2);
			GuiManager->addWidget(InsertChipButton, 3);

			// CHIP LIST
			GuiManager->addWidget(ChipListPanel, 3);
			GuiManager->addWidget(InsertCpuButton, 4);
			GuiManager->addWidget(InsertRamButton, 4);
			GuiManager->addWidget(InsertNandButton, 4);
			GuiManager->addWidget(InsertLedButton, 4);
			GuiManager->addWidget(InsertGroundButton, 4);
			GuiManager->addWidget(InsertPowerButton, 4);

			GuiManager->addWidget(InsertWireButton, 3);
			GuiManager->addWidget(InsertBusButton, 3);

			GuiManager->addWidget(Canvas, 1);
		}

	}
}
#include "TNewGameMenu.h"
#include "TGuiManager.h"
#include "TStaticText.h"
#include "TButton.h"

namespace nne
{
	namespace tgui
	{

		void TNewGameMenu::init(TGuiManager* GuiManager)
		{
#pragma region TOP PANEL
			// Top panel
			TContainer::Ptr HeaderPanel = std::make_shared<TContainer>();
			HeaderPanel->setName("HEADER_PANEL");
			//HeaderPanel->setPosition(mParentManager->getReferencePointPosition(TReferencePoint::LEFT_TOP));
			HeaderPanel->setPosition({ 0.f, 0.f });
			//HeaderPanel->setSize({ RenderingWindow.getSize().x, 50u });
			HeaderPanel->setSize({ 1600u, 50u });
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
			ZIndexButton->setPosition({ sf::Vector2f(1600.f, 0.f) + sf::Vector2f(-243.f, 16.f) });
			ZIndexButton->setZIndex(3);
			ZIndexButton->setName("ZINDEX_TEXT");
			ZIndexButton->setCaption("Z:100%");
			ZIndexButton->setCharacterSize(16);
			HeaderPanel->addWidget(ZIndexButton.get());

			// X Value
			TStaticText::Ptr XValueButton = std::make_shared<TStaticText>();
			//XValueButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-162.f, 16.f) });
			XValueButton->setPosition({ sf::Vector2f(1600.f, 0.f) + sf::Vector2f(-162.f, 16.f) });
			XValueButton->setZIndex(3);
			XValueButton->setName("XVALUE_TEXT");
			XValueButton->setCaption("X: 0");
			XValueButton->setCharacterSize(16);
			HeaderPanel->addWidget(XValueButton.get());

			// Y Value
			TStaticText::Ptr YValueButton = std::make_shared<TStaticText>();
			//YValueButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-81.f, 16.f) });
			YValueButton->setPosition({ sf::Vector2f(1600.f, 0.f) + sf::Vector2f(-81.f, 16.f) });
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
			//LeftToolsPanel->setPosition(mParentManager->getReferencePointPosition(TReferencePoint::LEFT_TOP) + sf::Vector2f(0, 50.f));
			LeftToolsPanel->setPosition(sf::Vector2f(0.f, 0.f) + sf::Vector2f(0, 50.f));
			//LeftToolsPanel->setSize({ 300, RenderingWindow.getSize().y });
			LeftToolsPanel->setSize({ 300u, 900u });
			LeftToolsPanel->setColor({ 0, 35, 64 });

#pragma region TOOLS LIST
			// Insert chip button
			TButton::Ptr InsertChipButton = std::make_shared<TButton>();
			InsertChipButton->setZIndex(3);
			InsertChipButton->setName("INSERT_CHIP_BUTTON");
			InsertChipButton->setCaption("INSERT CHIP");
			InsertChipButton->setCharacterSize(14);
			InsertChipButton->setSize({ 300, 35 });
			InsertChipButton->move({ 0.f, 20.f });
			InsertChipButton->setPadding({ 54u, 9u });
			InsertChipButton->setToggleable(true);
			LeftToolsPanel->addWidget(InsertChipButton.get());

			// Insert track button
			TButton::Ptr InsertTrackButton = std::make_shared<TButton>();
			InsertTrackButton->setZIndex(3);
			InsertTrackButton->setName("INSERT_TRACK_BUTTON");
			InsertTrackButton->setCaption("INSERT TRACK");
			InsertTrackButton->setCharacterSize(14);
			InsertTrackButton->setSize({ 300, 35 });
			InsertTrackButton->move({ 0.f, 55.f });
			InsertTrackButton->setPadding({ 54u, 9u });
			InsertTrackButton->setToggleable(true);
			LeftToolsPanel->addWidget(InsertTrackButton.get());

			// Insert bus button
			TButton::Ptr InsertBusButton = std::make_shared<TButton>();
			InsertBusButton->setZIndex(3);
			InsertBusButton->setName("INSERT_BUS_BUTTON");
			InsertBusButton->setCaption("INSERT BUS");
			InsertBusButton->setCharacterSize(14);
			InsertBusButton->setSize({ 300, 35 });
			InsertBusButton->move({ 0.f, 90.f });
			InsertBusButton->setPadding({ 54u, 9u });
			InsertBusButton->setToggleable(true);
			LeftToolsPanel->addWidget(InsertBusButton.get());
#pragma endregion

#pragma endregion

			// Adds the widgets to the menu
			GuiManager->addWidget(HeaderPanel, 1);
			GuiManager->addWidget(PCBButton, 2);
			GuiManager->addWidget(CodeButton, 2);

			GuiManager->addWidget(FileButton, 2);
			GuiManager->addWidget(EditButton, 2);
			GuiManager->addWidget(OptionsButton, 2);
			GuiManager->addWidget(HelpButton, 2);

			GuiManager->addWidget(ZIndexButton, 2);
			GuiManager->addWidget(XValueButton, 2);
			GuiManager->addWidget(YValueButton, 2);

			GuiManager->addWidget(LeftToolsPanel, 1);
			GuiManager->addWidget(InsertChipButton, 2);
			GuiManager->addWidget(InsertTrackButton, 2);
			GuiManager->addWidget(InsertBusButton, 2);
		}

	}
}
#include "TNewGameMenu.h"
#include "TButton.h"
#include "TPanel.h"
#include "TStaticText.h"

namespace nne
{
	namespace tgui
	{
		void TNewGameMenu::init()
		{
			// Get a ref to the rendering window
			auto& RenderingWindow = mParentManager->getRenderingWindow();

		#pragma region TOP PANEL
			// Top panel
			TPanel::UniquePtr HeaderPanel = std::make_unique<TPanel>();
			HeaderPanel->setName("HEADER_PANEL");
			HeaderPanel->setPosition(mParentManager->getReferencePointPosition(TReferencePoint::LEFT_TOP));
			HeaderPanel->setSize({ RenderingWindow.getSize().x, 50u});
			HeaderPanel->setColor({ 0, 21, 38 });

			#pragma region PCB AND CODE BUTTON
			// PCB button
			TButton::UniquePtr PCBButton = std::make_unique<TButton>();
			PCBButton->setZIndex(3);
			PCBButton->setName("PCB_BUTTON");
			PCBButton->SetCaption("PCB");
			PCBButton->setCharacterSize(24);
			PCBButton->setPosition({ 20.f, 11.f });
			HeaderPanel->addWidget(PCBButton.get());

			// Code button
			TButton::UniquePtr CodeButton = std::make_unique<TButton>();
			CodeButton->setZIndex(3);
			CodeButton->setName("CODE_BUTTON");
			CodeButton->SetCaption("CODE");
			CodeButton->setCharacterSize(24);
			CodeButton->setPosition({ 100.f, 11.f });
			HeaderPanel->addWidget(CodeButton.get());
			#pragma endregion

			#pragma region MAIN MENU
			// File button
			TButton::UniquePtr FileButton = std::make_unique<TButton>();
			FileButton->setZIndex(3);
			FileButton->setName("FILE_BUTTON");
			FileButton->SetCaption("FILE");
			FileButton->setCharacterSize(16);
			FileButton->setPosition({ 325.f, 16.f });
			HeaderPanel->addWidget(FileButton.get());

			// Edit button
			TButton::UniquePtr EditButton = std::make_unique<TButton>();
			EditButton->setZIndex(3);
			EditButton->setName("EDIT_BUTTON");
			EditButton->SetCaption("EDIT");
			EditButton->setCharacterSize(16);
			EditButton->setPosition({ 387.f, 16.f });
			HeaderPanel->addWidget(EditButton.get());

			// Options button
			TButton::UniquePtr OptionsButton = std::make_unique<TButton>();
			OptionsButton->setZIndex(3);
			OptionsButton->setName("OPTIONS_BUTTON");
			OptionsButton->SetCaption("OPTIONS");
			OptionsButton->setCharacterSize(16);
			OptionsButton->setPosition({ 449.f, 16.f });
			HeaderPanel->addWidget(OptionsButton.get());

			// Help button
			TButton::UniquePtr HelpButton = std::make_unique<TButton>();
			HelpButton->setZIndex(3);
			HelpButton->setName("HELP_BUTTON");
			HelpButton->SetCaption("HELP");
			HelpButton->setCharacterSize(16);
			HelpButton->setPosition({ 539.f, 16.f });
			HeaderPanel->addWidget(HelpButton.get());
			#pragma endregion

			#pragma region DEBUG TEXT
			// Z Index
			TStaticText::UniquePtr ZIndexButton = std::make_unique<TStaticText>();
			ZIndexButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-243.f, 16.f) });
			ZIndexButton->setZIndex(3);
			ZIndexButton->setName("ZINDEX_TEXT");
			ZIndexButton->SetCaption("Z:100%");
			ZIndexButton->setCharacterSize(16);
			HeaderPanel->addWidget(ZIndexButton.get());

			// X Value
			TStaticText::UniquePtr XValueButton = std::make_unique<TStaticText>();
			XValueButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-162.f, 16.f) });
			XValueButton->setZIndex(3);
			XValueButton->setName("XVALUE_TEXT");
			XValueButton->SetCaption("X: ");
			XValueButton->setCharacterSize(16);
			HeaderPanel->addWidget(XValueButton.get());

			// Y Value
			TStaticText::UniquePtr YValueButton = std::make_unique<TStaticText>();
			YValueButton->setPosition({ mParentManager->getReferencePointPosition(TReferencePoint::RIGHT_TOP) + sf::Vector2f(-81.f, 16.f) });
			YValueButton->setZIndex(3);
			YValueButton->setName("YVALUE_TEXT");
			YValueButton->SetCaption("Y: ");
			YValueButton->setCharacterSize(16);
			HeaderPanel->addWidget(YValueButton.get());
			#pragma endregion

		#pragma endregion

		#pragma region LEFT TOOLS
			// Left tools panel
			TPanel::UniquePtr LeftToolsPanel = std::make_unique<TPanel>();
			LeftToolsPanel->setName("HEADER_PANEL");
			LeftToolsPanel->setPosition(mParentManager->getReferencePointPosition(TReferencePoint::LEFT_TOP) + sf::Vector2f(0, 50.f));
			LeftToolsPanel->setSize({ 300, RenderingWindow.getSize().y });
			LeftToolsPanel->setColor({ 0, 35, 64 });

			#pragma region TOOLS LIST
			// Insert chip button
			TButton::UniquePtr InsertChipButton = std::make_unique<TButton>();
			InsertChipButton->setZIndex(3);
			InsertChipButton->setName("INSERT_CHIP_BUTTON");
			InsertChipButton->SetCaption("INSERT CHIP");
			InsertChipButton->setCharacterSize(14);
			InsertChipButton->setPosition({ 54.f, 31.f });
			LeftToolsPanel->addWidget(InsertChipButton.get());

			// Insert track button
			TButton::UniquePtr InsertTrackButton = std::make_unique<TButton>();
			InsertTrackButton->setZIndex(3);
			InsertTrackButton->setName("INSERT_TRACK_BUTTON");
			InsertTrackButton->SetCaption("INSERT TRACK");
			InsertTrackButton->setCharacterSize(14);
			InsertTrackButton->setPosition({ 54.f, 66.f });
			LeftToolsPanel->addWidget(InsertTrackButton.get());

			// Insert bus button
			TButton::UniquePtr InsertBusButton = std::make_unique<TButton>();
			InsertBusButton->setZIndex(3);
			InsertBusButton->setName("INSERT_BUS_BUTTON");
			InsertBusButton->SetCaption("INSERT BUS");
			InsertBusButton->setCharacterSize(14);
			InsertBusButton->setPosition({ 54.f, 101.f });
			LeftToolsPanel->addWidget(InsertBusButton.get());
			#pragma endregion

		#pragma endregion

			// Adds the widgets to the menu
			this->addWidget(HeaderPanel);
			this->addWidget(PCBButton);
			this->addWidget(CodeButton);

			this->addWidget(FileButton);
			this->addWidget(EditButton);
			this->addWidget(OptionsButton);
			this->addWidget(HelpButton);

			this->addWidget(ZIndexButton);
			this->addWidget(XValueButton);
			this->addWidget(YValueButton);

			this->addWidget(LeftToolsPanel);
			this->addWidget(InsertChipButton);
			this->addWidget(InsertTrackButton);
			this->addWidget(InsertBusButton);
		}

		void TNewGameMenu::handleEvent(sf::Event& Event)
		{

		}

		void TNewGameMenu::refresh(const sf::Time& ElapsedTime)
		{
			IScreenView::refresh(ElapsedTime);

			auto XStaticText = getWidget<TStaticText>("XVALUE_TEXT");
			auto YStaticText = getWidget<TStaticText>("YVALUE_TEXT");

			auto& MousePos = sf::Mouse::getPosition(mParentManager->getRenderingWindow());

			XStaticText->SetCaption("X:" + std::to_string(MousePos.x));
			YStaticText->SetCaption("Y:" + std::to_string(MousePos.y));
		}

	}
}


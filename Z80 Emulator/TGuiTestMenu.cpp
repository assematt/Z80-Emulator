#include "TGuiTestMenu.h"

#include <Windows.h>

#include "TButton.h"
#include "TImage.h"
#include "TPanel.h"
#include "TStaticText.h"
#include "TGuiManager.h"
#include "TSceneManager.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{
		void TGuiTestMenu::init()
		{
			// Get a ref from the cache manager
			auto& CacheManager = TCacheManager::getInstance();

			// Create a Test Button
			tgui::TButton::UniquePtr TestButton = std::make_unique<tgui::TButton>();
			TestButton->setPosition({ 50.f, 50.f });
			TestButton->setName("TEST_BUTTON");
			TestButton->SetCaption("TEST BUTTON");
			TestButton->connectSignal(std::bind(&TGuiTestMenu::onTestButtonClick, this, std::placeholders::_1), tevent::_OnMouseClick);
			addWidget(TestButton);

			// Create a Static Label
			tgui::TStaticText::UniquePtr TextStatic = std::make_unique<tgui::TStaticText>();
			TextStatic->setPosition({ 50.f, 100.f });
			TextStatic->setName("STATIC_TEXT");
			TextStatic->SetCaption("STATIC TEXT");
			addWidget(TextStatic);

			// Create a Static Label
			tgui::TStaticText::UniquePtr TextStatic2 = std::make_unique<tgui::TStaticText>();
			TextStatic2->setPosition({ 600.f, 50.f });
			TextStatic2->setName("STATIC_TEXT_2");
			TextStatic2->SetCaption("MULTI-LINE TEXT\nMULTI-LINE TEXT");
			TextStatic2->getComponentAsPtr<TTextComponent>()->setOutlineColor(sf::Color::White);
			TextStatic2->getComponentAsPtr<TTextComponent>()->setOutlineThickness(2.f);
			TextStatic2->getComponentAsPtr<TTextComponent>()->setStyle(TTextComponent::TStyle::StrikeThrough | TTextComponent::TStyle::Underlined | TTextComponent::TStyle::Bold);
			TextStatic2->getComponentAsPtr<TTextComponent>()->setCharacterFillColor(sf::Color::Red, 1, 3);
			TextStatic2->getComponentAsPtr<TTextComponent>()->setCharacterOutlineColor(sf::Color::Blue, 4);
			addWidget(TextStatic2);

			// Create a simple image
			tgui::TImage::UniquePtr TestImage = std::make_unique<tgui::TImage>();
			TestImage->setName("TEST_IMAGE");
			TestImage->setPosition({ 50.f, 150.f });
			TestImage->SetImage(CacheManager.getResource<sf::Texture>("test_image"));
			TestImage->disableInput();
			addWidget(TestImage);

			// Create a container class that contains some widget
			tgui::TPanel::UniquePtr TestPanel = std::make_unique<tgui::TPanel>();
			TestPanel->setName("TEST_PANEL");
			TestPanel->setPosition({ 400.f, 50.f });
			TestPanel->disableInput();
			addWidget(TestPanel);
		}

		void TGuiTestMenu::onTestButtonClick(const sf::Event::MouseButtonEvent& Button)
		{
			std::string DebugMessage = "Test button pressed X:" + std::to_string(Button.x) + " Y:" + std::to_string(Button.y);
			MessageBoxA(NULL, DebugMessage.c_str(), "Test button pressed", MB_OK);
		}

	}
}


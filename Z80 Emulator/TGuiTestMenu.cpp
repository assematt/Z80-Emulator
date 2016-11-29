#include "TGuiTestMenu.h"

#include <Windows.h>

#include "TGuiButton.h"
#include "TGuiImage.h"
#include "TGuiPanel.h"
#include "TGuiStaticText.h"
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
			tgui::TGuiButton::UniquePtr TestButton = std::make_unique<tgui::TGuiButton>();
			TestButton->setPosition({ 50.f, 50.f });
			TestButton->setName("TEST_BUTTON");
			TestButton->SetCaption("TEST BUTTON");
			TestButton->connectSignal(std::bind(&TGuiTestMenu::onTestButtonClick, this, std::placeholders::_1), tevent::_OnMouseClick);
			this->addWidget(TestButton);

			// Create a Static Label
			tgui::TGuiStaticText::UniquePtr TextStatic = std::make_unique<tgui::TGuiStaticText>();
			TextStatic->setPosition({ 50.f, 100.f });
			TextStatic->setName("STATIC_TEXT");
			TextStatic->SetCaption("STATIC TEXT");
			this->addWidget(TextStatic);

			// Create a simple image
			tgui::TGuiImage::UniquePtr TestImage = std::make_unique<tgui::TGuiImage>();
			TestImage->setPosition({ 50.f, 150.f });
			TestImage->SetImage(CacheManager.getResource<sf::Texture>("test_image"));
			TestImage->disableInput();
			this->addWidget(TestImage);

			// Create a container class that contains some widget
			tgui::TGuiPanel::UniquePtr TestPanel = std::make_unique<tgui::TGuiPanel>();
			TestPanel->setPosition({ 400.f, 50.f });
			TestPanel->disableInput();
			this->addWidget(TestPanel);

		}

		void TGuiTestMenu::onTestButtonClick(const sf::Event::MouseButtonEvent& Button)
		{
			std::string DebugMessage = "Test button pressed X:" + std::to_string(Button.x) + " Y:" + std::to_string(Button.y);
			MessageBoxA(NULL, DebugMessage.c_str(), "Test button pressed", MB_OK);
		}

	}
}


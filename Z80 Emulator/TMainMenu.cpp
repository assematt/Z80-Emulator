#include "TMainMenu.h"

#include <SFML/Graphics/Texture.hpp>
#include <Windows.h>

#include "TCacheManager.h"
#include "TGuiManager.h"
#include "TMenuButton.h"
#include "TImage.h"

namespace nne
{
	namespace tgui
	{

		TMainMenu::TMainMenu(const std::string& MenuName /*= "MAIN_MENU"*/)
		{
			TWidget::TWidget(MenuName);
		}

		void TMainMenu::init(TGuiManager* GuiManager)
		{
			// Menu property
			this->setColor({ 0, 0, 170 });
			this->enableInput(false);

			TImage::Ptr MonitorEffect = std::make_shared<TImage>();
			MonitorEffect->setName("MONITOR_SHADOW");
			MonitorEffect->setImage(TCacheManager::getInstance().getResource<sf::Texture>("monitor_shadow"));
			MonitorEffect->setSize(getSize());
			MonitorEffect->enableInput(false);

			TImage::Ptr MonitorFrame = std::make_shared<TImage>();
			MonitorFrame->setName("MONITOR_EFFECT");
			auto& Texture = TCacheManager::getInstance().getResource<sf::Texture>("monitor_effect_2");
			Texture.setRepeated(true);
			MonitorFrame->setTexture(&Texture);
			MonitorFrame->setTextureRect({ { 0, 0 }, static_cast<sf::Vector2i>(getSize()) });
			MonitorFrame->setOpacity(76);
			MonitorFrame->enableInput(false);
			MonitorFrame->setSize(getSize());

			TMenuButton::Ptr StoryMode = std::make_shared<TMenuButton>();
			StoryMode->setName("STORY_MODE");
			StoryMode->setCaption("STORY MODE");
			StoryMode->setFillColor(sf::Color::White);
			StoryMode->setCharacterFillColor({ 51u, 51u, 51u }, 0);
			StoryMode->setPosition(getWidgetReferencePointPosition(TReferencePoint::CENTER) - sf::Vector2f(StoryMode->getSize().x / 2.f, 0.f));
			StoryMode->disableWidget();

			TMenuButton::Ptr SandboxMode = std::make_shared<TMenuButton>();
			SandboxMode->setName("SANDBOX_MODE");
			SandboxMode->setCaption("SANDBOX MODE");
			SandboxMode->setFillColor(sf::Color::White);
			SandboxMode->setCharacterFillColor({ 170u, 0u, 0u }, 1);
			SandboxMode->attachEvent(events::onMouseUp, [](TWidget* Sender, const sf::Event& EventData) {
				// Goes to the editor
				Sender->getManager().changeScene(1);
			});
			SandboxMode->setPosition(getWidgetReferencePointPosition(TReferencePoint::CENTER) + sf::Vector2f(-(SandboxMode->getSize().x / 2.f), 50.f));

			TMenuButton::Ptr ChallangeMode = std::make_shared<TMenuButton>();
			ChallangeMode->setName("CHALLANGE_MODE");
			ChallangeMode->setCaption("CHALLANGE MODE");
			ChallangeMode->disableWidget();
			ChallangeMode->setFillColor(sf::Color::White);
			ChallangeMode->setCharacterFillColor({ 51u, 51u, 51u }, 0);
			ChallangeMode->setPosition(getWidgetReferencePointPosition(TReferencePoint::CENTER) + sf::Vector2f(-(ChallangeMode->getSize().x / 2.f), 100.f));

			TMenuButton::Ptr Options = std::make_shared<TMenuButton>();
			Options->setName("OPTIONS");
			Options->setCaption("OPTIONS");
			Options->disableWidget();
			Options->setFillColor(sf::Color::White);
			Options->setCharacterFillColor({ 51u, 51u, 51u }, 0);
			Options->setPosition(getWidgetReferencePointPosition(TReferencePoint::CENTER) + sf::Vector2f(-(Options->getSize().x / 2.f), 150.f));

			TMenuButton::Ptr Credits = std::make_shared<TMenuButton>();
			Credits->setName("CREDITS");
			Credits->setCaption("CREDITS");
			Credits->disableWidget();
			Credits->setFillColor(sf::Color::White);
			Credits->setCharacterFillColor({ 51u, 51u, 51u }, 0);
			Credits->setPosition(getWidgetReferencePointPosition(TReferencePoint::CENTER) + sf::Vector2f(-(Credits->getSize().x / 2.f), 200.f));

			TMenuButton::Ptr Quit = std::make_shared<TMenuButton>();
			Quit->setName("QUIT");
			Quit->setCaption("QUIT");
			Quit->setFillColor(sf::Color::White);
			Quit->setCharacterFillColor({ 170u, 0u, 0u }, 0);
			Quit->attachEvent(events::onClick, [](TWidget* Sender, const sf::Event& EventData) {
				// Quit the program
				Sender->getManager().changeScene(IScene::Exit);
			});
			Quit->setPosition(getWidgetReferencePointPosition(TReferencePoint::CENTER) + sf::Vector2f(-(Quit->getSize().x / 2.f), 250.f));

			// Adds the widgets to the menu
			//GuiManager->addWidget(BackgroundColor, 1);
			GuiManager->addWidget(MonitorEffect, 2);
			GuiManager->addWidget(MonitorFrame, 2);
			GuiManager->addWidget(StoryMode, 3);
			GuiManager->addWidget(SandboxMode, 3);
			GuiManager->addWidget(ChallangeMode, 3);
			GuiManager->addWidget(Options, 3);
			GuiManager->addWidget(Credits, 3);
			GuiManager->addWidget(Quit, 3);
		}

	}
}
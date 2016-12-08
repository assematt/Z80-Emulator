#include "TMainMenu.h"
#include <SFML/Graphics/Texture.hpp>
#include "TCacheManager.h"
#include "TGuiManager.h"
#include "TButton.h"
#include "TImage.h"

namespace nne
{
	namespace tgui
	{

		void TMainMenu::init(TGuiManager* GuiManager)
		{
			TImage::Ptr BackgroundColor = std::make_shared<TImage>();
			BackgroundColor->setName("BACKGROUND_COLOR");
			BackgroundColor->setSize({ 1600u, 900u });
			BackgroundColor->setColor({ 0, 0, 170 });
			BackgroundColor->enableInput(false);

			TImage::Ptr MonitorEffect = std::make_shared<TImage>();
			MonitorEffect->setName("MONITOR_SHADOW");
			MonitorEffect->setImage(TCacheManager::getInstance().getResource<sf::Texture>("monitor_shadow"));
			MonitorEffect->setSize({ 1600u, 900u });
			MonitorEffect->enableInput(false);

			TImage::Ptr MonitorFrame = std::make_shared<TImage>();
			MonitorFrame->setName("MONITOR_EFFECT");
			auto& Texture = TCacheManager::getInstance().getResource<sf::Texture>("monitor_effect_2");
			Texture.setRepeated(true);
			dynamic_cast<TWidget*>(MonitorFrame.get())->setTexture(&Texture);
			dynamic_cast<TWidget*>(MonitorFrame.get())->setTextureRect({ 0, 0, 1600, 900 });
			dynamic_cast<TWidget*>(MonitorFrame.get())->setOpacity(76);
			MonitorFrame->enableInput(false);
			MonitorFrame->setSize({ 1600u, 900u });

			TButton::Ptr StoryMode = std::make_shared<TButton>();
			StoryMode->setName("STORY_MODE");
			StoryMode->setCaption("STORY MODE");
			StoryMode->setPosition(getWidgetReferencePointPosition(TWidget::TReferencePoint::CENTER) - sf::Vector2f(StoryMode->getSize().x / 2.f, 0.f));
			//StoryMode->connectSignal(std::bind(&TMainMenu::onNewGameButtonClick, this, std::placeholders::_1), tevent::_OnMouseClick);

			TButton::Ptr SandboxMode = std::make_shared<TButton>();
			SandboxMode->setName("SANDBOX_MODE");
			SandboxMode->setCaption("SANDBOX MODE");
			SandboxMode->setPosition(getWidgetReferencePointPosition(TWidget::TReferencePoint::CENTER) + sf::Vector2f(-(SandboxMode->getSize().x / 2.f), 50.f));

			TButton::Ptr ChallangeMode = std::make_shared<TButton>();
			ChallangeMode->setName("CHALLANGE_MODE");
			ChallangeMode->setCaption("CHALLANGE MODE");
			ChallangeMode->setPosition(getWidgetReferencePointPosition(TWidget::TReferencePoint::CENTER) + sf::Vector2f(-(ChallangeMode->getSize().x / 2.f), 100.f));

			TButton::Ptr Options = std::make_shared<TButton>();
			Options->setName("OPTIONS");
			Options->setCaption("OPTIONS");
			Options->setPosition(getWidgetReferencePointPosition(TWidget::TReferencePoint::CENTER) + sf::Vector2f(-(Options->getSize().x / 2.f), 150.f));

			TButton::Ptr Credits = std::make_shared<TButton>();
			Credits->setName("CREDITS");
			Credits->setCaption("CREDITS");
			Credits->setPosition(getWidgetReferencePointPosition(TWidget::TReferencePoint::CENTER) + sf::Vector2f(-(Credits->getSize().x / 2.f), 200.f));

			TButton::Ptr Quit = std::make_shared<TButton>();
			Quit->setName("QUIT");
			Quit->setCaption("QUIT");
			Quit->setPosition(getWidgetReferencePointPosition(TWidget::TReferencePoint::CENTER) + sf::Vector2f(-(Quit->getSize().x / 2.f), 250.f));

			// Adds the widgets to the menu
			GuiManager->addWidget(BackgroundColor, 1);
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
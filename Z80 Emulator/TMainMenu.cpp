#include "TMainMenu.h"

namespace nne
{
	namespace tgui
	{
		void TMainMenu::setup()
		{
			// get a ref to the cache manager and the rendering window
			auto& CacheManager = TCacheManager::getInstance();
			auto& RenderingWindow = TGuiWindow::getInstance();

			tgui::TGuiImage::UniquePtr BackgroundColor = std::make_unique<tgui::TGuiImage>();
			sf::Image TempImage;
			TempImage.create(RenderingWindow.getSize().x, RenderingWindow.getSize().y, sf::Color(0, 0, 170));
			sf::Texture TempTexture;
			TempTexture.loadFromImage(TempImage);
			BackgroundColor->SetImage(TempTexture);
			BackgroundColor->disableInput();
			this->addWidget(BackgroundColor, 0);

			tgui::TGuiImage::UniquePtr MonitorEffect = std::make_unique<tgui::TGuiImage>();
			MonitorEffect->SetImage(CacheManager.getResource<sf::Texture>("monitor_shadow"));
			MonitorEffect->setSize(RenderingWindow.getSize());
			MonitorEffect->disableInput();
			this->addWidget(MonitorEffect, 10);

			tgui::TGuiImage::UniquePtr MonitorFrame = std::make_unique<tgui::TGuiImage>();
			MonitorFrame->SetImage(CacheManager.getResource<sf::Texture>("monitor_effect"));
			MonitorFrame->disableInput();
			this->addWidget(MonitorFrame, 9);

			tgui::TGuiButton::UniquePtr StoryMode = std::make_unique<tgui::TGuiButton>();
			StoryMode->setPosition(getReferencePointPosition());
			StoryMode->setName("STORY_MODE");
			StoryMode->SetCaption("STORY MODE");
			StoryMode->connectSignal(std::bind(&TMainMenu::onNewGameButtonClick, this, std::placeholders::_1), tevent::_OnMouseClick);
			this->addWidget(StoryMode, 3);

			tgui::TGuiButton::UniquePtr SandboxMode = std::make_unique<tgui::TGuiButton>();
			SandboxMode->setPosition(getReferencePointPosition() + sf::Vector2f(0.f, 50.f));
			SandboxMode->setName("SANDBOX_MODE");
			SandboxMode->SetCaption("SANDBOX MODE");
			this->addWidget(SandboxMode, 3);

			tgui::TGuiButton::UniquePtr ChallangeMode = std::make_unique<tgui::TGuiButton>();
			ChallangeMode->setPosition(getReferencePointPosition() + sf::Vector2f(0.f, 100.f));
			ChallangeMode->setName("CHALLANGE_MODE");
			ChallangeMode->SetCaption("CHALLANGE MODE");
			this->addWidget(ChallangeMode, 3);

			tgui::TGuiButton::UniquePtr Options = std::make_unique<tgui::TGuiButton>();
			Options->setPosition(getReferencePointPosition() + sf::Vector2f(0.f, 150.f));
			Options->setName("OPTIONS");
			Options->SetCaption("OPTIONS");
			this->addWidget(Options, 3);

			tgui::TGuiButton::UniquePtr Credits = std::make_unique<tgui::TGuiButton>();
			Credits->setPosition(getReferencePointPosition() + sf::Vector2f(0.f, 200.f));
			Credits->setName("CREDITS");
			Credits->SetCaption("CREDITS");
			this->addWidget(Credits, 3);

			tgui::TGuiButton::UniquePtr Quit = std::make_unique<tgui::TGuiButton>();
			Quit->setPosition(getReferencePointPosition() + sf::Vector2f(0.f, 250.f));
			Quit->setName("QUIT");
			Quit->SetCaption("QUIT");
			this->addWidget(Quit, 3);
		}

		void TMainMenu::onNewGameButtonClick(const sf::Event::MouseButtonEvent& Button)
		{
			mParentManager->changeMenu(1);
		}

	}
}


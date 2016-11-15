#include "TMainMenu.h"

namespace nne
{
	namespace tgui
	{
		void TMainMenu::Setup()
		{
			// get a ref to the cache manager and the rendering window
			auto& CacheManager = TCacheManager::GetInstance();
			auto& RenderingWindow = TGuiWindow::GetInstance();

			tgui::TGuiImage::UniquePtr BackgroundColor = std::make_unique<tgui::TGuiImage>();
			sf::Image TempImage;
			TempImage.create(RenderingWindow.getSize().x, RenderingWindow.getSize().y, sf::Color(0, 0, 170));
			sf::Texture TempTexture;
			TempTexture.loadFromImage(TempImage);
			BackgroundColor->SetImage(TempTexture);
			BackgroundColor->DisableInput();
			this->AddWidget(BackgroundColor, 0);

			tgui::TGuiImage::UniquePtr MonitorEffect = std::make_unique<tgui::TGuiImage>();
			MonitorEffect->SetImage(CacheManager.GetResource<sf::Texture>("monitor_shadow"));
			MonitorEffect->SetSize(RenderingWindow.getSize());
			MonitorEffect->DisableInput();
			this->AddWidget(MonitorEffect, 10);

			tgui::TGuiImage::UniquePtr MonitorFrame = std::make_unique<tgui::TGuiImage>();
			MonitorFrame->SetImage(CacheManager.GetResource<sf::Texture>("monitor_effect"));
			MonitorFrame->DisableInput();
			this->AddWidget(MonitorFrame, 9);

			tgui::TGuiButton::UniquePtr StoryMode = std::make_unique<tgui::TGuiButton>();
			StoryMode->SetPosition(GetReferencePointPosition());
			StoryMode->SetName("STORY_MODE");
			StoryMode->SetCaption("STORY MODE");
			StoryMode->ConnectSignal(std::bind(&TMainMenu::OnNewGameButtonClick, this, std::placeholders::_1), tevent::_OnMouseClick);
			this->AddWidget(StoryMode, 3);

			tgui::TGuiButton::UniquePtr SandboxMode = std::make_unique<tgui::TGuiButton>();
			SandboxMode->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 50.f));
			SandboxMode->SetName("SANDBOX_MODE");
			SandboxMode->SetCaption("SANDBOX MODE");
			this->AddWidget(SandboxMode, 3);

			tgui::TGuiButton::UniquePtr ChallangeMode = std::make_unique<tgui::TGuiButton>();
			ChallangeMode->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 100.f));
			ChallangeMode->SetName("CHALLANGE_MODE");
			ChallangeMode->SetCaption("CHALLANGE MODE");
			this->AddWidget(ChallangeMode, 3);

			tgui::TGuiButton::UniquePtr Options = std::make_unique<tgui::TGuiButton>();
			Options->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 150.f));
			Options->SetName("OPTIONS");
			Options->SetCaption("OPTIONS");
			this->AddWidget(Options, 3);

			tgui::TGuiButton::UniquePtr Credits = std::make_unique<tgui::TGuiButton>();
			Credits->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 200.f));
			Credits->SetName("CREDITS");
			Credits->SetCaption("CREDITS");
			this->AddWidget(Credits, 3);

			tgui::TGuiButton::UniquePtr Quit = std::make_unique<tgui::TGuiButton>();
			Quit->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 250.f));
			Quit->SetName("QUIT");
			Quit->SetCaption("QUIT");
			this->AddWidget(Quit, 3);
		}

		void TMainMenu::OnNewGameButtonClick(const sf::Event::MouseButtonEvent& Button)
		{
			mParentManager->ChangeMenu(1);
		}

	}
}


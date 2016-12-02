#include "TMainMenu.h"
#include "TGuiManager.h"
#include "TSceneManager.h"

namespace nne
{
	namespace tgui
	{
		void TMainMenu::init()
		{
			// get a ref to the cache manager and the rendering window
			auto& CacheManager = TCacheManager::getInstance();
			auto& RenderingWindow = mParentManager->getRenderingWindow();

			tgui::TImage::UniquePtr BackgroundColor = std::make_unique<tgui::TImage>();
			BackgroundColor->setName("BACKGROUND_COLOR");
			BackgroundColor->setSize({RenderingWindow.getSize().x, RenderingWindow.getSize().y});
			BackgroundColor->getComponentAsPtr<TDrawableComponent>()->setColor({ 0, 0, 170 });
			BackgroundColor->setZIndex(0);
			BackgroundColor->disableInput();
			this->addWidget(BackgroundColor);

			tgui::TImage::UniquePtr MonitorEffect = std::make_unique<tgui::TImage>();
			MonitorEffect->setName("MONITOR_SHADOW");
			MonitorEffect->SetImage(CacheManager.getResource<sf::Texture>("monitor_shadow"));
			MonitorEffect->setZIndex(10);
			MonitorEffect->setSize(RenderingWindow.getSize());
			MonitorEffect->disableInput();
			this->addWidget(MonitorEffect);

			tgui::TImage::UniquePtr MonitorFrame = std::make_unique<tgui::TImage>();
			MonitorFrame->setName("MONITOR_EFFECT");
			MonitorFrame->SetImage(CacheManager.getResource<sf::Texture>("monitor_effect"));
			MonitorFrame->setZIndex(9);
			MonitorFrame->disableInput();
			this->addWidget(MonitorFrame);

			tgui::TButton::UniquePtr StoryMode = std::make_unique<tgui::TButton>();
			StoryMode->setPosition(mParentManager->getReferencePointPosition());
			StoryMode->setZIndex(3);
			StoryMode->setName("STORY_MODE");
			StoryMode->SetCaption("STORY MODE");
			StoryMode->connectSignal(std::bind(&TMainMenu::onNewGameButtonClick, this, std::placeholders::_1), tevent::_OnMouseClick);
			this->addWidget(StoryMode);

			tgui::TButton::UniquePtr SandboxMode = std::make_unique<tgui::TButton>();
			SandboxMode->setPosition(mParentManager->getReferencePointPosition() + sf::Vector2f(0.f, 50.f));
			SandboxMode->setZIndex(3);
			SandboxMode->setName("SANDBOX_MODE");
			SandboxMode->SetCaption("SANDBOX MODE");
			this->addWidget(SandboxMode);

			tgui::TButton::UniquePtr ChallangeMode = std::make_unique<tgui::TButton>();
			ChallangeMode->setPosition(mParentManager->getReferencePointPosition() + sf::Vector2f(0.f, 100.f));
			ChallangeMode->setZIndex(3);
			ChallangeMode->setName("CHALLANGE_MODE");
			ChallangeMode->SetCaption("CHALLANGE MODE");
			this->addWidget(ChallangeMode);

			tgui::TButton::UniquePtr Options = std::make_unique<tgui::TButton>();
			Options->setPosition(mParentManager->getReferencePointPosition() + sf::Vector2f(0.f, 150.f));
			Options->setZIndex(3);
			Options->setName("OPTIONS");
			Options->SetCaption("OPTIONS");
			this->addWidget(Options);

			tgui::TButton::UniquePtr Credits = std::make_unique<tgui::TButton>();
			Credits->setPosition(mParentManager->getReferencePointPosition() + sf::Vector2f(0.f, 200.f));
			Credits->setZIndex(3);
			Credits->setName("CREDITS");
			Credits->SetCaption("CREDITS");
			this->addWidget(Credits);

			tgui::TButton::UniquePtr Quit = std::make_unique<tgui::TButton>();
			Quit->setPosition(mParentManager->getReferencePointPosition() + sf::Vector2f(0.f, 250.f));
			Quit->setZIndex(3);
			Quit->setName("QUIT");
			Quit->SetCaption("QUIT");
			this->addWidget(Quit);
		}

		void TMainMenu::onNewGameButtonClick(const sf::Event::MouseButtonEvent& Button)
		{
			mParentManager->getSceneManager()->changeScene(1);
		}

	}
}


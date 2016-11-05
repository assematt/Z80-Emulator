#include "TGameApp.h"

namespace nne
{

	TGameApp::TGameApp() :
		mAppName(PROGRAM_NAME)
	{
	}

	bool TGameApp::Init()
	{
		// Load the resources
		auto& CacheManager = TCacheManager::GetInstance();
		CacheManager.AddResource(nne::TResourceLoader<nne::TTexture>(nne::TTextureLoader("resources/images/crt_monitor_effect.png"), "sprite_1"));
		CacheManager.AddResource(nne::TResourceLoader<nne::TTexture>(nne::TTextureLoader("resources/images/crt_monitor_frame.png"), "sprite_2"));

		// Create a temp value the background and logo image
		auto& BackgroundImage = TFactory::MakeDrawableEntity();
		auto& Logo = TFactory::MakeDrawableEntity();

		// Set the texture for the background and logo image
		*BackgroundImage->GetComponentAsPtr<TTexture>() = CacheManager.GetResource<nne::TTexture>("sprite_1");
		*Logo->GetComponentAsPtr<TTexture>() = CacheManager.GetResource<nne::TTexture>("sprite_2");

		//BackgroundImage->GetComponentAsPtr<TTexture>()->SetTexture(CacheManager.GetResource<nne::TTexture>("sprite_1"));
		//Logo->GetComponentAsPtr<TTexture>()->SetTexture(CacheManager.GetResource<nne::TTexture>("sprite_2"));

		// Add the background and logo to the entity manager
		auto& Manager = TManager::GetInstance();
		Manager.AddComponent<TGraphicEntity>(std::move(BackgroundImage));
		Manager.AddComponent<TGraphicEntity>(std::move(Logo));

		// Create the window
		TGuiWindow::GetInstance().create(sf::VideoMode(1920, 1080), mAppName.c_str(), sf::Style::Default);

		// Initialize the GUI
		mAppGui.Setup();

		return true;
	}

	bool TGameApp::LoadConfiguration(const std::string& ConfigFile)
	{
		return true;
	}

	int TGameApp::Run()
	{
		mAppClock.restart();

		while (TGuiWindow::GetInstance().isOpen())
		{
			sf::Time ElapsedTime = mAppClock.restart();

			EventLoop();

			Refresh(ElapsedTime);

			Update(ElapsedTime);

			Draw();
		}

		return 0;
	}

	void TGameApp::EventLoop()
	{
		while (TGuiWindow::GetInstance().pollEvent(mAppEvent))
		{
			//mAppGui.ProcessEvents(mAppEvent);

			if (mAppEvent.type == sf::Event::Closed)
				TGuiWindow::GetInstance().close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				TGuiWindow::GetInstance().close();
		}
	}

	void TGameApp::Refresh(sf::Time ElapsedTime)
	{
		mAppGui.Refresh(ElapsedTime);

		nne::TManager::GetInstance().Refresh(ElapsedTime);
	}

	void TGameApp::Update(sf::Time ElapsedTime)
	{
		mAppGui.Update(ElapsedTime);

		nne::TManager::GetInstance().Update(ElapsedTime);
	}

	void TGameApp::Draw()
	{
		// Clear the back buffered window
		TGuiWindow::GetInstance().clear();

		// Render all the entity in the the entity manager
		nne::TManager::GetInstance().Draw();

		// Render the GUI
		mAppGui.Draw();
					
		// Display the back buffered window
		TGuiWindow::GetInstance().display();
	}

}
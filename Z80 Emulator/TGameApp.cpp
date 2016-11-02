#include "TGameApp.h"

namespace nne
{

	TGameApp::TGameApp() :
		mAppName(PROGRAM_NAME)
	{
	}

	bool TGameApp::Init()
	{
		TGuiWindow::GetInstance().create(sf::VideoMode(1920, 1080), mAppName.c_str(), sf::Style::Default);

		// Load background image
		auto& BackgroundImage = TFactory::MakeDrawableEntity();

		// If the image is successfully loaded put that in the array
		if (BackgroundImage->GetComponentAsPtr<TTexture>()->LoadTextureFromFile("resources/images/crt_monitor_effect.png"))
		{
			TManager::GetInstance().AddComponent<TGraphicEntity>(std::move(BackgroundImage));
		}

		// Load logo image
		auto& Logo = TFactory::MakeDrawableEntity();

		// If the image is successfully loaded put that in the array
		if (Logo->GetComponentAsPtr<TTexture>()->LoadTextureFromFile("resources/images/crt_monitor_frame.png"))
		{
			Logo->GetComponentAsPtr<TTransformable>()->SetPosition(664.f, 37.f);
			TManager::GetInstance().AddComponent<TGraphicEntity>(std::move(Logo));
		}

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
		//nne::TManager::GetInstance().Draw();

		// Render the GUI
		mAppGui.Draw();

		// Display the back buffered window
		TGuiWindow::GetInstance().display();
	}

}
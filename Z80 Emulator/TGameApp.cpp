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
		CacheManager.AddResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_effect.png"), "monitor_effect"));
		CacheManager.AddResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_shadow.png"), "monitor_shadow"));
		CacheManager.AddResource(nne::TResourceLoader<sf::Font>(nne::SFPathLoader<sf::Font>("resources/fonts/font.ttf"), "font_1"));

		// Create a Z80 and RAM entity
		mLogicEntity.AddComponent<nne::tmodules::TZ80>();
		mLogicEntity.AddComponent<nne::tmodules::TRam>();
		mLogicEntity.InitComponents();

		// Get the Z80 and the ram entity
		auto& Z80 = mLogicEntity.GetComponentAsPtr<nne::tmodules::TZ80>();
		auto& Ram = mLogicEntity.GetComponentAsPtr<nne::tmodules::TRam>();

		Z80->ConnectRam(Ram);
		if (!Z80->LoadProgram("resources/programs/DJ.A01"))
		{
			std::cout << "Error! Could not open the file" << std::endl;

			// Something went bad :(
			return 1;
		}

		// Create a temp value the z80 and the ram
		auto& Z80Chip = TFactory::MakeChip(Z80.get());
		auto& RamChip = TFactory::MakeChip(Ram.get());
		auto& ConductiveRack = TFactory::MakeConductiveTrack();

		Z80Chip->GetComponentAsPtr<TTransformable>()->SetScale(.5f, .5f);
		Z80Chip->GetComponentAsPtr<TTransformable>()->SetPosition(500.f, 300.f);

		RamChip->GetComponentAsPtr<TTransformable>()->SetScale(.5f, .5f);
		RamChip->GetComponentAsPtr<TTransformable>()->SetPosition(1000.f, 350.f);

		auto& Manager = TManager::GetInstance();
		Manager.AddComponent<TGraphicEntity>(std::move(Z80Chip));
		Manager.AddComponent<TGraphicEntity>(std::move(RamChip));
		Manager.AddComponent<TGraphicEntity>(std::move(ConductiveRack));

		// Create the window
		TGuiWindow::GetInstance().create(sf::VideoMode(1600, 900), mAppName.c_str(), sf::Style::Default);

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
			mAppGui.ProcessEvents(mAppEvent);

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
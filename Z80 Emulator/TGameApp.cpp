#include "TGameApp.h"

namespace nne
{

	TGameApp::TGameApp() :
		mAppName(PROGRAM_NAME)
	{
	}

	bool TGameApp::init()
	{
		// Load the resources
		auto& CacheManager = TCacheManager::getInstance();
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_effect.png"), "monitor_effect"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_shadow.png"), "monitor_shadow"));
		CacheManager.addResource(nne::TResourceLoader<sf::Font>(nne::SFPathLoader<sf::Font>("resources/fonts/font.ttf"), "font_1"));

		// Create a Z80 and RAM entity
		mLogicEntity.addComponent<nne::tmodules::TZ80>();
		mLogicEntity.addComponent<nne::tmodules::TRam>();
		mLogicEntity.initComponents();

		// Get the Z80 and the ram entity
		auto& Z80 = mLogicEntity.getComponentAsPtr<nne::tmodules::TZ80>();
		auto& Ram = mLogicEntity.getComponentAsPtr<nne::tmodules::TRam>();

		Z80->connectRam(Ram);
		if (!Z80->loadProgram("resources/programs/DJ.A01"))
		{
			std::cout << "Error! Could not open the file" << std::endl;

			// Something went bad :(
			return 1;
		}

		// Create a temp value the z80 and the ram
		auto& Z80Chip = TFactory::makeChip(Z80.get());
		auto& RamChip = TFactory::makeChip(Ram.get());
		auto& ConductiveRack = TFactory::makeConductiveTrack();

		//Z80Chip->getComponentAsPtr<TTransformable>()->SetScale(.5f, .5f);
		Z80Chip->getComponentAsPtr<TTransformable>()->setPosition(250.f, 100.f);

		//RamChip->getComponentAsPtr<TTransformable>()->SetScale(.5f, .5f);
		RamChip->getComponentAsPtr<TTransformable>()->setPosition(900.f, 100.f);

		auto& Manager = TManager::getInstance();
		Manager.addComponent<TGraphicEntity>(std::move(Z80Chip));
		Manager.addComponent<TGraphicEntity>(std::move(RamChip));
		//Manager.addComponent<TGraphicEntity>(std::move(ConductiveRack));

		// Create the window
		TGuiWindow::getInstance().create(sf::VideoMode(1600, 900), mAppName.c_str(), sf::Style::Default);

		// Initialize the GUI
		mAppGui.setup();

		return true;
	}

	bool TGameApp::loadConfiguration(const std::string& ConfigFile)
	{
		return true;
	}

	int TGameApp::run()
	{
		mAppClock.restart();

		while (TGuiWindow::getInstance().isOpen())
		{
			sf::Time ElapsedTime = mAppClock.restart();

			eventLoop();

			refresh(ElapsedTime);

			update(ElapsedTime);

			draw();
		}

		return 0;
	}

	void TGameApp::eventLoop()
	{
		while (TGuiWindow::getInstance().pollEvent(mAppEvent))
		{
			mAppGui.processEvents(mAppEvent);

			if (mAppEvent.type == sf::Event::Closed)
				TGuiWindow::getInstance().close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				TGuiWindow::getInstance().close();
		}
	}

	void TGameApp::refresh(sf::Time ElapsedTime)
	{
		mAppGui.refresh(ElapsedTime);

		nne::TManager::getInstance().refresh(ElapsedTime);
	}

	void TGameApp::update(sf::Time ElapsedTime)
	{
		mAppGui.update(ElapsedTime);

		nne::TManager::getInstance().update(ElapsedTime);
	}

	void TGameApp::draw()
	{
		// Clear the back buffered window
		TGuiWindow::getInstance().clear();
		
		// Render all the entity in the the entity manager
		nne::TManager::getInstance().draw();

		// Render the GUI
		mAppGui.draw();
					
		// Display the back buffered window
		TGuiWindow::getInstance().display();
	}

}
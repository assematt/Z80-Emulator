#include "TGameApp.h"

namespace nne
{

	TGameApp::TGameApp() :
		mAppName(PROGRAM_NAME),
		mAppWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode(1600, 900), mAppName.c_str(), sf::Style::Default))
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

		Z80Chip->getComponentAsPtr<TDrawableComponent>()->setPosition(250.f, 100.f);
		RamChip->getComponentAsPtr<TDrawableComponent>()->setPosition(900.f, 100.f);

		mGraphicEntity.addComponent<TGraphicEntity>(std::move(Z80Chip));
		mGraphicEntity.addComponent<TGraphicEntity>(std::move(RamChip));
		mGraphicEntity.initComponents();

		// Initialize the GUI
		mAppGui.setup(mAppWindow);

		return true;
	}

	bool TGameApp::loadConfiguration(const std::string& ConfigFile)
	{
		return true;
	}

	int TGameApp::run()
	{
		mAppClock.restart();
		
		while (mAppWindow->isOpen())
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
		while (mAppWindow->pollEvent(mAppEvent))
		{
			mAppGui.processEvents(mAppEvent);

			if (mAppEvent.type == sf::Event::Closed)
				mAppWindow->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mAppWindow->close();
		}
	}

	void TGameApp::refresh(sf::Time ElapsedTime)
	{
		mAppGui.refresh(ElapsedTime);

		mGraphicEntity.refresh(ElapsedTime);
	}

	void TGameApp::update(sf::Time ElapsedTime)
	{
		mAppGui.update(ElapsedTime);

		mGraphicEntity.update(ElapsedTime);
	}

	void TGameApp::draw()
	{
		// Clear the back buffered window
		mAppWindow->clear();

		// Render all the entity in the the entity manager
		//mGraphicEntity.draw(*mAppWindow);

		// Render the GUI
		mAppGui.draw();

		// Display the back buffered window
		mAppWindow->display();
	}

}
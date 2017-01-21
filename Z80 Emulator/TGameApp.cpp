#include "TGameApp.h"
#include "TMainMenuScene.h"
#include "TNewGameScene.h"


namespace nne
{

	TGameApp::TGameApp() :
		mAppName(PROGRAM_NAME),
		mAppWindow(sf::VideoMode(1600, 900), mAppName.c_str(), sf::Style::Default)
	{
		//mAppWindow.setFramerateLimit(1);
		//mAppWindow.setFramerateLimit(60);
	}

	bool TGameApp::init()
	{
		mSceneManager.setup(mAppWindow);

		// Load the resources
		auto& CacheManager = TCacheManager::getInstance();
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_effect.png"), "monitor_effect"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/crt_monitor_effect_2.png"), "monitor_effect_2"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_shadow.png"), "monitor_shadow"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/test_Image.png"), "test_image"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/grid_pattern.png"), "grid_pattern"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/ground.png"), "ground"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/power.png"), "power"));

		// Image BTN
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/bus_btn.png"), "bus_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/chip_btn.png"), "chip_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/track_btn.png"), "track_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/cpu_btn.png"), "cpu_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/ram_btn.png"), "ram_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/nand_btn.png"), "nand_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/led_btn.png"), "led_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/ground_btn.png"), "ground_btn"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/icons/power_btn.png"), "power_btn"));

		// Dialog exit
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/exit_dialog.png"), "exit_dialog"));

		CacheManager.addResource(nne::TResourceLoader<sf::Font>(nne::SFPathLoader<sf::Font>("resources/fonts/font.ttf"), "font_1"));

		mSceneManager.addScene(std::unique_ptr<IScene>(new TMainMenuScene()), "main_scene");		
		mSceneManager.addScene(std::unique_ptr<IScene>(new TNewGameScene()), "new_game_scene");
		mSceneManager.initScenes();

		return true;
	}

	bool TGameApp::loadConfiguration(const std::string& ConfigFile)
	{
		return true;
	}

	int TGameApp::run()
	{
		mAppClock.restart();

		// Run the app and 
		while (mAppWindow.isOpen())
			mSceneManager.run(mAppClock.restart());

		return 0;
	}

}
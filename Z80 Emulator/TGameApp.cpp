#include "TGameApp.h"

namespace nne
{

	TGameApp::TGameApp() :
		mAppName(PROGRAM_NAME),
		mAppWindow(sf::VideoMode(1600, 900), mAppName.c_str(), sf::Style::Default)
	{
	}

	bool TGameApp::init()
	{
		mSceneManager.setup(mAppWindow);

		// Load the resources
		auto& CacheManager = TCacheManager::getInstance();
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_effect.png"), "monitor_effect"));
		CacheManager.addResource(nne::TResourceLoader<sf::Texture>(nne::SFPathLoader<sf::Texture>("resources/images/new_crt_monitor_shadow.png"), "monitor_shadow"));
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
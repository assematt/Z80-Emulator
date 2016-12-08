#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <memory>
#include <string>

#include "TManager.h"
#include "TLoaders.h"
#include "TCacheManager.h"
#include "TFactory.h"
#include "TSceneManager.h"

namespace nne
{
	class TGameApp
	{
	public:
		using TGameWindow = sf::RenderWindow;
		using TGameWindowPtr = std::shared_ptr<TGameWindow>;

		TGameApp();
		TGameApp(const TGameApp& Copy) = delete;
		TGameApp(TGameApp&& Move) = delete;

		bool init();

		bool loadConfiguration(const std::string& ConfigFile);

		int run();

	private:
 		sf::Clock			mAppClock;
 		std::string			mAppName;
		TSceneManager		mSceneManager;
		sf::RenderWindow	mAppWindow;
	};
}
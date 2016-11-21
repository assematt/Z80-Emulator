#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <memory>
#include <string>

#include "TManager.h"
#include "TLoaders.h"
#include "TCacheManager.h"
#include "TGuiManager.h"
#include "TFactory.h"

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
		void eventLoop();

		void refresh(sf::Time ElapsedTime);

		void update(sf::Time ElapsedTime);

		void draw();

	private:
 		sf::Clock			mAppClock;
		sf::Event			mAppEvent;
 		std::string			mAppName;
		TGameWindowPtr		mAppWindow;
		tgui::TGuiManager	mAppGui;

		TManager mLogicEntity;
		TManager mGraphicEntity;
	};
}
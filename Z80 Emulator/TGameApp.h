#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

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

		bool Init();

		bool LoadConfiguration(const std::string& ConfigFile);

		int Run();

	private:
		void EventLoop();

		void Refresh(sf::Time ElapsedTime);

		void Update(sf::Time ElapsedTime);

		void Draw();
		
	private:
		std::string mAppName;
		sf::Event	mAppEvent;
		sf::Clock	mAppClock;
		tgui::TGuiManager mAppGui;
	};
}
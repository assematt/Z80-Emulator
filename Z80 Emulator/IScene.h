#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <limits>
#include <memory>

namespace nne
{
	class TSceneManager;

	namespace tgui
	{
		class TGuiManager;
	}

	struct IScene
	{
		using ID = std::size_t;
		using Ptr = std::unique_ptr<IScene>;

		const ID Same = std::numeric_limits<ID>::max();
		const ID NotFound = std::numeric_limits<ID>::max() - 1;

		IScene();

		virtual void init() = 0;

		ID& run(const sf::Time& ElapsedTime);

	protected:
		virtual ID eventLoop() = 0;

		virtual void refresh(sf::Time ElapsedTime) = 0;

		virtual void update(sf::Time ElapsedTime) = 0;

		virtual void draw() = 0;

	protected:
		ID					mID;
		sf::Event			mAppEvent;
		TSceneManager*		mParent;
		sf::RenderWindow*	mRenderSurface;

		friend class TSceneManager;
	};
}
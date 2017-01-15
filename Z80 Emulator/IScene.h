#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <limits>
#include <memory>

#include "TRenderSurface.h"

namespace nne
{
	class TSceneManager;

	namespace tgui
	{
		class TGuiManager;
	}

	class IScene
	{
	public:
		using ID = std::size_t;
		using Ptr = std::unique_ptr<IScene>;

		const static ID Same = std::numeric_limits<ID>::max();
		const static ID NotFound = std::numeric_limits<ID>::max() - 1;
		const static ID Exit = std::numeric_limits<ID>::max() - 2;

		IScene();

		virtual void init() = 0;

		// Set/get the size of the scene (basically it's the size of the render window)
		void setSize(const sf::Vector2u& Size);
		const sf::Vector2u getSize() const;

		// Get the current utilized view
		const TRenderSurface& getRenderSurface() const;

		const sf::RenderWindow& getRenderWindow() const;
		

		ID& run(const sf::Time& ElapsedTimem);

	protected:
		virtual ID eventLoop() = 0;

		virtual void refresh(sf::Time ElapsedTime) = 0;

		virtual void update(sf::Time ElapsedTime) = 0;

		virtual void draw() = 0;

	protected:
		ID					mID;
		sf::Event			mAppEvent;
		sf::Vector2u		mSize;
		TSceneManager*		mParent;
		TRenderSurface		mRenderSurface;
		sf::RenderWindow*	mRenderWindow;

		friend class TSceneManager;
	};
}
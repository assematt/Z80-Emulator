#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
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

		/// Set/get the size of the scene (basically it's the size of the render window)
		void setSize(const sf::Vector2u& Size);
		const sf::Vector2u getSize() const;

		/// Get the used sf::RenderWindow
		const sf::RenderWindow& getRenderWindow() const;
		
		sf::Vector2f getMousePosition() const;
		sf::Vector2f getMousePosition(const sf::View& View) const;

		ID& run(const sf::Time& ElapsedTimem);

	protected:
		virtual ID eventLoop() = 0;

		virtual void refresh(const sf::Time& ElapsedTime) = 0;

		virtual void update(const sf::Time& ElapsedTime) = 0;

		virtual void draw() = 0;

	protected:
		ID					mID;
		sf::Event			mAppEvent;
		sf::Vector2u		mSize;
		TSceneManager*		mParent;
		sf::RenderWindow*	mRenderWindow;

		friend class TSceneManager;
	};
}
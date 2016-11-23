#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <vector>

#include "IScreenView.h"

namespace nne
{
	class TSceneManager;

	namespace tgui
	{
		enum class TReferencePoint
		{
			LEFT_TOP,
			CENTER_TOP,
			RIGHT_TOP,

			LEFT_CENTER,
			CENTER,
			RIGHT_CENTER,

			LEFT_BOTTOM,
			CENTER_BOTTOM,
			RIGHT_BOTTOM,
		};

		class TGuiManager
		{
		public:
			TGuiManager();
			virtual ~TGuiManager() = default;

			void setup(sf::RenderWindow& RenderTarget);

			void processEvents(sf::Event& EventToProcess);

			void addMenu(IScreenView::UniquePtr& Menu);

			void initMenus(sf::RenderWindow& RenderWindow, TSceneManager& SceneManager);

			void changeMenu(std::size_t NextMenu);

			void refresh(const sf::Time& ElapsedTime);

			void update(const sf::Time& ElapsedTime);

			void draw();

			/// Function to access a reference point position
			const sf::Vector2f getReferencePointPosition(TReferencePoint RefPoint = TReferencePoint::CENTER);

			/// Get a ref to the window in which we are rendering the GUI
			sf::RenderWindow& getRenderingWindow() const;

			TSceneManager* getSceneManager();

		private:
			bool								mIsRunning;
			std::size_t							mCurrentViewIndex;
			std::size_t							mPreviousViewIndex;
			TSceneManager*						mSceneManager;
			sf::RenderWindow*					mRenderWindow;
			std::vector<IScreenView::UniquePtr> mScreens;
		};
	}
}
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <memory>

#include "IScene.h"
#include "IDGenerator.h"
#include "ILoadingScreen.h"

namespace nne
{
	class TSceneManager
	{
	public:
		TSceneManager();

		void setup(sf::RenderWindow& RenderTarget);

		void addScene(std::unique_ptr<IScene>& Scene, const std::string& SceneKey);

		IScene::Ptr& getScene(const IScene::ID& Scene);

		void initScenes();

		void changeScene(IScene::ID NewScene);

		void run(const sf::Time& ElapsedTime);

		sf::RenderWindow& getRenderWindow();

	private:
		IScene::ID					mSelectedScene;
		IScene::ID					mNextMenu;
		sf::RenderWindow*			mRenderWindow;
		std::vector<IScene::Ptr>	mSceneVector;
	};
}
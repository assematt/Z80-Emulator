#include "TSceneManager.h"

namespace nne
{

	TSceneManager::TSceneManager() :
		mSelectedScene(0),
		mNextMenu(mSelectedScene)
	{
	}

	void TSceneManager::setup(sf::RenderWindow& RenderTarget)
	{
		mRenderWindow = &RenderTarget;
	}

	void TSceneManager::addScene(std::unique_ptr<IScene>& Scene, const std::string& SceneKey)
	{
		Scene->mParent = this;
		Scene->mID = nne::idgenerator::GenerateByString::getUniqueID(SceneKey);
		Scene->mRenderSurface = mRenderWindow;

		mSceneVector.push_back(std::move(Scene));
	}
	
	nne::IScene::Ptr& TSceneManager::getScene(const IScene::ID& Scene)
	{
		std::size_t ScenePos = 0;
		std::size_t VectorSize = mSceneVector.size();

		while (mSceneVector[ScenePos]->mID != Scene && ++ScenePos < VectorSize);

		return mSceneVector[ScenePos];
	}

	void TSceneManager::initScenes()
	{
		for (auto& Scene : mSceneVector)
			Scene->init();
	}

	void TSceneManager::changeScene(IScene::ID NewScene)
	{
		mNextMenu = NewScene;
	}

	void TSceneManager::run(const sf::Time& ElapsedTime)
	{
		// Run the scene code

		mSceneVector[mSelectedScene]->run(ElapsedTime);

		mSelectedScene = mNextMenu;
	}

	sf::RenderWindow& TSceneManager::getRenderWindow()
	{
		return *mRenderWindow;
	}

}
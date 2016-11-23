#include "IScene.h"

namespace nne
{
	IScene::IScene() :
		mID(0),
		mParent(nullptr),
		mRenderSurface(nullptr)
	{
	}

	IScene::ID& IScene::run(const sf::Time& ElapsedTime)
	{
		IScene::ID SelectedID = eventLoop();

		refresh(ElapsedTime);

		update(ElapsedTime);

		draw();

		return SelectedID == Same ? mID : SelectedID;
	}

}
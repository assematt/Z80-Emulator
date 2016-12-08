#include "IScene.h"

namespace nne
{
	
	IScene::IScene() :
		mID(0),
		mParent(nullptr)
	{

	}

	void IScene::init()
	{

	}

	void IScene::setSize(const sf::Vector2u& Size)
	{
		mSize = Size;
	}

	const sf::Vector2u IScene::getSize() const
	{
		return mSize;
	}

	nne::IScene::ID& IScene::run(const sf::Time& ElapsedTime)
	{
		IScene::ID SelectedID = eventLoop();

		refresh(ElapsedTime);

		update(ElapsedTime);

		draw();

		return SelectedID == Same ? mID : SelectedID;
	}

}
#include "IScene.h"

#include <SFML/Window/Mouse.hpp>

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

	const sf::RenderWindow& IScene::getRenderWindow() const
	{
		return *mRenderWindow;
	}

	sf::Vector2f IScene::getMousePosition() const
	{
		return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mRenderWindow));
	}

	sf::Vector2f IScene::getMousePosition(const sf::View& View) const
	{
		return getMousePosition();
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
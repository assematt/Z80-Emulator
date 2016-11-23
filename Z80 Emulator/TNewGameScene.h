#pragma once

#include <SFML/Window/Event.hpp>

#include "IScene.h"
#include "TManager.h"
#include "TFactory.h"

namespace nne
{
	class TNewGameScene : public IScene
	{

	public:
		virtual void init() override;

	protected:
		virtual ID eventLoop() override;

		virtual void refresh(sf::Time ElapsedTime) override;

		virtual void update(sf::Time ElapsedTime) override;

		virtual void draw() override;

	private:
		sf::Event	mAppEvent;
		TManager	mLogicEntity;
		TManager	mGraphicEntity;
	};
}
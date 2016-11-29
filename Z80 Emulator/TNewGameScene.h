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
		/// Add a conductive track in the manager and logic board and set it as the current selected track
		void addConductiveTrack();

	private:
		sf::Event	mAppEvent;
		TManager	mLogicEntity;
		TManager	mGraphicEntity;
		std::size_t mTrackCounter;

		TLogicBoardComponent* mLogicBoard;
		TEntity::EntityPtr mTempChip;
		TEntity::EntityPtr mTempTrack;
	};
}
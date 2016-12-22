#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "IScene.h"
#include "TManager.h"
#include "TFactory.h"
#include "TGuiManager.h"
#include "TLogicBoardComponent.h"
#include "TGridComponent.h"

namespace nne
{
	class TNewGameScene : public IScene
	{
	public:

		enum class TInsertionMethod
		{
			CHIP,
			TRACK,
			BUS,
			NONE
		};

		TNewGameScene();

		virtual void init() override;

	protected:
		virtual ID eventLoop() override;

		void updateDebugInfo();

		virtual void refresh(sf::Time ElapsedTime) override;

		virtual void update(sf::Time ElapsedTime) override;

		virtual void draw() override;

	private:
		/// Add a conductive track in the manager and logic board and set it as the current selected track
		void addConductiveTrack();

		/// Convert the mouse coordinate from window coordinate to the sf::View coordinate
		sf::Vector2f convertMouseCoordinate(sf::Vector2i MouseCoordinate);

	private:
		sf::Event				mAppEvent;
		TManager				mLogicEntity;
		TManager				mGraphicEntity;
		std::size_t				mTrackCounter;
		sf::Uint32				mZoomSteps;
		TInsertionMethod		mInsertionMethod;
		tgui::TGuiManager		mGuiManager;
		TGridComponent*			mGridComponent;
		TLogicBoardComponent*	mLogicBoard;
		TEntity::EntityPtr		mTempChip;
		TEntity::EntityPtr		mTempTrack;
	};
}
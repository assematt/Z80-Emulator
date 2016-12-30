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
			WIRE,
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
		/// Add a wire in the manager and logic board and set it as the current selected wire
		void addWire();

		/// Add a bus in the manager and logic board and set it as the current selected bus
		void addBus();

		/// Convert the mouse coordinate from window coordinate to the sf::View coordinate
		sf::Vector2f convertMouseCoordinate(sf::Vector2i MouseCoordinate);

	private:
		sf::Event				mAppEvent;
		TManager				mLogicEntity;
		TManager				mGraphicEntity;
		sf::Uint32				mZoomSteps;
		TInsertionMethod		mInsertionMethod;
		tgui::TGuiManager		mGuiManager;
		TGridComponent*			mGridComponent;
		TLogicBoardComponent*	mLogicBoard;

		/// Variable to keep track of how many wires/bus/chips we have in the logic board
		std::size_t				mWireCounter;
		std::size_t				mBusCounter;

		/// Variable the old a shared_ptr to the last added wires/bus/chips
		TEntity::EntityPtr		mTempChip;
		TEntity::EntityPtr		mTempWire;
		TEntity::EntityPtr		mTempBus;

		/// Variable to establish if we are drawing from a bus to a chip or viceversa
		bool mDrawingFromBusToChip;
	};
}
#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "IScene.h"
#include "TManager.h"
#include "TFactory.h"
#include "TGuiManager.h"
#include "TRenderCanvas.h"
#include "TGridComponent.h"
#include "TLogicBoardComponent.h"
#include "TZ80Component.h"

namespace nne
{
	class TNewGameScene : public IScene
	{
	public:
		
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

		/// Add a chip in the manager and logic board 
		void addChip(const std::string& ChipToAdd);

		/// Handle all the mouse move event for the RenderSurface/LogicBoard
		void handleMouseMoveEvent(const sf::Vector2f& MousePos);

		/// Handle all the right mouse up event for the RenderSurface/LogicBoard
		void handleRightMouseUpEvent();

		/// Handle all the left mouse up event for the RenderSurface/LogicBoard
		void handleLeftMouseUpEvent(const sf::Vector2f& MousePos);

		/// Handle all the keyboard inputs for the RenderSurface/LogicBoard
		void handleKeyboardInputs(const sf::Keyboard::Key& KeyCode);

		/// Check for temporary object we are currently trying to place and eventually remove it if we are trying to place another object
		void removeTemporaryEntity();

		/// Return the formatted string with the debug z80 registers
		std::string formatZ80Registers(const tcomponents::TZ80Component& Z80);

		/// Return the formatted string with the debug z80 flags
		std::string formatZ80Flags(const tcomponents::TZ80Component& Z80);

	private:
		TManager				mGraphicEntity;
		sf::Event				mAppEvent;
		sf::Uint32				mZoomSteps;
		tgui::TGuiManager		mGuiManager;
		TGridComponent*			mGridComponent;
		tgui::TRenderCanvas*	mRenderCanvas;
		TLogicBoardComponent*	mLogicBoard;

		/// Variable to keep track of how many wires/bus/chips we have in the logic board
		std::size_t				mWireCounter;
		std::size_t				mChipCounter;
		std::size_t				mBusCounter;

		/// Variable the old a shared_ptr to the last added wires/bus/chips
		TEntity::EntityPtr		mTempChip;
		TEntity::EntityPtr		mTempWire;
		TEntity::EntityPtr		mTempBus;

		/// Variable to establish if we are drawing from a bus to a chip or viceversa
		bool mDrawingFromBusToChip;
	};
}
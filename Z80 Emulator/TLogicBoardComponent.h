#pragma once

#include <memory>
#include <vector>

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include "TDrawableComponent.h"
#include "TChipComponent.h"
#include "TWireComponent.h"
#include "TBusComponent.h"
#include INCLUDE_ENTITY_CLASS

namespace nne
{
	class TBoard;

	class TLogicBoardComponent : BASE_COMPONENT_CLASS
	{
	public:

		// Default constructor
		TLogicBoardComponent();

		virtual void update(REFRESH_UPDATE_PARAMETER) override;


		virtual void refresh(REFRESH_UPDATE_PARAMETER) override;


		virtual void init() override;

		/// Set the board
		void setBoard(TBoard& Board);

		/// Return the board
		TBoard& getBoard() const;

		/// Return true if we set up a board
		bool hasBoard() const;

	private:
		TBoard* mPlacedBoard;
	};

}
#pragma once

#include <memory>
#include <vector>

#include "IComponent.h"
#include "TDrawableComponent.h"
#include "TChipComponent.h"
#include "TWireComponent.h"
#include "TBusComponent.h"
#include "TEntity.h"

namespace nne
{
	class TBoard;

	class TLogicBoardComponent : public IComponent
	{
	public:

		// Default constructor
		TLogicBoardComponent();

		virtual void update(const sf::Time& ElapsedTime) override;


		virtual void refresh(const sf::Time& ElapsedTime) override;


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
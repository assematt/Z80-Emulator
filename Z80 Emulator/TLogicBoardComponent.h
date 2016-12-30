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

	class TLogicBoardComponent : public IComponent
	{
	public:

		TLogicBoardComponent();

		virtual void init() override;

		virtual void refresh(const sf::Time& ElapsedTime) override;

		virtual void update(const sf::Time& ElapsedTime) override;


		/// Function to place a component in the board
		void placeChip(TChipComponent* Component);
		void placeChip(TEntity* Entity);

		/// Function to place a wire in the board
		void placeWire(TWireComponent* Wire);
		void placeWire(TEntity* Entity);

		/// Function to place a wire in the board
		void placeBus(TBusComponent* Bus);
		void placeBus(TEntity* Entity);

		/// Function to set/get the currently selected component
		void setSelectedChip(TChipComponent* Chip);
		TChipComponent* getSelectedChip() const;
		TChipComponent* getFormerSelectedChip() const;
		void deselectChip(bool DisableFormerChipToo = false);

		/// Function to set/get the currently selected wire
		void setSelectedWire(TWireComponent* Wire);
		TWireComponent* getSelectedWire() const;
		TWireComponent* getFormerSelectedWire() const;
		void deselectWire(bool DisableFormerWireToo = false);

		/// Function to set/get the currently selected wire
		void setSelectedBus(TBusComponent* Bus);
		TBusComponent* getSelectedBus() const;
		TBusComponent* getFormerSelectedBus() const;
		void deselectBus(bool DisableFormerBusToo = false);

		/// Helper function to deselect everything
		void deselectEverything();

	private:
		TChipComponent*					mSelectedChip;
		TChipComponent*					mFormerSelectedChip;

		TWireComponent*					mSelectedWire;
		TWireComponent*					mFormerSelectedWire;

		TBusComponent*					mSelectedBus;
		TBusComponent*					mFormerSelectedBus;

		std::vector<TBusComponent*>		mBusVector;
		std::vector<TChipComponent*>	mComponentVector;
		std::vector<TWireComponent*>	mWireVector;
	};
}
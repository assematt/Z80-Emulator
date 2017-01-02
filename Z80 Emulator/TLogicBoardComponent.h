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

		/// Check if the chip we are trying to place is colliding with another chip already on the logic board
		bool checkCollisions(TChipComponent* Chip);

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

		/// get the chip vector
		const std::vector<TChipComponent*>& getChipVector() const;

		/// get the bus vector
		const std::vector<TBusComponent*>& getBusVector() const;

		/// get the wire vector
		const std::vector<TWireComponent*>& getWireVector() const;
		
	private:
		TChipComponent*					mSelectedChip;
		TChipComponent*					mFormerSelectedChip;

		TWireComponent*					mSelectedWire;
		TWireComponent*					mFormerSelectedWire;

		TBusComponent*					mSelectedBus;
		TBusComponent*					mFormerSelectedBus;

		std::vector<TBusComponent*>		mBusVector;
		std::vector<TChipComponent*>	mChipVector;
		std::vector<TWireComponent*>	mWireVector;
	};
}
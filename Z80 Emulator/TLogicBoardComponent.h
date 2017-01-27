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

		enum class TInsertionMethod
		{
			CHIP,
			WIRE,
			BUS,
			NONE
		};

		TLogicBoardComponent();

		virtual void init() override;

		virtual void refresh(const sf::Time& ElapsedTime) override;

		virtual void update(const sf::Time& ElapsedTime) override;

		/// function to save the current board
		bool saveBoard(const std::string& Path);

		/// Function to lead a file in the board
		bool loadBoard(const std::string& Path, TManager& EntityManager, IScene* Scene);

		/// Function to place a chip in the board
		void placeChip(TChipComponent* ChipToPlace);
		void placeChip(TEntity* Entity);
		
		/// Function to remove a chip from the board
		void removeChip(TChipComponent* ChipToRemove);
		void removeChip(TEntity* Entity);

		/// Function to place a wire in the board
		void placeWire(TWireComponent* Wire);
		void placeWire(TEntity* Entity);

		/// Function to remove a wire from the board
		void removeWire(TWireComponent* WireToRemove);
		void removeWire(TEntity* Entity);

		/// Function to place a wire in the board
		void placeBus(TBusComponent* Bus);
		void placeBus(TEntity* Entity);

		/// Function to remove a bus from the board
		void removeBus(TBusComponent* BusToRemove);
		void removeBus(TEntity* Entity);

		/// Set/Get insertion mode
		void setInsertionMethod(const TInsertionMethod& Method);
		const TInsertionMethod& getInsertionMethod() const;

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
		
		/// Template function for a fast delete of an element pointed by Index in Vector
		/// Done by taking the element to remove, swapping it with the last element in the vector
		/// And then popping back, this way we avoid vector shuffling of the elements from Index to Vector.size()
		template <class T>
		void fastDelete(T& Vector, const std::size_t& Index);
		
	private:
		std::string						mLastAddedChip;

		TBusComponent*					mSelectedBus;
		TBusComponent*					mFormerSelectedBus;

		TChipComponent*					mSelectedChip;
		TChipComponent*					mFormerSelectedChip;

		TWireComponent*					mSelectedWire;
		TWireComponent*					mFormerSelectedWire;

		TInsertionMethod				mInsertionMethod;

		std::vector<TBusComponent*>		mBusVector;
		std::vector<TChipComponent*>	mChipVector;
		std::vector<TWireComponent*>	mWireVector;
	};

	template <class T>
	void nne::TLogicBoardComponent::fastDelete(T& Vector, const std::size_t& Index)
	{
		std::swap(Vector.begin() + Index, Vector.end() - 1);
		Vector.pop_back();
	}

}
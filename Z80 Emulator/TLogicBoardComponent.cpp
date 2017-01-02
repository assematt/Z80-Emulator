#include "TLogicBoardComponent.h"

#include <SFML/Graphics.hpp>

#include "TSceneManager.h"
#include "TCacheManager.h"

namespace nne
{

	TLogicBoardComponent::TLogicBoardComponent() :
		mSelectedChip(nullptr),
		mFormerSelectedChip(nullptr),

		mFormerSelectedWire(nullptr),
		mSelectedWire(nullptr),

		mFormerSelectedBus(nullptr),
		mSelectedBus(nullptr)
	{
	}

	void TLogicBoardComponent::update(const sf::Time& ElapsedTime)
	{
	}

	void TLogicBoardComponent::refresh(const sf::Time& ElapsedTime)
	{
	}

	void TLogicBoardComponent::init()
	{
	}

	void TLogicBoardComponent::placeChip(TChipComponent* Component)
	{
		mChipVector.push_back(Component);
	}


	void TLogicBoardComponent::placeChip(TEntity* Entity)
	{
		// Add the logic-board component to the entity
		Entity->addComponent<TLogicBoardComponent>(this);

		placeChip(Entity->getComponentAsPtr<TChipComponent>());
	}

	void TLogicBoardComponent::placeWire(TWireComponent* Wire)
	{
		mWireVector.push_back(Wire);
	}

	void TLogicBoardComponent::placeWire(TEntity* Entity)
	{
		// Add the logic-board component to the entity
		Entity->addComponent<TLogicBoardComponent>(this);

		placeWire(Entity->getComponentAsPtr<TWireComponent>());
	}

	
	void TLogicBoardComponent::placeBus(TBusComponent* Bus)
	{
		mBusVector.push_back(Bus);
	}

	void TLogicBoardComponent::placeBus(TEntity* Entity)
	{
		// Add the logic-board component to the entity
		Entity->addComponent<TLogicBoardComponent>(this);

		placeBus(Entity->getComponentAsPtr<TBusComponent>());
	}

	bool TLogicBoardComponent::checkCollisions(TChipComponent* Chip)
	{
		bool CollisionFound = false;
		auto ChipsNumber = mChipVector.size();
		auto Index = 0u;

		while (Index < ChipsNumber && CollisionFound == false)
		{
			if (Chip != mChipVector[Index])
				CollisionFound = Chip->checkCollision(*mChipVector[Index]);

			++Index;
		}

		return CollisionFound;
	}

	void TLogicBoardComponent::setSelectedChip(TChipComponent* Chip)
	{
		// Check if is the first time we are assigning the selected chip, if yes also check if have selected a different chip
		if (mSelectedChip && mSelectedChip != Chip)
			mFormerSelectedChip = mSelectedChip;

		// Set the selected chip
		mSelectedChip = Chip;
	}

	TChipComponent* TLogicBoardComponent::getSelectedChip() const
	{
		return mSelectedChip;
	}

	TChipComponent* TLogicBoardComponent::getFormerSelectedChip() const
	{
		return mFormerSelectedChip;
	}

	void TLogicBoardComponent::deselectChip(bool DisableFormerChipToo /*= false*/)
	{
		mSelectedChip = nullptr;

		if (DisableFormerChipToo)
			mFormerSelectedChip = nullptr;
	}

	void TLogicBoardComponent::setSelectedWire(TWireComponent* Wire)
	{
		// Check if is the first time we are assigning the selected wire, if yes also check if have selected a different wire
		if (mSelectedWire && mSelectedWire != Wire)
			mFormerSelectedWire = mSelectedWire;

		// Set the selected wire
		mSelectedWire = Wire;
	}

	TWireComponent* TLogicBoardComponent::getSelectedWire() const
	{
		return mSelectedWire;
	}

	TWireComponent* TLogicBoardComponent::getFormerSelectedWire() const
	{
		return mFormerSelectedWire;
	}

	void TLogicBoardComponent::deselectWire(bool DisableFormerWireToo /*= false*/)
	{
		if (mSelectedWire)
		{
			mSelectedWire->setSelectedStatus(false);
			mSelectedWire = nullptr;
		}
		
		if (DisableFormerWireToo && mFormerSelectedWire)
		{
			mFormerSelectedWire->setSelectedStatus(false);
			mFormerSelectedWire = nullptr;
		}
	}

	void TLogicBoardComponent::setSelectedBus(TBusComponent* Bus)
	{
		// Check if is the first time we are assigning the selected bus, if yes also check if have selected a different bus
		if (mSelectedWire && mSelectedBus != Bus)
			mFormerSelectedBus = mSelectedBus;

		// Set the selected bus
		mSelectedBus = Bus;
	}

	nne::TBusComponent* TLogicBoardComponent::getSelectedBus() const
{
		return mSelectedBus;
	}

	nne::TBusComponent* TLogicBoardComponent::getFormerSelectedBus() const
{
		return mFormerSelectedBus;
	}

	void TLogicBoardComponent::deselectBus(bool DisableFormerBusToo /*= false*/)
	{
		if (mSelectedBus)
		{
			mSelectedBus->setSelectedStatus(false);
			mSelectedBus = nullptr;
		}		

		if (DisableFormerBusToo && mFormerSelectedBus)
		{
			mFormerSelectedBus->setSelectedStatus(false);
			mFormerSelectedBus = nullptr;
		}
	}	

	void TLogicBoardComponent::deselectEverything()
	{
		deselectBus(true);
		deselectChip(true);
		deselectWire(true);
	}

	const std::vector<TChipComponent*>& TLogicBoardComponent::getChipVector() const
	{
		return mChipVector;
	}

	const std::vector<TBusComponent*>& TLogicBoardComponent::getBusVector() const
	{
		return mBusVector;
	}

	const std::vector<TWireComponent*>& TLogicBoardComponent::getWireVector() const
	{
		return mWireVector;
	}

}
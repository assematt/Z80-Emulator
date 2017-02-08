#include "TChipComponent.h"

#include "TLogicBoardComponent.h"
#include "TPackageComponent.h"
#include "TWireComponent.h"
#include "TCacheManager.h"
#include "TSceneManager.h"
#include "TBoard.h"

#define DEBUG_ONCE TRUE

namespace nne
{
	TChipComponent::TChipComponent() :
		mIsPlaced(false),
		mIsValid(true)
	{
	}

	void TChipComponent::init()
	{
		// Cache the TDrawableComponenet
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();

		// Cache the TTextComponent
		mLabels = mParent->getComponentAsPtr<TTextComponent>();

		mLabels->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
		mLabels->setCharacterSize(13);
		mLabels->setFillColor({ 171,171,171 });

		// Set the pin parent name
		auto& PinList = mParent->getComponent<TPinComponent>().getPinList();

		mChipName = "chip_" + std::to_string(mParent->getEntityID());

		for (auto& Pin : PinList)
			Pin.setPinParent(mChipName);
	}

	void TChipComponent::update(const sf::Time& ElapsedTime)
	{			
		// Only update the chip if we haven't placed it yet
		if (mIsPlaced)
			return;

		mIsValid ? mDrawableComponent->setColor({ 4u, 85u, 6u, 175u }) : mDrawableComponent->setColor({ 84u, 4u, 4u, 175u });
	}

	void TChipComponent::refresh(const sf::Time& ElapsedTime)
	{
		
	}

	void TChipComponent::setPlacedStatus(const bool& IsPlaced /*= true*/)
	{
		mIsPlaced = IsPlaced;

		if (mIsPlaced)
			mIsValid = true;
	}

	const bool& TChipComponent::isPlaced() const
	{
		return mIsPlaced;
	}

	void TChipComponent::setChipName(const std::string& Name)
	{
		mChipName = Name;

		// Update the pin parent name
		auto& PinList = mParent->getComponent<TPinComponent>().getPinList();

		// Update the pin parent name
		for (auto& Pin : PinList)
			Pin.setPinParent(mChipName);
	}

	const std::string& TChipComponent::getName() const
	{
		return mChipName;
	}

	sf::FloatRect TChipComponent::getLocalBound() const
	{
		auto& Position = mParent->getComponent<TDrawableComponent>().getPosition();
		auto& Size = mParent->getComponent<TDrawableComponent>().getVertexArray()[2].position;	

		return{ Position, Size };
	}

	sf::FloatRect TChipComponent::getGlobalBound() const
	{
		return mParent->getComponent<TDrawableComponent>().getTransform().transformRect(getLocalBound());
	}

	bool TChipComponent::checkCollision(const TChipComponent& Chip)
	{
		auto ThisBound = getLocalBound();
		auto OtherBound = Chip.getLocalBound();

		// Check if the 2 bounds intersect with each-other
		mIsValid = !ThisBound.intersects(OtherBound);

		return mIsValid;
	}

	const bool& TChipComponent::isValid() const
	{
		return mIsValid;
	}

	void TChipComponent::deselectPin()
	{
		mParent->getComponent<TPinComponent>().deselectPin();
	}
	
	const nne::tcomponents::TPin& TChipComponent::getSelectedPin() const
	{		
		return mParent->getComponent<TPinComponent>().getSelectedPin();
	}

	nne::tcomponents::TPin& TChipComponent::getSelectedPin()
	{
		return mParent->getComponent<TPinComponent>().getSelectedPin();
	}

	const nne::tcomponents::TPin& TChipComponent::getHoverPin() const
	{
		return mParent->getComponent<TPinComponent>().getHoverPin();
	}

}
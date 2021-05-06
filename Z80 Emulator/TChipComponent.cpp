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
#if ENTITY_SYSTEM == NNE
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();

		// Cache the TTextComponent
		mLabels = mParent->getComponentAsPtr<TTextComponent>();
#else
		mDrawableComponent = &(*mParent->getComponent<TDrawableComponent>());

		// Cache the TTextComponent
		mLabels = &(*mParent->getComponent<TTextComponent>());
#endif

		mLabels->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
		mLabels->setCharacterSize(13);
		mLabels->setFillColor({ 171,171,171 });

		// Set the pin parent name
#if ENTITY_SYSTEM == NNE
		auto& PinList = mParent->getComponent<TPinComponent>().getPinList();

		mChipName = "chip_" + std::to_string(mParent->getEntityID());
#else
		auto& PinList = mParent->getComponent<TPinComponent>()->getPinList();

		mChipName = "chip_" + std::to_string(mParent->getID());
#endif
		for (auto& Pin : PinList)
			Pin.setPinParent(mChipName);
	}

	void TChipComponent::update(REFRESH_UPDATE_PARAMETER)
	{			
		// Only update the chip if we haven't placed it yet
		if (mIsPlaced)
			return;

		mIsValid ? mDrawableComponent->setColor({ 4u, 85u, 6u, 175u }) : mDrawableComponent->setColor({ 84u, 4u, 4u, 175u });
	}

	void TChipComponent::refresh(REFRESH_UPDATE_PARAMETER)
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
#if ENTITY_SYSTEM == NNE
		auto& PinList = mParent->getComponent<TPinComponent>().getPinList();
#else
		auto& PinList = mParent->getComponent<TPinComponent>()->getPinList();
#endif

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
#if ENTITY_SYSTEM == NNE
		auto& Position = mParent->getComponent<TDrawableComponent>().getPosition();
		auto& Size = mParent->getComponent<TDrawableComponent>().getVertexArray()[2].position;	
#else
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
		auto& Position = DrawableComponent->getPosition();
		auto& Size = DrawableComponent->getVertexArray()[2].position;
#endif

		return{ Position, Size };
	}

	sf::FloatRect TChipComponent::getGlobalBound() const
	{
#if ENTITY_SYSTEM == NNE
		return mParent->getComponent<TDrawableComponent>().getTransform().transformRect(getLocalBound());
#else
		return mParent->getComponent<TDrawableComponent>()->getTransform().transformRect(getLocalBound());
#endif
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
#if ENTITY_SYSTEM == NNE
		mParent->getComponent<TPinComponent>().deselectPin();
#else
		mParent->getComponent<TPinComponent>()->deselectPin();
#endif
	}
	
	const nne::tcomponents::TPin& TChipComponent::getSelectedPin() const
	{		
#if ENTITY_SYSTEM == NNE
		return mParent->getComponent<TPinComponent>().getSelectedPin();
#else
		return mParent->getComponent<TPinComponent>()->getSelectedPin();
#endif
	}

	nne::tcomponents::TPin& TChipComponent::getSelectedPin()
	{
#if ENTITY_SYSTEM == NNE
		return mParent->getComponent<TPinComponent>().getSelectedPin();
#else
		return mParent->getComponent<TPinComponent>()->getSelectedPin();
#endif
	}

	const nne::tcomponents::TPin& TChipComponent::getHoverPin() const
	{
#if ENTITY_SYSTEM == NNE
		return mParent->getComponent<TPinComponent>().getHoverPin();
#else
		return mParent->getComponent<TPinComponent>()->getHoverPin();
#endif
	}

}
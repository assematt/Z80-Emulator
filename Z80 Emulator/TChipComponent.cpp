#include "TChipComponent.h"

#include "TLogicBoardComponent.h"
#include "TLedComponent.h"
#include "TCacheManager.h"
#include "TSceneManager.h"

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
	}

	void TChipComponent::update(const sf::Time& ElapsedTime)
	{			
		// Only update the chip if we haven't placed it yet
		if (!mIsPlaced)
		{
			mIsValid ? mDrawableComponent->setColor({ 4u, 85u, 6u, 175u }) : mDrawableComponent->setColor({ 84u, 4u, 4u, 175u });
		}
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

	const std::size_t& TChipComponent::getSelectedPinNumber() const
	{
		return mParent->getComponent<TPinComponent>().getSelectedPinNumber();
	}

	const nne::tcomponents::TPin& TChipComponent::getSelectedPin() const
	{		
		return mParent->getComponent<TPinComponent>().getSelectedPin();
	}

	nne::tcomponents::TPin& TChipComponent::getSelectedPin()
	{
		return mParent->getComponent<TPinComponent>().getSelectedPin();
	}
	
}
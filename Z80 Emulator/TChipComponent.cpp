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

// 		if (!mParent->hasComponent<TLedComponent>())
// 			renderDipChip();
// 		else
// 			renderLed();
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
		mParent->getComponent<tcomponents::TPinComponent>().deselectPin();
	}

	const std::size_t& TChipComponent::getSelectedPinNumber() const
	{
		return mParent->getComponent<tcomponents::TPinComponent>().getSelectedPinNumber();
	}

	const nne::tcomponents::TPin& TChipComponent::getSelectedPin() const
	{		
		return mParent->getComponent<tcomponents::TPinComponent>().getSelectedPin();
	}

	nne::tcomponents::TPin& TChipComponent::getSelectedPin()
	{
		return mParent->getComponent<tcomponents::TPinComponent>().getSelectedPin();
	}

	void TChipComponent::renderDipChip()
	{
		/*// Get a ref to the PIN component
		auto& PinComponent = mParent->getComponent<tcomponents::TPinComponent>();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		// Set the chip's base properties
		mDrawableComponent->setSize({ 185, (9 * NumberOfPins / 2 + 14 * (NumberOfPins / 2 - 1)) + 38 });

		mChipSize = mDrawableComponent->getSize();

		// Set the chip color
		mDrawableComponent->setColor({ 30, 30, 30 });

		// Define pin size
		sf::Vector2f PinSize = { 15.f, 9.f };

		// Get the chip position
		sf::Vector2f ChipPosition = mDrawableComponent->getPosition();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = mDrawableComponent->getVertexArray();

		std::string ChipTotalString = "";
		
		// Set the chip's pins properties
		for (std::size_t PinCounter = 0; PinCounter < NumberOfPins; ++PinCounter)
		{
			float LabelOffsetX = PinCounter < NumberOfPins / 2 ? 22 : -23.f;

			sf::Vector2f PinPosition;
			if (PinCounter < NumberOfPins / 2)
				PinPosition = { -PinSize.x, 23.f * PinCounter + 19.f };
			else
				PinPosition = { static_cast<float>(mChipSize.x), 23.f * (NumberOfPins - PinCounter) - 4.f };

			// Create a pin and put the info in the main vertex array
			createPin(PinPosition + ChipPosition, PinSize, PinColorNormal, Vertices);
			
			// Create the pin label			
			auto& PinName = PinComponent.getPin(PinCounter + 1).mPinName; //PinComponent[PinCounter].mPinName; //
			ChipTotalString += PinName + "  ";
			mLabels->setString(ChipTotalString);
			mLabels->setCharacterPosition(PinName + " ", { LabelOffsetX + PinPosition.x, PinPosition.y - 3.f });
		}*/
	}

	void TChipComponent::renderLed()
	{
		/*// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = mDrawableComponent->getVertexArray();

		// Define pin size
		sf::Vector2f PinSize = { 10.f, 9.f };

		// Get the size of the texture
		auto LedBound = mDrawableComponent->getLocalBounds();

		// Create the anode PIN
		createPin({ -PinSize.x, LedBound.height / 2.f - PinSize.y / 2.f }, PinSize, PinColorNormal, Vertices);

		// Create the cathode PIN
		createPin({ LedBound.width, LedBound.height / 2.f - PinSize.y / 2.f }, PinSize, PinColorNormal, Vertices);*/
	}


}
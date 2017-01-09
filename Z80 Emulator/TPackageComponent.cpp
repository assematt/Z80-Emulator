#include "TPackageComponent.h"

#include "TChipComponent.h"
#include "TDrawableComponent.h"

namespace nne
{

	TPackageComponent::TPackageComponent()
	{

	}

	void TPackageComponent::update(const sf::Time& ElapsedTime)
	{
		// 
		auto& IsPlaced = mParent->getComponent<TChipComponent>().isPlaced();

		// Update the LED color only if the component it's placed
		if (IsPlaced)
		{
			mParent->getComponent<TDrawableComponent>().setColor({ 30u, 30u, 30u, 255u });
		}
	}

	void TPackageComponent::refresh(const sf::Time& ElapsedTime)
	{

	}

	void TPackageComponent::init()
	{
		renderDipChip();
	}

	void TPackageComponent::renderDipChip()
	{
		// Get a ref to the PIN, drawable and text component
		auto& PinComponent = mParent->getComponent<tcomponents::TPinComponent>();
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
		auto& Labels = mParent->getComponent<TTextComponent>();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		// Set the chip's base properties
		DrawableComponent.setSize({ 185, (9 * NumberOfPins / 2 + 14 * (NumberOfPins / 2 - 1)) + 38 });

		auto ChipSize = DrawableComponent.getSize();

		// Set the chip color
		DrawableComponent.setColor({ 30, 30, 30 });

		// Define pin size
		sf::Vector2f PinSize = { 15.f, 9.f };

		// Get the chip position
		sf::Vector2f ChipPosition = DrawableComponent.getPosition();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = DrawableComponent.getVertexArray();

		std::string ChipTotalString = "";

		// Set the chip's pins properties
		for (std::size_t PinCounter = 0; PinCounter < NumberOfPins; ++PinCounter)
		{
			float LabelOffsetX = PinCounter < NumberOfPins / 2 ? 22 : -23.f;

			sf::Vector2f PinPosition;
			if (PinCounter < NumberOfPins / 2)
				PinPosition = { -PinSize.x, 23.f * PinCounter + 19.f };
			else
				PinPosition = { static_cast<float>(ChipSize.x), 23.f * (NumberOfPins - PinCounter) - 4.f };

			// Create a pin and put the info in the main vertex array
			PinComponent.createPin(PinPosition + ChipPosition, PinSize, Vertices);

			// Create the pin label			
			auto& PinName = PinComponent.getPin(PinCounter + 1).mPinName; //PinComponent[PinCounter].mPinName; //
			ChipTotalString += PinName + "  ";
			Labels.setString(ChipTotalString);
			Labels.setCharacterPosition(PinName + " ", { LabelOffsetX + PinPosition.x, PinPosition.y - 3.f });
		}
	}

}
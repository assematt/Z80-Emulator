#include "TPackageComponent.h"

#include "TChipComponent.h"
#include "TDrawableComponent.h"

namespace nne
{

	TPackageComponent::TPackageComponent() :
		mPackageColor({ 30u, 30u, 30u })
	{

	}

	void TPackageComponent::update(const sf::Time& ElapsedTime)
	{
		// Update the package color only if the component it's placed
		if (mParent->getComponent<TChipComponent>().isPlaced())
			mParent->getComponent<TDrawableComponent>().setColor(mPackageColor);
	}

	void TPackageComponent::refresh(const sf::Time& ElapsedTime)
	{
		// Check if the package it's powered on if the chip is placed
		if (mParent->getComponent<TChipComponent>().isPlaced())
			checkPowerStatus();
	}

	void TPackageComponent::init()
	{
		renderDipChip();
	}

	void TPackageComponent::renderDipChip()
	{
		// Get a ref to the PIN, drawable and text component
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
		auto& Labels = mParent->getComponent<TTextComponent>();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		// Set the chip's base properties
		DrawableComponent.setSize({ 185, (9 * NumberOfPins / 2 + 14 * (NumberOfPins / 2 - 1)) + 38 });

		auto ChipSize = static_cast<sf::Vector2f>(DrawableComponent.getSize());

		// Set the chip color
		DrawableComponent.setColor({ 30, 30, 30 });

		renderPins({ 15.f, 9.f }, DrawableComponent.getPosition(), ChipSize);

		renderPinLabels({ 15.f, 9.f }, DrawableComponent.getPosition(), ChipSize);

		renderChipName(mParent->getComponent<TChipComponent>().getName(), ChipSize);
	}

	void TPackageComponent::checkPowerStatus()
	{
		// Get a ref to the PIN Component
		auto& PinComponent = mParent->getComponent<TPinComponent>();

		// Get the anode and the cathode
		auto& VCC = PinComponent.getPin("VCC");
		auto& GND = PinComponent.getPin("GND");

		// If both pin are connected to something
		if (VCC.hasConnections() && GND.hasConnections())
		{
			// If the anode is positive and the cathode is 0
			mIsPowered = (VCC.getPinStatus() == TPin::HIGH && GND == TPin::LOW) ? true : false;
		}
	}

	void TPackageComponent::renderPins(const sf::Vector2f& PinSize, const sf::Vector2f& ChipPosition, const sf::Vector2f& ChipSize)
	{
		// Get a ref to the TPinComponent
		auto& PinComponent = mParent->getComponent<TPinComponent>();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		for (std::size_t PinCounter = 0; PinCounter < NumberOfPins; ++PinCounter)
		{
			sf::Vector2f PinPosition;
			if (PinCounter < NumberOfPins / 2)
				PinPosition = { -PinSize.x, 23.f * PinCounter + 19.f };
			else
				PinPosition = { static_cast<float>(ChipSize.x), 23.f * (NumberOfPins - PinCounter) - 4.f };

			PinComponent.createPin(PinPosition + ChipPosition, PinSize, Vertices);
		}
	}

	void TPackageComponent::renderPinLabels(const sf::Vector2f& PinSize, const sf::Vector2f& ChipPosition, const sf::Vector2f& ChipSize)
{
		// Get a ref to the TPinComponent
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& Labels = mParent->getComponent<TTextComponent>();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		// Chip total string
		std::string ChipTotalString = "";

		for (std::size_t PinCounter = 0; PinCounter < NumberOfPins; ++PinCounter)
		{
			float LabelOffsetX = PinCounter < NumberOfPins / 2 ? 22 : -14.f;

			sf::Vector2f LabelPosition;
			if (PinCounter < NumberOfPins / 2)
				LabelPosition = { -PinSize.x, 23.f * PinCounter + 19.f };
			else
				LabelPosition = { ChipSize.x, 23.f * (NumberOfPins - PinCounter) - 4.f };

			// Create the pin label			
			auto& PinName = PinComponent.getPin(PinCounter + 1).mPinName;

			// Compute the length of the Label
			float LabelLength = PinCounter < NumberOfPins / 2 ? 0.f : getStringLength(Labels, sf::String(PinName + " "));

			ChipTotalString += PinName + "  ";
			Labels.setString(ChipTotalString);
			Labels.setCharacterPosition(PinName + " ", { LabelOffsetX + LabelPosition.x - LabelLength, LabelPosition.y - 3.f });
		}
	}

	float TPackageComponent::getStringLength(const TTextComponent& Text, const sf::String& String)
	{
		float LineWidth = 0.f;

		// Add the char size to the line total
		for (auto Index = 0u; Index < String.getSize(); ++Index)
			LineWidth += Text.getFont()->getGlyph(String[Index], Text.getCharacterSize(), Text.getStyle() == TTextComponent::Bold).advance;

		return LineWidth;
	}

	const bool& TPackageComponent::isPoweredOn() const
	{
		return mIsPowered;
	}

	void TPackageComponent::updateChipName()
	{
		// 
		renderChipName(mParent->getComponent<TChipComponent>().getName(), static_cast<sf::Vector2f>(mParent->getComponent<TDrawableComponent>().getSize()));
	}

	void TPackageComponent::renderChipName(const std::string& ChipName, const sf::Vector2f& ChipSize)
	{
		// Get the chip labels
		auto& Labels = mParent->getComponent<TTextComponent>();

		// Get the std::string that holds all the character in TTextComponent
		auto OldString = Labels.getString().toAnsiString();

		// Remove the old part with the chip name from that list
		auto& OldStringWithoutName = OldString.substr(0, OldString.find_last_of(" "));

		// Get the length 
		auto ChipNameLength = getStringLength(Labels, ChipName);

		// Compute where the chip name label should be positioned
		//sf::Vector2f ChipNamePos = { std::roundf((ChipSize.x - 30.f) / 2.f - ChipNameLength / 2.f) - 22.f - ChipNameLength / 2.f, std::roundf(ChipSize.y / 2.f) };
		sf::Vector2f ChipNamePos = { 50.f, std::roundf(ChipSize.y / 2.f) };

		Labels.setString(OldStringWithoutName + ChipName);
		Labels.setCharacterPosition(ChipName, ChipNamePos);
	}

}
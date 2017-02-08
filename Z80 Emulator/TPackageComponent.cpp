#include "TPackageComponent.h"


#include <Windows.h>

#include "TBoard.h"
#include "TCacheManager.h"
#include "TChipComponent.h"
#include "TEventComponent.h"
#include "TPowerComponent.h"
#include "TDrawableComponent.h"
#include "TLogicBoardComponent.h"

namespace nne
{

	TPackageComponent::TPackageComponent() :
		mPackageColor({ 30u, 30u, 30u }),
		mPackageType(TPackageType::DIP)
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
		// Skip the refresh function if we didn't place the chip yet
		if (!mParent->getComponent<TChipComponent>().isPlaced())
			return;

		// Check if the package it's powered on if the chip is placed
		checkPowerStatus();

		// Get mouse info
		auto& MousePos = mParent->getComponent<tcomponents::TEventComponent>().getMousePosition();

		// Check if we clicked on the chip
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && getGlobalBound().contains(MousePos))
		{
			// Set this chip component as the chip selected in the board
			mParent->getComponent<TLogicBoardComponent>().getBoard().setSelectedComponent(mParent->getComponentAsPtr<TChipComponent>());

			// Debug message
			std::string DebugMessage = "We clicked on the chip: " + mParent->getComponent<TChipComponent>().getName();
			::MessageBoxA(NULL, DebugMessage.c_str(), "Clicked!", MB_OK);
		}
	}

	void TPackageComponent::init()
	{
		//renderDipChip();
	}

	void TPackageComponent::computeChipSize(const TPackageType& PackageType, const std::size_t& PinsNumber)
	{
		// The value of the half pin number (easier and faster to type and read XD)
		auto HalfPinNumber = PinsNumber / 2;

		switch (PackageType)
		{
			/*
				DIP PACKAGE SIZE:
								
								B
					C  _   _   _   _   _   _ C 		LEGEND:
					 _|_|_|_|_|_|_|_|_|_|_|_|_			A = Width
					|						  |			B = Height
				A	|	   DIP PACKAGE		  |			C = Initial gap
					|_________________________|			D = Pin width
					  |_|F|_| |_| |_| |_| |_|			F = Pin height
														E = Pin gap
				       D	 E 
				
				In a DIP package the width (A) is of a fixed 185.f. The height (B) it's based on the number of pins and the value of C and D.
				C it's the gap between the first pin in a row and the beginning of the chip. This value also applies between the last pin in 
				a row and the end of the chip.
				D it's the width of a pin.
				F it's the height of the pin.
				E it's the gap between pins.

				In our application those value are if the chip is posed horizontally:
				A = 185.f
				C = 19.f
				D = 9.f  (Pin width)
				F = 15.f (Pin height)
				E = 14.f
				B = (C * 2) + (D * (PinNumber / 2)) + (E * ((PinNumber / 2) - 1)
					
			*/
			case TPackageType::DIP:
			{
				// Pin size
				mPinSize = { 15.f, 9.f };

				// Chip size
				mChipSize = { 185.f, 38.f + (mPinSize.y * HalfPinNumber) + (14 * (HalfPinNumber - 1)) };

				// Create a base drawable component shape with the chip size
				mParent->getComponent<TDrawableComponent>().setSize(static_cast<sf::Vector2u>(mChipSize));

				// Save the local chip bound without the pins
				mChipBound = { { 0.f, 0.f }, mChipSize };

				// Save the local chip bound with the pins
				mChipAndPinsBound = { { -mPinSize.x, 0.f }, mChipSize + sf::Vector2f(mPinSize.x * 2.f, 0.f) };
			} break;

			/*

				LED PACKAGE SIZE:
				   ______	
				 _|		 |_
				|_|		 |_|
				  |______|
			*/
			case TPackageType::LED:
			{
				// Pin size
				mPinSize = { 15.f, 9.f };

				// Chip size
				mChipSize = { 47.f, 47.f }/*{ 35.f, 35.f }*/;

				// Create a base drawable component shape with the chip size
				mParent->getComponent<TDrawableComponent>().setSize(static_cast<sf::Vector2u>(mChipSize));

				// Save the local chip bound without the pins
				mChipBound = { { 0.f, 0.f }, mChipSize };

				// Save the local chip bound with the pins
				mChipAndPinsBound = { { -mPinSize.x, 0.f }, mChipSize + sf::Vector2f(mPinSize.x * 2.f, 0.f) };
			} break;

			/*

				LED PACKAGE SIZE:

					 VCC		   GND
				   _______			_
				  |		  |		 __|_|__
				  |		  |		|		|
				  |_______|		|		|
					 |_|		|_______|
				  				   	
				  
			*/
			case TPackageType::POWER_CONNECTOR:
			{
				// Load the texture based on the power type
				auto PowerTypeIsGround = mParent->getComponent<TPowerComponent>().getPowerType() == TPowerComponent::Type::GROUND ? true : false;
				auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
				std::string PowerTypeResource = PowerTypeIsGround ? "ground" : "power";

				// Load the texture
				DrawableComponent.setTexture(TCacheManager::getInstance().getResource<sf::Texture>(PowerTypeResource));

				// Pin size
				mPinSize = { 9.f, 15.f };

				// Chip size
				mChipSize = static_cast<sf::Vector2f>(DrawableComponent.getSize());

				// Save the local chip bound without the pins
				mChipBound = { { 0.f, 0.f }, mChipSize };

				// Save the local chip bound with the pins
				if (PowerTypeIsGround)
					mChipAndPinsBound = { { 0.f, -mPinSize.y }, mChipSize };
				else
					mChipAndPinsBound = { { 0.f, 0.f }, mChipSize + sf::Vector2f(0.f, mPinSize.y) };				
			} break;
		}
	}

	void TPackageComponent::renderDipChip()
	{
		// Get a ref to the PIN, drawable and text component
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		// Set the chip color
		DrawableComponent.setColor({ 30, 30, 30 });

		// Compute the chip size and the pin size
		computeChipSize(TPackageType::DIP, NumberOfPins);

		// Add the pin to the drawable component
		renderPins(DrawableComponent.getPosition());

		// Add the pins labels to the drawable component
		renderPinLabels(DrawableComponent.getPosition());

		// Add the chip name to the drawable component
		renderChipName(mParent->getComponent<TChipComponent>().getName());
	}

	void TPackageComponent::renderLed()
	{
		// Get a ref to the PIN, drawable component
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = DrawableComponent.getVertexArray();

		// Compute the chip size and the pin size
		computeChipSize(TPackageType::LED, PinComponent.getPinList().size());

		// Add the pin to the drawable component
		renderPins(DrawableComponent.getPosition());
		
		// Add the pins labels to the drawable component
		//renderPinLabels(DrawableComponent.getPosition());

		// Add the chip name to the drawable component
		//renderChipName(mParent->getComponent<TChipComponent>().getName());
	}

	void TPackageComponent::renderPowerConnector()
	{
		// Get a ref to the drawable and pin component
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& PowerType = mParent->getComponent<TPowerComponent>().getPowerType();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = DrawableComponent.getVertexArray();

		// Compute the chip size and the pin size
		computeChipSize(TPackageType::POWER_CONNECTOR, PinComponent.getPinList().size());

		// Add the pin to the drawable component
		renderPins(DrawableComponent.getPosition());

		// Add the pins labels to the drawable component
		//renderPinLabels(DrawableComponent.getPosition());

		// Add the chip name to the drawable component
		//renderChipName(mParent->getComponent<TChipComponent>().getName());
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

	void TPackageComponent::renderPins(const sf::Vector2f& ChipPosition)
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

			switch (mPackageType)
			{
				case TPackageType::DIP:
				{
					if (PinCounter < NumberOfPins / 2)
						PinPosition = { -mPinSize.x, 23.f * PinCounter + 19.f };
					else
						PinPosition = { mChipSize.x, 23.f * (NumberOfPins - PinCounter) - 4.f };
				} break;
				case TPackageType::LED:
				{
					if (PinCounter < NumberOfPins / 2)
						PinPosition = { -mPinSize.x, mChipSize.y / 2.f - mPinSize.y / 2.f }; // Create the anode PIN
					else
						PinPosition = { mChipSize.x, mChipSize.y / 2.f - mPinSize.y / 2.f }; // Create the cathode PIN
				} break;
				case TPackageType::POWER_CONNECTOR:
				{
					if (mParent->getComponent<TPowerComponent>().getPowerType() == TPowerComponent::Type::GROUND)
						PinPosition = { mChipSize.x / 2.f - mPinSize.x / 2.f, -mPinSize.y }; // Create the GND PIN
					else
						PinPosition = { mChipSize.x / 2.f - mPinSize.x / 2.f, mChipSize.y }; // Create the VCC PIN
				} break;
			}

			PinComponent.createPin(PinPosition /*+ ChipPosition*/, mPinSize, Vertices);
		}
	}

	void TPackageComponent::renderPinLabels(const sf::Vector2f& ChipPosition)
	{
		// Get a ref to the TPinComponent
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& Labels = mParent->getComponent<TTextComponent>();

		// Clear
		Labels.clearCharacterPosition();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		// Chip total string
		std::string ChipTotalString = "";

		for (std::size_t PinCounter = 0; PinCounter < NumberOfPins; ++PinCounter)
		{
			// Pin global bound
			auto PinBound = PinComponent.getPinLocalBounds(PinCounter);
			
			// Pin label position
			sf::Vector2f LabelPosition = { PinBound.left, PinBound.top };

			// Pin offset
			sf::Vector2f LabelOffset = PinCounter < NumberOfPins / 2 ? sf::Vector2f(17.f, 0.f) : sf::Vector2f(-13.f, 0.f);
			
			// Create the pin label			
			auto& PinName = PinComponent.getPin(PinCounter + 1).mPinName;

			// Compute the length of the Label
			float LabelLength = PinCounter < NumberOfPins / 2 ? 0.f : getStringLength(Labels, sf::String(PinName + " "));

			ChipTotalString += PinName + "  ";
			Labels.setString(ChipTotalString);
			Labels.setCharacterPosition(PinName + " ", { LabelPosition.x - LabelLength + LabelOffset.x, LabelPosition.y - 3.f + LabelOffset.y });
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
		renderChipName(mParent->getComponent<TChipComponent>().getName());
	}

	const sf::FloatRect& TPackageComponent::getLocalBound(const bool& IncludePinsBound /*= false*/) const
	{
		return IncludePinsBound ? mChipAndPinsBound : mChipBound;
	}

	sf::FloatRect TPackageComponent::getGlobalBound(const bool& IncludePinsBound /*= false*/) const
	{
		return mParent->getComponent<TDrawableComponent>().getTransform().transformRect(getLocalBound(IncludePinsBound));
	}

	void TPackageComponent::renderChipName(const std::string& ChipName)
	{
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& Labels = mParent->getComponent<TTextComponent>();

		// Get the length 
		auto ChipNameWidth = getStringLength(Labels, ChipName);

		// Chip width
		auto ChipWidth = mChipBound.width;

		auto CharHeight = Labels.getFont()->getGlyph('A', Labels.getCharacterSize(), Labels.getStyle() == TTextComponent::Bold).textureRect.height / 2.f;

		// Compute where the chip name label should be positioned
		sf::Vector2f ChipNamePos = { std::roundf(ChipWidth / 2.f - ChipNameWidth / 2.f - mPinSize.x), std::roundf(mChipSize.y / 2.f - CharHeight - 3.f) };
		
		// Render pin labels
		renderPinLabels(mParent->getComponent<TDrawableComponent>().getPosition());

		// Chip total string
		std::string ChipTotalString = Labels.getString().toAnsiString();
		
		Labels.setString(ChipTotalString + ChipName + "  ");
		Labels.setCharacterPosition(ChipName + " ", ChipNamePos);
	}

	void TPackageComponent::setPackageType(const TPackageType& PackageType)
	{
		// Set the package type
		mPackageType = PackageType;

		// Update the package look
		switch (mPackageType)
		{
			// Render a dip chip
			case TPackageType::DIP:
				renderDipChip();
				break;

			// Render a led
			case TPackageType::LED:
				renderLed();
				break;

			// Render a custom chip so only render the labels and pin
			case nne::TPackageComponent::TPackageType::POWER_CONNECTOR:
				renderPowerConnector();
				break;
		}
	}

	const TPackageComponent::TPackageType& TPackageComponent::getPackageType() const
	{
		return mPackageType;
	}

	void TPackageComponent::setPackageColor(const sf::Color& PackageColor)
	{
		mPackageColor = PackageColor;
	}

	const sf::Color& TPackageComponent::getPackageColor() const
	{
		return mPackageColor;
	}

}
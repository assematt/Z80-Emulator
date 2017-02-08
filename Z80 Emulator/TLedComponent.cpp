#include "TLedComponent.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "TPackageComponent.h"
#include "TChipComponent.h"
#include "TCacheManager.h"

namespace nne
{

	TLedComponent::TLedComponent() :
		mOnColor({ 255u, 0u, 0u }),
		mOffColor({ 25u, 25u, 25u }),
		mIsOn(false)
	{
	}

	void TLedComponent::update(const sf::Time& ElapsedTime)
	{
		// 
		auto& IsPlaced = mParent->getComponent<TChipComponent>().isPlaced();
		auto& Package = mParent->getComponent<TPackageComponent>();
		
		// Update the LED color only if the component it's placed
		if (IsPlaced)
		{
			mIsOn ? Package.setPackageColor({ mOnColor }) : Package.setPackageColor(mOffColor);
		}
	}

	void TLedComponent::refresh(const sf::Time& ElapsedTime)
	{
		// Change the status based on the value of the anode and cathode
		checkLedStatus();
	}

	void TLedComponent::init()
	{
		// Setup the LED Pins
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		PinComponent.setupPins(std::initializer_list<tcomponents::TPin>{
			//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber
			{ tcomponents::TPin::TMode::INPUT, "ANODE", tcomponents::TPin::TStatus::LOW, 1 },	 // A1
			{ tcomponents::TPin::TMode::OUTPUT, "CATHODE",  tcomponents::TPin::TStatus::LOW, 2 }, // A2
		}, 2);
	}

	const bool& TLedComponent::isOn() const
	{
		return mIsOn;
	}
	
	void TLedComponent::checkLedStatus()
	{
		// Get a ref to the PIN Component
		auto& PinComponent = mParent->getComponent<TPinComponent>();

		// Get the anode and the cathode
		auto& Anode = PinComponent.getPin(1);
		auto& Cathode = PinComponent.getPin(2);

		// By default we assume the led is off
		mIsOn = false;

		// If both pin are connected to something
		if (Anode.hasConnections() && Cathode.hasConnections())
		{
			// If the anode is positive and the cathode is 0
			mIsOn = (Anode.getPinStatus() == TPin::HIGH && Cathode.getPinStatus() == TPin::LOW) ? true : false;
		}
	}

}
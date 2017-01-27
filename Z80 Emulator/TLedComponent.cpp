#include "TLedComponent.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "TDrawableComponent.h"
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
		
		// Update the LED color only if the component it's placed
		if (IsPlaced)
		{
			auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
			mIsOn ? DrawableComponent.setColor({ mOnColor }) : DrawableComponent.setColor(mOffColor);
		}
	}

	void TLedComponent::refresh(const sf::Time& ElapsedTime)
	{
		// Get a ref to the PIN Component
		auto& PinComponent = mParent->getComponent<TPinComponent>();

		// Change the status based on the value of the anode and cathode
		checkLedStatus();
	}

	void TLedComponent::init()
	{
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();

		// Setup the LED Pins
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		PinComponent.setupPins(std::initializer_list<tcomponents::TPin>{
			//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber
			{ tcomponents::TPin::TMode::INPUT, "ANODE", tcomponents::TPin::TStatus::LOW, 1 },	 // A1
			{ tcomponents::TPin::TMode::OUTPUT, "CATHODE",  tcomponents::TPin::TStatus::LOW, 2 }, // A2
		}, 2);
				
		renderLed();
	}

	const bool& TLedComponent::isOn() const
	{
		return mIsOn;
	}

	void TLedComponent::renderLed()
	{
		// Get a ref to the PIN, drawable component
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = DrawableComponent.getVertexArray();

		// Define pin size
		sf::Vector2f PinSize = { 10.f, 9.f };

		// Define the LED size
		DrawableComponent.setSize({ 35u, 35u });

		// Get the size of the texture
		auto LedBound = DrawableComponent.getLocalBounds();

		// Create the anode PIN
		PinComponent.createPin({ -PinSize.x, LedBound.height / 2.f - PinSize.y / 2.f }, PinSize, Vertices);

		// Create the cathode PIN
		PinComponent.createPin({ LedBound.width, LedBound.height / 2.f - PinSize.y / 2.f }, PinSize, Vertices);

		// Set the origin to be at the center bottom
		DrawableComponent.setOrigin({ 35.f / 2.f, 35.f / 2.f });
	}
	
	void TLedComponent::checkLedStatus()
	{
		// Get a ref to the PIN Component
		auto& PinComponent = mParent->getComponent<TPinComponent>();

		// Get the anode and the cathode
		auto& Anode = PinComponent.getPin(1);
		auto& Cathode = PinComponent.getPin(2);

		// If both pin are connected to something
		if (Anode.hasConnections() && Cathode.hasConnections())
		{
			// If the anode is positive and the cathode is 0
			mIsOn = (Anode.getPinStatus() == TPin::HIGH && Cathode.getPinStatus() == TPin::LOW) ? true : false;
		}
	}

}
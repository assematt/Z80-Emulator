#include "TLedComponent.h"

#include <SFML/Graphics/Texture.hpp>
#include "TDrawableComponent.h"
#include "TChipComponent.h"
#include "TCacheManager.h"

namespace nne
{

	TLedComponent::TLedComponent() :
		mOnColor({ 255u, 0u, 0u }),
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
			mIsOn ? DrawableComponent.setColor({ mOnColor }) : DrawableComponent.setColor({ 30u, 30u, 30u, 255u });
		}
	}

	void TLedComponent::refresh(const sf::Time& ElapsedTime)
	{
		// Get a ref to the PIN Component
		auto& PinComponent = mParent->getComponent<tcomponents::TPinComponent>();

		// Change the status based on the value of the anode
		mIsOn = PinComponent.getPin(1).getPinStatus() == tcomponents::TPin::HIGH ? true : false;
	}

	void TLedComponent::init()
	{
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();

		// Setup the CPU Pins
		auto& PinComponent = mParent->getComponent<tcomponents::TPinComponent>();
		PinComponent.setupPins(std::initializer_list<tcomponents::TPin>{
			//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber
			{ tcomponents::TPin::TMode::INPUT, "ANODE", tcomponents::TPin::TStatus::LOW, 1, 0, 0 },		// A1
			{ tcomponents::TPin::TMode::OUTPUT, "CATHODE",  tcomponents::TPin::TStatus::LOW, 2, 0, 0 }, // A2
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
		auto& PinComponent = mParent->getComponent<tcomponents::TPinComponent>();
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
	}

}
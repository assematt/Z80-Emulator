#include "TPowerComponent.h"

#include "TDrawableComponent.h"
#include "TChipComponent.h"
#include "TCacheManager.h"

namespace nne
{
	TPowerComponent::TPowerComponent(const Type& Mode /*= Type::GROUND*/) :
		mPowerType(Mode)
	{
	}

	void TPowerComponent::update(const sf::Time& ElapsedTime)
	{
		// 
		auto& IsPlaced = mParent->getComponent<TChipComponent>().isPlaced();

		// Update the LED color only if the component it's placed
		if (IsPlaced)
		{
			auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
			DrawableComponent.setColor({ 30u, 30u, 30u, 255u });
		}
	}

	void TPowerComponent::refresh(const sf::Time& ElapsedTime)
	{

	}

	void TPowerComponent::init()
	{
		// Get a ref to the drawable and pin component
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
		auto& PinComponent = mParent->getComponent<TPinComponent>();

		if (mPowerType == Type::GROUND)
		{
			// Set the texture
			DrawableComponent.setTexture(TCacheManager::getInstance().getResource<sf::Texture>("ground"));

			PinComponent.setupPins(std::initializer_list<tcomponents::TPin>{
				//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber
				{ tcomponents::TPin::TMode::POWER, "GND", tcomponents::TPin::TStatus::LOW, 1, 0, 0 }, // GND
			}, 1);

		}
		else if (mPowerType == Type::POWER)
		{
			// Set the texture
			DrawableComponent.setTexture(TCacheManager::getInstance().getResource<sf::Texture>("power"));

			PinComponent.setupPins(std::initializer_list<tcomponents::TPin>{
				//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber
				{ tcomponents::TPin::TMode::POWER, "VCC", tcomponents::TPin::TStatus::HIGH, 1, 0, 0 }, // GND
			}, 1);
		}

		// Add a connection PIN
		addConnectionPin();
	}

	void TPowerComponent::addConnectionPin()
	{
		// Get a ref to the PIN, drawable component
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = DrawableComponent.getVertexArray();

		// Define pin size
		sf::Vector2f PinSize = { 9.f, 15.f };

		// Size
		auto ChipSize = DrawableComponent.getSize();

		if (mPowerType == Type::GROUND)
		{
			// Create the connection PIN on the center top
			PinComponent.createPin({ ChipSize.x / 2.f - PinSize.x / 2.f, -PinSize.y }, PinSize, Vertices);

			// Set the origin to be at the center top
			DrawableComponent.setOrigin({ ChipSize.x / 2.f - 1.f, 0 });
		}
		else if (mPowerType == Type::POWER)
		{
			// Create the connection PIN on the center bottom
			PinComponent.createPin({ ChipSize.x / 2.f - PinSize.x / 2.f, static_cast<float>(ChipSize.y) }, PinSize, Vertices);

			// Set the origin to be at the center bottom
			DrawableComponent.setOrigin({ ChipSize.x / 2.f - 1.f, static_cast<float>(ChipSize.y) });
		}
	}

}
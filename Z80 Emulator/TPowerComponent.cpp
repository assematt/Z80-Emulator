#include "TPowerComponent.h"

#include "TDrawableComponent.h"
#include "TPinComponent.h"
#include "TChipComponent.h"
#include "TCacheManager.h"

namespace nne
{
	TPowerComponent::TPowerComponent(const Type& Mode /*= Type::GROUND*/) :
		mPowerType(Mode)
	{
	}

	void TPowerComponent::update(REFRESH_UPDATE_PARAMETER)
	{
		// Update the LED color only if the component it's placed
#if ENTITY_SYSTEM == NNE
		if (mParent->getComponent<TChipComponent>().isPlaced())
		{
			auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
			DrawableComponent.setColor({ 30u, 30u, 30u, 255u });
		}
#else
		if (mParent->getComponent<TChipComponent>()->isPlaced())
		{
			auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
			DrawableComponent->setColor({ 30u, 30u, 30u, 255u });
		}
#endif		
			
	}

	void TPowerComponent::refresh(REFRESH_UPDATE_PARAMETER)
	{

	}

	void TPowerComponent::init()
	{
		// Get a ref to the drawable and pin component
#if ENTITY_SYSTEM == NNE
		auto PinComponent = mParent->getComponentAsPtr<TPinComponent>();
#else
		auto& PinComponent = mParent->getComponent<TPinComponent>();
#endif

		// Set the pin type according to the type of the power connector
		if (mPowerType == Type::GROUND)
		{
			PinComponent->setupPins(std::initializer_list<tcomponents::TPin>{
				//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber
				{ tcomponents::TPin::TMode::POWER, "GND", tcomponents::TPin::TStatus::LOW, 1 }, // GND
			}, 1);
		}
		else if (mPowerType == Type::POWER)
		{
			PinComponent->setupPins(std::initializer_list<tcomponents::TPin>{
				//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber
				{ tcomponents::TPin::TMode::POWER, "VCC", tcomponents::TPin::TStatus::HIGH, 1 }, // GND
			}, 1);
		}
	}

	const TPowerComponent::Type& TPowerComponent::getPowerType() const
	{
		return mPowerType;
	}

	void TPowerComponent::addConnectionPin()
	{
		// Get a ref to the PIN, drawable component
#if ENTITY_SYSTEM == NNE
		auto PinComponent = mParent->getComponentAsPtr<TPinComponent>();
		auto DrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();
#else
		auto& PinComponent = mParent->getComponent<TPinComponent>();
		auto& DrawableComponent = mParent->getComponent<TDrawableComponent>();
#endif

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = DrawableComponent->getVertexArray();

		// Define pin size
		sf::Vector2f PinSize = { 9.f, 15.f };

		// Size
		auto ChipSize = DrawableComponent->getSize();

		if (mPowerType == Type::GROUND)
		{
			// Create the connection PIN on the center top
			PinComponent->createPin({ ChipSize.x / 2.f - PinSize.x / 2.f, -PinSize.y }, PinSize, Vertices);

			// Set the origin to be at the center top
			DrawableComponent->setOrigin({ ChipSize.x / 2.f - 1.f, 0 });
		}
		else if (mPowerType == Type::POWER)
		{
			// Create the connection PIN on the center bottom
			PinComponent->createPin({ ChipSize.x / 2.f - PinSize.x / 2.f, static_cast<float>(ChipSize.y) }, PinSize, Vertices);

			// Set the origin to be at the center bottom
			DrawableComponent->setOrigin({ ChipSize.x / 2.f - 1.f, static_cast<float>(ChipSize.y) });
		}
	}

}
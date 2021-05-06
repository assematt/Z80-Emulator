#pragma once

#include <functional>
#include <string>
#include <memory>

#include "TValues.h"
#include "TPowerComponent.h"
#include INCLUDE_ENTITY_CLASS
#include <ECS/_TManager.h>

namespace nne
{
	namespace TFactory
	{
		ENTITY_PTR makeWire(FACTORY_ARGUMENT);

		ENTITY_PTR makeBus(FACTORY_ARGUMENT);

		ENTITY_PTR makeLogicBoard(FACTORY_ARGUMENT);

		ENTITY_PTR makeZ80(FACTORY_ARGUMENT);

		ENTITY_PTR makeRam(FACTORY_ARGUMENT);

		ENTITY_PTR makeLed(FACTORY_ARGUMENT);

		ENTITY_PTR makeNandChip(FACTORY_ARGUMENT);

#if ENTITY_SYSTEM == NNE
		ENTITY_PTR makePowerConnector(const TPowerComponent::Type& Mode);
#else
		ENTITY_PTR makePowerConnector(FACTORY_ARGUMENT, const TPowerComponent::Type& Mode);
#endif

		ENTITY_PTR makeGuiWidget(FACTORY_ARGUMENT);

#if ENTITY_SYSTEM == USE_ECS
		void fillManagerWithSystems(ecs::_TManager& Manager);
#endif

	};
}
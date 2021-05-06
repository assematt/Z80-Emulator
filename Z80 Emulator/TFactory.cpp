#include "TFactory.h"

#include "TChipComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TWireComponent.h"
#include "TBusComponent.h"
#include "TLogicBoardComponent.h"
#include "TPackageComponent.h"
#include "TLogicGateComponent.h"
#include "TEventComponent.h"
#include "TLedComponent.h"
#include "TZ80Component.h"
#include "TPinComponent.h"
#include "TRamComponent.h"
#include "TMemoryComponent.h"
#include "TGridComponent.h"
#include "TStateComponent.h"
#include "TMultiplexerComponent.h"

#include <ECS/_TManager.h>

namespace nne
{
	namespace TFactory
	{
		using namespace nne::tcomponents;


		ENTITY_PTR makeWire(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TWireComponent>();
			TempPtr->addComponent<TEventComponent>();
			TempPtr->addComponent<TStateComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();

			return std::move(TempPtr);
		}

		ENTITY_PTR makeBus(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TBusComponent>();
			TempPtr->addComponent<TEventComponent>();
			TempPtr->addComponent<TStateComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();

			return std::move(TempPtr);
		}

		ENTITY_PTR makeLogicBoard(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TGridComponent>();
			
			return std::move(TempPtr);
		}

		ENTITY_PTR makeZ80(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
#if ENTITY_SYSTEM == NNE
			TempPtr->addComponent<tcomponents::TZ80Component>();
#else
			TempPtr->addComponent<TZ80Component>();
#endif
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();
			TempPtr->addComponent<TEventComponent>();
			TempPtr->addComponent<TStateComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();

			return std::move(TempPtr);
		}

		ENTITY_PTR makeRam(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<tcomponents::TRamComponent>();
			TempPtr->addComponent<tcomponents::TMemoryComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();
			TempPtr->addComponent<TEventComponent>();
			TempPtr->addComponent<TStateComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();

			return std::move(TempPtr);
		}

		ENTITY_PTR makeLed(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TLedComponent>();
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();
			TempPtr->addComponent<TEventComponent>();
			TempPtr->addComponent<TStateComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();

			return std::move(TempPtr);
		}

		ENTITY_PTR makeNandChip(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<TLogicGateComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();
			TempPtr->addComponent<TEventComponent>();
			TempPtr->addComponent<TStateComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();

			return std::move(TempPtr);
		}

#if ENTITY_SYSTEM == NNE
		ENTITY_PTR makePowerConnector(const TPowerComponent::Type& Mode)
#else
		ENTITY_PTR makePowerConnector(FACTORY_ARGUMENT, const TPowerComponent::Type& Mode)
#endif
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<TTextComponent>();
#if ENTITY_SYSTEM == NNE
			TempPtr->addComponent<TPowerComponent>(Mode);
#else
			TempPtr->addComponent<TPowerComponent>();
#endif
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();
			TempPtr->addComponent<TEventComponent>();
			TempPtr->addComponent<TStateComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();

			return std::move(TempPtr);
		}

		ENTITY_PTR makeGuiWidget(FACTORY_ARGUMENT)
		{
			ENTITY_PTR TempPtr = CORRECT_MAKE_SHARED;

			TempPtr->addComponent<TDrawableComponent>();

			return std::move(TempPtr);
		}

#if ENTITY_SYSTEM == USE_ECS
		void fillManagerWithSystems(ecs::_TManager& Manager)
		{
			Manager.addSystem<TEventComponent>();
			Manager.addSystem<TLogicGateComponent>();
			Manager.addSystem<TMemoryComponent>();
			Manager.addSystem<TMultiplexerComponent>();
			Manager.addSystem<TRamComponent>();
			Manager.addSystem<TStateComponent>();
			Manager.addSystem<TZ80Component>();
			Manager.addSystem<TBusComponent>();
			Manager.addSystem<TChipComponent>();
			Manager.addSystem<TDrawableComponent>();
			Manager.addSystem<TGridComponent>();
			Manager.addSystem<TLedComponent>();
			Manager.addSystem<TLogicBoardComponent>();
			Manager.addSystem<TPackageComponent>();
			Manager.addSystem<TPinComponent>();
			Manager.addSystem<TPowerComponent>();
			Manager.addSystem<TTextComponent>();
			Manager.addSystem<TWireComponent>();
		}
#endif

	}
}
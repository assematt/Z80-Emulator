#include "TFactory.h"

#include "TChipComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TWireComponent.h"
#include "TBusComponent.h"
#include "TLogicBoardComponent.h"
#include "TPackageComponent.h"
#include "TLogicGateComponent.h"
#include "TLedComponent.h"
#include "TZ80Component.h"
#include "TPinComponent.h"
#include "TRamComponent.h"
#include "TMemoryComponent.h"
#include "TGridComponent.h"

namespace nne
{
	namespace TFactory
	{
		
		std::shared_ptr<nne::TEntity> makeWire()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TWireComponent>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeBus()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TBusComponent>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeLogicBoard()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TGridComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();
			
			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeZ80()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<tcomponents::TZ80Component>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeRam()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<tcomponents::TRamComponent>();
			TempPtr->addComponent<tcomponents::TMemoryComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeLed()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TLedComponent>();
			TempPtr->addComponent<TChipComponent>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeNandChip()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<TLogicGateComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TChipComponent>();
			TempPtr->addComponent<TPackageComponent>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makePowerConnector(const TPowerComponent::Type& Mode)
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TPinComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TPowerComponent>(Mode);
			TempPtr->addComponent<TChipComponent>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeGuiWidget()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();

			return std::move(TempPtr);
		}

	}
}
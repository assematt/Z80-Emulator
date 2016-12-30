#include "TFactory.h"

#include "TChipComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TWireComponent.h"
#include "TBusComponent.h"
#include "TLogicBoardComponent.h"
#include "TZ80Component.h"
#include "TPinComponent.h"
#include "TRamComponent.h"
#include "TMemoryComponent.h"
#include "TGridComponent.h"

namespace nne
{
	namespace TFactory
	{

		std::shared_ptr<nne::TEntity> makeChip(TEntity* ChipToRender)
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TTextComponent>();
			TempPtr->addComponent<TChipComponent>(ChipToRender);

			return std::move(TempPtr);
		}

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

			TempPtr->addComponent<tcomponents::TPinComponent>();
			TempPtr->addComponent<tcomponents::TZ80Component>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeRam()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<tcomponents::TPinComponent>();
			TempPtr->addComponent<tcomponents::TRamComponent>();
			TempPtr->addComponent<tcomponents::TMemoryComponent>();

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
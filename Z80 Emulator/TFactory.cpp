#include "TFactory.h"

namespace nne
{
	namespace TFactory
	{

		std::shared_ptr<nne::TEntity> makeChip(TEntity* ChipToRender)
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();
			TempPtr->addComponent<TChipComponent>(ChipToRender);

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeConductiveTrack()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TLogicBoardComponent>();
			TempPtr->addComponent<TConductiveTracks>();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TEntity> makeLogicBoard()
		{
			std::shared_ptr<nne::TEntity> TempPtr = std::make_shared<nne::TEntity>();

			TempPtr->addComponent<TDrawableComponent>();
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
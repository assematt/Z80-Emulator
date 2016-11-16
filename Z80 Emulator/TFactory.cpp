#include "TFactory.h"

namespace nne
{
	namespace TFactory
	{

		std::shared_ptr<nne::TGraphicEntity> makeChip(TEntity* ChipToRender)
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->addComponent<TSprite>();
			TempPtr->addComponent<TTransformable>();
			TempPtr->addComponent<TdrawableVector>();
			TempPtr->addComponent<TChip>(ChipToRender);
			TempPtr->initComponents();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TGraphicEntity> makeConductiveTrack()
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->addComponent<TSprite>();
			TempPtr->addComponent<TTransformable>();
			TempPtr->addComponent<TdrawableVector>();
			TempPtr->addComponent<TConductiveTracks>();
			TempPtr->initComponents();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TGraphicEntity> makeGuiWidget()
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->addComponent<TSprite>();
			TempPtr->addComponent<TTransformable>();
			TempPtr->addComponent<TdrawableVector>();
			TempPtr->initComponents();

			return std::move(TempPtr);
		}

	}
}
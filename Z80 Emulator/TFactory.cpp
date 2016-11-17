#include "TFactory.h"

namespace nne
{
	namespace TFactory
	{

		std::shared_ptr<nne::TGraphicEntity> makeChip(TEntity* ChipToRender)
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TChipComponent>(ChipToRender);
			TempPtr->initComponents();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TGraphicEntity> makeConductiveTrack()
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->addComponent<TConductiveTracks>();
			TempPtr->initComponents();

			return std::move(TempPtr);
		}

		std::shared_ptr<nne::TGraphicEntity> makeGuiWidget()
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->addComponent<TDrawableComponent>();
			TempPtr->initComponents();

			return std::move(TempPtr);
		}

		

	}
}
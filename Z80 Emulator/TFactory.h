#pragma once

#include <memory>

#include "TChip.h"
#include "TTexture.h"
#include "TTransformable.h"
#include "TGraphicEntity.h"

namespace nne
{
	struct TFactory
	{
		static std::shared_ptr<TGraphicEntity> MakeDrawableEntity()
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->AddComponent<TTexture>();
			TempPtr->AddComponent<TTransformable>();
			TempPtr->InitComponents();

			return std::move(TempPtr);
		}

		static std::shared_ptr<TGraphicEntity> MakeChip(TEntity* ChipToRender)
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->AddComponent<TTexture>();
			TempPtr->AddComponent<TTransformable>();
			TempPtr->AddComponent<TChip>(ChipToRender);
			TempPtr->InitComponents();

			return std::move(TempPtr);
		}

		static std::shared_ptr<TGraphicEntity> MakeGuiWidget()
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->AddComponent<TTexture>();
			TempPtr->AddComponent<TTransformable>();
			TempPtr->InitComponents();

			return std::move(TempPtr);
		}

	};
}
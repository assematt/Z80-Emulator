#pragma once

#include <memory>

#include "TFont.h"
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

		static std::shared_ptr<TGraphicEntity> MakeGuiWidget()
		{
			std::shared_ptr<TGraphicEntity> TempPtr = std::make_shared<TGraphicEntity>();

			TempPtr->AddComponent<TTexture>();
			TempPtr->AddComponent<TTransformable>();
			TempPtr->AddComponent<TFont>();
			TempPtr->GetComponentAsPtr<TFont>()->SetText("");
			TempPtr->InitComponents();

			return std::move(TempPtr);
		}

	};
}
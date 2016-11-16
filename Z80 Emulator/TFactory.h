#pragma once

#include <memory>

#include "TChip.h"
#include "TSprite.h"
#include "TdrawableVector.h"
#include "TConductiveTracks.h"
#include "TTransformable.h"
#include "TGraphicEntity.h"

namespace nne
{
	namespace TFactory
	{
		std::shared_ptr<TGraphicEntity> makeChip(TEntity* ChipToRender);

		std::shared_ptr<TGraphicEntity> makeConductiveTrack();

		std::shared_ptr<TGraphicEntity> makeGuiWidget();

	};
}
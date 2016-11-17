#pragma once

#include <memory>

#include "TChipComponent.h"
#include "TDrawableComponent.h"
#include "TConductiveTracks.h"
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
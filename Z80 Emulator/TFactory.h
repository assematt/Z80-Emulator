#pragma once

#include <memory>

#include "TChipComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TConductiveTracks.h"
#include "TZ80Component.h"
#include "TPinComponent.h"
#include "TRamComponent.h"
#include "TMemoryComponent.h"

namespace nne
{
	namespace TFactory
	{
		std::shared_ptr<TEntity> makeChip(TEntity* ChipToRender);

		std::shared_ptr<TEntity> makeZ80();

		std::shared_ptr<TEntity> makeRam();

		std::shared_ptr<TEntity> makeConductiveTrack();

		std::shared_ptr<TEntity> makeGuiWidget();
	};
}
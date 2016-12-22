#pragma once

#include <memory>
#include "TEntity.h"



namespace nne
{
	namespace TFactory
	{
		std::shared_ptr<TEntity> makeChip(TEntity* ChipToRender);

		std::shared_ptr<TEntity> makeConductiveTrack();

		std::shared_ptr<TEntity> makeLogicBoard();

		std::shared_ptr<TEntity> makeZ80();

		std::shared_ptr<TEntity> makeRam();

		std::shared_ptr<TEntity> makeGuiWidget();
	};
}
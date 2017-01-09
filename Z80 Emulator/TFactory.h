#pragma once

#include <memory>
#include "TEntity.h"

namespace nne
{
	namespace TFactory
	{
	
		std::shared_ptr<TEntity> makeWire();

		std::shared_ptr<TEntity> makeBus();

		std::shared_ptr<TEntity> makeLogicBoard();

		std::shared_ptr<TEntity> makeZ80();

		std::shared_ptr<TEntity> makeRam();

		std::shared_ptr<TEntity> makeLed();

		std::shared_ptr<TEntity> makeGuiWidget();

	};
}
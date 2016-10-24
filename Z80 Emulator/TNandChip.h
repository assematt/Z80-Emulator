#pragma once

#pragma once

#include "TValues.h"
#include "TEntity.h"
#include "TPinComponent.h"
#include "TLogicGateComponent.h"

#include <array>

namespace TGame
{
	namespace TModules
	{
		class TNandChip : public TInternals::TEntity
		{
		public:
			TNandChip()
			{
				AddComponent<TPinComponent>();
				AddComponent<TLogicGateComponent>();
				InitComponents();
			}

		};
	}
}


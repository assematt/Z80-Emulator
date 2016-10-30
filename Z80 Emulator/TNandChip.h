#pragma once

#pragma once

#include "TValues.h"
#include "TEntity.h"
#include "TPinComponent.h"
#include "TLogicGateComponent.h"

#include <array>

namespace nne
{
	namespace tmodules
	{
		class TNandChip : public nne::TEntity
		{
		public:
			TNandChip()
			{
				AddComponent<tcomponents::TPinComponent>();
				AddComponent<tcomponents::TLogicGateComponent>();
				InitComponents();
			}

		};
	}
}


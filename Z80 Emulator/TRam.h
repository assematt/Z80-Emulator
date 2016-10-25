#pragma once

#include "TValues.h"
#include "TPinComponent.h"
#include "TMemoryComponent.h"
#include "TEntity.h"
#include <array>

namespace TGame
{
	namespace TModules
	{
		namespace TRamPinGroup
		{
			const TComponents::TPin::TPinGroupID AddressBus = 0;
			const TComponents::TPin::TPinGroupID DataBus = 1;
			const TComponents::TPin::TPinGroupID ChipControl = 2;
			const TComponents::TPin::TPinGroupID Others = 3;
		}

		// 84256 RAM 
		class TRam : public TInternals::TEntity
		{
		public:
			TRam();
			TRam(const TU16BitValue& MemorySize);

			~TRam() = default;

			void Update();

			void Init();

			virtual void MakeVirtual() {};
		private:
			// Cache some pins status for easy access to them
			TU16BitValue				mMemorySize;
			TComponents::TPin::TStatus* mChipEnablePin;
			TComponents::TPin::TStatus* mWritePin;
			TComponents::TPin::TStatus* mOutputEnable;			
		};
	}
}

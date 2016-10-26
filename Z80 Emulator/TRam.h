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
			//TRam(const TRam& Right) = default;
			explicit TRam(const TU16BitValue& MemorySize);

			~TRam() = default;

			void Init();

			void Refresh();

			void RefreshMemory();

			void Update();

			/// 
			TMemory::iterator& begin();
			TMemory::iterator& end();

			/// Subscript operator to access individual memory cell
			TU8BitValue& operator [](const std::size_t Index);
			const TU8BitValue& operator [](const std::size_t Index) const;

			/// Helper to get the entire ram internal memory
			TMemory& GetInternalMemory();
			const TMemory& GetInternalMemory() const;

			virtual void MakeVirtual() {};
		private:
			// Save the size of the ram
			TU16BitValue		mMemorySize;

			// Cache some pins status for easy access to them
			TComponents::TPin*	mChipEnablePin;
			TComponents::TPin*  mWritePin;
			TComponents::TPin*  mOutputEnable;			
		};
	}
}

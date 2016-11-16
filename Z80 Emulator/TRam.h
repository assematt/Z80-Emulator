#pragma once

#include "TValues.h"
#include "TPinComponent.h"
#include "TMemoryComponent.h"
#include "TEntity.h"
#include <array>

namespace nne
{
	namespace tmodules
	{
		namespace TRamPinGroup
		{
			const tcomponents::TPin::TPinGroupID AddressBus = 0;
			const tcomponents::TPin::TPinGroupID DataBus = 1;
			const tcomponents::TPin::TPinGroupID ChipControl = 2;
			const tcomponents::TPin::TPinGroupID Others = 3;
		}

		// 84256 RAM 
		class TRam : public nne::TEntity
		{
		public:

			TRam();
			explicit TRam(const TU16BitValue& MemorySize);

			~TRam() = default;

			void init();

			void refresh();

			void update();

			void refreshMemory();

			/// 
			TMemory::iterator& begin();
			TMemory::iterator& end();

			/// Subscript operator to access individual memory cell
			TU8BitValue& operator [](const std::size_t Index);
			const TU8BitValue& operator [](const std::size_t Index) const;

			/// Helper to get the entire ram internal memory
			TMemory& getInternalMemory();
			const TMemory& getInternalMemory() const;

			virtual void makeVirtual() {};
		private:
			// Save the size of the ram
			TU16BitValue		mMemorySize;

			// Cache some pins status for easy access to them
			tcomponents::TPin*	mChipEnablePin;
			tcomponents::TPin*  mWritePin;
			tcomponents::TPin*  mOutputEnable;			
		};
	}
}

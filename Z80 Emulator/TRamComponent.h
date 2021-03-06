#pragma once

#include <memory>
#include <array>

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include "TPinComponent.h"
#include "TMemoryComponent.h"
#include INCLUDE_ENTITY_CLASS

namespace nne
{
	namespace tcomponents
	{

		namespace TRamPinGroup
		{
			const tcomponents::TPin::TPinGroupID AddressBus = 0;
			const tcomponents::TPin::TPinGroupID DataBus = 1;
			const tcomponents::TPin::TPinGroupID ChipControl = 2;
			const tcomponents::TPin::TPinGroupID Others = 3;
		}

		// 84256 RAM 
		class TRamComponent : BASE_COMPONENT_CLASS
		{
		public:

			TRamComponent();
			explicit TRamComponent(const TU16BitValue& MemorySize);

			~TRamComponent() = default;

			void init();

			void refresh(REFRESH_UPDATE_PARAMETER);

			void update(REFRESH_UPDATE_PARAMETER);

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

		private:
			// Save the size of the ram
			TU16BitValue		mMemorySize;
			TMemoryComponent*	mMemoryComponent;

			// Cache some pins status for easy access to them
			tcomponents::TPin*	mChipEnablePin;
			tcomponents::TPin*	mWritePin;
			tcomponents::TPin*	mOutputEnable;
		};
	}
}
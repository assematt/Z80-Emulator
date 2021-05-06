#pragma once

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include <memory>

namespace nne
{
	namespace tcomponents
	{

		class TMemoryComponent : BASE_COMPONENT_CLASS
		{
		public:
			TMemoryComponent() = default;
			explicit TMemoryComponent(const TU16BitValue& MemorySize);

			void init() override;

			void update(REFRESH_UPDATE_PARAMETER) override;

			void refresh(REFRESH_UPDATE_PARAMETER) override {}

			TU8BitValue& operator[] (const std::size_t Index);
			const TU8BitValue& operator[] (const std::size_t Index) const;

			void resize(const TU16BitValue& MemorySize);

			TMemory& getInternalMemory();
			const TMemory& getInternalMemory() const;

		private:
			TMemory mInternalMemory;
		};
	}
}

#pragma once

#include "IComponent.h"
#include "TValues.h"
#include <memory>

namespace nne
{
	namespace tcomponents
	{

		struct TMemoryComponent : nne::IComponent
		{
		public:
			TMemoryComponent();
			explicit TMemoryComponent(const TU16BitValue& MemorySize);

			void init() override;

			void update() override;

			void refresh() override {}

			TU8BitValue& operator[] (const std::size_t Index);
			const TU8BitValue& operator[] (const std::size_t Index) const;

			TMemory& getInternalMemory();
			const TMemory& getInternalMemory() const;

		private:
			std::shared_ptr<TMemory> mInternalMemory;
		};
	}
}

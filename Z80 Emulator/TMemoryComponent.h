#pragma once


#include "IComponent.h"
#include "TValues.h"

namespace TGame
{
	namespace TComponents
	{

		struct TMemoryComponent : TInternals::IComponent
		{
		public:
			explicit TMemoryComponent(const TU16BitValue& MemorySize);

			void Init();

			void Update();

			TU8BitValue& operator[] (const std::size_t Index);
			const TU8BitValue& operator[] (const std::size_t Index) const;

			TMemory& GetInternalMemory();
			const TMemory& GetInternalMemory() const;

		private:
			TMemory mInternalMemory;
		};
	}
}

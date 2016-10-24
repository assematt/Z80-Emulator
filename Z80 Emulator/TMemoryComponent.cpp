#include "TMemoryComponent.h"

namespace TGame
{
	namespace TComponents
	{
		TMemoryComponent::TMemoryComponent(const TU16BitValue& MemorySize)
		{
			mInternalMemory.resize(MemorySize);
		}

		void TMemoryComponent::Init()
		{
			
		}

		void TMemoryComponent::Update()
		{

		}

		TMemory& TMemoryComponent::GetInternalMemory()
		{
			return mInternalMemory;
		}

		const TMemory& TMemoryComponent::GetInternalMemory() const
		{
			return mInternalMemory;
		}
	}
}
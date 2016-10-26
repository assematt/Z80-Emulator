#include "TMemoryComponent.h"

namespace TGame
{
	namespace TComponents
	{
		TMemoryComponent::TMemoryComponent()
		{
			mInternalMemory = std::make_shared<TMemory>();
		}

		TMemoryComponent::TMemoryComponent(const TU16BitValue& MemorySize)
		{
			mInternalMemory = std::make_shared<TMemory>();
			mInternalMemory->resize(MemorySize);
		}

		void TMemoryComponent::Init()
		{
			
		}

		void TMemoryComponent::Update()
		{

		}

		TU8BitValue & TMemoryComponent::operator[](const std::size_t Index)
		{
			return (*mInternalMemory)[Index];
		}

		const TU8BitValue & TMemoryComponent::operator[](const std::size_t Index) const
		{
			return (*mInternalMemory)[Index];
		}

		TMemory& TMemoryComponent::GetInternalMemory()
		{
			return *mInternalMemory;
		}

		const TMemory& TMemoryComponent::GetInternalMemory() const
		{
			return *mInternalMemory;
		}
	}
}
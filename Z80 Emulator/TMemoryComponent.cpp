#include "TMemoryComponent.h"

namespace nne
{
	namespace tcomponents
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

		void TMemoryComponent::init()
{
			
		}

		void TMemoryComponent::update()
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

		TMemory& TMemoryComponent::getInternalMemory()
		{
			return *mInternalMemory;
		}

		const TMemory& TMemoryComponent::getInternalMemory() const
		{
			return *mInternalMemory;
		}
	}
}
#include "TMemoryComponent.h"

namespace nne
{
	namespace tcomponents
	{

		TMemoryComponent::TMemoryComponent(const TU16BitValue& MemorySize)
		{
			mInternalMemory.resize(MemorySize);
		}

		void TMemoryComponent::init()
		{
			
		}

		void TMemoryComponent::update(const sf::Time& ElapsedTime)
		{

		}

		TU8BitValue & TMemoryComponent::operator[](const std::size_t Index)
		{
			return mInternalMemory[Index];
		}

		const TU8BitValue & TMemoryComponent::operator[](const std::size_t Index) const
		{
			return mInternalMemory[Index];
		}

		void TMemoryComponent::resize(const TU16BitValue& MemorySize)
		{
			mInternalMemory.resize(MemorySize);
		}

		TMemory& TMemoryComponent::getInternalMemory()
		{
			return mInternalMemory;
		}

		const TMemory& TMemoryComponent::getInternalMemory() const
		{
			return mInternalMemory;
		}
	}
}
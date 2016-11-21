#pragma once

#include "IComponent.h"
#include "TValues.h"
#include <memory>

namespace nne
{
	namespace tcomponents
	{

		class TMemoryComponent : public nne::IComponent
		{
		public:
			TMemoryComponent() = default;
			explicit TMemoryComponent(const TU16BitValue& MemorySize);

			void init() override;

			void update(const sf::Time& ElapsedTime) override;

			void refresh(const sf::Time& ElapsedTime) override {}

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

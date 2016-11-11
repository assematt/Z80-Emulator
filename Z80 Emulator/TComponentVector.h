#pragma once

#include <vector>
#include <memory>

#include "IComponent.h"
#include "TComponentHandle.h"

namespace nne
{
	class TComponentVector
	{
	public:

		using TIterator = std::vector<IComponent*>::iterator;
		using TConstIterator = std::vector<IComponent*>::const_iterator;

		/// Constructor
		TComponentVector()
		{
			mComponentVector.resize(1024);
		}

		/// Helper function for c++11 foreach use
		TIterator& begin()
		{
			return mComponentVector.begin();
		}
		TConstIterator& begin() const
		{
			return mComponentVector.cbegin();
		}

		TIterator& end()
		{
			return mComponentVector.end();
		}
		TConstIterator& end() const
		{
			return mComponentVector.cend();
		}

		/// Subscript operator to access an entity by index
		IComponent* operator[] (const int Index)
		{
			return mComponentVector[Index];
		}
		const IComponent* operator[] (const int Index) const
		{
			return mComponentVector[Index];
		}

	private:
		std::vector<IComponent*> mComponentVector;
	};
}
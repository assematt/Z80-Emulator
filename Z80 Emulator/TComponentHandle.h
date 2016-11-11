#pragma once

#include "IComponent.h"

namespace nne
{
	class TComponentHandle
	{
	public:
		TComponentHandle() :
			mIsValid(false),
			mTrackedObject(nullptr)
		{
		}

		IComponent* GetTrackedObject()
		{
			return mTrackedObject;
		}

	private:
		bool mIsValid;
		IComponent* mTrackedObject;
	};
}
#include "IComponent.h"

namespace nne
{

	IComponent::~IComponent()
	{
	}

	const TComponentID IComponent::GetComponentID() const
	{
		return mID;
	}
}
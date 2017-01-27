#include "IComponent.h"

namespace nne
{

	IComponent::~IComponent()
	{
	}

	const nne::TComponentID IComponent::getComponentID() const
	{
		return mID;
	}

	nne::TEntity* IComponent::getParent() const
	{
		return mParent;
	}

}
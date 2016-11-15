#include "TInputOutputComponent.h"

namespace nne
{
	namespace tcomponents
	{
		void TInputOutputComponent::Init()
		{
			assert(mParent->HasComponent<TPinComponent>() && "A is not equal to B");

			mPinComponent = mParent->GetComponentAsPtr<TPinComponent>();
		}

		void TInputOutputComponent::Update()
		{

		}

	}
}
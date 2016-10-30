#include "TInputOutputComponent.h"

namespace nne
{
	namespace tcomponents
	{
		void TInputOutputComponent::Init()
		{
			assert(mParent->HasComponent<TPinComponent>());

			mPinComponent = mParent->GetComponentAsPtr<TPinComponent>();
		}

		void TInputOutputComponent::Update()
		{

		}

	}
}
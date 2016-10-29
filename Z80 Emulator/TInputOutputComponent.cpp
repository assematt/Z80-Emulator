#include "TInputOutputComponent.h"

namespace TGame
{
	namespace TComponents
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
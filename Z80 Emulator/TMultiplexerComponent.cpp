#include "TMultiplexerComponent.h"

namespace TGame
{
	namespace TComponents
	{

		TGame::TComponents::TPin& TMultiplexerComponent::SelectInput(const TU8BitValue& SelectedInput)
		{
			return mPinComponent->GetPin(SelectedInput);
		}

		const TGame::TComponents::TPin& TMultiplexerComponent::SelectInput(const TU8BitValue& SelectedInput) const
		{
			return mPinComponent->GetPin(SelectedInput);
		}

		void TMultiplexerComponent::Init()
		{
			assert(mParent->HasComponent<TPinComponent>());

			mPinComponent = mParent->GetComponentAsPtr<TPinComponent>();
		}

		void TMultiplexerComponent::Update()
		{

		}

	}
}
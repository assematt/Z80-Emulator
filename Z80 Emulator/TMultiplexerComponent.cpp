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
			assert(mParentEntity->HasComponent<TPinComponent>());

			mPinComponent = mParentEntity->GetComponentAsPtr<TPinComponent>();
		}

		void TMultiplexerComponent::Update()
		{

		}

	}
}
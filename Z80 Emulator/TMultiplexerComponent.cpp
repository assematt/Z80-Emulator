#include "TMultiplexerComponent.h"

namespace nne
{
	namespace tcomponents
	{

		nne::tcomponents::TPin& TMultiplexerComponent::selectInput(const TU8BitValue& SelectedInput)
		{
			return mPinComponent->getPin(SelectedInput);
		}

		const nne::tcomponents::TPin& TMultiplexerComponent::selectInput(const TU8BitValue& SelectedInput) const
		{
			return mPinComponent->getPin(SelectedInput);
		}

		void TMultiplexerComponent::init()
		{
			assert(mParent->hasComponent<TPinComponent>());

#if ENTITY_SYSTEM == NNE
			mPinComponent = mParent->getComponentAsPtr<TPinComponent>();
#else
			mPinComponent = &(*mParent->getComponent<TPinComponent>());
#endif
		}

		void TMultiplexerComponent::update(REFRESH_UPDATE_PARAMETER)
		{

		}

	}
}
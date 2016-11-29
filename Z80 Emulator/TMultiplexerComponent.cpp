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

			mPinComponent = mParent->getComponentAsPtr<TPinComponent>();
		}

		void TMultiplexerComponent::update(const sf::Time& ElapsedTime)
		{

		}

	}
}
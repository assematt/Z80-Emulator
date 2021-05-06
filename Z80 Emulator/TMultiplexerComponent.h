#pragma once

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include "TPinComponent.h"
#include INCLUDE_ENTITY_CLASS
#include <assert.h>

namespace nne
{
	namespace tcomponents
	{
		class TMultiplexerComponent : BASE_COMPONENT_CLASS
		{
		public:
			tcomponents::TPin& selectInput(const TU8BitValue& SelectedInput);
			const tcomponents::TPin& selectInput(const TU8BitValue& SelectedInput) const;

			void init() override;

			void update(REFRESH_UPDATE_PARAMETER) override;

			void refresh(REFRESH_UPDATE_PARAMETER) override {}

		private:
			TPinComponent*	mPinComponent;
		};
	}
}

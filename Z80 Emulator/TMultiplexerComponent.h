#pragma once


#include "IComponent.h"
#include "TPinComponent.h"
#include "TEntity.h"
#include "TValues.h"
#include <assert.h>

namespace nne
{
	namespace tcomponents
	{
		struct TMultiplexerComponent : nne::IComponent
		{
		public:
			tcomponents::TPin& selectInput(const TU8BitValue& SelectedInput);
			const tcomponents::TPin& selectInput(const TU8BitValue& SelectedInput) const;

			void init() override;

			void update() override;

			void refresh() override {}

		private:
			std::shared_ptr<TPinComponent> mPinComponent;
		};
	}
}

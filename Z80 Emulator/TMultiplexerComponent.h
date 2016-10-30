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
			tcomponents::TPin& SelectInput(const TU8BitValue& SelectedInput);
			const tcomponents::TPin& SelectInput(const TU8BitValue& SelectedInput) const;

			void Init() override;

			void Update() override;

		private:
			std::shared_ptr<TPinComponent> mPinComponent;
		};
	}
}

#pragma once


#include "IComponent.h"
#include "TPinComponent.h"
#include "TEntity.h"
#include "TValues.h"
#include <assert.h>

namespace TGame
{
	namespace TComponents
	{
		struct TMultiplexerComponent : TInternals::IComponent
		{
		public:
			TComponents::TPin& SelectInput(const TU8BitValue& SelectedInput);
			const TComponents::TPin& SelectInput(const TU8BitValue& SelectedInput) const;

			void Init();

			void Update();

		private:
			std::shared_ptr<TPinComponent> mPinComponent;
		};
	}
}

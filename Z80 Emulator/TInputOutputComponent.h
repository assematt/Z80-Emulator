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
		struct TInputOutputComponent : TInternals::IComponent
		{
		public:

			template <class T>
			T& ComputeOutput();

			void Init();

			void Update();

		private:
			TU8BitValue mNumberOfInputs;
			TU8BitValue mNumberOfOutput;
			std::shared_ptr<TPinComponent> mPinComponent;
		};

		template <class T>
		T& TInputOutputComponent::ComputeOutput()
		{
			return T();
		}

	}
}
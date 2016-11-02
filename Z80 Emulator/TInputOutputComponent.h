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
		struct TInputOutputComponent : nne::IComponent
		{
		public:

			template <class T>
			T& ComputeOutput();

			void Init() override;

			void Update() override;

			void Refresh() override {}

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
#pragma once

#include "IComponent.h"
#include "TPin.h"
#include "TValues.h"


namespace nne
{
	namespace tcomponents
	{
		struct TLogicGateComponent : nne::IComponent
		{
		public:

			enum class TOperation : TU8BitValue
			{
				OR,
				AND,
				NOT,
				NAND,
				NOR,
				XOR,
				XNOR
			};

			TPin::TStatus PerformInstruction(const TPin::TStatus& LeftPin, const TPin::TStatus& RightPin, const TOperation& Operation);

			void Init() override;

			void Update() override;

			void Refresh() override {}


		private:
			
		};
	}
}

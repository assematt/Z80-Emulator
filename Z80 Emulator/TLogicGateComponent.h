#pragma once

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include "TPin.h"

namespace nne
{
	namespace tcomponents
	{
		class TLogicGateComponent : BASE_COMPONENT_CLASS
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

			TLogicGateComponent(const TOperation& Mode = TOperation::NAND);


			void init() override;

			void update(REFRESH_UPDATE_PARAMETER) override;

			void refresh(REFRESH_UPDATE_PARAMETER) override;

			/// Perform the logic operation specified by the "Operation" value between the 2 specified PINs
			TPin::TStatus performInstruction(const TPin::TStatus& LeftPin, const TPin::TStatus& RightPin, const TOperation& Operation);

		private:
			TOperation mOperationMode;
		};
	}
}

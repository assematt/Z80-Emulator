#pragma once

#include "IComponent.h"
#include "TPin.h"
#include "TValues.h"


namespace TGame
{
	namespace TComponents
	{
		struct TLogicGateComponent : TInternals::IComponent
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

			void Init();

			void Update();

		private:
			
		};
	}
}

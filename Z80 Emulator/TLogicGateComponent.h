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

			TLogicGateComponent(const TOperation& Mode = TOperation::NAND);


			void init() override;

			void update(const sf::Time& ElapsedTime) override;

			void refresh(const sf::Time& ElapsedTime) override;

			/// Perform the logic operation specified by the "Operation" value between the 2 specified PINs
			TPin::TStatus performInstruction(const TPin::TStatus& LeftPin, const TPin::TStatus& RightPin, const TOperation& Operation);

		private:
			TOperation mOperationMode;
		};
	}
}

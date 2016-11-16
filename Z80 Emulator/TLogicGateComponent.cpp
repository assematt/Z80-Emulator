#include "TLogicGateComponent.h"

namespace nne
{
	namespace tcomponents
	{

		nne::tcomponents::TPin::TStatus TLogicGateComponent::performInstruction(const TPin::TStatus& LeftPin, const TPin::TStatus& RightPin, const TOperation& Operation)
		{
			switch (Operation)
			{
			case TOperation::OR:	return logicOr(LeftPin, RightPin);
			case TOperation::AND:	return logicAnd(LeftPin, RightPin);
			case TOperation::NOT:	return logicNot(LeftPin);
			case TOperation::NAND:	return logicNand(LeftPin, RightPin);
			case TOperation::NOR:	return logicNor(LeftPin, RightPin);
			case TOperation::XOR:	return logicXor(LeftPin, RightPin);
			case TOperation::XNOR:	return logicXnor(LeftPin, RightPin);
			}
		}

		void TLogicGateComponent::init()
{

		}

		void TLogicGateComponent::update()
{
			
		}

	}
}
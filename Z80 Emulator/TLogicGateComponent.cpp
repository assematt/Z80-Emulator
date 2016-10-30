#include "TLogicGateComponent.h"

namespace nne
{
	namespace tcomponents
	{

		nne::tcomponents::TPin::TStatus TLogicGateComponent::PerformInstruction(const TPin::TStatus& LeftPin, const TPin::TStatus& RightPin, const TOperation& Operation)
		{
			switch (Operation)
			{
			case TOperation::OR:	return LogicOr(LeftPin, RightPin);
			case TOperation::AND:	return LogicAnd(LeftPin, RightPin);
			case TOperation::NOT:	return LogicNot(LeftPin);
			case TOperation::NAND:	return LogicNand(LeftPin, RightPin);
			case TOperation::NOR:	return LogicNor(LeftPin, RightPin);
			case TOperation::XOR:	return LogicXor(LeftPin, RightPin);
			case TOperation::XNOR:	return LogicXnor(LeftPin, RightPin);
			}
		}

		void TLogicGateComponent::Init()
		{

		}

		void TLogicGateComponent::Update()
		{
			
		}

	}
}
#include "TLogicGateComponent.h"

#include "TPinComponent.h"
#include "TPackageComponent.h"

namespace nne
{
	namespace tcomponents
	{

		TLogicGateComponent::TLogicGateComponent(const TOperation& Mode /*= TOperation::NAND*/) :
			mOperationMode(TOperation::NAND)
		{
		}

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
			// Setup the CPU Pins
			auto& PinComponent = *mParent->getComponentAsPtr<TPinComponent>();
			PinComponent.setupPins(std::initializer_list<tcomponents::TPin>{

				//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber

				// ADDRESS BUS
				{ tcomponents::TPin::TMode::INPUT, "1A", tcomponents::TPin::TStatus::LOW,  1 }, // 1A
				{ tcomponents::TPin::TMode::INPUT, "1B", tcomponents::TPin::TStatus::LOW,  2 }, // 1B
				{ tcomponents::TPin::TMode::OUTPUT, "1Y", tcomponents::TPin::TStatus::LOW, 3 }, // 1Y

				{ tcomponents::TPin::TMode::INPUT, "2A", tcomponents::TPin::TStatus::LOW,  4 }, // 2A
				{ tcomponents::TPin::TMode::INPUT, "2B", tcomponents::TPin::TStatus::LOW,  5 }, // 2B
				{ tcomponents::TPin::TMode::OUTPUT, "2Y", tcomponents::TPin::TStatus::LOW, 6 }, // 2Y

				{ tcomponents::TPin::TMode::INPUT, "3A", tcomponents::TPin::TStatus::LOW,  9 }, // 3A
				{ tcomponents::TPin::TMode::INPUT, "3B", tcomponents::TPin::TStatus::LOW, 10 },// 3B
				{ tcomponents::TPin::TMode::OUTPUT, "3Y", tcomponents::TPin::TStatus::LOW, 8 },	// 3Y

				{ tcomponents::TPin::TMode::INPUT, "4A", tcomponents::TPin::TStatus::LOW,  12 }, // 4A
				{ tcomponents::TPin::TMode::INPUT, "4B", tcomponents::TPin::TStatus::LOW,  13 }, // 4B
				{ tcomponents::TPin::TMode::OUTPUT, "4Y", tcomponents::TPin::TStatus::LOW, 11 }, // 4Y

				{ tcomponents::TPin::TMode::INPUT, "VCC", tcomponents::TPin::TStatus::LOW, 14 }, // VCC
				{ tcomponents::TPin::TMode::INPUT, "GND", tcomponents::TPin::TStatus::LOW,  7 },	// GND

			}, 14);
		}

		void TLogicGateComponent::update(const sf::Time& ElapsedTime)
		{
			
		}

		void TLogicGateComponent::refresh(const sf::Time& ElapsedTime)
		{
			// Skip the cycle if the chip isn't powered ON
			if (!mParent->getComponent<TPackageComponent>().isPoweredOn())
				return;

			// Get a ref of the TPinComponent
			auto& PinComponent = mParent->getComponent<TPinComponent>();

			// Execute operation on the first set if both the input are connected to something
			{
				const auto& Input1 = PinComponent.getPin(1);
				const auto& Input2 = PinComponent.getPin(2);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(3).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
			}

			// Execute operation on the second set
			{
				const auto& Input1 = PinComponent.getPin(4);
				const auto& Input2 = PinComponent.getPin(5);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(6).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
			}

			// Execute operation on the third set
			{
				const auto& Input1 = PinComponent.getPin(9);
				const auto& Input2 = PinComponent.getPin(10);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(8).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
			}

			// Execute operation on the fourth set
			{
				const auto& Input1 = PinComponent.getPin(12);
				const auto& Input2 = PinComponent.getPin(13);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(11).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
			}
		}

	}
}
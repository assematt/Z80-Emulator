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
#if ENTITY_SYSTEM == NNE
			auto PinComponent = mParent->getComponentAsPtr<TPinComponent>();
#else
			auto& PinComponent = mParent->getComponent<TPinComponent>();
#endif

			PinComponent->setupPins(std::initializer_list<tcomponents::TPin>{

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

		void TLogicGateComponent::update(REFRESH_UPDATE_PARAMETER)
		{
			
		}

		void TLogicGateComponent::refresh(REFRESH_UPDATE_PARAMETER)
		{
			// Skip the cycle if the chip isn't powered ON
#if ENTITY_SYSTEM == NNE
			if (!mParent->getComponent<TPackageComponent>().isPoweredOn())
				return;
#else
			if (!mParent->getComponent<TPackageComponent>()->isPoweredOn())
				return;
#endif

			// Get a ref of the TPinComponent
#if ENTITY_SYSTEM == NNE
			auto& PinComponent = mParent->getComponent<TPinComponent>();
#else
			auto& PinComponent = mParent->getComponent<TPinComponent>();
#endif

			// Execute operation on the first set if both the input are connected to something
			{
#if ENTITY_SYSTEM == NNE
				const auto& Input1 = PinComponent.getPin(1);
				const auto& Input2 = PinComponent.getPin(2);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(3).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#else
				const auto& Input1 = PinComponent->getPin(1);
				const auto& Input2 = PinComponent->getPin(2);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent->getPin(3).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#endif
			}

			// Execute operation on the second set
			{
#if ENTITY_SYSTEM == NNE
				const auto& Input1 = PinComponent.getPin(4);
				const auto& Input2 = PinComponent.getPin(5);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(6).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#else
				const auto& Input1 = PinComponent->getPin(4);
				const auto& Input2 = PinComponent->getPin(5);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent->getPin(6).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#endif
			}

			// Execute operation on the third set
			{
#if ENTITY_SYSTEM == NNE
				const auto& Input1 = PinComponent.getPin(9);
				const auto& Input2 = PinComponent.getPin(10);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(8).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#else
				const auto& Input1 = PinComponent->getPin(9);
				const auto& Input2 = PinComponent->getPin(10);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent->getPin(8).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#endif
			}

			// Execute operation on the fourth set
			{
#if ENTITY_SYSTEM == NNE
				const auto& Input1 = PinComponent.getPin(12);
				const auto& Input2 = PinComponent.getPin(13);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent.getPin(11).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#else
				const auto& Input1 = PinComponent->getPin(12);
				const auto& Input2 = PinComponent->getPin(13);
				if (Input1.hasConnections() && Input2.hasConnections())
					PinComponent->getPin(11).changePinStatus(performInstruction(Input1, Input2, mOperationMode));
#endif
			}
		}

	}
}
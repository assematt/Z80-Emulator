#include "TRam.h"

namespace TGame
{
	namespace TModules
	{

		TRam::TRam(const TU16BitValue& MemorySize)
		{

			AddComponent<TComponents::TPinComponent>(std::initializer_list<TComponents::TPin>{
				// ADDRESS BUS
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 10, TRamPinGroup::AddressBus, 0 }, // A0
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  9, TRamPinGroup::AddressBus, 1 }, // A1
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  8, TRamPinGroup::AddressBus, 2 }, // A2
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  7, TRamPinGroup::AddressBus, 3 }, // A3
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  6, TRamPinGroup::AddressBus, 4 }, // A4
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  5, TRamPinGroup::AddressBus, 5 }, // A5
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  4, TRamPinGroup::AddressBus, 6 }, // A6
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  3, TRamPinGroup::AddressBus, 7 }, // A7
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 25, TRamPinGroup::AddressBus, 8 }, // A8
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 24, TRamPinGroup::AddressBus, 9 }, // A9
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 21, TRamPinGroup::AddressBus, 10 }, // A10
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 23, TRamPinGroup::AddressBus, 11 }, // A11
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  2, TRamPinGroup::AddressBus, 12 }, // A12
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 26, TRamPinGroup::AddressBus, 13 }, // A13
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  1, TRamPinGroup::AddressBus, 14 }, // A14

				// DATA BUS
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 11, TRamPinGroup::DataBus, 0 }, // D0
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 12, TRamPinGroup::DataBus, 1 }, // D1
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 13, TRamPinGroup::DataBus, 2 }, // D2
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 15, TRamPinGroup::DataBus, 3 }, // D3
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 16, TRamPinGroup::DataBus, 4 }, // D4
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 17, TRamPinGroup::DataBus, 5 }, // D5
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 18, TRamPinGroup::DataBus, 6 }, // D6
				{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 19, TRamPinGroup::DataBus, 7 }, // D7

				// CHIP CONTROL
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 20, TRamPinGroup::ChipControl }, // CE
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 22, TRamPinGroup::ChipControl }, // OE 
				{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW, 27, TRamPinGroup::ChipControl }, // WE 

				// Others
				{ TComponents::TPin::TMode::POWER, TComponents::TPin::TStatus::LOW, 28, TRamPinGroup::Others }, // VCC
				{ TComponents::TPin::TMode::POWER, TComponents::TPin::TStatus::LOW, 14, TRamPinGroup::Others }, // GND
			}, 28);
			AddComponent<TComponents::TMemoryComponent>(MemorySize);
			InitComponents();

			// Connects the 
		}

	}
}
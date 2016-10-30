#include "TRam.h"

namespace nne
{
	namespace tmodules
	{

		TRam::TRam(const TU16BitValue& MemorySize) :
			mMemorySize(mMemorySize)
		{
		}

		TRam::TRam() :
			mMemorySize(65535)
		{
		}

		void TRam::Update()
		{
			RefreshMemory();
		}

		TMemory::iterator& TRam::begin()
		{
			return GetInternalMemory().begin();
		}

		TMemory::iterator& TRam::end()
		{
			return GetInternalMemory().end();
		}

		TU8BitValue& TRam::operator[](const std::size_t Index)
		{
			return GetInternalMemory()[Index];
		}

		const TU8BitValue& TRam::operator[](const std::size_t Index) const
		{
			return GetInternalMemory()[Index];
		}

		TMemory& TRam::GetInternalMemory()
		{
			return GetComponentAsPtr<tcomponents::TMemoryComponent>()->GetInternalMemory();
		}

		const TMemory& TRam::GetInternalMemory() const
		{
			return GetComponentAsPtr<tcomponents::TMemoryComponent>()->GetInternalMemory();
		}

		void TRam::Init()
		{
			AddComponent<tcomponents::TPinComponent>(std::initializer_list<tcomponents::TPin>{
				// ADDRESS BUS
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW, 10, TRamPinGroup::AddressBus, 0 }, // A0
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  9, TRamPinGroup::AddressBus, 1 }, // A1
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  8, TRamPinGroup::AddressBus, 2 }, // A2
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  7, TRamPinGroup::AddressBus, 3 }, // A3
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  6, TRamPinGroup::AddressBus, 4 }, // A4
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  5, TRamPinGroup::AddressBus, 5 }, // A5
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  4, TRamPinGroup::AddressBus, 6 }, // A6
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  3, TRamPinGroup::AddressBus, 7 }, // A7
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW, 25, TRamPinGroup::AddressBus, 8 }, // A8
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW, 24, TRamPinGroup::AddressBus, 9 }, // A9
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW, 21, TRamPinGroup::AddressBus, 10 }, // A10
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW, 23, TRamPinGroup::AddressBus, 11 }, // A11
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  2, TRamPinGroup::AddressBus, 12 }, // A12
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW, 26, TRamPinGroup::AddressBus, 13 }, // A13
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  1, TRamPinGroup::AddressBus, 14 }, // A14

				// DATA BUS
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 11, TRamPinGroup::DataBus, 0 }, // D0
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 12, TRamPinGroup::DataBus, 1 }, // D1
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 13, TRamPinGroup::DataBus, 2 }, // D2
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 15, TRamPinGroup::DataBus, 3 }, // D3
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 16, TRamPinGroup::DataBus, 4 }, // D4
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 17, TRamPinGroup::DataBus, 5 }, // D5
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 18, TRamPinGroup::DataBus, 6 }, // D6
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 19, TRamPinGroup::DataBus, 7 }, // D7

				// CHIP CONTROL
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::HIGH, 20, TRamPinGroup::ChipControl }, // CE
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::HIGH, 22, TRamPinGroup::ChipControl }, // OE 
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::HIGH, 27, TRamPinGroup::ChipControl }, // WE 

				// Others
				{ tcomponents::TPin::TMode::POWER, tcomponents::TPin::TStatus::LOW, 28, TRamPinGroup::Others }, // VCC
				{ tcomponents::TPin::TMode::POWER, tcomponents::TPin::TStatus::LOW, 14, TRamPinGroup::Others }, // GND
			}, 28);
			AddComponent<tcomponents::TMemoryComponent>(mMemorySize);
			InitComponents();

			// Cache the status of some pins for easy access during the program life time
			auto& PinComponent = GetComponentAsPtr<tcomponents::TPinComponent>();
			
			mChipEnablePin = &(PinComponent->GetPin(20));
			mWritePin = &(PinComponent->GetPin(27));
			mOutputEnable = &(PinComponent->GetPin(22));
		}

		void TRam::Refresh()
		{
			RefreshMemory();
		}

		void TRam::RefreshMemory()
		{
			// Check if the chip is disabled (this one is disabled on high)
			if (*mChipEnablePin == tcomponents::TPin::HIGH)
				return;

			// Check if the output is disabled (this one is disabled on high)
			if (*mOutputEnable == tcomponents::TPin::HIGH)
				return;

			// If we arrive at this point we are sure we are performing a read/write operation

			// Get a ref to the pin component
			auto& PinComponent = *GetComponentAsPtr<tcomponents::TPinComponent>();

			// Get a ref to the memory component
			auto& MemoryComponent = *GetComponentAsPtr<tcomponents::TMemoryComponent>();

			// Read the data on the address bus to figure it where we are writing/reading the data
			//TU16BitValue MemoryAddress = PinComponent.PinToTU16BitValue(TRamPinGroup::AddressBus);
			TU16BitValue MemoryAddress = PinComponent.PinsToValue<TU16BitValue>(TRamPinGroup::AddressBus);

			// Reads the data that we want to write/read to the ram
			//TU16BitValue Data = PinComponent.PinToTU8BitValue(TRamPinGroup::DataBus);
			TU16BitValue Data = PinComponent.PinsToValue<TU8BitValue>(TRamPinGroup::DataBus);

			// Check if we are reading data from the ram
			if (*mWritePin == tcomponents::TPin::HIGH)
			{
				// Writes the data into the ram
				PinComponent.ValueToPins<TU8BitValue>(MemoryComponent[MemoryAddress], TRamPinGroup::DataBus);
			}
			// If we got here it means we are writing to the ram
			else
			{
				MemoryComponent[MemoryAddress] = Data;
			}
		}

	}
}
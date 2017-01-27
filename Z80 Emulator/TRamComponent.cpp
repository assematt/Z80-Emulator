#include "TRamComponent.h"

#include "TPackageComponent.h"

namespace nne
{
	namespace tcomponents
	{
		TRamComponent::TRamComponent(const TU16BitValue& MemorySize) :
			mMemorySize(mMemorySize)
		{
		}

		TRamComponent::TRamComponent() :
			mMemorySize(65535)
		{
		}

		void TRamComponent::update(const sf::Time& ElapsedTime)
		{
			if (!mParent->getComponent<TPackageComponent>().isPoweredOn())
				return;

			refreshMemory();
		}

		TMemory::iterator& TRamComponent::begin()
		{
			return getInternalMemory().begin();
		}

		TMemory::iterator& TRamComponent::end()
		{
			return getInternalMemory().end();
		}

		TU8BitValue& TRamComponent::operator[](const std::size_t Index)
		{
			return getInternalMemory()[Index];
		}

		const TU8BitValue& TRamComponent::operator[](const std::size_t Index) const
		{
			return getInternalMemory()[Index];
		}

		TMemory& TRamComponent::getInternalMemory()
		{
			return mMemoryComponent->getInternalMemory();
		}

		const TMemory& TRamComponent::getInternalMemory() const
		{
			return mMemoryComponent->getInternalMemory();
		}

		void TRamComponent::init()
		{
			// Cache the memory component
			mMemoryComponent = mParent->getComponentAsPtr<TMemoryComponent>();
			mMemoryComponent->resize(mMemorySize);

			// Get a ref to the pin component
			auto PinComponent = mParent->getComponentAsPtr<TPinComponent>();

			// Setup the RAM pins
			PinComponent->setupPins(std::initializer_list<tcomponents::TPin>{

				//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber

				// ADDRESS BUS
				{ tcomponents::TPin::TMode::INPUT, "A0",  tcomponents::TPin::TStatus::LOW, 10, TRamPinGroup::AddressBus, 0 }, // A0
				{ tcomponents::TPin::TMode::INPUT, "A1",  tcomponents::TPin::TStatus::LOW,  9, TRamPinGroup::AddressBus, 1 }, // A1
				{ tcomponents::TPin::TMode::INPUT, "A2",  tcomponents::TPin::TStatus::LOW,  8, TRamPinGroup::AddressBus, 2 }, // A2
				{ tcomponents::TPin::TMode::INPUT, "A3",  tcomponents::TPin::TStatus::LOW,  7, TRamPinGroup::AddressBus, 3 }, // A3
				{ tcomponents::TPin::TMode::INPUT, "A4",  tcomponents::TPin::TStatus::LOW,  6, TRamPinGroup::AddressBus, 4 }, // A4
				{ tcomponents::TPin::TMode::INPUT, "A5",  tcomponents::TPin::TStatus::LOW,  5, TRamPinGroup::AddressBus, 5 }, // A5
				{ tcomponents::TPin::TMode::INPUT, "A6",  tcomponents::TPin::TStatus::LOW,  4, TRamPinGroup::AddressBus, 6 }, // A6
				{ tcomponents::TPin::TMode::INPUT, "A7",  tcomponents::TPin::TStatus::LOW,  3, TRamPinGroup::AddressBus, 7 }, // A7
				{ tcomponents::TPin::TMode::INPUT, "A8",  tcomponents::TPin::TStatus::LOW, 25, TRamPinGroup::AddressBus, 8 }, // A8
				{ tcomponents::TPin::TMode::INPUT, "A9",  tcomponents::TPin::TStatus::LOW, 24, TRamPinGroup::AddressBus, 9 }, // A9
				{ tcomponents::TPin::TMode::INPUT, "A10", tcomponents::TPin::TStatus::LOW, 21, TRamPinGroup::AddressBus, 10 }, // A10
				{ tcomponents::TPin::TMode::INPUT, "A11", tcomponents::TPin::TStatus::LOW, 23, TRamPinGroup::AddressBus, 11 }, // A11
				{ tcomponents::TPin::TMode::INPUT, "A12", tcomponents::TPin::TStatus::LOW,  2, TRamPinGroup::AddressBus, 12 }, // A12
				{ tcomponents::TPin::TMode::INPUT, "A13", tcomponents::TPin::TStatus::LOW, 26, TRamPinGroup::AddressBus, 13 }, // A13
				{ tcomponents::TPin::TMode::INPUT, "A14", tcomponents::TPin::TStatus::LOW,  1, TRamPinGroup::AddressBus, 14 }, // A14

				// DATA BUS
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D0", tcomponents::TPin::TStatus::LOW, 11, TRamPinGroup::DataBus, 0 }, // D0
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D1", tcomponents::TPin::TStatus::LOW, 12, TRamPinGroup::DataBus, 1 }, // D1
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D2", tcomponents::TPin::TStatus::LOW, 13, TRamPinGroup::DataBus, 2 }, // D2
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D3", tcomponents::TPin::TStatus::LOW, 15, TRamPinGroup::DataBus, 3 }, // D3
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D4", tcomponents::TPin::TStatus::LOW, 16, TRamPinGroup::DataBus, 4 }, // D4
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D5", tcomponents::TPin::TStatus::LOW, 17, TRamPinGroup::DataBus, 5 }, // D5
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D6", tcomponents::TPin::TStatus::LOW, 18, TRamPinGroup::DataBus, 6 }, // D6
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D7", tcomponents::TPin::TStatus::LOW, 19, TRamPinGroup::DataBus, 7 }, // D7

				// CHIP CONTROL
				{ tcomponents::TPin::TMode::INPUT, "CE", tcomponents::TPin::TStatus::HIGH, 20, TRamPinGroup::ChipControl }, // CE
				{ tcomponents::TPin::TMode::INPUT, "OE", tcomponents::TPin::TStatus::HIGH, 22, TRamPinGroup::ChipControl }, // OE 
				{ tcomponents::TPin::TMode::INPUT, "WE", tcomponents::TPin::TStatus::HIGH, 27, TRamPinGroup::ChipControl }, // WE 

				// Others
				{ tcomponents::TPin::TMode::INPUT, "VCC", tcomponents::TPin::TStatus::LOW, 28, TRamPinGroup::Others }, // VCC
				{ tcomponents::TPin::TMode::INPUT, "GND", tcomponents::TPin::TStatus::LOW, 14, TRamPinGroup::Others }, // GND
			}, 28);

			// Cache some pins
			mChipEnablePin = &(PinComponent->getPin(20));
			mWritePin = &(PinComponent->getPin(27));
			mOutputEnable = &(PinComponent->getPin(22));
		}

		void TRamComponent::refresh(const sf::Time& ElapsedTime)
		{
			if (!mParent->getComponent<TPackageComponent>().isPoweredOn())
				return;

			refreshMemory();
		}

		void TRamComponent::refreshMemory()
		{
			// Check if the chip is disabled (this one is disabled on high)
			if (*mChipEnablePin == tcomponents::TPin::HIGH)
				return;

			// Check if the output is disabled (this one is disabled on high)
			if (*mOutputEnable == tcomponents::TPin::HIGH)
				return;

			// If we arrive at this point we are sure we are performing a read/write operation

			// Get a ref to the pin component
			auto& PinComponent = *mParent->getComponentAsPtr<TPinComponent>();

			// Get a ref to the memory component
			auto& MemoryComponent = *mMemoryComponent;

			// Read the data on the address bus to figure it where we are writing/reading the data
			TU16BitValue MemoryAddress = PinComponent.pinsToValue<TU16BitValue>(TRamPinGroup::AddressBus);

			// Reads the data that we want to write/read to the ram
			TU8BitValue Data = PinComponent.pinsToValue<TU8BitValue>(TRamPinGroup::DataBus);

			// Check if we are reading data from the ram
			if (*mWritePin == tcomponents::TPin::HIGH)
			{
				// Writes the data into the ram
				PinComponent.valueToPins<TU8BitValue>(MemoryComponent[MemoryAddress], TRamPinGroup::DataBus);
			}
			// If we got here it means we are writing to the ram
			else
			{
				MemoryComponent[MemoryAddress] = Data;
			}
		}
	}
}
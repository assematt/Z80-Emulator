#include "TDebugger.h"

namespace nne
{
	TDebugger::TDebugger()
	{
		// Get console handle
		mConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
		/* Save current attributes */
		GetConsoleScreenBufferInfo(mConsoleHandle, &mConsoleInfo);
		mSavedAttributes = mConsoleInfo.wAttributes;
	}
	
	void TDebugger::clearWindow()
	{
		// clear console
		system("cls");
	}
	
	void TDebugger::showDebugWindow(const TRegisterContainer& Registers, const TMemory* Memory, const TU8BitValue& DataBus, const TU16BitValue& AddressBus, const nne::TClock& Clock)
	{
		// clear console
		clearWindow();
	
		// Show title
		std::cout << "Test Z80 Emulator" << std::endl << std::endl;
	
		// Show registers content
		showRegistersValue(Registers);
	
		// Print flags
		showFlags(Registers.flags());

		// Show data bus
		showDataBus(DataBus);

		// Show address bus
		showAddressBus(AddressBus);
	
		// Show program memory
		if (Memory)
			showProgramMemory(Registers.programCounter(), *Memory);

		// Show timing
		showTiming(Clock);

	}
	
	void TDebugger::showProgramMemory(const nne::T16BitRegister& ProgramCounter, const TMemory& Memory)
	{
		// Add an additional black row on top
		std::cout << std::endl << std::endl;
	
		// Set up how many row and column we want to display
		const int Row = 5;
		const int Column = 20;
	
		// The page (how much memory we show is based on the number or row and column)
		int Page = Row * Column;
	
		int Start = (ProgramCounter - Page) < 0 ? 0 : ProgramCounter;
	
		int TempColumn = 0;
		for (auto Index = Start; Index < Start + Page; ++Index)
		{
			if (Index == ProgramCounter)
			{
				SetConsoleTextAttribute(mConsoleHandle, FOREGROUND_RED);
			}
	
			printf("%02X ", Memory[Index]);
	
			SetConsoleTextAttribute(mConsoleHandle, mSavedAttributes);
	
			if (++TempColumn > Column - 1)
			{
				printf("\n");
				TempColumn = 0;
			}
		}
	}
	
	void TDebugger::showFlags(const nne::T8BitRegister& FlagRegister)
	{
		if (nne::TUtility::getBit(FlagRegister, TFlags::C) == 1)
		{
			SetConsoleTextAttribute(mConsoleHandle, FOREGROUND_RED);
		}
	
		printf("C ");
		SetConsoleTextAttribute(mConsoleHandle, mSavedAttributes);
	
		if (nne::TUtility::getBit(FlagRegister, TFlags::H) == 1)
		{
			SetConsoleTextAttribute(mConsoleHandle, FOREGROUND_RED);
		}
	
		printf("H ");
		SetConsoleTextAttribute(mConsoleHandle, mSavedAttributes);
	
		if (nne::TUtility::getBit(FlagRegister, TFlags::N) == 1)
		{
			SetConsoleTextAttribute(mConsoleHandle, FOREGROUND_RED);
		}
	
		printf("N ");
		SetConsoleTextAttribute(mConsoleHandle, mSavedAttributes);
	
		if (nne::TUtility::getBit(FlagRegister, TFlags::P_V) == 1)
		{
			SetConsoleTextAttribute(mConsoleHandle, FOREGROUND_RED);
		}
	
		printf("P_V ");
		SetConsoleTextAttribute(mConsoleHandle, mSavedAttributes);
	
		if (nne::TUtility::getBit(FlagRegister, TFlags::S) == 1)
		{
			SetConsoleTextAttribute(mConsoleHandle, FOREGROUND_RED);
		}
	
		printf("S ");
		SetConsoleTextAttribute(mConsoleHandle, mSavedAttributes);
	
		if (nne::TUtility::getBit(FlagRegister, TFlags::Z) == 1)
		{
			SetConsoleTextAttribute(mConsoleHandle, FOREGROUND_RED);
		}
	
		printf("Z ");
		SetConsoleTextAttribute(mConsoleHandle, mSavedAttributes);
	}
	
	void TDebugger::showRegistersValue(const TRegisterContainer& Registers)
	{
		std::cout << "Registers: " << std::endl;

		printf("A = %02X, B = %02X %8c | %8c PC = %04X, SP = %04X  \n",
			Registers.getRegister<nne::T8BitRegister>(TRegisterType::A).getInternalValue(), Registers.getRegister<nne::T8BitRegister>(TRegisterType::B).getInternalValue(), ' ', ' ',
			Registers.getRegister<nne::T16BitRegister>(TRegisterType::PC).getInternalValue(), Registers.getRegister<nne::T16BitRegister>(TRegisterType::SP).getInternalValue());
		printf("C = %02X, D = %02X %8c | %8c IX = %04X, IY = %04X  \n",
			Registers.getRegister<nne::T8BitRegister>(TRegisterType::C).getInternalValue(), Registers.getRegister<nne::T8BitRegister>(TRegisterType::D).getInternalValue(), ' ', ' ',
			Registers.getRegister<nne::T16BitRegister>(TRegisterType::IX).getInternalValue(), Registers.getRegister<nne::T16BitRegister>(TRegisterType::IY).getInternalValue());
		printf("E = %02X, F = %02X %8c | %8c Flags: \n", Registers.getRegister<nne::T8BitRegister>(TRegisterType::E).getInternalValue(), Registers.getRegister<nne::T8BitRegister>(TRegisterType::F).getInternalValue(), ' ', ' ');
		printf("H = %02X, L = %02X %8c | %8c ", Registers.getRegister<nne::T8BitRegister>(TRegisterType::H).getInternalValue(), Registers.getRegister<nne::T8BitRegister>(TRegisterType::L).getInternalValue(), ' ', ' ');


	}

	void TDebugger::showTiming(const nne::TClock& Clock)
	{
		std::cout << std::endl << Clock.getDuration().asSeconds() << std::endl;
	}

	void TDebugger::showDataBus(const TU8BitValue & Value)
	{
		std::cout << std::endl;

		printf("Data bus: %02X %10c | %8c ", Value, ' ', ' ');
	}

	void TDebugger::showAddressBus(const TU16BitValue& Value)
	{
		//std::cout << std::endl;

		printf("Address bus: %04X \n", Value);
	}

}

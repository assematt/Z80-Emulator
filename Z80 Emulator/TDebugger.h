#pragma once

#include <windows.h> 
#include <iostream>
#include <chrono>

#include "TAlu.h"
#include "TClock.h"

namespace nne
{
	class TDebugger
	{
	public:
		TDebugger();

		void ClearWindow();

		void ShowDebugWindow(const TRegisterContainer& Registers, const TMemory* Memory, const TU8BitValue& DataBus, const TU16BitValue& AddressBus, const nne::TClock& Clock);

	private:

		void ShowProgramMemory(const nne::T16BitRegister& ProgramCounter, const TMemory& Memory);

		void ShowFlags(const nne::T8BitRegister& FlagRegister);

		void ShowRegistersValue(const TRegisterContainer& Registers);

		void ShowTiming(const nne::TClock& Clock);

		void ShowDataBus(const TU8BitValue& Value);

		void ShowAddressBus(const TU16BitValue& Value);

	private:
		HANDLE mConsoleHandle;
		CONSOLE_SCREEN_BUFFER_INFO mConsoleInfo;
		WORD mSavedAttributes;
	};
}

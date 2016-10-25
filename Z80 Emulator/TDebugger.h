#pragma once

#include <windows.h> 
#include <iostream>
#include <chrono>

#include "TAlu.h"
#include "TClock.h"

namespace TGame
{
	class TDebugger
	{
	public:
		TDebugger();

		void ClearWindow();

		void ShowDebugWindow(const TRegisterContainer& Registers, const TMemory* Memory, const TU8BitValue& DataBus, const TU8BitValue& AddressBus, const TInternals::TClock& Clock);

	private:

		void ShowProgramMemory(const TInternals::T16BitRegister& ProgramCounter, const TMemory& Memory);

		void ShowFlags(const TInternals::T8BitRegister& FlagRegister);

		void ShowRegistersValue(const TRegisterContainer& Registers);

		void ShowTiming(const TInternals::TClock& Clock);

		void ShowDataBus(const TU8BitValue& Value);

		void ShowAddressBus(const TU16BitValue& Value);

	private:
		HANDLE mConsoleHandle;
		CONSOLE_SCREEN_BUFFER_INFO mConsoleInfo;
		WORD mSavedAttributes;
	};
}

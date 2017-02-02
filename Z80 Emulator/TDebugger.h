#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>
#include <unordered_set>
#include <windows.h>
#include <iostream>
#include <chrono>

#include "TAlu.h"
#include "TClock.h"
#include "TInstructions.h"
#include "TCacheManager.h"

namespace nne
{
	
	class TDebugger
	{
	public:
		TDebugger();

		void clearWindow();

		void showDebugWindow(const TRegisterContainer& Registers, const TMemory* Memory, const TU8BitValue& DataBus, const TU16BitValue& AddressBus, const nne::TClock& Clock);

	private:

		void showProgramMemory(const nne::T16BitRegister& ProgramCounter, const TMemory& Memory);

		void showFlags(const nne::T8BitRegister& FlagRegister);

		void showRegistersValue(const TRegisterContainer& Registers);

		void showTiming(const nne::TClock& Clock);

		void showDataBus(const TU8BitValue& Value);

		void showAddressBus(const TU16BitValue& Value);

	private:
		HANDLE mConsoleHandle;
		CONSOLE_SCREEN_BUFFER_INFO mConsoleInfo;
		WORD mSavedAttributes;
	};
}

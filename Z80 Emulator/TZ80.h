#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <memory>

#include "TRegisterContainer.h"
#include "TInstruction.h"
#include "TAlu.h"
#include "TDebugger.h"

#include "TPinComponent.h"
#include "TEntity.h"
#include "TRam.h"
#include "TClock.h"

namespace TGame
{
	namespace CPUPinGroup
	{
		const TComponents::TPin::TPinGroupID AddressBus = 0;
		const TComponents::TPin::TPinGroupID DataBus = 1;
		const TComponents::TPin::TPinGroupID Others = 3;
	}

	class TZ80 : public TInternals::TEntity
	{
	public:
		enum class TInterruptMode : TU8BitValue
		{
			MODE_0,
			MODE_1,
			MODE_2
		};

	public:
		TZ80();
		~TZ80() = default;

		void Reset();

		void Init();

		void Update();

		bool LoadProgram(const std::string& Program);

		bool ConnectRam(std::shared_ptr<TModules::TRam>& Ram);

		void MainLoop();

		virtual void MakeVirtual() {};

		/// Fetch the instruction from memory
		template <class T>
		T FetchInstruction(const TU16BitValue& Address = 0);

		// Execute instruction
		TU16BitValue ExecuteInstruction(const TOpCodesMainInstruction& OpCode);

	private:

		/// Put the data in the address bus
		void PushDataToAddressBus(const TU16BitValue& Value);

		/// Get the data from the data bus
		TU8BitValue GetDataFromDataBus();

		/// Put the data in the data bus
		void PushDataToDataBus(const TU8BitValue& Value);

		/// Helper function for loading data into register
		template <class T, class S = T>
		void LoadRegisterFromRegister(const TRegisterType& Destination, const TRegisterType& Source);
		template <class T>
		void LoadRegisterFromMemory(const TRegisterType& Register, const TMemoryAddress& MemoryLocation);
		template <class T, class S = T>
		void LoadRegisterFromNumber(const TRegisterType& LeftRegister, const S& RightRegister);

		/// Helper function for loading data into memory
		template <class T>
		void LoadMemoryFromRegister(const TRegisterType& Register, const TMemoryAddress& MemoryLocation);

		/// Stack functions
		void PushMemory(const TRegisterType& Register);
		void PopMemory(const TRegisterType& Register);

		/// Call/Return functions
		void Call(const TU16BitValue& Address);
		void Return();

	private:
		bool mIsRunning;
		bool mIsHalted;
		bool mMaskableInterrupt;
		TInternals::TClock mClock;
		TInterruptMode mInterruptMode;
		
		TU16BitValue mAddressBus;
		TU8BitValue mDataBus;

		// EXTERNAL RAM COMPONENT
		std::shared_ptr<TModules::TRam> mRam;

		// Cache the RAM memory
		std::shared_ptr<TMemory> mMemory;

		// Internal CPU ALU
		TAlu mAlu;
		TRegisterContainer mRegisters;

		// Debugger window
		TDebugger mDebugger;
	};

	template <class T>
	T TZ80::FetchInstruction(const TU16BitValue& Address /*= 0*/)
	{
		// Check if we have a connected ram, if we don't have one return nop
		if (!mRam)
			return static_cast<T>(TOpCodesMainInstruction::NOP);

		// If we specify an address return the instruction specified by the address
		if (Address > 0)
		{
			PushDataToAddressBus(Address);

			return static_cast<T>((*mMemory)[Address]);
		}

		// get a ref to PC
		auto& ProgramCounter = mRegisters.ProgramCounter();

		PushDataToAddressBus(ProgramCounter);

		// Otherwise return the instruction pointed by the program counter
		return static_cast<T>((*mMemory)[ProgramCounter]);
	}

	template <class T, class S /*= T*/>
	void TZ80::LoadRegisterFromRegister(const TRegisterType& Destination, const TRegisterType& Source)
	{
		mRegisters.GetRegister<T>(Destination) = mRegisters.GetRegister<S>(Source);
	}

	template <class T>
	void TZ80::LoadRegisterFromMemory(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
	{
		mRegisters.GetRegister<T>(Register) = (*mMemory)[MemoryLocation];
	}

	template <class T, class S /*= T*/>
	void TZ80::LoadRegisterFromNumber(const TRegisterType& LeftRegister, const S& RightRegister)
	{
		mRegisters.GetRegister<T>(LeftRegister) = mRegisters.GetRegister<S>(RightRegister);
	}

	template <class T>
	void TZ80::LoadMemoryFromRegister(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
	{
		(*mMemory)[MemoryLocation] = mRegisters.GetRegister<T>(Register);
	}

}



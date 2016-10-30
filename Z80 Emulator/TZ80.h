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

namespace nne
{
	namespace tmodules
	{
		namespace CPUPinGroup
		{
			const tcomponents::TPin::TPinGroupID AddressBus = 0;
			const tcomponents::TPin::TPinGroupID DataBus = 1;
			const tcomponents::TPin::TPinGroupID Others = 3;
		}
	
		class TZ80 : public nne::TEntity
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
	
			// Use the refresh instruction as an M1 cycle
			void Refresh();
	
			void Update();
	
			bool LoadProgram(const std::string& Program);
	
			bool ConnectRam(std::shared_ptr<tmodules::TRam> Ram);
	
			virtual void MakeVirtual() {};
	
			/// Fetch the instruction from memory
			TU8BitValue FetchInstruction(const TU16BitValue& Address = 0);
	
			// Execute instruction
			TU16BitValue ExecuteInstruction(const TOpCodesMainInstruction& OpCode);
	
		private:
	
			/// Put the data in the address bus
			void PushDataToAddressBus(const TU16BitValue& Value);
	
			/// Get the data from the address bus
			TU16BitValue GetDataFromAddressBus();
	
			/// Put the data in the data bus
			void PushDataToDataBus(const TU8BitValue& Value);
	
			/// Get the data from the data bus
			TU8BitValue GetDataFromDataBus();
	
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
			
			TInterruptMode mInterruptMode;
	
			// Current instruction
			TU8BitValue mCurrentInstruction;
	
			// Clock and T states
			nne::TClock mClock;
			TU8BitValue mTStates;
			
			// Cache the value of the address and data bus
			TU16BitValue mAddressBus;
			TU8BitValue mDataBus;
	
			// EXTERNAL ROM COMPONENT
			std::shared_ptr<tmodules::TRam> mRam;
			
			// Internal CPU ALU
			TAlu mAlu;
			TRegisterContainer mRegisters;
	
			// Debugger window
			TDebugger mDebugger;
		};
	
		template <class T, class S /*= T*/>
		void TZ80::LoadRegisterFromRegister(const TRegisterType& Destination, const TRegisterType& Source)
		{
			mRegisters.GetRegister<T>(Destination) = mRegisters.GetRegister<S>(Source);
		}
	
		template <class T>
		void TZ80::LoadRegisterFromMemory(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
		{
			mRegisters.GetRegister<T>(Register) = (*mRam)[MemoryLocation];
		}
	
		template <class T, class S /*= T*/>
		void TZ80::LoadRegisterFromNumber(const TRegisterType& LeftRegister, const S& RightRegister)
		{
			mRegisters.GetRegister<T>(LeftRegister) = mRegisters.GetRegister<S>(RightRegister);
		}
	
		template <class T>
		void TZ80::LoadMemoryFromRegister(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
		{
			(*mRam)[MemoryLocation] = mRegisters.GetRegister<T>(Register);
		}
	}
}



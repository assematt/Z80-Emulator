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

#include "IComponent.h"
#include "TPinComponent.h"
#include "TRamComponent.h"
#include "TEntity.h"
#include "TClock.h"
#include "TValues.h"


namespace nne
{
	namespace tcomponents
	{
		namespace CPUPinGroup
		{
			const tcomponents::TPin::TPinGroupID AddressBus = 0;
			const tcomponents::TPin::TPinGroupID DataBus = 1;
			const tcomponents::TPin::TPinGroupID Others = 3;
		}

		class TZ80Component : public nne::IComponent
		{
		public:
			enum class TInterruptMode : TU8BitValue
			{
				MODE_0,
				MODE_1,
				MODE_2
			};

		public:
			TZ80Component();
			~TZ80Component() = default;

			void reset();

			void init();

			// Use the refresh instruction as an M1 cycle
			void refresh(const sf::Time& ElapsedTime);

			void update(const sf::Time& ElapsedTime);

			bool loadProgram(const std::string& Program);

			bool connectRam(std::shared_ptr<TEntity> Ram);

			virtual void makeVirtual() {};

			/// Fetch the instruction from memory
			TU8BitValue fetchInstruction(const TU16BitValue& Address = 0);

			// Execute instruction
			TU16BitValue executeInstruction(const TOpCodesMainInstruction& OpCode);

		private:

			/// Put the data in the address bus
			void pushDataToAddressBus(const TU16BitValue& Value);

			/// Get the data from the address bus
			TU16BitValue getDataFromAddressBus();

			/// Put the data in the data bus
			void pushDataToDataBus(const TU8BitValue& Value);

			/// Get the data from the data bus
			TU8BitValue getDataFromDataBus();

			/// Helper function for loading data into register
			template <class T, class S = T>
			void loadRegisterFromRegister(const TRegisterType& Destination, const TRegisterType& Source);
			template <class T>
			void loadRegisterFromMemory(const TRegisterType& Register, const TMemoryAddress& MemoryLocation);
			template <class T, class S = T>
			void loadRegisterFromNumber(const TRegisterType& LeftRegister, const S& RightRegister);

			/// Helper function for loading data into memory
			template <class T>
			void loadMemoryFromRegister(const TRegisterType& Register, const TMemoryAddress& MemoryLocation);

			/// Stack functions
			void pushMemory(const TRegisterType& Register);
			void popMemory(const TRegisterType& Register);

			/// Call/Return functions
			void call(const TU16BitValue& Address);
			void returnFromCall();

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
			std::shared_ptr<TEntity> mRam;

			// Internal CPU ALU
			TAlu mAlu;
			TRegisterContainer mRegisters;

			// Debugger window
			TDebugger mDebugger;
		};

		template <class T, class S /*= T*/>
		void TZ80Component::loadRegisterFromRegister(const TRegisterType& Destination, const TRegisterType& Source)
		{
			mRegisters.getRegister<T>(Destination) = mRegisters.getRegister<S>(Source);
		}

		template <class T>
		void TZ80Component::loadRegisterFromMemory(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
		{
			mRegisters.getRegister<T>(Register) = mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory()[MemoryLocation];
		}

		template <class T, class S /*= T*/>
		void TZ80Component::loadRegisterFromNumber(const TRegisterType& LeftRegister, const S& RightRegister)
		{
			mRegisters.getRegister<T>(LeftRegister) = mRegisters.getRegister<S>(RightRegister);
		}

		template <class T>
		void TZ80Component::loadMemoryFromRegister(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
		{
			mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory()[MemoryLocation] = mRegisters.getRegister<T>(Register);
		}
	}
}

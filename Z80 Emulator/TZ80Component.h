#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <memory>

#include "TRegisterContainer.h"
#include "TInstructions.h"
#include "TAlu.h"
#include "TDebugger.h"

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include "TPinComponent.h"
#include "TRamComponent.h"
//#include INCLUDE_ENTITY_CLASS
#include "TEntity.h"
#include "TClock.h"


namespace nne
{
		
	using TSourceCode = std::vector<TInstruction>;

	namespace tcomponents
	{
		namespace CPUPinGroup
		{
			const tcomponents::TPin::TPinGroupID AddressBus = 0;
			const tcomponents::TPin::TPinGroupID DataBus = 1;
			const tcomponents::TPin::TPinGroupID Others = 3;
		}

		class TZ80Component : BASE_COMPONENT_CLASS
		{
		public:
			enum class TInterruptMode : TU8BitValue
			{
				MODE_0,
				MODE_1,
				MODE_2
			};

			enum class TMachineCycleMode : TU8BitValue
			{
				INSTRUCTION_FETCH,
				MEMORY_READ,
				MEMORY_WRITE
			};

			TZ80Component();

			void reset();

			void init();

			/// Use the refresh instruction as an M1 cycle
			void refresh(REFRESH_UPDATE_PARAMETER);

			void update(REFRESH_UPDATE_PARAMETER);

			/// Get the TRegisterContainer 
			const TRegisterContainer& getRegisterCointainer() const;

			/// Load a HEX file source code into the attached
			bool loadProgram(const std::string& Program);

			/// Return the program source code 
			const TSourceCode& getProgram() const;
			const sf::Uint16& getProgramSize() const;

			/// Connect a RAM to the z80 for easier program execution
			bool connectRam(ENTITY_PTR& Ram);

			/// Pause the program execution
			void pauseExecution();

			/// Resume the program execution
			void resumeExecution();

			/// Restart the program execution
			void restartExecution();

			/// Return true if the z80 is currently powered on and running, otherwise return false
			const bool & isRunning() const;

			/// Return true if the z80 is currently halted
			const bool& isHalted() const;

			/// Return in what type of M cycle we are currently operating under
			const TMachineCycleMode& getCurrentCycleMode() const;
			
			/// Fetch the instruction from memory
			TU8BitValue fetchInstruction(const TU16BitValue& Address = 0);

			/// Execute instruction
			TU16BitValue executeInstruction(const TOpCodesMainInstruction& OpCode);

			TZ80Component& operator=(const TZ80Component& Right) { return *this; };

		private:

			/// Put the data in the address bus
			void pushDataToAddressBus(const TU16BitValue& Value);

			/// Get the data from the address bus
			TU16BitValue getDataFromAddressBus();

			/// Put the data in the data bus
			void pushDataToDataBus(const TU8BitValue& Value);

			/// Get the data from the data bus
			TU8BitValue getDataFromDataBus();

			/// Fetch the register type we are addressing
			TRegisterType fetchRegisterType(const TU8BitValue& OpCode, const TU8BitValue& Shift, const TU8BitValue& Mask);

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

			///
			void fetchInstructionMCycle();
			void memoryReadMCycle();
			void memoryWriteMCycle();

		private:
			bool				mIsRunning;
			bool				mIsHalted;
			bool				mMaskableInterrupt;

			TInterruptMode		mInterruptMode;

			// Current instruction
			int					mLowMemoryRWValue;
			int					mHighMemoryRWValue;
			TU8BitValue			mCurrentInstruction;

			// Clock and T states
			nne::TClock			mClock;
			TU8BitValue			mTStates;
			TMachineCycleMode	mMachineCycleMode;

			// Cache the value of the address and data bus
			TU8BitValue			mDataBus;
			TU16BitValue		mAddressBus;

			// EXTERNAL ROM COMPONENT
			TSourceCode			mProgramSource;
			sf::Uint16			mProgramSize;
#if ENTITY_SYSTEM == NNE
			ENTITY_PTR			mRam;
#else
			ecs::_TEntity::Ptr	mRam;
#endif

			// Internal CPU ALU
			TAlu				mAlu;
			TRegisterContainer	mRegisters;

			// Debugger window
			TDebugger			mDebugger;

			//friend class TCodeEditor;
		};

		template <class T, class S /*= T*/>
		void TZ80Component::loadRegisterFromRegister(const TRegisterType& Destination, const TRegisterType& Source)
		{
			mRegisters.getRegister<T>(Destination) = mRegisters.getRegister<S>(Source);
		}

		template <class T>
		void TZ80Component::loadRegisterFromMemory(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
		{
#if ENTITY_SYSTEM == NNE
			mRegisters.getRegister<T>(Register) = mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory()[MemoryLocation];
#else
			mRegisters.getRegister<T>(Register) = mRam->getComponent<TMemoryComponent>()->getInternalMemory()[MemoryLocation];
#endif
		}

		template <class T, class S /*= T*/>
		void TZ80Component::loadRegisterFromNumber(const TRegisterType& LeftRegister, const S& RightRegister)
		{
			mRegisters.getRegister<T>(LeftRegister) = mRegisters.getRegister<S>(RightRegister);
		}

		template <class T>
		void TZ80Component::loadMemoryFromRegister(const TRegisterType& Register, const TMemoryAddress& MemoryLocation)
		{			
#if ENTITY_SYSTEM == NNE
			mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory()[MemoryLocation] = mRegisters.getRegister<T>(Register);
#else
			mRam->getComponent<TMemoryComponent>()->getInternalMemory()[MemoryLocation] = mRegisters.getRegister<T>(Register);
#endif
		}
	}
}

#include "TZ80Component.h"

#include "TPackageComponent.h"

namespace nne
{
	namespace tcomponents
	{
		TZ80Component::TZ80Component() :
			mIsRunning(false),
			mIsHalted(false),
			mMaskableInterrupt(true),
			mAlu(mRegisters),
			mClock(hertz(1.l)),
			mTStates(0),
			mRam(nullptr),
			mAddressBus(0),
			mDataBus(0),
			mLowMemoryRWValue(0),
			mHighMemoryRWValue(0),
			mProgramSize(0),
			mCurrentInstruction(TOpCodesMainInstruction::NOP),
			mMachineCycleMode(TMachineCycleMode::INSTRUCTION_FETCH)
		{
		}
		
		void TZ80Component::reset()
		{
			// Reset the state of the register
			mRegisters.reset();
		
			// Reset the R/W Memory portion if we have one connected
			if (mRam)
			{
				for (auto& Memory : mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory())
				{
					Memory = 0;
				}
			}		
		}
		
		void TZ80Component::init()
		{
			// Add the right Components to make a CPU

			// Setup the CPU Pins
			auto& PinComponent = *mParent->getComponentAsPtr<TPinComponent>();
			PinComponent.setupPins(std::initializer_list<tcomponents::TPin>{
				
				//PinMode, PinName, PinStatus, PinNumber, PinGroupID, PinGroupNumber

				// ADDRESS BUS
				{ tcomponents::TPin::TMode::OUTPUT, "A0",  tcomponents::TPin::TStatus::LOW, 30, CPUPinGroup::AddressBus, 1 }, // A1
				{ tcomponents::TPin::TMode::OUTPUT, "A1",  tcomponents::TPin::TStatus::LOW, 31, CPUPinGroup::AddressBus, 2 }, // A2
				{ tcomponents::TPin::TMode::OUTPUT, "A2",  tcomponents::TPin::TStatus::LOW, 32, CPUPinGroup::AddressBus, 0 }, // A0
				{ tcomponents::TPin::TMode::OUTPUT, "A3",  tcomponents::TPin::TStatus::LOW, 33, CPUPinGroup::AddressBus, 3 }, // A3
				{ tcomponents::TPin::TMode::OUTPUT, "A4",  tcomponents::TPin::TStatus::LOW, 34, CPUPinGroup::AddressBus, 4 }, // A4
				{ tcomponents::TPin::TMode::OUTPUT, "A5",  tcomponents::TPin::TStatus::LOW, 35, CPUPinGroup::AddressBus, 5 }, // A5
				{ tcomponents::TPin::TMode::OUTPUT, "A6",  tcomponents::TPin::TStatus::LOW, 36, CPUPinGroup::AddressBus, 6 }, // A6
				{ tcomponents::TPin::TMode::OUTPUT, "A7",  tcomponents::TPin::TStatus::LOW, 37, CPUPinGroup::AddressBus, 7 }, // A7
				{ tcomponents::TPin::TMode::OUTPUT, "A8",  tcomponents::TPin::TStatus::LOW, 38, CPUPinGroup::AddressBus, 8 }, // A8
				{ tcomponents::TPin::TMode::OUTPUT, "A9",  tcomponents::TPin::TStatus::LOW, 39, CPUPinGroup::AddressBus, 9 }, // A9
				{ tcomponents::TPin::TMode::OUTPUT, "A10", tcomponents::TPin::TStatus::LOW, 40, CPUPinGroup::AddressBus, 10 }, // A10
				{ tcomponents::TPin::TMode::OUTPUT, "A11", tcomponents::TPin::TStatus::LOW,  1, CPUPinGroup::AddressBus, 11 }, // A11
				{ tcomponents::TPin::TMode::OUTPUT, "A12", tcomponents::TPin::TStatus::LOW,  2, CPUPinGroup::AddressBus, 12 }, // A12
				{ tcomponents::TPin::TMode::OUTPUT, "A13", tcomponents::TPin::TStatus::LOW,  3, CPUPinGroup::AddressBus, 13 }, // A13
				{ tcomponents::TPin::TMode::OUTPUT, "A14", tcomponents::TPin::TStatus::LOW,  4, CPUPinGroup::AddressBus, 14 }, // A14
				{ tcomponents::TPin::TMode::OUTPUT, "A15", tcomponents::TPin::TStatus::LOW,  5, CPUPinGroup::AddressBus, 15 }, // A15

				// DATA BUS
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D0", tcomponents::TPin::TStatus::LOW, 14, CPUPinGroup::DataBus, 0 }, // D0
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D1", tcomponents::TPin::TStatus::LOW, 15, CPUPinGroup::DataBus, 1 }, // D1
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D2", tcomponents::TPin::TStatus::LOW, 12, CPUPinGroup::DataBus, 2 }, // D2
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D3", tcomponents::TPin::TStatus::LOW,  8, CPUPinGroup::DataBus, 3 }, // D3
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D4", tcomponents::TPin::TStatus::LOW,  7, CPUPinGroup::DataBus, 4 }, // D4
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D5", tcomponents::TPin::TStatus::LOW,  9, CPUPinGroup::DataBus, 5 }, // D5
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D6", tcomponents::TPin::TStatus::LOW, 10, CPUPinGroup::DataBus, 6 }, // D6
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, "D7", tcomponents::TPin::TStatus::LOW, 13, CPUPinGroup::DataBus, 7 }, // D7

				// SYSTEM CONTROL
				{ tcomponents::TPin::TMode::OUTPUT, "M1", tcomponents::TPin::TStatus::HIGH,   27, CPUPinGroup::Others }, // M1
				{ tcomponents::TPin::TMode::OUTPUT, "MREQ", tcomponents::TPin::TStatus::HIGH, 19, CPUPinGroup::Others }, // MREQ
				{ tcomponents::TPin::TMode::OUTPUT, "IORQ", tcomponents::TPin::TStatus::HIGH, 20, CPUPinGroup::Others }, // IORQ
				{ tcomponents::TPin::TMode::OUTPUT, "RD", tcomponents::TPin::TStatus::HIGH,   21, CPUPinGroup::Others }, // RD
				{ tcomponents::TPin::TMode::OUTPUT, "WR", tcomponents::TPin::TStatus::HIGH,	  22, CPUPinGroup::Others }, // WR
				{ tcomponents::TPin::TMode::OUTPUT, "RFSH", tcomponents::TPin::TStatus::HIGH, 28, CPUPinGroup::Others }, // RFSH

				// CPU CONTROL
				{ tcomponents::TPin::TMode::OUTPUT, "HALT", tcomponents::TPin::TStatus::LOW, 18, CPUPinGroup::Others }, // HALT
				{ tcomponents::TPin::TMode::INPUT, "WAIT", tcomponents::TPin::TStatus::LOW,  24, CPUPinGroup::Others }, // WAIT
				{ tcomponents::TPin::TMode::INPUT, "INT", tcomponents::TPin::TStatus::LOW,   16, CPUPinGroup::Others }, // INT
				{ tcomponents::TPin::TMode::INPUT, "NMI", tcomponents::TPin::TStatus::LOW,   17, CPUPinGroup::Others }, // NMI
				{ tcomponents::TPin::TMode::INPUT, "RESET", tcomponents::TPin::TStatus::LOW, 26, CPUPinGroup::Others }, // RESET 

				// CPU BUS CONTROL
				{ tcomponents::TPin::TMode::OUTPUT, "BUSAK", tcomponents::TPin::TStatus::LOW, 25, CPUPinGroup::Others }, // BUSAK
				{ tcomponents::TPin::TMode::INPUT, "BUSRQ", tcomponents::TPin::TStatus::LOW,  23, CPUPinGroup::Others }, // BUSRQ 

				// CPUPinGroup::Others
				{ tcomponents::TPin::TMode::CLOCK, "CLK", tcomponents::TPin::TStatus::LOW,  6, CPUPinGroup::Others }, // CLK
				{ tcomponents::TPin::TMode::INPUT, "VCC", tcomponents::TPin::TStatus::LOW, 11, CPUPinGroup::Others }, // VCC
				{ tcomponents::TPin::TMode::INPUT, "GND", tcomponents::TPin::TStatus::LOW, 29, CPUPinGroup::Others }, // GND

			}, 40);

			// Reset the state of the CPU
			reset();
		}
		
		void TZ80Component::refresh(const sf::Time& ElapsedTime)
		{
			// Before check if the z80 is still active
			if (!mIsRunning || !mParent->getComponent<TPackageComponent>().isPoweredOn())
				return;

			if (mIsHalted)
			{
				mCurrentInstruction = TOpCodesMainInstruction::NOP;
				return;
			}

			switch (mMachineCycleMode)
			{
			case TMachineCycleMode::INSTRUCTION_FETCH:
				fetchInstructionMCycle();
				break;
			case TMachineCycleMode::MEMORY_READ:
				memoryReadMCycle();
				break;
			case TMachineCycleMode::MEMORY_WRITE:
				memoryWriteMCycle();
				break;
			}

		}
	
		void TZ80Component::update(const sf::Time& ElapsedTime)
		{
			// Before check if the z80 is still active
			if (!mIsRunning || !mParent->getComponent<TPackageComponent>().isPoweredOn())
				return;
	
			// Show the debug window
			if (mRam)
				mDebugger.showDebugWindow(mRegisters, &mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory(), mDataBus, mAddressBus, mClock);
					
			//mClock.wait();
		}
	
		const nne::TRegisterContainer& TZ80Component::getRegisterCointainer() const
		{
			return mRegisters;
		}

		bool TZ80Component::loadProgram(const std::string& Program)
		{
			// Check if we have a connected ram to load the program into
			if (!mRam)
				return false;

			auto& Memory = mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory();

			// Load the instruction set
	
			// Read the file		
			std::ifstream InputFile(Program.c_str());
	
			// Check if the file is opened
			if (!InputFile.is_open())
				return false;

			// Reset the program source code and size
			mProgramSize = 0;
			mProgramSource.clear();
	
			// Scan the HEX file and reads it
			std::string CodeLine;
			while (getline(InputFile, CodeLine))
			{
				// Read how much data it's in the line
				std::size_t ByteCount = std::stoi(CodeLine.substr(1, 2).c_str(), 0, 16);

				// 
				mProgramSize += ByteCount;
	
				// Read where the data start
				sf::Uint16 StartAddress = std::stoi(CodeLine.substr(3, 4).c_str(), 0, 16);
	
				// Record types
				std::size_t RecordType = std::stoi(CodeLine.substr(7, 2).c_str(), 0, 16);
	
				// If record type it's 0 the following bytes are the program source code
				if (RecordType == 0)
				{
					for (sf::Uint16 Index = 0, MemoryIndex = StartAddress; Index < ByteCount * 2; Index += 2, ++MemoryIndex)
					{
						// Write the byte into memory only if the ram section pointed by the HEX file is within the range of the RAM if we using
						if (MemoryIndex < Memory.size())
						{
							// Extract the instruction string
							std::string InstructionString = CodeLine.substr(9 + Index, 2);

							// Convert the instruction string in a 16 unsigned int
							TU16BitValue InstructionCode = std::stoi(InstructionString, 0, 16);

							// Put the instruction code in the RAM
							Memory[MemoryIndex] = InstructionCode;

							// Find the instruction data in the instruction set
							auto Inst = std::find(InstructionSet.begin(), InstructionSet.end(), InstructionCode);

							// Put the instruction data in the source code vector
							mProgramSource.push_back({ Inst->InstructionSize, MemoryIndex, Inst->InstructionCode, Inst->InstructionName });
						}
					}
				}
			}
	
			InputFile.close();
	
			return true;
		}
		
		const nne::TSourceCode& TZ80Component::getProgram() const
		{
			return mProgramSource;
		}

		const sf::Uint16& TZ80Component::getProgramSize() const
		{
			return mProgramSize;
		}

		bool TZ80Component::connectRam(std::shared_ptr<TEntity>& Ram)
		{
			// Check the the passed argument points to something
			if (!Ram)
				return false;
	
			// Creates a copy of the ram pointer
			mRam = Ram;
	
			// Get a ref to the PinComponent of the z80 and ram
			auto CpuPinComponent = mParent->getComponentAsPtr<TPinComponent>();
			auto RamPinComponent = Ram->getComponentAsPtr<TPinComponent>();
	
			// Connects the Z80 Address bus to the Ram AddressBus
			auto& LeftBus = CpuPinComponent->getPinBus(CPUPinGroup::AddressBus, 0, 14);
			auto& RightBus = RamPinComponent->getPinBus(tcomponents::TRamPinGroup::AddressBus);
			TPinComponentUtility::connectPins(LeftBus, RightBus);
	
			// Connects the Z80 data bus to the Ram data bus
			LeftBus = CpuPinComponent->getPinBus(CPUPinGroup::DataBus);
			RightBus = RamPinComponent->getPinBus(tcomponents::TRamPinGroup::DataBus);
			TPinComponentUtility::connectPins(LeftBus, RightBus);
	
			// Connect the MREQ pin to the CE of the ram
			TPinComponentUtility::connectPins(CpuPinComponent->getPin(19), RamPinComponent->getPin(20));
	
			// Connect the RD pin to the OE of the ram
			TPinComponentUtility::connectPins(CpuPinComponent->getPin(21), RamPinComponent->getPin(22));

			return true;
		}
		
		void TZ80Component::pauseExecution()
		{
			mIsRunning = false;
		}

		void TZ80Component::resumeExecution()
		{
			mIsRunning = true;
		}

		void TZ80Component::restartExecution()
		{
			// Reset the state of the register
			mRegisters.reset();

			// Remove halted states
			mIsHalted = false;

			// Reset the TState
			mTStates = 0;
		}

		const bool& TZ80Component::isRunning() const
		{
			return mIsRunning;
		}

		const bool& TZ80Component::isHalted() const
		{
			return mIsHalted;
		}

		const TZ80Component::TMachineCycleMode& TZ80Component::getCurrentCycleMode() const
		{
			return mMachineCycleMode;
		}

		TU8BitValue TZ80Component::fetchInstruction(const TU16BitValue& Address /*= 0*/)
		{
			// Check if we have a connected ram, if we don't have one return nop
			if (!mRam)
				return static_cast<TOpCodesMainInstruction>(TOpCodesMainInstruction::NOP);
	
			// Get a ref to the PinComponent
			auto Pins = mParent->getComponentAsPtr<TPinComponent>();
	
			// Activates MREQ and RD pin
			Pins->getPin(19).changePinStatus(tcomponents::TPin::LOW, true);
			Pins->getPin(21).changePinStatus(tcomponents::TPin::LOW, true);
	
			// Select the instruction by putting the address in the address bus
			auto& PC = mRegisters.programCounter();
			pushDataToAddressBus(Address > 0 ? Address : PC);
	
			// refresh the memory logic			
			mRam->getComponentAsPtr<TRamComponent>()->refreshMemory();
	
			// Get the instruction from the bus
			mCurrentInstruction = getDataFromDataBus();
			
			// Deactivates MREQ and RD pin
			Pins->getPin(19).changePinStatus(tcomponents::TPin::HIGH, true);
			Pins->getPin(21).changePinStatus(tcomponents::TPin::HIGH, true);
	
			return mCurrentInstruction;
		}
	
		TU16BitValue TZ80Component::executeInstruction(const TOpCodesMainInstruction& OpCode)
		{
			// Forward declare TMemory
			TMemory* Memory = nullptr;

			// Get a ref to the RAM internal memory for better access if we setted one other wise exit the function
			if (mRam && mRam->hasComponent<TMemoryComponent>())
				Memory = &mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory();
			
			///auto& Memory = mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory();

			switch (OpCode)
			{
		
				#pragma region Loading instruction
		
		#pragma region LD R,R
				// LD R,R'
			case LD_B_B:
			case LD_B_C:
			case LD_B_D:
			case LD_B_E:
			case LD_B_H:
			case LD_B_L:
			case LD_B_A:
			case LD_C_B:
			case LD_C_C:
			case LD_C_D:
			case LD_C_E:
			case LD_C_H:
			case LD_C_L:
			case LD_C_A:
			case LD_D_B:
			case LD_D_C:
			case LD_D_D:
			case LD_D_E:
			case LD_D_H:
			case LD_D_L:
			case LD_D_A:
			case LD_E_B:
			case LD_E_C:
			case LD_E_D:
			case LD_E_E:
			case LD_E_H:
			case LD_E_L:
			case LD_E_A:
			case LD_H_B:
			case LD_H_C:
			case LD_H_D:
			case LD_H_E:
			case LD_H_H:
			case LD_H_L:
			case LD_H_A:
			case LD_L_B:
			case LD_L_C:
			case LD_L_D:
			case LD_L_E:
			case LD_L_H:
			case LD_L_L:
			case LD_L_A:
			case LD_A_B:
			case LD_A_C:
			case LD_A_D:
			case LD_A_E:
			case LD_A_H:
			case LD_A_L:
			case LD_A_A:
			{
				TRegisterType SourceRegister, DestinationRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: DestinationRegister = TRegisterType::B; break;
				case 1: DestinationRegister = TRegisterType::C; break;
				case 2: DestinationRegister = TRegisterType::D; break;
				case 3: DestinationRegister = TRegisterType::E; break;
				case 4: DestinationRegister = TRegisterType::H; break;
				case 5: DestinationRegister = TRegisterType::L; break;
				case 7: DestinationRegister = TRegisterType::A; break;
				}
		
				// Perform the loading operation
				loadRegisterFromRegister<T8BitRegister>(DestinationRegister, SourceRegister);
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		#pragma endregion
		
		#pragma region LD R,N
			case LD_A_n:
			case LD_B_n:
			case LD_C_n:
			case LD_D_n:
			case LD_E_n:
			case LD_H_n:
			case LD_L_n:
			{
				if (mMachineCycleMode == TMachineCycleMode::INSTRUCTION_FETCH)
				{
					// Next M cycle it's a memory read cycle
					mMachineCycleMode = TMachineCycleMode::MEMORY_READ;
				}
				else if (mMachineCycleMode == TMachineCycleMode::MEMORY_READ && mTStates == 2)
				{
					// Get the source address by looking at the second 3 bits
					TRegisterType DestinationRegister = fetchRegisterType(OpCode, 3, 7);

					mRegisters.getRegister<T8BitRegister>(DestinationRegister) = mLowMemoryRWValue;

					// Next M cycle it's a fetch instruction
					mMachineCycleMode = TMachineCycleMode::INSTRUCTION_FETCH;
				}
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		#pragma endregion
		
		#pragma region LD R,(HL)
			case LD_A_INDIRECT_HL:
			case LD_B_INDIRECT_HL:
			case LD_C_INDIRECT_HL:
			case LD_D_INDIRECT_HL:
			case LD_E_INDIRECT_HL:
			case LD_H_INDIRECT_HL:
			case LD_L_INDIRECT_HL:
			{
				TRegisterType DestinationRegister;
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: DestinationRegister = TRegisterType::B; break;
				case 1: DestinationRegister = TRegisterType::C; break;
				case 2: DestinationRegister = TRegisterType::D; break;
				case 3: DestinationRegister = TRegisterType::E; break;
				case 4: DestinationRegister = TRegisterType::H; break;
				case 5: DestinationRegister = TRegisterType::L; break;
				case 7: DestinationRegister = TRegisterType::A; break;
				}
		
				// Perform the loading operation
				loadRegisterFromMemory<T8BitRegister>(DestinationRegister, mRegisters.getRegister<T16BitRegister>(TRegisterType::HL));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		#pragma endregion
		
		#pragma region LD (HL),R
			case LD_INDIRECT_HL_B:
			case LD_INDIRECT_HL_C:
			case LD_INDIRECT_HL_D:
			case LD_INDIRECT_HL_E:
			case LD_INDIRECT_HL_H:
			case LD_INDIRECT_HL_L:
			case LD_INDIRECT_HL_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the loading instruction
				loadMemoryFromRegister<T8BitRegister>(SourceRegister, mRegisters.getRegister<T16BitRegister>(TRegisterType::HL));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		#pragma endregion
		
		#pragma region LD DD,NN
			case LD_BC_n:
			case LD_DE_n:
			case LD_HL_n:
			case LD_SP_n:
			{
				TRegisterType DestinationRegister;
		
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 4 & 3)
				{
				case 0: DestinationRegister = TRegisterType::BC; break;
				case 1: DestinationRegister = TRegisterType::DE; break;
				case 2: DestinationRegister = TRegisterType::HL; break;
				case 3: DestinationRegister = TRegisterType::SP; break;
				}
		
				// Perform the loading operation
				auto MemoryToLoad = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
				mRegisters.getRegister<T16BitRegister>(DestinationRegister) = MemoryToLoad;
		
				// Increment the PC
				ProgramCounter += 3;
			} break;
		#pragma endregion
		
			// LD A,(BC)
			case LD_A_INDIRECT_BC:
			{
				// Perform the loading operation
				loadRegisterFromMemory<T8BitRegister>(TRegisterType::A, mRegisters.getRegister<T16BitRegister>(TRegisterType::BC));
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		
			// LD A,(DE)
			case LD_A_INDIRECT_DE:
			{
				// Perform the loading operation
				loadRegisterFromMemory<T8BitRegister>(TRegisterType::A, mRegisters.getRegister<T16BitRegister>(TRegisterType::DE));
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		
			// LD (BC),A
			case LD_INDIRECT_BC_A:
			{
				// Perform the loading operation
				loadMemoryFromRegister<T8BitRegister>(TRegisterType::A, mRegisters.getRegister<T16BitRegister>(TRegisterType::BC));
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		
			// LD (DE),A
			case LD_INDIRECT_DE_A:
			{
				// Perform the loading operation
				loadMemoryFromRegister<T8BitRegister>(TRegisterType::A, mRegisters.getRegister<T16BitRegister>(TRegisterType::BC));
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		
			// LD A,(NN)
			case LD_A_INDIRECT_ADR:
			{
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Perform the loading operation
				loadRegisterFromMemory<T8BitRegister>(TRegisterType::A, TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]));
		
				// Increment the PC
				ProgramCounter += 3;
			}break;
		
			// LD (NN),A
			case LD_INDIRECT_ADR_A:
			{
		
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Perform the loading operation
				loadMemoryFromRegister<T8BitRegister>(TRegisterType::A, TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]));
		
				// Increment the PC
				ProgramCounter += 3;
			}break;
		
			// LD (NN),HL
			case LD_INDIRECT_ADR_HL:
			{
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Get the destination address
				auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
				// Perform the loading operation
				(*Memory)[Address] = mRegisters.getRegister<T8BitRegister>(TRegisterType::L);
				(*Memory)[Address + 1] = mRegisters.getRegister<T8BitRegister>(TRegisterType::H);
		
				// Increment PC
				ProgramCounter += 3;
			}break;
		
			// LD HL,(NN)
			case LD_HL_INDIRECT_ADR:
			{
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Get the destination address
				auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
				// Perform the loading operation
				mRegisters.getRegister<T8BitRegister>(TRegisterType::L) = (*Memory)[Address];
				mRegisters.getRegister<T8BitRegister>(TRegisterType::H) = (*Memory)[Address + 1];
		
				// Increment PC
				ProgramCounter += 3;
			}break;
		
			// LD (HL),N
			case LD_INDIRECT_HL_n:
			{
				if (mMachineCycleMode == TMachineCycleMode::INSTRUCTION_FETCH)
				{
					// Next M cycle it's a memory read cycle
					mMachineCycleMode = TMachineCycleMode::MEMORY_READ;
				}
				else if (mMachineCycleMode == TMachineCycleMode::MEMORY_READ && mTStates == 2)
				{
					// Perform the loading operation
					(*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)] = mLowMemoryRWValue;

					// Next M cycle it's a fetch instruction
					mMachineCycleMode = TMachineCycleMode::INSTRUCTION_FETCH;
				}

				// Increment the PC
				++mRegisters.programCounter();
			}break;
		
			// LD SP,HL
			case LD_SP_HL:
			{
				// Perform the loading operation
				loadRegisterFromRegister<T16BitRegister>(TRegisterType::SP, TRegisterType::HL);
		
				// Increment PC
				++mRegisters.programCounter();
			}break;
		
		#pragma endregion
				
				#pragma region Stack Function
			// PUSH QQ
			case PUSH_BC:
			case PUSH_DE:
			case PUSH_HL:
			case PUSH_AF:
			{
				TRegisterType DestinationRegister;
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 4 & 3)
				{
				case 0: DestinationRegister = TRegisterType::BC; break;
				case 1: DestinationRegister = TRegisterType::DE; break;
				case 2: DestinationRegister = TRegisterType::HL; break;
				case 3: DestinationRegister = TRegisterType::AF; break;
				}
		
				// Perform the push operation
				pushMemory(DestinationRegister);
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// POP QQ
			case POP_BC:
			case POP_DE:
			case POP_HL:
			case POP_AF:
			{
				TRegisterType DestinationRegister;
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 4 & 3)
				{
				case 0: DestinationRegister = TRegisterType::BC; break;
				case 1: DestinationRegister = TRegisterType::DE; break;
				case 2: DestinationRegister = TRegisterType::HL; break;
				case 3: DestinationRegister = TRegisterType::AF; break;
				}
		
				// Perform the push operation
				popMemory(DestinationRegister);
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
		#pragma endregion
				
				#pragma region Exchange function
			// EX AF,AF'
			case EX_AF_AF:
			{
				std::swap(mRegisters.getRegister<T16BitRegister>(TRegisterType::AF), mRegisters.getRegister<T16BitRegister>(TRegisterType::ALTAF));
				mRegisters.programCounter() += 1;
			}break;
		
			// EXX
			case EXX:
			{
				std::swap(mRegisters.getRegister<T16BitRegister>(TRegisterType::BC), mRegisters.getRegister<T16BitRegister>(TRegisterType::ALTBC));
				std::swap(mRegisters.getRegister<T16BitRegister>(TRegisterType::DE), mRegisters.getRegister<T16BitRegister>(TRegisterType::ALTDE));
				std::swap(mRegisters.getRegister<T16BitRegister>(TRegisterType::HL), mRegisters.getRegister<T16BitRegister>(TRegisterType::ALTHL));
				mRegisters.programCounter() += 1;
			}break;
		
			// EX (SP),HL
			case EX_INDIRECT_SP_HL:
			{
				mRegisters.getRegister<T8BitRegister>(TRegisterType::H) = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::SP) + 1];
				mRegisters.getRegister<T8BitRegister>(TRegisterType::L) = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::SP)];
				mRegisters.programCounter() += 1;
			}break;
		
			// EX DE,HL
			case EX_DE_HL:
			{
				std::swap(mRegisters.getRegister<T16BitRegister>(TRegisterType::DE), mRegisters.getRegister<T16BitRegister>(TRegisterType::HL));
				mRegisters.programCounter() += 1;
			}break;
		#pragma endregion
				
				#pragma region 8-Bit Arithmetic Group
		
		#pragma region ADD A,R
			case ADD_A_B:
			case ADD_A_C:
			case ADD_A_D:
			case ADD_A_E:
			case ADD_A_H:
			case ADD_A_L:
			case ADD_A_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the addition
				mAlu.aluAdd<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// ADD A,(HL)
			case ADD_A_INDIRECT_HL:
			{
				// Perform the addition
				mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		
			// ADD A,N
			case ADD_A_n:
			{
				// Perform the addition
				mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1]);
		
				// Increment the PC
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion
		
		#pragma region ADC A,R
			case ADC_A_B:
			case ADC_A_C:
			case ADC_A_D:
			case ADC_A_E:
			case ADC_A_H:
			case ADC_A_L:
			case ADC_A_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the addition
				mAlu.aluAdd<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister) + mAlu.checkFlag(TFlags::C));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// ADC A,(HL)
			case ADC_A_INDIRECT_HL:
			{
				// Perform the addition
				mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)] + mAlu.checkFlag(TFlags::C));
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		
			// ADC A,N
			case ADC_A_n:
			{
				// Perform the addition
				mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1] + mAlu.checkFlag(TFlags::C));
		
				// Increment the PC
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion
		
		#pragma region SBC, S
			case SBC_A_B:
			case SBC_A_C:
			case SBC_A_D:
			case SBC_A_E:
			case SBC_A_H:
			case SBC_A_L:
			case SBC_A_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the subtraction
				mAlu.aluSub<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister) - mAlu.checkFlag(TFlags::C));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// SBC A,(HL)
			case SBC_A_INDIRECT_HL:
			{
				mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)] - mAlu.checkFlag(TFlags::C));
		
				mRegisters.programCounter() += 1;
			}break;
		
			// SBC A,N
			case SBC_A_n:
			{
				mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1] - mAlu.checkFlag(TFlags::C));
		
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion
		
		#pragma region SUB S
			case SUB_B:
			case SUB_C:
			case SUB_D:
			case SUB_E:
			case SUB_H:
			case SUB_L:
			case SUB_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the subtraction
				mAlu.aluSub<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// SUB (HL)
			case SUB_INDIRECT_HL:
			{
				mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.programCounter() += 1;
			}break;
		
			// SUB N
			case SUB_n:
			{
				mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1]);
		
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion		
		
		#pragma region INC R
			case INC_B:
			case INC_C:
			case INC_D:
			case INC_E:
			case INC_H:
			case INC_L:
			case INC_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the increment
				mAlu.aluInc<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister).getInternalValue());
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// INC (HL)
			case INC_INDIRECT_HL:
			{
				// Perform the increment
				mAlu.aluInc<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		#pragma endregion
		
		#pragma region DEC R
			case DEC_B:
			case DEC_C:
			case DEC_D:
			case DEC_E:
			case DEC_H:
			case DEC_L:
			case DEC_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the decrement
				mAlu.aluDec<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister).getInternalValue());
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// DEC (HL)
			case DEC_INDIRECT_HL:
			{
				// Perform the increment
				mAlu.aluDec<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				// Increment the PC
				++mRegisters.programCounter();
			}break;
		#pragma endregion
		
		#pragma region AND R
			case AND_B:
			case AND_C:
			case AND_D:
			case AND_E:
			case AND_H:
			case AND_L:
			case AND_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the subtraction
				mAlu.aluAnd<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// AND (HL)
			case AND_INDIRECT_HL:
			{
				mAlu.aluAnd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.programCounter() += 1;
			}break;
		
			// AND N
			case AND_n:
			{
				mAlu.aluAnd<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1]);
		
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion
		
		#pragma region OR R
			case OR_B:
			case OR_C:
			case OR_D:
			case OR_E:
			case OR_H:
			case OR_L:
			case OR_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the subtraction
				mAlu.aluOr<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// OR (HL)
			case OR_INDIRECT_HL:
			{
				mAlu.aluOr<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.programCounter() += 1;
			}break;
		
			// OR N
			case OR_n:
			{
				mAlu.aluOr<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1]);
		
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion			
		
		#pragma region XOR R
			case XOR_B:
			case XOR_C:
			case XOR_D:
			case XOR_E:
			case XOR_H:
			case XOR_L:
			case XOR_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the subtraction
				mAlu.aluXor<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// XOR (HL)
			case XOR_INDIRECT_HL:
			{
				mAlu.aluXor<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.programCounter() += 1;
			}break;
		
			// XOR N
			case XOR_n:
			{
				mAlu.aluXor<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1]);
		
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion			
		
		#pragma region CP R
			case CP_B:
			case CP_C:
			case CP_D:
			case CP_E:
			case CP_H:
			case CP_L:
			case CP_A:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) & 7)
				{
				case 0: SourceRegister = TRegisterType::B; break;
				case 1: SourceRegister = TRegisterType::C; break;
				case 2: SourceRegister = TRegisterType::D; break;
				case 3: SourceRegister = TRegisterType::E; break;
				case 4: SourceRegister = TRegisterType::H; break;
				case 5: SourceRegister = TRegisterType::L; break;
				case 7: SourceRegister = TRegisterType::A; break;
				}
		
				// Perform the subtraction
				mAlu.aluCp<TU8BitValue>(mRegisters.getRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		
			// CP (HL)
			case CP_INDIRECT_HL:
			{
				mAlu.aluCp<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.programCounter() += 1;
			}break;
		
			// CP N
			case CP_n:
			{
				mAlu.aluCp<TU8BitValue>((*Memory)[mRegisters.programCounter() + 1]);
		
				mRegisters.programCounter() += 2;
			}break;
		#pragma endregion
		
		#pragma endregion
				
				#pragma region General-Purpose Arithmetic and CPU Control Groups
			// DAA
			case DAA:
			{
				// Get a ref to the accumulator
				auto& Accumulator = mRegisters.accumulator();
				auto AccLowNibble = TUtility::getLowerNible(Accumulator);
				auto AccHighNibble = TUtility::getUpperNible(Accumulator);
		
		
				if ((TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0, 8) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0xA, 0xF)) ||
					(TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0, 9) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0, 3) && mAlu.checkFlag(TFlags::H)))
				{
					Accumulator += 6;
				}
				else
					if ((TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0xA, 0xF) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0, 9)) ||
						(TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0, 2) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0, 9) && mAlu.checkFlag(TFlags::C)))
					{
						Accumulator += 60;
		
						mAlu.setFlag(TFlags::C);
					}
					else
						if ((TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 9, 0xF) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0xA, 0xF)) ||
							(TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0xA, 0xF) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0, 3) && mAlu.checkFlag(TFlags::H)) ||
							(TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0, 2) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0xA, 0xF) && mAlu.checkFlag(TFlags::C)) ||
							(TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0, 3) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0, 3) && mAlu.checkFlag(TFlags::C) && mAlu.checkFlag(TFlags::H)))
						{
							Accumulator += 66;
		
							mAlu.setFlag(TFlags::C);
						}
						else
							if ((TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 0, 8) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 6, 0xF)) && mAlu.checkFlag(TFlags::H))
							{
								Accumulator += 0xFA;
							}
							else
								if ((TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 7, 0xF) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 0, 9)) && mAlu.checkFlag(TFlags::C))
								{
									Accumulator += 0xA0;
		
									mAlu.setFlag(TFlags::C);
								}
								else
									if ((TUtility::valueIsBetween<TU8BitValue>(AccHighNibble, 6, 7) && TUtility::valueIsBetween<TU8BitValue>(AccLowNibble, 6, 0xF)) && mAlu.checkFlag(TFlags::C) && mAlu.checkFlag(TFlags::H))
									{
										Accumulator += 0x9A;
		
										mAlu.setFlag(TFlags::C);
									}
		
				// Set flags
		
				// S is set if most - significant bit of the Accumulator is 1 after an operation; otherwise, it is reset.
				TUtility::getBit<TU8BitValue>(Accumulator, 7) == 1 ? mAlu.setFlag(TFlags::S) : mAlu.setFlag(TFlags::S);
		
				// Z is set if the Accumulator is 0 after an operation; otherwise, it is reset.
				Accumulator == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.setFlag(TFlags::Z);
		
				// P/V is set if the Accumulator is at even parity after an operation; otherwise, it is reset.
				TUtility::checkParity(Accumulator) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
			} break;
		
			// CPL
			case CPL:
			{
				mRegisters.accumulator() = ~mRegisters.accumulator();
		
				mAlu.setFlag(TFlags::H | TFlags::S);
		
				++mRegisters.programCounter();
			} break;
		
			// CCF
			case CCF:
			{
				// H, previous carry is copied.
				mAlu.checkFlag(TFlags::C) ? mAlu.setFlag(TFlags::H) : mAlu.resetFlag(TFlags::H);
		
				// N is reset.
				mAlu.resetFlag(TFlags::N);
		
				// Flip the carry bit
				mAlu.checkFlag(TFlags::C) ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
				++mRegisters.programCounter();
			} break;
		
			// SCF
			case SCF:
			{
				// N and H is reset.
				mAlu.resetFlag(TFlags::N | TFlags::H);
		
				// Set the carry bit
				mAlu.setFlag(TFlags::C);
		
				++mRegisters.programCounter();
			} break;
		
			// NOP
			case NOP:
			{
				++mRegisters.programCounter();
			} break;
		
			// Halt
			case HALT:
			{
				mIsHalted = true;
		
				++mRegisters.programCounter();
			} break;
		
			// DI
			case DI:
			{
				mMaskableInterrupt = false;
		
				++mRegisters.programCounter();
			} break;
		
			// EI
			case EI:
			{
				mMaskableInterrupt = true;
		
				++mRegisters.programCounter();
			} break;
		
		#pragma endregion
				
				#pragma region 16-Bit Arithmetic Group
		
		#pragma region ADD HL, SS
			case ADD_HL_BC:
			case ADD_HL_DE:
			case ADD_HL_HL:
			case ADD_HL_SP:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 4 & 2)
				{
				case 0: SourceRegister = TRegisterType::BC; break;
				case 1: SourceRegister = TRegisterType::DE; break;
				case 2: SourceRegister = TRegisterType::HL; break;
				case 3: SourceRegister = TRegisterType::SP; break;
				}
		
				// Perform the addition
				mAlu.aluAdd<TU16BitValue>(mRegisters.getRegister<T16BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		#pragma endregion
		
		#pragma region INC SS
			case INC_BC:
			case INC_DE:
			case INC_HL:
			case INC_SP:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 4 & 2)
				{
				case 0: SourceRegister = TRegisterType::BC; break;
				case 1: SourceRegister = TRegisterType::DE; break;
				case 2: SourceRegister = TRegisterType::HL; break;
				case 3: SourceRegister = TRegisterType::SP; break;
				}
		
				// Perform the addition
				mAlu.aluInc<TU16BitValue>(mRegisters.getRegister<T16BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		#pragma endregion
		
		#pragma region DEC SS
			case DEC_BC:
			case DEC_DE:
			case DEC_HL:
			case DEC_SP:
			{
				TRegisterType SourceRegister;
		
				// Get the source address by looking at the first 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 4 & 2)
				{
				case 0: SourceRegister = TRegisterType::BC; break;
				case 1: SourceRegister = TRegisterType::DE; break;
				case 2: SourceRegister = TRegisterType::HL; break;
				case 3: SourceRegister = TRegisterType::SP; break;
				}
		
				// Perform the addition
				mAlu.aluDec<TU16BitValue>(mRegisters.getRegister<T16BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.programCounter();
			} break;
		#pragma endregion
		
		#pragma endregion
				
				#pragma region Shift group
			// RLCA
			case RLCA:
			{
				// Get a reference to the accumulator
				auto& Accumulator = mRegisters.accumulator();
		
				// Rotate left the accumulator
				mAlu.rotateLeft(Accumulator);
		
				++mRegisters.programCounter();
			} break;
		
			// RLA
			case RLA:
			{
				mAlu.rotateLeft(mRegisters.accumulator());
		
				++mRegisters.programCounter();
			} break;
		
			// RRCA
			case RRCA:
			{
				mAlu.rotateRight(mRegisters.accumulator(), true);
		
				++mRegisters.programCounter();
			} break;
		
			// RRA
			case RRA:
			{
				mAlu.rotateRight(mRegisters.accumulator(), true);
		
				++mRegisters.programCounter();
			} break;
		#pragma endregion
				
				#pragma region Bit instructions (CB)
			// TOpCodesBitInstructions
			case BITS:
			{
				// Get the instruction
				auto BitInstruction = static_cast<TOpCodesBitInstructions>(fetchInstruction(++mRegisters.programCounter()));
		
				// Get the register to test by looking at the first 3 bit
				TRegisterType RegisterToTest;
				switch (static_cast<TU8BitValue>(BitInstruction) & 7)
				{
				case 0: RegisterToTest = TRegisterType::B;
				case 1: RegisterToTest = TRegisterType::C;
				case 2: RegisterToTest = TRegisterType::D;
				case 3: RegisterToTest = TRegisterType::E;
				case 4: RegisterToTest = TRegisterType::H;
				case 5: RegisterToTest = TRegisterType::L;
				case 6: RegisterToTest = TRegisterType::HL;
				case 7: RegisterToTest = TRegisterType::A;
				}
		
				// When comparing the instruction looks only at the first 2 bytes that specifies which Extended Instruction we are executing 
				switch (BitInstruction)
				{
		#pragma region RLC R
					// RLC R
				case RLC_B & 0xFF:
				case RLC_C & 0xFF:
				case RLC_D & 0xFF:
				case RLC_E & 0xFF:
				case RLC_H & 0xFF:
				case RLC_L & 0xFF:
				case RLC_A & 0xFF:
				{
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.rotateLeft(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				}break;
		
				// RLC (HL)
				case RLC_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.rotateLeft(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region RL R
				// RL R
				case RL_B & 0xFF:
				case RL_C & 0xFF:
				case RL_D & 0xFF:
				case RL_E & 0xFF:
				case RL_H & 0xFF:
				case RL_L & 0xFF:
				case RL_A & 0xFF:
				{
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.rotateLeft(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				}break;
		
				// RL (HL)
				case RL_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.rotateLeft(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region SLA R
				// SLA R
				case SLA_B & 0xFF:
				case SLA_C & 0xFF:
				case SLA_D & 0xFF:
				case SLA_E & 0xFF:
				case SLA_H & 0xFF:
				case SLA_L & 0xFF:
				case SLA_A & 0xFF:
				{
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					TUtility::rotateLeft(Register) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
					// Set flags
					mAlu.resetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				}break;
		
				// SLA (HL)
				case SLA_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					TUtility::rotateLeft(Register) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
					// Set flags
					mAlu.resetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region SRA R
				// SRA R
				case SRA_B & 0xFF:
				case SRA_C & 0xFF:
				case SRA_D & 0xFF:
				case SRA_E & 0xFF:
				case SRA_H & 0xFF:
				case SRA_L & 0xFF:
				case SRA_A & 0xFF:
				{
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Get the 7th bit for preservation purpose
					bool Bit = TUtility::getBit(Register, 7);
		
					TUtility::rotateRight(Register) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
					// Put the old 7th bit in the new 7th bit slot
					TUtility::setBit(Register, 7, Bit);
		
					// Set flags
					mAlu.resetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				}break;
		
				// SRA (HL)
				case SRA_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Get the 7th bit for preservation purpose
					bool Bit = TUtility::getBit(Register, 7);
		
					TUtility::rotateRight(Register) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
					// Put the old 7th bit in the new 7th bit slot
					TUtility::setBit(Register, 7, Bit);
		
					// Set flags
					mAlu.resetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region SRL R
				// SRA R
				case SRL_B & 0xFF:
				case SRL_C & 0xFF:
				case SRL_D & 0xFF:
				case SRL_E & 0xFF:
				case SRL_H & 0xFF:
				case SRL_L & 0xFF:
				case SRL_A & 0xFF:
				{
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					TUtility::rotateRight(Register) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
					// Set flags
					mAlu.resetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				}break;
		
				// SRA (HL)
				case SRL_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto& Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					TUtility::rotateRight(Register) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
					// Set flags
					mAlu.resetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region BIT B, R
				case BIT_0_B & 0xFF:
				case BIT_0_C & 0xFF:
				case BIT_0_D & 0xFF:
				case BIT_0_E & 0xFF:
				case BIT_0_H & 0xFF:
				case BIT_0_L & 0xFF:
				case BIT_0_A & 0xFF:
				case BIT_1_B & 0xFF:
				case BIT_1_C & 0xFF:
				case BIT_1_D & 0xFF:
				case BIT_1_E & 0xFF:
				case BIT_1_H & 0xFF:
				case BIT_1_L & 0xFF:
				case BIT_1_A & 0xFF:
				case BIT_2_B & 0xFF:
				case BIT_2_C & 0xFF:
				case BIT_2_D & 0xFF:
				case BIT_2_E & 0xFF:
				case BIT_2_H & 0xFF:
				case BIT_2_L & 0xFF:
				case BIT_2_A & 0xFF:
				case BIT_3_B & 0xFF:
				case BIT_3_C & 0xFF:
				case BIT_3_D & 0xFF:
				case BIT_3_E & 0xFF:
				case BIT_3_H & 0xFF:
				case BIT_3_L & 0xFF:
				case BIT_3_A & 0xFF:
				case BIT_4_B & 0xFF:
				case BIT_4_C & 0xFF:
				case BIT_4_D & 0xFF:
				case BIT_4_E & 0xFF:
				case BIT_4_H & 0xFF:
				case BIT_4_L & 0xFF:
				case BIT_4_A & 0xFF:
				case BIT_5_B & 0xFF:
				case BIT_5_C & 0xFF:
				case BIT_5_D & 0xFF:
				case BIT_5_E & 0xFF:
				case BIT_5_H & 0xFF:
				case BIT_5_L & 0xFF:
				case BIT_5_A & 0xFF:
				case BIT_6_B & 0xFF:
				case BIT_6_C & 0xFF:
				case BIT_6_D & 0xFF:
				case BIT_6_E & 0xFF:
				case BIT_6_H & 0xFF:
				case BIT_6_L & 0xFF:
				case BIT_6_A & 0xFF:
				case BIT_7_B & 0xFF:
				case BIT_7_C & 0xFF:
				case BIT_7_D & 0xFF:
				case BIT_7_E & 0xFF:
				case BIT_7_H & 0xFF:
				case BIT_7_L & 0xFF:
				case BIT_7_A & 0xFF:
				{
					// Get the bit to test				
					TU8BitValue BitPosition = (static_cast<TU8BitValue>(BitInstruction) >> 3) & 7;
		
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Z is set if specified bit is 0; otherwise, it is reset.
					TUtility::getBit(Register, BitPosition) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// H is set.
					mAlu.setFlag(TFlags::H);
		
					// N is set.
					mAlu.resetFlag(TFlags::N);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		
				case BIT_0_INDIRECT_HL & 0xFF:
				case BIT_1_INDIRECT_HL & 0xFF:
				case BIT_2_INDIRECT_HL & 0xFF:
				case BIT_3_INDIRECT_HL & 0xFF:
				case BIT_4_INDIRECT_HL & 0xFF:
				case BIT_5_INDIRECT_HL & 0xFF:
				case BIT_6_INDIRECT_HL & 0xFF:
				case BIT_7_INDIRECT_HL & 0xFF:
				{
					// Get the bit to test				
					TU8BitValue BitPosition = (static_cast<TU8BitValue>(BitInstruction) >> 3) & 7;
		
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Z is set if specified bit is 0; otherwise, it is reset.
					TUtility::getBit(Register, BitPosition) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// H is set.
					mAlu.setFlag(TFlags::H);
		
					// N is set.
					mAlu.resetFlag(TFlags::N);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region SET B, R
				case SET_0_B & 0xFF:
				case SET_0_C & 0xFF:
				case SET_0_D & 0xFF:
				case SET_0_E & 0xFF:
				case SET_0_H & 0xFF:
				case SET_0_L & 0xFF:
				case SET_0_A & 0xFF:
				case SET_1_B & 0xFF:
				case SET_1_C & 0xFF:
				case SET_1_D & 0xFF:
				case SET_1_E & 0xFF:
				case SET_1_H & 0xFF:
				case SET_1_L & 0xFF:
				case SET_1_A & 0xFF:
				case SET_2_B & 0xFF:
				case SET_2_C & 0xFF:
				case SET_2_D & 0xFF:
				case SET_2_E & 0xFF:
				case SET_2_H & 0xFF:
				case SET_2_L & 0xFF:
				case SET_2_A & 0xFF:
				case SET_3_B & 0xFF:
				case SET_3_C & 0xFF:
				case SET_3_D & 0xFF:
				case SET_3_E & 0xFF:
				case SET_3_H & 0xFF:
				case SET_3_L & 0xFF:
				case SET_3_A & 0xFF:
				case SET_4_B & 0xFF:
				case SET_4_C & 0xFF:
				case SET_4_D & 0xFF:
				case SET_4_E & 0xFF:
				case SET_4_H & 0xFF:
				case SET_4_L & 0xFF:
				case SET_4_A & 0xFF:
				case SET_5_B & 0xFF:
				case SET_5_C & 0xFF:
				case SET_5_D & 0xFF:
				case SET_5_E & 0xFF:
				case SET_5_H & 0xFF:
				case SET_5_L & 0xFF:
				case SET_5_A & 0xFF:
				case SET_6_B & 0xFF:
				case SET_6_C & 0xFF:
				case SET_6_D & 0xFF:
				case SET_6_E & 0xFF:
				case SET_6_H & 0xFF:
				case SET_6_L & 0xFF:
				case SET_6_A & 0xFF:
				case SET_7_B & 0xFF:
				case SET_7_C & 0xFF:
				case SET_7_D & 0xFF:
				case SET_7_E & 0xFF:
				case SET_7_H & 0xFF:
				case SET_7_L & 0xFF:
				case SET_7_A & 0xFF:
				{
					// Get the bit to test				
					TU8BitValue BitPosition = (static_cast<TU8BitValue>(BitInstruction) >> 3) & 7;
		
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Set the specified bit
					TUtility::setBit(Register, BitPosition, 1);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		
				case SET_0_INDIRECT_HL & 0xFF:
				case SET_1_INDIRECT_HL & 0xFF:
				case SET_2_INDIRECT_HL & 0xFF:
				case SET_3_INDIRECT_HL & 0xFF:
				case SET_4_INDIRECT_HL & 0xFF:
				case SET_5_INDIRECT_HL & 0xFF:
				case SET_6_INDIRECT_HL & 0xFF:
				case SET_7_INDIRECT_HL & 0xFF:
				{
					// Get the bit to test				
					TU8BitValue BitPosition = (static_cast<TU8BitValue>(BitInstruction) >> 3) & 7;
		
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Set the specified bit
					TUtility::setBit(Register, BitPosition, 1);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region RES B, R
				case RES_0_B & 0xFF:
				case RES_0_C & 0xFF:
				case RES_0_D & 0xFF:
				case RES_0_E & 0xFF:
				case RES_0_H & 0xFF:
				case RES_0_L & 0xFF:
				case RES_0_A & 0xFF:
				case RES_1_B & 0xFF:
				case RES_1_C & 0xFF:
				case RES_1_D & 0xFF:
				case RES_1_E & 0xFF:
				case RES_1_H & 0xFF:
				case RES_1_L & 0xFF:
				case RES_1_A & 0xFF:
				case RES_2_B & 0xFF:
				case RES_2_C & 0xFF:
				case RES_2_D & 0xFF:
				case RES_2_E & 0xFF:
				case RES_2_H & 0xFF:
				case RES_2_L & 0xFF:
				case RES_2_A & 0xFF:
				case RES_3_B & 0xFF:
				case RES_3_C & 0xFF:
				case RES_3_D & 0xFF:
				case RES_3_E & 0xFF:
				case RES_3_H & 0xFF:
				case RES_3_L & 0xFF:
				case RES_3_A & 0xFF:
				case RES_4_B & 0xFF:
				case RES_4_C & 0xFF:
				case RES_4_D & 0xFF:
				case RES_4_E & 0xFF:
				case RES_4_H & 0xFF:
				case RES_4_L & 0xFF:
				case RES_4_A & 0xFF:
				case RES_5_B & 0xFF:
				case RES_5_C & 0xFF:
				case RES_5_D & 0xFF:
				case RES_5_E & 0xFF:
				case RES_5_H & 0xFF:
				case RES_5_L & 0xFF:
				case RES_5_A & 0xFF:
				case RES_6_B & 0xFF:
				case RES_6_C & 0xFF:
				case RES_6_D & 0xFF:
				case RES_6_E & 0xFF:
				case RES_6_H & 0xFF:
				case RES_6_L & 0xFF:
				case RES_6_A & 0xFF:
				case RES_7_B & 0xFF:
				case RES_7_C & 0xFF:
				case RES_7_D & 0xFF:
				case RES_7_E & 0xFF:
				case RES_7_H & 0xFF:
				case RES_7_L & 0xFF:
				case RES_7_A & 0xFF:
				{
					// Get the bit to test				
					TU8BitValue BitPosition = (static_cast<TU8BitValue>(BitInstruction) >> 3) & 7;
		
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Reset the specified bit
					TUtility::setBit(Register, BitPosition, 0);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		
				case RES_0_INDIRECT_HL & 0xFF:
				case RES_1_INDIRECT_HL & 0xFF:
				case RES_2_INDIRECT_HL & 0xFF:
				case RES_3_INDIRECT_HL & 0xFF:
				case RES_4_INDIRECT_HL & 0xFF:
				case RES_5_INDIRECT_HL & 0xFF:
				case RES_6_INDIRECT_HL & 0xFF:
				case RES_7_INDIRECT_HL & 0xFF:
				{
					// Get the bit to test				
					TU8BitValue BitPosition = (static_cast<TU8BitValue>(BitInstruction) >> 3) & 7;
		
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Reset the specified bit
					TUtility::setBit(Register, BitPosition, 0);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region RRC R
				// RRC R
				case RC_B & 0xFF:
				case RC_C & 0xFF:
				case RC_D & 0xFF:
				case RC_E & 0xFF:
				case RC_H & 0xFF:
				case RC_L & 0xFF:
				case RC_A & 0xFF:
				{
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.rotateRight(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				}break;
		
				// RRC (HL)
				case RC_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.rotateRight(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region RR R
				// RR R
				case R_B & 0xFF:
				case R_C & 0xFF:
				case R_D & 0xFF:
				case R_E & 0xFF:
				case R_H & 0xFF:
				case R_L & 0xFF:
				case R_A & 0xFF:
				{
					// Get a ref to the register
					auto& Register = mRegisters.getRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.rotateRight(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				}break;
		
				// RR (HL)
				case R_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.rotateRight(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P/V register
					mAlu.checkParity(Register) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
				}
			} break;
		#pragma endregion
				
				#pragma region Jump Group
		
		#pragma region JP CC,NN
			case JP_NZ_ADR:
			case JP_Z_ADR:
			case JP_NC_ADR:
			case JP_C_ADR:
			case JP_PO_ADR:
			case JP_PE_ADR:
			case JP_P_ADR:
			case JP_M_ADR:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Destination address
				auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
				// See what flag we have to check and base the jump based on the flag condition
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: !mAlu.checkFlag(TFlags::Z) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 1: mAlu.checkFlag(TFlags::Z) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 2: !mAlu.checkFlag(TFlags::C) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 3: mAlu.checkFlag(TFlags::C) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 4: !mAlu.checkFlag(TFlags::P_V) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 5: mAlu.checkFlag(TFlags::P_V) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 6: !mAlu.checkFlag(TFlags::S) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 7: mAlu.checkFlag(TFlags::S) ? ProgramCounter = Address : ProgramCounter += 3; break;
				}
			} break;
		#pragma endregion
		
			// JP NN
			case JP_ADR:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				ProgramCounter = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
			} break;
		
			// JP (HL)
			case JP_INDIRECT_HL:
			{
				loadRegisterFromRegister<T16BitRegister>(TRegisterType::PC, TRegisterType::HL);
			} break;
		
			// JR E
			case JR_dis:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				ProgramCounter += (*Memory)[ProgramCounter + 1] + 2;
			} break;
		
		#pragma region JR CC,DIS
			case JR_NZ_dis:
			case JR_Z_dis:
			case JR_NC_dis:
			case JR_C_dis:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Destination address
				auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
				// See what flag we have to check
				bool Flag;
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 3)
				{
				case 0: Flag = !mAlu.checkFlag(TFlags::Z); break;
				case 1: Flag = mAlu.checkFlag(TFlags::Z); break;
				case 2: Flag = !mAlu.checkFlag(TFlags::C); break;
				case 3: Flag = mAlu.checkFlag(TFlags::C); break;
				}
		
				// Displacement
				const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1] + 2;
		
				// Base the jump based on the flag condition
				Flag ? ProgramCounter.getInternalValue() += Displacement : ProgramCounter += 2;
			} break;
		#pragma endregion
		
			// DJNZ E
			case DJNZ_dis:
			{
				// Get a reference to the B and PC registers
				auto& Register = mRegisters.getRegister<T8BitRegister>(TRegisterType::B);
				auto& ProgramCounter = mRegisters.programCounter();
				const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1] + 2;
		
				// Decrement the B register, if B > 0 add an offset to the PC otherwise goes to the next instruction
				--Register > 0 ? ProgramCounter.getInternalValue() += Displacement : ProgramCounter += 2;
			} break;
		
		#pragma endregion
				
				#pragma region Call group
		
		#pragma region CALL CC,NN
			case CALL_NZ_ADR:
			case CALL_Z_ADR:
			case CALL_NC_ADR:
			case CALL_C_ADR:
			case CALL_PO_ADR:
			case CALL_PE_ADR:
			case CALL_P_ADR:
			case CALL_M_ADR:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Destination address
				auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
				// See what flag we have to check
				bool Flag;
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: Flag = !mAlu.checkFlag(TFlags::Z); break;
				case 1: Flag = mAlu.checkFlag(TFlags::Z); break;
				case 2: Flag = !mAlu.checkFlag(TFlags::C); break;
				case 3: Flag = mAlu.checkFlag(TFlags::C); break;
				case 4: Flag = !mAlu.checkFlag(TFlags::P_V); break;
				case 5: Flag = mAlu.checkFlag(TFlags::P_V); break;
				case 6: Flag = !mAlu.checkFlag(TFlags::S); break;
				case 7: Flag = mAlu.checkFlag(TFlags::S); break;
				}
		
				// Base the jump based on the flag condition
				Flag ? call(Address) : ProgramCounter += 3;
			} break;
		#pragma endregion
		
			// CALL NN
			case CALL_ADR:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// Put the PC on the stack on goes to the memory location specified by the CALL instruction
				call(TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]));
			} break;
		
		#pragma region RET CC
			case RET_NZ:
			case RET_Z:
			case RET_NC:
			case RET_C:
			case RET_PO:
			case RET_PE:
			case RET_P:
			case RET_M:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// See what flag we have to check
				bool Flag;
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: Flag = !mAlu.checkFlag(TFlags::Z); break;
				case 1: Flag = mAlu.checkFlag(TFlags::Z); break;
				case 2: Flag = !mAlu.checkFlag(TFlags::C); break;
				case 3: Flag = mAlu.checkFlag(TFlags::C); break;
				case 4: Flag = !mAlu.checkFlag(TFlags::P_V); break;
				case 5: Flag = mAlu.checkFlag(TFlags::P_V); break;
				case 6: Flag = !mAlu.checkFlag(TFlags::S); break;
				case 7: Flag = mAlu.checkFlag(TFlags::S); break;
				}
		
				// If the check is true execute the return function otherwise goes to the next instruction
				Flag ? returnFromCall() : ++mRegisters.programCounter();
			} break;
		#pragma endregion			
		
			// RET
			case RET:
			{
				returnFromCall();
			} break;
		
		#pragma region RST P
			case RST_0H:
			case RST_08H:
			case RST_10H:
			case RST_18H:
			case RST_20H:
			case RST_28H:
			case RST_30H:
			case RST_38H:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.programCounter();
		
				// See what flag we have to check
				TMemoryAddress Address;
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: Address = 0x00; break;
				case 1: Address = 0x08; break;
				case 2: Address = 0x10; break;
				case 3: Address = 0x18; break;
				case 4: Address = 0x20; break;
				case 5: Address = 0x28; break;
				case 6: Address = 0x30; break;
				case 7: Address = 0x38; break;
				}
		
				// Push the content of PC in the stack
				pushMemory(TRegisterType::PC);
		
				// Move the PC to the desired location
				mRegisters.programCounter() = Address;
			} break;
		#pragma endregion
		
		#pragma endregion
		
				// IN A,(N)
				case IN_A_INDIRECT_port:
				{
				// Get a ref to the accumulator
				auto& Accumulator = mRegisters.accumulator();
	
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.programCounter();
	
				// Get the address of the port
				auto Port = (*Memory)[ProgramCounter + 1];
	
				// Put the data from the data bus to the accumulator
				Accumulator = getDataFromDataBus();
	
				// Increment the PC
				ProgramCounter += 2;
			} break;
	
				// OUT (N),A
				case OUT_INDIRECT_port_A:
				{
				// Get a ref to the accumulator
				auto& Accumulator = mRegisters.accumulator();
	
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.programCounter();
	
				// Get the address of the port
				auto Port = (*Memory)[ProgramCounter + 1];
	
				// Put the data from the data bus to the accumulator
				pushDataToDataBus(Accumulator);
	
				// Increment the PC
				ProgramCounter += 2;
			} break;
		
				#pragma region IX Instruction
				// TOpCodesIXInstructions
			case IX_INSTRUCTIONS:
			{
				// Cast the bit instruction as an 8 bit value
				auto IXInstruction = static_cast<TOpCodesIXInstructions>(fetchInstruction(++mRegisters.programCounter()));
		
				switch (IXInstruction)
				{
					// PUSH IX
				case PUSH_IX:
				{
					pushMemory(TRegisterType::IX);
		
					++mRegisters.programCounter();
				} break;
		
				// POP IX
				case POP_IX:
				{
					popMemory(TRegisterType::IX);
		
					++mRegisters.programCounter();
				} break;
		
				// EX (SP), IX
				case EX_INDIRECT_SP_IX:
				{
					auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					IXRegister.getHighOrderRegister() = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::SP) + 1];
					IXRegister.getLowOrderRegister() = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::SP)];
					mRegisters.programCounter() += 1;
				} break;
		
				// AND (IX + DIS)
				case AND_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluAnd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// OR (IX + DIS)
				case OR_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluOr<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// XOR (IX + DIS)
				case XOR_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluXor<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// CP (IX + DIS)
				case CP_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluCp<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// ADD IX, BC
				case ADD_IX_BC:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD IX, DE
				case ADD_IX_DE:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD IX, IX
				case ADD_IX_IX:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD IX, SP
				case ADD_IX_SP:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::SP);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD A, (IX + DIS)
				case ADD_A_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// ADC A, (IX + DIS)
				case ADC_A_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement] + mAlu.checkFlag(TFlags::C));
		
					mRegisters.programCounter() += 2;
				} break;
		
				// SBC A, (IX + DIS)
				case SBC_A_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement] - mAlu.checkFlag(TFlags::C));
		
					mRegisters.programCounter() += 2;
				} break;
		
				// INC IX
				case INC_IX:
				{
					++mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
		
					++mRegisters.programCounter();
				} break;
		
				// INC (IX + DIS)
				case INC_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluInc<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// DEX IX
				case DEC_IX:
				{
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
		
					++mRegisters.programCounter();
				} break;
		
				// DEC (IX + DIS)
				case DEC_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluDec<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
		#pragma region IX Bit instruction
				// TOpCodesIXBitInstructions
				case IX_BIT_INSTRUCTIONS:
				{
					// Get the instruction
					auto IXBitInstruction = static_cast<TOpCodesIXBitInstructions>(fetchInstruction(++mRegisters.programCounter()));
		
					switch (IXBitInstruction)
					{
						// RLC (IX + DIS)
					case RLC_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateLeft<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], false);
		
						mRegisters.programCounter() += 2;
					} break;
		
		#pragma region Check Bit
					// BIT 0, (IX + DIS)
					case BIT_0_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 0) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 1, (IX + DIS)
					case BIT_1_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 1) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 2, (IX + DIS)
					case BIT_2_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 2) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 3, (IX + DIS)
					case BIT_3_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 3) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 4, (IX + DIS)
					case BIT_4_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 4) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 5, (IX + DIS)
					case BIT_5_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 5) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 6, (IX + DIS)
					case BIT_6_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 6) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 7, (IX + DIS)
					case BIT_7_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 7) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		#pragma endregion
		
		#pragma region Set Bit
					// SET 0, (IX + DIS)
					case SET_0_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 0, 1);
					} break;
		
					// SET 1, (IX + DIS)
					case SET_1_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 1, 1);
					} break;
		
					// SET 2, (IX + DIS)
					case SET_2_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 2, 1);
					} break;
		
					// SET 3, (IX + DIS)
					case SET_3_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 3, 1);
					} break;
		
					// SET 4, (IX + DIS)
					case SET_4_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 4, 1);
					} break;
		
					// SET 5, (IX + DIS)
					case SET_5_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 5, 1);
					} break;
		
					// SET 6, (IX + DIS)
					case SET_6_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 6, 1);
					} break;
		
					// SET 7, (IX + DIS)
					case SET_7_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 7, 1);
					} break;
		#pragma endregion
		
		#pragma region Reset Bit
					// SET 0, (IX + DIS)
					case RES_0_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 0, 0);
					} break;
		
					// SET 1, (IX + DIS)
					case RES_1_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 1, 0);
					} break;
		
					// SET 2, (IX + DIS)
					case RES_2_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 2, 0);
					} break;
		
					// SET 3, (IX + DIS)
					case RES_3_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 3, 0);
					} break;
		
					// SET 4, (IX + DIS)
					case RES_4_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 4, 0);
					} break;
		
					// SET 5, (IX + DIS)
					case RES_5_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 5, 0);
					} break;
		
					// SET 6, (IX + DIS)
					case RES_6_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 6, 0);
					} break;
		
					// SET 7, (IX + DIS)
					case RES_7_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 7, 0);
					} break;
		#pragma endregion
		
					// RL (IX + DIS)
					case RL_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateLeft<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// RR (IX + DIS)
					case R_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateRight((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// RRC (IX + DIS)
					case RC_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateRight((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement], false);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// SLA (IX + DIS)
					case SLA_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						TUtility::rotateLeft((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
						// Set flags
						mAlu.resetFlag(TFlags::N | TFlags::H);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// SRA (IX + DIS)
					case SRA_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
						auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
		
						// Get the 7th bit for preservation purpose
						bool Bit = TUtility::getBit(IXRegister, 7);
		
						TUtility::rotateRight(IXRegister) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
						// Put the old 7th bit in the new 7th bit slot
						TUtility::setBit(IXRegister, 7, Bit);
		
						// Set flags
						mAlu.resetFlag(TFlags::N | TFlags::H);
					} break;
		
					// SRL (IX + DIS)
					case SRL_INDIRECT_IX_dis:
					{
						TUtility::rotateRight(mRegisters.getRegister<T16BitRegister>(TRegisterType::IX)) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
						// Set flags
						mAlu.resetFlag(TFlags::N | TFlags::H);
					} break;
					}
				} break;
		#pragma endregion
		
				// JP (IX)
				case JP_INDIRECT_IX:
				{
					loadRegisterFromRegister<T16BitRegister>(TRegisterType::PC, TRegisterType::IX);
				} break;
		
		#pragma region Load Instruction
				// LD IX, N
				case LD_IX_n:
				{
					// Get a ref to the PC
					auto& ProgramCounter = mRegisters.programCounter();
		
					mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (NN), IX
				case LD_INDIRECT_ADR_IX:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
					(*Memory)[Address + 1] = IXRegister.getHighOrderRegister();
					(*Memory)[Address] = IXRegister.getLowOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				// LD IX, (NN)
				case LD_IX_INDIRECT_ADR:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
					IXRegister = TUtility::to16BitValue((*Memory)[Address + 1], (*Memory)[Address]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (IX + DIS), N
				case LD_INDIRECT_IX_dis_n:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
					const auto Number = (*Memory)[ProgramCounter + 2];
		
					(*Memory)[IXRegister + Displacement] = Number;
		
					ProgramCounter += 3;
				} break;
		
				// LD B, (IX + DIS)
				case LD_B_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::B, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD C, (IX + DIS)
				case LD_C_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::C, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD D, (IX + DIS)
				case LD_D_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::D, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD E, (IX + DIS)
				case LD_E_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::E, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD H, (IX + DIS)
				case LD_H_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::H, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD L, (IX + DIS)
				case LD_L_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::L, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), B
				case LD_INDIRECT_IX_dis_B:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::B, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), C
				case LD_INDIRECT_IX_dis_C:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::C, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), D
				case LD_INDIRECT_IX_dis_D:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::D, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), E
				case LD_INDIRECT_IX_dis_E:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::E, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), H
				case LD_INDIRECT_IX_dis_H:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::H, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), L
				case LD_INDIRECT_IX_dis_L:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::L, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), A
				case LD_INDIRECT_IX_dis_A:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::A, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD A, (IX + DIS)
				case LD_A_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IXRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::A, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
		#pragma endregion
		
				// SUB (IX + DIS)
				case SUB_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// LD SP, IX
				case LD_SP_IX:
				{
					loadRegisterFromRegister<T16BitRegister>(TRegisterType::SP, TRegisterType::IX);
		
					++mRegisters.programCounter();
				} break;
				}
			} break;
		#pragma endregion
				
				#pragma region Extended instructions
			// TOpCodesExtendedInstruction
			case EXTENDED_INSTRUCTIONS:
			{
				// Cast the bit instruction as an 8 bit value
				auto ExtendedInstruction = static_cast<TOpCodesExtendedInstruction>(fetchInstruction(++mRegisters.programCounter()));
		
				switch (ExtendedInstruction)
				{
		#pragma region Block Transfer
					// LDI
				case LDI:
				{
					(*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::DE)] = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
					++mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
					++mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N flags
					mAlu.resetFlag(TFlags::H | TFlags::N);
		
					// P/V is set if BC – 1 != 0; otherwise, it is reset
					mRegisters.getRegister<T16BitRegister>(TRegisterType::BC) - 1 != 0 ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					++mRegisters.programCounter();
				}break;
		
				// LDIR
				case LDIR:
				{
					(*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::DE)] = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
					++mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
					++mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N and P/V flags
					mAlu.resetFlag(TFlags::H | TFlags::N | TFlags::P_V);
		
					// If BC is 0 than terminates the operation bu allowing the program to go further otherwise decrement the PC by 2 to allows the operation to be executed again
					mRegisters.getRegister<T16BitRegister>(TRegisterType::BC) == 0 ? ++mRegisters.programCounter() : mRegisters.programCounter() -= 2;
				}break;
		
				// LDD
				case LDD:
				{
					(*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::DE)] = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N flags
					mAlu.resetFlag(TFlags::H | TFlags::N);
		
					// P/V is set if BC – 1 != 0; otherwise, it is reset
					mRegisters.getRegister<T16BitRegister>(TRegisterType::BC) - 1 != 0 ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					++mRegisters.programCounter();
				} break;
		
				// LDDR
				case LDDR:
				{
					(*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::DE)] = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N flags
					mAlu.resetFlag(TFlags::H | TFlags::N | TFlags::P_V);
		
					// If BC is 0 than terminates the operation bu allowing the program to go further otherwise decrement the PC by 2 to allows the operation to be executed again
					mRegisters.getRegister<T16BitRegister>(TRegisterType::BC) == 0 ? ++mRegisters.programCounter() : mRegisters.programCounter() -= 2;
				} break;
		#pragma endregion
		
		#pragma region Search instruction
				// CPI
				case CPI:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.accumulator() == (*Memory)[HLRegister];
		
					// Increment HL and decrement BC
					++HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.setFlag(TFlags::N);
		
					// C is not affected.
		
					// Increment PC
					++mRegisters.programCounter();
				} break;
		
				// CPIR
				case CPIR:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.accumulator() == (*Memory)[HLRegister];
		
					// Increment HL and decrement BC
					++HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.setFlag(TFlags::N);
		
					// C is not affected.
		
					// If decrementing causes BC to go to 0 or if A = (HL), the instruction is terminated.If BC is not 0 and A != (HL), the program counter is decremented by two and the instruction is repeated.
					Result == true || BCRegister == 0 ? ++mRegisters.programCounter() : mRegisters.programCounter();
				} break;
		
				// CPD
				case CPD:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.accumulator() == (*Memory)[HLRegister];
		
					// Decrement BC and HL
					--HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.setFlag(TFlags::N);
		
					// C is not affected.
		
					// Increment PC
					++mRegisters.programCounter();
				} break;
		
				// CPDR
				case CPDR:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.accumulator() == (*Memory)[HLRegister];
		
					// Decrement BC and HL
					--HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.setFlag(TFlags::N);
		
					// C is not affected.
		
					// If decrementing causes BC to go to 0 or if A = (HL), the instruction is terminated.If BC is not 0 and A != (HL), the program counter is decremented by two and the instruction is repeated.
					Result == true || BCRegister == 0 ? ++mRegisters.programCounter() : mRegisters.programCounter();
				} break;
		#pragma endregion
		
				// NEG
				case NEG:
				{
					// Get a ref to the aaccumulator
					auto& Accumulator = mRegisters.accumulator();
		
					// Bitwise complement of the accumulator
					Accumulator = ~Accumulator;
		
					// S is set if result is negative; otherwise, it is reset.
					Accumulator > 0x7f ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z is set if result is 0; otherwise, it is reset.
					Accumulator == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
					// H register
					mAlu.checkBorrowFromBit<TU8BitValue>(4, Accumulator, ~Accumulator) ? mAlu.setFlag(TFlags::H) : mAlu.resetFlag(TFlags::H);
		
					// P / V is set if Accumulator was 80h before operation; otherwise, it is reset.
					~Accumulator == 0x80 ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.setFlag(TFlags::N);
		
					// C is set if Accumulator was not 00h before operation; otherwise, it is reset.
					~Accumulator != 0 ? mAlu.setFlag(TFlags::C) : mAlu.resetFlag(TFlags::C);
		
				} break;
		
				// IM 0
				case IM_0:
				{
					mInterruptMode = TInterruptMode::MODE_0;
		
					++mRegisters.programCounter();
				} break;
		
				// IM 1
				case IM_1:
				{
					mInterruptMode = TInterruptMode::MODE_0;
		
					++mRegisters.programCounter();
				} break;
		
				// IM 2
				case IM_2:
				{
					mInterruptMode = TInterruptMode::MODE_0;
		
					++mRegisters.programCounter();
				} break;
		
		#pragma region 16-Bit Arithmetic Group
		
		#pragma region ADC HL, SS
				case ADC_HL_BC:
				case ADC_HL_DE:
				case ADC_HL_HL:
				case ADC_HL_SP:
				{
					TRegisterType SourceRegister;
		
					// Get the source address by looking at the first 3 bits
					switch (static_cast<TU8BitValue>(OpCode) >> 4 & 2)
					{
					case 0: SourceRegister = TRegisterType::BC; break;
					case 1: SourceRegister = TRegisterType::DE; break;
					case 2: SourceRegister = TRegisterType::HL; break;
					case 3: SourceRegister = TRegisterType::SP; break;
					}
		
					// Perform the addition
					mAlu.aluAdd<TU16BitValue>(mRegisters.getRegister<T16BitRegister>(SourceRegister) + mAlu.checkFlag(TFlags::C));
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma region SBC HL, SS
				case SBC_HL_BC:
				case SBC_HL_DE:
				case SBC_HL_HL:
				case SBC_HL_SP:
				{
					TRegisterType SourceRegister;
		
					// Get the source address by looking at the first 3 bits
					switch (static_cast<TU8BitValue>(OpCode) >> 4 & 2)
					{
					case 0: SourceRegister = TRegisterType::BC; break;
					case 1: SourceRegister = TRegisterType::DE; break;
					case 2: SourceRegister = TRegisterType::HL; break;
					case 3: SourceRegister = TRegisterType::SP; break;
					}
		
					// Perform the addition
					mAlu.aluSub<TU16BitValue>(mRegisters.getRegister<T16BitRegister>(SourceRegister) - mAlu.checkFlag(TFlags::C));
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		#pragma endregion
		
		#pragma endregion
		
		#pragma region Shift function
				// RLD
				case RLD:
				{
					// Get a ref to the accumulator and HL
					auto& Accumulator = mRegisters.accumulator();
					auto& IndirectMemory = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Swap low nibble of (HL) with high nibble of (HL)
					{
						auto LowerNibble = TUtility::getLowerNible(IndirectMemory);
						auto UpperNibble = TUtility::getUpperNible(IndirectMemory);
						auto Temp = UpperNibble;
		
						UpperNibble = (UpperNibble & 0b00001111) | (LowerNibble << 4);
						LowerNibble = (LowerNibble & 0b11110000) | (Temp >> 4);
					}
		
					// Swap low nibble of (HL) with low nibble of Accumulator
					{
						auto LowerAccumulatorNibble = TUtility::getLowerNible(Accumulator);
						auto LowerIndirMemoryNibble = TUtility::getLowerNible(IndirectMemory);
						auto Temp = LowerAccumulatorNibble;
		
						LowerAccumulatorNibble = (LowerAccumulatorNibble & 0b11110000) | LowerIndirMemoryNibble;
						LowerIndirMemoryNibble = (LowerIndirMemoryNibble & 0b11110000) | Temp;
					}
		
					// S is set if the Accumulator is negative after an operation; otherwise, it is reset.
					Accumulator > 0x7F ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z is set if the Accumulator is 0 after an operation; otherwise, it is reset.
					Accumulator == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P / V is set if the parity of the Accumulator is even after an operation; otherwise, it is reset.
					mAlu.checkParity(Accumulator) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// H and N is reset.
					mAlu.resetFlag(TFlags::H | TFlags::N);
		
					// C is not affected.
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		
				// RRD
				case RRD:
				{
					// Get a ref to the accumulator and HL
					auto& Accumulator = mRegisters.accumulator();
					auto& IndirectMemory = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Swap low nibble of (HL) with low nibble of Accumulator
					{
						auto LowerAccumulatorNibble = TUtility::getLowerNible(Accumulator);
						auto LowerIndirMemoryNibble = TUtility::getLowerNible(IndirectMemory);
						auto Temp = LowerAccumulatorNibble;
		
						LowerAccumulatorNibble = (LowerAccumulatorNibble & 0b11110000) | LowerIndirMemoryNibble;
						LowerIndirMemoryNibble = (LowerIndirMemoryNibble & 0b11110000) | Temp;
					}
		
					// Swap low nibble of (HL) with high nibble of (HL)
					{
						auto LowerNibble = TUtility::getLowerNible(IndirectMemory);
						auto UpperNibble = TUtility::getUpperNible(IndirectMemory);
						auto Temp = UpperNibble;
		
						UpperNibble = (UpperNibble & 0b00001111) | (LowerNibble << 4);
						LowerNibble = (LowerNibble & 0b11110000) | (Temp >> 4);
					}
		
					// S is set if the Accumulator is negative after an operation; otherwise, it is reset.
					Accumulator > 0x7F ? mAlu.setFlag(TFlags::S) : mAlu.resetFlag(TFlags::S);
		
					// Z is set if the Accumulator is 0 after an operation; otherwise, it is reset.
					Accumulator == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
					// P / V is set if the parity of the Accumulator is even after an operation; otherwise, it is reset.
					mAlu.checkParity(Accumulator) ? mAlu.setFlag(TFlags::P_V) : mAlu.resetFlag(TFlags::P_V);
		
					// H and N is reset.
					mAlu.resetFlag(TFlags::H | TFlags::N);
		
					// C is not affected.
		
					// Increment the PC
					++mRegisters.programCounter();
				} break;
		
		#pragma endregion
		
				// RETI
				case RETI:
				{
		
				} break;
		
				// RETN
				case RETN:
				{
		
				} break;
		
		
				case IN_B_INDIRECT_C:
					break;
				case IN_C_INDIRECT_C:
					break;
				case IN_D_INDIRECT_C:
					break;
				case IN_E_INDIRECT_C:
					break;
				case IN_H_INDIRECT_C:
					break;
				case IN_L_INDIRECT_C:
					break;
				case IN_A_INDIRECT_C:
					break;
				case INI:
					break;
				case INIR:
					break;
				case IND:
					break;
				case INDR:
					break;
				case OUT_INDIRECT_C_B:
					break;
				case OUT_INDIRECT_C_C:
					break;
				case OUT_INDIRECT_C_D:
					break;
				case OUT_INDIRECT_C_E:
					break;
				case OUT_INDIRECT_C_H:
					break;
				case OUT_INDIRECT_C_L:
					break;
				case OUT_INDIRECT_C_A:
					break;
				case OUTI:
					break;
				case OTIR:
					break;
				case OUTD:
					break;
				case OTDR:
					break;
		
					// LD (NN), BC
				case LD_INDIRECT_ADR_BC:
				{
					// get a ref to the PC and BC
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& SourceRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Get the address destination
					auto Address = TUtility::to16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					(*Memory)[Address] = SourceRegister.getLowOrderRegister();
					(*Memory)[Address + 1] = SourceRegister.getHighOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				case LD_I_A:
					break;
		
					// LD BC, (NN)
				case LD_BC_INDIRECT_ADR:
				{
					// get a ref to the PC and BC
					auto& ProgramCounter = mRegisters.programCounter();
					auto& DestinationRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// Get the address source
					auto Address = TUtility::to16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					DestinationRegister.getLowOrderRegister() = (*Memory)[Address];
					DestinationRegister.getHighOrderRegister() = (*Memory)[Address + 1];
		
					ProgramCounter += 3;
				} break;
		
				case LD_R_A:
					break;
		
					// LD (NN), DE
				case LD_INDIRECT_ADR_DE:
				{
					// get a ref to the PC and DE
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& SourceRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
		
					// Get the address destination
					auto Address = TUtility::to16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					(*Memory)[Address] = SourceRegister.getLowOrderRegister();
					(*Memory)[Address + 1] = SourceRegister.getHighOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				case LD_A_I:
					break;
		
					// LD DE, (NN)
				case LD_DE_INDIRECT_ADR:
				{
					// get a ref to the PC and DE
					auto& ProgramCounter = mRegisters.programCounter();
					auto& DestinationRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
		
					// Get the address source
					auto Address = TUtility::to16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					DestinationRegister.getLowOrderRegister() = (*Memory)[Address];
					DestinationRegister.getHighOrderRegister() = (*Memory)[Address + 1];
		
					ProgramCounter += 3;
				} break;
		
				case LD_A_R:
					break;
		
					// LD (NN), SP
				case LD_INDIRECT_ADR_SP:
				{
					// get a ref to the PC and SP
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& SourceRegister = mRegisters.stackPointer();
		
					// Get the address destination
					auto Address = TUtility::to16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					(*Memory)[Address] = SourceRegister.getLowOrderRegister();
					(*Memory)[Address + 1] = SourceRegister.getHighOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				// LD SP, (NN)
				case LD_SP_INDIRECT_ADR:
				{
					// get a ref to the PC and SP
					auto& ProgramCounter = mRegisters.programCounter();
					auto& DestinationRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::SP);
		
					// Get the address source
					auto Address = TUtility::to16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					DestinationRegister.getLowOrderRegister() = (*Memory)[Address];
					DestinationRegister.getHighOrderRegister() = (*Memory)[Address + 1];
		
					ProgramCounter += 3;
				} break;
				}
			} break;
		
		#pragma endregion
				
				#pragma region IY Instruction
			// TOpCodesIYInstructions
			case IY_INSTRUCTIONS:
			{
				// Cast the bit instruction as an 8 bit value
				auto IYInstruction = static_cast<TOpCodesIYInstructions>(fetchInstruction(++mRegisters.programCounter()));
		
				switch (IYInstruction)
				{
					// PUSH IY
				case PUSH_IY:
				{
					pushMemory(TRegisterType::IY);
		
					++mRegisters.programCounter();
				} break;
		
				// POP IY
				case POP_IY:
				{
					popMemory(TRegisterType::IY);
		
					++mRegisters.programCounter();
				} break;
		
				// EX (SP), IY
				case EX_INDIRECT_SP_IY:
				{
					auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					IYRegister.getHighOrderRegister() = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::SP) + 1];
					IYRegister.getLowOrderRegister() = (*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::SP)];
					mRegisters.programCounter() += 1;
				} break;
		
				// AND (IY + DIS)
				case AND_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluAnd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// OR (IY + DIS)
				case OR_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluOr<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// XOR (IY + DIS)
				case XOR_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluXor<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// CP (IY + DIS)
				case CP_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluCp<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// ADD IY, BC
				case ADD_IY_BC:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::BC);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD IY, DE
				case ADD_IY_DE:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::DE);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD IY, IY
				case ADD_IY_IY:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD IY, SP
				case ADD_IY_SP:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.getRegister<T16BitRegister>(TRegisterType::SP);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.checkCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.setFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.checkCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.programCounter();
				} break;
		
				// ADD A, (IY + DIS)
				case ADD_A_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// ADC A, (IY + DIS)
				case ADC_A_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluAdd<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement] + mAlu.checkFlag(TFlags::C));
		
					mRegisters.programCounter() += 2;
				} break;
		
				// SBC A, (IY + DIS)
				case SBC_A_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement] - mAlu.checkFlag(TFlags::C));
		
					mRegisters.programCounter() += 2;
				} break;
		
				// INC IY
				case INC_IY:
				{
					++mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
		
					++mRegisters.programCounter();
				} break;
		
				// INC (IY + DIS)
				case INC_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluInc<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// DEX IY
				case DEC_IY:
				{
					--mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
		
					++mRegisters.programCounter();
				} break;
		
				// DEC (IY + DIS)
				case DEC_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluDec<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
		#pragma region IY Bit instruction
				// TOpCodesIYBitInstructions
				case IY_BIT_INSTRUCTIONS:
				{
					// Get the instruction
					auto IYBitInstruction = static_cast<TOpCodesIYBitInstructions>(fetchInstruction(++mRegisters.programCounter()));
		
					switch (IYBitInstruction)
					{
						// RLC (IY + DIS)
					case RLC_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateLeft<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], false);
		
						mRegisters.programCounter() += 2;
					} break;
		
		#pragma region Check Bit
					// BIT 0, (IY + DIS)
					case BIT_0_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 0) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 1, (IY + DIS)
					case BIT_1_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 1) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 2, (IY + DIS)
					case BIT_2_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 2) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 3, (IY + DIS)
					case BIT_3_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 3) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 4, (IY + DIS)
					case BIT_4_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 4) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 5, (IY + DIS)
					case BIT_5_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 5) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 6, (IY + DIS)
					case BIT_6_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 6) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		
					// BIT 7, (IY + DIS)
					case BIT_7_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::getBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 7) == 0 ? mAlu.setFlag(TFlags::Z) : mAlu.resetFlag(TFlags::Z);
		
						// H is set.
						mAlu.setFlag(TFlags::H);
		
						// N is set.
						mAlu.resetFlag(TFlags::N);
					} break;
		#pragma endregion
		
		#pragma region Set Bit
					// SET 0, (IY + DIS)
					case SET_0_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 0, 1);
					} break;
		
					// SET 1, (IY + DIS)
					case SET_1_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 1, 1);
					} break;
		
					// SET 2, (IY + DIS)
					case SET_2_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 2, 1);
					} break;
		
					// SET 3, (IY + DIS)
					case SET_3_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 3, 1);
					} break;
		
					// SET 4, (IY + DIS)
					case SET_4_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 4, 1);
					} break;
		
					// SET 5, (IY + DIS)
					case SET_5_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 5, 1);
					} break;
		
					// SET 6, (IY + DIS)
					case SET_6_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 6, 1);
					} break;
		
					// SET 7, (IY + DIS)
					case SET_7_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 7, 1);
					} break;
		#pragma endregion
		
		#pragma region Reset Bit
					// SET 0, (IY + DIS)
					case RES_0_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 0, 0);
					} break;
		
					// SET 1, (IY + DIS)
					case RES_1_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 1, 0);
					} break;
		
					// SET 2, (IY + DIS)
					case RES_2_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 2, 0);
					} break;
		
					// SET 3, (IY + DIS)
					case RES_3_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 3, 0);
					} break;
		
					// SET 4, (IY + DIS)
					case RES_4_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 4, 0);
					} break;
		
					// SET 5, (IY + DIS)
					case RES_5_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 5, 0);
					} break;
		
					// SET 6, (IY + DIS)
					case RES_6_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 6, 0);
					} break;
		
					// SET 7, (IY + DIS)
					case RES_7_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						// Set the specified bit
						TUtility::setBit((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 7, 0);
					} break;
		#pragma endregion
		
					// RL (IY + DIS)
					case RL_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateLeft<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// RR (IY + DIS)
					case R_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateRight((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// RRC (IY + DIS)
					case RC_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						mAlu.rotateRight((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement], false);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// SLA (IY + DIS)
					case SLA_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
		
						TUtility::rotateLeft((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
						// Set flags
						mAlu.resetFlag(TFlags::N | TFlags::H);
		
						mRegisters.programCounter() += 2;
					} break;
		
					// SRA (IY + DIS)
					case SRA_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*Memory)[mRegisters.programCounter()];;
						auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
		
						// Get the 7th bit for preservation purpose
						bool Bit = TUtility::getBit(IYRegister, 7);
		
						TUtility::rotateRight(IYRegister) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
						// Put the old 7th bit in the new 7th bit slot
						TUtility::setBit(IYRegister, 7, Bit);
		
						// Set flags
						mAlu.resetFlag(TFlags::N | TFlags::H);
					} break;
		
					// SRL (IY + DIS)
					case SRL_INDIRECT_IY_dis:
					{
						TUtility::rotateRight(mRegisters.getRegister<T16BitRegister>(TRegisterType::IY)) == 0 ? mAlu.resetFlag(TFlags::C) : mAlu.setFlag(TFlags::C);
		
						// Set flags
						mAlu.resetFlag(TFlags::N | TFlags::H);
					} break;
					}
				} break;
		#pragma endregion
		
				// JP (IY)
				case JP_INDIRECT_IY:
				{
					loadRegisterFromRegister<T16BitRegister>(TRegisterType::PC, TRegisterType::IY);
				} break;
		
		#pragma region Load Instruction
				// LD IY, N
				case LD_IY_n:
				{
					// Get a ref to the PC
					auto& ProgramCounter = mRegisters.programCounter();
		
					mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (NN), IY
				case LD_INDIRECT_ADR_IY:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
					(*Memory)[Address + 1] = IYRegister.getHighOrderRegister();
					(*Memory)[Address] = IYRegister.getLowOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				// LD IY, (NN)
				case LD_IY_INDIRECT_ADR:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const auto Address = TUtility::to16BitValue((*Memory)[ProgramCounter + 2], (*Memory)[ProgramCounter + 1]);
		
					IYRegister = TUtility::to16BitValue((*Memory)[Address + 1], (*Memory)[Address]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (IY + DIS), N
				case LD_INDIRECT_IY_dis_n:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
					const auto Number = (*Memory)[ProgramCounter + 2];
		
					(*Memory)[IYRegister + Displacement] = Number;
		
					ProgramCounter += 3;
				} break;
		
				// LD B, (IY + DIS)
				case LD_B_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::B, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD C, (IY + DIS)
				case LD_C_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::C, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD D, (IY + DIS)
				case LD_D_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::D, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD E, (IY + DIS)
				case LD_E_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::E, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD H, (IY + DIS)
				case LD_H_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::H, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD L, (IY + DIS)
				case LD_L_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::L, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), B
				case LD_INDIRECT_IY_dis_B:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::B, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), C
				case LD_INDIRECT_IY_dis_C:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::C, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), D
				case LD_INDIRECT_IY_dis_D:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::D, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), E
				case LD_INDIRECT_IY_dis_E:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::E, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), H
				case LD_INDIRECT_IY_dis_H:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::H, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), L
				case LD_INDIRECT_IY_dis_L:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::L, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), A
				case LD_INDIRECT_IY_dis_A:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadMemoryFromRegister<T8BitRegister>(TRegisterType::A, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD A, (IY + DIS)
				case LD_A_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.programCounter();
					const auto& IYRegister = mRegisters.getRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*Memory)[ProgramCounter + 1];
		
					loadRegisterFromMemory<T8BitRegister>(TRegisterType::A, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
		#pragma endregion
		
				// SUB (IY + DIS)
				case SUB_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*Memory)[mRegisters.programCounter() + 1];;
		
					mAlu.aluSub<TU8BitValue>((*Memory)[mRegisters.getRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.programCounter() += 2;
				} break;
		
				// LD SP, IY
				case LD_SP_IY:
				{
					loadRegisterFromRegister<T16BitRegister>(TRegisterType::SP, TRegisterType::IY);
		
					++mRegisters.programCounter();
				} break;
				}
			} break;
		#pragma endregion
		
			}
		
			return 0;
		}
	
		TU8BitValue TZ80Component::getDataFromDataBus()
		{
			mDataBus = mParent->getComponentAsPtr<TPinComponent>()->pinsToValue<TU8BitValue>(CPUPinGroup::DataBus);
	
			return mDataBus;
		}
	
		nne::TRegisterType TZ80Component::fetchRegisterType(const TU8BitValue& OpCode, const TU8BitValue& Shift, const TU8BitValue& Mask)
		{
			switch (static_cast<TU8BitValue>(OpCode) >> Shift & Mask)
			{
				case 0: return TRegisterType::B; break;
				case 1: return TRegisterType::C; break;
				case 2: return TRegisterType::D; break;
				case 3: return TRegisterType::E; break;
				case 4: return TRegisterType::H; break;
				case 5: return TRegisterType::L; break;
				case 7: return TRegisterType::A; break;
			}
		}

		void TZ80Component::pushDataToDataBus(const TU8BitValue & Value)
		{
			mDataBus = Value;
	
			mParent->getComponentAsPtr<TPinComponent>()->valueToPins<TU8BitValue>(mDataBus, CPUPinGroup::DataBus);
		}
		
		void TZ80Component::pushDataToAddressBus(const TU16BitValue& Value)
		{
			mAddressBus = Value;
	
			mParent->getComponentAsPtr<TPinComponent>()->valueToPins<TU16BitValue>(mAddressBus, CPUPinGroup::AddressBus);
		}
	
		TU16BitValue TZ80Component::getDataFromAddressBus()
		{
			mAddressBus = mParent->getComponentAsPtr<TPinComponent>()->pinsToValue<TU16BitValue>(CPUPinGroup::AddressBus);
	
			return mAddressBus;
		}
	
		void TZ80Component::pushMemory(const TRegisterType& Register)
		{
			// Get the SP reference
			auto& StackPointer = mRegisters.stackPointer();

			// Get a ref to the RAM internal memory for better aces
			auto& Memory = mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory();
		
			// Get a reference to the register
			const T16BitRegister& RegisterReference = mRegisters.getRegister<T16BitRegister>(Register);
		
			// First decrement PC and load the high order register
			Memory[--StackPointer] = TUtility::getUpper8Bit(RegisterReference);
		
			// Than decrement PC again and load the low order register
			Memory[--StackPointer] = TUtility::getLower8Bit(RegisterReference);
		}
		
		void TZ80Component::popMemory(const TRegisterType& Register)
		{
			// Get the SP reference
			auto& StackPointer = mRegisters.stackPointer();

			// Get a ref to the RAM internal memory for better aces
			auto& Memory = mRam->getComponentAsPtr<TMemoryComponent>()->getInternalMemory();
		
			// Get a reference to the register
			T16BitRegister& RegisterReference = mRegisters.getRegister<T16BitRegister>(Register);
		
			// Load the content pointed bu the SP in the register specified in the argument
			RegisterReference = TUtility::to16BitValue(Memory[StackPointer + 1], Memory[StackPointer]);
		
			// Increment the stack pointer by 2
			StackPointer += 2;
		}
		
		void TZ80Component::call(const TU16BitValue& Address)
		{
			// Get a reference to the PC
			auto& ProgramCounter = mRegisters.programCounter();
		
			// Increment the PC by 3 to make sure that when we return from the function it goes to the next instruction
			ProgramCounter += 3;
		
			// Push the content of the PC in the stack
			pushMemory(TRegisterType::PC);
		
			// Goes to the location specified by the argument
			ProgramCounter = Address;
		}
		
		void TZ80Component::returnFromCall()
		{
			// Pop the old PC value from the SP
			popMemory(TRegisterType::PC);
		}

		void TZ80Component::fetchInstructionMCycle()
		{
			// Instruction fetch
			switch (mTStates)
			{
				// T1
				case 0:
				{
					// The Program Counter is placed on the address bus at the beginning of the M1 cycle
					// Select the instruction by putting the address in the address bus
					auto& PC = mRegisters.programCounter();
					pushDataToAddressBus(PC);
				} break;

				// T2
				case 1:
				{
					// One half clock cycle later, the MREQ signal goes active.At this time, the address to memory has had time to stabilize 
					// so that the falling edge of MREQ can be used directly as a chip enable clock to dynamic memories.
					// The RD line also goes active to indicate that the memory read data should be enabled onto the CPU data bus.

					// Get a ref to the PinComponent
					auto Pins = mParent->getComponentAsPtr<TPinComponent>();

					// Activates MREQ and RD pin
					Pins->getPin(19).changePinStatus(tcomponents::TPin::LOW, true); // MREQ
					Pins->getPin(21).changePinStatus(tcomponents::TPin::LOW, true); // RD
				} break;

				// T3
				case 2:
				{
					// The CPU samples the data from the memory space on the data bus with the rising edge of the clock of state T3, and this same edge is used by the
					// CPU to turn off the RD and MREQ signals. As a result, the data is sampled by the CPU before the RD signal becomes inactive

					// Get the instruction from the bus
					mCurrentInstruction = getDataFromDataBus();

					// Get a ref to the PinComponent
					auto Pins = mParent->getComponentAsPtr<TPinComponent>();

					// Deactivates MREQ and RD pin
					Pins->getPin(19).changePinStatus(tcomponents::TPin::HIGH, true); // MREQ
					Pins->getPin(21).changePinStatus(tcomponents::TPin::HIGH, true); // RD
				} break;

				// T4
				case 3:
				{
					// Execute the instruction
					executeInstruction(static_cast<TOpCodesMainInstruction>(mCurrentInstruction));
				} break;
			}
		
			// Reset the TState
			if (++mTStates == 4)
				mTStates = 0;
			
		}

		void TZ80Component::memoryReadMCycle()
		{
			// Instruction fetch
			switch (mTStates)
			{
				
				// T1
				case 0:
				{
					// The Program Counter is placed on the address bus at the beginning of the M1 cycle
					// Select the instruction by putting the address in the address bus
					auto& PC = mRegisters.programCounter();
					pushDataToAddressBus(PC);
				} break;

				// T2
				case 1:
				{
					// One half clock cycle later, the MREQ signal goes active.At this time, the address to memory has had time to stabilize 
					// so that the falling edge of MREQ can be used directly as a chip enable clock to dynamic memories.
					// The RD line also goes active to indicate that the memory read data should be enabled onto the CPU data bus.

					// Get a ref to the PinComponent
					auto Pins = mParent->getComponentAsPtr<TPinComponent>();

					// Activates MREQ and RD pin
					Pins->getPin(19).changePinStatus(tcomponents::TPin::LOW, true); // MREQ
					Pins->getPin(21).changePinStatus(tcomponents::TPin::LOW, true); // RD
				} break;

				// T3
				case 2:
				{
					// The CPU samples the data from the memory space on the data bus with the rising edge of the clock of state T3, and this same edge is used by the
					// CPU to turn off the RD and MREQ signals. As a result, the data is sampled by the CPU before the RD signal becomes inactive

					// Get the instruction from the bus
					mLowMemoryRWValue = getDataFromDataBus();

					// Get a ref to the PinComponent
					auto Pins = mParent->getComponentAsPtr<TPinComponent>();

					// Deactivates MREQ and RD pin
					Pins->getPin(19).changePinStatus(tcomponents::TPin::HIGH, true); // MREQ
					Pins->getPin(21).changePinStatus(tcomponents::TPin::HIGH, true); // RD

					// Execute the instruction
					auto Instruction = static_cast<TOpCodesMainInstruction>(mCurrentInstruction);
					executeInstruction(Instruction);
				} break;
			}

			// Reset the TState
			if (++mTStates == 3)
				mTStates = 0;
		}

		void TZ80Component::memoryWriteMCycle()
		{

		}

	}
}
#include "TZ80.h"

namespace nne
{
	namespace tmodules
	{	
		TZ80::TZ80() :
			mIsRunning(true),
			mIsHalted(false),
			mMaskableInterrupt(true),
			mAlu(mRegisters),
			mClock(Hertz(1.l)),
			mTStates(0),
			mRam(nullptr),
			mAddressBus(0),
			mDataBus(0),
			mCurrentInstruction(TOpCodesMainInstruction::NOP)
		{
			// Add the right Components to make a CPU
	
			// Setup the CPU Pins
			AddComponent<tcomponents::TPinComponent>(std::initializer_list<tcomponents::TPin>{
				// ADDRESS BUS
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 30, CPUPinGroup::AddressBus, 1 }, // A1
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 31, CPUPinGroup::AddressBus, 2 }, // A2
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 32, CPUPinGroup::AddressBus, 0 }, // A0
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 33, CPUPinGroup::AddressBus, 3 }, // A3
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 34, CPUPinGroup::AddressBus, 4 }, // A4
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 35, CPUPinGroup::AddressBus, 5 }, // A5
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 36, CPUPinGroup::AddressBus, 6 }, // A6
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 37, CPUPinGroup::AddressBus, 7 }, // A7
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 38, CPUPinGroup::AddressBus, 8 }, // A8
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 39, CPUPinGroup::AddressBus, 9 }, // A9
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 40, CPUPinGroup::AddressBus, 10 }, // A10
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW,  1, CPUPinGroup::AddressBus, 11 }, // A11
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW,  2, CPUPinGroup::AddressBus, 12 }, // A12
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW,  3, CPUPinGroup::AddressBus, 13 }, // A13
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW,  4, CPUPinGroup::AddressBus, 14 }, // A14
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW,  5, CPUPinGroup::AddressBus, 15 }, // A15
	
				// DATA BUS
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 14, CPUPinGroup::DataBus, 0 }, // D0
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 15, CPUPinGroup::DataBus, 1 }, // D1
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 12, CPUPinGroup::DataBus, 2 }, // D2
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW,  8, CPUPinGroup::DataBus, 3 }, // D3
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW,  7, CPUPinGroup::DataBus, 4 }, // D4
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW,  9, CPUPinGroup::DataBus, 5 }, // D5
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 10, CPUPinGroup::DataBus, 6 }, // D6
				{ tcomponents::TPin::TMode::INPUT_OUTPUT, tcomponents::TPin::TStatus::LOW, 13, CPUPinGroup::DataBus, 7 }, // D7
	
				// SYSTEM CONTROL
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::HIGH, 27, CPUPinGroup::Others }, // M1
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::HIGH, 19, CPUPinGroup::Others }, // MREQ
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::HIGH, 20, CPUPinGroup::Others }, // IORQ
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::HIGH, 21, CPUPinGroup::Others }, // RD
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::HIGH, 22, CPUPinGroup::Others }, // WR
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::HIGH, 28, CPUPinGroup::Others }, // RFSH
	
				// CPU CONTROL
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 18, CPUPinGroup::Others }, // HALT
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  24, CPUPinGroup::Others}, // WAIT
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  16, CPUPinGroup::Others}, // INT
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  17, CPUPinGroup::Others}, // NMI
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  26, CPUPinGroup::Others}, // RESET 
																					   
				// CPU BUS CONTROL
				{ tcomponents::TPin::TMode::OUTPUT, tcomponents::TPin::TStatus::LOW, 25, CPUPinGroup::Others }, // BUSAK
				{ tcomponents::TPin::TMode::INPUT, tcomponents::TPin::TStatus::LOW,  23, CPUPinGroup::Others }, // BUSRQ 
	
				// CPUPinGroup::Others
				{ tcomponents::TPin::TMode::CLOCK, tcomponents::TPin::TStatus::LOW,  6, CPUPinGroup::Others }, // CLK
				{ tcomponents::TPin::TMode::POWER, tcomponents::TPin::TStatus::LOW, 11, CPUPinGroup::Others }, // VCC
				{ tcomponents::TPin::TMode::POWER, tcomponents::TPin::TStatus::LOW, 29, CPUPinGroup::Others }, // GND
	
			}, 40 );
			InitComponents();
	
			// Reset the state of the CPU
			Reset();
		}
		
		void TZ80::Reset()
		{
			// Reset the state of the register
			mRegisters.Reset();
		
			// Reset the R/W Memory portion if we have one connected
			if (mRam)
			{
				for (auto& Memory : (*mRam))
				{
					Memory = 0;
				}
			}		
		}
		
		void TZ80::Init()
		{
		
		}
		
		void TZ80::Refresh()
		{
			// Get the current instruction Opcode
			FetchInstruction();
		}
	
		void TZ80::Update()
		{
			// Before check if the z80 is still active
			if (!mIsRunning)
				return;
	
			// Show the debug window
			mDebugger.ShowDebugWindow(mRegisters, &mRam->GetInternalMemory(), mDataBus, mAddressBus, mClock);
			
			// Get the current instruction Opcode
			//TOpCodesMainInstruction CurrentInstruction = FetchInstruction<TOpCodesMainInstruction>();
	
			// Execute the instruction
			auto Instruction = static_cast<TOpCodesMainInstruction>(mCurrentInstruction);
			ExecuteInstruction(Instruction);
	
			mClock.Wait();
		}
	
		bool TZ80::LoadProgram(const std::string& Program)
		{
			// Check if we have a connected ram to load the program into
			if (!mRam)
				return false;
	
			// Read the file		
			std::ifstream InputFile(Program.c_str());
	
			// Check if the file is opened
			if (!InputFile.is_open())
				return false;
	
			// Scan the HEX file and reads it
			std::string CodeLine;
			while (getline(InputFile, CodeLine))
			{
				// Read how much data it's in the line
				std::size_t ByteCount = std::stoi(CodeLine.substr(1, 2).c_str(), 0, 16);
	
				// Read where the data start
				std::size_t StartAddress = std::stoi(CodeLine.substr(3, 4).c_str(), 0, 16);
	
				// Record types
				std::size_t RecordType = std::stoi(CodeLine.substr(7, 2).c_str(), 0, 16);
	
				// If record type it's 0 the following bytes are the program source code
				if (RecordType == 0)
				{
					for (std::size_t Index = 0, MemoryIndex = 0; Index < ByteCount * 2; Index += 2, ++MemoryIndex)
					{
	
						(*mRam)[StartAddress + MemoryIndex] = std::stoi(CodeLine.substr(9 + Index, 2).c_str(), 0, 16);
					}
				}
			}
	
			InputFile.close();
	
			return true;
		}
		
		bool TZ80::ConnectRam(std::shared_ptr<tmodules::TRam> Ram)
		{
			// Check the the passed argument points to something
			if (!Ram)
				return false;
	
			// Creates a copy of the ram pointer
			mRam = std::make_shared<tmodules::TRam>(*Ram.get());
	
			// Get a ref to the PinComponent of the z80 and ram
			auto& CpuPinComponent = GetComponentAsPtr<tcomponents::TPinComponent>();
			auto& RamPinComponent = mRam->GetComponentAsPtr<tcomponents::TPinComponent>();
	
			// Connects the Z80 Address bus to the Ram AddressBus
			auto& LeftBus = CpuPinComponent->GetPinBus(CPUPinGroup::AddressBus, 0, 14);
			auto& RightBus = RamPinComponent->GetPinBus(tmodules::TRamPinGroup::AddressBus);
			tcomponents::TPinComponentUtility::ConnectPins(LeftBus, RightBus);
	
			// Connects the Z80 data bus to the Ram data bus
			LeftBus = CpuPinComponent->GetPinBus(CPUPinGroup::DataBus);
			RightBus = RamPinComponent->GetPinBus(tmodules::TRamPinGroup::DataBus);
			tcomponents::TPinComponentUtility::ConnectPins(LeftBus, RightBus);
	
			// Connect the MREQ pin to the CE of the ram
			tcomponents::TPinComponentUtility::ConnectPins(CpuPinComponent->GetPin(19), RamPinComponent->GetPin(20));
	
			// Connect the RD pin to the OE of the ram
			tcomponents::TPinComponentUtility::ConnectPins(CpuPinComponent->GetPin(21), RamPinComponent->GetPin(22));
		}
		
		TU8BitValue TZ80::FetchInstruction(const TU16BitValue& Address /*= 0*/)
		{
			// Check if we have a connected ram, if we don't have one return nop
			if (!mRam)
				return static_cast<TOpCodesMainInstruction>(TOpCodesMainInstruction::NOP);
	
			// Get a ref to the PinComponent
			auto& Pins = GetComponentAsPtr<tcomponents::TPinComponent>();
	
			// Activates MREQ and RD pin
			Pins->GetPin(19).ChangePinStatus(tcomponents::TPin::LOW, true);
			Pins->GetPin(21).ChangePinStatus(tcomponents::TPin::LOW, true);
	
			// Select the instruction by putting the address in the address bus
			auto& PC = mRegisters.ProgramCounter();
			PushDataToAddressBus(Address > 0 ? Address : PC);
	
			// Refresh the memory logic
			mRam->RefreshMemory();
	
			// Get the instruction from the bus
			mCurrentInstruction = GetDataFromDataBus();
			
			// Deactivates MREQ and RD pin
			Pins->GetPin(19).ChangePinStatus(tcomponents::TPin::HIGH, true);
			Pins->GetPin(21).ChangePinStatus(tcomponents::TPin::HIGH, true);
	
			return mCurrentInstruction;
		}
	
		TU16BitValue TZ80::ExecuteInstruction(const TOpCodesMainInstruction& OpCode)
		{
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
				LoadRegisterFromRegister<T8BitRegister>(DestinationRegister, SourceRegister);
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				LoadRegisterFromMemory<T8BitRegister>(DestinationRegister, mRegisters.ProgramCounter() + 1);
		
				// Increment the PC
				mRegisters.ProgramCounter() += 2;
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
				LoadRegisterFromMemory<T8BitRegister>(DestinationRegister, mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				LoadMemoryFromRegister<T8BitRegister>(SourceRegister, mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Get the source address by looking at the second 3 bits
				switch (static_cast<TU8BitValue>(OpCode) >> 4 & 3)
				{
				case 0: DestinationRegister = TRegisterType::BC; break;
				case 1: DestinationRegister = TRegisterType::DE; break;
				case 2: DestinationRegister = TRegisterType::HL; break;
				case 3: DestinationRegister = TRegisterType::SP; break;
				}
		
				// Perform the loading operation
				mRegisters.GetRegister<T16BitRegister>(DestinationRegister) = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
				// Increment the PC
				ProgramCounter += 3;
			} break;
		#pragma endregion
		
			// LD A,(BC)
			case LD_A_INDIRECT_BC:
			{
				// Perform the loading operation
				LoadRegisterFromMemory<T8BitRegister>(TRegisterType::A, mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			}break;
		
			// LD A,(DE)
			case LD_A_INDIRECT_DE:
			{
				// Perform the loading operation
				LoadRegisterFromMemory<T8BitRegister>(TRegisterType::A, mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			}break;
		
			// LD (BC),A
			case LD_INDIRECT_BC_A:
			{
				// Perform the loading operation
				LoadMemoryFromRegister<T8BitRegister>(TRegisterType::A, mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			}break;
		
			// LD (DE),A
			case LD_INDIRECT_DE_A:
			{
				// Perform the loading operation
				LoadMemoryFromRegister<T8BitRegister>(TRegisterType::A, mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			}break;
		
			// LD A,(NN)
			case LD_A_INDIRECT_ADR:
			{
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Perform the loading operation
				LoadRegisterFromMemory<T8BitRegister>(TRegisterType::A, TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]));
		
				// Increment the PC
				ProgramCounter += 3;
			}break;
		
			// LD (NN),A
			case LD_INDIRECT_ADR_A:
			{
		
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Perform the loading operation
				LoadMemoryFromRegister<T8BitRegister>(TRegisterType::A, TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]));
		
				// Increment the PC
				ProgramCounter += 3;
			}break;
		
			// LD (NN),HL
			case LD_INDIRECT_ADR_HL:
			{
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Get the destination address
				auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
				// Perform the loading operation
				(*mRam)[Address] = mRegisters.GetRegister<T8BitRegister>(TRegisterType::L);
				(*mRam)[Address + 1] = mRegisters.GetRegister<T8BitRegister>(TRegisterType::H);
		
				// Increment PC
				ProgramCounter += 3;
			}break;
		
			// LD HL,(NN)
			case LD_HL_INDIRECT_ADR:
			{
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Get the destination address
				auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
				// Perform the loading operation
				mRegisters.GetRegister<T8BitRegister>(TRegisterType::L) = (*mRam)[Address];
				mRegisters.GetRegister<T8BitRegister>(TRegisterType::H) = (*mRam)[Address + 1];
		
				// Increment PC
				ProgramCounter += 3;
			}break;
		
			// LD (HL),N
			case LD_INDIRECT_HL_n:
			{
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Perform the loading operation
				(*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)] = (*mRam)[ProgramCounter + 1];
		
				// Increment the PC
				ProgramCounter += 2;
			}break;
		
			// LD SP,HL
			case LD_SP_HL:
			{
				// Perform the loading operation
				LoadRegisterFromRegister<T16BitRegister>(TRegisterType::SP, TRegisterType::HL);
		
				// Increment PC
				++mRegisters.ProgramCounter();
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
				PushMemory(DestinationRegister);
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				PopMemory(DestinationRegister);
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
		#pragma endregion
				
				#pragma region Exchange function
			// EX AF,AF'
			case EX_AF_AF:
			{
				std::swap(mRegisters.GetRegister<T16BitRegister>(TRegisterType::AF), mRegisters.GetRegister<T16BitRegister>(TRegisterType::ALTAF));
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// EXX
			case EXX:
			{
				std::swap(mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC), mRegisters.GetRegister<T16BitRegister>(TRegisterType::ALTBC));
				std::swap(mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE), mRegisters.GetRegister<T16BitRegister>(TRegisterType::ALTDE));
				std::swap(mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL), mRegisters.GetRegister<T16BitRegister>(TRegisterType::ALTHL));
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// EX (SP),HL
			case EX_INDIRECT_SP_HL:
			{
				mRegisters.GetRegister<T8BitRegister>(TRegisterType::H) = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP) + 1];
				mRegisters.GetRegister<T8BitRegister>(TRegisterType::L) = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP)];
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// EX DE,HL
			case EX_DE_HL:
			{
				std::swap(mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE), mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL));
				mRegisters.ProgramCounter() += 1;
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
				mAlu.AluAdd<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// ADD A,(HL)
			case ADD_A_INDIRECT_HL:
			{
				// Perform the addition
				mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			}break;
		
			// ADD A,N
			case ADD_A_n:
			{
				// Perform the addition
				mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1]);
		
				// Increment the PC
				mRegisters.ProgramCounter() += 2;
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
				mAlu.AluAdd<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister) + mAlu.CheckFlag(TFlags::C));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// ADC A,(HL)
			case ADC_A_INDIRECT_HL:
			{
				// Perform the addition
				mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)] + mAlu.CheckFlag(TFlags::C));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			}break;
		
			// ADC A,N
			case ADC_A_n:
			{
				// Perform the addition
				mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1] + mAlu.CheckFlag(TFlags::C));
		
				// Increment the PC
				mRegisters.ProgramCounter() += 2;
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
				mAlu.AluSub<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister) - mAlu.CheckFlag(TFlags::C));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// SBC A,(HL)
			case SBC_A_INDIRECT_HL:
			{
				mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)] - mAlu.CheckFlag(TFlags::C));
		
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// SBC A,N
			case SBC_A_n:
			{
				mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1] - mAlu.CheckFlag(TFlags::C));
		
				mRegisters.ProgramCounter() += 2;
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
				mAlu.AluSub<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// SUB (HL)
			case SUB_INDIRECT_HL:
			{
				mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// SUB N
			case SUB_n:
			{
				mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1]);
		
				mRegisters.ProgramCounter() += 2;
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
				mAlu.AluInc<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// INC (HL)
			case INC_INDIRECT_HL:
			{
				// Perform the increment
				mAlu.AluInc<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				mAlu.AluDec<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// DEC (HL)
			case DEC_INDIRECT_HL:
			{
				// Perform the increment
				mAlu.AluDec<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				mAlu.AluAnd<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// AND (HL)
			case AND_INDIRECT_HL:
			{
				mAlu.AluAnd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// AND N
			case AND_n:
			{
				mAlu.AluAnd<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1]);
		
				mRegisters.ProgramCounter() += 2;
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
				mAlu.AluOr<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// OR (HL)
			case OR_INDIRECT_HL:
			{
				mAlu.AluOr<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// OR N
			case OR_n:
			{
				mAlu.AluOr<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1]);
		
				mRegisters.ProgramCounter() += 2;
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
				mAlu.AluXor<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// XOR (HL)
			case XOR_INDIRECT_HL:
			{
				mAlu.AluXor<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// XOR N
			case XOR_n:
			{
				mAlu.AluXor<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1]);
		
				mRegisters.ProgramCounter() += 2;
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
				mAlu.AluCp<TU8BitValue>(mRegisters.GetRegister<T8BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		
			// CP (HL)
			case CP_INDIRECT_HL:
			{
				mAlu.AluCp<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)]);
		
				mRegisters.ProgramCounter() += 1;
			}break;
		
			// CP N
			case CP_n:
			{
				mAlu.AluCp<TU8BitValue>((*mRam)[mRegisters.ProgramCounter() + 1]);
		
				mRegisters.ProgramCounter() += 2;
			}break;
		#pragma endregion
		
		#pragma endregion
				
				#pragma region General-Purpose Arithmetic and CPU Control Groups
			// DAA
			case DAA:
			{
				// Get a ref to the accumulator
				auto& Accumulator = mRegisters.Accumulator();
				auto AccLowNibble = TUtility::GetLowerNible(Accumulator);
				auto AccHighNibble = TUtility::GetUpperNible(Accumulator);
		
		
				if ((TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0, 8) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0xA, 0xF)) ||
					(TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0, 9) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0, 3) && mAlu.CheckFlag(TFlags::H)))
				{
					Accumulator += 6;
				}
				else
					if ((TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0xA, 0xF) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0, 9)) ||
						(TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0, 2) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0, 9) && mAlu.CheckFlag(TFlags::C)))
					{
						Accumulator += 60;
		
						mAlu.SetFlag(TFlags::C);
					}
					else
						if ((TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 9, 0xF) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0xA, 0xF)) ||
							(TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0xA, 0xF) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0, 3) && mAlu.CheckFlag(TFlags::H)) ||
							(TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0, 2) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0xA, 0xF) && mAlu.CheckFlag(TFlags::C)) ||
							(TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0, 3) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0, 3) && mAlu.CheckFlag(TFlags::C) && mAlu.CheckFlag(TFlags::H)))
						{
							Accumulator += 66;
		
							mAlu.SetFlag(TFlags::C);
						}
						else
							if ((TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 0, 8) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 6, 0xF)) && mAlu.CheckFlag(TFlags::H))
							{
								Accumulator += 0xFA;
							}
							else
								if ((TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 7, 0xF) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 0, 9)) && mAlu.CheckFlag(TFlags::C))
								{
									Accumulator += 0xA0;
		
									mAlu.SetFlag(TFlags::C);
								}
								else
									if ((TUtility::ValueIsBetween<TU8BitValue>(AccHighNibble, 6, 7) && TUtility::ValueIsBetween<TU8BitValue>(AccLowNibble, 6, 0xF)) && mAlu.CheckFlag(TFlags::C) && mAlu.CheckFlag(TFlags::H))
									{
										Accumulator += 0x9A;
		
										mAlu.SetFlag(TFlags::C);
									}
		
				// Set flags
		
				// S is set if most - significant bit of the Accumulator is 1 after an operation; otherwise, it is reset.
				TUtility::GetBit<TU8BitValue>(Accumulator, 7) == 1 ? mAlu.SetFlag(TFlags::S) : mAlu.SetFlag(TFlags::S);
		
				// Z is set if the Accumulator is 0 after an operation; otherwise, it is reset.
				Accumulator == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.SetFlag(TFlags::Z);
		
				// P/V is set if the Accumulator is at even parity after an operation; otherwise, it is reset.
				TUtility::CheckParity(Accumulator) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
			} break;
		
			// CPL
			case CPL:
			{
				mRegisters.Accumulator() = ~mRegisters.Accumulator();
		
				mAlu.SetFlag(TFlags::H | TFlags::S);
		
				++mRegisters.ProgramCounter();
			} break;
		
			// CCF
			case CCF:
			{
				// H, previous carry is copied.
				mAlu.CheckFlag(TFlags::C) ? mAlu.SetFlag(TFlags::H) : mAlu.ResetFlag(TFlags::H);
		
				// N is reset.
				mAlu.ResetFlag(TFlags::N);
		
				// Flip the carry bit
				mAlu.CheckFlag(TFlags::C) ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
				++mRegisters.ProgramCounter();
			} break;
		
			// SCF
			case SCF:
			{
				// N and H is reset.
				mAlu.ResetFlag(TFlags::N | TFlags::H);
		
				// Set the carry bit
				mAlu.SetFlag(TFlags::C);
		
				++mRegisters.ProgramCounter();
			} break;
		
			// NOP
			case NOP:
			{
				++mRegisters.ProgramCounter();
			} break;
		
			// Halt
			case HALT:
			{
				mIsHalted = true;
		
				++mRegisters.ProgramCounter();
			} break;
		
			// DI
			case DI:
			{
				mMaskableInterrupt = false;
		
				++mRegisters.ProgramCounter();
			} break;
		
			// EI
			case EI:
			{
				mMaskableInterrupt = true;
		
				++mRegisters.ProgramCounter();
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
				mAlu.AluAdd<TU16BitValue>(mRegisters.GetRegister<T16BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				mAlu.AluInc<TU16BitValue>(mRegisters.GetRegister<T16BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
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
				mAlu.AluDec<TU16BitValue>(mRegisters.GetRegister<T16BitRegister>(SourceRegister));
		
				// Increment the PC
				++mRegisters.ProgramCounter();
			} break;
		#pragma endregion
		
		#pragma endregion
				
				#pragma region Shift group
			// RLCA
			case RLCA:
			{
				// Get a reference to the accumulator
				auto& Accumulator = mRegisters.Accumulator();
		
				// Rotate left the accumulator
				mAlu.RotateLeft(Accumulator);
		
				++mRegisters.ProgramCounter();
			} break;
		
			// RLA
			case RLA:
			{
				mAlu.RotateLeft(mRegisters.Accumulator());
		
				++mRegisters.ProgramCounter();
			} break;
		
			// RRCA
			case RRCA:
			{
				mAlu.RotateRight(mRegisters.Accumulator(), true);
		
				++mRegisters.ProgramCounter();
			} break;
		
			// RRA
			case RRA:
			{
				mAlu.RotateRight(mRegisters.Accumulator(), true);
		
				++mRegisters.ProgramCounter();
			} break;
		#pragma endregion
				
				#pragma region Bit instructions (CB)
			// TOpCodesBitInstructions
			case BITS:
			{
				// Get the instruction
				auto BitInstruction = static_cast<TOpCodesBitInstructions>(FetchInstruction(++mRegisters.ProgramCounter()));
		
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.RotateLeft(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				}break;
		
				// RLC (HL)
				case RLC_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.RotateLeft(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.RotateLeft(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				}break;
		
				// RL (HL)
				case RL_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.RotateLeft(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					TUtility::RotateLeft(Register) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
					// Set flags
					mAlu.ResetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				}break;
		
				// SLA (HL)
				case SLA_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					TUtility::RotateLeft(Register) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
					// Set flags
					mAlu.ResetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Get the 7th bit for preservation purpose
					bool Bit = TUtility::GetBit(Register, 7);
		
					TUtility::RotateRight(Register) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
					// Put the old 7th bit in the new 7th bit slot
					TUtility::SetBit(Register, 7, Bit);
		
					// Set flags
					mAlu.ResetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				}break;
		
				// SRA (HL)
				case SRA_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Get the 7th bit for preservation purpose
					bool Bit = TUtility::GetBit(Register, 7);
		
					TUtility::RotateRight(Register) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
					// Put the old 7th bit in the new 7th bit slot
					TUtility::SetBit(Register, 7, Bit);
		
					// Set flags
					mAlu.ResetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					TUtility::RotateRight(Register) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
					// Set flags
					mAlu.ResetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				}break;
		
				// SRA (HL)
				case SRL_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto& Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					TUtility::RotateRight(Register) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
					// Set flags
					mAlu.ResetFlag(TFlags::N | TFlags::H);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Z is set if specified bit is 0; otherwise, it is reset.
					TUtility::GetBit(Register, BitPosition) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// H is set.
					mAlu.SetFlag(TFlags::H);
		
					// N is set.
					mAlu.ResetFlag(TFlags::N);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Z is set if specified bit is 0; otherwise, it is reset.
					TUtility::GetBit(Register, BitPosition) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// H is set.
					mAlu.SetFlag(TFlags::H);
		
					// N is set.
					mAlu.ResetFlag(TFlags::N);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Set the specified bit
					TUtility::SetBit(Register, BitPosition, 1);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Set the specified bit
					TUtility::SetBit(Register, BitPosition, 1);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Reset the specified bit
					TUtility::SetBit(Register, BitPosition, 0);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Reset the specified bit
					TUtility::SetBit(Register, BitPosition, 0);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.RotateRight(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				}break;
		
				// RRC (HL)
				case RC_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.RotateRight(Register, false);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& Register = mRegisters.GetRegister<T8BitRegister>(RegisterToTest);
		
					// Perform the operation
					mAlu.RotateRight(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				}break;
		
				// RR (HL)
				case R_INDIRECT_HL & 0xFF:
				{
					// Get a ref to the register
					auto Register = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Perform the operation
					mAlu.RotateRight(Register);
		
					// Set flags
					// the N, H, C flags are set in the rotation functions
		
					// S register
					Register > 0x7F /*(0111 1111)*/ ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z register
					Register == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P/V register
					mAlu.CheckParity(Register) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Destination address
				auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
				// See what flag we have to check and base the jump based on the flag condition
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: !mAlu.CheckFlag(TFlags::Z) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 1: mAlu.CheckFlag(TFlags::Z) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 2: !mAlu.CheckFlag(TFlags::C) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 3: mAlu.CheckFlag(TFlags::C) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 4: !mAlu.CheckFlag(TFlags::P_V) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 5: mAlu.CheckFlag(TFlags::P_V) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 6: !mAlu.CheckFlag(TFlags::S) ? ProgramCounter = Address : ProgramCounter += 3; break;
				case 7: mAlu.CheckFlag(TFlags::S) ? ProgramCounter = Address : ProgramCounter += 3; break;
				}
			} break;
		#pragma endregion
		
			// JP NN
			case JP_ADR:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				ProgramCounter = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
			} break;
		
			// JP (HL)
			case JP_INDIRECT_HL:
			{
				LoadRegisterFromRegister<T16BitRegister>(TRegisterType::PC, TRegisterType::HL);
			} break;
		
			// JR E
			case JR_dis:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				ProgramCounter += (*mRam)[ProgramCounter + 1] + 2;
			} break;
		
		#pragma region JR CC,DIS
			case JR_NZ_dis:
			case JR_Z_dis:
			case JR_NC_dis:
			case JR_C_dis:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Destination address
				auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
				// See what flag we have to check
				bool Flag;
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 3)
				{
				case 0: Flag = !mAlu.CheckFlag(TFlags::Z); break;
				case 1: Flag = mAlu.CheckFlag(TFlags::Z); break;
				case 2: Flag = !mAlu.CheckFlag(TFlags::C); break;
				case 3: Flag = mAlu.CheckFlag(TFlags::C); break;
				}
		
				// Displacement
				const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1] + 2;
		
				// Base the jump based on the flag condition
				Flag ? ProgramCounter.GetInternalValue() += Displacement : ProgramCounter += 2;
			} break;
		#pragma endregion
		
			// DJNZ E
			case DJNZ_dis:
			{
				// Get a reference to the B and PC registers
				auto& Register = mRegisters.GetRegister<T8BitRegister>(TRegisterType::B);
				auto& ProgramCounter = mRegisters.ProgramCounter();
				const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1] + 2;
		
				// Decrement the B register, if B > 0 add an offset to the PC otherwise goes to the next instruction
				--Register > 0 ? ProgramCounter.GetInternalValue() += Displacement : ProgramCounter += 2;
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
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Destination address
				auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
				// See what flag we have to check
				bool Flag;
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: Flag = !mAlu.CheckFlag(TFlags::Z); break;
				case 1: Flag = mAlu.CheckFlag(TFlags::Z); break;
				case 2: Flag = !mAlu.CheckFlag(TFlags::C); break;
				case 3: Flag = mAlu.CheckFlag(TFlags::C); break;
				case 4: Flag = !mAlu.CheckFlag(TFlags::P_V); break;
				case 5: Flag = mAlu.CheckFlag(TFlags::P_V); break;
				case 6: Flag = !mAlu.CheckFlag(TFlags::S); break;
				case 7: Flag = mAlu.CheckFlag(TFlags::S); break;
				}
		
				// Base the jump based on the flag condition
				Flag ? Call(Address) : ProgramCounter += 3;
			} break;
		#pragma endregion
		
			// CALL NN
			case CALL_ADR:
			{
				// Get a reference to the PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// Put the PC on the stack on goes to the memory location specified by the CALL instruction
				Call(TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]));
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
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
				// See what flag we have to check
				bool Flag;
				switch (static_cast<TU8BitValue>(OpCode) >> 3 & 7)
				{
				case 0: Flag = !mAlu.CheckFlag(TFlags::Z); break;
				case 1: Flag = mAlu.CheckFlag(TFlags::Z); break;
				case 2: Flag = !mAlu.CheckFlag(TFlags::C); break;
				case 3: Flag = mAlu.CheckFlag(TFlags::C); break;
				case 4: Flag = !mAlu.CheckFlag(TFlags::P_V); break;
				case 5: Flag = mAlu.CheckFlag(TFlags::P_V); break;
				case 6: Flag = !mAlu.CheckFlag(TFlags::S); break;
				case 7: Flag = mAlu.CheckFlag(TFlags::S); break;
				}
		
				// If the check is true execute the return function otherwise goes to the next instruction
				Flag ? Return() : ++mRegisters.ProgramCounter();
			} break;
		#pragma endregion			
		
			// RET
			case RET:
			{
				Return();
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
				auto& ProgramCounter = mRegisters.ProgramCounter();
		
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
				PushMemory(TRegisterType::PC);
		
				// Move the PC to the desired location
				mRegisters.ProgramCounter() = Address;
			} break;
		#pragma endregion
		
		#pragma endregion
		
				// IN A,(N)
				case IN_A_INDIRECT_port:
				{
				// Get a ref to the accumulator
				auto& Accumulator = mRegisters.Accumulator();
	
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
	
				// Get the address of the port
				auto Port = (*mRam)[ProgramCounter + 1];
	
				// Put the data from the data bus to the accumulator
				Accumulator = GetDataFromDataBus();
	
				// Increment the PC
				ProgramCounter += 2;
			} break;
	
				// OUT (N),A
				case OUT_INDIRECT_port_A:
				{
				// Get a ref to the accumulator
				auto& Accumulator = mRegisters.Accumulator();
	
				// Get a ref to PC
				auto& ProgramCounter = mRegisters.ProgramCounter();
	
				// Get the address of the port
				auto Port = (*mRam)[ProgramCounter + 1];
	
				// Put the data from the data bus to the accumulator
				PushDataToDataBus(Accumulator);
	
				// Increment the PC
				ProgramCounter += 2;
			} break;
		
				#pragma region IX Instruction
				// TOpCodesIXInstructions
			case IX_INSTRUCTIONS:
			{
				// Cast the bit instruction as an 8 bit value
				auto IXInstruction = static_cast<TOpCodesIXInstructions>(FetchInstruction(++mRegisters.ProgramCounter()));
		
				switch (IXInstruction)
				{
					// PUSH IX
				case PUSH_IX:
				{
					PushMemory(TRegisterType::IX);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// POP IX
				case POP_IX:
				{
					PopMemory(TRegisterType::IX);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// EX (SP), IX
				case EX_INDIRECT_SP_IX:
				{
					auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					IXRegister.GetHighOrderRegister() = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP) + 1];
					IXRegister.GetLowOrderRegister() = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP)];
					mRegisters.ProgramCounter() += 1;
				} break;
		
				// AND (IX + DIS)
				case AND_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluAnd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// OR (IX + DIS)
				case OR_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluOr<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// XOR (IX + DIS)
				case XOR_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluXor<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// CP (IX + DIS)
				case CP_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluCp<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// ADD IX, BC
				case ADD_IX_BC:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD IX, DE
				case ADD_IX_DE:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD IX, IX
				case ADD_IX_IX:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD IX, SP
				case ADD_IX_SP:
				{
					// Get a ref to IX and a temp copy of it
					auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					auto CopyRegister = IXRegister;
		
					// Add the content of BC to IX
					IXRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IXRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IXRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD A, (IX + DIS)
				case ADD_A_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// ADC A, (IX + DIS)
				case ADC_A_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement] + mAlu.CheckFlag(TFlags::C));
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// SBC A, (IX + DIS)
				case SBC_A_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement] - mAlu.CheckFlag(TFlags::C));
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// INC IX
				case INC_IX:
				{
					++mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// INC (IX + DIS)
				case INC_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluInc<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// DEX IX
				case DEC_IX:
				{
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// DEC (IX + DIS)
				case DEC_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluDec<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
		#pragma region IX Bit instruction
				// TOpCodesIXBitInstructions
				case IX_BIT_INSTRUCTIONS:
				{
					// Get the instruction
					auto IXBitInstruction = static_cast<TOpCodesIXBitInstructions>(FetchInstruction(++mRegisters.ProgramCounter()));
		
					switch (IXBitInstruction)
					{
						// RLC (IX + DIS)
					case RLC_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateLeft<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], false);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
		#pragma region Check Bit
					// BIT 0, (IX + DIS)
					case BIT_0_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 0) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 1, (IX + DIS)
					case BIT_1_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 1) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 2, (IX + DIS)
					case BIT_2_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 2) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 3, (IX + DIS)
					case BIT_3_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 3) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 4, (IX + DIS)
					case BIT_4_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 4) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 5, (IX + DIS)
					case BIT_5_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 5) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 6, (IX + DIS)
					case BIT_6_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 6) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 7, (IX + DIS)
					case BIT_7_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 7) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		#pragma endregion
		
		#pragma region Set Bit
					// SET 0, (IX + DIS)
					case SET_0_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 0, 1);
					} break;
		
					// SET 1, (IX + DIS)
					case SET_1_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 1, 1);
					} break;
		
					// SET 2, (IX + DIS)
					case SET_2_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 2, 1);
					} break;
		
					// SET 3, (IX + DIS)
					case SET_3_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 3, 1);
					} break;
		
					// SET 4, (IX + DIS)
					case SET_4_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 4, 1);
					} break;
		
					// SET 5, (IX + DIS)
					case SET_5_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 5, 1);
					} break;
		
					// SET 6, (IX + DIS)
					case SET_6_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 6, 1);
					} break;
		
					// SET 7, (IX + DIS)
					case SET_7_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 7, 1);
					} break;
		#pragma endregion
		
		#pragma region Reset Bit
					// SET 0, (IX + DIS)
					case RES_0_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 0, 0);
					} break;
		
					// SET 1, (IX + DIS)
					case RES_1_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 1, 0);
					} break;
		
					// SET 2, (IX + DIS)
					case RES_2_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 2, 0);
					} break;
		
					// SET 3, (IX + DIS)
					case RES_3_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 3, 0);
					} break;
		
					// SET 4, (IX + DIS)
					case RES_4_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 4, 0);
					} break;
		
					// SET 5, (IX + DIS)
					case RES_5_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 5, 0);
					} break;
		
					// SET 6, (IX + DIS)
					case RES_6_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 6, 0);
					} break;
		
					// SET 7, (IX + DIS)
					case RES_7_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], 7, 0);
					} break;
		#pragma endregion
		
					// RL (IX + DIS)
					case RL_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateLeft<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// RR (IX + DIS)
					case R_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateRight((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// RRC (IX + DIS)
					case RC_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateRight((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement], false);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// SLA (IX + DIS)
					case SLA_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						TUtility::RotateLeft((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
						// Set flags
						mAlu.ResetFlag(TFlags::N | TFlags::H);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// SRA (IX + DIS)
					case SRA_INDIRECT_IX_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
						auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
		
						// Get the 7th bit for preservation purpose
						bool Bit = TUtility::GetBit(IXRegister, 7);
		
						TUtility::RotateRight(IXRegister) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
						// Put the old 7th bit in the new 7th bit slot
						TUtility::SetBit(IXRegister, 7, Bit);
		
						// Set flags
						mAlu.ResetFlag(TFlags::N | TFlags::H);
					} break;
		
					// SRL (IX + DIS)
					case SRL_INDIRECT_IX_dis:
					{
						TUtility::RotateRight(mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX)) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
						// Set flags
						mAlu.ResetFlag(TFlags::N | TFlags::H);
					} break;
					}
				} break;
		#pragma endregion
		
				// JP (IX)
				case JP_INDIRECT_IX:
				{
					LoadRegisterFromRegister<T16BitRegister>(TRegisterType::PC, TRegisterType::IX);
				} break;
		
		#pragma region Load Instruction
				// LD IX, N
				case LD_IX_n:
				{
					// Get a ref to the PC
					auto& ProgramCounter = mRegisters.ProgramCounter();
		
					mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (NN), IX
				case LD_INDIRECT_ADR_IX:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
					(*mRam)[Address + 1] = IXRegister.GetHighOrderRegister();
					(*mRam)[Address] = IXRegister.GetLowOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				// LD IX, (NN)
				case LD_IX_INDIRECT_ADR:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
					IXRegister = TUtility::To16BitValue((*mRam)[Address + 1], (*mRam)[Address]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (IX + DIS), N
				case LD_INDIRECT_IX_dis_n:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
					const auto Number = (*mRam)[ProgramCounter + 2];
		
					(*mRam)[IXRegister + Displacement] = Number;
		
					ProgramCounter += 3;
				} break;
		
				// LD B, (IX + DIS)
				case LD_B_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::B, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD C, (IX + DIS)
				case LD_C_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::C, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD D, (IX + DIS)
				case LD_D_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::D, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD E, (IX + DIS)
				case LD_E_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::E, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD H, (IX + DIS)
				case LD_H_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::H, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD L, (IX + DIS)
				case LD_L_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::L, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), B
				case LD_INDIRECT_IX_dis_B:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::B, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), C
				case LD_INDIRECT_IX_dis_C:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::C, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), D
				case LD_INDIRECT_IX_dis_D:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::D, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), E
				case LD_INDIRECT_IX_dis_E:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::E, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), H
				case LD_INDIRECT_IX_dis_H:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::H, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), L
				case LD_INDIRECT_IX_dis_L:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::L, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IX + DIS), A
				case LD_INDIRECT_IX_dis_A:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::A, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD A, (IX + DIS)
				case LD_A_INDIRECT_IX_dis:
				{
					// Get a ref to the PC and IX and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IXRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::A, IXRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
		#pragma endregion
		
				// SUB (IX + DIS)
				case SUB_INDIRECT_IX_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IX) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// LD SP, IX
				case LD_SP_IX:
				{
					LoadRegisterFromRegister<T16BitRegister>(TRegisterType::SP, TRegisterType::IX);
		
					++mRegisters.ProgramCounter();
				} break;
				}
			} break;
		#pragma endregion
				
				#pragma region Extended instructions
			// TOpCodesExtendedInstruction
			case EXTENDED_INSTRUCTIONS:
			{
				// Cast the bit instruction as an 8 bit value
				auto ExtendedInstruction = static_cast<TOpCodesExtendedInstruction>(FetchInstruction(++mRegisters.ProgramCounter()));
		
				switch (ExtendedInstruction)
				{
		#pragma region Block Transfer
					// LDI
				case LDI:
				{
					(*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE)] = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
					++mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
					++mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N flags
					mAlu.ResetFlag(TFlags::H | TFlags::N);
		
					// P/V is set if BC – 1 != 0; otherwise, it is reset
					mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC) - 1 != 0 ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					++mRegisters.ProgramCounter();
				}break;
		
				// LDIR
				case LDIR:
				{
					(*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE)] = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
					++mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
					++mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N and P/V flags
					mAlu.ResetFlag(TFlags::H | TFlags::N | TFlags::P_V);
		
					// If BC is 0 than terminates the operation bu allowing the program to go further otherwise decrement the PC by 2 to allows the operation to be executed again
					mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC) == 0 ? ++mRegisters.ProgramCounter() : mRegisters.ProgramCounter() -= 2;
				}break;
		
				// LDD
				case LDD:
				{
					(*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE)] = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N flags
					mAlu.ResetFlag(TFlags::H | TFlags::N);
		
					// P/V is set if BC – 1 != 0; otherwise, it is reset
					mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC) - 1 != 0 ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// LDDR
				case LDDR:
				{
					(*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE)] = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Reset the H and N flags
					mAlu.ResetFlag(TFlags::H | TFlags::N | TFlags::P_V);
		
					// If BC is 0 than terminates the operation bu allowing the program to go further otherwise decrement the PC by 2 to allows the operation to be executed again
					mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC) == 0 ? ++mRegisters.ProgramCounter() : mRegisters.ProgramCounter() -= 2;
				} break;
		#pragma endregion
		
		#pragma region Search instruction
				// CPI
				case CPI:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.Accumulator() == (*mRam)[HLRegister];
		
					// Increment HL and decrement BC
					++HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.SetFlag(TFlags::N);
		
					// C is not affected.
		
					// Increment PC
					++mRegisters.ProgramCounter();
				} break;
		
				// CPIR
				case CPIR:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.Accumulator() == (*mRam)[HLRegister];
		
					// Increment HL and decrement BC
					++HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.SetFlag(TFlags::N);
		
					// C is not affected.
		
					// If decrementing causes BC to go to 0 or if A = (HL), the instruction is terminated.If BC is not 0 and A != (HL), the program counter is decremented by two and the instruction is repeated.
					Result == true || BCRegister == 0 ? ++mRegisters.ProgramCounter() : mRegisters.ProgramCounter();
				} break;
		
				// CPD
				case CPD:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.Accumulator() == (*mRam)[HLRegister];
		
					// Decrement BC and HL
					--HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.SetFlag(TFlags::N);
		
					// C is not affected.
		
					// Increment PC
					++mRegisters.ProgramCounter();
				} break;
		
				// CPDR
				case CPDR:
				{
					// Get a ref to BC and HL
					auto& HLRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL);
					auto& BCRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Test if the content of the accumulator is equal to the content of the memory location pointed by HL
					bool Result = mRegisters.Accumulator() == (*mRam)[HLRegister];
		
					// Decrement BC and HL
					--HLRegister;
					--BCRegister;
		
					// S is set if result is negative; otherwise, it is reset.
		
					// Z is set if A is(HL); otherwise, it is reset.
					Result ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
		
					// P / V is set if BC – 1 is not 0; otherwise, it is reset.
					BCRegister - 1 != 0 ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.SetFlag(TFlags::N);
		
					// C is not affected.
		
					// If decrementing causes BC to go to 0 or if A = (HL), the instruction is terminated.If BC is not 0 and A != (HL), the program counter is decremented by two and the instruction is repeated.
					Result == true || BCRegister == 0 ? ++mRegisters.ProgramCounter() : mRegisters.ProgramCounter();
				} break;
		#pragma endregion
		
				// NEG
				case NEG:
				{
					// Get a ref to the aaccumulator
					auto& Accumulator = mRegisters.Accumulator();
		
					// Bitwise complement of the accumulator
					Accumulator = ~Accumulator;
		
					// S is set if result is negative; otherwise, it is reset.
					Accumulator > 0x7f ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z is set if result is 0; otherwise, it is reset.
					Accumulator == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// H is set if borrow from bit 4; otherwise, it is reset.
					// H register
					mAlu.CheckBorrowFromBit<TU8BitValue>(4, Accumulator, ~Accumulator) ? mAlu.SetFlag(TFlags::H) : mAlu.ResetFlag(TFlags::H);
		
					// P / V is set if Accumulator was 80h before operation; otherwise, it is reset.
					~Accumulator == 0x80 ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// N is set.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if Accumulator was not 00h before operation; otherwise, it is reset.
					~Accumulator != 0 ? mAlu.SetFlag(TFlags::C) : mAlu.ResetFlag(TFlags::C);
		
				} break;
		
				// IM 0
				case IM_0:
				{
					mInterruptMode = TInterruptMode::MODE_0;
		
					++mRegisters.ProgramCounter();
				} break;
		
				// IM 1
				case IM_1:
				{
					mInterruptMode = TInterruptMode::MODE_0;
		
					++mRegisters.ProgramCounter();
				} break;
		
				// IM 2
				case IM_2:
				{
					mInterruptMode = TInterruptMode::MODE_0;
		
					++mRegisters.ProgramCounter();
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
					mAlu.AluAdd<TU16BitValue>(mRegisters.GetRegister<T16BitRegister>(SourceRegister) + mAlu.CheckFlag(TFlags::C));
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					mAlu.AluSub<TU16BitValue>(mRegisters.GetRegister<T16BitRegister>(SourceRegister) - mAlu.CheckFlag(TFlags::C));
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				} break;
		#pragma endregion
		
		#pragma endregion
		
		#pragma region Shift function
				// RLD
				case RLD:
				{
					// Get a ref to the accumulator and HL
					auto& Accumulator = mRegisters.Accumulator();
					auto& IndirectMemory = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Swap low nibble of (HL) with high nibble of (HL)
					{
						auto LowerNibble = TUtility::GetLowerNible(IndirectMemory);
						auto UpperNibble = TUtility::GetUpperNible(IndirectMemory);
						auto Temp = UpperNibble;
		
						UpperNibble = (UpperNibble & 0b00001111) | (LowerNibble << 4);
						LowerNibble = (LowerNibble & 0b11110000) | (Temp >> 4);
					}
		
					// Swap low nibble of (HL) with low nibble of Accumulator
					{
						auto LowerAccumulatorNibble = TUtility::GetLowerNible(Accumulator);
						auto LowerIndirMemoryNibble = TUtility::GetLowerNible(IndirectMemory);
						auto Temp = LowerAccumulatorNibble;
		
						LowerAccumulatorNibble = (LowerAccumulatorNibble & 0b11110000) | LowerIndirMemoryNibble;
						LowerIndirMemoryNibble = (LowerIndirMemoryNibble & 0b11110000) | Temp;
					}
		
					// S is set if the Accumulator is negative after an operation; otherwise, it is reset.
					Accumulator > 0x7F ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z is set if the Accumulator is 0 after an operation; otherwise, it is reset.
					Accumulator == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P / V is set if the parity of the Accumulator is even after an operation; otherwise, it is reset.
					mAlu.CheckParity(Accumulator) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// H and N is reset.
					mAlu.ResetFlag(TFlags::H | TFlags::N);
		
					// C is not affected.
		
					// Increment the PC
					++mRegisters.ProgramCounter();
				} break;
		
				// RRD
				case RRD:
				{
					// Get a ref to the accumulator and HL
					auto& Accumulator = mRegisters.Accumulator();
					auto& IndirectMemory = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::HL)];
		
					// Swap low nibble of (HL) with low nibble of Accumulator
					{
						auto LowerAccumulatorNibble = TUtility::GetLowerNible(Accumulator);
						auto LowerIndirMemoryNibble = TUtility::GetLowerNible(IndirectMemory);
						auto Temp = LowerAccumulatorNibble;
		
						LowerAccumulatorNibble = (LowerAccumulatorNibble & 0b11110000) | LowerIndirMemoryNibble;
						LowerIndirMemoryNibble = (LowerIndirMemoryNibble & 0b11110000) | Temp;
					}
		
					// Swap low nibble of (HL) with high nibble of (HL)
					{
						auto LowerNibble = TUtility::GetLowerNible(IndirectMemory);
						auto UpperNibble = TUtility::GetUpperNible(IndirectMemory);
						auto Temp = UpperNibble;
		
						UpperNibble = (UpperNibble & 0b00001111) | (LowerNibble << 4);
						LowerNibble = (LowerNibble & 0b11110000) | (Temp >> 4);
					}
		
					// S is set if the Accumulator is negative after an operation; otherwise, it is reset.
					Accumulator > 0x7F ? mAlu.SetFlag(TFlags::S) : mAlu.ResetFlag(TFlags::S);
		
					// Z is set if the Accumulator is 0 after an operation; otherwise, it is reset.
					Accumulator == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
					// P / V is set if the parity of the Accumulator is even after an operation; otherwise, it is reset.
					mAlu.CheckParity(Accumulator) ? mAlu.SetFlag(TFlags::P_V) : mAlu.ResetFlag(TFlags::P_V);
		
					// H and N is reset.
					mAlu.ResetFlag(TFlags::H | TFlags::N);
		
					// C is not affected.
		
					// Increment the PC
					++mRegisters.ProgramCounter();
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
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& SourceRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Get the address destination
					auto Address = TUtility::To16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					(*mRam)[Address] = SourceRegister.GetLowOrderRegister();
					(*mRam)[Address + 1] = SourceRegister.GetHighOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				case LD_I_A:
					break;
		
					// LD BC, (NN)
				case LD_BC_INDIRECT_ADR:
				{
					// get a ref to the PC and BC
					auto& ProgramCounter = mRegisters.ProgramCounter();
					auto& DestinationRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// Get the address source
					auto Address = TUtility::To16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					DestinationRegister.GetLowOrderRegister() = (*mRam)[Address];
					DestinationRegister.GetHighOrderRegister() = (*mRam)[Address + 1];
		
					ProgramCounter += 3;
				} break;
		
				case LD_R_A:
					break;
		
					// LD (NN), DE
				case LD_INDIRECT_ADR_DE:
				{
					// get a ref to the PC and DE
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& SourceRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
		
					// Get the address destination
					auto Address = TUtility::To16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					(*mRam)[Address] = SourceRegister.GetLowOrderRegister();
					(*mRam)[Address + 1] = SourceRegister.GetHighOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				case LD_A_I:
					break;
		
					// LD DE, (NN)
				case LD_DE_INDIRECT_ADR:
				{
					// get a ref to the PC and DE
					auto& ProgramCounter = mRegisters.ProgramCounter();
					auto& DestinationRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
		
					// Get the address source
					auto Address = TUtility::To16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					DestinationRegister.GetLowOrderRegister() = (*mRam)[Address];
					DestinationRegister.GetHighOrderRegister() = (*mRam)[Address + 1];
		
					ProgramCounter += 3;
				} break;
		
				case LD_A_R:
					break;
		
					// LD (NN), SP
				case LD_INDIRECT_ADR_SP:
				{
					// get a ref to the PC and SP
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& SourceRegister = mRegisters.StackPointer();
		
					// Get the address destination
					auto Address = TUtility::To16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					(*mRam)[Address] = SourceRegister.GetLowOrderRegister();
					(*mRam)[Address + 1] = SourceRegister.GetHighOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				// LD SP, (NN)
				case LD_SP_INDIRECT_ADR:
				{
					// get a ref to the PC and SP
					auto& ProgramCounter = mRegisters.ProgramCounter();
					auto& DestinationRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP);
		
					// Get the address source
					auto Address = TUtility::To16BitValue(ProgramCounter + 2, ProgramCounter + 1);
		
					DestinationRegister.GetLowOrderRegister() = (*mRam)[Address];
					DestinationRegister.GetHighOrderRegister() = (*mRam)[Address + 1];
		
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
				auto IYInstruction = static_cast<TOpCodesIYInstructions>(FetchInstruction(++mRegisters.ProgramCounter()));
		
				switch (IYInstruction)
				{
					// PUSH IY
				case PUSH_IY:
				{
					PushMemory(TRegisterType::IY);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// POP IY
				case POP_IY:
				{
					PopMemory(TRegisterType::IY);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// EX (SP), IY
				case EX_INDIRECT_SP_IY:
				{
					auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					IYRegister.GetHighOrderRegister() = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP) + 1];
					IYRegister.GetLowOrderRegister() = (*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP)];
					mRegisters.ProgramCounter() += 1;
				} break;
		
				// AND (IY + DIS)
				case AND_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluAnd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// OR (IY + DIS)
				case OR_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluOr<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// XOR (IY + DIS)
				case XOR_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluXor<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// CP (IY + DIS)
				case CP_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluCp<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// ADD IY, BC
				case ADD_IY_BC:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::BC);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD IY, DE
				case ADD_IY_DE:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::DE);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD IY, IY
				case ADD_IY_IY:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD IY, SP
				case ADD_IY_SP:
				{
					// Get a ref to IY and a temp copy of it
					auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					auto CopyRegister = IYRegister;
		
					// Add the content of BC to IY
					IYRegister += mRegisters.GetRegister<T16BitRegister>(TRegisterType::SP);
		
					// H is set if carry from bit 11; otherwise, it is reset.
					mAlu.CheckCarryFromBit(11, CopyRegister, IYRegister);
		
					// N is reset.
					mAlu.SetFlag(TFlags::N);
		
					// C is set if carry from bit 15; otherwise, it is reset.
					mAlu.CheckCarryFromBit(15, CopyRegister, IYRegister);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// ADD A, (IY + DIS)
				case ADD_A_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// ADC A, (IY + DIS)
				case ADC_A_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluAdd<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement] + mAlu.CheckFlag(TFlags::C));
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// SBC A, (IY + DIS)
				case SBC_A_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement] - mAlu.CheckFlag(TFlags::C));
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// INC IY
				case INC_IY:
				{
					++mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// INC (IY + DIS)
				case INC_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluInc<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// DEX IY
				case DEC_IY:
				{
					--mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
		
					++mRegisters.ProgramCounter();
				} break;
		
				// DEC (IY + DIS)
				case DEC_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluDec<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
		#pragma region IY Bit instruction
				// TOpCodesIYBitInstructions
				case IY_BIT_INSTRUCTIONS:
				{
					// Get the instruction
					auto IYBitInstruction = static_cast<TOpCodesIYBitInstructions>(FetchInstruction(++mRegisters.ProgramCounter()));
		
					switch (IYBitInstruction)
					{
						// RLC (IY + DIS)
					case RLC_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateLeft<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], false);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
		#pragma region Check Bit
					// BIT 0, (IY + DIS)
					case BIT_0_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 0) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 1, (IY + DIS)
					case BIT_1_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 1) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 2, (IY + DIS)
					case BIT_2_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 2) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 3, (IY + DIS)
					case BIT_3_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 3) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 4, (IY + DIS)
					case BIT_4_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 4) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 5, (IY + DIS)
					case BIT_5_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 5) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 6, (IY + DIS)
					case BIT_6_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 6) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		
					// BIT 7, (IY + DIS)
					case BIT_7_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Z is set if specified bit is 0; otherwise, it is reset.
						TUtility::GetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 7) == 0 ? mAlu.SetFlag(TFlags::Z) : mAlu.ResetFlag(TFlags::Z);
		
						// H is set.
						mAlu.SetFlag(TFlags::H);
		
						// N is set.
						mAlu.ResetFlag(TFlags::N);
					} break;
		#pragma endregion
		
		#pragma region Set Bit
					// SET 0, (IY + DIS)
					case SET_0_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 0, 1);
					} break;
		
					// SET 1, (IY + DIS)
					case SET_1_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 1, 1);
					} break;
		
					// SET 2, (IY + DIS)
					case SET_2_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 2, 1);
					} break;
		
					// SET 3, (IY + DIS)
					case SET_3_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 3, 1);
					} break;
		
					// SET 4, (IY + DIS)
					case SET_4_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 4, 1);
					} break;
		
					// SET 5, (IY + DIS)
					case SET_5_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 5, 1);
					} break;
		
					// SET 6, (IY + DIS)
					case SET_6_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 6, 1);
					} break;
		
					// SET 7, (IY + DIS)
					case SET_7_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 7, 1);
					} break;
		#pragma endregion
		
		#pragma region Reset Bit
					// SET 0, (IY + DIS)
					case RES_0_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 0, 0);
					} break;
		
					// SET 1, (IY + DIS)
					case RES_1_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 1, 0);
					} break;
		
					// SET 2, (IY + DIS)
					case RES_2_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 2, 0);
					} break;
		
					// SET 3, (IY + DIS)
					case RES_3_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 3, 0);
					} break;
		
					// SET 4, (IY + DIS)
					case RES_4_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 4, 0);
					} break;
		
					// SET 5, (IY + DIS)
					case RES_5_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 5, 0);
					} break;
		
					// SET 6, (IY + DIS)
					case RES_6_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 6, 0);
					} break;
		
					// SET 7, (IY + DIS)
					case RES_7_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						// Set the specified bit
						TUtility::SetBit((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], 7, 0);
					} break;
		#pragma endregion
		
					// RL (IY + DIS)
					case RL_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateLeft<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// RR (IY + DIS)
					case R_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateRight((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// RRC (IY + DIS)
					case RC_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						mAlu.RotateRight((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement], false);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// SLA (IY + DIS)
					case SLA_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
		
						TUtility::RotateLeft((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
						// Set flags
						mAlu.ResetFlag(TFlags::N | TFlags::H);
		
						mRegisters.ProgramCounter() += 2;
					} break;
		
					// SRA (IY + DIS)
					case SRA_INDIRECT_IY_dis:
					{
						// Get the displacement value
						TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter()];;
						auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
		
						// Get the 7th bit for preservation purpose
						bool Bit = TUtility::GetBit(IYRegister, 7);
		
						TUtility::RotateRight(IYRegister) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
						// Put the old 7th bit in the new 7th bit slot
						TUtility::SetBit(IYRegister, 7, Bit);
		
						// Set flags
						mAlu.ResetFlag(TFlags::N | TFlags::H);
					} break;
		
					// SRL (IY + DIS)
					case SRL_INDIRECT_IY_dis:
					{
						TUtility::RotateRight(mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY)) == 0 ? mAlu.ResetFlag(TFlags::C) : mAlu.SetFlag(TFlags::C);
		
						// Set flags
						mAlu.ResetFlag(TFlags::N | TFlags::H);
					} break;
					}
				} break;
		#pragma endregion
		
				// JP (IY)
				case JP_INDIRECT_IY:
				{
					LoadRegisterFromRegister<T16BitRegister>(TRegisterType::PC, TRegisterType::IY);
				} break;
		
		#pragma region Load Instruction
				// LD IY, N
				case LD_IY_n:
				{
					// Get a ref to the PC
					auto& ProgramCounter = mRegisters.ProgramCounter();
		
					mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (NN), IY
				case LD_INDIRECT_ADR_IY:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
					(*mRam)[Address + 1] = IYRegister.GetHighOrderRegister();
					(*mRam)[Address] = IYRegister.GetLowOrderRegister();
		
					ProgramCounter += 3;
				} break;
		
				// LD IY, (NN)
				case LD_IY_INDIRECT_ADR:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const auto Address = TUtility::To16BitValue((*mRam)[ProgramCounter + 2], (*mRam)[ProgramCounter + 1]);
		
					IYRegister = TUtility::To16BitValue((*mRam)[Address + 1], (*mRam)[Address]);
		
					ProgramCounter += 3;
				} break;
		
				// LD (IY + DIS), N
				case LD_INDIRECT_IY_dis_n:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
					const auto Number = (*mRam)[ProgramCounter + 2];
		
					(*mRam)[IYRegister + Displacement] = Number;
		
					ProgramCounter += 3;
				} break;
		
				// LD B, (IY + DIS)
				case LD_B_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::B, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD C, (IY + DIS)
				case LD_C_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::C, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD D, (IY + DIS)
				case LD_D_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::D, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD E, (IY + DIS)
				case LD_E_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::E, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD H, (IY + DIS)
				case LD_H_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::H, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD L, (IY + DIS)
				case LD_L_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::L, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), B
				case LD_INDIRECT_IY_dis_B:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::B, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), C
				case LD_INDIRECT_IY_dis_C:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::C, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), D
				case LD_INDIRECT_IY_dis_D:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::D, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), E
				case LD_INDIRECT_IY_dis_E:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::E, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), H
				case LD_INDIRECT_IY_dis_H:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::H, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), L
				case LD_INDIRECT_IY_dis_L:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::L, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD (IY + DIS), A
				case LD_INDIRECT_IY_dis_A:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadMemoryFromRegister<T8BitRegister>(TRegisterType::A, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
				// LD A, (IY + DIS)
				case LD_A_INDIRECT_IY_dis:
				{
					// Get a ref to the PC and IY and the address of destination
					auto& ProgramCounter = mRegisters.ProgramCounter();
					const auto& IYRegister = mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY);
					const TS8BitValue Displacement = (*mRam)[ProgramCounter + 1];
		
					LoadRegisterFromMemory<T8BitRegister>(TRegisterType::A, IYRegister + Displacement);
		
					ProgramCounter += 2;
				} break;
		
		#pragma endregion
		
				// SUB (IY + DIS)
				case SUB_INDIRECT_IY_dis:
				{
					// Get the displacement value
					TS8BitValue Displacement = (*mRam)[mRegisters.ProgramCounter() + 1];;
		
					mAlu.AluSub<TU8BitValue>((*mRam)[mRegisters.GetRegister<T16BitRegister>(TRegisterType::IY) + Displacement]);
		
					mRegisters.ProgramCounter() += 2;
				} break;
		
				// LD SP, IY
				case LD_SP_IY:
				{
					LoadRegisterFromRegister<T16BitRegister>(TRegisterType::SP, TRegisterType::IY);
		
					++mRegisters.ProgramCounter();
				} break;
				}
			} break;
		#pragma endregion
		
			}
		
			return 0;
		}
	
		TU8BitValue TZ80::GetDataFromDataBus()
		{
			mDataBus = GetComponentAsPtr<tcomponents::TPinComponent>()->PinsToValue<TU8BitValue>(CPUPinGroup::DataBus);
	
			return mDataBus;
		}
	
		void TZ80::PushDataToDataBus(const TU8BitValue & Value)
		{
			mDataBus = Value;
	
			GetComponentAsPtr<tcomponents::TPinComponent>()->ValueToPins<TU8BitValue>(mDataBus, CPUPinGroup::DataBus);
		}
		
		void TZ80::PushDataToAddressBus(const TU16BitValue& Value)
		{
			mAddressBus = Value;
	
			GetComponentAsPtr<tcomponents::TPinComponent>()->ValueToPins<TU8BitValue>(mAddressBus, CPUPinGroup::AddressBus);
		}
	
		TU16BitValue TZ80::GetDataFromAddressBus()
		{
			mAddressBus = GetComponentAsPtr<tcomponents::TPinComponent>()->PinsToValue<TU16BitValue>(CPUPinGroup::AddressBus);
	
			return mAddressBus;
		}
	
		void TZ80::PushMemory(const TRegisterType& Register)
		{
			// Get the SP reference
			auto& StackPointer = mRegisters.StackPointer();
		
			// Get a reference to the register
			const T16BitRegister& RegisterReference = mRegisters.GetRegister<T16BitRegister>(Register);
		
			// First decrement PC and load the high order register
			(*mRam)[--StackPointer] = TUtility::GetUpper8Bit(RegisterReference);
		
			// Than decrement PC again and load the low order register
			(*mRam)[--StackPointer] = TUtility::GetLower8Bit(RegisterReference);
		}
		
		void TZ80::PopMemory(const TRegisterType& Register)
		{
			// Get the SP reference
			auto& StackPointer = mRegisters.StackPointer();
		
			// Get a reference to the register
			T16BitRegister& RegisterReference = mRegisters.GetRegister<T16BitRegister>(Register);
		
			// Load the content pointed bu the SP in the register specified in the argument
			RegisterReference = TUtility::To16BitValue((*mRam)[StackPointer + 1], (*mRam)[StackPointer]);
		
			// Increment the stack pointer by 2
			StackPointer += 2;
		}
		
		void TZ80::Call(const TU16BitValue& Address)
		{
			// Get a reference to the PC
			auto& ProgramCounter = mRegisters.ProgramCounter();
		
			// Increment the PC by 3 to make sure that when we return from the function it goes to the next instruction
			ProgramCounter += 3;
		
			// Push the content of the PC in the stack
			PushMemory(TRegisterType::PC);
		
			// Goes to the location specified by the argument
			ProgramCounter = Address;
		}
		
		void TZ80::Return()
		{
			// Pop the old PC value from the SP
			PopMemory(TRegisterType::PC);
		}
	}
}

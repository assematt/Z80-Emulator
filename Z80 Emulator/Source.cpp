#include <iostream>

#include "TZ80.h"
#include "TManager.h"

using namespace std;
using namespace TGame;

int main()
{
	std::cout.sync_with_stdio(false);
	cout << "Test Z80 Emulator" << endl;

	TInternals::TManager EntitiesManager;
	EntitiesManager.AddComponent<TZ80>();
	EntitiesManager.AddComponent<TModules::TRam>();
	EntitiesManager.InitComponents();

	// Get the Z80 and the ram entity
	auto& Z80 = EntitiesManager.GetComponentAsPtr<TZ80>();
	auto& Ram = EntitiesManager.GetComponentAsPtr<TModules::TRam>();

	Z80->ConnectRam(Ram);
	Z80->LoadProgram("Resources/Blink.0A1");
	Z80->MainLoop();

// 	TZ80 Z80;
// 
// 	Z80.Init();
// 
// 	Z80.LoadProgram("Resources/BLINK.0A1");
// 
// 	Z80.MainLoop();

	
// 	// Creates all the entity we need to function (so far just the z80 and the ram)
// 	TInternals::TManager EntitiesManager;
// 
// 	// Creates the Z80 entities
// 	TInternals::TEntity::TEntityPtr Z80 = TInternals::TEntity::MakeEntity();
// 	Z80->AddComponent<TComponents::TPinComponent>(std::initializer_list<TComponents::TPin>{
// 		// ADDRESS BUS
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 30, CPUPinGroup::AddressBus, 1 }, // A1
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 31, CPUPinGroup::AddressBus, 2 }, // A2
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 32, CPUPinGroup::AddressBus, 0 }, // A0
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 33, CPUPinGroup::AddressBus, 3 }, // A3
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 34, CPUPinGroup::AddressBus, 4 }, // A4
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 35, CPUPinGroup::AddressBus, 5 }, // A5
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 36, CPUPinGroup::AddressBus, 6 }, // A6
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 37, CPUPinGroup::AddressBus, 7 }, // A7
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 38, CPUPinGroup::AddressBus, 8 }, // A8
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 39, CPUPinGroup::AddressBus, 9 }, // A9
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 40, CPUPinGroup::AddressBus, 10 }, // A10
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW,  1, CPUPinGroup::AddressBus, 11 }, // A11
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW,  2, CPUPinGroup::AddressBus, 12 }, // A12
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW,  3, CPUPinGroup::AddressBus, 13 }, // A13
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW,  4, CPUPinGroup::AddressBus, 14 }, // A14
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW,  5, CPUPinGroup::AddressBus, 15 }, // A15
// 
// 		// DATA BUS
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 14, CPUPinGroup::DataBus, 0 }, // D0
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 15, CPUPinGroup::DataBus, 1 }, // D1
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 12, CPUPinGroup::DataBus, 2 }, // D2
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW,  8, CPUPinGroup::DataBus, 3 }, // D3
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW,  7, CPUPinGroup::DataBus, 4 }, // D4
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW,  9, CPUPinGroup::DataBus, 5 }, // D5
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 10, CPUPinGroup::DataBus, 6 }, // D6
// 		{ TComponents::TPin::TMode::INPUT_OUTPUT, TComponents::TPin::TStatus::LOW, 13, CPUPinGroup::DataBus, 7 }, // D7
// 
// 		// SYSTEM CONTROL
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 27, CPUPinGroup::Others }, // M1
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 19, CPUPinGroup::Others }, // MREQ
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 20, CPUPinGroup::Others }, // IORQ
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 21, CPUPinGroup::Others }, // RD
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 22, CPUPinGroup::Others }, // WR
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 28, CPUPinGroup::Others }, // RFSH
// 
// 		// CPU CONTROL
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 18, CPUPinGroup::Others }, // HALT
// 		{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  24, CPUPinGroup::Others }, // WAIT
// 		{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  16, CPUPinGroup::Others }, // INT
// 		{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  17, CPUPinGroup::Others }, // NMI
// 		{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  26, CPUPinGroup::Others }, // RESET 
// 
// 		// CPU BUS CONTROL
// 		{ TComponents::TPin::TMode::OUTPUT, TComponents::TPin::TStatus::LOW, 25, CPUPinGroup::Others }, // BUSAK
// 		{ TComponents::TPin::TMode::INPUT, TComponents::TPin::TStatus::LOW,  23, CPUPinGroup::Others }, // BUSRQ 
// 
// 		// CPUPinGroup::Others
// 		{ TComponents::TPin::TMode::CLOCK, TComponents::TPin::TStatus::LOW,  6, CPUPinGroup::Others }, // CLK
// 		{ TComponents::TPin::TMode::POWER, TComponents::TPin::TStatus::LOW, 11, CPUPinGroup::Others }, // VCC
// 		{ TComponents::TPin::TMode::POWER, TComponents::TPin::TStatus::LOW, 29, CPUPinGroup::Others }, // GND
// 	}, 40);
// 	Z80->AddComponent<TComponents::TZ80Component>();
// 	Z80->InitComponents();
// 	
// 	// Add the entity to the manager
// 	EntitiesManager.AddEntity(std::move(Z80));
// 
// 	do 
// 	{
// 		// Refresh the entities
// 		EntitiesManager.Refresh();
// 
// 		// Update the entities
// 		EntitiesManager.Update();
// 	} while (true);	

	system("PAUSE");
}
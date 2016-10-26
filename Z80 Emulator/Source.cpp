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

	do 
	{
		// Refresh the entities
		EntitiesManager.Refresh();

		// Update the entities
		EntitiesManager.Update();
	} while (true);

	system("PAUSE");
}
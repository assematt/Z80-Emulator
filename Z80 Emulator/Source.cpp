#include <iostream>

#include "TZ80.h"
#include "TManager.h"
#include "TGameApp.h"

using namespace std;

int main()
{
// 	std::cout.sync_with_stdio(false);
// 	cout << "Test Z80 Emulator" << endl;
// 
// 	nne::TManager EntitiesManager;
// 	EntitiesManager.AddComponent<nne::tmodules::TZ80>();
// 	EntitiesManager.AddComponent<nne::tmodules::TRam>();
// 	EntitiesManager.InitComponents();
// 
// 	// Get the Z80 and the ram entity
// 	auto& Z80 = EntitiesManager.GetComponentAsPtr<nne::tmodules::TZ80>();
// 	auto& Ram = EntitiesManager.GetComponentAsPtr<nne::tmodules::TRam>();
// 
// 	Z80->ConnectRam(Ram);
// 	if (!Z80->LoadProgram("Resources/DJ.A01"))
// 	{
// 		std::cout << "Error! Could not open the file" << std::endl;
// 
// 		// Something went bad :(
// 		return 1;
// 	}
// 
// 	do 
// 	{
// 		// Refresh the entities
// 		EntitiesManager.Refresh(sf::Time::Zero);
// 
// 		// Update the entities
// 		EntitiesManager.Update(sf::Time::Zero);
// 	} while (false);

	nne::TGameApp App;

	App.Init();

	return App.Run();
}
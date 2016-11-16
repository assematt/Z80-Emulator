#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "TZ80.h"
#include "TManager.h"
#include "TGameApp.h"
#include "TCacheManager.h"
#include "TLoaders.h"

using namespace std;

int main()
{
// 	std::cout.sync_with_stdio(false);
// 	cout << "Test Z80 Emulator" << endl;
// 
// 	nne::TManager EntitiesManager;
// 	EntitiesManager.addComponent<nne::tmodules::TZ80>();
// 	EntitiesManager.addComponent<nne::tmodules::TRam>();
// 	EntitiesManager.initComponents();
// 
// 	// Get the Z80 and the ram entity
// 	auto& Z80 = EntitiesManager.getComponentAsPtr<nne::tmodules::TZ80>();
// 	auto& Ram = EntitiesManager.getComponentAsPtr<nne::tmodules::TRam>();
// 
// 	Z80->ConnectRam(Ram);
// 	if (!Z80->LoadProgram("resources/programs/DJ.A01"))
// 	{
// 		std::cout << "Error! Could not open the file" << std::endl;
// 
// 		// Something went bad :(
// 		return 1;
// 	}
// 
// 	do 
// 	{
// 		// refresh the entities
// 		EntitiesManager.refresh(sf::Time::Zero);
// 
// 		// update the entities
// 		EntitiesManager.update(sf::Time::Zero);
// 	} while (false)
	
	nne::TGameApp App;

	App.init();

	return App.run();
}
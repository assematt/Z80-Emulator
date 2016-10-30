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
// 	TInternals::TManager EntitiesManager;
// 	EntitiesManager.AddComponent<TZ80>();
// 	EntitiesManager.AddComponent<TModules::TRam>();
// 	EntitiesManager.InitComponents();
// 
// 	// Get the Z80 and the ram entity
// 	auto& Z80 = EntitiesManager.GetComponentAsPtr<TZ80>();
// 	auto& Ram = EntitiesManager.GetComponentAsPtr<TModules::TRam>();
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
// 		EntitiesManager.Refresh();
// 
// 		// Update the entities
// 		EntitiesManager.Update();
// 	} while (false);
// 
// 	sf::RenderWindow Window(sf::VideoMode(1024, 768), "Z80 Emulator");
// 
// 	while (Window.isOpen())
// 	{
// 		sf::Event Event;
// 		while (Window.pollEvent(Event))
// 		{
// 			if (Event.type == sf::Event::Closed)
// 				Window.close();
// 		}
// 
// 		Window.clear();
// 		Window.display();
// 	}
// 
// 	// Everything went ok
// 	return 0;

	nne::TGameApp App;

	App.Init();

	return App.Run();
}
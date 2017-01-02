#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <map>

#include "TZ80Component.h"
#include "TManager.h"
#include "TGameApp.h"
#include "TCacheManager.h"
#include "TLoaders.h"
#include "TFactory.h"

using namespace std;

int main()
{
// 	std::cout.sync_with_stdio(false);
// 	cout << "Test Z80 Emulator" << endl;
// 
// 	nne::TManager EntitiesManager;
// 	EntitiesManager.addEntity(nne::TFactory::makeZ80(), "Z80");
// 	EntitiesManager.addEntity(nne::TFactory::makeRam(), "Ram");
// 	EntitiesManager.initEntities();
// 
// 	// Get the Z80 and the ram entity
// 	auto Z80 = EntitiesManager.getEntityByKey("Z80")->getComponentAsPtr<nne::tcomponents::TZ80Component>();
// 	auto Ram = EntitiesManager.getEntityByKey("Ram");
// 
// 	Z80->connectRam(Ram);
// 	if (!Z80->loadProgram("resources/programs/INDIR.A01"))
// 	{
// 		std::cout << "Error! Could not open the file" << std::endl;
// 
// 		// Something went bad :(
// 		return 1;
// 	}
// 	Z80->resumeExecution();
// 
// 	do 
// 	{
// 		// refresh the entities
// 		EntitiesManager.refresh(sf::Time::Zero);
// 
// 		// update the entities
// 		EntitiesManager.update(sf::Time::Zero);
// 
// 		sf::sleep(sf::seconds(0.25f));
// 	} while (true);
	
	nne::TGameApp App;

	App.init();

	return App.run();
}
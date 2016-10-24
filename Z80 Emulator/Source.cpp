#include <iostream>

#include "TZ80.h"

using namespace std;

int main()
{
	std::cout.sync_with_stdio(false);
	cout << "Test Z80 Emulator" << endl;
	

	TGame::TZ80 Z80;

	Z80.Init();

	Z80.LoadProgram("Resources/BLINK.0A1");

	Z80.MainLoop();

	system("PAUSE");
}
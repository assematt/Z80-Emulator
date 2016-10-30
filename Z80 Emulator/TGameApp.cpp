#include "TGameApp.h"

namespace nne
{

	TGameApp::TGameApp() :
		mAppName(PROGRAM_NAME)
	{
		mAppWindow = std::make_shared<TGameWindow>();
	}

	bool TGameApp::Init()
	{
		mAppWindow->create(sf::VideoMode(1024, 768), mAppName.c_str(), sf::Style::Close);

		return true;
	}

	bool TGameApp::LoadConfiguration(const std::string& ConfigFile)
	{
		return true;
	}

	int TGameApp::Run()
	{
		mAppClock.restart();

		while (mAppWindow->isOpen())
		{
			sf::Time ElapsedTime = mAppClock.restart();

			EventLoop();

			Refresh(ElapsedTime);

			Update(ElapsedTime);

			Draw();
		}

		return 0;
	}

	void TGameApp::EventLoop()
	{
		while (mAppWindow->pollEvent(mAppEvent))
		{
			//mAppGui.ProcessEvents(mAppEvent);

			if (mAppEvent.type == sf::Event::Closed)
				mAppWindow->close();
		}
	}

	void TGameApp::Refresh(sf::Time ElapsedTime)
	{

	}

	void TGameApp::Update(sf::Time ElapsedTime)
	{

	}

	void TGameApp::Draw()
	{
		// Clear the back buffered window
		mAppWindow->clear();

		// Display the back buffered window
		mAppWindow->display();
	}

}
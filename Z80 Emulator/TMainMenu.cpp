#include "TMainMenu.h"

namespace nne
{
	namespace tgui
	{
		void TMainMenu::Setup()
		{
			tgui::TGuiButton::UniquePtr StoryMode = std::make_unique<tgui::TGuiButton>();
			StoryMode->SetPosition(GetReferencePointPosition());
			StoryMode->SetName("STORY_MODE");
			StoryMode->SetCaption("STORY MODE");
			this->AddWidget(StoryMode);

			tgui::TGuiButton::UniquePtr SandboxMode = std::make_unique<tgui::TGuiButton>();
			SandboxMode->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 50.f));
			SandboxMode->SetName("SANDBOX_MODE");
			SandboxMode->SetCaption("SANDBOX MODE");
			this->AddWidget(SandboxMode);

			tgui::TGuiButton::UniquePtr ChallangeMode = std::make_unique<tgui::TGuiButton>();
			ChallangeMode->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 100.f));
			ChallangeMode->SetName("CHALLANGE_MODE");
			ChallangeMode->SetCaption("CHALLANGE MODE");
			this->AddWidget(ChallangeMode);

			tgui::TGuiButton::UniquePtr Options = std::make_unique<tgui::TGuiButton>();
			Options->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 150.f));
			Options->SetName("OPTIONS");
			Options->SetCaption("OPTIONS");
			this->AddWidget(Options);

			tgui::TGuiButton::UniquePtr Credits = std::make_unique<tgui::TGuiButton>();
			Credits->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 200.f));
			Credits->SetName("CREDITS");
			Credits->SetCaption("CREDITS");
			this->AddWidget(Credits);

			tgui::TGuiButton::UniquePtr Quit = std::make_unique<tgui::TGuiButton>();
			Quit->SetPosition(GetReferencePointPosition() + sf::Vector2f(0.f, 250.f));
			Quit->SetName("QUIT");
			Quit->SetCaption("QUIT");
			this->AddWidget(Quit);
		}

		void TMainMenu::HandleEvent(sf::Event& Event)
		{
			if (Event.type == sf::Event::MouseButtonPressed)
			{
				// Check what we clicked
				int Index = 0;
				for (auto& Widget : mWidgetsContainer)
				{
					auto& MouseX = Event.mouseButton.x;
					auto& MouseY = Event.mouseButton.y;

					if (CheckMouseClick(Widget, { MouseX, MouseY }))
					{
						switch (Index)
						{
						case 0: OnNewGameButtonClick(MouseX, MouseY);
							break;
						case 1: OnInstructionButtonClick(MouseX, MouseY);
							break;
						case 2: OnInfoButtonClick(MouseX, MouseY);
							break;
						case 3: OnExitButtonClick(MouseX, MouseY);
							break;
						}

						break;
					}

					++Index;
				}
			}
		}

		void TMainMenu::OnNewGameButtonClick(int X, int Y)
		{
			mParentManager->ChangeMenu(1);
		}

		void TMainMenu::OnInstructionButtonClick(int X, int Y)
		{
			mParentManager->ChangeMenu(2);
		}

		void TMainMenu::OnInfoButtonClick(int X, int Y)
		{
			mParentManager->ChangeMenu(1);
		}

		void TMainMenu::OnExitButtonClick(int X, int Y)
		{
			nne::TGuiWindow::GetInstance().close();
		}

	}
}


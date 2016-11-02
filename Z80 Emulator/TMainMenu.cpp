#include "TMainMenu.h"

namespace nne
{
	namespace tgui
	{
		void TMainMenu::Setup()
		{
			// Add the the new game button
// 			tgui::TGuiWidget::UniquePtr NewGameButton = std::make_unique<tgui::TGuiWidget>();
// 			NewGameButton->GetComponentAsPtr<TFont>()->SetText("New Game");
// 			NewGameButton->GetComponentAsPtr<TFont>()->SetStyle(TFont::LINK);
// 			this->AddWidget(NewGameButton);
// 
// 			// Add the the instruction button
// 			tgui::TGuiWidget::UniquePtr InstructionButton = std::make_unique<tgui::TGuiWidget>();
// 			InstructionButton->GetComponentAsPtr<TFont>()->SetText("Instruction");
// 			InstructionButton->GetComponentAsPtr<TFont>()->SetStyle(TFont::LINK);
// 			InstructionButton->GetComponentAsPtr<TTransformable>()->Move(0.f, 96.f);
// 			this->AddWidget(InstructionButton);
// 
// 			// Add the the info button
// 			tgui::TGuiWidget::UniquePtr InfoButton = std::make_unique<tgui::TGuiWidget>();
// 			InfoButton->GetComponentAsPtr<TFont>()->SetText("Info");
// 			InfoButton->GetComponentAsPtr<TFont>()->SetStyle(TFont::LINK);
// 			InfoButton->GetComponentAsPtr<TTransformable>()->Move(0.f, 192.f);
// 			this->AddWidget(InfoButton);
// 
// 			// Add the the exit button
// 			tgui::TGuiWidget::UniquePtr ExitButton = std::make_unique<tgui::TGuiWidget>();
// 			ExitButton->GetComponentAsPtr<TFont>()->SetText("Exit");
// 			ExitButton->GetComponentAsPtr<TFont>()->SetStyle(TFont::LINK);
// 			ExitButton->GetComponentAsPtr<TTransformable>()->Move(0.f, 288.f);
// 			this->AddWidget(ExitButton);

			tgui::TGuiButton::UniquePtr TestButton = std::make_unique<tgui::TGuiButton>();
			this->AddWidget(TestButton);
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

		void TMainMenu::Display()
		{

		}

		void TMainMenu::OnNewGameButtonClick(int X, int Y)
		{
			mParentManager->ChangeMenu(2);
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


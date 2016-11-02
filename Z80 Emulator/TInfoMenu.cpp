#include "TInfoMenu.h"

namespace nne
{
	namespace tgui
	{
		void TInfoMenu::Setup()
		{
			// Add the the new game button
// 			tgui::TGuiWidget::UniquePtr VersionButton = std::make_unique<tgui::TGuiWidget>();
// 			VersionButton->GetComponentAsPtr<TFont>()->SetText("Version 0.1");
// 			this->AddWidget(VersionButton);
// 
// 			// Add the the instruction button
// 			tgui::TGuiWidget::UniquePtr DateButton = std::make_unique<tgui::TGuiWidget>();
// 			DateButton->GetComponentAsPtr<TFont>()->SetText("Date: 14/12/2015");
// 			DateButton->GetComponentAsPtr<TTransformable>()->Move(0.f, 96.f);
// 			this->AddWidget(DateButton);
// 
// 			// Add the the info button
// 			tgui::TGuiWidget::UniquePtr AuthorButton = std::make_unique<tgui::TGuiWidget>();
// 			AuthorButton->GetComponentAsPtr<TFont>()->SetText("Author: Assenza Matteo");
// 			AuthorButton->GetComponentAsPtr<TTransformable>()->Move(0.f, 192.f);
// 			this->AddWidget(AuthorButton);
// 
// 			// Add the the exit button
// 			tgui::TGuiWidget::UniquePtr BackButton = std::make_unique<tgui::TGuiWidget>();
// 			BackButton->GetComponentAsPtr<TFont>()->SetText("Go back to main menu");
// 			BackButton->GetComponentAsPtr<TFont>()->SetStyle(TFont::LINK);
// 			BackButton->GetComponentAsPtr<TTransformable>()->Move(0.f, 288.f);
// 			this->AddWidget(BackButton);
		}

		void TInfoMenu::HandleEvent(sf::Event& Event)
		{

		}

		void TInfoMenu::Display()
		{

		}
	}
}


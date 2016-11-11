#include "TNewGameLoadingScreen.h"

namespace nne
{

	void tgui::TNewGameLoadingScreen::Setup()
	{
		tgui::TGuiButton::UniquePtr Loading = std::make_unique<tgui::TGuiButton>();
		Loading->SetPosition(GetReferencePointPosition());
		Loading->SetName("LOADING");
		Loading->SetCaption("LOADING");
		this->AddWidget(Loading);

		mFiles.push_back("resources/boards/logic_board.brd");
	}

	void tgui::TNewGameLoadingScreen::Loading(std::atomic_bool& IsLoading)
	{
		sf::sleep(sf::seconds(5.f));

		IsLoading = false;
	}

	void tgui::TNewGameLoadingScreen::HandleEvent(sf::Event& Event)
	{

	}

}
#include "TNewGameLoadingScreen.h"

namespace nne
{

	void tgui::TNewGameLoadingScreen::Setup()
	{
		tgui::TGuiImage::UniquePtr BackgroundColor = std::make_unique<tgui::TGuiImage>();
		sf::Image TempImage;
		TempImage.create(1920, 1080, sf::Color(0, 0, 170));
		sf::Texture TempTexture;
		TempTexture.loadFromImage(TempImage);
		BackgroundColor->SetImage(TempTexture);
		this->AddWidget(BackgroundColor, 0);

		tgui::TGuiButton::UniquePtr Loading = std::make_unique<tgui::TGuiButton>();
		Loading->SetPosition(GetReferencePointPosition());
		Loading->SetName("LOADING");
		Loading->SetCaption("LOADING");
		this->AddWidget(Loading, 1);

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
#include "TNewGameLoadingScreen.h"

namespace nne
{

	void tgui::TNewGameLoadingScreen::setup(nne::tgui::TGuiManager* GuiManager)
	{
		mParentManager = GuiManager;

		tgui::TGuiImage::UniquePtr BackgroundColor = std::make_unique<tgui::TGuiImage>();
		sf::Image TempImage;
		TempImage.create(1920, 1080, sf::Color(0, 0, 170));
		sf::Texture TempTexture;
		TempTexture.loadFromImage(TempImage);
		BackgroundColor->SetImage(TempTexture);
		this->addWidget(BackgroundColor, 0);

		tgui::TGuiButton::UniquePtr Loading = std::make_unique<tgui::TGuiButton>();
		Loading->setPosition(getReferencePointPosition());
		Loading->setName("LOADING");
		Loading->SetCaption("LOADING");
		this->addWidget(Loading, 1);

		mFiles.push_back("resources/boards/logic_board.brd");
	}

	void tgui::TNewGameLoadingScreen::loading(std::atomic_bool& IsLoading)
	{
		sf::sleep(sf::seconds(5.f));

		IsLoading = false;
	}

	void tgui::TNewGameLoadingScreen::handleEvent(sf::Event& Event)
	{

	}

}
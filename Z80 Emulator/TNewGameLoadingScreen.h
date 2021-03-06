#pragma once

#include "IScene.h"
#include "ILoadingScreen.h"
#include "TGuiManager.h"

namespace nne
{
	class TNewGameLoadingScreen : public tgui::ILoadingScreen, public IScene
	{
	public:

		virtual void loading(std::atomic_bool& IsLoading) override;

		virtual void init() override;

		virtual ID& run(const sf::Time& ElapsedTime) override;

	protected:
		virtual ID eventLoop() override;

		virtual void refresh(sf::Time ElapsedTime) override;

		virtual void update(sf::Time ElapsedTime) override;

		virtual void draw() override;

	private:
		sf::Event			mAppEvent;
		tgui::TGuiManager	mAppGui;
	};
}
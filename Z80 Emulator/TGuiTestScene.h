#pragma once

#include <SFML/Window/Event.hpp>

#include "IScene.h"
#include "TGuiManager.h"

namespace nne
{
	class TGuiTestScene : public IScene, public tgui::IScreenView
	{

	public:
		virtual void init() override;

	protected:
		virtual ID eventLoop() override;

		virtual void refresh(sf::Time ElapsedTime) override;

		virtual void update(sf::Time ElapsedTime) override;

		virtual void draw() override;

	private:
		tgui::TGuiManager	mAppGui;
	};
}
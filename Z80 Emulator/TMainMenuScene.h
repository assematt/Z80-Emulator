#pragma once

#include <SFML/Window/Event.hpp>

#include "IScene.h"
#include "TGuiManager.h"

namespace nne
{
	class TMainMenuScene : public IScene
	{
		
	public:
		virtual void init() override;
		
	protected:
		virtual ID eventLoop() override;

		virtual void refresh(const sf::Time& ElapsedTime) override;

		virtual void update(const sf::Time& ElapsedTime) override;

		virtual void draw() override;

	private:
		tgui::TGuiManager mGuiManager;
	};
}
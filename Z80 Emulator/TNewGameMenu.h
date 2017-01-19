#pragma once

#include "TContainer.h"
#include "IMenu.h"

namespace nne
{
	namespace tgui
	{
		class TNewGameMenu : public TContainer, public IMenu
		{
		public:

			using Ptr = std::shared_ptr<TNewGameMenu>;

			TNewGameMenu(const std::string& MenuName = "NEW_GAME_MENU");

			virtual void init(TGuiManager* GuiManager) override;

		};
	}
}
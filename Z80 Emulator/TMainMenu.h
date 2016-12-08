#pragma once

#include "TContainer.h"
#include "IMenu.h"

namespace nne
{
	namespace tgui
	{
		class TMainMenu : public TContainer, public IMenu
		{
		public:

			using Ptr = std::shared_ptr<TMainMenu>;

			virtual void init(TGuiManager* GuiManager) override;

		};
	}
}
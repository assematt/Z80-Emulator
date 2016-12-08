#pragma once

namespace nne
{
	namespace tgui
	{
		class TGuiManager;

		struct IMenu
		{
			virtual ~IMenu() = default;

			virtual void init(TGuiManager* GuiManager) = 0;
		};
	}
}
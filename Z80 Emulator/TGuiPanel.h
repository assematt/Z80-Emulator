#pragma once

#include "TGuiWidget.h"
#include "IComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{
		class TGuiPanel : public TGuiWidget
		{
		public:
			TGuiPanel();

			using UniquePtr = std::unique_ptr<TGuiPanel>;
			using SharedPtr = std::shared_ptr<TGuiPanel>;

			/// Init function
			void init();
			
		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		private:
			std::vector<TGuiWidget*> mChildWidget;
		};
	}
}
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
		class TGuiButton : public TGuiWidget
		{
		public:
			TGuiButton();

			using UniquePtr = std::unique_ptr<TGuiButton>;
			using SharedPtr = std::shared_ptr<TGuiButton>;

			/// Init function
			void init();
			
			/// Functions to change the widget property
			void SetCaption(const std::string& WidgetName);
			const std::string& GetCaption() const;
			
		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}
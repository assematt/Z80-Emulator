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
		class TGuiStaticText : public TGuiWidget
		{
		public:
			TGuiStaticText();

			using UniquePtr = std::unique_ptr<TGuiStaticText>;
			using SharedPtr = std::shared_ptr<TGuiStaticText>;

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
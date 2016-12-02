#pragma once

#include "TWidget.h"
#include "IComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{
		class TStaticText : public TWidget
		{
		public:
			TStaticText();

			using UniquePtr = std::unique_ptr<TStaticText>;
			using SharedPtr = std::shared_ptr<TStaticText>;

			/// Init function
			void init();

			/// Functions to change the widget property
			void SetCaption(const std::string& WidgetName);
			const std::string& GetCaption() const;

			/// Set character size
			void setCharacterSize(const std::size_t& CharacterSize);
			const std::size_t& getCharacterSize();

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}
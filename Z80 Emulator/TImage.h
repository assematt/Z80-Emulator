#pragma once

#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TImage : public TWidget
		{
		public:
			using Ptr = std::shared_ptr<TImage>;

			TImage();

			/// Functions to change the widget property
			void setImage(const sf::Texture& Image);
			const sf::Texture& GetImage() const;
			
		private:
			void draw(sf::RenderTarget& Target, sf::RenderStates States) const;
		};
	}
}
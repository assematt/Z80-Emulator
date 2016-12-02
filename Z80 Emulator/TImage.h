#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TWidget.h"
#include "IComponent.h"

namespace nne
{
	namespace tgui
	{
		class TImage : public TWidget
		{
		public:
			TImage();

			using UniquePtr = std::unique_ptr<TImage>;
			using SharedPtr = std::shared_ptr<TImage>;

			/// Init function
			void init();
			
			/// Functions to change the widget property
			void SetImage(const sf::Texture& Image);
			const sf::Texture& GetImage() const;

			/// Functions to get/set the widget size
			virtual void setSize(const sf::Vector2u& Size) override;
			virtual sf::Vector2u getSize() override;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}
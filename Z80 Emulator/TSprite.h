#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

#include "TTransformable.h"
#include "TdrawableVector.h"
#include "IComponent.h"
#include "TEntity.h"
#include "TResource.h"

namespace nne
{
	class TSprite : public nne::IComponent
	{
	public:
		TSprite();

		void init() override;

		void update() override {}

		void refresh() override {}
		
		/// Function to set/get the sprite texture
		void setTexture(const sf::Texture& Texture);
		const sf::Texture& getTexture() const;

		/// Function to set/get the sprite opacity
		void setOpacity(sf::Uint8 Opacity);
		const sf::Uint8& getOpacity() const; 

		/// Functions to get/set the widget size
		void setSize(const sf::Vector2u& Size);
		const sf::Vector2u& getSize() const;

	private:
		void updateTextureBounds(const sf::Vector2f& NewTextureSize);
				
	private:
		std::shared_ptr<sf::VertexArray> mVertexArray;
		std::shared_ptr<sf::Texture> mTexture;
		sf::Uint8 mOpacity;
	};
}
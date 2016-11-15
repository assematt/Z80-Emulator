#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

#include "TTransformable.h"
#include "TDrawableVector.h"
#include "IComponent.h"
#include "TEntity.h"
#include "TResource.h"

namespace nne
{
	class TSprite : public nne::IComponent
	{
	public:
		TSprite();

		void Init() override;

		void Update() override {}

		void Refresh() override {}
		
		/// Function to set/get the sprite texture
		void SetTexture(const sf::Texture& Texture);
		const sf::Texture& GetTexture() const;

		/// Function to set/get the sprite opacity
		void SetOpacity(sf::Uint8 Opacity);
		const sf::Uint8& GetOpacity() const; 

		/// Functions to get/set the widget size
		void SetSize(const sf::Vector2u& Size);
		const sf::Vector2u& GetSize() const;

	private:
		void UpdateTextureBounds(const sf::Vector2f& NewTextureSize);
				
	private:
		std::shared_ptr<sf::VertexArray> mVertexArray;
		std::shared_ptr<sf::Texture> mTexture;
		sf::Uint8 mOpacity;
	};
}
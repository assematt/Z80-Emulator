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
		void SetTexture(sf::Texture& Texture);
		const sf::Texture& GetTexture() const;

		/// Function to set/get the sprite opacity
		void SetOpacity(sf::Uint8 Opacity);
		const sf::Uint8& GetOpacity() const;
				
	private:
		std::shared_ptr<sf::Sprite> mSprite;
		sf::Texture mTexture;
		sf::Uint8 mOpacity;
	};
}
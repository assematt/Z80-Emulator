#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include INCLUDE_ENTITY_CLASS
#include "TResource.h"

namespace nne
{
	class TDrawableComponent : BASE_COMPONENT_CLASS, public sf::Drawable, public sf::Transformable
	{
	public:
		TDrawableComponent();

		void init() override;

		void update(REFRESH_UPDATE_PARAMETER) override {}

		void refresh(REFRESH_UPDATE_PARAMETER) override {}
		
		/// Function to set/get the sprite texture
		void setTexture(const sf::Texture& Texture, bool UpdateBounds = true);
		const sf::Texture& getTexture() const;

		/// Function to set/get the sprite texture rect
		void setTextureRect(const sf::IntRect& rectangle);
		const sf::IntRect& getTextureRect() const;

		/// Functino to set/get the sprite color
		void setColor(const sf::Color& Color);
		const sf::Color& getColor() const;

		/// Function to set/get the sprite opacity
		void setOpacity(sf::Uint8 Opacity);
		const sf::Uint8& getOpacity() const; 

		/// Functions to get/set the widget size
		void setSize(const sf::Vector2u& Size);
		sf::Vector2u getSize();

		/// Get a ref to the internal vertex array for other component to use
		sf::VertexArray& getVertexArray();
		const sf::VertexArray& getVertexArray() const;

		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;

	protected:
		/// SFML function to draw the graphics
		virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

	private:
		/// Update the visible texture bound
		void updateTextureBounds(const sf::IntRect& TextureRect);

		/// Update the size of the sprite
		void updateSpriteBounds(const sf::Vector2u& SpriteSize);

		/// Compute local bounds for drawables with more than 4 vertices
		sf::FloatRect computeComplexLocalBound() const;
				
	private:
		sf::VertexArray		mVertexArray;
		const sf::Texture*	mTexture;
	};
}
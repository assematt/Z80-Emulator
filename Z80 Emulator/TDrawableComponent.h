#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "IComponent.h"
#include "TEntity.h"
#include "TResource.h"

namespace nne
{
	class TDrawableComponent : public nne::IComponent, public sf::Drawable, public sf::Transformable
	{
	public:
		TDrawableComponent();

		void init() override;

		void update() override {}

		void refresh() override {}
		
		/// Function to set/get the sprite texture
		void setTexture(const sf::Texture& Texture);
		void setTexture(const sf::Texture* Texture);
		const sf::Texture& getTexture() const;

		/// Functio to set/get the sprite color
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

		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

	protected:
		/// SFML function to draw the graphics
		virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

	private:
		/// Update the visible texture bound
		void updateTextureBounds(const sf::IntRect& TextureRect);

		/// Update the size of the sprite
		void updateSpriteBounds(const sf::Vector2u& SpriteSize);

		/// Compute local bounds for drawables with more than 4 vertices
		sf::FloatRect computeComplexLocalBound();
				
	private:
		const sf::Texture*					mExternalTexture;
		std::shared_ptr<sf::Texture>		mTexture;
		std::shared_ptr<sf::VertexArray>	mVertexArray;
	};
}
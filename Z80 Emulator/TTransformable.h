#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <algorithm>

#include "IComponent.h"
#include "TSprite.h"

namespace nne
{
	class TTransformable : public nne::IComponent
	{
	public:

		TTransformable();
		
		void init() override {}

		void update() override {}

		void refresh() override;

		/// Function to set the entity position
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f& position);

		/// Function to set the entity rotation
		void setRotation(float angle);

		/// Function to set the entity scale
		void setScale(float factorX, float factorY);
		void setScale(const sf::Vector2f& factors);

		/// Function to set the entity origin
		void setOrigin(float x, float y);
		void setOrigin(const sf::Vector2f& origin);

		/// Function to get the entity position
		const sf::Vector2f& getPosition() const;

		/// Function to get the entity rotation
		float getRotation() const;

		/// Get the entity scale
		const sf::Vector2f& getScale() const;

		/// Get the entity origin
		const sf::Vector2f& getOrigin() const;

		/// Function to get the entity bounds
		const sf::FloatRect& getBounds();

		/// Function to get the entity size
		const sf::Vector2f& getSize() const;

		/// Move the entity by a specified offset
		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f& offset);

		/// Rotate the entity by a specified amount
		void rotate(float angle);

		/// Scale the entity by a specified amount
		void scale(float factorX, float factorY);
		void scale(const sf::Vector2f& factor);

		/// Function to get the internal transform object
		const sf::Transform& getTransform() const;
		const sf::Transform& getInverseTransform() const;

	private:
		void updateBounds();
		const float computeWidth(const sf::VertexArray& Vertices) const;
		const float computeHeigth(const sf::VertexArray& Vertices) const;

	private:
		sf::Transformable mTransformable;
		sf::FloatRect mBounds;
		bool mNeedrefresh;
	};
}
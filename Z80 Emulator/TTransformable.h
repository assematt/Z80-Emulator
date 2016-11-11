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
		
		void Init() override {}

		void Update() override {}

		void Refresh() override {}

		/// Function to set the entity position
		void SetPosition(float x, float y);
		void SetPosition(const sf::Vector2f& position);

		/// Function to set the entity rotation
		void SetRotation(float angle);

		/// Function to set the entity scale
		void SetScale(float factorX, float factorY);
		void SetScale(const sf::Vector2f& factors);

		/// Function to set the entity origin
		void SetOrigin(float x, float y);
		void SetOrigin(const sf::Vector2f& origin);

		/// Function to get the entity position
		const sf::Vector2f& GetPosition() const;

		/// Function to get the entity rotation
		float GetRotation() const;

		/// Get the entity scale
		const sf::Vector2f& GetScale() const;

		/// Get the entity origin
		const sf::Vector2f& GetOrigin() const;

		/// Function to get the entity bounds
		const sf::FloatRect& GetEntityBounds() const;

		/// Funcion to get the enity size
		const sf::Vector2f& GetEntitySize() const;

		/// Move the entity by a specified offset
		void Move(float offsetX, float offsetY);
		void Move(const sf::Vector2f& offset);

		/// Rotate the entity by a specified amount
		void Rotate(float angle);

		/// Scale the entity by a specified amount
		void Scale(float factorX, float factorY);
		void Scale(const sf::Vector2f& factor);

		/// Function to get the internal transform object
		const sf::Transform& GetTransform() const;
		const sf::Transform& GetInverseTransform() const;

	private:
// 		const float ComputeWidth(const sf::VertexArray& Vertices) const;
// 		const float ComputeHeigth(const sf::VertexArray& Vertices) const;

	private:
		sf::Transformable mTransformable;
		mutable sf::FloatRect mBounds;
	};
}
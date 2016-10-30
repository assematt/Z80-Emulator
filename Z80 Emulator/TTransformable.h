#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <algorithm>

#include "IComponent.h"
#include "TTexture.h"

namespace nne
{
	struct TTransformable : nne::IComponent
	{
	public:

// 		void Update(const sf::Time& ElapsedTime) override {};
// 
// 		void Refresh(const sf::Time& ElapsedTime) override {};

		void Init() override {}

		void Update() override {}

		void SetPosition(float x, float y);
		void SetPosition(const sf::Vector2f& position);

		void SetRotation(float angle);

		void SetScale(float factorX, float factorY);
		void SetScale(const sf::Vector2f& factors);

		void SetOrigin(float x, float y);
		void SetOrigin(const sf::Vector2f& origin);

		const sf::Vector2f& GetPosition() const;

		float GetRotation() const;

		const sf::Vector2f GetSize() const;
		const sf::Vector2f& GetScale() const;

		const sf::Vector2f& GetOrigin() const;

		void Move(float offsetX, float offsetY);
		void Move(const sf::Vector2f& offset);

		void Rotate(float angle);

		void Scale(float factorX, float factorY);
		void Scale(const sf::Vector2f& factor);

		const sf::Transform& GetTransform() const;

		const sf::Transform& GetInverseTransform() const;

	private:
		const float ComputeWidth(const sf::VertexArray& Vertices) const;
		const float ComputeHeigth(const sf::VertexArray& Vertices) const;

	private:
		sf::Transformable mTransformable;
	};
}
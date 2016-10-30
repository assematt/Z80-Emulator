#include "TTransformable.h"

namespace nne
{
	void TTransformable::SetPosition(float x, float y)
	{
		mTransformable.setPosition(x, y);
	}

	void TTransformable::SetRotation(float angle)
	{
		mTransformable.setRotation(angle);
	}

	void TTransformable::SetScale(float factorX, float factorY)
	{
		mTransformable.setScale(factorX, factorY);
	}

	void TTransformable::SetOrigin(float x, float y)
	{
		mTransformable.setOrigin(x, y);
	}

	const sf::Vector2f& TTransformable::GetPosition() const
	{
		return mTransformable.getPosition();
	}

	float TTransformable::GetRotation() const
	{
		return mTransformable.getRotation();
	}

	const sf::Vector2f TTransformable::GetSize() const
	{
		auto& VertexArray = mParent->GetComponentAsPtr<TTexture>()->GetVertexArray();

		return sf::Vector2f(ComputeWidth(VertexArray), ComputeHeigth(VertexArray));
	}

	const sf::Vector2f& TTransformable::GetScale() const
	{
		return mTransformable.getScale();
	}

	const sf::Vector2f& TTransformable::GetOrigin() const
	{
		return mTransformable.getOrigin();
	}

	void TTransformable::Move(float offsetX, float offsetY)
	{
		mTransformable.move(offsetX, offsetY);
	}

	void TTransformable::Rotate(float angle)
	{
		mTransformable.rotate(angle);
	}

	void TTransformable::Scale(float factorX, float factorY)
	{
		mTransformable.scale(factorX, factorY);
	}

	const sf::Transform& TTransformable::GetTransform() const
	{
		return mTransformable.getTransform();
	}

	const sf::Transform& TTransformable::GetInverseTransform() const
	{
		return mTransformable.getInverseTransform();
	}

	const float TTransformable::ComputeWidth(const sf::VertexArray& Vertices) const
	{
		const auto& NumOfVertices = Vertices.getVertexCount();
		float MaxValue = 0.f;

		for (auto Index = 0u; Index < NumOfVertices; ++Index)
		{
			auto& Vertex = Vertices[Index];

			if (Vertices[Index].position.x > MaxValue)
			{
				MaxValue = Vertices[Index].position.x;
			}
		}

		return MaxValue;
	}

	const float TTransformable::ComputeHeigth(const sf::VertexArray& Vertices) const
	{
		const auto& NumOfVertices = Vertices.getVertexCount();
		float MaxValue = 0.f;

		for (auto Index = 0u; Index < NumOfVertices; ++Index)
		{
			auto& Vertex = Vertices[Index];

			if (Vertices[Index].position.y > MaxValue)
			{
				MaxValue = Vertices[Index].position.y;
			}
		}

		return MaxValue;
	}

	void TTransformable::Scale(const sf::Vector2f& factor)
	{
		mTransformable.scale(factor);
	}

	void TTransformable::Move(const sf::Vector2f& offset)
	{
		mTransformable.move(offset);
	}

	void TTransformable::SetOrigin(const sf::Vector2f& origin)
	{
		mTransformable.setOrigin(origin);
	}

	void TTransformable::SetScale(const sf::Vector2f& factors)
	{
		mTransformable.setScale(factors);
	}

	void TTransformable::SetPosition(const sf::Vector2f& position)
	{
		mTransformable.setPosition(position);
	}
}
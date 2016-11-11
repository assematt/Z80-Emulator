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

/*
	const sf::Vector2f TTransformable::GetSize() const
	{
		auto& VertexArray = mParent->GetComponentAsPtr<TTexture>()->GetVertexArray();

		return sf::Vector2f(ComputeWidth(VertexArray), ComputeHeigth(VertexArray));
	}*/

	const sf::Vector2f& TTransformable::GetScale() const
	{
		return mTransformable.getScale();
	}

	const sf::Vector2f& TTransformable::GetOrigin() const
	{
		return mTransformable.getOrigin();
	}

	const sf::FloatRect& TTransformable::GetEntityBounds() const
	{
		auto& DrawableVector = *mParent->GetComponentAsPtr<TDrawableVector>();

		mBounds.height = 0;
		mBounds.width = 0;
		mBounds.left = 0;
		mBounds.top = 0;

		for (std::size_t Index = 0; Index < DrawableVector.GetVectorSize(); ++Index)
		{
			sf::Sprite* Sprite = dynamic_cast<sf::Sprite*>(DrawableVector[0].lock().get());

			auto& SpriteBounds = Sprite->getGlobalBounds();

			mBounds.height += SpriteBounds.height;
			mBounds.width += SpriteBounds.width;
			mBounds.left += SpriteBounds.left;
			mBounds.top += SpriteBounds.top;
		}

		return mBounds;
	}

	const sf::Vector2f& TTransformable::GetEntitySize() const
	{
		return sf::Vector2f(mBounds.width, mBounds.height);
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

/*
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
	}*/

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
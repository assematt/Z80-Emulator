#include "TTransformable.h"

namespace nne
{

	TTransformable::TTransformable() :
		mNeedRefresh(false)
	{
	}

	void TTransformable::Refresh()
	{
		if (mNeedRefresh)
			UpdateBounds();
	}

	void TTransformable::SetPosition(float x, float y)
	{
		mTransformable.setPosition(x, y);

		mNeedRefresh = true;
	}

	void TTransformable::SetRotation(float angle)
	{
		mTransformable.setRotation(angle);

		mNeedRefresh = true;
	}

	void TTransformable::SetScale(float factorX, float factorY)
	{
		mTransformable.setScale(factorX, factorY);

		mNeedRefresh = true;
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

	const sf::Vector2f& TTransformable::GetScale() const
	{
		return mTransformable.getScale();
	}

	const sf::Vector2f& TTransformable::GetOrigin() const
	{
		return mTransformable.getOrigin();
	}

	const sf::FloatRect& TTransformable::GetBounds()
	{
		UpdateBounds();

		return mBounds;
	}

	const sf::Vector2f& TTransformable::GetSize() const
	{
		auto& Drawables = *mParent->GetComponentAsPtr<TDrawableVector>();
		
		float MaxWidth = ComputeWidth(Drawables[0].GetVertexArray());
		float MaxHeight = ComputeHeigth(Drawables[0].GetVertexArray());

		for (std::size_t Index = 1; Index < Drawables.GetVectorSize(); ++Index)
		{
			const auto& CompWidth = ComputeWidth(Drawables[Index].GetVertexArray());
			const auto& CompHeight = ComputeHeigth(Drawables[Index].GetVertexArray());

			MaxWidth = MaxWidth < CompWidth ? CompWidth : MaxWidth;
			MaxHeight = MaxHeight < CompHeight ? CompHeight : MaxHeight;
		}

		return sf::Vector2f(MaxWidth, MaxHeight);
	}

	void TTransformable::Move(float offsetX, float offsetY)
	{
		mTransformable.move(offsetX, offsetY);

		mNeedRefresh = true;
	}

	void TTransformable::Rotate(float angle)
	{
		mTransformable.rotate(angle);

		mNeedRefresh = true;
	}

	void TTransformable::Scale(float factorX, float factorY)
	{
		mTransformable.scale(factorX, factorY);

		mNeedRefresh = true;
	}

	const sf::Transform& TTransformable::GetTransform() const
	{
		return mTransformable.getTransform();
	}

	const sf::Transform& TTransformable::GetInverseTransform() const
	{
		return mTransformable.getInverseTransform();
	}

	void TTransformable::UpdateBounds()
	{
		mBounds = sf::FloatRect(GetPosition(), GetSize());
	}

	const float TTransformable::ComputeWidth(const sf::VertexArray& Vertices) const
	{
		if (!Vertices.getVertexCount())
			return 0.f;

		float MaxValue = Vertices[0].position.x;

		for (auto Index = 1u; Index < Vertices.getVertexCount(); ++Index)
		{
			if (Vertices[Index].position.x > MaxValue)
			{
				MaxValue = Vertices[Index].position.x;
			}
		}

		return MaxValue;
	}

	const float TTransformable::ComputeHeigth(const sf::VertexArray& Vertices) const
	{
		if (!Vertices.getVertexCount())
			return 0.f;

		float MaxValue = Vertices[0].position.y;

		for (auto Index = 1u; Index < Vertices.getVertexCount(); ++Index)
		{
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

		mNeedRefresh = true;
	}

	void TTransformable::Move(const sf::Vector2f& offset)
	{
		mTransformable.move(offset);

		mNeedRefresh = true;
	}

	void TTransformable::SetOrigin(const sf::Vector2f& origin)
	{
		mTransformable.setOrigin(origin);

		mNeedRefresh = true;
	}

	void TTransformable::SetScale(const sf::Vector2f& factors)
	{
		mTransformable.setScale(factors);
	}

	void TTransformable::SetPosition(const sf::Vector2f& position)
	{
		mTransformable.setPosition(position);

		mNeedRefresh = true;
	}
}
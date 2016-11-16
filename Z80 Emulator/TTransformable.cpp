#include "TTransformable.h"

namespace nne
{

	TTransformable::TTransformable() :
		mNeedrefresh(false)
	{
	}

	void TTransformable::refresh()
{
		if (mNeedrefresh)
			updateBounds();
	}

	void TTransformable::setPosition(float x, float y)
	{
		mTransformable.setPosition(x, y);

		mNeedrefresh = true;
	}

	void TTransformable::setRotation(float angle)
	{
		mTransformable.setRotation(angle);

		mNeedrefresh = true;
	}

	void TTransformable::setScale(float factorX, float factorY)
	{
		mTransformable.setScale(factorX, factorY);

		mNeedrefresh = true;
	}

	void TTransformable::setOrigin(float x, float y)
	{
		mTransformable.setOrigin(x, y);
	}

	const sf::Vector2f& TTransformable::getPosition() const
	{
		return mTransformable.getPosition();
	}

	float TTransformable::getRotation() const
	{
		return mTransformable.getRotation();
	}

	const sf::Vector2f& TTransformable::getScale() const
	{
		return mTransformable.getScale();
	}

	const sf::Vector2f& TTransformable::getOrigin() const
	{
		return mTransformable.getOrigin();
	}

	const sf::FloatRect& TTransformable::getBounds()
	{
		updateBounds();

		return mBounds;
	}

	const sf::Vector2f& TTransformable::getSize() const
	{
		auto& drawables = *mParent->getComponentAsPtr<TdrawableVector>();
		
		float MaxWidth = computeWidth(drawables[0].getVertexArray());
		float MaxHeight = computeHeigth(drawables[0].getVertexArray());

		for (std::size_t Index = 1; Index < drawables.getVectorSize(); ++Index)
		{
			const auto& CompWidth = computeWidth(drawables[Index].getVertexArray());
			const auto& CompHeight = computeHeigth(drawables[Index].getVertexArray());

			MaxWidth = MaxWidth < CompWidth ? CompWidth : MaxWidth;
			MaxHeight = MaxHeight < CompHeight ? CompHeight : MaxHeight;
		}

		return sf::Vector2f(MaxWidth, MaxHeight);
	}

	void TTransformable::move(float offsetX, float offsetY)
	{
		mTransformable.move(offsetX, offsetY);

		mNeedrefresh = true;
	}

	void TTransformable::rotate(float angle)
	{
		mTransformable.rotate(angle);

		mNeedrefresh = true;
	}

	void TTransformable::scale(float factorX, float factorY)
	{
		mTransformable.scale(factorX, factorY);

		mNeedrefresh = true;
	}

	const sf::Transform& TTransformable::getTransform() const
	{
		return mTransformable.getTransform();
	}

	const sf::Transform& TTransformable::getInverseTransform() const
	{
		return mTransformable.getInverseTransform();
	}

	void TTransformable::updateBounds()
	{
		mBounds = sf::FloatRect(getPosition(), getSize());
	}

	const float TTransformable::computeWidth(const sf::VertexArray& Vertices) const
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

	const float TTransformable::computeHeigth(const sf::VertexArray& Vertices) const
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

	void TTransformable::scale(const sf::Vector2f& factor)
	{
		mTransformable.scale(factor);

		mNeedrefresh = true;
	}

	void TTransformable::move(const sf::Vector2f& offset)
	{
		mTransformable.move(offset);

		mNeedrefresh = true;
	}

	void TTransformable::setOrigin(const sf::Vector2f& origin)
	{
		mTransformable.setOrigin(origin);

		mNeedrefresh = true;
	}

	void TTransformable::setScale(const sf::Vector2f& factors)
	{
		mTransformable.setScale(factors);
	}

	void TTransformable::setPosition(const sf::Vector2f& position)
	{
		mTransformable.setPosition(position);

		mNeedrefresh = true;
	}
}
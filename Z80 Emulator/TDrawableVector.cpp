#include "TDrawableVector.h"

namespace nne
{

	void TDrawableVector::Update()
	{

	}

	void TDrawableVector::Refresh()
	{
		/// Remove dead entity
		for (std::size_t Index = 0; Index < mDrawablesVector.size(); ++Index)
		{
			if (mDrawablesVector[Index].IsExpired())
				mDrawablesVector.erase(mDrawablesVector.begin() + Index);
		}
	}

	void TDrawableVector::PushDrawableObject(const TRenderPair& Drawable)
	{
		mDrawablesVector.emplace_back(Drawable);
	}

	void TDrawableVector::Init()
	{

	}

	const std::size_t& TDrawableVector::GetVectorSize() const
	{
		return mDrawablesVector.size();
	}

	nne::TDrawableVector::Iterator& TDrawableVector::begin()
	{
		return mDrawablesVector.begin();
	}

	nne::TDrawableVector::Iterator& TDrawableVector::end()
	{
		return mDrawablesVector.end();
	}

	const nne::TDrawableVector::TRenderPair& TDrawableVector::operator[](const int Index) const
	{
		return mDrawablesVector[Index];
	}

	nne::TDrawableVector::TRenderPair& TDrawableVector::operator[](const int Index)
	{
		return mDrawablesVector[Index];
	}

	TDrawableVector::TRenderPair::TRenderPair(const std::shared_ptr<sf::VertexArray>& Vertices, const sf::Texture* Texture /*= nullptr*/) :
		mDrawable(Vertices),
		mTexture(Texture)
	{

	}

	const sf::VertexArray& TDrawableVector::TRenderPair::GetVertexArray() const
	{
		return *(mDrawable.lock());
	}

	const sf::Texture* TDrawableVector::TRenderPair::GetTexture() const
	{
		return mTexture;
	}

	bool TDrawableVector::TRenderPair::IsExpired()
	{
		return mDrawable.expired();
	}

}
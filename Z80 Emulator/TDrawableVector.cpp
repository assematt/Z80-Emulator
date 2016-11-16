#include "TdrawableVector.h"

namespace nne
{

	void TdrawableVector::update()
{

	}

	void TdrawableVector::refresh()
{
		/// Remove dead entity
		for (std::size_t Index = 0; Index < mdrawablesVector.size(); ++Index)
		{
			if (mdrawablesVector[Index].isExpired())
				mdrawablesVector.erase(mdrawablesVector.begin() + Index);
		}
	}

	void TdrawableVector::pushdrawableObject(const TRenderPair& drawable)
	{
		mdrawablesVector.emplace_back(drawable);
	}

	void TdrawableVector::init()
{

	}

	const std::size_t& TdrawableVector::getVectorSize() const
	{
		return mdrawablesVector.size();
	}

	nne::TdrawableVector::Iterator& TdrawableVector::begin()
	{
		return mdrawablesVector.begin();
	}

	nne::TdrawableVector::Iterator& TdrawableVector::end()
	{
		return mdrawablesVector.end();
	}

	const nne::TdrawableVector::TRenderPair& TdrawableVector::operator[](const int Index) const
	{
		return mdrawablesVector[Index];
	}

	nne::TdrawableVector::TRenderPair& TdrawableVector::operator[](const int Index)
	{
		return mdrawablesVector[Index];
	}

	TdrawableVector::TRenderPair::TRenderPair(const std::shared_ptr<sf::VertexArray>& Vertices, const sf::Texture* Texture /*= nullptr*/) :
		mdrawable(Vertices),
		mTexture(Texture)
	{

	}

	const sf::VertexArray& TdrawableVector::TRenderPair::getVertexArray() const
	{
		return *(mdrawable.lock());
	}

	const sf::Texture* TdrawableVector::TRenderPair::getTexture() const
	{
		return mTexture;
	}

	bool TdrawableVector::TRenderPair::isExpired()
	{
		return mdrawable.expired();
	}

}
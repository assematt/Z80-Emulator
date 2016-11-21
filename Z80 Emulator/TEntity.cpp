#include "TEntity.h"

namespace nne
{
	TEntity::TEntity() :
		mAlive(true),
		TComponentArray(this)
	{
	}
	
	const bool TEntity::isAlive() const
	{
		return mAlive;
	}
	
	void TEntity::kill()
	{
		mAlive = false;
	}

	void TEntity::update(const sf::Time& ElapsedTime)
{
		for (auto& Component : mComponents)
		{
			Component->update(ElapsedTime);
		}
	}

	void TEntity::init()
	{
	}

	void TEntity::refresh(const sf::Time& ElapsedTime)
{
		for (auto& Component : mComponents)
		{
			Component->refresh(ElapsedTime);
		}
	}

	const TEntity::TEntityID& TEntity::getEntityID() const
	{
		return mID;
	}
}
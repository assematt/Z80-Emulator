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

	void TEntity::update()
	{
		for (auto& Component : mComponents)
		{
			Component->update();
		}
	}

	void TEntity::init()
	{
	}

	void TEntity::refresh()
	{
		for (auto& Component : mComponents)
		{
			Component->refresh();
		}
	}

	const TEntity::TEntityID& TEntity::getEntityID() const
	{
		return mID;
	}
}
#include "TEntity.h"

namespace nne
{
	TEntity::TEntity() :
		mAlive(true),
		TComponentArray(this)
	{
	}
	
	const bool TEntity::IsAlive() const
	{
		return mAlive;
	}
	
	void TEntity::Kill()
	{
		mAlive = false;
	}

	void TEntity::Update()
	{
		for (auto& Component : mComponents)
		{
			Component->Update();
		}
	}

	void TEntity::Init()
	{
	}

	void TEntity::Refresh()
	{
	}
	
	void TEntity::OnCreate()
	{
		std::cout << "Entity created" << std::endl;
	}
	
	void TEntity::OnDestroy()
	{
		std::cout << "Entity destroyed" << std::endl;
	}
}
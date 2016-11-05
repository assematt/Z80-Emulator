#include "TManager.h"

namespace nne
{
	TManager::TManager() :
		mAliveElement(0),
		mNewElement(0),
		TComponentArray(this)
	{
	}

	TManager & TManager::GetInstance()
	{
		static TManager Instance;
		return Instance;
	}
	
	void TManager::Update(const sf::Time& ElapsedTime)
	{
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{
			mComponents[Counter]->Update();
		}
	}
	
	void TManager::Refresh(const sf::Time& ElapsedTime)
	{
		ComputeAliveEntities();

		// Call the function that sort the entity container
		SortEntityContainer();

	
		// Refresh the alive entities
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{
			mComponents[Counter]->Refresh();
		}
	}
	
	void TManager::Draw()
	{
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{			
			TGuiWindow::GetInstance().draw(*(dynamic_cast<TGraphicEntity*>(mComponents[Counter].get())));
		}
	}

	std::vector<TEntity::TEntityPtr>::iterator TManager::begin()
	{
		return mComponents.begin();
	}

	std::vector<TEntity::TEntityPtr>::iterator TManager::end()
	{
		return mComponents.end();
	}

	nne::TEntity::TEntityPtr& TManager::operator[](const int Index)
	{
		return mComponents[Index];
	}

	const nne::TEntity::TEntityPtr& TManager::operator[](const int Index) const
	{
		return mComponents[Index];
	}

	void TManager::ComputeAliveEntities()
	{
		mAliveElement = 0;

		for (auto& Entity : mComponents)
		{
			if (Entity->IsAlive())
			{
				++mAliveElement;
			}
		}
	}

	void TManager::SortEntityContainer()
	{
		std::sort(mComponents.begin(), mComponents.end(), [](const TEntity::TEntityPtr& Left, const TEntity::TEntityPtr& Right) {
			return (Left->IsAlive() && !Right->IsAlive());
		});
	}
	
}

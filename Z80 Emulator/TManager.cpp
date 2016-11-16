#include "TManager.h"

namespace nne
{
	TManager::TManager() :
		mAliveElement(0),
		mNewElement(0),
		TComponentArray(this)
	{
	}

	TManager & TManager::getInstance()
	{
		static TManager Instance;
		return Instance;
	}
	
	void TManager::update(const sf::Time& ElapsedTime)
	{
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{
			mComponents[Counter]->update();
		}
	}
	
	void TManager::refresh(const sf::Time& ElapsedTime)
	{
		computeAliveEntities();

		// Call the function that sort the entity container
		sortEntityContainer();

	
		// refresh the alive entities
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{
			mComponents[Counter]->refresh();
		}
	}
	
	void TManager::draw()
	{
		for (int Counter = 0; Counter < mAliveElement; ++Counter)
		{			
			TGuiWindow::getInstance().draw(*(dynamic_cast<TGraphicEntity*>(mComponents[Counter].get())));
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

	void TManager::computeAliveEntities()
	{
		mAliveElement = 0;

		for (auto& Entity : mComponents)
		{
			if (Entity->isAlive())
			{
				++mAliveElement;
			}
		}
	}

	void TManager::sortEntityContainer()
	{
		std::sort(mComponents.begin(), mComponents.end(), [](const TEntity::TEntityPtr& Left, const TEntity::TEntityPtr& Right) {
			return (Left->isAlive() && !Right->isAlive());
		});
	}
	
}

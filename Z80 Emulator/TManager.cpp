#include "TManager.h"

namespace nne
{
	
	TManager::TManager() :
		mAliveElement(0)
	{

	}

	void TManager::addEntity(TEntity::TEntityPtr& Entity, const std::string& EntityKey)
	{
		Entity->mParent = this;
		Entity->mID = static_cast<TEntity::TEntityID>(nne::idgenerator::GenerateByString::getUniqueID(EntityKey));

		mEntityVector.push_back({ Entity });
	}

	void TManager::removeEntity(const TEntity::TEntityID& IDToRemove)
	{
		// Get the position of the element to remove
		auto EntityPos = getEntityPos(IDToRemove);

		// If we can find the entity in the array return early
		if (EntityPos == mEntityVector.size())
			return;

		// Remove the element from the array by swapping it with the last valid element and popping back
		std::swap(mEntityVector[EntityPos], mEntityVector.back());
		mEntityVector.pop_back();
	}

	TEntity::TEntityPtr& TManager::getEntityByID(const TEntity::TEntityID& IDToSearch)
	{
		// Get the position of the element to remove
		auto EntityPos = getEntityPos(IDToSearch);

		// If we can find the entity in the array return early
		if (EntityPos == mEntityVector.size())
			return std::shared_ptr<TEntity>(nullptr);

		return mEntityVector[EntityPos];
	}

	TEntity::TEntityPtr& TManager::getEntityByKey(const std::string& EntityKey)
	{
		return getEntityByID(nne::idgenerator::GenerateByString::getUniqueID(EntityKey));
	}

	void TManager::draw(sf::RenderTarget& Target)
	{
		for (std::size_t Index = 0; Index < mAliveElement; ++Index)
			Target.draw(*mEntityVector[Index]->getComponentAsPtr<TDrawableComponent>());
	}

	void TManager::initEntities()
	{
		while (mAliveElement < mEntityVector.size())
			mEntityVector[mAliveElement++]->init();
	}

	void TManager::update(const sf::Time& ElapsedTime)
	{
		for (std::size_t Index = 0; Index < mAliveElement; ++Index)
			mEntityVector[Index]->update(ElapsedTime);
	}

	void TManager::refresh(const sf::Time& ElapsedTime)
	{
		auto VectorSize = mEntityVector.size();
		mAliveElement = VectorSize;

		for (std::size_t Index = 0; Index < VectorSize; ++Index)
		{
			mEntityVector[Index]->refresh(ElapsedTime);

			if (!mEntityVector[Index]->isAlive())
				--mAliveElement;
		}
	}

	const TEntity::TEntityPtr& TManager::operator[](const std::size_t& Index) const
	{
		return mEntityVector[Index];
	}

	TEntity::TEntityPtr& TManager::operator[](const std::size_t& Index)
	{
		return mEntityVector[Index];
	}

	std::size_t TManager::getEntityPos(const TEntity::TEntityID& IDToSearch)
	{
		auto VectorSize = mEntityVector.size();
		std::size_t EntityPos = 0;

		// Iterate trough the vector until we find what we are looking for
		while (mEntityVector[EntityPos]->getEntityID() != IDToSearch && ++EntityPos < VectorSize);

		return EntityPos;
	}

}

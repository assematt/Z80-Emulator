#include "TManager.h"

namespace nne
{
	
	TManager::TManager() :
		mAliveElement(0)
	{

	}

	void TManager::addEntity(TEntity::EntityPtr& Entity, const std::string& EntityKey, IScene* CurrentScene /*= nullptr*/)
	{
		Entity->mParent = this;
		Entity->mID = static_cast<TEntity::EntityID>(nne::idgenerator::GenerateByString::getUniqueID(EntityKey));
		Entity->mParentScene = CurrentScene;

		mEntityVector.push_back({ Entity });
	}

	void TManager::removeEntity(const TEntity::EntityID& IDToRemove)
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

	TEntity::EntityPtr& TManager::getEntityByID(const TEntity::EntityID& IDToSearch)
	{
		// Get the position of the element to remove
		auto EntityPos = getEntityPos(IDToSearch);

		// If we can find the entity in the array return early
		if (EntityPos == mEntityVector.size())
			return std::shared_ptr<TEntity>(nullptr);

		return mEntityVector[EntityPos];
	}

	TEntity::EntityPtr& TManager::getEntityByKey(const std::string& EntityKey)
	{
		return getEntityByID(nne::idgenerator::GenerateByString::getUniqueID(EntityKey));
	}

	void TManager::initEntities()
	{
		while (mAliveElement < mEntityVector.size())
			mEntityVector[mAliveElement++]->init();
	}

	void TManager::initLastEntity()
	{
		mEntityVector.back()->init();
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

	TManager::EntityIterator TManager::begin()
	{
		return mEntityVector.begin();
	}

	TManager::EntityIterator TManager::end()
	{
		return mEntityVector.end();
	}

	const TEntity::EntityPtr& TManager::operator[](const std::size_t& Index) const
	{
		return mEntityVector[Index];
	}

	TEntity::EntityPtr& TManager::operator[](const std::size_t& Index)
	{
		return mEntityVector[Index];
	}

	std::size_t TManager::getEntityPos(const TEntity::EntityID& IDToSearch)
	{
		auto VectorSize = mEntityVector.size();
		std::size_t EntityPos = 0;

		// Iterate trough the vector until we find what we are looking for
		while (mEntityVector[EntityPos]->getEntityID() != IDToSearch && ++EntityPos < VectorSize);

		return EntityPos;
	}

	void TManager::addSorted(TEntity::EntityPtr& Entity)
	{
// 		// If the manager is empty simply add the entity
// 		if (mEntityVector.empty())
// 		{
// 			mEntityVector.push_back({ Entity });
// 
// 			return;
// 		}
// 
// 		// Get the entity size
// 		auto VectorSize = mEntityVector.size();
// 		std::size_t InsertionPos = 0;
// 
// 		// Get the value to compare
// 		auto CompareValue = Entity->getComponentAsPtr<TDrawableComponent>()->getZIndex();
// 
// 		// Find the insert position
// 		while (CompareValue > mEntityVector[InsertionPos]->getComponentAsPtr<TDrawableComponent>()->getZIndex() && ++InsertionPos < VectorSize);
// 
// 		// Shift all the element right of the insertion position to the right
// 		// but first make sure we have enough space for one more element by adding an empty object
// 		mEntityVector.emplace_back();
// 
// 		for (std::size_t Index = VectorSize; Index > InsertionPos; --Index)
// 		{
// 			mEntityVector[Index] = std::move(mEntityVector[Index - 1]);
// 		}
// 
// 		// Put the element in the right place
// 		mEntityVector[InsertionPos] = std::move(Entity);
	}

}

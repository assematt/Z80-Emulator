#pragma once

#include "TEntity.h"
#include "TUtility.h"

#include <array>
#include <bitset>
#include <assert.h>
#include <memory>
#include <functional>

namespace nne
{
	template <class TType, class TParent, class TID>
	class TComponentArray
	{
	public:
		using TComponentPtr = std::shared_ptr<TType>;

		TComponentArray(TParent* ParentEntity) :
			mComponentsParent(ParentEntity)
		{
		}

		/// Function to add a component to the entity
		template <class T, typename... TArgs>
		void addComponent(TArgs&&... mArgs)
		{
			// Make sure we are not adding a duplicate component
			assert(!hasComponent<T>());

			// Compute an unique ID
			TID UniqueID = TUtility::getTypeID<TID, T>();

			// Creates a shared ptr that hold the component and set his parent entity and component id value
			auto NewComponentPtr = std::make_shared<T>(std::forward<TArgs>(mArgs)...);
			NewComponentPtr->mParent = mComponentsParent;
			NewComponentPtr->mID = UniqueID;

			//TComponentHandle Test = TComponentHandle::CreatesHandle<T>();

			// Put the position of the newly created shared_ptr in the mComponentsArray for easy access
			mComponentsArray[UniqueID] = mComponents.size();

			// Flag the component as alive
			mComponentsState[UniqueID] = true;

			// Put the component in the component array
			mComponents.push_back(std::move(NewComponentPtr));			
		}

		template <class T>
		void addComponent(std::shared_ptr<T>&& Move)
		{
			// Make sure we are not adding a duplicate component
			assert(!hasComponent<T>() && "A is not equal to B");

			// Put the position of the newly created shared_ptr in the mComponentsArray for easy access
			mComponentsArray[Move->mID] = mComponents.size();

			// Flag the component as alive
			mComponentsState[Move->mID] = true;

			mComponents.push_back(std::move(Move));
		}

		/// Function to remove a component by component type
		template <class T>
		inline void removeComponent()
		{
			removeComponent(TUtility::getTypeID<TID, T>());
		}

		/// Function to remove a component by component ID
		inline void removeComponent(TID ID)
		{
			// Delete the component and flag the component as dead
			mComponents.erase(mComponents.begin() + ID);
			mComponentsArray[ID] = 0;
			mComponentsState[ID] = false;
		}

		/// Function to get a component by component type as cast
		template <class T>
		inline T& getComponent() const
		{
			return *dynamic_cast<T*>(getComponent(TUtility::getTypeID<TID, T>()).get());
		}

		/// Function to get a component by component type as shared_ptr 
		template <class T>
		inline std::shared_ptr<T> getComponentAsPtr() const
		{
			return std::static_pointer_cast<T>(getComponent(TUtility::getTypeID<TID, T>()));
		}

		/// Function to get a component to the entity by component ID
		inline TComponentPtr getComponent(TID ID) const
		{
			// Make sure the component we are trying to get exist
			assert(hasComponent(ID) && "A is not equal to B");

			// Get the component from the array
			return mComponents[mComponentsArray[ID]];
		}

		/// Function to check if a component exist by component type
		template <class T>
		inline const bool hasComponent() const
		{
			return mComponentsState[TUtility::getTypeID<TID, T>()];
		}

		/// Function to check if a component exist by component ID
		inline const bool hasComponent(TID ID) const
		{
			return mComponentsState[ID];
		}

		/// Function that init all the components
		inline void initComponents()
		{
			for (auto& Component : mComponents)
			{
				Component->init();
			}
		}

		/// Function that init a single component by component type
		template <class T>
		inline void initComponent()
		{
			getComponent<T>().init();
		}

		/// Function that init a single component by component ID
		inline void initComponent(TID ID)
		{
			getComponent(ID)->init();
		}

	private:
		std::array<std::size_t, 32> mComponentsArray;
		std::bitset<32> mComponentsState;
		TParent* mComponentsParent;

	protected:
		std::vector<TComponentPtr> mComponents;
	};
}
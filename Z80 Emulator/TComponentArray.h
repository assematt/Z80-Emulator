#pragma once

#include "TEntity.h"
#include "TUtility.h"
#include "TComponentHandle.h"

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
		void AddComponent(TArgs&&... mArgs)
		{
			// Make sure we are not adding a duplicate component
			assert(!HasComponent<T>());

			// Compute an unique ID
			TID UniqueID = TUtility::GetTypeID<TID, T>();

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
		void AddComponent(std::shared_ptr<T>&& Move)
		{
			// Make sure we are not adding a duplicate component
			assert(!HasComponent<T>());

			// Put the position of the newly created shared_ptr in the mComponentsArray for easy access
			mComponentsArray[Move->mID] = mComponents.size();

			// Flag the component as alive
			mComponentsState[Move->mID] = true;

			mComponents.push_back(std::move(Move));
		}

		/// Function to remove a component by component type
		template <class T>
		inline void RemoveComponent()
		{
			RemoveComponent(TUtility::GetTypeID<TID, T>());
		}

		/// Function to remove a component by component ID
		inline void RemoveComponent(TID ID)
		{
			// Delete the component and flag the component as dead
			mComponents.erase(mComponents.begin() + ID);
			mComponentsArray[ID] = 0;
			mComponentsState[ID] = false;
		}

		/// Function to get a component by component type as cast
		template <class T>
		inline T& GetComponent() const
		{
			return *dynamic_cast<T*>(GetComponent(TUtility::GetTypeID<TID, T>()).get());
		}

		/// Function to get a component by component type as shared_ptr 
		template <class T>
		inline std::shared_ptr<T> GetComponentAsPtr() const
		{
			return std::static_pointer_cast<T>(GetComponent(TUtility::GetTypeID<TID, T>()));
		}

		/// Function to get a component to the entity by component ID
		inline TComponentPtr GetComponent(TID ID) const
		{
			// Make sure the component we are trying to get exist
			assert(HasComponent(ID));

			// Get the component from the array
			return mComponents[mComponentsArray[ID]];
		}

		/// Function to check if a component exist by component type
		template <class T>
		inline const bool HasComponent() const
		{
			return mComponentsState[TUtility::GetTypeID<TID, T>()];
		}

		/// Function to check if a component exist by component ID
		inline const bool HasComponent(TID ID) const
		{
			return mComponentsState[ID];
		}

		/// Function that init all the components
		inline void InitComponents()
		{
			for (auto& Component : mComponents)
			{
				Component->Init();
			}
		}

		/// Function that init a single component by component type
		template <class T>
		inline void InitComponent()
		{
			GetComponent<T>().Init();
		}

		/// Function that init a single component by component ID
		inline void InitComponent(TID ID)
		{
			GetComponent(ID)->Init();
		}

	private:
		std::array<std::size_t, 32> mComponentsArray;
		std::bitset<32> mComponentsState;
		TParent* mComponentsParent;

	protected:
		std::vector<TComponentPtr> mComponents;
	};
}
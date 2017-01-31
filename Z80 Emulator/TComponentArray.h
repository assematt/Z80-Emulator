#pragma once

#include "TEntity.h"
#include "TUtility.h"
#include "IDGenerator.h"

#include <array>
#include <bitset>
#include <assert.h>
#include <memory>
#include <functional>

namespace nne
{
	class TComponentArray
	{
	public:
		TComponentArray(TEntity* ParentEntity) :
			mComponentsParent(ParentEntity)
		{
		}

		/// Function to add a component to the entity
		template <class T, typename... TArgs>
		void addComponent(TArgs&&... mArgs);
		
		template <class T>
		void addComponent(T* Pointer);

		template <class T>
		void addComponent(std::unique_ptr<T>&& Move);

		template <class T, typename... TArgs>
		void replaceComponent(TArgs&&... mArgs);

		template <class T>
		void replaceComponent(T* Pointer);

		template <class T>
		void replaceComponent(std::unique_ptr<T>&& Move);

		/// Function to remove a component by component type
		template <class T>
		inline void removeComponent();

		/// Function to remove a component by component ID
		inline void removeComponent(TComponentID ID);

		/// Function to get a component by component type as cast
		template <class T>
		inline T& getComponent() const;

		/// Function to get a component by component type as shared_ptr 
		template <class T>
		inline T* getComponentAsPtr() const;

		/// Function to get a component to the entity by component ID
		inline IComponent* getComponent(TComponentID ID) const;

		/// Function to check if a component exist by component type
		template <class T>
		inline const bool hasComponent() const;

		/// Function to check if a component exist by component ID
		inline const bool hasComponent(TComponentID ID) const;

		/// Function that init all the components
		inline void initComponents();

		/// Function that init a single component by component type
		template <class T>
		inline void initComponent();

		/// Function that init a single component by component ID
		inline void initComponent(TComponentID ID);

	private:
		std::array<std::size_t, 32> mComponentsArray;
		std::bitset<32> mComponentsState;
		TEntity* mComponentsParent;

	protected:
		std::vector<std::unique_ptr<IComponent>> mComponents;
	};

	#include "TComponentArray.inl"
}
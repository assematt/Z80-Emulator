#pragma once

#include "IComponent.h"
#include "TComponentArray.h"
#include "TEventContainer.h"
#include <memory>
#include <iostream>


namespace TInternals
{
	class TManager;

	class TEntity : public TComponentArray<IComponent, TEntity, TComponentID>, public TEventContainer
	{
	public:
		using TEntityPtr = std::shared_ptr<TEntity>;
		using TEntityID = std::size_t;
	
		TEntity();
		virtual ~TEntity() = default;
	
		/// Helper function to make an entity
		template <typename... TArgs>
		static TEntityPtr MakeEntity(TArgs&&... mArgs)
		{
			return std::make_unique<TEntity>(std::forward<TArgs>(mArgs)...);
		}
	
		/// Function to check if a function in alive
		const bool IsAlive() const;
	
		/// Helper function to kill the entity
		void Kill();
	
		/// Update function
		void Update();

		/// Init function
		virtual void Init();
	
		/// Update function
		void Refresh();
	
		/// This function is called when the entity is created
		void OnCreate();
	
		/// This function is called when the entity is destroyed
		void OnDestroy();

		/// 
		virtual void MakeVirtual() = 0;
	private:
		bool mAlive;
		TManager* mParent;
		TEntityID mID;

		friend class TComponentArray<TEntity, TManager, TEntity::TEntityID>;
	};
}
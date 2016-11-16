#pragma once

#include "IComponent.h"
#include "TComponentArray.h"
#include "TEventContainer.h"
#include <memory>
#include <iostream>


namespace nne
{
	class TManager;
	
	class TEntity : public TComponentArray<IComponent, TEntity, TComponentID>//, public TEventContainer
	{
	public:
		using TEntityPtr = std::shared_ptr<TEntity>;
		using TEntityID = std::size_t;

		TEntity();
		virtual ~TEntity() = default;

		/// Helper function to make an entity
		template <typename... TArgs>
		static TEntityPtr makeEntity(TArgs&&... mArgs)
		{
			return std::make_unique<TEntity>(std::forward<TArgs>(mArgs)...);
		}

		/// Function to check if a function in alive
		const bool isAlive() const;

		/// Helper function to kill the entity
		void kill();

		/// update function
		virtual void update();

		/// update function
		virtual void refresh();

		/// Init function
		virtual void init();

		/// Get entity ID
		const TEntityID& getEntityID() const;

		/// 
		virtual void makeVirtual() = 0;
	private:
		bool mAlive;
		TManager* mParent;
		TEntityID mID;

		friend class TComponentArray<TEntity, TManager, TEntity::TEntityID>;
	};
}
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "IComponent.h"
#include "TComponentArray.h"
#include "TEventContainer.h"
#include "IDGenerator.h"


namespace nne
{
	class TManager;
	class TSceneManager;
	class IScene;
	
	class TEntity : public TComponentArray// <IComponent, TEntity, TComponentID>//, public TEventContainer
	{
	public:
		using EntityPtr = std::shared_ptr<TEntity>;
		using EntityID = std::size_t;

		TEntity();
		virtual ~TEntity() = default;

		/// Helper function to make an entity
		template <typename... TArgs>
		static EntityPtr makeEntity(TArgs&&... mArgs)
		{
			return std::make_unique<TEntity>(std::forward<TArgs>(mArgs)...);
		}

		/// Function to check if a function in alive
		const bool isAlive() const;

		/// Helper function to kill the entity
		void kill();

		/// update function
		virtual void update(const sf::Time& ElapsedTime);

		/// update function
		virtual void refresh(const sf::Time& ElapsedTime);

		/// Init function
		virtual void init();

		/// Get entity ID
		const EntityID& getEntityID() const;

		/// Get the entity manager
		TManager& getEntityManager();

		const IScene* getParentScene() const;
		
	private:
		bool			mAlive;
		EntityID		mID;
		TManager*		mParent;
		IScene*			mParentScene;

		friend class TManager;
	};
}
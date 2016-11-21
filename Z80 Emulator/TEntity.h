#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "IComponent.h"
#include "TComponentArray.h"
#include "TEventContainer.h"


namespace nne
{
	class TManager;

	namespace idgenerator
	{
		using GlobalID = std::size_t;

		struct GenerateByString
		{
			static GlobalID getUniqueID(const std::string& IDKey)
			{
				static std::map<std::string, GlobalID> mIDMap;
				static GlobalID mLastID;

				return mIDMap.count(IDKey) == 1 ? mIDMap[IDKey] : mIDMap[IDKey] = mLastID++;
			}
		};
	}
	
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
		virtual void update(const sf::Time& ElapsedTime);

		/// update function
		virtual void refresh(const sf::Time& ElapsedTime);

		/// Init function
		virtual void init();

		/// Get entity ID
		const TEntityID& getEntityID() const;
		
		/// 
		//virtual void makeVirtual() = 0;
	private:
		bool		mAlive;
		TEntityID	mID;
		TManager*	mParent;

		friend class TManager;
	};
}
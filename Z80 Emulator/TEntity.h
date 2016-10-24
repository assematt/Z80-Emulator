#pragma once

#include "IComponent.h"
#include "TComponentArray.h"
#include "TEventContainer.h"
#include <memory>
#include <iostream>


namespace TInternals
{
	class TEntity : public TComponentArray, public TEventContainer
	{
	public:
		using TEntityPtr = std::unique_ptr<TEntity>;
	
		TEntity();
	
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
	
		/// Update function
		void Refresh();
	
		/// This function is called when the entity is created
		void OnCreate();
	
		/// This function is called when the entity is destroyed
		void OnDestroy();
	private:
		bool mAlive;
	};
}
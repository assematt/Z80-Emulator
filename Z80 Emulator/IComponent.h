#pragma once

#include "TEventContainer.h"

namespace TInternals
{
	using TComponentID = unsigned int;
	
	inline TComponentID getUniqueComponentID() noexcept
	{
		static TComponentID lastID = 0u;
		return lastID++;
	}
	
	template <typename T>
	inline TComponentID getComponentTypeID() noexcept
	{
		static TComponentID typeID = getUniqueComponentID();
		return typeID;
	}
	
	class TEntity;
	
	class IComponent
	{
	public:
		virtual void Update() = 0;
	
		virtual void Init() = 0;
	
		virtual ~IComponent() {};

		const TComponentID GetComponentID() const
		{
			return mComponentID;
		}
	
	protected:
		TEntity* mParentEntity;
		TComponentID mComponentID;
	
		friend class TEntity;
		friend class TComponentArray;
	};
}

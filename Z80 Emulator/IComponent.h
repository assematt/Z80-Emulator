#pragma once

#include "TEventContainer.h"
#include "TUtility.h"

namespace nne
{
	using TComponentID = unsigned int;

	class TEntity;

	template <class TType, class TParent, class TID>
	class TComponentArray;

	class IComponent
	{
	public:
		virtual void Update() = 0;

		virtual void Refresh() = 0;

		virtual void Init() = 0;

		virtual ~IComponent();

		const TComponentID GetComponentID() const;

	protected:
		TEntity* mParent;
		TComponentID mID;

		friend class TEntity;
		friend class TComponentArray<IComponent, TEntity, TComponentID>;
	};
}

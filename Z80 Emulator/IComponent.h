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
		virtual void update() = 0;

		virtual void refresh() = 0;

		virtual void init() = 0;

		virtual ~IComponent();

		const TComponentID getComponentID() const;

	protected:
		TEntity* mParent;
		TComponentID mID;

		friend class TEntity;
		friend class TComponentArray<IComponent, TEntity, TComponentID>;
	};
}

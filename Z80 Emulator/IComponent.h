#pragma once

#include <SFML/System/Time.hpp>

#include "TUtility.h"

namespace nne
{
	using TComponentID = unsigned int;

	class TEntity;

	class TComponentArray;

	class IComponent
	{
	public:
		virtual void update(const sf::Time& ElapsedTime) = 0;

		virtual void refresh(const sf::Time& ElapsedTime) = 0;

		virtual void init() = 0;

		virtual ~IComponent();

		const TComponentID getComponentID() const;

		TEntity* getParent() const;

	protected:
		TEntity* mParent;
		TComponentID mID;

		friend class TEntity;
		friend class TComponentArray;// <IComponent, TEntity, TComponentID>;
	};
}

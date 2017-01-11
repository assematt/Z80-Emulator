#pragma once

#include "IComponent.h"
#include "TEntity.h"

namespace nne
{
	class TPowerComponent : public IComponent
	{
	public:

		enum class Type : sf::Uint8
		{
			POWER,
			GROUND
		};

		TPowerComponent(const Type& Mode = Type::GROUND);

		///
		virtual void update(const sf::Time& ElapsedTime) override;

		///
		virtual void refresh(const sf::Time& ElapsedTime) override;

		///
		virtual void init() override;

	private:

		/// Add a pin to connect this component to the rest
		void addConnectionPin();
		
	private:
		Type mPowerType;
	};
}

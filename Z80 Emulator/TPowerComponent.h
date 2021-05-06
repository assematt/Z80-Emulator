#pragma once

#include <SFML/Config.hpp>
#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include INCLUDE_ENTITY_CLASS

namespace nne
{
	class TPowerComponent : BASE_COMPONENT_CLASS
	{
	public:

		enum class Type : sf::Uint8
		{
			POWER,
			GROUND
		};

		TPowerComponent(const Type& Mode = Type::GROUND);

		///
		virtual void update(REFRESH_UPDATE_PARAMETER) override;

		///
		virtual void refresh(REFRESH_UPDATE_PARAMETER) override;

		///
		virtual void init() override;

		/// Get the type of power type
		const Type& getPowerType() const;

	private:

		/// Add a pin to connect this component to the rest
		void addConnectionPin();
		
	private:
		Type mPowerType;
	};
}

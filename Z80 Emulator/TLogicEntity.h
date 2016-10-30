#pragma once

#include <SFML/System/Time.hpp>

namespace nne
{
	struct TLogicEntity
	{
		/// Update function
		virtual void Update(const sf::Time& ElapsedTime) {}

		/// Update function
		virtual void Refresh(const sf::Time& ElapsedTime) {}
	};
}
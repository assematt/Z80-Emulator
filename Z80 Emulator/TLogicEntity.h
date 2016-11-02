#pragma once

#include <SFML/System/Time.hpp>

namespace nne
{
	class TLogicEntity
	{
	public:
		/// Update function
		virtual void Update(const sf::Time& ElapsedTime) = 0;

		/// Update function
		virtual void Refresh(const sf::Time& ElapsedTime) = 0;
	};
}
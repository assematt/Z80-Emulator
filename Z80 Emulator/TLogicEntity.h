#pragma once

#include <SFML/System/Time.hpp>

namespace nne
{
	class TLogicEntity
	{
	public:
		/// update function
		virtual void update(const sf::Time& ElapsedTime) = 0;

		/// update function
		virtual void refresh(const sf::Time& ElapsedTime) = 0;
	};
}
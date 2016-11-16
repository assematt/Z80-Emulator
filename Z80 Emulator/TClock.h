#pragma once

#include <SFML/System.hpp>

#include "TFrequency.h"


namespace nne
{
	class TClock
	{
	public:
	
		TClock(const TFrequency Frequency);

		bool wait();

		void restart();

		const sf::Time& getElapsedTime();

		const sf::Time& getDuration() const;

	private:
		TFrequency mFrequency;
		sf::Time mCurrentElapsedTime;
		sf::Clock mInternalClock;
	};
}
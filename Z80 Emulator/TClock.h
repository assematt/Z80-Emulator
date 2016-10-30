#pragma once

#include <SFML/System.hpp>

#include "TFrequency.h"


namespace nne
{
	class TClock
	{
	public:
	
		TClock(const TFrequency Frequency);

		bool Wait();

		void Restart();

		const sf::Time& GetElapsedTime();

		const sf::Time& GetDuration() const;

	private:
		TFrequency mFrequency;
		sf::Time mCurrentElapsedTime;
		sf::Clock mInternalClock;
	};
}
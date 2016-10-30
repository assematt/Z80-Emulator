#pragma once

#include <SFML/System.hpp>
#include <ratio>

namespace nne
{
	
	struct TFrequency
	{
		TFrequency();
		TFrequency(const sf::Time Period);
		TFrequency(const TFrequency& Frequency);

		friend bool operator< (const sf::Time& Time, const TFrequency& Frequency);
		friend bool operator> (const sf::Time& Time, const TFrequency& Frequency);

	private:

		friend TFrequency Hertz(float Value);
		friend TFrequency KiloHertz(float Value);
		friend TFrequency MegaHertz(float Value);

	private:
		sf::Time mPeriod;
	};

	TFrequency Hertz(float Value);
	TFrequency KiloHertz(float Value);
	TFrequency MegaHertz(float Value);
}
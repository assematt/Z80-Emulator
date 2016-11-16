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

		friend TFrequency hertz(float Value);
		friend TFrequency kiloHertz(float Value);
		friend TFrequency megaHertz(float Value);

	private:
		sf::Time mPeriod;
	};

	TFrequency hertz(float Value);
	TFrequency kiloHertz(float Value);
	TFrequency megaHertz(float Value);
}
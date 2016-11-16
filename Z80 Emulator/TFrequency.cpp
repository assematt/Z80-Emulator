#include "TFrequency.h"

namespace nne
{

	TFrequency::TFrequency(const sf::Time Period) :
		mPeriod(Period)
	{
	}

	TFrequency::TFrequency(const TFrequency& Frequency):
		mPeriod(Frequency.mPeriod)
	{
	}

	TFrequency::TFrequency()
	{
		mPeriod = sf::seconds(1);
	}

	TFrequency hertz(float Value)
	{
		return TFrequency(sf::seconds(1 / Value));
	}

	TFrequency kiloHertz(float Value)
	{
		return TFrequency(sf::seconds(1 / (Value * std::kilo::num)));
	}

	TFrequency megaHertz(float Value)
	{
		return TFrequency(sf::seconds(1 / (Value * std::mega::num)));
	}

	bool operator> (const sf::Time& Time, const TFrequency& Frequency)
	{
		return Time.asSeconds() > Frequency.mPeriod.asSeconds();
	}

	long double operator""_Hz(long double Value)
	{
		return Value;
	}

	bool operator< (const sf::Time& Time, const TFrequency& Frequency)
	{
		return Time.asSeconds() < Frequency.mPeriod.asSeconds();
	}
}
#include "TClock.h"

namespace nne
{
	TClock::TClock(const TFrequency Frequency /*= TInternals::Hertz(2.f)*/) :
		mFrequency(Frequency)
	{
		mInternalClock.restart();
	}

	bool TClock::wait()
	{
		while (getElapsedTime() < mFrequency);

		restart();

		return true;
	}

	void TClock::restart()
	{
		mInternalClock.restart();
	}

	const sf::Time& TClock::getElapsedTime()
	{
		return mCurrentElapsedTime = mInternalClock.getElapsedTime();
	}

	const sf::Time& TClock::getDuration() const
	{
		return mCurrentElapsedTime;
	}
}
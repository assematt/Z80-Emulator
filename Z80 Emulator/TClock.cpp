#include "TClock.h"

namespace TInternals
{
	TClock::TClock(const TFrequency Frequency /*= TInternals::Hertz(2.f)*/) :
		mFrequency(Frequency)
	{
		mInternalClock.restart();
	}

	bool TClock::Wait()
	{
		while (GetElapsedTime() < mFrequency);

		Restart();

		return true;
	}

	void TClock::Restart()
	{
		mInternalClock.restart();
	}

	const sf::Time& TClock::GetElapsedTime()
	{
		return mCurrentElapsedTime = mInternalClock.getElapsedTime();
	}

	const sf::Time& TClock::GetDuration() const
	{
		return mCurrentElapsedTime;
	}
}
#include "TPin.h"

namespace nne
{
	namespace tcomponents
	{

		TPin::TPin() :
			mPinMode(TMode::INPUT),
			mPinName(""),
			mPinStatus(TStatus::LOW),
			mPinNumber(0),
			mPinGroupID(0),
			mPinGroupNumber(0),
			mPinID(generateID())
		{
		}

		TPin::TPin(const TMode& PinMode, const TPinName& PinName, const TStatus& PinStatus /*= TStatus::LOW*/, const TPinNumber& PinNumber /*= 0*/, const TPinGroupID& PinGroupID /*= 0*/, const TPinNumber& PinGroupNumber/* = 0*/) :
			mPinMode(PinMode),
			mPinName(PinName),
			mPinStatus(PinStatus),
			mPinNumber(PinNumber == 0 ? ++mPinNumber : PinNumber),
			mPinGroupID(PinGroupID),
			mPinGroupNumber(PinGroupNumber),
			mPinID(generateID())
		{
		}

		bool TPin::operator==(TPin const& Right)
		{
			return mPinStatus == Right.mPinStatus;
		}

		bool TPin::operator!=(TPin const& Right)
		{
			return !(*this == Right);
		}

		TPin::operator TStatus()
		{
			return mPinStatus;
		}

		TPin::operator const TStatus() const
		{
			return mPinStatus;
		}

		TPin::TStatus TPin::getPinStatus()
		{
			return mPinStatus;
		}

		const TPin::TStatus TPin::getPinStatus() const
		{
			return mPinStatus;
		}

		const TPin::TPinID& TPin::getPinID()
		{
			return mPinID;
		}

		TPin::TPinID TPin::generateID()
		{
			static TPin::TPinID PinID = 0;

			return PinID++;
		}

		void TPin::changePinStatus(const TStatus& NewStatus, bool Propagate /*= false*/)
		{
			// update the pin status
			mPinStatus = NewStatus;

			// IF the propagate value is true update all the pin connection
			if (Propagate)
			{
				for (auto& Pin : mPinConnections)
				{
					Pin->changePinStatus(NewStatus, false);
				}
			}
		}

		nne::tcomponents::TPin::TStatus logicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left && Right);
		}

		nne::tcomponents::TPin::TStatus logicOr(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left || Right);
		}

		nne::tcomponents::TPin::TStatus logicNot(const TPin::TStatus& Pin)
		{
			return Pin == TPin::HIGH ? TPin::LOW : TPin::HIGH;
		}

		nne::tcomponents::TPin::TStatus logicNand(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return logicNot(logicAnd(Left, Right));
		}

		nne::tcomponents::TPin::TStatus logicNor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return logicNot(logicOr(Left, Right));
		}

		nne::tcomponents::TPin::TStatus logicXor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return logicAnd(logicOr(Left, Right), logicNand(Left, Right));
			/*
			
			A | B | C	A | B | C	A | B | C
			---------	---------	---------	
			0 | 0 | 0	0 | 0 | 1	0 | 0 | 0
			0 | 1 | 1	0 | 1 | 1	0 | 1 | 1
			1 | 0 | 1	1 | 0 | 1	1 | 0 | 1
			1 | 1 | 1	1 | 1 | 0	1 | 1 | 0
			
			*/
		}

		nne::tcomponents::TPin::TStatus logicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return logicNot(logicXor(Left, Right));
		}

	}
}
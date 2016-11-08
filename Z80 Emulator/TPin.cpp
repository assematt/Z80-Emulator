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
			mPinID(GenerateID())
		{
		}

		TPin::TPin(const TMode& PinMode, const TPinName& PinName, const TStatus& PinStatus /*= TStatus::LOW*/, const TPinNumber& PinNumber /*= 0*/, const TPinGroupID& PinGroupID /*= 0*/, const TPinNumber& PinGroupNumber/* = 0*/) :
			mPinMode(PinMode),
			mPinName(PinName),
			mPinStatus(PinStatus),
			mPinNumber(PinNumber == 0 ? ++mPinNumber : PinNumber),
			mPinGroupID(PinGroupID),
			mPinGroupNumber(PinGroupNumber),
			mPinID(GenerateID())
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

		TPin::TStatus TPin::GetPinStatus()
		{
			return mPinStatus;
		}

		const TPin::TStatus TPin::GetPinStatus() const
		{
			return mPinStatus;
		}

		const TPin::TPinID& TPin::GetPinID()
		{
			return mPinID;
		}

		TPin::TPinID TPin::GenerateID()
		{
			static TPin::TPinID PinID = 0;

			return PinID++;
		}

		void TPin::ChangePinStatus(const TStatus& NewStatus, bool Propagate /*= false*/)
		{
			// Update the pin status
			mPinStatus = NewStatus;

			// IF the propagate value is true update all the pin connection
			if (Propagate)
			{
				for (auto& Pin : mPinConnections)
				{
					Pin->ChangePinStatus(NewStatus, false);
				}
			}
		}

		nne::tcomponents::TPin::TStatus LogicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left && Right);
		}

		nne::tcomponents::TPin::TStatus LogicOr(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left || Right);
		}

		nne::tcomponents::TPin::TStatus LogicNot(const TPin::TStatus& Pin)
		{
			return Pin == TPin::HIGH ? TPin::LOW : TPin::HIGH;
		}

		nne::tcomponents::TPin::TStatus LogicNand(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return LogicNot(LogicAnd(Left, Right));
		}

		nne::tcomponents::TPin::TStatus LogicNor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return LogicNot(LogicOr(Left, Right));
		}

		nne::tcomponents::TPin::TStatus LogicXor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return LogicAnd(LogicOr(Left, Right), LogicNand(Left, Right));
			/*
			
			A | B | C	A | B | C	A | B | C
			---------	---------	---------	
			0 | 0 | 0	0 | 0 | 1	0 | 0 | 0
			0 | 1 | 1	0 | 1 | 1	0 | 1 | 1
			1 | 0 | 1	1 | 0 | 1	1 | 0 | 1
			1 | 1 | 1	1 | 1 | 0	1 | 1 | 0
			
			*/
		}

		nne::tcomponents::TPin::TStatus LogicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return LogicNot(LogicXor(Left, Right));
		}

	}
}
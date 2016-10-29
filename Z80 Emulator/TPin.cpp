#include "TPin.h"

namespace TGame
{
	namespace TComponents
	{

		TPin::TPin() :
			mPinMode(TMode::INPUT),
			mPinStatus(TStatus::LOW),
			mPinNumber(0),
			mPinGroupID(0),
			mPinGroupNumber(0),
			mPinID(GenerateID())
		{
		}

		TPin::TPin(const TMode& PinMode, const TStatus& PinStatus /*= TStatus::LOW*/, const TPinNumber& PinNumber /*= 0*/, const TPinGroupID& PinGroupID /*= 0*/, const TPinNumber& PinGroupNumber/* = 0*/) :
			mPinMode(PinMode),
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

		TGame::TComponents::TPin::TStatus LogicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left && Right);
		}

		TGame::TComponents::TPin::TStatus LogicOr(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left || Right);
		}

		TGame::TComponents::TPin::TStatus LogicNot(const TPin::TStatus& Pin)
		{
			return Pin == TPin::HIGH ? TPin::LOW : TPin::HIGH;
		}

		TGame::TComponents::TPin::TStatus LogicNand(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return LogicNot(LogicAnd(Left, Right));
		}

		TGame::TComponents::TPin::TStatus LogicNor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return LogicNot(LogicOr(Left, Right));
		}

		TGame::TComponents::TPin::TStatus LogicXor(const TPin::TStatus& Left, const TPin::TStatus& Right)
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

		TGame::TComponents::TPin::TStatus LogicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return LogicNot(LogicXor(Left, Right));
		}

	}
}
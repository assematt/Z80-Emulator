#include "TPin.h"

#include "TEntity.h"
#include "TPinComponent.h"

namespace nne
{
	namespace tcomponents
	{

		std::vector<TPin*> TPin::mPinVectors;

		TPin& TPin::NotFound = TPin(TMode::INPUT, "NOT_FOUND", tcomponents::TPin::TStatus::LOW, 0, 0, 0);

		TPin::TPin() :
			mPinMode(TMode::INPUT),
			mPinName(""),
			mPinStatus(TStatus::LOW),
			mPinNumber(0),
			mPinGroupID(0),
			mPinGroupNumber(0),
			mPinID(generateID()),
			mParentName("")
		{
			mPinVectors.push_back(this);
		}

		TPin::TPin(const TMode& PinMode, const TPinName& PinName, const TStatus& PinStatus /*= TStatus::LOW*/, const TPinNumber& PinNumber /*= 0*/, const TPinGroupID& PinGroupID /*= 0*/, const TPinNumber& PinGroupNumber/* = 0*/) :
			mPinMode(PinMode),
			mPinName(PinName),
			mPinStatus(PinStatus),
			mPinNumber(PinNumber == 0 ? ++mPinNumber : PinNumber),
			mPinGroupID(PinGroupID),
			mPinGroupNumber(PinGroupNumber),
			mPinID(generateID()),
			mParentName("")
		{
			mPinVectors.push_back(this);
		}

		TPin::TPin(const TPin& Copy) :
			mPinMode(Copy.mPinMode),
			mPinName(Copy.mPinName),
			mPinStatus(Copy.mPinStatus),
			mPinNumber(Copy.mPinNumber),
			mPinGroupID(Copy.mPinGroupID),
			mPinGroupNumber(Copy.mPinGroupNumber),
			mPinID(generateID()),
			mParentName(Copy.mParentName)
		{
			mPinVectors.push_back(this);
		}

		TPin::TPin(TPin&& Move) :
			mPinMode(Move.mPinMode),
			mPinName(Move.mPinName),
			mPinStatus(Move.mPinStatus),
			mPinNumber(Move.mPinNumber),
			mPinGroupID(Move.mPinGroupID),
			mPinGroupNumber(Move.mPinGroupNumber),
			mPinID(generateID()),
			mParentName(Move.mParentName)
		{
			mPinID = Move.mPinID;

			auto PinDoDelete = std::find(mPinVectors.begin(), mPinVectors.end(), this);

			if (PinDoDelete != mPinVectors.end())
				mPinVectors.erase(PinDoDelete);

			mPinVectors.push_back(this);
		}

		TPin::~TPin()
		{
			auto PinDoDelete = std::find(mPinVectors.begin(), mPinVectors.end(), this);

			if (PinDoDelete != mPinVectors.end())
				mPinVectors.erase(PinDoDelete);
		}

		bool TPin::operator==(const TPin& Right)
		{
			return mPinName == Right.mPinName && mParentName == Right.mParentName;
		}

		bool TPin::operator!=(const TPin& Right)
		{
			return !(*this == Right);
		}

		bool TPin::operator==(const TStatus& Right)
		{
			return mPinStatus == Right;
		}

		bool TPin::operator!=(const TStatus& Right)
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

		void TPin::addConnections(TPin& RightPin)
		{
			// Add the left pin to the right pin connections
			RightPin.mPinConnections.push_back(this);

			// Add the right pin to the left pin connections
			this->mPinConnections.push_back(&RightPin);
		}

		bool TPin::hasConnections() const
		{
			return static_cast<bool>(mPinConnections.size());
		}

		const TPin::TPinConnections& TPin::getPinConnections() const
		{
			return mPinConnections;
		}

		bool TPin::isValid()
		{
			return mPinName != "NOT_FOUND";
		}

		TPin& TPin::getPinByID(const TPinID& ID)
		{
			for (auto Pin : mPinVectors)
			{
				if (Pin->mPinID == ID)
					return *Pin;
			}

			return NotFound;
		}

		TPin& TPin::getPinByName(const std::string& PinName, const std::string& ParentEntity)
		{
			for (auto Pin : mPinVectors)
			{
				if (Pin->mPinName == PinName && Pin->mParentName == ParentEntity)
					return *Pin;
			}

			return NotFound;
		}

		const std::vector<TPin*> TPin::getGlobalPinVector()
		{
			return mPinVectors;
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

		void TPin::setPinParent(const std::string& ParentName)
		{
			mParentName = ParentName;
		}

		const std::string& TPin::getPinParent() const
		{
			return mParentName;
		}

		TPin::TStatus logicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left && Right);
		}

		TPin::TStatus logicOr(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return static_cast<TPin::TStatus>(Left || Right);
		}

		TPin::TStatus logicNot(const TPin::TStatus& Pin)
		{
			return Pin == TPin::HIGH ? TPin::LOW : TPin::HIGH;
		}

		TPin::TStatus logicNand(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return logicNot(logicAnd(Left, Right));
		}

		TPin::TStatus logicNor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return logicNot(logicOr(Left, Right));
		}

		TPin::TStatus logicXor(const TPin::TStatus& Left, const TPin::TStatus& Right)
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

		TPin::TStatus logicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right)
		{
			return logicNot(logicXor(Left, Right));
		}

	}
}
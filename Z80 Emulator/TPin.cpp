#include "TPin.h"

#include INCLUDE_ENTITY_CLASS
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
			return mPinID == Right.mPinID;
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

		TPin& TPin::operator=(const TPin& Right)
		{
			mPinMode = Right.mPinMode;
			mPinName = Right.mPinName;
			mPinStatus = Right.mPinStatus;
			mPinNumber = Right.mPinNumber;
			mPinGroupID = Right.mPinGroupID;
			mPinGroupNumber = Right.mPinGroupNumber;
			mPinID = Right.mPinID;
			mParentName = Right.mParentName;

			mPinVectors.push_back(this);

			return *this;
		}

		TPin& TPin::operator=(TPin&& Right)
		{
			mPinMode = Right.mPinMode;
			mPinName = Right.mPinName;
			mPinStatus = Right.mPinStatus;
			mPinNumber = Right.mPinNumber;
			mPinGroupID = Right.mPinGroupID;
			mPinGroupNumber = Right.mPinGroupNumber;
			mPinID = generateID();
			mParentName = Right.mParentName;

			auto PinDoDelete = std::find(mPinVectors.begin(), mPinVectors.end(), this);

			if (PinDoDelete != mPinVectors.end())
				mPinVectors.erase(PinDoDelete);

			mPinVectors.push_back(this);

			return *this;
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

		const TPin::TPinID& TPin::getPinID() const
		{
			return mPinID;
		}

		void TPin::addConnections(TPin& RightPin)
		{
			// Add the left pin to the right pin connections
			RightPin.mPinConnections.insert(this);

			// Add the right pin to the left pin connections
			this->mPinConnections.insert(&RightPin);

		}

		bool TPin::hasConnections() const
		{
			return mPinConnections.empty() ? false : true;
		}

		void TPin::removeConnection(TPin& RightPin)
		{			
			// Remove the left pin from the right pin connections
			RightPin.mPinConnections.erase(this);

			// Remove the right pin from the left pin connections
			this->mPinConnections.erase(&RightPin);
		}

		void TPin::detachPin()
		{

			// Remove this wire from his connection
			std::for_each(mPinConnections.begin(), mPinConnections.end(), [&](TPin* Pin) {

				Pin->mPinConnections.erase(this);

				//TPinComponentUtility::detachPins(*Pin, *this);
			});

			const bool Flag = true;
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

		//////////////////////////////////////////////////////////////////////////

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

		//////////////////////////////////////////////////////////////////////////

		
	}

	//////////////////////////////////////////////////////////////////////////
	void TPinComponentUtility::connectPins(tcomponents::TPin& LeftPin, tcomponents::TPin& RightPin)
	{
		if (LeftPin == RightPin)
			return;

		// Create the connection only if we don't have already connected the pin
		LeftPin.addConnections(RightPin);

		// Update the status of the connected PINs based on their type
		updatePinStatus(LeftPin, RightPin);
	}

	void TPinComponentUtility::connectPins(tcomponents::TPin& LeftPin, std::initializer_list<tcomponents::TPin>& RightPins)
	{
		for (auto Pin : RightPins)
			TPinComponentUtility::connectPins(LeftPin, Pin);
	}

	void TPinComponentUtility::connectPins(const TPinBus& LeftBus, const TPinBus& RightBus)
	{
		//
		for (TPinBus::first_type LeftPin = LeftBus.first, RightPin = RightBus.first; LeftPin != LeftBus.second; ++LeftPin, ++RightPin)
			connectPins(*LeftPin, *RightPin);
	}
	//////////////////////////////////////////////////////////////////////////

	void TPinComponentUtility::updatePinStatus(TPin& LeftPin, TPin& RightPin)
	{
		switch (LeftPin.mPinMode)
		{
			// If the PIN is a CLOCK type
			case tcomponents::TPin::TMode::CLOCK:
			{
			} break;

			// If the PIN is just an INPUT type
			case tcomponents::TPin::TMode::INPUT:
			{
				// If the other PIN is of an OUTPUT or POWER type applies his status to this PIN
				if ((RightPin.mPinMode == tcomponents::TPin::TMode::POWER) || (RightPin.mPinMode == tcomponents::TPin::TMode::OUTPUT))
					LeftPin.changePinStatus(RightPin.getPinStatus(), false);
			} break;

			// If the PIN is both an INPUT and an OUTPUT type
			case tcomponents::TPin::TMode::INPUT_OUTPUT:
			{

			} break;

			// If the PIN is just an INPUT type
			case tcomponents::TPin::TMode::OUTPUT:
			{
				// If the other pin it's an input change his status to match this one
				if (RightPin.mPinMode == tcomponents::TPin::TMode::INPUT)
					LeftPin.changePinStatus(RightPin.getPinStatus(), false);
			} break;

			// If the PIN is just an POWER type
			case tcomponents::TPin::TMode::POWER:
			{
				// If the PIN is a power type then applies it's value to the other PIN no matter what
				RightPin.changePinStatus(LeftPin.getPinStatus(), false);
			} break;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TPinComponentUtility::detachPins(tcomponents::TPin& LeftPin, tcomponents::TPin& RightPin)
	{
		LeftPin.removeConnection(RightPin);
	}

	void TPinComponentUtility::detachPins(tcomponents::TPin& LeftPin, std::initializer_list<tcomponents::TPin>& RightPins)
	{
		for (auto Pin : RightPins)
			TPinComponentUtility::detachPins(LeftPin, Pin);
	}

	void TPinComponentUtility::detachPins(const TPinBus& LeftBus, const TPinBus& RightBus)
	{
		for (TPinBus::first_type LeftPin = LeftBus.first, RightPin = RightBus.first; LeftPin != LeftBus.second; ++LeftPin, ++RightPin)
			detachPins(*LeftPin, *RightPin);
	}
	//////////////////////////////////////////////////////////////////////////

}
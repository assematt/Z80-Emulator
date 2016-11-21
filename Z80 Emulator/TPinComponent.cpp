#include "TPinComponent.h"

namespace nne
{
	namespace tcomponents
	{

		TPinComponent::TPinComponent(const std::initializer_list<TPin>& PinList, std::size_t PinCount)
		{
			setupPins(PinList, PinCount);
		}

		void TPinComponent::setupPins(const std::initializer_list<TPin>& PinList, std::size_t PinCount)
		{
			mPins.resize(PinCount);

			mPins = std::move(PinList);
		}

		TPin& TPinComponent::operator[](const TPin::TPinNumber PinToSelect)
		{
			return mPins[PinToSelect];
		}

		const TPin& TPinComponent::operator[](const TPin::TPinNumber PinToSelect) const
		{
			return mPins[PinToSelect];
		}

		void TPinComponentUtility::connectPins(TPin& LeftPin, TPin& RightPin)
		{
			RightPin.mPinConnections.push_back(&LeftPin);

			LeftPin.mPinConnections.push_back(&RightPin);
		}

		void TPinComponentUtility::connectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins)
		{
			for (auto Pin : RightPins)
			{
				Pin.mPinConnections.push_back(&LeftPin);

				LeftPin.mPinConnections.push_back(&Pin);
			}
		}
		
		void TPinComponentUtility::connectPins(const TPinBus& LeftBus, const TPinBus& RightBus)
		{
			// 
			for (TPinBus::first_type LeftPin = LeftBus.first, RightPin = RightBus.first; LeftPin != LeftBus.second; ++LeftPin, ++RightPin)
			{
				RightPin->mPinConnections.push_back(&(*LeftPin));
				LeftPin->mPinConnections.push_back(&(*RightPin));
			}
		}

		void TPinComponentUtility::detachPins(TPin& LeftPin, TPin& RightPin)
		{

		}

		void TPinComponentUtility::detachPins(const TPinBus& LeftBus, const TPinBus& RightBus)
		{

		}

		void TPinComponentUtility::detachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins)
		{

		}

		TPinBus TPinComponent::getPinBus(const TPin::TPinGroupID BusID, const TPinBusIndex BusBegin /*= 0*/, const TPinBusIndex BusEnd /*= 0*/)
		{
			// store the return value
			TPinBus ReturnValue(mPins.end(), mPins.end());

			// Move the index to the first occurance of the right GroupID starting from the beginning
			std::size_t Index;
			for (Index = 0; Index < mPins.size() && mPins[Index].mPinGroupID != BusID; ++Index);
			ReturnValue.first = mPins.begin() + Index;

			// Move the index to the first occurance of the right GroupID starting from the end
			for (Index = mPins.size() - 1; Index > 0 && mPins[Index].mPinGroupID != BusID; --Index);
			ReturnValue.second = mPins.begin() + Index + 1;

			if (BusBegin == BusEnd)
			{
				return ReturnValue;
			}

			return TPinBus(ReturnValue.first + BusBegin, ReturnValue.first + BusEnd + 1);
		}

		TPinList& TPinComponent::getPinList()
		{
			return mPins;
		}

		const TPinList& TPinComponent::getPinList() const
		{
			return mPins;
		}

		TPin& TPinComponent::getPin(TPin::TPinNumber PinToSelect)
		{
			assert((PinToSelect < mPins.size()) && "Pin out of bound");

			// TODO: insert return statement here
			for (auto& Pin : mPins)
			{
				if (Pin.mPinNumber == PinToSelect)
					return Pin;
			}

			return mPins[PinToSelect];
		}

		const TPin& TPinComponent::getPin(TPin::TPinNumber PinToSelect) const
		{
			// TODO: insert return statement here
			return mPins[PinToSelect];
		}

		void TPinComponent::init()
{

		}

		void TPinComponent::update(const sf::Time& ElapsedTime)
		{
			
		}

		

	}
}
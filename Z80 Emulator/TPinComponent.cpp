#include "TPinComponent.h"

namespace TGame
{
	namespace TComponents
	{

		TPinComponent::TPinComponent(const std::initializer_list<TPin>& PinList, std::size_t PinCount)
		{
			SetupPins(PinList, PinCount);
		}

		void TPinComponent::SetupPins(const std::initializer_list<TPin>& PinList, std::size_t PinCount)
		{
			mPins.resize(PinCount);

			mPins = std::move(PinList);
		}

		void TPinComponentUtility::ConnectPins(TPin& LeftPin, TPin& RightPin)
		{
			RightPin.mPinConnections.push_back(&LeftPin);

			LeftPin.mPinConnections.push_back(&RightPin);
		}

		void TPinComponentUtility::ConnectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins)
		{
			for (auto Pin : RightPins)
			{
				Pin.mPinConnections.push_back(&LeftPin);

				LeftPin.mPinConnections.push_back(&Pin);
			}
		}
		
		void TPinComponentUtility::ConnectPins(const TPinBus& LeftBus, const TPinBus& RightBus)
		{
			// 
			for (TPinBus::first_type LeftPin = LeftBus.first, RightPin = RightBus.first; LeftPin != LeftBus.second; ++LeftPin, ++RightPin)
			{
				RightPin->mPinConnections.push_back(&(*LeftPin));
				LeftPin->mPinConnections.push_back(&(*RightPin));
			}
		}

		void TPinComponentUtility::DetachPins(TPin& LeftPin, TPin& RightPin)
		{

		}

		void TPinComponentUtility::DetachPins(const TPinBus& LeftBus, const TPinBus& RightBus)
		{

		}

		void TPinComponentUtility::DetachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins)
		{

		}


		TGame::TComponents::TPinBus TPinComponent::GetPinBus(const TPin::TPinGroupID BusID, const TPinBusIndex BusBegin /*= 0*/, const TPinBusIndex BusEnd /*= 0*/)
		{
			// store the return value
			TPinBus ReturnValue(mPins.end(), mPins.end());

			// Move the index to the first occurance of the right GroupID starting from the beginning
			std::size_t Index;
			for (Index = 0; Index < mPins.size() && mPins[Index].mPinGroupID != BusID; ++Index);
			ReturnValue.first = mPins.begin() + Index;

			// Move the index to the first occurance of the right GroupID starting from the end
			for (Index = mPins.size() - 1; Index > 0 && mPins[Index].mPinGroupID != BusID; --Index);
			ReturnValue.second = mPins.end() - Index;

			if (BusBegin == BusEnd)
			{
				return ReturnValue;
			}

			return TPinBus(ReturnValue.first + BusBegin, ReturnValue.first + BusEnd);
		}

		TGame::TComponents::TPinList& TPinComponent::GetPinList()
		{
			return mPins;
		}

		const TGame::TComponents::TPinList& TPinComponent::GetPinList() const
		{
			return mPins;
		}

		TU8BitValue TPinComponent::PinToTU8BitValue(TPin::TPinGroupID PinGroup /*= 0*/)
		{
			TU8BitValue Temp = 0;

			// Get the value of all the bit of the same ID
			for (std::size_t Index = 0, Bit = 0; Index < mPins.size() && Bit < 8; ++Index)
			{
				if (mPins[Index].mPinGroupID == PinGroup)
				{
					Temp |= mPins[Index].GetPinStatus() << Bit++;
				}
			}

			return Temp;
		}

		TU16BitValue TPinComponent::PinToTU16BitValue(TPin::TPinGroupID PinGroup /*= 0*/)
		{
			TU16BitValue Temp = 0;

			// Get the value of all the bit of the same ID
			for (std::size_t Index = 0, Bit = 0; Index < mPins.size() && Bit < 16; ++Index)
			{
				if (mPins[Index].mPinGroupID == PinGroup)
				{
					Temp |= mPins[Index].GetPinStatus() << Bit++;
				}
			}

			return Temp;
		}

		void TPinComponent::TU8BitValueToPins(const TU8BitValue& Value, TPin::TPinGroupID PinGroup /*= 0*/)
		{
			TU8BitValue Temp = 0;

			// Get the value of all the bit of the same ID
			for (std::size_t Index = 0, Bit = 0; Index < mPins.size() && Bit < 8; ++Index)
			{
				if (mPins[Index].mPinGroupID == PinGroup)
				{
					mPins[Index] = static_cast<TComponents::TPin::TStatus>(TInternals::TUtility::GetBit(Value, Bit++));
				}
			}
		}

		void TPinComponent::TU16BitValueToPins(const TU16BitValue& Value, TPin::TPinGroupID PinGroup /*= 0*/)
		{
			TU16BitValue Temp = 0;

			// Get the value of all the bit of the same ID
			for (std::size_t Index = 0, Bit = 0; Index < mPins.size() && Bit < 16; ++Index)
			{
				if (mPins[Index].mPinGroupID == PinGroup)
				{
					mPins[Index] = static_cast<TComponents::TPin::TStatus>(TInternals::TUtility::GetBit(Value, Bit++));
				}
			}
		}

		TPin & TPinComponent::GetPin(TPin::TPinNumber PinToSelect)
		{
			// TODO: insert return statement here
			return mPins[PinToSelect];
		}

		const TPin & TPinComponent::GetPin(TPin::TPinNumber PinToSelect) const
		{
			// TODO: insert return statement here
			return mPins[PinToSelect];
		}

		void TPinComponent::Init()
		{

		}

		void TPinComponent::Update()
		{
			
		}

		

	}
}
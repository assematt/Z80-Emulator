#pragma once

#include <assert.h>
#include <vector>
#include <memory>
#include <utility>
#include <initializer_list>

#include "IComponent.h"
#include "TUtility.h"
#include "TPin.h"
#include "TValues.h"

namespace TGame
{
	namespace TComponents
	{
		using TPinBusIndex = std::size_t;
		using TPinList = std::vector<TPin>;
		//using TPinList = std::map<TPin::TPinNumber, TPin>;
		using TPinBus = std::pair<TPinList::iterator, TPinList::iterator>;

		// Connect a single Pin to another single pin or multiple pin
		namespace TPinComponentUtility
		{
			void ConnectPins(TPin& LeftPin, TPin& RightPin);
			void ConnectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			void ConnectPins(const TPinBus& LeftBus, const TPinBus& RightBus);

			void DetachPins(TPin& LeftPin, TPin& RightPin);
			void DetachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			void DetachPins(const TPinBus& LeftBus, const TPinBus& RightBus);
		}

		struct TPinComponent : TInternals::IComponent
		{
		public:

			TPinComponent() = default;

			TPinComponent(const std::initializer_list<TPin>& PinList, std::size_t PinCount);

			/// Setup the pins configuration
			void SetupPins(const std::initializer_list<TPin>& PinList, std::size_t PinCount);

			/// Subscript operator to get a pin
			TPin& operator[] (const TPin::TPinNumber PinToSelect);
			const TPin& operator[] (const TPin::TPinNumber PinToSelect) const;
			
			/// Get a pin
			TPin& GetPin(const TPin::TPinNumber PinToSelect);
			const TPin& GetPin(const TPin::TPinNumber PinToSelect) const;

			/// Get bus
			TPinBus GetPinBus(const TPin::TPinGroupID BusID, const TPinBusIndex BusBegin = 0, const TPinBusIndex BusEnd = 0);

			/// Get the pin list
			TPinList& GetPinList();
			const TPinList& GetPinList() const;

			/// Convert the value of the pins to a single 8 bit value or 16 bit value
			template <class T>
			T PinsToValue(TPin::TPinGroupID PinGroup = 0);

			/// Convert the value a single 8 bit value or 16 bit value to the pins
			template <class T>
			void ValueToPins(const T& Value, TPin::TPinGroupID PinGroup = 0);

			void Init();

			void Update();

		private:
			
			// Connect a single Pin to another single pin or multiple pin
			friend void TPinComponentUtility::ConnectPins(TPin& LeftPin, TPin& RightPin);
			friend void TPinComponentUtility::ConnectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			friend void TPinComponentUtility::ConnectPins(const TPinBus& LeftBus, const TPinBus& RightBus);

			// Function to detach pin
			friend void TPinComponentUtility::DetachPins(TPin& LeftPin, TPin& RightPin);
			friend void TPinComponentUtility::DetachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			friend void TPinComponentUtility::DetachPins(const TPinBus& LeftBus, const TPinBus& RightBus);

		private:
			TPinList mPins;
		};

		template<class T>
		inline T TPinComponent::PinsToValue(TPin::TPinGroupID PinGroup)
		{
			T ReturnValue = 0;

			// Get the bus where we are writing the data
			auto PinBus = GetPinBus(PinGroup);

			// Bit value to store which bit we are trying to write
			std::size_t Bit = 0;

			// Put the bit in the bus
			for (auto& Pin = PinBus.first; Pin != PinBus.second; ++Pin)
			{
				ReturnValue |= Pin->GetPinStatus() << Bit++;
			}

			return ReturnValue;
		}

		template<class T>
		inline void TPinComponent::ValueToPins(const T& Value, TPin::TPinGroupID PinGroup)
		{
			// Get the bus where we are writing the data
			auto PinBus = GetPinBus(PinGroup);

			// Bit value to store which bit we are trying to write
			std::size_t Bit = 0;

			// Put the bit in the bus
			for (auto& Pin = PinBus.first; Pin != PinBus.second; ++Pin)
			{
				auto SelectedBit = TInternals::TUtility::GetBit(Value, Bit++);
				auto NewStatus = static_cast<TComponents::TPin::TStatus>(SelectedBit);
				Pin->ChangePinStatus(NewStatus, true);
			}
		}
	}
}

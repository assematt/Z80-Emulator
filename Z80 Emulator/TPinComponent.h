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

namespace nne
{
	namespace tcomponents
	{
		using TPinBusIndex = std::size_t;
		using TPinList = std::vector<TPin>;
		//using TPinList = std::map<TPin::TPinNumber, TPin>;
		using TPinBus = std::pair<TPinList::iterator, TPinList::iterator>;

		// Connect a single Pin to another single pin or multiple pin
		namespace TPinComponentUtility
		{
			void connectPins(TPin& LeftPin, TPin& RightPin);
			void connectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			void connectPins(const TPinBus& LeftBus, const TPinBus& RightBus);

			void detachPins(TPin& LeftPin, TPin& RightPin);
			void detachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			void detachPins(const TPinBus& LeftBus, const TPinBus& RightBus);
		}

		struct TPinComponent : nne::IComponent
		{
		public:

			TPinComponent() = default;

			TPinComponent(const std::initializer_list<TPin>& PinList, std::size_t PinCount);

			/// Setup the pins configuration
			void setupPins(const std::initializer_list<TPin>& PinList, std::size_t PinCount);

			/// Subscript operator to get a pin
			TPin& operator[] (const TPin::TPinNumber PinToSelect);
			const TPin& operator[] (const TPin::TPinNumber PinToSelect) const;
			
			/// Get a pin
			TPin& getPin(const TPin::TPinNumber PinToSelect);
			const TPin& getPin(const TPin::TPinNumber PinToSelect) const;

			/// Get bus
			TPinBus getPinBus(const TPin::TPinGroupID BusID, const TPinBusIndex BusBegin = 0, const TPinBusIndex BusEnd = 0);

			/// Get the pin list
			TPinList& getPinList();
			const TPinList& getPinList() const;

			/// Convert the value of the pins to a single 8 bit value or 16 bit value
			template <class T>
			T pinsToValue(TPin::TPinGroupID PinGroup = 0);

			/// Convert the value a single 8 bit value or 16 bit value to the pins
			template <class T>
			void valueToPins(const T& Value, TPin::TPinGroupID PinGroup = 0);

			void init() override;

			void update() override;

			void refresh() override {}

		private:
			
			// Connect a single Pin to another single pin or multiple pin
			friend void TPinComponentUtility::connectPins(TPin& LeftPin, TPin& RightPin);
			friend void TPinComponentUtility::connectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			friend void TPinComponentUtility::connectPins(const TPinBus& LeftBus, const TPinBus& RightBus);

			// Function to detach pin
			friend void TPinComponentUtility::detachPins(TPin& LeftPin, TPin& RightPin);
			friend void TPinComponentUtility::detachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			friend void TPinComponentUtility::detachPins(const TPinBus& LeftBus, const TPinBus& RightBus);

		private:
			TPinList mPins;
		};

		template<class T>
		inline T TPinComponent::pinsToValue(TPin::TPinGroupID PinGroup)
		{
			T ReturnValue = 0;

			// Get the bus where we are writing the data
			auto PinBus = getPinBus(PinGroup);

			// Bit value to store which bit we are trying to write
			std::size_t Bit = 0;

			// Put the bit in the bus
			for (auto& Pin = PinBus.first; Pin != PinBus.second; ++Pin)
			{
				ReturnValue |= Pin->getPinStatus() << Bit++;
			}

			return ReturnValue;
		}

		template<class T>
		inline void TPinComponent::valueToPins(const T& Value, TPin::TPinGroupID PinGroup)
		{
			// Get the bus where we are writing the data
			auto PinBus = getPinBus(PinGroup);

			// Bit value to store which bit we are trying to write
			TU8BitValue Bit = 0;

			// Put the bit in the bus
			for (auto& Pin = PinBus.first; Pin != PinBus.second; ++Pin)
			{
				auto SelectedBit = nne::TUtility::getBit(Value, Bit++);
				auto NewStatus = static_cast<tcomponents::TPin::TStatus>(SelectedBit);
				Pin->changePinStatus(NewStatus, true);
			}
		}
	}
}

#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <initializer_list>
#include <assert.h>
#include <utility>
#include <vector>
#include <memory>

#include "TPin.h"
#include "TValues.h"
#include "TEntity.h"
#include "TUtility.h"
#include "IComponent.h"

namespace nne
{
	using namespace tcomponents;

	class TPinComponent : public nne::IComponent
	{
	public:

		static const std::size_t None;
		static const sf::Color PinColorNormal;
		static const sf::Color PinColorHover;
		static const sf::Color PinColorSelected;

		static const sf::Color PinColorStatusLow;
		static const sf::Color PinColorStatusHigh;
		static const sf::Color PinColorStatusHighZ;

		TPinComponent();

		TPinComponent(const std::initializer_list<TPin>& PinList, std::size_t PinCount);

		void init() override;

		void update(const sf::Time& ElapsedTime) override;

		void refresh(const sf::Time& ElapsedTime) override;

		/// Setup the pins configuration
		void setupPins(const std::initializer_list<TPin>& PinList, std::size_t PinCount);

		/// Subscript operator to get a pin
		TPin& operator[] (const TPin::TPinID& PinIDToSelect);
		const TPin& operator[] (const TPin::TPinID& PinIDToSelect) const;

		/// Get a pin by PIN number
		TPin& getPin(const TPin::TPinNumber& PinToSelect);
		const TPin& getPin(const TPin::TPinNumber& PinToSelect) const;

		/// Get a pin by name
		TPin& getPin(const std::string& PinToSelect);
		const TPin& getPin(const std::string& PinToSelect) const;

		/// Return the selected pin color
		const sf::Color& getPinColor(const std::size_t& PinIndex) const;

		/// Function to set the color for all the pins in the chip
		void setPinsColor(const sf::Color& Color);

		/// Function to set the color for one specific pin in the chip
		void setPinColor(const sf::Color& Color, const std::size_t& PinIndex);

		/// Get bus
		TPinBus getPinBus(const TPin::TPinGroupID BusID, const TPinBusIndex BusBegin = 0, const TPinBusIndex BusEnd = 0);

		/// Get the pin list
		TPinList& getPinList();
		const TPinList& getPinList() const;

		/// Get the selected pin
		tcomponents::TPin& getSelectedPin();
		const tcomponents::TPin& getSelectedPin() const;

		/// Get the hover pin
		const tcomponents::TPin& getHoverPin() const;

		/// Function to reset the state of the selected PIN
		void deselectPin();

		/// Get the local/global bound of a single PIN
		sf::FloatRect getPinLocalBounds(const std::size_t& PinIndex);
		sf::FloatRect getPinLocalBounds(const std::string& PinToSelect);
		sf::FloatRect getPinLocalBounds(const TPin::TPinNumber& PinToSelect);

		sf::FloatRect getPinGlobalBounds(const std::size_t& PinIndex);
		sf::FloatRect getPinGlobalBounds(const std::string& PinToSelect);
		sf::FloatRect getPinGlobalBounds(const TPin::TPinNumber& PinToSelect);

		/// Convert the value of the pins to a single 8 bit value or 16 bit value
		template <class T>
		T pinsToValue(TPin::TPinGroupID PinGroup = 0);

		/// Convert the value a single 8 bit value or 16 bit value to the pins
		template <class T>
		void valueToPins(const T& Value, TPin::TPinGroupID PinGroup = 0);

		/// Create an array of 4 vertices with the appropriate size and position based on the passed argument
		void createPin(const sf::Vector2f& Position, const sf::Vector2f& Size, sf::VertexArray& OutputVertices);

	private:

		/// Because the pin size can be negative due to the fact vertex array data is relative to the main we have to do some math to figure out the pin real size
		sf::Vector2f computePinSize(const std::size_t& PinIndex);

		/// Check if we clicked on a pin and return that pin index
		bool checkMouseClickOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos);

		/// Check if we clicked on a pin and return that pin index
		bool checkMouseOverOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos);

		/// Connect a single Pin to another single pin or multiple pin
		friend void TPinComponentUtility::connectPins(TPin& LeftPin, TPin& RightPin);
		friend void TPinComponentUtility::connectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
		friend void TPinComponentUtility::connectPins(const TPinBus& LeftBus, const TPinBus& RightBus);

		/// Function to detach pin
		friend void TPinComponentUtility::detachPins(TPin& LeftPin, TPin& RightPin);
		friend void TPinComponentUtility::detachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
		friend void TPinComponentUtility::detachPins(const TPinBus& LeftBus, const TPinBus& RightBus);

	private:
		TPinList		mPins;
		std::size_t		mPreviousOverPin;
		std::size_t		mOverPin;
		std::size_t		mPreviousSelectedPin;
		std::size_t		mSelectedPin;

		TPin::TPinID	mSelectedPinID;
		TPin::TPinID	mOverPinID;
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

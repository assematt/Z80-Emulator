#include "TPinComponent.h"

#include <SFML/Window/Event.hpp>

#include "TBoard.h"
#include "TSceneManager.h"
#include "TChipComponent.h"
#include "TEventComponent.h"
#include "TStateComponent.h"
#include "TDrawableComponent.h"
#include "TLogicBoardComponent.h"

namespace nne
{
	const std::size_t TPinComponent::None = std::numeric_limits<unsigned int>::max();
	const sf::Color TPinComponent::PinColorNormal = { 120, 120, 120 };
	const sf::Color TPinComponent::PinColorHover = { 60, 60, 60 };
	const sf::Color TPinComponent::PinColorSelected = { 15, 15, 15 };

	const sf::Color TPinComponent::PinColorStatusLow = { 120, 0, 0 };
	const sf::Color TPinComponent::PinColorStatusHigh = { 0, 120, 0 };
	const sf::Color TPinComponent::PinColorStatusHighZ = { 0, 0, 128 };

	TPinComponent::TPinComponent() :
		mPreviousOverPin(None),
		mOverPin(None),
		mPreviousSelectedPin(None),
		mSelectedPin(None)
	{
	}

	TPinComponent::TPinComponent(const std::initializer_list<TPin>& PinList, std::size_t PinCount) :
		TPinComponent::TPinComponent()
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
		// Create the connection
		LeftPin.addConnections(RightPin);

		// Update the status of the connected PINs based on their type
		updatePinStatus(LeftPin, RightPin);
	}

	void TPinComponentUtility::connectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins)
	{
		for (auto Pin : RightPins)
			connectPins(LeftPin, Pin);
	}

	void TPinComponentUtility::connectPins(const TPinBus& LeftBus, const TPinBus& RightBus)
	{
		//

		for (TPinBus::first_type LeftPin = LeftBus.first, RightPin = RightBus.first; LeftPin != LeftBus.second; ++LeftPin, ++RightPin)
			connectPins(*LeftPin, *RightPin);
	}

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

	const std::size_t& TPinComponent::getSelectedPinNumber() const
	{
		return mSelectedPin + 1;
	}

	nne::tcomponents::TPin& TPinComponent::getSelectedPin()
	{
		return mParent->getComponent<TPinComponent>().getPin(mSelectedPin + 1);
	}

	const nne::tcomponents::TPin& TPinComponent::getSelectedPin() const
	{
		return mParent->getComponent<TPinComponent>().getPin(mSelectedPin + 1);
	}

	void TPinComponent::deselectPin()
	{
		mPreviousOverPin = None;
		mOverPin = None;
		mPreviousSelectedPin = None;
		mSelectedPin = None;
	}

	sf::FloatRect TPinComponent::getPinLocalBounds(const std::size_t& PinIndex)
	{
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();

		sf::Vector2f PinPosition = Vertices[PinIndex * 4 + 4 + 0].position;

		// Because the pin size can be negative due to the fact vertex array data is relative to the main we have to do some math to figure out the pin real size
		sf::Vector2f PinSize = computePinSize(PinIndex);

		return{ PinPosition, PinSize };
	}

	sf::FloatRect TPinComponent::getPinGlobalBounds(const std::size_t& PinIndex)
	{
		return mParent->getComponent<TDrawableComponent>().getTransform().transformRect(getPinLocalBounds(PinIndex));
	}

	void TPinComponent::createPin(const sf::Vector2f& Position, const sf::Vector2f& Size, sf::VertexArray& OutputVertices)
	{
		OutputVertices.append({ sf::Vector2f(0.f, 0.f) + Position, PinColorNormal });
		OutputVertices.append({ sf::Vector2f(0.f, Size.y) + Position, PinColorNormal });
		OutputVertices.append({ sf::Vector2f(Size.x, Size.y) + Position, PinColorNormal });
		OutputVertices.append({ sf::Vector2f(Size.x, 0.f) + Position, PinColorNormal });
	}

	sf::Vector2f TPinComponent::computePinSize(const std::size_t& PinIndex)
	{
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();

		auto Width = std::abs(Vertices[PinIndex * 4 + 4 + 3].position.x - Vertices[PinIndex * 4 + 4 + 0].position.x);
		auto Height = std::abs(Vertices[PinIndex * 4 + 4 + 2].position.y - Vertices[PinIndex * 4 + 4 + 0].position.y);

		return{ Width, Height };
	}

	bool TPinComponent::checkMouseClickOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos)
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Left) && PinBound.contains(MousePos) ? true : false;
	}

	bool TPinComponent::checkMouseOverOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos)
	{
		return PinBound.contains(MousePos) ? true : false;
	}
	
	TPin& TPinComponent::getPin(const TPin::TPinNumber& PinToSelect)
	{
		// Look in all the pins of this component
		for (auto& Pin : mPins)
		{
			// And if the current iterated PIN it's the one we are looking for return it (and so exit the function)
			if (Pin.mPinNumber == PinToSelect)
				return Pin;
		}

		return TPin::NotFound;
	}

	const TPin& TPinComponent::getPin(const TPin::TPinNumber& PinToSelect) const
	{
		// Look in all the pins of this component
		for (auto& Pin : mPins)
		{
			// And if the current iterated PIN it's the one we are looking for return it (and so exit the function)
			if (Pin.mPinNumber == PinToSelect)
				return Pin;
		}

		return TPin::NotFound;
	}

	nne::tcomponents::TPin& TPinComponent::getPin(const std::string& PinToSelect)
	{
		// Look in all the pins of this component
		for (auto& Pin : mPins)
		{
			// And if the current iterated PIN it's the one we are looking for return it (and so exit the function)
			if (Pin.mPinName == PinToSelect)
				return Pin;
		}

		return TPin::NotFound;
	}

	const nne::tcomponents::TPin& TPinComponent::getPin(const std::string& PinToSelect) const
	{
		// Look in all the pins of this component
		for (auto& Pin : mPins)
		{
			// And if the current iterated PIN it's the one we are looking for return it (and so exit the function)
			if (Pin.mPinName == PinToSelect)
				return Pin;
		}

		return TPin::NotFound;
	}

	const sf::Color& TPinComponent::getPinColor(const std::size_t& PinIndex) const
	{
		return mParent->getComponent<TDrawableComponent>().getVertexArray()[PinIndex * 4 + 4].color;
	}

	void TPinComponent::setPinsColor(const sf::Color& Color)
	{
		// Get a ref to vertex array
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();

		// Get the number of pins
		std::size_t NumberOfPins = mParent->getComponent<TPinComponent>().getPinList().size();

		// Iterate through all the pins vertices
		for (size_t Index = 0; Index < NumberOfPins; ++Index)
		{
			Vertices[Index * 4 + 4 + 0].color = Color;
			Vertices[Index * 4 + 4 + 1].color = Color;
			Vertices[Index * 4 + 4 + 2].color = Color;
			Vertices[Index * 4 + 4 + 3].color = Color;
		}
	}

	void TPinComponent::setPinColor(const sf::Color& Color, const std::size_t& PinIndex)
	{
		// Get a ref to vertex array
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();

		// Change the pin color
		Vertices[PinIndex * 4 + 4 + 0].color = Color;
		Vertices[PinIndex * 4 + 4 + 1].color = Color;
		Vertices[PinIndex * 4 + 4 + 2].color = Color;
		Vertices[PinIndex * 4 + 4 + 3].color = Color;
	}

	void TPinComponent::init()
	{

	}

	void TPinComponent::update(const sf::Time& ElapsedTime)
	{
		// Execute the update cycle only if we placed the chip the pin color only we placed the chip
		if (!mParent->getComponent<TChipComponent>().isPlaced())
			return;

		// Get a ref to the pin component
		std::size_t PinsNumber = mPins.size();

		// Update the pin color only we placed the chip
		for (auto Index = 0u; Index < PinsNumber; ++Index)
		{
			if (!getPin(Index + 1).hasConnections())
			{
				setPinColor(PinColorNormal, Index);

				continue;
			}

			switch (getPin(Index + 1).getPinStatus())
			{
			case tcomponents::TPin::LOW:
				setPinColor(PinColorStatusLow, Index);
				break;
			case tcomponents::TPin::HIGH:
				setPinColor(PinColorStatusHigh, Index);
				break;
			case tcomponents::TPin::HIGH_Z:
				setPinColor(PinColorStatusHighZ, Index);
				break;
			}
		}

		// Set the color of the hover pin appropriately
		if (mOverPin != None)
		{
			setPinColor(PinColorHover, mOverPin);
		}
		else if (mPreviousOverPin != None)
		{
			setPinColor(PinColorNormal, mPreviousOverPin);
		}

		// Set the color of the selected pin appropriately
		if (mSelectedPin != None)
		{
			if (mPreviousSelectedPin != None)
				setPinColor(PinColorNormal, mPreviousSelectedPin);

			setPinColor(PinColorSelected, mSelectedPin);
		}
		else if (mPreviousSelectedPin != None)
		{
			setPinColor(PinColorNormal, mPreviousSelectedPin);
		}
	}

	void TPinComponent::refresh(const sf::Time& ElapsedTime)
	{
		// Execute the refresh cycle only if we placed the chip the pin color only we placed the chip
		if (!mParent->getComponent<TChipComponent>().isPlaced())
			return;

		// Get a ref to the logic board component
		//auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>();
		auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>().getBoard();

		// Get the number of pins
		std::size_t NumberOfPins = mPins.size();

		// Get mouse info
		auto MousePos = mParent->getComponent<tcomponents::TEventComponent>().getMousePosition();

		// Swap the status of the selected and over pin
		mPreviousOverPin = mOverPin;

		// Reset the status of the hover pin
		mOverPin = None;
		
		// Iterate through all the PINS
		for (size_t Index = 0; Index < NumberOfPins; ++Index)
		{
			// Get the pin bound of the selected PIN
			auto PinBound = getPinGlobalBounds(Index);
			
			// If we clicked on the entity
			if (checkMouseClickOnPin(PinBound, MousePos))
			{
				mPreviousSelectedPin = mSelectedPin;
				mSelectedPin = Index;

				// Inform the logic board component that we selected this component
				//LogicBoard.setSelectedChip(&mParent->getComponent<TChipComponent>());
				LogicBoard.setSelectedComponent<TChipComponent>(mParent->getComponentAsPtr<TChipComponent>());

				return;
			}
			// If we are just hovering the entity
			else if (checkMouseOverOnPin(PinBound, MousePos))
			{
				mOverPin = Index;

				return;
			}
		}
	
		// If we arrive at this point maybe we have to deselect the chip
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && LogicBoard.getInsertionMethod() != TLogicBoardComponent::TInsertionMethod::WIRE)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && LogicBoard.getInsertionMethod() != TBoard::TInsertionMethod::WIRE)
		{
// 			if (LogicBoard.getSelectedChip() == mParent->getComponentAsPtr<TChipComponent>())
// 				LogicBoard.deselectChip();
			if (LogicBoard.getSelectedComponent<TChipComponent>() == mParent->getComponentAsPtr<TChipComponent>())
				LogicBoard.deselectComponent<TChipComponent>();
		}
	}
}
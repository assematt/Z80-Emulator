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

	TPin& TPinComponent::operator[](const TPin::TPinID& PinIDToSelect)
	{
		// Look in all the pins of this component
		for (auto& Pin : mPins)
		{
			// And if the current iterated PIN it's the one we are looking for return it (and so exit the function)
			if (Pin.getPinID() == PinIDToSelect)
				return Pin;
		}
		
		return TPin::NotFound;
	}

	const TPin& TPinComponent::operator[](const TPin::TPinID& PinIDToSelect) const
	{
		// Look in all the pins of this component
		for (auto& Pin : mPins)
		{
			// And if the current iterated PIN it's the one we are looking for return it (and so exit the function)
			if (Pin.getPinID() == PinIDToSelect)
				return Pin;
		}

		return TPin::NotFound;
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
	
	nne::tcomponents::TPin& TPinComponent::getSelectedPin()
	{
		return (*this)[mSelectedPinID];
	}

	const nne::tcomponents::TPin& TPinComponent::getSelectedPin() const
	{
		return (*this)[mSelectedPinID];
	}

	const nne::tcomponents::TPin& TPinComponent::getHoverPin() const
	{
		return (*this)[mOverPinID];
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
#if ENTITY_SYSTEM == NNE
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();
#else
		auto& Vertices = mParent->getComponent<TDrawableComponent>()->getVertexArray();
#endif

		sf::Vector2f PinPosition = Vertices[PinIndex * 4 + 4].position;

		// Because the pin size can be negative due to the fact vertex array data is relative to the main we have to do some math to figure out the pin real size
		sf::Vector2f PinSize = computePinSize(PinIndex);

		return{ PinPosition, PinSize };
	}

	sf::FloatRect TPinComponent::getPinLocalBounds(const std::string& PinToSelect)
	{
		auto Index = 0u;
		auto Size = mPins.size();

		while (Index < Size && mPins[Index++].mPinName != PinToSelect);

		// Return an empty sf::FloatRect if we don't find anything
		if (Index == Size)
			return{};

		return getPinLocalBounds(Index - 1);
	}

	sf::FloatRect TPinComponent::getPinLocalBounds(const TPin::TPinNumber& PinToSelect)
	{
		auto Index = 0u;
		auto Size = mPins.size();

		while (Index < Size && mPins[Index++].mPinNumber != PinToSelect);

		// Return an empty sf::FloatRect if we don't find anything
		if (Index == Size)
			return{};

		return getPinLocalBounds(Index - 1);
	}

	sf::FloatRect TPinComponent::getPinGlobalBounds(const std::size_t& PinIndex)
	{
#if ENTITY_SYSTEM == NNE
		auto Pos = mParent->getComponent<TDrawableComponent>().getPosition();
#else
		auto Pos = mParent->getComponent<TDrawableComponent>()->getPosition();
#endif

		auto PinBound = getPinLocalBounds(PinIndex);

		PinBound.left += Pos.x;
		PinBound.top += Pos.y;

		//return mParent->getComponent<TDrawableComponent>().getTransform().transformRect(getPinLocalBounds(PinIndex));
		return PinBound;
	}

	sf::FloatRect TPinComponent::getPinGlobalBounds(const std::string& PinToSelect)
	{
		return getPinLocalBounds(PinToSelect);
	}

	sf::FloatRect TPinComponent::getPinGlobalBounds(const TPin::TPinNumber& PinToSelect)
	{
		return getPinLocalBounds(PinToSelect);
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
#if ENTITY_SYSTEM == NNE
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();
#else
		auto& Vertices = mParent->getComponent<TDrawableComponent>()->getVertexArray();
#endif

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
#if ENTITY_SYSTEM == NNE
		return mParent->getComponent<TDrawableComponent>().getVertexArray()[PinIndex * 4 + 4].color;
#else
		return mParent->getComponent<TDrawableComponent>()->getVertexArray()[PinIndex * 4 + 4].color;
#endif		
	}

	void TPinComponent::setPinsColor(const sf::Color& Color)
	{
		// Get a ref to vertex array		
#if ENTITY_SYSTEM == NNE
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();
#else
		auto& Vertices = mParent->getComponent<TDrawableComponent>()->getVertexArray();
#endif		

		// Get the number of pins
#if ENTITY_SYSTEM == NNE
		std::size_t NumberOfPins = mParent->getComponent<TPinComponent>().getPinList().size();
#else
		std::size_t NumberOfPins = mParent->getComponent<TPinComponent>()->getPinList().size();
#endif	

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
#if ENTITY_SYSTEM == NNE
		auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();
#else
		auto& Vertices = mParent->getComponent<TDrawableComponent>()->getVertexArray();
#endif	

		// Change the pin color
		Vertices[PinIndex * 4 + 4 + 0].color = Color;
		Vertices[PinIndex * 4 + 4 + 1].color = Color;
		Vertices[PinIndex * 4 + 4 + 2].color = Color;
		Vertices[PinIndex * 4 + 4 + 3].color = Color;
	}

	void TPinComponent::init()
	{

	}

	void TPinComponent::update(REFRESH_UPDATE_PARAMETER)
	{
		// Execute the update cycle only if we placed the chip the pin color only we placed the chip		
#if ENTITY_SYSTEM == NNE
		if (!mParent->getComponent<TChipComponent>().isPlaced())
#else
		if (!mParent->getComponent<TChipComponent>()->isPlaced())
#endif	
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

	void TPinComponent::refresh(REFRESH_UPDATE_PARAMETER)
	{
		// Execute the refresh cycle only if we placed the chip the pin color only we placed the chip
#if ENTITY_SYSTEM == NNE
		if (!mParent->getComponent<TChipComponent>().isPlaced())
#else
		if (!mParent->getComponent<TChipComponent>()->isPlaced())
#endif	
			return;

		// Get a ref to the logic board component
#if ENTITY_SYSTEM == NNE
		auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>().getBoard();
#else
		auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>()->getBoard();
#endif
		
		// Get the number of pins
		std::size_t NumberOfPins = mPins.size();

		// Get mouse info
#if ENTITY_SYSTEM == NNE
		auto MousePos = mParent->getComponent<tcomponents::TEventComponent>().getMousePosition();
#else
		auto MousePos = mParent->getComponent<tcomponents::TEventComponent>()->getMousePosition();
#endif

		// Swap the status of the selected and over pin
		mPreviousOverPin = mOverPin;

		// Reset the status of the hover pin
		mOverPin = None;
		
		// Iterate through all the PINS
		auto Index = 0u;
		for (auto& Pin : mPins)
		{
			// Get the pin bound of the selected PIN
			auto PinBound = getPinGlobalBounds(Index);

			// If we clicked on the entity
			if (checkMouseClickOnPin(PinBound, MousePos))
			{
				mPreviousSelectedPin = mSelectedPin;

				mSelectedPin = Index;
				mSelectedPinID = getPin(Index + 1).getPinID();

				// Inform the logic board component that we selected this component
#if ENTITY_SYSTEM == NNE
				LogicBoard.setSelectedComponent<TChipComponent>(mParent->getComponentAsPtr<TChipComponent>());
#else
				LogicBoard.setSelectedComponent<TChipComponent>(&(*mParent->getComponent<TChipComponent>()));
#endif
				return;
			}
			// If we are just hovering the entity
			else if (checkMouseOverOnPin(PinBound, MousePos))
			{
				mOverPin = Index;
				mOverPinID = getPin(Index + 1).getPinID();

				return;
			}

			++Index;
		}

		// If we arrive at this point maybe we have to deselect the chip
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && LogicBoard.getInsertionMethod() != TBoard::TInsertionMethod::WIRE)
		{
			
#if ENTITY_SYSTEM == NNE
			if (LogicBoard.getSelectedComponent<TChipComponent>() == mParent->getComponentAsPtr<TChipComponent>())
#else
			if (LogicBoard.getSelectedComponent<TChipComponent>() == (&(*mParent->getComponent<TChipComponent>())))
#endif
				LogicBoard.deselectComponent<TChipComponent>();
		}

	}
}
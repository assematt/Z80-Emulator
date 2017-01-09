#include "TPinComponent.h"

#include <SFML/Window/Event.hpp>

#include "TSceneManager.h"
#include "TLogicBoardComponent.h"
#include "TDrawableComponent.h"

namespace nne
{
	namespace tcomponents
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

		const std::size_t& TPinComponent::getSelectedPinNumber() const
		{
			return mSelectedPin + 1;
		}

		nne::tcomponents::TPin& TPinComponent::getSelectedPin()
		{
			return mParent->getComponent<tcomponents::TPinComponent>().getPin(mSelectedPin + 1);
		}

		const nne::tcomponents::TPin& TPinComponent::getSelectedPin() const
		{
			return mParent->getComponent<tcomponents::TPinComponent>().getPin(mSelectedPin + 1);
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

		TPin& TPinComponent::getPin(TPin::TPinNumber PinToSelect)
		{
			assert((PinToSelect <= mPins.size()) && "Pin out of bound");

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

		const sf::Color& TPinComponent::getPinColor(const std::size_t& PinIndex) const
		{
			return mParent->getComponent<TDrawableComponent>().getVertexArray()[PinIndex * 4 + 4].color;
		}

		void TPinComponent::setPinsColor(const sf::Color& Color)
		{
			// Get a ref to vertex array
			auto& Vertices = mParent->getComponent<TDrawableComponent>().getVertexArray();

			// Get the number of pins
			std::size_t NumberOfPins = mParent->getComponent<tcomponents::TPinComponent>().getPinList().size();

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

			// Iterates 
			bool PinFound = false;
			bool PinSelectedFound = false;

			// Get the number of pins
			std::size_t NumberOfPins = mPins.size();

			// Get a ref to TRenderSurface
			auto& RenderWindow = mParent->getParentScene()->getRenderWindow();
			auto& RenderSurface = mParent->getParentScene()->getRenderSurface();

			// Get mouse info
			auto MousePosition = sf::Mouse::getPosition(RenderWindow) - static_cast<sf::Vector2i>(RenderSurface.getPosition());
			auto MousePositionAdj = RenderSurface.mapPixelToCoords(MousePosition);

			// Swap the status of the selected and over pin
			mPreviousOverPin = mOverPin;

			// Reset the status of the selected pin and the hover pin
			mOverPin = None;

			for (size_t Index = 0; Index < NumberOfPins && !PinFound; ++Index)
			{
				auto& PinBound = getPinGlobalBounds(Index);

				if (checkMouseClickOnPin(PinBound, MousePositionAdj))
				{
					mPreviousSelectedPin = mSelectedPin;
					mSelectedPin = Index;

					// Inform the logic board component that we selected this component
					mParent->getComponentAsPtr<TLogicBoardComponent>()->setSelectedChip(&mParent->getComponent<TChipComponent>());

					PinFound = true;
				}

				if (checkMouseOverOnPin(PinBound, MousePositionAdj))
				{
					mOverPin = Index;

					PinFound = true;
				}
			}
		}

	}
}
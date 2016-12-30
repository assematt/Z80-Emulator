#include "TChipComponent.h"

#include "TLogicBoardComponent.h"
#include "TCacheManager.h"
#include "TSceneManager.h"

#define DEBUG_ONCE TRUE

namespace nne
{
	const std::size_t TChipComponent::None = std::numeric_limits<unsigned int>::max();
	const sf::Color TChipComponent::PinColorNormal = { 120, 120, 120 };
	const sf::Color TChipComponent::PinColorHover = { 60, 60, 60 };
	const sf::Color TChipComponent::PinColorSelected = { 15, 15, 15 };

	const sf::Color TChipComponent::PinColorStatusLow = { 120, 0, 0 };
	const sf::Color TChipComponent::PinColorStatusHigh = { 0, 120, 0 };
	const sf::Color TChipComponent::PinColorStatusHighZ = { 0, 0, 128 };

	TChipComponent::TChipComponent(TEntity* ManagedObject) :
		mManagedObject(ManagedObject),
		mOverPin(None),
		mPreviousOverPin(None),
		mSelectedPin(None),
		mPreviousSelectedPin(None)
	{

	}

	void TChipComponent::init()
	{
		// Get the drawable component
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();

		mLabels = mParent->getComponentAsPtr<TTextComponent>();

		mLabels->setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
		mLabels->setCharacterSize(13);
		mLabels->setFillColor({ 171,171,171 });

		renderDipChip();
	}

	void TChipComponent::update(const sf::Time& ElapsedTime)
	{
		// Get a ref to the pin component
		auto& PinComponent = *mManagedObject->getComponentAsPtr<tcomponents::TPinComponent>();
		const auto& PinsNumber = PinComponent.getPinList().size();

		// Draw the pin with the proper color
		for (auto Index = 0u; Index < PinsNumber; ++Index)
		{			
			switch (PinComponent.getPin(Index + 1).getPinStatus())
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

	void TChipComponent::refresh(const sf::Time& ElapsedTime)
	{
		// Iterates 
		bool PinFound = false;
		bool PinSelectedFound = false;

		// Get the number of pins
		std::size_t NumberOfPins = mManagedObject->getComponentAsPtr<tcomponents::TPinComponent>()->getPinList().size();

		// Get mouse info
		auto MousePosition = sf::Mouse::getPosition(mParent->getParentScene()->getRenderWindow()) - static_cast<sf::Vector2i>(mParent->getParentScene()->getRenderSurface().getPosition());
		auto MousePositionAdj = mParent->getParentScene()->getRenderSurface().mapPixelToCoords(MousePosition);
		
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
				mParent->getComponentAsPtr<TLogicBoardComponent>()->setSelectedChip(this);

				PinFound = true;
			}

			if (checkMouseOverOnPin(PinBound, MousePositionAdj))
			{
				mOverPin = Index;

				PinFound = true;
			}
		}
	}

	void TChipComponent::setPinsColor(const sf::Color& Color)
	{
		// Get a ref to vertex array
		auto& Vertices = mDrawableComponent->getVertexArray();

		// Get the number of pins
		std::size_t NumberOfPins = mManagedObject->getComponentAsPtr<tcomponents::TPinComponent>()->getPinList().size();

		// Iterate through all the pins vertices
		for (size_t Index = 0; Index < NumberOfPins; ++Index)
		{
			Vertices[Index * 4 + 4 + 0].color = Color;
			Vertices[Index * 4 + 4 + 1].color = Color;
			Vertices[Index * 4 + 4 + 2].color = Color;
			Vertices[Index * 4 + 4 + 3].color = Color;
		}
	}

	void TChipComponent::setPinColor(const sf::Color& Color, const std::size_t& PinIndex)
	{
		// Get a ref to vertex array
		auto& Vertices = mDrawableComponent->getVertexArray();

		// Change the pin color
		Vertices[PinIndex * 4 + 4 + 0].color = Color;
		Vertices[PinIndex * 4 + 4 + 1].color = Color;
		Vertices[PinIndex * 4 + 4 + 2].color = Color;
		Vertices[PinIndex * 4 + 4 + 3].color = Color;
	}

	const sf::Color& TChipComponent::getPinColor(const std::size_t& PinIndex) const
	{
		return mDrawableComponent->getVertexArray()[PinIndex * 4 + 4].color;
	}

	sf::Uint32 TChipComponent::getPinColor(const std::size_t& PinIndex)
	{
		return mDrawableComponent->getVertexArray()[PinIndex * 4 + 4].color.toInteger();
	}

	sf::FloatRect TChipComponent::getPinLocalBounds(const std::size_t& PinIndex)
	{
		auto& Vertices = mDrawableComponent->getVertexArray();

		sf::Vector2f PinPosition = Vertices[PinIndex * 4 + 4 + 0].position;

		// Because the pin size can be negative due to the fact vertex array data is relative to the main we have to do some math to figure out the pin real size
		sf::Vector2f PinSize = computePinSize(PinIndex);

		return { PinPosition, PinSize };
	}

	sf::FloatRect TChipComponent::getPinGlobalBounds(const std::size_t& PinIndex)
	{
		return mDrawableComponent->getTransform().transformRect(getPinLocalBounds(PinIndex));
	}

	void TChipComponent::deselectPin()
	{
		mPreviousOverPin = None;
		mOverPin = None;
		mPreviousSelectedPin = None;
		mSelectedPin = None;
	}

	const std::size_t& TChipComponent::getSelectedPinNumber() const
	{
		return mSelectedPin + 1;
	}

	const nne::tcomponents::TPin& TChipComponent::getSelectedPin() const
	{
		return mManagedObject->getComponent<tcomponents::TPinComponent>().getPin(mSelectedPin + 1);
	}

	nne::tcomponents::TPin& TChipComponent::getSelectedPin()
	{
		return mManagedObject->getComponent<tcomponents::TPinComponent>().getPin(mSelectedPin + 1);
	}

	void TChipComponent::renderDipChip()
	{
		// Get a ref to the PIN component
		auto& PinComponent = mManagedObject->getComponent<tcomponents::TPinComponent>();

		// Get the number of pins
		std::size_t NumberOfPins = PinComponent.getPinList().size();

		// Resize the vertex array to fit all the vertices
		mDrawableComponent->getVertexArray().resize(NumberOfPins * 4 + 4);

		// Set the chip's base properties
		mDrawableComponent->setSize({ 185, (9 * NumberOfPins / 2 + 14 * (NumberOfPins / 2 - 1)) + 38 });

		mChipSize = mDrawableComponent->getSize();

		// Set the chip color
		mDrawableComponent->setColor({ 30, 30, 30 });

		// Define pin size
		sf::Vector2f PinSize = { 15.f, 9.f };

		// Get the chip position
		sf::Vector2f ChipPosition = mDrawableComponent->getPosition();

		// Get a ref to the drawable component vertex array for cache purposes
		auto& Vertices = mDrawableComponent->getVertexArray();

		std::string ChipTotalString = "";
		
		// Set the chip's pins properties
		for (std::size_t PinCounter = 0; PinCounter < NumberOfPins; ++PinCounter)
		{
			float LabelOffsetX = PinCounter < NumberOfPins / 2 ? 22 : -23.f;

			sf::Vector2f PinPosition;
			if (PinCounter < NumberOfPins / 2)
				PinPosition = { -PinSize.x, 23.f * PinCounter + 19.f };
			else
				PinPosition = { static_cast<float>(mChipSize.x), 23.f * (NumberOfPins - PinCounter) - 4.f };


			// Create a pin and put the info in the main vertex array
			auto PinVerticesArray = createPin(PinPosition + ChipPosition, PinSize, PinColorNormal);
			
			Vertices[PinCounter * 4 + 4 + 0] = PinVerticesArray[0];
			Vertices[PinCounter * 4 + 4 + 1] = PinVerticesArray[1];
			Vertices[PinCounter * 4 + 4 + 2] = PinVerticesArray[2];
			Vertices[PinCounter * 4 + 4 + 3] = PinVerticesArray[3];

			// 

			// Create the pin label			
			auto& PinName = PinComponent.getPin(PinCounter + 1).mPinName; //PinComponent[PinCounter].mPinName; //
			ChipTotalString += PinName + "  ";
			mLabels->setString(ChipTotalString);
			mLabels->setCharacterPosition(PinName + " ", { LabelOffsetX + PinPosition.x, PinPosition.y - 3.f });
		}
	}

	sf::Vector2f TChipComponent::computePinSize(const std::size_t& PinIndex)
	{
		auto& Vertices = mDrawableComponent->getVertexArray();

		auto Width = std::abs(Vertices[PinIndex * 4 + 4 + 3].position.x - Vertices[PinIndex * 4 + 4 + 0].position.x);
		auto Height = std::abs(Vertices[PinIndex * 4 + 4 + 2].position.y - Vertices[PinIndex * 4 + 4 + 0].position.y);

		return { Width, Height };
	}

	bool TChipComponent::checkMouseClickOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && PinBound.contains(MousePos))
			return true;

		return false;
	}

	bool TChipComponent::checkMouseOverOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos)
	{
		if (PinBound.contains(MousePos))
			return true;

		return false;
	}

	const std::array<sf::Vertex, 4> TChipComponent::createPin(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Color& Color)
	{
		std::array<sf::Vertex, 4> Pin;

		Pin[0] = { sf::Vector2f(0.f, 0.f) + Position, Color };
		Pin[1] = { sf::Vector2f(0.f, Size.y) + Position, Color };
		Pin[2] = { sf::Vector2f(Size.x, Size.y) + Position, Color };
		Pin[3] = { sf::Vector2f(Size.x, 0.f) + Position, Color };

		return std::move(Pin);
	}

}
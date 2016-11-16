#include "TChip.h"

namespace nne
{

	TChip::TChip(TEntity* ManagedObject) :
		mManagedObject(ManagedObject)
	{

	}

	void TChip::init()
	{
		mObjectShape = std::make_shared<sf::VertexArray>(sf::Quads, 4);
		mParent->getComponentAsPtr<TdrawableVector>()->pushdrawableObject({mObjectShape});

		renderDipChip();
	}

	void TChip::update()
	{
		// Pass the update event onto the chip pins
		for (auto& Pin : mPins)
			Pin.update();
	}

	void TChip::refresh()
	{
		// Pass the refresh event onto the chip pins
		for (auto& Pin : mPins)
			Pin.refresh();
	}

	void TChip::setSize(const sf::Vector2f& Size)
	{
		mSize = Size;

		auto& Vertices = *mObjectShape;

		Vertices[0].position = { 0.f, 0.f };
		Vertices[1].position = { mSize.x, 0.f };
		Vertices[2].position = mSize;
		Vertices[3].position = { 0.f, mSize.y };
	}

	const sf::Vector2f TChip::getSize() const
	{
		return mSize;
	}

	void TChip::setChipColor(const sf::Color& Color)
	{
		auto& Vertices = *mObjectShape;

		Vertices[0].color = Color;
		Vertices[1].color = Color;
		Vertices[2].color = Color;
		Vertices[3].color = Color;
	}

	void TChip::updateChipPosition()
	{
	}

	void TChip::renderDipChip()
	{
		// Get the number of pins
		std::size_t NumberOfPins = mManagedObject->getComponentAsPtr<tcomponents::TPinComponent>()->getPinList().size();

		// Get a ref to the vertex array
		auto& Vertices = *mObjectShape;

		// Resize the pin vector appropriately
		mPins.reserve(NumberOfPins);

		// Set the chip's base properties
		setSize({ 403.f, (21.f * NumberOfPins / 2 + 33.f * (NumberOfPins / 2 - 1)) + 70.f });

		// Set the chip color
		setChipColor(sf::Color(30, 30, 30));

		// Define pin size
		sf::Vector2f PinSize = { 82.f, 21.f };

		// Get the chip position
		sf::Vector2f ChipPosition = mParent->getComponentAsPtr<TTransformable>()->getPosition();
		
		// Set the chip's pins properties
		for (std::size_t PinCounter = 0; PinCounter < NumberOfPins; ++PinCounter)
		{
			sf::Vector2f RelativePinPosition = PinCounter < NumberOfPins / 2 ? sf::Vector2f(-PinSize.x, 54.f * PinCounter + 35.f) : sf::Vector2f(getSize().x, 54.f * (PinCounter - NumberOfPins / 2) + 35.f);

			RelativePinPosition += ChipPosition;

			// Bottom PIN portion
			mPins.emplace_back(this, RelativePinPosition, PinSize, sf::Color(120, 120, 120));

			// Add the last created pin in the rendering queque
			mParent->getComponentAsPtr<TdrawableVector>()->pushdrawableObject({ mPins.back().getVertexArray() });
		}
	}

}
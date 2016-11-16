#include "TChipPin.h"

namespace nne
{

	TChipPin::TChipPin(TChip* ParentChip) :
		mParentChip(ParentChip),
		mPin(std::make_shared<sf::VertexArray>(sf::Quads, 4)),
		mPosition(0.f, 0.f),
		mSize(0.f, 0.f),
		mHoverColor(60, 60, 60)
	{
	}

	TChipPin::TChipPin(TChip* ParentChip, const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Color& Color) :
		mParentChip(ParentChip),
		mPin(std::make_shared<sf::VertexArray>(sf::Quads, 4)),
		mPosition(Position),
		mSize(Size),
		mColor(Color),
		mHoverColor(60, 60, 60)
	{
		updateVertexArray(Position, Size);

		setColor(Color);		
	}

	void TChipPin::update()
	{
	}

	void TChipPin::refresh()
	{
		sf::Vector2f MousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(TGuiWindow::getInstance()));

		if (sf::FloatRect(mPosition, mSize).contains(MousePosition))
			setColor(mHoverColor);
	}

	void TChipPin::setPosition(const sf::Vector2f& Position)
	{
		mPosition = Position;

		updateVertexArray(mPosition, mSize);
	}

	const sf::Vector2f& TChipPin::getPosition() const
	{
		return mPosition;
	}

	void TChipPin::setSize(const sf::Vector2f& Size)
	{
		mSize = Size;

		updateVertexArray(mPosition, mSize);
	}

	const sf::Vector2f& TChipPin::getSize() const
	{
		return mSize;
	}

	void TChipPin::setColor(const sf::Color& Color)
	{
		(*mPin)[0].color = Color;
		(*mPin)[1].color = Color;
		(*mPin)[2].color = Color;
		(*mPin)[3].color = Color;
	}

	const sf::Color& TChipPin::getColor() const
	{
		return mColor;
	}

	const std::shared_ptr<sf::VertexArray>& TChipPin::getVertexArray() const
	{
		return mPin;
	}

	void TChipPin::updateVertexArray(const sf::Vector2f& Position, const sf::Vector2f& Size)
	{
		(*mPin)[0].position = sf::Vector2f(0.f, 0.f) + Position;
		(*mPin)[1].position = sf::Vector2f(0.f, Size.y) + Position;
		(*mPin)[2].position = sf::Vector2f(Size.x, Size.y) + Position;
		(*mPin)[3].position = sf::Vector2f(Size.x, 0.f) + Position;
	}

}
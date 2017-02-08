#include "TGridComponent.h"

namespace nne
{

	TGridComponent::TGridComponent(const sf::Vector2f& Size, const float& ColSize, const float& RowSize) :
		mSize(Size),
		mCellSize(ColSize, RowSize),
		mView(nullptr),
		mBuffer(0),
		mNeedsUpdate(false)
	{
		setSize(Size);
	}

	TGridComponent::TGridComponent() :
		mSize(0.f, 0.f),
		mCellSize(0.f, 0.f),
		mView(nullptr),
		mBuffer(0),
		mNeedsUpdate(false)
	{

	}

	void TGridComponent::setCellSize(const sf::Vector2f& CellSize)
	{
		mCellSize = CellSize;

		mNeedsUpdate = true;
	}

	const sf::Vector2f& TGridComponent::getCellSize() const
	{
		return mCellSize;
	}

	void TGridComponent::setSize(const sf::Vector2f& NewSize)
	{
		mSize = NewSize;

		mNeedsUpdate = true;
	}

	const sf::Vector2f& TGridComponent::getSize() const
	{
		return mSize;
	}

	void TGridComponent::setView(const sf::View& AttachedView)
	{
		mView = &AttachedView;

		mNeedsUpdate = true;
	}

	void TGridComponent::update(const sf::Time& ElapsedTime)
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}

	void TGridComponent::refresh(const sf::Time& ElapsedTime)
	{
		// If we don't need to update the vertex array 
		if (!mNeedsUpdate)
			return;

		// Get the view size
		auto ViewCenter = mView ? mView->getCenter() : mSize / 2.f;
		auto ViewSize = mView ? mView->getSize() : mSize;
		auto ViewPos = ViewCenter - (ViewSize / 2.f);

		// Get the number of cols and rows currently displayed
		auto GridSize = getColsRowsNumber(ViewSize);
		auto OffsetCell = getColsRowsNumber(ViewPos);

		// Clear the grid vector and resize it to accommodate all the cells
		auto& Grid = mDrawableComponent->getVertexArray();
		Grid.clear();

		// Fill the vertex array
		auto Index = 0u;
		for (auto Row = OffsetCell.y + -mBuffer; Row < GridSize.y + mBuffer + OffsetCell.y; ++Row)
			for (auto Col = OffsetCell.x + -mBuffer; Col < GridSize.x + mBuffer + OffsetCell.x; ++Col)
				Grid.append({ transformCellCoords({ Col, Row }), sf::Color::White });

		// The vertex array it's updated
		mNeedsUpdate = false;
	}

	void TGridComponent::init()
	{
		// Get the pointer to the entity drawable component and set some properties to his vertex array
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();
		mDrawableComponent->getVertexArray().setPrimitiveType(sf::Points);
	}

	sf::Vector2i TGridComponent::mouseCoordsToWindowCellCoords(const sf::Vector2i& MousePos)
	{
		// Compute in which column and row of the grid we are
		auto Col = std::roundf(MousePos.x / mCellSize.x);
		auto Row = std::roundf(MousePos.y / mCellSize.y);

		// Multiplies the selected row and col by the grid gap
		return sf::Vector2i(Col, Row);
	}

	sf::Vector2i TGridComponent::mouseCoordsToGridCellCoords(const sf::Vector2i& MousePos)
	{
		// Get the number of cols and rows currently displayed
		auto GridSize = getColsRowsNumber();

		// Compute in which column and row of the grid we are
		auto Col = static_cast<int>(std::roundf(MousePos.x / mCellSize.x)) % GridSize.x;
		auto Row = static_cast<int>(std::roundf(MousePos.y / mCellSize.y)) % GridSize.y;

		// Multiplies the selected row and col by the grid gap
		return sf::Vector2i(Col, Row);
	}

	sf::Vector2f TGridComponent::transformCellCoords(const sf::Vector2i& GridCoords)
	{
		// Multiplies the selected row and col by the grid gap
		return sf::Vector2f(GridCoords.x * mCellSize.x, GridCoords.y * mCellSize.y);
	}

	sf::Vector2f TGridComponent::convertCoordinate(const sf::RenderTarget& Target, const sf::Vector2f& InitialCoor)
	{
		// Convert the passed coordinate into the coordinate of the sf::RenderTarget passed
		auto TargetCoor = Target.mapPixelToCoords(static_cast<sf::Vector2i>(InitialCoor));

		// Convert those coordinate in cell coordinate
		auto CellCoord = mouseCoordsToWindowCellCoords(static_cast<sf::Vector2i>(TargetCoor));

		// Return the transformed cell coord
		return transformCellCoords(CellCoord);
	}

	sf::Vector2i TGridComponent::getColsRowsNumber(const sf::Vector2f& Size)
	{
		return sf::Vector2i(static_cast<std::size_t>(Size.x / mCellSize.x), static_cast<std::size_t>(Size.y / mCellSize.y));
	}

	sf::Vector2i TGridComponent::getColsRowsNumber()
	{
		return sf::Vector2i(static_cast<std::size_t>(mSize.x / mCellSize.x), static_cast<std::size_t>(mSize.y / mCellSize.y));
	}

	void TGridComponent::forceRefresh()
	{
		mNeedsUpdate = true;
	}

}
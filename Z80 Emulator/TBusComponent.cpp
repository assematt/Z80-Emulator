#include "TBusComponent.h"

#include <SFML/Window/Mouse.hpp>

#include "TBoard.h"
#include "IScene.h"
#include "TEventComponent.h"
#include "TStateComponent.h"
#include "TLogicBoardComponent.h"

namespace
{
	bool sameXAxes(const sf::Vector2f& Point1, const sf::Vector2f& Point2)
	{
		return (Point1.x != Point2.x) && (Point1.y == Point2.y);
	}

	bool sameYAxes(const sf::Vector2f& Point1, const sf::Vector2f& Point2)
	{
		return (Point1.x == Point2.x) && (Point1.y != Point2.y);
	}
}

namespace nne
{

	const sf::Color TBusComponent::BusColorNormal = { 0, 28, 52 };
	const sf::Color TBusComponent::BusColorHover = { 0, 28, 38 };
	const sf::Color TBusComponent::BusColorSelected = { 0, 14, 26 };

	const sf::Color TBusComponent::BusColorStatusLow = { 120, 0, 0 };
	const sf::Color TBusComponent::BusColorStatusHigh = { 0, 120, 0 };
	const sf::Color TBusComponent::BusColorStatusHighZ = { 0, 0, 128 };

	const sf::Vector2f Unnecessary = { std::numeric_limits<float>::min(), std::numeric_limits<float>::max() };

	TBusComponent::TBusComponent() :
		mDrawableComponent(nullptr),
		mFixedPoints(0u),
		mThickness(6.f),
		mEnableDraw(false),
		mLastPointPos(0.f, 0.f),
		mLastPointPosTemp(0.f, 0.f),
		mWireColor(BusColorNormal)
	{

	}

	void TBusComponent::update(REFRESH_UPDATE_PARAMETER)
	{
		// If we didn't enable the drawing return early
		if (mEnableDraw)
			return;

		// Get a ref to the vertex array
		auto& VertexArray = mDrawableComponent->getVertexArray();
		auto VerticesNumber = VertexArray.getVertexCount();

		// We this bus doesn't have any vertices skip the update function
		if (!VerticesNumber)
			return;

		// Update the color of the wire if we are hovering it and we didn't do it already
		if (mIsHovered && mDrawableComponent->getColor() != BusColorHover)
		{
			for (auto VIndex = 0u; VIndex < VerticesNumber; ++VIndex)
				VertexArray[VIndex].color = BusColorHover;
		}
		// Update the color of the wire if we selected it and we didn't do it already
		else if (!mIsHovered && mIsSelected && mDrawableComponent->getColor() != BusColorSelected)
		{
			// Change the color of all the vertices in the vertex array
			for (auto VIndex = 0u; VIndex < VerticesNumber; ++VIndex)
				VertexArray[VIndex].color = BusColorSelected;
		}
		// Reset the color of the wire to is normal color if we didn't do it already
		else if (!mIsSelected && !mIsHovered && mDrawableComponent->getColor() != BusColorNormal)
		{
			for (auto VIndex = 0u; VIndex < VerticesNumber; ++VIndex)
				VertexArray[VIndex].color = BusColorNormal;
		}
	}

	void TBusComponent::refresh(REFRESH_UPDATE_PARAMETER)
	{
		// If we didn't enable the drawing return early
		if (mEnableDraw)
			return;
		
		// Get a ref to the vertex array
		auto& VertexArray = mDrawableComponent->getVertexArray();
		auto VerticesNumber = VertexArray.getVertexCount();

		// Reset the state of the hover status by default
		setHoveredStatus(false);

		// Get a ref to the logic board component
#if ENTITY_SYSTEM == NNE
		auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>().getBoard();
#else
		auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>()->getBoard();
#endif
		
		// Get mouse info
#if ENTITY_SYSTEM == NNE
		auto MousePositionAdj = mParent->getComponent<tcomponents::TEventComponent>().getMousePosition();
#else
		auto MousePositionAdj = mParent->getComponent<tcomponents::TEventComponent>()->getMousePosition();
#endif

		// Execute the BUS check only if we clicked or we are hovering the chip
#if ENTITY_SYSTEM == NNE
		auto ComponentState = mParent->getComponent<tcomponents::TStateComponent>().getState();
#else
		auto ComponentState = mParent->getComponent<tcomponents::TStateComponent>()->getState();
#endif

		// Iterates through all the quads
		for (auto Index = 0u; Index < VerticesNumber; Index += 4)
		{
			// Get the quad bounding box and adjust it
			sf::FloatRect Quad = extractQuad(&VertexArray[Index]);
			adjustWireBound(Quad);

			// If we are clicking on the wire
			if (checkMouseClickOnWire(Quad, MousePositionAdj))
			{
				// Inform the logic board component that we selected this wire
				LogicBoard.setSelectedComponent<TBusComponent>(this);

				// Change the selection status of this wire
				setSelectedStatus(true);

				// This function had done it's job we can exit now
				return;
			}
			// If we are just hovering on the wire
			else if (checkMouseOverOnWire(Quad, MousePositionAdj))
			{
				// Change the selection status of this wire
				setHoveredStatus(true);

				// This function had done it's job we can exit now
				return;
			}
		}
	
	}

	void TBusComponent::init()
	{
#if ENTITY_SYSTEM == NNE
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();
#else
		mDrawableComponent = &(*mParent->getComponent<TDrawableComponent>());
#endif
		mDrawableComponent->getVertexArray().setPrimitiveType(sf::Quads);
	}

	void TBusComponent::setThickness(const float& Thickness)
	{
		mThickness = Thickness;

		renderWire();
	}

	const float& TBusComponent::getThickness() const
	{
		return mThickness;
	}

	void TBusComponent::setSelectedStatus(const bool& IsSelected /*= true*/)
	{
		mIsSelected = IsSelected;
	}

	const bool& TBusComponent::isSelected() const
	{
		return mIsSelected;
	}

	void TBusComponent::setHoveredStatus(const bool& IsHovered /*= true*/)
	{
		mIsHovered = IsHovered;
	}

	const bool& TBusComponent::isHovered() const
	{
		return mIsHovered;
	}

	void TBusComponent::confirmPoints()
	{
		// If we didn't enable the drawing return early
		if (!mEnableDraw)
			return;

		// Update the number of fixed point by validating the entire vertex array
		mFixedPoints = mDrawableComponent->getVertexArray().getVertexCount();

		// Add the last valid vertex in the array
		mVertices.push_back(mLastPointPosTemp);

		// The last point it's the last temp point
		mLastPointPos = mLastPointPosTemp;

		// Optimize the vertex vector by removing the uncessary vertices
		optimizeVertexArray();
	}

	void TBusComponent::adjustLine(const sf::Vector2f& Point1, const sf::Vector2f& Point2)
	{
		// Check if we are drawing an oblique line
		if (Point1.y != Point2.y)
		{
			// Establish in which verse we want to draw the intermediate line
			sf::Vector2f IntermediateLine = std::abs(Point1.x - Point2.x) < std::abs(Point1.y - Point2.y) ? sf::Vector2f(Point1.x, Point2.y) : sf::Vector2f(Point2.x, Point1.y);

			lineToQuad(Point1, IntermediateLine);
			lineToQuad(IntermediateLine, Point2);
		}
		else
		{
			lineToQuad(Point1, Point2);
		}
	}

	void TBusComponent::placePointTemp(const sf::Vector2f& PointPos)
	{
		// If we didn't enable the drawing return early
		if (!mEnableDraw)
			return;

		// Removes all the temp points
		mDrawableComponent->getVertexArray().resize(mFixedPoints);

		// If we didn't place any points yet, just draw a single point at the adjusted mouse coordinate.
		// Otherwise draw a line that goes from the position of the last point place to the adjusted mouse coordinate
		mFixedPoints == 0 ? placeInitialPoint(PointPos) : adjustLine(mLastPointPos, PointPos);
	}

	bool TBusComponent::checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd)
	{
		// Check if horizontal (return true)
		if (LineBegin.y == LineEnd.y)
			return true;

		return false;
	}

	void TBusComponent::renderWire()
	{
		// Clear the previous content of the vertex array
		mDrawableComponent->getVertexArray().clear();

		// Draw all the quad
		for (auto Index = 0u; Index < mVertices.size() - 1; ++Index)
			lineToQuad(mVertices[Index], mVertices[Index + 1]);
	}

	void TBusComponent::removeUnnecessaryVertices()
	{
		mVertices.erase(std::remove_if(std::begin(mVertices), std::end(mVertices),
			[](const sf::Vector2f& Vertex)
		{
			return Vertex == Unnecessary;
		}), std::end(mVertices));
	}

	void TBusComponent::optimizeVertexArray()
	{
		/*
		Removes unnecessary quads (from now on referred as vertex) in the vertex array. An unnecessary vertex it's a vertex that it's in the middle
		of 2 other vertices on the same x-axes or y-axes.

		Example:
		A	B	C
		.___.___.
		|
		. D
		|
		.___.
		E	F

		In the example above both B and D are unnecessary vertices and need to be removed.
		B it's on the same y-axes of A and C and in between them so it's unnecessary.
		D it's on the same x-axes of C and E and in between them so it's unnecessary.
		So at the end of the optimization the vertex array will look like this.

		A		C
		._______.
		|
		|
		|
		.___.
		E	F
		*/

		std::size_t CurrentVertex = 0;
		std::size_t NextVertex = 0;

		// Until we checked all the vertices
		while (NextVertex < mVertices.size() - 1)
		{
			// Increment what the next vertex is
			++NextVertex;

			// Compare the vertex pointed by CurrentVertex with the vertex pointed by NextVertex.
			// If they are on the same x-axes or y-axes skip the inside of the if statement and simply increment the next vertex to check out
			if (!(sameXAxes(mVertices[CurrentVertex], mVertices[NextVertex]) ||
				sameYAxes(mVertices[CurrentVertex], mVertices[NextVertex])))
			{
				// If the are not on the same x-axes or y-axes see if there is any vertices to remove
				// To find that out compute the indices 
				auto BeginIndex = CurrentVertex + 1;
				auto EndIndex = NextVertex - 1;

				if (BeginIndex != EndIndex)
				{
					// If there is vertices to remove
					for (auto Index = BeginIndex; Index < EndIndex; ++Index)
						mVertices[Index] = Unnecessary;
				}

				// Increment the current vertex to check and reset the value of NextVertex
				++CurrentVertex;
				NextVertex = CurrentVertex;
			}
		}

		// remove the vertices marked as unnecessary
		removeUnnecessaryVertices();

		// Transform the vertices in mVertices in quads in the vertex array
		renderWire();
	}

	bool TBusComponent::checkMouseClickOnWire(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && WireBound.contains(MousePos))
			return true;

		return false;
	}

	bool TBusComponent::checkMouseOverOnWire(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos)
	{
		if (WireBound.contains(MousePos))
			return true;

		return false;
	}

	void TBusComponent::adjustWireBound(sf::FloatRect& WireBound)
	{
		auto Width = std::abs(WireBound.width - WireBound.left);
		auto Height = std::abs(WireBound.height - WireBound.top);

		WireBound.width = Width;
		WireBound.height = Height;
	}

	void TBusComponent::shiftVerticesLeft(std::size_t BeginIndex, std::size_t EndIndex, std::size_t Steps)
	{
		// Get a ref to the vertex array
		auto& VertexArray = mDrawableComponent->getVertexArray();

		while (BeginIndex < EndIndex)
		{
			VertexArray[BeginIndex + 0] = VertexArray[BeginIndex + Steps + 0];
			VertexArray[BeginIndex + 1] = VertexArray[BeginIndex + Steps + 1];
			VertexArray[BeginIndex + 2] = VertexArray[BeginIndex + Steps + 2];
			VertexArray[BeginIndex + 3] = VertexArray[BeginIndex + Steps + 3];

			BeginIndex += 4;
		}
	}

	void TBusComponent::placeInitialPoint(const sf::Vector2f& PointPos)
	{
		auto& VertexArray = mDrawableComponent->getVertexArray();

		VertexArray.append({ { PointPos.x - (mThickness / 2.f), PointPos.y - (mThickness / 2.f) }, mWireColor });
		VertexArray.append({ { PointPos.x - (mThickness / 2.f), PointPos.y + (mThickness / 2.f) }, mWireColor });
		VertexArray.append({ { PointPos.x + (mThickness / 2.f), PointPos.y + (mThickness / 2.f) }, mWireColor });
		VertexArray.append({ { PointPos.x + (mThickness / 2.f), PointPos.y - (mThickness / 2.f) }, mWireColor });

		mLastPointPosTemp = PointPos;
	}

	void TBusComponent::lineToQuad(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd)
	{
		auto& VertexArray = mDrawableComponent->getVertexArray();

		// In case of horizontal alignment
		if (checkOrentation(LineBegin, LineEnd))
		{
			VertexArray.append({ { LineBegin.x, LineBegin.y - (mThickness / 2) }, mWireColor });
			VertexArray.append({ { LineBegin.x, LineBegin.y + (mThickness / 2) }, mWireColor });
			VertexArray.append({ { LineEnd.x, LineEnd.y + (mThickness / 2) }, mWireColor });
			VertexArray.append({ { LineEnd.x, LineEnd.y - (mThickness / 2) }, mWireColor });
		}
		// In case of vertical alignment
		else
		{
			VertexArray.append({ { LineBegin.x - (mThickness / 2), LineBegin.y }, mWireColor });
			VertexArray.append({ { LineBegin.x + (mThickness / 2), LineBegin.y }, mWireColor });
			VertexArray.append({ { LineEnd.x + (mThickness / 2), LineEnd.y }, mWireColor });
			VertexArray.append({ { LineEnd.x - (mThickness / 2), LineEnd.y }, mWireColor });
		}

		mLastPointPosTemp = LineEnd;
	}

	sf::FloatRect TBusComponent::extractQuad(const sf::Vertex* Vertices)
	{
		// Return value 
		sf::FloatRect ReturnValue;

		// First of all establish the quad orientation
		bool Horizontal = checkOrentation((Vertices + 0)->position, (Vertices + 3)->position);
		bool Verse = Horizontal ? (Vertices + 0)->position.x > (Vertices + 3)->position.x : (Vertices + 1)->position.y > (Vertices + 2)->position.y;

		ReturnValue = !Verse ? sf::FloatRect((Vertices + 0)->position, (Vertices + 2)->position) : sf::FloatRect((Vertices + 3)->position, (Vertices + 1)->position);

		return ReturnValue;
	}

	void TBusComponent::toggleDraw()
	{
		mEnableDraw = !mEnableDraw;

		// Removes all the temp points
		mDrawableComponent->getVertexArray().resize(mFixedPoints);
	}

	const bool& TBusComponent::isDrawing() const
	{
		return mEnableDraw;
	}

	void TBusComponent::connectEntryWire(TPin& PinToConnect)
	{
		//LOG_VALUE("We are connecting an entry wire number #" + std::to_string(PinToConnect.mPinNumber));
	}

	void TBusComponent::connectExitWire(TPin& PinToConnect)
	{
		//LOG_VALUE("We are connecting an exit wire number #" + std::to_string(PinToConnect.mPinNumber));
	}

	sf::FloatRect TBusComponent::getLocalBound()
	{
#if ENTITY_SYSTEM == NNE
		return mParent->getComponentAsPtr<TDrawableComponent>()->getLocalBounds();
#else
		return mParent->getComponent<TDrawableComponent>()->getLocalBounds();
#endif
	}

	sf::FloatRect TBusComponent::getGlobalBound()
	{
#if ENTITY_SYSTEM == NNE
		return mParent->getComponentAsPtr<TDrawableComponent>()->getGlobalBounds();
#else
		return mParent->getComponent<TDrawableComponent>()->getGlobalBounds();
#endif
	}

	sf::FloatRect TBusComponent::getSegmentLocalBound(const std::size_t SegmentNumber)
	{
#if ENTITY_SYSTEM == NNE
		auto& VertexArray = mParent->getComponentAsPtr<TDrawableComponent>()->getVertexArray();
#else
		auto& VertexArray = mParent->getComponent<TDrawableComponent>()->getVertexArray();
#endif

		return sf::FloatRect(VertexArray[SegmentNumber * 4 + 0].position.x, VertexArray[SegmentNumber * 4 + 0].position.y,
			VertexArray[SegmentNumber * 4 + 3].position.x, VertexArray[SegmentNumber * 4 + 3].position.y);
	}

	sf::FloatRect TBusComponent::getSegmentGlobalBound(const std::size_t SegmentNumber)
	{
#if ENTITY_SYSTEM == NNE
		return mParent->getComponentAsPtr<TDrawableComponent>()->getTransform().transformRect(getSegmentLocalBound(SegmentNumber));
#else
		return mParent->getComponent<TDrawableComponent>()->getTransform().transformRect(getSegmentLocalBound(SegmentNumber));
#endif
	}

}
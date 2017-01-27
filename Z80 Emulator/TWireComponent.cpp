#include "TWireComponent.h"

#include <SFML/Window/Mouse.hpp>


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

	const sf::Color TWireComponent::WireColorNormal = { 3, 81, 121 };
	const sf::Color TWireComponent::WireColorHover = { 1, 40, 60 };
	const sf::Color TWireComponent::WireColorSelected = { 1, 20, 30 };
				
	const sf::Color TWireComponent::WireColorStatusLow = { 120, 0, 0 };
	const sf::Color TWireComponent::WireColorStatusHigh = { 0, 120, 0 };
	const sf::Color TWireComponent::WireColorStatusHighZ = { 0, 0, 128 };

	const sf::Vector2f Unnecessary = { std::numeric_limits<float>::min(), std::numeric_limits<float>::max() };

	TWireComponent::TWireComponent() :
		mDrawableComponent(nullptr),
		mFixedPoints(0u),
		mThickness(3.f),
		mJunctionThickness(9.f),
		mEnableDraw(false),
		mIsSelected(false),
		mLastPointPos(0.f, 0.f),
		mLastPointPosTemp(0.f, 0.f),
		mMidPointPosTemp(InvalidVector<float>),
		mWireColor(WireColorNormal)
	{
	}

	void TWireComponent::update(const sf::Time& ElapsedTime)
	{
		// If we didn't enable the drawing return early
		if (mEnableDraw)
			return;

		// Get a ref to the vertex array
		auto& VertexArray = mDrawableComponent->getVertexArray();
		auto VerticesNumber = VertexArray.getVertexCount();

		// We this wire doesn't have any vertices skip the update function
		if (!VerticesNumber)
			return;
		
		// Update the color of the wire if we are hovering it and we didn't do it already
		if (mIsHovered && mDrawableComponent->getColor() != WireColorHover)
		{
			for (auto VIndex = 0u; VIndex < VerticesNumber; ++VIndex)
				VertexArray[VIndex].color = WireColorHover;
		}
		// Update the color of the wire if we selected it and we didn't do it already
		else if (!mIsHovered && mIsSelected && mDrawableComponent->getColor() != WireColorSelected)
		{
			// Change the color of all the vertices in the vertex array
			for (auto VIndex = 0u; VIndex < VerticesNumber; ++VIndex)
				VertexArray[VIndex].color = WireColorSelected;
		}
		// Reset the color of the wire to is normal color if we didn't do it already
		else if (!mIsSelected && !mIsHovered && mDrawableComponent->getColor() != WireColorNormal)
		{
			for (auto VIndex = 0u; VIndex < VerticesNumber; ++VIndex)
				VertexArray[VIndex].color = WireColorNormal;
		}

	}

	void TWireComponent::refresh(const sf::Time& ElapsedTime)
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
		auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>();

		// Get a ref to the sf::RenderWindow
		auto& RenderWindow = mParent->getParentScene()->getRenderWindow();

		// Get mouse info
		auto MousePositionAdj = mParent->getComponent<tcomponents::TEventComponent>().getMousePosition();

		// Execute the WIRE check only if we clicked or we are hovering the chip
		auto ComponentState = mParent->getComponent<tcomponents::TStateComponent>().getState();

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
				LogicBoard.setSelectedWire(this);

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

		// If we arrive at this point maybe we have to deselect the chip
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
// 			if (LogicBoard.getSelectedWire() == this)
// 				LogicBoard.deselectWire();
			if (LogicBoard.getSelectedWire() == this)
				LogicBoard.deselectWire();
		}
	}

	void TWireComponent::init()
	{
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();
		mDrawableComponent->getVertexArray().setPrimitiveType(sf::Quads);
	}

	void TWireComponent::setThickness(const float& Thickness)
	{
		mThickness = Thickness;

		renderWire();
	}

	const float& TWireComponent::getThickness() const
	{
		return mThickness;
	}

	void TWireComponent::setSelectedStatus(const bool& IsSelected /*= true*/)
	{
		mIsSelected = IsSelected;
	}

	const bool& TWireComponent::isSelected() const
	{
		return mIsSelected;
	}

	void TWireComponent::setHoveredStatus(const bool& IsHovered /*= true*/)
	{
		mIsHovered = IsHovered;
	}

	const bool& TWireComponent::isHovered() const
	{
		return mIsHovered;
	}

	void TWireComponent::confirmPoints()
	{
		// If we didn't enable the drawing return early
		if (!mEnableDraw)
			return;

		// Update the number of fixed point by validating the entire vertex array
		mFixedPoints = mDrawableComponent->getVertexArray().getVertexCount();

		// If we have a mid point
		if (mMidPointPosTemp != InvalidVector<float>)
		{
			mVertices.push_back(mMidPointPosTemp);
			mMidPointPosTemp = InvalidVector<float>;
		}

		// Add the last valid vertex in the array
		mVertices.push_back(mLastPointPosTemp);

		// The last point it's the last temp point
		mLastPointPos = mLastPointPosTemp;

		// Optimize the vertex vector by removing the uncessary vertices
		optimizeVertexArray();
	}

	void TWireComponent::connectPins(TPin& LeftPin, TPin& RightPin)
	{
		mPins.push_back(LeftPin);
		mPins.push_back(RightPin);
	}

	void TWireComponent::adjustLine(const sf::Vector2f& Point1, const sf::Vector2f& Point2)
	{
		// Check if we are drawing an oblique line
		if (Point1.y != Point2.y)
		{
			// Establish in which verse we want to draw the intermediate line
			sf::Vector2f IntermediateLine = std::abs(Point1.x - Point2.x) < std::abs(Point1.y - Point2.y) ? sf::Vector2f(Point1.x, Point2.y) : sf::Vector2f(Point2.x, Point1.y);

			lineToQuad(Point1, IntermediateLine);
			lineToQuad(IntermediateLine, Point2);

			mMidPointPosTemp = IntermediateLine;
		}
		else
		{
			lineToQuad(Point1, Point2);
		}

		mLastPointPosTemp = Point2;
	}

	nne::TPinList& TWireComponent::getPinList()
	{
		return mPins;
	}

	const nne::TPinList& TWireComponent::getPinList() const
	{
		return mPins;
	}

	const std::vector<sf::Vector2f>& TWireComponent::getVerticesVector() const
	{
		return mVertices;
	}

	const std::vector<sf::Vector2f>& TWireComponent::getJunctionsVector() const
	{
		return mJunctions;
	}

	void TWireComponent::placePointTemp(const sf::Vector2f& PointPos)
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

	void TWireComponent::placeJunction(const sf::Vector2f& PointPos)
	{
		mJunctions.push_back(PointPos);

		// Transform the vertices in mVertices in quads in the vertex array
		renderWire();
	}

	bool TWireComponent::checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd)
	{
		// Check if horizontal (return true)
		if (LineBegin.y == LineEnd.y)
			return true;

		return false;
	}

	void TWireComponent::renderWire()
	{
		if (mVertices.size() == 0)
			return;

		// Clear the previous content of the vertex array
		mDrawableComponent->getVertexArray().clear();

		// Draw all the quad
		for (auto Index = 0u; Index < mVertices.size() - 1; ++Index)
			lineToQuad(mVertices[Index], mVertices[Index + 1]);

		if (mJunctions.size() == 0)
			return;

		for (auto Index = 0u; Index < mJunctions.size(); ++Index)
			pointToJunction(mJunctions[Index] + sf::Vector2f(1.f, 0.f));
	}

	void TWireComponent::removeUnnecessaryVertices()
	{
		mVertices.erase(std::remove_if(std::begin(mVertices), std::end(mVertices),
			[](const sf::Vector2f& Vertex)
		{
			return Vertex == Unnecessary;
		}), std::end(mVertices));
	}

	void TWireComponent::optimizeVertexArray()
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

	bool TWireComponent::checkMouseClickOnWire(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && WireBound.contains(MousePos))
			return true;

		return false;
	}

	bool TWireComponent::checkMouseOverOnWire(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos)
	{
		if (WireBound.contains(MousePos))
			return true;

		return false;
	}

	void TWireComponent::adjustWireBound(sf::FloatRect& WireBound)
	{
		auto Width = std::abs(WireBound.width - WireBound.left);
		auto Height = std::abs(WireBound.height - WireBound.top);

		WireBound.width = Width;
		WireBound.height = Height;
	}

	void TWireComponent::shiftVerticesLeft(std::size_t BeginIndex, std::size_t EndIndex, std::size_t Steps)
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

	void TWireComponent::placeInitialPoint(const sf::Vector2f& PointPos)
	{
		auto& VertexArray = mDrawableComponent->getVertexArray();

		VertexArray.append({ { PointPos.x - (mThickness / 2.f), PointPos.y - (mThickness / 2.f) }, mWireColor });
		VertexArray.append({ { PointPos.x - (mThickness / 2.f), PointPos.y + (mThickness / 2.f) }, mWireColor });
		VertexArray.append({ { PointPos.x + (mThickness / 2.f), PointPos.y + (mThickness / 2.f) }, mWireColor });
		VertexArray.append({ { PointPos.x + (mThickness / 2.f), PointPos.y - (mThickness / 2.f) }, mWireColor });

		mLastPointPosTemp = PointPos;
	}

	void TWireComponent::lineToQuad(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd)
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
			VertexArray.append({ { LineBegin.x - (mThickness / 2) + 1.f, LineBegin.y }, mWireColor });
			VertexArray.append({ { LineBegin.x + (mThickness / 2) + 1.f, LineBegin.y }, mWireColor });
			VertexArray.append({ { LineEnd.x + (mThickness / 2) + 1.f, LineEnd.y }, mWireColor });
			VertexArray.append({ { LineEnd.x - (mThickness / 2) + 1.f, LineEnd.y }, mWireColor });
		}
	}

	void TWireComponent::pointToJunction(const sf::Vector2f& Point)
	{
		auto& VertexArray = mDrawableComponent->getVertexArray();

		VertexArray.append({ { Point.x - (mJunctionThickness / 2.f), Point.y - (mJunctionThickness / 2.f) }, mWireColor });
		VertexArray.append({ { Point.x - (mJunctionThickness / 2.f), Point.y + (mJunctionThickness / 2.f) }, mWireColor });
		VertexArray.append({ { Point.x + (mJunctionThickness / 2.f), Point.y + (mJunctionThickness / 2.f) }, mWireColor });
		VertexArray.append({ { Point.x + (mJunctionThickness / 2.f), Point.y - (mJunctionThickness / 2.f) }, mWireColor });
	}

	sf::FloatRect TWireComponent::extractQuad(const sf::Vertex* Vertices)
	{
		// Return value 
		sf::FloatRect ReturnValue;

		// First of all establish the quad orientation
		bool Horizontal = checkOrentation((Vertices + 0)->position, (Vertices + 3)->position);
		bool Verse = Horizontal ? (Vertices + 0)->position.x > (Vertices + 3)->position.x : (Vertices + 1)->position.y > (Vertices + 2)->position.y;

		ReturnValue = !Verse ? sf::FloatRect((Vertices + 0)->position, (Vertices + 2)->position) : sf::FloatRect((Vertices + 3)->position, (Vertices + 1)->position);

		return ReturnValue;
	}

	void TWireComponent::toggleDraw()
	{
		mEnableDraw = !mEnableDraw;

		// Removes all the temp points
		mDrawableComponent->getVertexArray().resize(mFixedPoints);
	}

	const bool& TWireComponent::isDrawing() const
	{
		return mEnableDraw;
	}

	sf::FloatRect TWireComponent::getLocalBound()
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getLocalBounds();
	}

	sf::FloatRect TWireComponent::getGlobalBound()
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getGlobalBounds();
	}

	sf::FloatRect TWireComponent::getSegmentLocalBound(const std::size_t SegmentNumber)
	{
		auto& VertexArray = mParent->getComponentAsPtr<TDrawableComponent>()->getVertexArray();

		return sf::FloatRect(VertexArray[SegmentNumber * 4 + 0].position.x, VertexArray[SegmentNumber * 4 + 0].position.y,
			VertexArray[SegmentNumber * 4 + 3].position.x, VertexArray[SegmentNumber * 4 + 3].position.y);
	}

	sf::FloatRect TWireComponent::getSegmentGlobalBound(const std::size_t SegmentNumber)
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getTransform().transformRect(getSegmentLocalBound(SegmentNumber));
	}

}
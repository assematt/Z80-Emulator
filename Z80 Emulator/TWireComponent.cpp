#include "TWireComponent.h"

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

	const sf::Color TWireComponent::WireColorNormal = { 3, 81, 121 };
	const sf::Color TWireComponent::WireColorHover = { 1, 40, 60 };
	const sf::Color TWireComponent::WireColorSelected = { 1, 20, 30 };
				
	const sf::Color TWireComponent::WireColorStatusLow = { 120, 0, 0 };
	const sf::Color TWireComponent::WireColorStatusHigh = { 0, 120, 0 };
	const sf::Color TWireComponent::WireColorStatusHighZ = { 0, 0, 128 };

	const sf::Vector2f Unnecessary = { std::numeric_limits<float>::min(), std::numeric_limits<float>::max() };

	std::vector<TWireComponent*> TWireComponent::mWireVectors;

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
		mWireVectors.push_back(this);
	}

	TWireComponent::~TWireComponent()
	{
		auto It = std::find(mWireVectors.cbegin(), mWireVectors.cend(), this);

		if (It != mWireVectors.cend())
			mWireVectors.erase(It);
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
		auto& LogicBoard = mParent->getComponent<TLogicBoardComponent>().getBoard();

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
			if (checkMouseClickOnWireSegment(Quad, MousePositionAdj))
			{
				// Inform the logic board component that we selected this wire
				LogicBoard.setSelectedComponent<TWireComponent>(this);

				// Change the selection status of this wire
				setSelectedStatus(true);

				// This function had done it's job we can exit now
				return;
			} 
			// If we are just hovering on the wire
			else if (checkMouseOverOnWireSegment(Quad, MousePositionAdj))
			{
				// Change the selection status of this wire
				setHoveredStatus(true);

				// This function had done it's job we can exit now
				return;
			}
		}

		// If we arrive at this point maybe we have to deselect the chip
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (LogicBoard.getSelectedComponent<TWireComponent>() == this)
				LogicBoard.deselectComponent<TWireComponent>();
		}
	}

	void TWireComponent::init()
	{
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();
		mDrawableComponent->getVertexArray().setPrimitiveType(sf::Quads);
	}

	void TWireComponent::setWireName(const std::string& Name)
	{
		mWireName = Name;
	}

	const std::string& TWireComponent::getWireName() const
	{
		return mWireName;
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

		// Optimize the vertex vector by removing the unnecessary vertices
		optimizeVertexArray();
	}

	void TWireComponent::connectPin(TPin& RightPin)
	{
		// Add the pin in the wire
		mConnectedPins.insert(&RightPin);

		// Connect this pin with all the other pin in the wire, if we have some
		for (auto ConnectedWire : mConnectedWires)
			for (auto LeftPin : ConnectedWire->getConnectedPins())
			{
				/// FUTURE FIX
				/*for (auto ConnectedPin : LeftPin->getPinConnections())
					TPinComponentUtility::connectPins(*LeftPin, *ConnectedPin);*/

				TPinComponentUtility::connectPins(*LeftPin, RightPin);
			}
	}

	void TWireComponent::connectPins(TPin& LeftPin, TPin& RightPin)
	{
		if (LeftPin == RightPin)
			return;

		// Add the 2 pins in the wire
		mConnectedPins.insert(&LeftPin);
		mConnectedPins.insert(&RightPin);
				
		// Connect the 2 pin with each other...
		TPinComponentUtility::connectPins(LeftPin, RightPin);

		// ... and the other pins connected to the wire
		for (auto ConnectedWire : mConnectedWires)
			for (auto OtherPin : ConnectedWire->getConnectedPins())
			{
				/// FUTURE FIX
				/*for (auto ConnectedPin : OtherPin->getPinConnections())
				{
					TPinComponentUtility::connectPins(LeftPin, *ConnectedPin);
					TPinComponentUtility::connectPins(RightPin, *ConnectedPin);
				}*/

				TPinComponentUtility::connectPins(LeftPin, *OtherPin);
				TPinComponentUtility::connectPins(RightPin, *OtherPin);
			}
	}

	void TWireComponent::disconnectPin(TPin& RightPin)
	{
		// Remove the pin from the list of pin connected to the wire 
		mConnectedPins.erase(&RightPin);
	}

	void TWireComponent::disconnectPins(TPin& LeftPin, TPin& RightPin)
	{
		if (LeftPin == RightPin)
			return;

		// Remove the pins
		mConnectedPins.erase(&LeftPin);
		mConnectedPins.erase(&RightPin);
	}

	void TWireComponent::connectWire(TWireComponent* Wire)
	{
		// Add the wire connection
		this->mConnectedWires.insert(Wire);
		Wire->mConnectedWires.insert(this);

		// Connect all the pin in this wire with other pin in the wire
		for (auto LeftPin : mConnectedPins)
			for (auto ConnectedWire : mConnectedWires)
				for (auto ConnectedPin : ConnectedWire->getConnectedPins())
				{
					/// FUTURE FIX
					/*for (auto RightPin : ConnectedPin->getPinConnections())
						TPinComponentUtility::connectPins(*LeftPin, *RightPin);*/

					TPinComponentUtility::connectPins(*LeftPin, *ConnectedPin);
				}
	}

	void TWireComponent::disconnectWire()
	{
		// Remove this wire from his connection
		std::for_each(mConnectedWires.begin(), mConnectedWires.end(), [&](TWireComponent* Wire) {
			// Remove the junction with this wire and render it
			Wire->removeJunction(this);
			Wire->renderWire();

			// Remove this wire from the list of connected wire
			Wire->mConnectedWires.erase(this);
		});
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

	TWireComponent::TPinConnections& TWireComponent::getConnectedPins()
	{
		return mConnectedPins;
	}

	const TWireComponent::TPinConnections& TWireComponent::getConnectedPins() const
	{
		return mConnectedPins;
	}

	bool TWireComponent::hasConnectedPins() const
	{
		return !mConnectedPins.empty();
	}

	bool TWireComponent::hasConnectedWires() const
	{
		return !mConnectedWires.empty();
	}

	nne::TWireComponent::TWireConnections& TWireComponent::getConnectedWires()
	{
		return mConnectedWires;
	}

	const nne::TWireComponent::TWireConnections& TWireComponent::getConnectedWires() const
	{
		return mConnectedWires;
	}

	const std::vector<sf::Vector2f>& TWireComponent::getVerticesVector() const
	{
		return mVertices;
	}

	const std::vector<nne::TWireComponent::TJunction>& TWireComponent::getJunctionsVector() const
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

	void TWireComponent::placeJunction(const sf::Vector2f& PointPos, TWireComponent* Wire)
	{
		mJunctions.push_back({PointPos, Wire });

		// Transform the vertices in mVertices in quads in the vertex array
		renderWire();
	}

	bool TWireComponent::checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd) const
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
			pointToJunction(mJunctions[Index].first + sf::Vector2f(1.f, 0.f));
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

	bool TWireComponent::checkMouseClickOnWireSegment(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos) const
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && WireBound.contains(MousePos))
			return true;

		return false;
	}

	bool TWireComponent::checkMouseOverOnWireSegment(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos) const
	{
		if (WireBound.contains(MousePos))
			return true;

		return false;
	}

	void TWireComponent::adjustWireBound(sf::FloatRect& WireBound) const
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

	sf::FloatRect TWireComponent::extractQuad(const sf::Vertex* Vertices) const
	{
		// Return value 
		sf::FloatRect ReturnValue;

		// First of all establish the quad orientation
		bool Horizontal = checkOrentation((Vertices + 0)->position, (Vertices + 3)->position);
		bool Verse = Horizontal ? (Vertices + 0)->position.x > (Vertices + 3)->position.x : (Vertices + 1)->position.y > (Vertices + 2)->position.y;

		ReturnValue = !Verse ? sf::FloatRect((Vertices + 0)->position, (Vertices + 2)->position) : sf::FloatRect((Vertices + 3)->position, (Vertices + 1)->position);

		return ReturnValue;
	}

	void TWireComponent::removeJunction(const sf::Vector2f& PointPos)
	{
		auto It = std::find_if(mJunctions.begin(), mJunctions.end(), [&] (const TJunction& Junction) {
			return Junction.first == PointPos;
		});

		if (It != mJunctions.end())
			mJunctions.erase(It);
	}

	void TWireComponent::removeJunction(TWireComponent* Wire)
	{
		auto It = std::find_if(mJunctions.begin(), mJunctions.end(), [&](const TJunction& Junction) {
			return Junction.second == Wire;
		});

		if (It != mJunctions.end())
			mJunctions.erase(It);
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

	bool TWireComponent::checkMouseOverWire(const sf::Vector2f& MousePos) const
	{
		// Get a ref to the vertex array
		auto& VertexArray = mDrawableComponent->getVertexArray();
		auto VerticesNumber = VertexArray.getVertexCount();

		// Iterates through all the quads
		for (auto Index = 0u; Index < VerticesNumber; Index += 4)
		{
			// Get the quad bounding box and adjust it
			sf::FloatRect Segment = extractQuad(&VertexArray[Index]);
			adjustWireBound(Segment);

			if (checkMouseOverOnWireSegment(Segment, MousePos))
				return true;
		}

		return false;
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

	TWireComponent* TWireComponent::getWireByID(const TComponentID& ID)
	{
		auto It = std::find_if(mWireVectors.cbegin(), mWireVectors.cend(), [&] (const TWireComponent* Wire) {
			return Wire->getComponentID() == ID;
		});

		if (It != mWireVectors.cend())
			return *It;

		return nullptr;
	}

	TWireComponent * TWireComponent::getWireByName(const std::string& WireName)
	{
		auto It = std::find_if(mWireVectors.cbegin(), mWireVectors.cend(), [&](const TWireComponent* Wire) {
			return Wire->mWireName == WireName;
		});

		if (It != mWireVectors.cend())
			return *It;

		return nullptr;
	}

	const std::vector<TWireComponent*> TWireComponent::getGlobalWireVector()
	{
		return mWireVectors;
	}


}
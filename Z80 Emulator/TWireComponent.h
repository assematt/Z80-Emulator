#pragma once

#include <unordered_set>
#include <utility>
#include <memory>
#include <vector>
#include <set>

#include "TDrawableComponent.h"
#include "TPinComponent.h"
#include INCLUDE_COMPONENT_CLASS
#include INCLUDE_ENTITY_CLASS

namespace nne
{
	class TBoard;

	class TWireComponent : BASE_COMPONENT_CLASS
	{
	public:

		static const sf::Color WireColorNormal;
		static const sf::Color WireColorHover;
		static const sf::Color WireColorSelected;

		static const sf::Color WireColorStatusLow;
		static const sf::Color WireColorStatusHigh;
		static const sf::Color WireColorStatusHighZ;
		
		using TPinConnections = std::set<TPin*>;
		using TWireConnections = std::set<TWireComponent*>;
		using TJunction = std::pair<sf::Vector2f, TWireComponent*>;

		/// constructor
		TWireComponent();
		~TWireComponent();
			
		virtual void update(REFRESH_UPDATE_PARAMETER) override;

		virtual void refresh(REFRESH_UPDATE_PARAMETER) override;

		virtual void init() override;

		/// Set/Get wire name
		void setWireName(const std::string& Name);
		const std::string& getWireName() const;

		/// Set/Get the wire thickness
		void setThickness(const float& Thickness);
		const float& getThickness() const;

		/// Set/Get the selection status of this wire
		void setSelectedStatus(const bool& IsSelected = true);
		const bool& isSelected() const;

		/// Set/Get the hover status of this wire
		void setHoveredStatus(const bool& IsHovered = true);
		const bool& isHovered() const;

		/// place a fixed point
		void confirmPoints();

		/// Add a single connected pin
		void connectPin(TPin& RightPin);

		/// Add the 2 pin connected by the wire
		void connectPins(TPin& LeftPin, TPin& RightPin);

		/// Add a single connected pin
		void disconnectPin(TPin& RightPin);

		/// Disconnect the 2 pin connected by the wire
		void disconnectPins(TPin& LeftPin, TPin& RightPin);

		/// Connect this wire with another wire
		void connectWire(TWireComponent* Wire);

		/// Disconnect this wire with another wire
		void disconnectWire();

		/// Get the pin list
		TPinConnections& getConnectedPins();
		const TPinConnections& getConnectedPins() const;

		/// Return true if we have some pins connected
		bool hasConnectedPins() const;

		/// Return false if we have some pins connected
		bool hasConnectedWires() const;

		/// Get the wire list
		TWireConnections& getConnectedWires();
		const TWireConnections& getConnectedWires() const;

		/// Get the vertices ready only vector
		const std::vector<sf::Vector2f>& getVerticesVector() const;

		/// Get the junctions ready only vector
		const std::vector<TJunction>& getJunctionsVector() const;

		/// place a temp point
		void placePointTemp(const sf::Vector2f& PointPos);

		/// Place a junction point
		void placeJunction(const sf::Vector2f& PointPos, TWireComponent* Wire);

		/// Remove a junction point
		void removeJunction(const sf::Vector2f& PointPos);
		void removeJunction(TWireComponent* Wire);
		
		/// Toggle the ability to draw the wire
		void toggleDraw();

		/// Return the number of placed point
		const bool& isDrawing() const;

		/// Check if the mouse it's above the wire
		bool checkMouseOverWire(const sf::Vector2f& MousePos) const;

		/// Get the bound of the wire
		sf::FloatRect getLocalBound();
		sf::FloatRect getGlobalBound();

		/// Get the bound of a single segment of the wire
		sf::FloatRect getSegmentLocalBound(const std::size_t SegmentNumber);
		sf::FloatRect getSegmentGlobalBound(const std::size_t SegmentNumber);

	/// STATIC FUNCTION
	public:
		/// Get a wire by ID or by name
#if ENTITY_SYSTEM == NNE
		static TWireComponent* getWireByID(const TComponentID& ID);
#else
		static TWireComponent* getWireByID(const ecs::_IComponent::ID& ID);
#endif
		
		static TWireComponent* getWireByName(const std::string& WireName);

		/// Get the wire vector
		static const std::vector<TWireComponent*> getGlobalWireVector();

	private:
		static std::vector<TWireComponent*>	mWireVectors;

	private:
		/// Convert two points to a quad
		void lineToQuad(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);

		/// Convert a point in a junction point
		void pointToJunction(const sf::Vector2f& Point);

		/// Convert a quad to two points
		sf::FloatRect extractQuad(const sf::Vertex* Vertices) const;

		/// Put a single point in the vertex array
		void placeInitialPoint(const sf::Vector2f& PointPos);
		
		/// Adjust the oblique line to be a combination of an horizontal + vertical lines
		void adjustLine(const sf::Vector2f& Point1, const sf::Vector2f& Point2);

		/// Check the orientation of the lines we want to draw
		bool checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd) const;

		/// Optimize the vertex array removing the unnecessary vertices
		void optimizeVertexArray();

		/// Render the wire
		void renderWire();

		/// Remove all the vertices that we marked as unnecessary by the optimizeVertexArray() function
		void removeUnnecessaryVertices();
		
		/// Check if we clicked on a wire
		bool checkMouseClickOnWireSegment(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos) const;

		/// Check if we are hovering a wire
		bool checkMouseOverOnWireSegment(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos) const;

		/// Because the wire size can be negative due to the fact vertex array data is relative to the main view we have to do some math to figure out the wire real size
		void adjustWireBound(sf::FloatRect& WireBound) const;

		/// Shift the vertex array left by a specified amount
		void shiftVerticesLeft(std::size_t BeginIndex, std::size_t EndIndex, std::size_t Steps);

		/// Connect pins
		void connectWireAndPins(TWireComponent* Wire, TPin* Pin);

	private:
		bool						mEnableDraw;
		bool						mIsSelected;
		bool						mIsHovered;
		float						mThickness;
		float						mJunctionThickness;
		sf::Color					mWireColor;
		std::string					mWireName;
		std::size_t					mFixedPoints;

		TPinConnections				mConnectedPins;
		TWireConnections			mConnectedWires;

		sf::Vector2f				mLastPointPos;
		sf::Vector2f				mMidPointPosTemp;
		sf::Vector2f				mLastPointPosTemp;

		TDrawableComponent*			mDrawableComponent;
		std::vector<sf::Vector2f>	mVertices;
		std::vector<TJunction>		mJunctions;

		friend class TBoard;
	};
}
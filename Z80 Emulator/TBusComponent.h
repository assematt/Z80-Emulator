#pragma once

#include <memory>
#include <vector>

#include "TPinComponent.h"
#include INCLUDE_COMPONENT_CLASS
#include "TDrawableComponent.h"
#include "TWireComponent.h"
#include INCLUDE_ENTITY_CLASS

namespace nne
{

	using namespace tcomponents;

	class TBusComponent : BASE_COMPONENT_CLASS
	{
	public:

		static const sf::Color BusColorNormal;
		static const sf::Color BusColorHover;
		static const sf::Color BusColorSelected;

		static const sf::Color BusColorStatusLow;
		static const sf::Color BusColorStatusHigh;
		static const sf::Color BusColorStatusHighZ;

		/// constructor
		TBusComponent();
		virtual ~TBusComponent() = default;

		virtual void update(REFRESH_UPDATE_PARAMETER) override;

		virtual void refresh(REFRESH_UPDATE_PARAMETER) override;

		virtual void init() override;

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

		/// place a temp point
		void placePointTemp(const sf::Vector2f& PointPos);

		/// Toggle the ability to draw the wire
		void toggleDraw();

		/// Return the number of placed point
		const bool& isDrawing() const;

		/// Connect a wire from a chip/another wire to the bus (so we can assume it's entering the wire)
		void connectEntryWire(TPin& PinToConnect);

		/// Connect a wire from the bus to a chip/another wire (so we can assume it's exiting the wire)
		void connectExitWire(TPin& PinToConnect);

		/// Get the bound of the wire
		sf::FloatRect getLocalBound();
		sf::FloatRect getGlobalBound();

		/// Get the bound of a single segment of the wire
		sf::FloatRect getSegmentLocalBound(const std::size_t SegmentNumber);
		sf::FloatRect getSegmentGlobalBound(const std::size_t SegmentNumber);

	private:
		/// Convert two points to a quad
		void lineToQuad(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);

		/// Convert a quad to two points
		sf::FloatRect extractQuad(const sf::Vertex* Vertices);

		/// Put a single point in the vertex array
		void placeInitialPoint(const sf::Vector2f& PointPos);

		/// Adjust the oblique line to be a combination of an horizontal + vertical lines
		void adjustLine(const sf::Vector2f& Point1, const sf::Vector2f& Point2);

		/// Check the orientation of the lines we want to draw
		bool checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);

		/// Optimize the vertex array removing the unnecessary vertices
		void optimizeVertexArray();

		/// Render the wire
		void renderWire();

		/// Remove all the vertices that we marked as unnecessary by the optimizeVertexArray() function
		void removeUnnecessaryVertices();

		/// Check if we clicked on a wire
		bool checkMouseClickOnWire(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos);

		/// Check if we are hovering a wire
		bool checkMouseOverOnWire(const sf::FloatRect& WireBound, const sf::Vector2f& MousePos);

		/// Because the wire size can be negative due to the fact vertex array data is relative to the main view we have to do some math to figure out the wire real size
		void adjustWireBound(sf::FloatRect& WireBound);

		/// Shift the vertex array left by a specified amount
		void shiftVerticesLeft(std::size_t BeginIndex, std::size_t EndIndex, std::size_t Steps);

	private:
		bool						mEnableDraw;
		bool						mIsSelected;
		bool						mIsHovered;
		float						mThickness;
		sf::Color					mWireColor;
		std::size_t					mFixedPoints;
		sf::Vector2f				mLastPointPos;
		sf::Vector2f				mLastPointPosTemp;
		TDrawableComponent*			mDrawableComponent;
		std::vector<sf::Vector2f>	mVertices;

		std::vector<TPin>			mEntryWires;
		std::vector<TPin>			mExitWires;
	};
}
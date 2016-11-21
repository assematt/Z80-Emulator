#include "TConductiveTracks.h"

namespace nne
{

	TConductiveTracks::TConductiveTracks() :
		mTrackThickness(4.f)
	{

	}

	void TConductiveTracks::update(const sf::Time& ElapsedTime)
	{

	}

	void TConductiveTracks::refresh(const sf::Time& ElapsedTime)
{

	}

	void TConductiveTracks::init()
	{
		mVertexArray = std::make_shared<sf::VertexArray>(sf::Quads);
		//mParent->getComponentAsPtr<TDrawableVector>()->pushdrawableObject({ mVertexArray });

		auto& VertexArray = *mVertexArray;

		const std::size_t SegmentNumber = 3;

		// The vertex array size is corrisponded to the number of segment * 4 (to make a rectangleshape)
		VertexArray.resize(SegmentNumber * 4);

		lineToRectangleShape({ 100.f, 50.f }, { 250.f, 50.f }, 0);
		lineToRectangleShape({ 250.f, 50.f }, { 250.f, 500.f }, 1);
		lineToRectangleShape({ 250.f, 500.f }, { 60.f, 500.f }, 2);
	}

	bool TConductiveTracks::checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd)
	{
		// Check if horizontal (return true)
		if (LineBegin.y == LineEnd.y)
			return true;

		return false;
	}

	void TConductiveTracks::lineToRectangleShape(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd, const std::size_t SegmentNumber)
	{
		auto& VertexArray = *mVertexArray;

		// In case of horizontal alignment
		if (checkOrentation(LineBegin, LineEnd))
		{
			VertexArray[SegmentNumber * 4 + 0] = { { LineBegin.x, LineBegin.y - (mTrackThickness / 2) }, sf::Color::Red };
			VertexArray[SegmentNumber * 4 + 1] = { { LineBegin.x, LineBegin.y + (mTrackThickness / 2) }, sf::Color::Red };
			VertexArray[SegmentNumber * 4 + 2] = { { LineEnd.x, LineEnd.y + (mTrackThickness / 2) }, sf::Color::Red };
			VertexArray[SegmentNumber * 4 + 3] = { { LineEnd.x, LineEnd.y - (mTrackThickness / 2) }, sf::Color::Red };
		}
		// In case of vertical alignment
		else
		{
			VertexArray[SegmentNumber * 4 + 0] = { { LineBegin.x - (mTrackThickness / 2), LineBegin.y }, sf::Color::Red };
			VertexArray[SegmentNumber * 4 + 1] = { { LineBegin.x + (mTrackThickness / 2), LineBegin.y }, sf::Color::Red };
			VertexArray[SegmentNumber * 4 + 2] = { { LineEnd.x + (mTrackThickness / 2), LineEnd.y }, sf::Color::Red };
			VertexArray[SegmentNumber * 4 + 3] = { { LineEnd.x - (mTrackThickness / 2), LineEnd.y }, sf::Color::Red };
		}
	}

}
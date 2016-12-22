#include "TConductiveTracks.h"

namespace nne
{

	TConductiveTracks::TConductiveTracks() :
		mDrawableComponent(nullptr),
		mFixedPoints(0u),
		mThickness(4.f),
		mEnableDraw(false),
		mLastPointPos(0.f, 0.f),
		mLastPointPosTemp(0.f, 0.f),
		mTrackColor({ 3, 81, 121 })
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
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();
		mDrawableComponent->getVertexArray().setPrimitiveType(sf::Quads);
	}

	void TConductiveTracks::confirmPoints()
	{
		// If we didn't enable the drawing return early
		if (!mEnableDraw)
			return;

		// Update the number of fixed point by validating the entire vertex array
		mFixedPoints = mDrawableComponent->getVertexArray().getVertexCount();

		// The last point it's the last temp point
		mLastPointPos = mLastPointPosTemp;
	}

	void TConductiveTracks::adjustLine(const sf::Vector2f& Point1, const sf::Vector2f& Point2)
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

	void TConductiveTracks::placePointTemp(const sf::Vector2f& PointPos)
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

	bool TConductiveTracks::checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd)
	{
		// Check if horizontal (return true)
		if (LineBegin.y == LineEnd.y)
			return true;

		return false;
	}

	void TConductiveTracks::placeInitialPoint(const sf::Vector2f& PointPos)
	{
		auto& VertexArray = mDrawableComponent->getVertexArray();

		VertexArray.append({ { PointPos.x - (mThickness / 2.f), PointPos.y - (mThickness / 2.f) }, mTrackColor });
		VertexArray.append({ { PointPos.x - (mThickness / 2.f), PointPos.y + (mThickness / 2.f) }, mTrackColor });
		VertexArray.append({ { PointPos.x + (mThickness / 2.f), PointPos.y + (mThickness / 2.f) }, mTrackColor });
		VertexArray.append({ { PointPos.x + (mThickness / 2.f), PointPos.y - (mThickness / 2.f) }, mTrackColor });

		mLastPointPosTemp = PointPos;
	}

	void TConductiveTracks::lineToQuad(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd)
	{
		auto& VertexArray = mDrawableComponent->getVertexArray();

		// In case of horizontal alignment
		if (checkOrentation(LineBegin, LineEnd))
		{
			VertexArray.append({ { LineBegin.x, LineBegin.y - (mThickness / 2) }, mTrackColor });
			VertexArray.append({ { LineBegin.x, LineBegin.y + (mThickness / 2) }, mTrackColor });
			VertexArray.append({ { LineEnd.x, LineEnd.y + (mThickness / 2) }, mTrackColor });
			VertexArray.append({ { LineEnd.x, LineEnd.y - (mThickness / 2) }, mTrackColor });
		}
		// In case of vertical alignment
		else
		{
			VertexArray.append({ { LineBegin.x - (mThickness / 2), LineBegin.y }, mTrackColor });
			VertexArray.append({ { LineBegin.x + (mThickness / 2), LineBegin.y }, mTrackColor });
			VertexArray.append({ { LineEnd.x + (mThickness / 2), LineEnd.y }, mTrackColor });
			VertexArray.append({ { LineEnd.x - (mThickness / 2), LineEnd.y }, mTrackColor });
		}

		mLastPointPosTemp = LineEnd;
	}

	void TConductiveTracks::toggleDraw()
	{
		mEnableDraw = !mEnableDraw;

		// Removes all the temp points
		mDrawableComponent->getVertexArray().resize(mFixedPoints);
	}

	sf::FloatRect TConductiveTracks::getLocalBound()
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getLocalBounds();
	}

	sf::FloatRect TConductiveTracks::getGlobalBound()
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getGlobalBounds();
	}

	sf::FloatRect TConductiveTracks::getSegmentLocalBound(const std::size_t SegmentNumber)
	{
		auto& VertexArray = mParent->getComponentAsPtr<TDrawableComponent>()->getVertexArray();

		return sf::FloatRect(VertexArray[SegmentNumber * 4 + 0].position.x, VertexArray[SegmentNumber * 4 + 0].position.y,
			VertexArray[SegmentNumber * 4 + 3].position.x, VertexArray[SegmentNumber * 4 + 3].position.y);
	}

	sf::FloatRect TConductiveTracks::getSegmentGlobalBound(const std::size_t SegmentNumber)
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getTransform().transformRect(getSegmentLocalBound(SegmentNumber));
	}

}
#include "TConductiveTracks.h"
#include "TLogicBoardComponent.h"
#include "TSceneManager.h"
#include <SFML/Window/Mouse.hpp>

namespace nne
{

	TConductiveTracks::TConductiveTracks() :
		mTrackThickness(4.f),
		mTempLineBegin(.0f, .0f),
		mTempLineEnd(.0f, .0f),
		mSegmentNumber(0)
	{
	}

	void TConductiveTracks::update(const sf::Time& ElapsedTime)
	{
		// Update the vertex array
		if (mTempLineBegin != sf::Vector2f(0.f, 0.f) && mTempLineEnd != sf::Vector2f(0.f, 0.f))
		{
			// Get a ref to the vertex array
			auto& VertexArray = mDrawableComponent->getVertexArray();

			// Resize the array
			VertexArray.resize(1 * 4);
			
			// Draw the track
			lineToRectangleShape(mTempLineBegin, mTempLineEnd, 0);
		}
	}

	void TConductiveTracks::refresh(const sf::Time& ElapsedTime)
	{
		// See if we clicked on the mouse
		auto MousePosition = sf::Mouse::getPosition(mParent->getSceneManager().getRenderWindow());
		if (checkMouseClickOnTrack(MousePosition))
			mParent->getComponentAsPtr<TLogicBoardComponent>()->setSelectedTrack(this);

// 		// get a pointer to the selected chip
// 		auto CurrentChipPtr = mParent->getComponentAsPtr<TLogicBoardComponent>()->getSelectedChip();
// 		auto FormerChipPtr = mParent->getComponentAsPtr<TLogicBoardComponent>()->getFormerSelectedChip();
// 
// 		// Forward declare the value to old the selected pin
// 		std::size_t SelectedPin = TChipComponent::None;
// 
// 		// Check if the mouse is pressed and we selected a chip
// 		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && CurrentChipPtr && (SelectedPin = CurrentChipPtr->getSelectedPin()) != TChipComponent::None)
// 		{
// 			// Get the selected pin bound
// 			auto& Bound = CurrentChipPtr->getPinGlobalBounds(SelectedPin);
// 
// 			// Place the point if we just selected one chip
// 			if (!FormerChipPtr)
// 			{
// 				placePoint({ Bound.left + Bound.width, Bound.top + (Bound.height / 2) });
// 			}
// 			else
// 			{
// 				endTrack({ Bound.left, Bound.top + (Bound.height / 2) });
// 			}
// 		}
	}

	void TConductiveTracks::init()
	{
		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();

// 		auto& VertexArray = mDrawableComponent->getVertexArray();
// 
// 		const std::size_t SegmentNumber = 3;
// 
// 		// The vertex array size is corrisponded to the number of segment * 4 (to make a rectangleshape)
// 		VertexArray.resize(SegmentNumber * 4);
// 
// 		lineToRectangleShape({ 100.f, 50.f }, { 250.f, 50.f }, 0);
// 		lineToRectangleShape({ 250.f, 50.f }, { 250.f, 500.f }, 1);
// 		lineToRectangleShape({ 250.f, 500.f }, { 60.f, 500.f }, 2);
	}

	void TConductiveTracks::startTrack(const sf::Vector2f& LineBegin)
	{		
		mTempLineBegin = LineBegin;
	}

	void TConductiveTracks::placePoint(const sf::Vector2f& Point)
	{
		if (mTempLineBegin == sf::Vector2f(.0f, .0f))
		{
			startTrack(Point);
		}
	}

	void TConductiveTracks::endTrack(const sf::Vector2f& LineEnd)
	{
		if (mTempLineEnd == sf::Vector2f(.0f, .0f))
		{
			mTempLineEnd = LineEnd;
		}
	}

	sf::FloatRect TConductiveTracks::getTrackLocalBound()
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getLocalBounds();
	}

	sf::FloatRect TConductiveTracks::getTrackGlobalBound()
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getGlobalBounds();
	}

	sf::FloatRect TConductiveTracks::getSegmentLocalBound(const std::size_t SegmentNumber)
	{
		auto& VertexArray = mParent->getComponentAsPtr<TDrawableComponent>()->getVertexArray();

		return sf::FloatRect(	VertexArray[SegmentNumber * 4 + 0].position.x, VertexArray[SegmentNumber * 4 + 0].position.y,
								VertexArray[SegmentNumber * 4 + 3].position.x, VertexArray[SegmentNumber * 4 + 3].position.y);
	}

	sf::FloatRect TConductiveTracks::getSegmentGlobalBound(const std::size_t SegmentNumber)
	{
		return mParent->getComponentAsPtr<TDrawableComponent>()->getTransform().transformRect(getSegmentLocalBound(SegmentNumber));
	}

	bool TConductiveTracks::checkMouseClickOnTrack(const sf::Vector2i Mouse)
	{
		std::size_t Index = 0;
		
		// Iterate trough all the segment
		while (Index < mSegmentNumber)
		{
			// But if we find that the mouse is inside one track exist the function now with a true :)
			if (getSegmentGlobalBound(Index++).contains(static_cast<sf::Vector2f>(Mouse)))
				return true;
		}

		// If we reach this found it means the we didn't click in the track
		return false;
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
		auto& VertexArray = mDrawableComponent->getVertexArray();

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
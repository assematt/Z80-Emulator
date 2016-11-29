#pragma once

#include <memory>
#include <vector>

#include "TPinComponent.h"
#include "IComponent.h"
#include "TDrawableComponent.h"
#include "TEntity.h"

namespace nne
{
	class TConductiveTracks : public IComponent
	{
	public:

		TConductiveTracks();

		virtual void update(const sf::Time& ElapsedTime) override;

		virtual void refresh(const sf::Time& ElapsedTime) override;

		virtual void init() override;

		/// Start a track 
		void startTrack(const sf::Vector2f& LineBegin);

		/// Place a point in the track
		void placePoint(const sf::Vector2f& Point);

		/// End the track finally
		void endTrack(const sf::Vector2f& LineEnd);

		/// Get the bound of the track
		sf::FloatRect getTrackLocalBound();
		sf::FloatRect getTrackGlobalBound();

		/// Get the bound of a single segment of the track
		sf::FloatRect getSegmentLocalBound(const std::size_t SegmentNumber);
		sf::FloatRect getSegmentGlobalBound(const std::size_t SegmentNumber);

	private:

		/// Check if we clicked the mouse on the track
		bool checkMouseClickOnTrack(const sf::Vector2i Mouse);

		bool checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);

		void lineToRectangleShape(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd, const std::size_t SegmentNumber);

	private:
		std::size_t				mSegmentNumber;
		const float				mTrackThickness;
		sf::Vector2f			mTempLineBegin;
		sf::Vector2f			mTempLineEnd;
		std::vector<sf::Vertex>	mPathJoints;
		TDrawableComponent*		mDrawableComponent;
	};
}
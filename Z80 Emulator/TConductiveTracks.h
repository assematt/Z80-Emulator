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
		// constructor
		TConductiveTracks();

		virtual void update(const sf::Time& ElapsedTime) override;

		virtual void refresh(const sf::Time& ElapsedTime) override;

		virtual void init() override;

		// place a fixed point
		void confirmPoints();

		// Adjust the oblique line to be a combination of an horizontal + vertical lines
		void adjustLine(const sf::Vector2f& Point1, const sf::Vector2f& Point2);

		// place a temp point
		void placePointTemp(const sf::Vector2f& PointPos);

		// Check the orientation of the lines we want to draw
		bool checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);

		void placeInitialPoint(const sf::Vector2f& PointPos);

		void lineToQuad(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);
		
		// 
		void toggleDraw();

		/// Get the bound of the track
		sf::FloatRect getLocalBound();
		sf::FloatRect getGlobalBound();

		/// Get the bound of a single segment of the track
		sf::FloatRect getSegmentLocalBound(const std::size_t SegmentNumber);
		sf::FloatRect getSegmentGlobalBound(const std::size_t SegmentNumber);

	private:
		bool				mEnableDraw;
		float				mThickness;
		sf::Color			mTrackColor;
		std::size_t			mFixedPoints;
		sf::Vector2f		mLastPointPos;
		sf::Vector2f		mLastPointPosTemp;
		TDrawableComponent*	mDrawableComponent;
	};
}
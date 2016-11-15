#pragma once

#include <memory>
#include <vector>

#include "TDrawableVector.h"
#include "TPinComponent.h"
#include "IComponent.h"
#include "TSprite.h"
#include "TEntity.h"

namespace nne
{
	class TConductiveTracks : public IComponent
	{
	public:

		TConductiveTracks();

		virtual void Update() override;

		virtual void Refresh() override;

		virtual void Init() override;

	private:

		bool CheckOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);

		void LineToRectangleShape(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd, const std::size_t SegmentNumber);

	private:
		std::shared_ptr<sf::VertexArray> mVertexArray;
		const float mTrackThickness;
		std::vector<sf::Vertex> mPathJoints;
	};
}
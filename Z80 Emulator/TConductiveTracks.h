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

		virtual void update() override;

		virtual void refresh() override;

		virtual void init() override;

	private:

		bool checkOrentation(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd);

		void lineToRectangleShape(const sf::Vector2f& LineBegin, const sf::Vector2f& LineEnd, const std::size_t SegmentNumber);

	private:
		std::shared_ptr<sf::VertexArray> mVertexArray;
		const float mTrackThickness;
		std::vector<sf::Vertex> mPathJoints;
	};
}
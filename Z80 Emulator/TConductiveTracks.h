#pragma once

#include <memory>
#include <vector>

#include "TPinComponent.h"
#include "IComponent.h"
#include "TSprite.h"
#include "TEntity.h"

namespace nne
{
	class TConductiveTracks : public IComponent
	{
	public:		

		virtual void Update() override
		{
			//throw std::logic_error("The method or operation is not implemented.");
		}


		virtual void Refresh() override
		{
			//throw std::logic_error("The method or operation is not implemented.");
		}

		virtual void Init() override
		{
			//mDrawableComponent = mParent->GetComponentAsPtr<TSprite>();
			//mDrawableComponent->SetPrimitiveType(sf::PrimitiveType::LinesStrip);

			mVertexArray = std::make_shared<sf::VertexArray>();

			auto& VertexArray = *mVertexArray;
			VertexArray.resize(4);

			VertexArray[0] = { { 0.f, 0.f }, sf::Color::Red };
			VertexArray[1] = { { 250.f, 0.f }, sf::Color::Red };
			VertexArray[2] = { { 250.f, 500.f }, sf::Color::Red };
			VertexArray[3] = { { 60.f, 500.f }, sf::Color::Red };
		}

	private:
		//std::shared_ptr<TSprite> mDrawableComponent;
		std::shared_ptr<sf::VertexArray> mVertexArray;
		std::vector<sf::Vertex> mPathJoints;
	};
}
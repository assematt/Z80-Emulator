#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "IComponent.h"
#include "TPinComponent.h"
#include "TDrawableVector.h"
#include "TEntity.h"

namespace nne
{
	class TChip : public IComponent
	{
	public:
		enum class TPackage
		{
			DIP,
			SOIC,
			LQFP
		};

		TChip(TEntity* ManagedObject);

		void Init() override;

		void Update() override;

		void Refresh() override;

		void SetSize(const sf::Vector2f& Size);

		void SetChipColor(const sf::Color& Color);

	private:
		void RenderDipChip();

	private:
		nne::TEntity* mManagedObject;
		std::shared_ptr<sf::VertexArray> mObjectShape;
	};
}
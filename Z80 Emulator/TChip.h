#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>
#include <vector>

#include "IComponent.h"
#include "TPinComponent.h"
#include "TTransformable.h"
#include "TdrawableVector.h"
#include "TChipPin.h"
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

		void init() override;

		void update() override;

		void refresh() override;

		/// Function to Get/Set the chip size
		void setSize(const sf::Vector2f& Size);
		const sf::Vector2f getSize() const;
		
		void setChipColor(const sf::Color& Color);

		/// FUnction that updates the chip vertex array when we change the position
		void updateChipPosition();

	private:	

		void renderDipChip();

	private:
		sf::Vector2f						mSize;
		nne::TEntity*						mManagedObject;
		std::vector<TChipPin>				mPins;
		std::shared_ptr<sf::VertexArray>	mObjectShape;
	};
}
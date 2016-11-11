#pragma once

#include <SFML/Graphics.hpp>
#include "TEntity.h"
#include "TTransformable.h"
#include "TDrawableVector.h"
#include "TSprite.h"

namespace nne
{
	class TGraphicEntity : public TEntity, public sf::Drawable
	{
	public:
		/// Update function
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void MakeVirtual() override {}

	};
}
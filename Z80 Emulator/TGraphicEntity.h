#pragma once

#include <SFML/Graphics.hpp>
#include "TEntity.h"
#include "TTransformable.h"
#include "TTexture.h"

namespace nne
{
	struct TGraphicEntity : public TEntity, public sf::Drawable
	{
		/// Update function
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void MakeVirtual() override {}
	};
}
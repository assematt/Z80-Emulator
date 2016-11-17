#pragma once

#include <SFML/Graphics.hpp>
#include "TEntity.h"
#include "TDrawableComponent.h"

namespace nne
{
	class TGraphicEntity : public TEntity, public sf::Drawable
	{
	public:
		/// update function
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void makeVirtual() override {}

	};
}
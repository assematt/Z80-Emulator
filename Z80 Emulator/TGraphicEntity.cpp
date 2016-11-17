#include "TGraphicEntity.h"

namespace nne
{
	void TGraphicEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(*getComponentAsPtr<TDrawableComponent>(), states);
	}
}
#include "TGraphicEntity.h"

namespace nne
{
	void TGraphicEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= this->GetComponentAsPtr<TTransformable>()->GetTransform();

		states.texture = &this->GetComponentAsPtr<TTexture>()->GetTexture();

		target.draw(this->GetComponentAsPtr<TTexture>()->GetVertexArray(), states);
	}
}
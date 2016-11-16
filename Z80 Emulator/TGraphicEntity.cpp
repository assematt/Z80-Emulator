#include "TGraphicEntity.h"

namespace nne
{
	void TGraphicEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= this->getComponentAsPtr<TTransformable>()->getTransform();

		auto& drawablesComponent = *getComponentAsPtr<TdrawableVector>();

		for (std::size_t Index = 0; Index < drawablesComponent.getVectorSize(); ++Index)
		{
			states.texture = drawablesComponent[Index].getTexture();
			target.draw(drawablesComponent[Index].getVertexArray(), states);
		}		
	}
}
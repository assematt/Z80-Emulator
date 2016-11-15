#include "TGraphicEntity.h"

namespace nne
{
	void TGraphicEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= this->GetComponentAsPtr<TTransformable>()->GetTransform();

		auto& DrawablesComponent = *GetComponentAsPtr<TDrawableVector>();

		for (std::size_t Index = 0; Index < DrawablesComponent.GetVectorSize(); ++Index)
		{
			states.texture = DrawablesComponent[Index].GetTexture();
			target.draw(DrawablesComponent[Index].GetVertexArray(), states);
		}		
	}
}
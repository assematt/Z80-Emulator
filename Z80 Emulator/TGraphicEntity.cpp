#include "TGraphicEntity.h"

namespace nne
{
	void TGraphicEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= this->GetComponentAsPtr<TTransformable>()->GetTransform();

		auto& DrawablesComponent = *GetComponentAsPtr<TDrawableVector>();

		//states.texture = &this->GetComponentAsPtr<TTexture>()->GetTexture();

		for (std::size_t Index = 0; Index < DrawablesComponent.GetVectorSize(); ++Index)
		{			
			target.draw(*DrawablesComponent[Index].lock(), states);
		}
		
	}
}
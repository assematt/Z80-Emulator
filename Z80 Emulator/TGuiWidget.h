#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "TEntity.h"
#include "TTexture.h"
#include "TTransformable.h"
#include "TFont.h"

namespace nne
{
	namespace tgui
	{
		class TGuiWidget : public nne::TEntity, public sf::Drawable
		{
		public:
			using UniquePtr = std::unique_ptr<TGuiWidget>;
			using SharedPtr = std::shared_ptr<TGuiWidget>;

			TGuiWidget();

			void Init();

			void Refresh(sf::Time& ElapsedTime) {};

			void Update(sf::Time& ElapsedTime) {};

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			void MakeVirtual() override {};

			void OnMouseClick(int X, int Y)
			{

			}
		};
	}
}
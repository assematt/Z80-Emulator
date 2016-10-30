#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "TEntity.h"
#include "TLogicEntity.h"
#include "TGraphicEntity.h"
#include "TTexture.h"
#include "TTransformable.h"
#include "TFont.h"

namespace nne
{
	namespace tgui
	{
		class TGuiWidget : public nne::TLogicEntity, public TGraphicEntity
		{
		public:
			using UniquePtr = std::unique_ptr<TGuiWidget>;
			using SharedPtr = std::shared_ptr<TGuiWidget>;

			using nne::TLogicEntity::Update;

			TGuiWidget();

			void Init();

			void Refresh(sf::Time& ElapsedTime) {};

			void Update(sf::Time& ElapsedTime) {};

			void MakeVirtual() override {};

			void OnMouseClick(int X, int Y)
			{

			}
		};
	}
}
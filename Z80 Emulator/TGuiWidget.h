#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "TEntity.h"
#include "TLogicEntity.h"
#include "TGraphicEntity.h"
#include "TTexture.h"
#include "TTransformable.h"

namespace nne
{
	namespace tgui
	{
		class TGuiWidget : public nne::TLogicEntity, public nne::TEntity, public sf::Drawable
		{
		public:
			using UniquePtr = std::unique_ptr<TGuiWidget>;
			using SharedPtr = std::shared_ptr<TGuiWidget>;

			using nne::TLogicEntity::Update;
			using nne::TLogicEntity::Refresh;

			TGuiWidget();
			virtual ~TGuiWidget();

			virtual void Init();

			virtual void Refresh(const sf::Time& ElapsedTime) override;

			virtual void Update(const sf::Time& ElapsedTime) override;

			void MakeVirtual() override {};

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		};
	}
}
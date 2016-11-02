#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
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
			TGuiWidget(const std::string WidgetName);
			virtual ~TGuiWidget();

			virtual void Init();

			virtual void Refresh(const sf::Time& ElapsedTime) override;

			virtual void Update(const sf::Time& ElapsedTime) override;

			/// Functions to change the widget property
			void SetName(const std::string& WidgetName);
			const std::string& GetName() const;

			void SetSize(const sf::Vector2i& WidgetSize);
			const sf::Vector2i& GetSize() const;

			void SetPosition(const sf::Vector2f& WidgetSize);
			const sf::Vector2f& GetPosition() const;

			void SetVisibility(bool Show = true);
			
			/// Function based on the widgets event
			virtual void OnMouseClick(sf::Event::MouseButtonEvent Button) {}
			virtual void OnMouseDown(sf::Event::MouseButtonEvent Button) {}
			virtual void OnMouseUp(sf::Event::MouseButtonEvent Button) {}
			virtual void OnMouseEnter(sf::Event::MouseMoveEvent Button) {}
			virtual void OnMouseLeave(sf::Event::MouseMoveEvent Button) {}
			virtual void OnMouseMove(sf::Event::MouseMoveEvent Button) {}

		
			void MakeVirtual() override {};
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		private:
			std::string mName;
			sf::Vector2i mSize;
			sf::Vector2f mPosition;
			bool mVisible;
		};
	}
}
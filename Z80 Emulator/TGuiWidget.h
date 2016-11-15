#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <array>
#include <tuple>
#include <memory>
#include <windows.h>

#include "TTransformable.h"
#include "TLogicEntity.h"
#include "TEntity.h"
#include "TSprite.h"
#include "TFont.h"

namespace nne
{
	namespace tgui
	{
		namespace tevent
		{
			enum TEventTypes : sf::Uint8
			{
				_OnMouseClick,
				_OnMouseDown,
				_OnMouseUp,
				_OnMouseEnter,
				_OnMouseLeave,
				_OnMouseMove,

				// 
				TEventTypesSize
			};

			using BaseEvent		= std::function<void(const sf::Event::MouseButtonEvent&)>;
			using EventID		= std::size_t;
		}

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

			/// Functions to get/set the widget name
			void SetName(const std::string& WidgetName);
			const std::string& GetName() const;

			/// Functions to get/set the widget size
			virtual void SetSize(const sf::Vector2u& WidgetSize);
			virtual const sf::Vector2u& GetSize() const;

			/// Functions to get/set the widget position
			void SetPosition(const sf::Vector2f& WidgetSize);
			const sf::Vector2f& GetPosition() const;

			/// Functions to get/set the widget visibility
			void SetVisibility(bool Show = true);
			bool GetVisibility();

			/// Functions to get/set the widget ability to accept input
			void EnableInput();
			void DisableInput();
			bool IsInputEnabled();

			/// Connect a signal to the widget
			void ConnectSignal(const tevent::BaseEvent& Function, const tevent::TEventTypes& SignalToConnect);

			/// Raise a signal
			void RaiseSignal(const tevent::TEventTypes& SignalToConnect, const sf::Event::MouseButtonEvent& Button)
			{
				if (mSignals[SignalToConnect])
					mSignals[SignalToConnect](Button);
			}

			/// Get the widget bound
			const sf::FloatRect& GetWidgetBound() const;
		
		private:
			void MakeVirtual() override {};
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		private:
			std::string mName;
			sf::Vector2u mSize;
			sf::Vector2f mPosition;
			bool mVisible;
			bool mAcceptInput;

			std::array<tevent::BaseEvent, tevent::TEventTypesSize> mSignals;
		};			   		
	}
}					   	
					   	
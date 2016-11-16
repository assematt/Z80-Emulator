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
			
			using nne::TLogicEntity::update;
			using nne::TLogicEntity::refresh;

			TGuiWidget();
			TGuiWidget(const std::string WidgetName);
			virtual ~TGuiWidget();

			virtual void init();

			virtual void refresh(const sf::Time& ElapsedTime) override;

			virtual void update(const sf::Time& ElapsedTime) override;

			/// Functions to get/set the widget name
			void setName(const std::string& WidgetName);
			const std::string& getName() const;

			/// Functions to get/set the widget size
			virtual void setSize(const sf::Vector2u& WidgetSize);
			virtual const sf::Vector2u& getSize() const;

			/// Functions to get/set the widget position
			void setPosition(const sf::Vector2f& WidgetSize);
			const sf::Vector2f& getPosition() const;

			/// Functions to get/set the widget visibility
			void setVisibility(bool Show = true);
			bool IsVisible();

			/// Functions to get/set the widget ability to accept input
			void enableInput();
			void disableInput();
			bool isInputEnabled();

			/// Connect a signal to the widget
			void connectSignal(const tevent::BaseEvent& Function, const tevent::TEventTypes& SignalToConnect);

			/// Raise a signal
			void raiseSignal(const tevent::TEventTypes& SignalToConnect, const sf::Event::MouseButtonEvent& Button)
			{
				if (mSignals[SignalToConnect])
					mSignals[SignalToConnect](Button);
			}

			/// Get the widget bound
			const sf::FloatRect& getWidgetBound() const;
		
		private:
			void makeVirtual() override {};
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
					   	
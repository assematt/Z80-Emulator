#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include INCLUDE_ENTITY_CLASS
#include "TWidget.h"

namespace nne
{
	namespace tcomponents
	{
		namespace events
		{
			enum List
			{
				//* -> Implemented
				//& -> Not Implemented
				onClick,			//*	Occurs when the user clicks the control.
				onContextPopup,		//&	Occurs when the user right-clicks the control or otherwise invokes the pop-up menu (such as using the keyboard).
				onDragDrop,			//&	Occurs when the user drops an object being dragged.
				onDragOver,			//&	Occurs when the user drags an object over a control.
				onDropDownClick,	//&	Down arrow part of a Vista or later style split button is clicked.
				onEndDock,			//&	Occurs when the dragging of an object ends, either by docking the object or by canceling the dragging.
				onEndDrag,			//&	Occurs when the dragging of an object ends, either by dropping the object or by canceling the dragging.
				onEnter,			//&	Occurs when a control receives the input focus.
				onExit,				//&	Occurs when the input focus shifts away from one control to another.
				onGesture,			//&	Occurs when you perform a gesture associated with this control.
				onKeyDown,			//&	Occurs when a user presses any key while the control has focus.
				onKeyPress,			//*	Occurs when a key is pressed.
				onKeyUp,			//&	Occurs when the user releases a key that was pressed.
				onMouseActivate,	//&	Occurs when the user presses a mouse button with the mouse pointer over a control and the parent form is not active.
				onMouseDown,		//*	Occurs when the user presses a mouse button with the mouse pointer over a control.
				onMouseEnter,		//&	Occurs when the user moves the mouse into a control.
				onMouseLeave,		//&	Occurs when the user moves the mouse outside of a control.
				onMouseMove,		//*	Occurs when the user moves the mouse pointer while the mouse pointer is over a control.
				onMouseUp,			//*	Occurs when the user releases a mouse button that was pressed with the mouse pointer over a component.
				onMouseWheel,		//* Occurs when the mouse wheel is rotated.
				onMouseWheelDown,	//* Occurs when the mouse wheel is rotated downward.
				onMouseWheelUp,		//* Occurs when the mouse wheel is rotated upward.
				onStartDrag,		//&	Occurs when the user begins to drag the control or an object it contains by left-clicking the control and holding the mouse button down.
			};

			/// Typedef for the events
#if ENTITY_SYSTEM == NNE
			using TEvent = std::function<void(const TEntity* Sender, const sf::Event& EventData)>;
#else
			using TEvent = std::function<void(const ecs::_TEntity* Sender, const sf::Event& EventData)>;
#endif
			
			/// Typedef for event list/slot
			using TEventList = std::unordered_map<List, TEvent>;
			using TEventSlot = TEventList::iterator;
		}

		class TEventComponent : BASE_COMPONENT_CLASS
		{
		public:			

			TEventComponent();

			void init() override;

			void update(REFRESH_UPDATE_PARAMETER) override;

			void refresh(REFRESH_UPDATE_PARAMETER) override;

			/// Connect/Detach events
			const events::TEventSlot& attachEvent(const events::List& EventType, const events::TEvent& EventToAttach);
			void detachEvent(const events::List& EventType);

			/// Fire an event
#if ENTITY_SYSTEM == NNE
			void fireEvent(const events::List& EventToFire, const TEntity* Sender, const sf::Event& EventData);
#else
			void fireEvent(const events::List& EventToFire, const ecs::_TEntity* Sender, const sf::Event& EventData);
#endif

			void setMousePosition(const sf::Vector2f& NewPos);
			void setMousePosition(const float& X, const float& Y);

			const sf::Vector2f& getMousePosition() const;

		private:
			sf::Vector2f		mMousePos;
			events::TEventList	mEventsList;
		};
	}
}


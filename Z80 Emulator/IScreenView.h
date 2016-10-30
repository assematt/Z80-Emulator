#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "TGuiWindow.h"
#include "TGuiWidget.h"
#include "TRandom.h"

namespace nne
{
	namespace tgui
	{
		enum class TReferencePoint
		{
			LEFT_TOP,
			CENTER_TOP,
			RIGHT_TOP,

			LEFT_CENTER,
			CENTER,
			RIGHT_CENTER,

			LEFT_BOTTOM,
			CENTER_BOTTOM,
			RIGHT_BOTTOM,
		};
		
		class TGuiManager;

		class IScreenView
		{
		public:
			using UniquePtr = std::unique_ptr<IScreenView>;
			using SharedPtr = std::shared_ptr<IScreenView>;

			virtual ~IScreenView() = default;

			virtual void Setup() = 0;

			virtual void HandleEvent(sf::Event& Event) = 0;

			virtual void Display() = 0;

			void AddWidget(TGuiWidget::UniquePtr& Widget);

			template <typename... TArgs>
			void AddWidget(TArgs&&... mArgs)
			{
				// Creates a temp pointer that holds the value that we are gonna to insert in the array
				TGuiWidget::UniquePtr TempPtr = std::make_unique<TGuiWidget>(std::forward<TArgs>(mArgs)...);

				// Use the other function to add the entity
				AddWidget(std::move(TempPtr));
			}

			/// Function to remove a widget
			void RemoveWidget(std::size_t Index);

			const TGuiWidget::UniquePtr& GetWidget(const std::size_t Index) const;

			/// Updates every widget in the container
			void Update(sf::Time& ElapsedTime);

			/// Refreshes every widget in the container
			void Refresh(sf::Time& ElapsedTime);

			/// Draw all the widgets in the container
			void Draw();

			/// Set the position of the menu container
			void SetPosition(sf::Vector2f& NewPosition, TReferencePoint RefPoint = TReferencePoint::CENTER);
			void SetPosition(float NewPositionX, float NewPositionY, TReferencePoint RefPoint = TReferencePoint::CENTER);

			/// Helper function for c++11 foreach use
			std::vector<TGuiWidget::UniquePtr>::iterator begin();
			std::vector<TGuiWidget::UniquePtr>::iterator end();

			/// Subscript operator to access an widget by index
			TGuiWidget::UniquePtr& operator[] (const int Index);
			const TGuiWidget::UniquePtr& operator[] (const int Index) const;

		protected:
			bool CheckMouseClick(TGuiWidget::UniquePtr& Widget, const sf::Vector2i Mouse);

		protected:
			std::vector<TGuiWidget::UniquePtr> mWidgetsContainer;
			sf::Vector2f mPosition;
			TGuiManager* mParentManager;

			friend class TGuiManager;
		};
	}
}

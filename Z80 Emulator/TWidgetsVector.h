#pragma once

#include "TGuiWidget.h"
#include "IComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{
		class TWidgetsVector : public sf::Transformable
		{
		public:
			TWidgetsVector();
			
			/// Function to add a widget to the menu
			template <class T>
			void addWidget(T& Widget);
			template <typename... TArgs>
			void addWidget(TArgs&&... mArgs);
			
			/// Function to remove a widget
			void removeWidget(std::size_t Index);

			/// Function to retrieve a widget from the vector
			const TGuiWidget::UniquePtr& getWidget(const std::size_t Index) const;

			/// Get the last added widget
			const TGuiWidget::UniquePtr& getLastAdded();

			/// Get the widget with the highest ZIndex value (that also correspond to the last widget in the vector)
			const TGuiWidget::UniquePtr& getFrontWidget();

			/// Get the widget with the lowest ZIndex value (that also correspond to the first widget in the vector)
			const TGuiWidget::UniquePtr& getBackWidget();

			/// Helper function for c++11 for each use
			std::vector<TGuiWidget::UniquePtr>::iterator begin();
			std::vector<TGuiWidget::UniquePtr>::iterator end();

			/// Helper function for c++11 for each use as const iterator
			std::vector<TGuiWidget::UniquePtr>::const_iterator cbegin();
			std::vector<TGuiWidget::UniquePtr>::const_iterator cend();

			/// Helper function for c++11 for each use as reverse iterator
			std::vector<TGuiWidget::UniquePtr>::reverse_iterator rbegin();
			std::vector<TGuiWidget::UniquePtr>::reverse_iterator rend();

			/// Helper function for c++11 for each use as const reverse iterator
			std::vector<TGuiWidget::UniquePtr>::const_reverse_iterator crbegin();
			std::vector<TGuiWidget::UniquePtr>::const_reverse_iterator crend();

			/// Subscript operator to access an widget by index
			TGuiWidget::UniquePtr& operator[] (const int Index);
			const TGuiWidget::UniquePtr& operator[] (const int Index) const;
			
		private:
			std::size_t							mLastAddedPosition;
			sf::Vector2f						mContainerPos;
			std::vector<TGuiWidget::UniquePtr>	mWidgetsContainer;
		};

		template <typename... TArgs>
		void nne::tgui::TWidgetsVector::addWidget(TArgs&&... mArgs)
		{
			// Creates a temp pointer that holds the value that we are gonna to insert in the array
			TGuiWidget::UniquePtr TempPtr = std::make_unique<TGuiWidget>(std::forward<TArgs>(mArgs)...);

			addWidget(TempPtr);
		}

		template <class T>
		void nne::tgui::TWidgetsVector::addWidget(T& Widget)
		{
			// If the manager is empty simply add the entity
			if (mWidgetsContainer.empty())
			{
				// Push the element in the array
				mWidgetsContainer.push_back(std::move(Widget));

				// The last added element it's the first element in the array
				mLastAddedPosition = 0;

				return;
			}

			// Get the entity size
			auto VectorSize = mWidgetsContainer.size();
			std::size_t InsertionPos = 0;

			// Get the value to compare
			auto CompareValue = Widget->getZIndex();

			// Find the insert position
			while (CompareValue > mWidgetsContainer[InsertionPos]->getZIndex() && ++InsertionPos < VectorSize);

			// Shift all the element right of the insertion position to the right
			// but first make sure we have enough space for one more element by adding an empty object
			mWidgetsContainer.emplace_back();

			// Does the shifting to the right
			for (std::size_t Index = VectorSize; Index > InsertionPos; --Index)
				mWidgetsContainer[Index] = std::move(mWidgetsContainer[Index - 1]);

			// Put the element in the right place
			mWidgetsContainer[InsertionPos] = std::move(Widget);

			// Save the position of last added element
			mLastAddedPosition = InsertionPos;
		}

	}
}
#pragma once

#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TWidgetsContainer
		{
		public:
			TWidgetsContainer();
			
			/// Function to add a widget to the menu
			template <class T>
			void addWidget(T& Widget);
			template <typename... TArgs>
			void addWidget(TArgs&&... mArgs);
			
			/// Function to remove a widget
			void removeWidget(std::size_t Index);

			/// Function to retrieve a widget from the vector by Index
			template <class T>
			T* getWidget(const std::size_t Index) const;

			/// Function to retrieve a widget from the vector by Name
			template <class T>
			T* getWidget(const std::string& WidgetName) const;

			/// Get the last added widget
			const TWidget::UniquePtr& getLastAdded();

			/// Get the widget with the highest ZIndex value (that also correspond to the last widget in the vector)
			const TWidget::UniquePtr& getFrontWidget();

			/// Get the widget with the lowest ZIndex value (that also correspond to the first widget in the vector)
			const TWidget::UniquePtr& getBackWidget();

			/// Helper function for c++11 for each use
			std::vector<TWidget::UniquePtr>::iterator begin();
			std::vector<TWidget::UniquePtr>::iterator end();

			/// Helper function for c++11 for each use as const iterator
			std::vector<TWidget::UniquePtr>::const_iterator cbegin();
			std::vector<TWidget::UniquePtr>::const_iterator cend();

			/// Helper function for c++11 for each use as reverse iterator
			std::vector<TWidget::UniquePtr>::reverse_iterator rbegin();
			std::vector<TWidget::UniquePtr>::reverse_iterator rend();

			/// Helper function for c++11 for each use as const reverse iterator
			std::vector<TWidget::UniquePtr>::const_reverse_iterator crbegin();
			std::vector<TWidget::UniquePtr>::const_reverse_iterator crend();

			/// Subscript operator to access an widget by index
			TWidget::UniquePtr& operator[] (const int Index);
			const TWidget::UniquePtr& operator[] (const int Index) const;
			
		private:
			std::size_t							mLastAddedPosition;
			sf::Vector2f						mContainerPos;
			std::vector<TWidget::UniquePtr>		mWidgetsContainer;
		};

		template <typename... TArgs>
		void nne::tgui::TWidgetsContainer::addWidget(TArgs&&... mArgs)
		{
			// Creates a temp pointer that holds the value that we are gonna to insert in the array
			TWidget::UniquePtr TempPtr = std::make_unique<TWidget>(std::forward<TArgs>(mArgs)...);

			addWidget(TempPtr);
		}

		template <class T>
		void nne::tgui::TWidgetsContainer::addWidget(T& Widget)
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

		template <class T>
		T* TWidgetsContainer::getWidget(const std::size_t Index) const
		{
			return dynamic_cast<T*>(mWidgetsContainer[Index].get());
		}

		template <class T>
		T* TWidgetsContainer::getWidget(const std::string& WidgetName) const
		{
			for (auto& Widget : mWidgetsContainer)
				if (Widget->getName() == WidgetName)
					return dynamic_cast<T*>(Widget.get());

			return nullptr;
		}
	}
}
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <memory>

#include "IMenu.h"
#include "IScene.h"
#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TGuiManager
		{
		public:
			TGuiManager();

			/// Function to add a widget to the menu
			template <class T>
			void addWidget(const std::size_t& ZIndex = 0);

			template <class T>
			void addWidget(T& Widget, const std::size_t& ZIndex = 0);

			template <typename... TArgs>
			void addWidget(TArgs&&... mArgs, const std::size_t& ZIndex = 0);

			/// Function to remove a widget
			void removeWidget(const TWidget::ID& WidgetID);
			
			/// Function to retrieve a widget from the vector by Index or by Name
			TWidget::Ptr getWidget(const TWidget::ID& WidgetID) const;
			TWidget::Ptr getWidget(const std::string& WidgetName) const;

			/// Function to retrieve a widget from the vector by Index or by Name and cast it as a specific widget
			template <class T>
			std::shared_ptr<T> getWidget(const TWidget::ID& WidgetID) const;
			template <class T>
			std::shared_ptr<T> getWidget(const std::string& WidgetName) const;

			/// Function to retrieve a widget from the vector by Index or by Name and cast it as a derived type
			///template <class T>
			///T* getWidgetWithCast(const TWidget::ID& WidgetID) const;
			///template <class T>
			///T* getWidgetWithCast(const std::string& WidgetName) const;

			/// Get the position of the widget in the array
			std::size_t getWidgetPos(const TWidget::ID& WidgetID) const;
			std::size_t getWidgetPos(const std::string& WidgetName) const;

			/// Get the last added widget
			const TWidget::Ptr& getLastAdded();

			/// Get the widget with the highest ZIndex value (that also correspond to the last widget in the vector)
			const TWidget::Ptr& getFrontWidget();

			/// Get the widget with the lowest ZIndex value (that also correspond to the first widget in the vector)
			const TWidget::Ptr& getBackWidget();

			/// Helper function for c++11 for each use
			std::vector<TWidget::Ptr>::iterator begin();
			std::vector<TWidget::Ptr>::iterator end();

			/// Helper function for c++11 for each use as const iterator
			std::vector<TWidget::Ptr>::const_iterator cbegin();
			std::vector<TWidget::Ptr>::const_iterator cend();

			/// Helper function for c++11 for each use as reverse iterator
			std::vector<TWidget::Ptr>::reverse_iterator rbegin();
			std::vector<TWidget::Ptr>::reverse_iterator rend();

			/// Helper function for c++11 for each use as const reverse iterator
			std::vector<TWidget::Ptr>::const_reverse_iterator crbegin();
			std::vector<TWidget::Ptr>::const_reverse_iterator crend();

			/// Subscript operator to access an widget by index
			TWidget::Ptr& operator[] (const int Index);
			const TWidget::Ptr& operator[] (const int Index) const;
			
			/// update all the widget in the manager
			void update(const sf::Time& ElapsedTime);

			/// Process sf::Event's events and change the widget states accordingly and fires the widgets event
			IScene::ID processEvents(const sf::Event& Event, const sf::RenderWindow& EventWindow);

			/// Change the current displayed scene
			void changeScene(const IScene::ID& NewScene) const;

		private:

		private:
			mutable IScene::ID			mNextScene;
			std::size_t					mLastAddedPosition;
			std::vector<std::size_t>	mWidgetsZIndex;
			std::vector<TWidget::Ptr>	mWidgetsContainer;
		};

		template <class T>
		std::shared_ptr<T> TGuiManager::getWidget(const std::string& WidgetName) const
		{
			return std::dynamic_pointer_cast<T>(getWidget(WidgetName));
		}

		template <class T>
		std::shared_ptr<T> TGuiManager::getWidget(const TWidget::ID& WidgetID) const
		{
			return std::dynamic_pointer_cast<T>(getWidget(WidgetID));
		}

		template <typename... TArgs>
		void TGuiManager::addWidget(TArgs&&... mArgs, const std::size_t& ZIndex /*= 0*/)
		{
			// Creates a temp pointer that holds the value that we are gonna to insert in the array
			TWidget::Ptr TempPtr = std::make_shared<TWidget>(std::forward<TArgs>(mArgs)...);

			addWidget(TempPtr, ZIndex);
		}

		template <class T>
		void TGuiManager::addWidget(T& Widget, const std::size_t& ZIndex /*= 0*/)
		{
			// Set some widget property
			Widget->setZIndex(ZIndex);
			Widget->mGuiManager = this;

			// If the manager is empty simply add the entity
			if (mWidgetsContainer.empty())
			{
				// Push the element in the array
				mWidgetsContainer.push_back(std::move(Widget));
				mWidgetsZIndex.push_back(ZIndex);

				// The last added element it's the first element in the array
				mLastAddedPosition = 0;

				return;
			}

			// Get the entity size
			auto VectorSize = mWidgetsContainer.size();
			std::size_t InsertionPos = 0;

			// Find the insert position
			while (ZIndex > mWidgetsZIndex[InsertionPos] && ++InsertionPos < VectorSize);

			// Shift all the element right of the insertion position to the right
			// but first make sure we have enough space for one more element by adding an empty object
			mWidgetsContainer.emplace_back();
			mWidgetsZIndex.emplace_back();

			// Does the shifting to the right
			for (std::size_t Index = VectorSize; Index > InsertionPos; --Index)
			{
				mWidgetsContainer[Index] = std::move(mWidgetsContainer[Index - 1]);
				mWidgetsZIndex[Index] = std::move(mWidgetsZIndex[Index - 1]);
			}

			// Put the element in the right place
			mWidgetsContainer[InsertionPos] = std::move(Widget);
			mWidgetsZIndex[InsertionPos] = ZIndex;

			// Save the position of last added element
			mLastAddedPosition = InsertionPos;
		}

		template <class T>
		void TGuiManager::addWidget(const std::size_t& ZIndex /*= 0*/)
		{
			// Creates a temp pointer that holds the value that we are gonna to insert in the array
			T::Ptr TempPtr = std::make_shared<T>();

			addWidget(TempPtr, ZIndex);
		}

	}
}
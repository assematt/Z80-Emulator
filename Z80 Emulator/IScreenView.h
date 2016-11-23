#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <future>
#include <vector>

#include "TGuiWidget.h"
#include "ILoadingScreen.h"
#include "TDrawableComponent.h"

namespace nne
{
	namespace tgui
	{
		class TGuiManager;

		class IScreenView
		{
		public:
			using UniquePtr = std::unique_ptr<IScreenView>;
			using SharedPtr = std::shared_ptr<IScreenView>;
			using TZIndex = std::size_t;
			using ScreenID = std::size_t;
			
			struct TWdigetRenderStrcut
			{
			public:
				TWdigetRenderStrcut() {}

				template <class T>
				TWdigetRenderStrcut(T& Widget, const TZIndex& ZIndex) :
					mWidget(std::move(Widget)),
					mZIndex(ZIndex)
				{
				}
				TWdigetRenderStrcut(TWdigetRenderStrcut&& Right) :
					mWidget(std::move(Right.mWidget)),
					mZIndex(Right.mZIndex)
				{
				}

				TWdigetRenderStrcut& TWdigetRenderStrcut::operator =(TWdigetRenderStrcut& Right)
				{
					mWidget = std::move(Right.mWidget);
					mZIndex = std::move(Right.mZIndex);

					return *this;
				}

				bool TWdigetRenderStrcut::operator ==(const TWdigetRenderStrcut& Right) const
				{
					return (mZIndex == Right.mZIndex) && (mWidget.get() == Right.mWidget.get());
				}
				bool TWdigetRenderStrcut::operator !=(const TWdigetRenderStrcut& Right) const
				{
					return !(*this == Right);
				}
				bool TWdigetRenderStrcut::operator <(const TWdigetRenderStrcut& Right) const
				{
					return mZIndex < Right.mZIndex;
				}
				bool TWdigetRenderStrcut::operator >(const TWdigetRenderStrcut& Right) const
				{
					return mZIndex > Right.mZIndex;
				}

				TGuiWidget::UniquePtr& GetWidget()
				{
					return mWidget;
				}

			private:
				TGuiWidget::UniquePtr mWidget;
				TZIndex mZIndex;

				friend class IScreenView;
			};

			IScreenView();
			virtual ~IScreenView() = default;

			virtual void init() = 0;

			void handleEvent(const sf::Event& Event);
			
			template <class T>
			void addWidget(T& Widget, const TZIndex& WidgetZIndex = 0);

			template <typename... TArgs>
			void addWidget(TArgs&&... mArgs, const TZIndex& WidgetZIndex = 0);

			/// Function to remove a widget
			void removeWidget(std::size_t Index);

			const TGuiWidget::UniquePtr& getWidget(const std::size_t Index) const;

			/// updates every widget in the container
			void update(const sf::Time& ElapsedTime);

			/// refreshes every widget in the container
			void refresh(const sf::Time& ElapsedTime);

			/// draw all the widgets in the container
			void draw();
			
			/// Helper function for c++11 foreach use
			std::vector<TWdigetRenderStrcut>::iterator begin();
			std::vector<TWdigetRenderStrcut>::iterator end();

			/// Subscript operator to access an widget by index
			TGuiWidget::UniquePtr& operator[] (const int Index);
			const TGuiWidget::UniquePtr& operator[] (const int Index) const;

		protected:
			bool checkMouseClick(const sf::FloatRect& WidgetBound, const sf::Vector2i Mouse);

			template <class T>
			void insertWidget(T& Widget, const TZIndex& WidgetZIndex = 0);

		protected:
			TGuiManager*							mParentManager;
			sf::Vector2f							mPosition;
			std::vector<TWdigetRenderStrcut>		mWidgetsContainer;

			friend class TGuiManager;
		};

		template <typename... TArgs>
		void IScreenView::addWidget(TArgs&&... mArgs, const TZIndex& WidgetZIndex /*= 0*/)
		{
			// Creates a temp pointer that holds the value that we are gonna to insert in the array
			TGuiWidget::UniquePtr TempPtr = std::make_unique<TGuiWidget>(std::forward<TArgs>(mArgs)...);

			insertWidget(TempPtr, WidgetZIndex);
		}

		template <class T>
		void IScreenView::addWidget(T& Widget, const TZIndex& WidgetZIndex /*= 0*/)
		{
			insertWidget(Widget, WidgetZIndex);
		}

		template <class T>
		void IScreenView::insertWidget(T& Widget, const TZIndex& WidgetZIndex /*= 0*/)
		{
			// Get the number of element in the vector
			std::size_t VectorSize = mWidgetsContainer.size();

			// If the array it's empty just inser the element and return only
			if (!mWidgetsContainer.size() || (VectorSize >= 1 && WidgetZIndex >= mWidgetsContainer.back().mZIndex))
			{
				mWidgetsContainer.emplace_back(Widget, WidgetZIndex);

				return;
			}

			// Otherwise find the right point to insert the element
			std::size_t InsertPos = 0;
			while (WidgetZIndex < mWidgetsContainer[InsertPos++].mZIndex && InsertPos <= VectorSize);

			// Shift all the element right of the position we want to insert the new element in
			// But first of all resize the array to make sure we habe enough space for the shift
			mWidgetsContainer.resize(VectorSize + 1);
			for (std::size_t Index = VectorSize; Index > InsertPos; --Index)
			{
				mWidgetsContainer[Index] = mWidgetsContainer[Index - 1];
			}

			mWidgetsContainer[InsertPos] = std::move(TWdigetRenderStrcut(Widget, WidgetZIndex));
		}

	}
}

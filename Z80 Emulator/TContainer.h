#pragma once

#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TContainer : public TWidget
		{
		public:

			using Ptr = std::shared_ptr<TContainer>;

			/// Virtual destructor
			virtual ~TContainer() = default;

			/// Add a widget to the manager
			void addWidget(TWidget* Widget);

			void removeWidget(const TWidget::ID& WidgetToRemove);

		protected:
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
		};
	}
}
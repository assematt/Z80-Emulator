#pragma once

#include "TGuiWidget.h"
#include "IComponent.h"
#include "TTransformable.h"
#include "TText.h"
#include "TCacheManager.h"

namespace nne
{
	namespace tgui
	{
		class TGuiButton : public TGuiWidget
		{
		public:
			TGuiButton();

			using UniquePtr = std::unique_ptr<TGuiButton>;
			using SharedPtr = std::shared_ptr<TGuiButton>;

			/// Init function
			void init();

			virtual void refresh(const sf::Time& ElapsedTime) override;

			virtual void update(const sf::Time& ElapsedTime) override;

			/// Functions to change the widget property
			void SetCaption(const std::string& WidgetName);
			const std::string& GetCaption() const;
			
		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}
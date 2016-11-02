#pragma once

#include "TGuiWidget.h"
#include "IComponent.h"
#include "TFont.h"
#include "TTransformable.h"
#include "TText.h"

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
			void Init();

			virtual void Refresh(const sf::Time& ElapsedTime) override;

			virtual void Update(const sf::Time& ElapsedTime) override;

			/// Functions to change the widget property
			void SetCaption(const std::string& WidgetName);
			const std::string& GetCaption() const;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}
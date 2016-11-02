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

			void Init();

			virtual void Refresh(const sf::Time& ElapsedTime) override;

			virtual void Update(const sf::Time& ElapsedTime) override;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		private:
		};
	}
}
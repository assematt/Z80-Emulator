#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TWidget.h"
#include "TBasePanel.h"
#include "IComponent.h"

namespace nne
{

	namespace tgui
	{
		class TPanel : public TWidget, public TBasePanel
		{
		public:
			TPanel();

			using TBasePanel::setPosition;

			using UniquePtr = std::unique_ptr<TPanel>;
			using SharedPtr = std::shared_ptr<TPanel>;

			/// Init function
			void init();

			/// Set the color of the panel component, not of the child's widget!
			void setColor(const sf::Color& Color);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}
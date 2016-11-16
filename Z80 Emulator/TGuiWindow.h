#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace nne
{
	class TGuiWindow
	{
	public:
		TGuiWindow();

		static sf::RenderWindow& getInstance();

		void clear();

		void display();

		void draw(const sf::Drawable &drawable, const sf::RenderStates &States = sf::RenderStates::Default);

	private:
		sf::RenderWindow mRenderSurface;
	};
}
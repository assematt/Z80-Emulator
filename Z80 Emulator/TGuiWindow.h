#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace nne
{
	class TGuiWindow
	{
	public:
		TGuiWindow();

		static sf::RenderWindow& GetInstance();

		void Clear();

		void Display();

		void Draw(const sf::Drawable &Drawable, const sf::RenderStates &States = sf::RenderStates::Default);

	private:
		sf::RenderWindow mRenderSurface;
	};
}
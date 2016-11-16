#include "TGuiWindow.h"

namespace nne
{

	TGuiWindow::TGuiWindow()
	{

	}

	sf::RenderWindow& TGuiWindow::getInstance()
	{
		static sf::RenderWindow Instance;
		return Instance;
	}

	void TGuiWindow::clear()
	{
		mRenderSurface.clear();
	}

	void TGuiWindow::display()
	{
		mRenderSurface.display();
	}

	void TGuiWindow::draw(const sf::Drawable &drawable, const sf::RenderStates &States /*= sf::RenderStates::Default*/)
	{
		mRenderSurface.draw(drawable, States);
	}

}


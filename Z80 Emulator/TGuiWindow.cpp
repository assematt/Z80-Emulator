#include "TGuiWindow.h"

namespace nne
{

	TGuiWindow::TGuiWindow()
	{

	}

	sf::RenderWindow& TGuiWindow::GetInstance()
	{
		static sf::RenderWindow Instance;
		return Instance;
	}

	void TGuiWindow::Clear()
	{
		mRenderSurface.clear();
	}

	void TGuiWindow::Display()
	{
		mRenderSurface.display();
	}

	void TGuiWindow::Draw(const sf::Drawable &Drawable, const sf::RenderStates &States /*= sf::RenderStates::Default*/)
	{
		mRenderSurface.draw(Drawable, States);
	}

}


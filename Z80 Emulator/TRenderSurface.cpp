#include "TRenderSurface.h"

namespace nne
{

	TRenderSurface::TRenderSurface() :
		mZoomLevel(1.f)
	{
		mCurrentView.setSize({ 1600.f, 900.f });
		mCurrentView.setCenter({ 800.f, 450.f });
		mCurrentView.zoom(1.f);
		setView(mCurrentView);
	}

	void TRenderSurface::render(sf::RenderTarget* SurfaceToRender)
	{
		// Flip the back-buffer with the front-buffer
		display();
		
		// Get the texture from the back buffer
		mSprite.setTexture(getTexture());

		// Draw the sprite on the window
		SurfaceToRender->draw(mSprite, sf::RenderStates(getTransform()));
	}

	void TRenderSurface::setZoomView(const float& ZoomLevel)
	{
		mZoomLevel *= ZoomLevel;

		auto CurrentView = getView();
		CurrentView.zoom(ZoomLevel);
		setView(CurrentView);
	}

	const float& TRenderSurface::getZoomView() const
	{
		return mZoomLevel;
	}

	void TRenderSurface::moveView(const std::size_t& Direction)
	{
		auto CurrentView = getView();

		switch (Direction)
		{
		case 0: CurrentView.move({ 100.f, 0.f }); break;
		case 1: CurrentView.move({ -100.f, 0.f }); break;
		case 2: CurrentView.move({ 0.f, -100.f }); break;
		case 3: CurrentView.move({ 0.f, 100.f }); break;
		}
		setView(CurrentView);
	}

}
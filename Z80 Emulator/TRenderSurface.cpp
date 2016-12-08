#include "TRenderSurface.h"

namespace nne
{

	TRenderSurface::TRenderSurface()
	{
	}

	void TRenderSurface::render(sf::RenderTarget* SurfaceToRender)
	{
		sf::RenderStates states;

		states.transform *= getTransform();

		// Flip the back-buffer with the front-buffer
		display();

		// Get the texture from the back buffer
		mSprite.setTexture(getTexture());

		SurfaceToRender->draw(mSprite, states);
	}

}
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace nne
{

	class TRenderSurface : public sf::RenderTexture, public sf::Transformable
	{
	public:

		/// Default constructor
		TRenderSurface();

		/// Render this surface onto something else (usually the rendering window)
		void render(sf::RenderTarget* SurfaceToRender);

		void setZoomView(const float& ZoomLevel);
		const float& getZoomView() const;

		// Move the view
		void moveView(const std::size_t& Direction);
	private:
		float		mZoomLevel;
		sf::View	mCurrentView;
		sf::Sprite	mSprite;
	};
}
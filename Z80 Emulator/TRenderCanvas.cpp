#include "TRenderCanvas.h"

namespace nne
{
	namespace tgui
	{

		TRenderCanvas::TRenderCanvas() :
			mZoomLevel(1.f),
			mZoomFactor(25.f),
			mViewSize(0.f, 0.f),
			mViewPosition(0.f, 0.f)
		{
			setSize({ 1600.f, 900.f });
		}

		void TRenderCanvas::setSize(const sf::Vector2f& NewSize)
		{
			// Update base widget size
			TWidget::setSize(static_cast<sf::Vector2u>(NewSize));

			// set 
			mViewSize = NewSize;

			// Update the view size
			resetView();
		}

		void TRenderCanvas::setSize(const float& X, const float& Y)
		{
			setSize({ X, Y });
		}

		void TRenderCanvas::setPosition(const sf::Vector2f& NewPosition)
		{
			// Update base widget size
			TWidget::setPosition(NewPosition);

			mViewPosition = NewPosition;

			// Update the view position
			resetView();
		}

		void TRenderCanvas::setPosition(const float& X, const float& Y)
		{
			setPosition({X, Y});
		}
		
		void TRenderCanvas::zoom(const float& Factor)
		{
			auto CurrentView = getView();
			CurrentView.zoom(Factor);
			setView(CurrentView);
		}

		void TRenderCanvas::zoomIn()
		{
			// (100 + factor) : 100 = X : CurrentZoom
			// X = (100 + factor) * CurrentZoom / 100
			mZoomLevel = ((100 + mZoomFactor) * mZoomLevel) / 100.f;

			resetView();
		}

		void TRenderCanvas::zoomOut()
		{			
			// 100 : (100 + factor) = X : CurrentZoom
			// X = (100 * CurrentZoom) / (100 + factor)
			mZoomLevel = (100 * mZoomLevel) / (100 + mZoomFactor);

			resetView();
		}

		const float& TRenderCanvas::getZoomFactor() const
		{
			return mZoomLevel;
		}

		void TRenderCanvas::moveView(const sf::Vector2f& Offset)
		{
			mViewPosition += Offset;

			resetView();
		}

		void TRenderCanvas::render()
		{
			// Flip the back-buffer with the front-buffer
			display();

			// Get the texture from the back buffer
			mRenderSprite.setTexture(sf::RenderTexture::getTexture());
		}

		void TRenderCanvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();

			// Draw the sprite on the window
			target.draw(mRenderSprite, states);
		}
		
		void TRenderCanvas::resetView()
		{
			auto CurrentView = getView();
			CurrentView.setSize(mViewSize);
			CurrentView.setCenter(mViewSize / 2.f);
			CurrentView.move(mViewPosition);
			CurrentView.zoom(mZoomLevel);
			setView(CurrentView);
		}

		void TRenderCanvas::drawEntity(sf::Drawable& Entity)
		{
			sf::RenderTexture::draw(Entity);
		}

	}
}
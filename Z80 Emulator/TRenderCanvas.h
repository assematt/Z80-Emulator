#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "TWidget.h"

namespace nne
{
	namespace tgui
	{
		class TRenderCanvas : public TWidget, public sf::RenderTexture
		{
		public:
			using Ptr = std::shared_ptr<TRenderCanvas>;

			TRenderCanvas();
			
			/// Set the size of the canvas
			void setSize(const sf::Vector2f& NewSize);
			void setSize(const float& X, const float& Y);

			/// Set the position of the canvas
			void setPosition(const sf::Vector2f& NewPosition);
			void setPosition(const float& X, const float& Y);

			/// Function to zoom in/out
			void zoom(const float& Factor);
			void zoomIn();
			void zoomOut();
			const float& getZoomFactor() const;

			/// Move the view
			void moveView(const sf::Vector2f& Offset);

			/// Draw an object into the canvas
			void drawEntity(sf::Drawable& Entity);

			/// Render this surface onto something else (usually the rendering window)
			void render();
			
		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		private:
			void resetView();
			
		private:
			float				mZoomLevel;
			float				mZoomFactor;
			sf::View			mCurrentView;
			sf::Vector2f		mViewSize;
			sf::Vector2f		mViewPosition;
			mutable sf::Sprite	mRenderSprite;
		};
	}
}
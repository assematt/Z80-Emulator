#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <memory>

#include "IDGenerator.h"
#include "TStateManager.h"

namespace nne
{
	namespace tgui
	{
		class TGuiManager;

		// Base class for all the widgets
		class TWidget: public sf::Drawable, public sf::Transformable, public TStateManager
		{
		public:

			enum class TReferencePoint : sf::Uint8
			{
				LEFT_TOP,
				CENTER_TOP,
				RIGHT_TOP,

				LEFT_CENTER,
				CENTER,
				RIGHT_CENTER,

				LEFT_BOTTOM,
				CENTER_BOTTOM,
				RIGHT_BOTTOM,
			};

			enum class TState : sf::Uint8
			{
				NORMAL,
				HOVER,
				SELECTED,
				CLICKED,
				DISABLED
			};

			/// Typedef for a shared_ptr or the widget
			using Ptr = std::shared_ptr<TWidget>;

			/// Typedef for the widget ID
			using ID = std::size_t;

			/// Widget constructor
			TWidget();
			TWidget(TGuiManager& GuiManager);
			TWidget(const std::string& WidgetName);
			TWidget(TGuiManager& GuiManager, TWidget& Parent);
			TWidget(TGuiManager& GuiManager, const std::string& WidgetName);
			TWidget(TGuiManager& GuiManager, TWidget& Parent, const std::string& WidgetName);

			/// Copy constructor
			TWidget(const TWidget& Copy);

			/// Move constructor
			TWidget(TWidget&& Move);

			/// Virtual destructor
			virtual ~TWidget() = default;
			
			/// Get the ID
			const ID& getID() const;

			/// Get the parent transform
			const sf::Transform& getParentTransform() const;

			/// Set/get the input enable
			void enableInput(const bool& Enabled = true);
			const bool& isEnabled() const;

			/// Function to set/get the sprite texture
			void setTexture(const sf::Texture* Texture, bool UpdateBounds = true);
			const sf::Texture* getTexture() const;

			/// Function to set/get the sprite texture rect
			void setTextureRect(const sf::IntRect& Rectangle);
			const sf::IntRect& getTextureRect() const;

			/// Function to set/get the sprite color
			void setColor(const sf::Color& Color);
			const sf::Color& getColor() const;

			/// Function to set/get the sprite opacity
			void setOpacity(const sf::Uint8& Opacity);
			const sf::Uint8& getOpacity() const;

			void setZIndex(const std::size_t& ZIndex);
			const std::size_t& getZIndex() const;

			/// Set/Get widget name
			void setName(const std::string& WidgetName);
			const std::string& getName() const;

			/// Set/Get widget parent
			void setParent(const TWidget* WidgetParent);
			const TWidget* getParent() const;

			/// Set/Get widget parent
			void setManager(const TGuiManager& WidgetManager);
			const TGuiManager& getManager() const;

			/// Set/Get the widget size
			virtual void setSize(const sf::Vector2u& Size);
			virtual sf::Vector2u getSize();

			/// Get the position of a particular point of the widget without applying a transform
			virtual sf::Vector2f getWidgetReferencePointPosition(const TReferencePoint& ReferencePoint);

			/// Get the widget local bound
			virtual sf::FloatRect getLocalBound();

			/// Get the widget global bound
			virtual sf::FloatRect getGlobalBound();

			/// Copy the layout from another widget
			virtual void copyLayout(const TWidget& WidgetLayout);

			/// Return true if the current widget is selected or not
			void setSelected(const bool& Select);
			const bool& isSelected() const;

			/// Set the ability for 
			void setToggleable(const bool& Toggle);
			const bool& isToggleable() const;

			/// If the widget is 
			const bool& IsHovered() const;

		protected:
			/// Draw this widget
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

		private:
			/// Update the visible texture bound
			void updateTextureBounds(const sf::IntRect& TextureRect);

			/// Update the size of the sprite
			void updateSpriteBounds(const sf::Vector2u& SpriteSize);

		private:
			ID					mID;
			bool				mInputEnable;
			bool				mIsSelected;
			bool				mIsToggleable;
			bool				mIsHovered;
			TState				mState;
			std::size_t			mZIndex;
			sf::IntRect			mTextureRect;
			std::string			mName;
			const TWidget*		mParent;
			sf::VertexArray		mVertices;
			const sf::Texture*	mTexture;
			const TGuiManager*	mGuiManager;

			friend class TGuiManager;
		};
	}
}
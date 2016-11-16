#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>

#include "IComponent.h"
#include "TTransformable.h"
#include "TEntity.h"

namespace nne
{
	class TText : public IComponent//, public sf::Drawable
	{
	public:

		enum TStyle
		{
			Regular = 0,      ///< Regular characters, no style
			Bold = 1 << 0, ///< Bold characters
			Italic = 1 << 1, ///< Italic characters
			Underlined = 1 << 2, ///< Underlined characters
			StrikeThrough = 1 << 3  ///< Strike through characters
		};

		using TVertexArrayPtr = std::shared_ptr<sf::VertexArray>;

		
		TText();
		TText(const sf::String& String, const sf::Font& Font, unsigned int characterSize = 30);

		void setString(const sf::String& String);

		void setFont(const sf::Font& Font);

		void setCharacterSize(std::size_t Size);

		void setStyle(sf::Uint32 Style);

		void setFillColor(const sf::Color& Color);

		void setOutlineColor(const sf::Color& Color);

		void setOutlineThickness(float Thickness);

		const sf::String& getString() const;

		const sf::Font* getFont() const;

		std::size_t getCharacterSize() const;

		sf::Uint32 getStyle() const;

		const sf::Color& getFillColor() const;

		const sf::Color& getOutlineColor() const;

		float getOutlineThickness() const;

		sf::Vector2f findCharacterPos(std::size_t Index) const;

		sf::FloatRect getLocalBounds() const;

		sf::FloatRect getGlobalBounds() const;

		virtual void update() override;

		virtual void refresh() override;

		virtual void init() override;

		const sf::VertexArray& getVertexArray() const;

		const sf::Texture* getTexture() const;

	private:
		void ensureGeometryupdate() const;

	private:
		sf::String              mString;             ///< String to display
		const sf::Font*         mFont;               ///< Font used to display the string
		unsigned int			mCharacterSize;      ///< Base size of characters, in pixels
		sf::Uint32              mStyle;              ///< Text style (see Style enum)
		sf::Color               mFillColor;          ///< Text fill color
		sf::Color               mOutlineColor;       ///< Text outline color
		float					mOutlineThickness;   ///< Thickness of the text's outline
		mutable TVertexArrayPtr	mVertices;           ///< Vertex array containing the fill geometry
		mutable TVertexArrayPtr	mOutlineVertices;    ///< Vertex array containing the outline geometry
		mutable sf::FloatRect   mBounds;             ///< Bounding rectangle of the text (in local coordinates)
		mutable bool			mGeometryNeedupdate; ///< Does the geometry need to be recomputed?
	};

}
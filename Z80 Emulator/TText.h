#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
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

		void SetString(const sf::String& String);

		void SetFont(const sf::Font& Font);

		void SetCharacterSize(std::size_t Size);

		void SetStyle(sf::Uint32 Style);

		void SetFillColor(const sf::Color& Color);

		void SetOutlineColor(const sf::Color& Color);

		void SetOutlineThickness(float Thickness);

		const sf::String& GetString() const;

		const sf::Font* GetFont() const;

		std::size_t GetCharacterSize() const;

		sf::Uint32 GetStyle() const;

		const sf::Color& GetFillColor() const;

		const sf::Color& GetOutlineColor() const;

		float GetOutlineThickness() const;

		sf::Vector2f FindCharacterPos(std::size_t Index) const;

		sf::FloatRect GetLocalBounds() const;

		sf::FloatRect GetGlobalBounds() const;

		virtual void Update() override;

		virtual void Refresh() override;

		virtual void Init() override;

		const sf::VertexArray& GetVertexArray() const;

		const sf::Texture* GetTexture() const;

	private:
		void EnsureGeometryUpdate() const;

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
		mutable bool			mGeometryNeedUpdate; ///< Does the geometry need to be recomputed?
	};

}
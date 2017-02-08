#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <unordered_map>
#include <string>
#include <vector>

#include "IComponent.h"
#include "TEntity.h"
#include "TDrawableComponent.h"

namespace nne
{
	class TTextComponent : public IComponent
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

		template <class T>
		using TSpecialization = std::unordered_map<std::size_t, T>;
				
		TTextComponent();
		TTextComponent(const sf::String& String, const sf::Font& Font, const std::size_t& CharacterSize = 30);

		/// Set the component displayed text
		void setString(const sf::String& String);

		/// Set the font used by this component
		void setFont(const sf::Font& Font);

		/// Set the character size of this component
		void setCharacterSize(std::size_t Size);

		/// Set the style of this component
		void setStyle(sf::Uint32 Style);

		/// Set the fill color of the displayed text
		void setFillColor(const sf::Color& Color);

		/// Set the fill color of one single character text
		void setCharacterFillColor(const sf::Color& Color, const std::size_t CharacterPos);

		/// Set the fill color of a range of characters
		void setCharacterFillColor(const sf::Color& Color, const std::size_t& CharacterBegin, const std::size_t& CharacterEnd);

		/// Set the Outline color of the displayed test
		void setOutlineColor(const sf::Color& Color);

		/// Set the outline color of one single character text
		void setCharacterOutlineColor(const sf::Color& Color, const std::size_t CharacterPos);

		/// Set the outline color of a range of characters
		void setCharacterOutlineColor(const sf::Color& Color, const std::size_t& CharacterBegin, const std::size_t& CharacterEnd);

		/// Set the outline thickness of the displayed text
		void setOutlineThickness(float Thickness);

		/// Set the strike-through fill color
		void setStrikeThroughFillColor(const sf::Color& Color);

		/// Set the strike-through outline color
		void setStrikeThroughOutlineColor(const sf::Color& Color);

		/// Set the position of a single character in the text
		void setCharacterPosition(const std::size_t& CharacterPos, const sf::Vector2f& Position);
		void setCharacterPosition(const std::string& SubString, const sf::Vector2f& Position);

		void clearCharacterPosition();
		
		/// Get the displayed text as a sf::String
		const sf::String& getString() const;

		/// Get the font used by this component
		const sf::Font* getFont() const;

		/// Get the character size
		const std::size_t& getCharacterSize() const;

		/// Get the current style of component
		sf::Uint32 getStyle() const;

		/// Get the general fill color of the component
		const sf::Color& getFillColor() const;

		/// Get the general fill color of one single character text
		const sf::Color& getCharacterFillColor(const std::size_t& CharactePos) const;

		/// Get the general outline color of the component
		const sf::Color& getOutlineColor() const;

		/// Get the general outline color of one single character text
		const sf::Color& getCharacterOutlineColor(const std::size_t& CharactePos) const;

		/// Get the amount of the outline thickness of the component
		float getOutlineThickness() const;

		/// Get the strike-through color
		const sf::Color& getStrikeThroughFillColor() const;

		/// Get the strike-through outline color
		const sf::Color& getStrikeThroughOutlineColor() const;
				
		/// Get the local bounds of the component
		sf::FloatRect getLocalBounds() const;

		/// Get the local bounds of a single character in the string
		sf::FloatRect getCharacterLocalBounds(std::size_t Index);

		/// Get the global bounds of the component
		sf::FloatRect getGlobalBounds() const;

		/// Get the local bounds of a single character in the string
		sf::FloatRect getCharacterGlobalBounds(std::size_t Index);

		/// Get the vertex array (combining the outline vertex array an the normal vertex array)
		const sf::VertexArray& getVertexArray() const;

		/// Get the texture used by the text component at the current character size
		const sf::Texture* getTexture();

		/// Get the texture used by the text component using another character sizee
		const sf::Texture* getTexture(const std::size_t& CharacterSize);

		virtual void update(const sf::Time& ElapsedTime) override;

		virtual void refresh(const sf::Time& ElapsedTime) override;

		virtual void init() override;

	private:
		/// Renders the text
		void ensureGeometryUpdate() const;

		/// Compute the starting point for the normal vertex array
		std::size_t computeVerticesStartPos() const;

	private:
		sf::String						mString;					///< String to display
		const sf::Font*					mFont;						///< Font used to display the string
		unsigned int					mCharacterSize;				///< Base size of characters, in pixels
		sf::Uint32						mStyle;						///< Text style (see Style enum)
		sf::Color						mFillColor;					///< Text fill color
		sf::Color						mStrikeThroughFillColor;	///< Fill color for the StrikeThrough style, by default it's the same color of the Fill Color
		sf::Color						mUnderlineFillColor;		///< Fill color for the StrikeThrough style, by default it's the same color of the Fill Color
		sf::Color						mOutlineColor;				///< Text outline color
		sf::Color						mStrikeThroughOutlineColor; ///< Outline color for the StrikeThrough style, by default it's the same color of the outline Color
		sf::Color						mUnderlineOutlineColor;		///< Outline color for the StrikeThrough style, by default it's the same color of the outline Color
		float							mOutlineThickness;			///< Thickness of the text's outline
		mutable sf::FloatRect			mBounds;					///< Bounding rectangle of the text (in local coordinates)
		mutable bool					mGeometryNeedupdate;		///< Does the geometry need to be recomputed
		mutable sf::VertexArray			mVertices;					///< Vertex array containing the fill geometry
		TSpecialization<sf::Color>		mCharactersFillColor;		/// The individual fill color of the single character
		TSpecialization<sf::Color>		mCharactersOutlineColor;	/// The individual outline color of the single character
		TSpecialization<sf::Vector2f>	mCharactersPositions;		/// The individual position of the single character
	};

}
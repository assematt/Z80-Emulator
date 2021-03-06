#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>

namespace nne
{
	namespace tgui
	{
		class TComplexText : public sf::Drawable, public sf::Transformable
		{
		private:

			const int NotSet = std::numeric_limits<int>::max();

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

			TComplexText();
			TComplexText(const sf::String& String, const sf::Font& Font, const std::size_t& CharacterSize = 30);

			/// Set the component displayed text
			void setString(const sf::String& String);

			/// Set the font used by this component
			void setFont(const sf::Font& Font);

			/// Set the character size of this component
			void setCharacterSize(std::size_t Size);

			/// Set the character leading
			void setLeading(const int& Leading);

			/// Set the style of this component
			void setStyle(sf::Uint32 Style);

			/// Set the fill color of the displayed text
			void setFillColor(const sf::Color& Color, const bool& OverrideOtherColor = true);

			/// Set the text opacity
			void setOpacity(const sf::Uint8& Opacity);

			/// Set the fill color of one single character text
			void setCharacterFillColor(const sf::Color& Color, const std::size_t CharacterPos);

			/// Set the fill color of a range of characters
			void setCharacterFillColor(const sf::Color& Color, const std::size_t& CharacterBegin, const std::size_t& CharacterEnd);

			/// Set the Outline color of the displayed test
			void setOutlineColor(const sf::Color& Color, const bool& OverrideOtherColor = true);

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

			/// Get the displayed text as a sf::String
			const sf::String& getString() const;

			/// Get the font used by this component
			const sf::Font* getFont() const;

			/// Get the character size
			const std::size_t& getCharacterSize() const;

			/// Get the character leading
			const int& getLeading() const;

			/// Get the current style of component
			sf::Uint32 getStyle() const;

			/// Get the general fill color of the component
			const sf::Color& getFillColor() const;

			/// Get the text opacity
			const sf::Uint8& getOpacity() const;

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
			
		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		private:
			/// Renders the text
			void ensureGeometryUpdate() const;

			/// Compute the starting point for the normal vertex array
			std::size_t computeVerticesStartPos() const;

			/// Add an underline or strike through line to the vertex array
			void addLine(std::size_t CharactePos, float LineLength, float LineTop, const sf::Color& Color, float Offset, float Thickness, float OutlineThickness = 0) const;
		
			/// Add a glyph quad to the vertex array
			void addGlyphQuad(std::size_t CharactePos, sf::Vector2f Position, const sf::Color& Color, const sf::Glyph& Glyph, float Italic, float OutlineThickness = 0) const;

		private:
			int								mLeading;					///< Leading
			sf::String						mString;					///< String to display
			const sf::Font*					mFont;						///< Font used to display the string
			unsigned int					mCharacterSize;				///< Base size of characters, in pixels
			sf::Uint8						mOpacity;
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
}
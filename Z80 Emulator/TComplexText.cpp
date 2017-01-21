#include "TComplexText.h"

namespace nne
{
	

	namespace tgui
	{
		////////////////////////////////////////////////////////////
		TComplexText::TComplexText() :
			mString(),
			mFont(nullptr),
			mCharacterSize(30),
			mStyle(Regular),
			mFillColor(255, 255, 255),
			mOutlineColor(0, 0, 0),
			mOutlineThickness(0),
			mBounds(),
			mGeometryNeedupdate(false),
			mVertices(sf::Triangles),
			mStrikeThroughFillColor(255, 255, 255),
			mStrikeThroughOutlineColor(0, 0, 0),
			mUnderlineFillColor(255, 255, 255),
			mUnderlineOutlineColor(0, 0, 0),
			mLeading(NotSet)
		{
		}

		TComplexText::TComplexText(const sf::String& String, const sf::Font& Font, const std::size_t& CharacterSize/* = 30*/) :
			mString(String),
			mFont(&Font),
			mCharacterSize(CharacterSize),
			mStyle(Regular),
			mFillColor(255, 255, 255),
			mOutlineColor(0, 0, 0),
			mOutlineThickness(0),
			mBounds(),
			mGeometryNeedupdate(true),
			mVertices(sf::Triangles),
			mStrikeThroughFillColor(255, 255, 255),
			mStrikeThroughOutlineColor(0, 0, 0),
			mUnderlineFillColor(255, 255, 255),
			mUnderlineOutlineColor(0, 0, 0),
			mLeading(NotSet)
		{
		}

		void TComplexText::setString(const sf::String& String)
		{
			// If we are trying to replace the current string with the same string we can exit the function now
			if (mString == String)
				return;

			mString = String;
			mGeometryNeedupdate = true;

		}

		void TComplexText::setFont(const sf::Font& Font)
		{
			// If we are trying to replace the current font with the same font we can exit the function now
			if (mFont == &Font)
				return;

			mFont = &Font;
			mGeometryNeedupdate = true;
		}

		void TComplexText::setCharacterSize(std::size_t Size)
		{
			// If we are trying to replace the current character size with the same character size we can exit the function now
			if (mCharacterSize == Size)
				return;

			mCharacterSize = Size;
			mGeometryNeedupdate = true;
		}

		void TComplexText::setLeading(const int& Leading)
		{
			mLeading = Leading;
		}

		void TComplexText::setStyle(sf::Uint32 Style)
		{
			// If we are trying to replace the current style with the same style we can exit the function now
			if (mStyle == Style)
				return;

			mStyle = Style;
			mGeometryNeedupdate = true;
		}

		void TComplexText::setFillColor(const sf::Color& Color, const bool& OverrideOtherColor /*= true*/)
		{
			// If we are trying to replace the fill color with the same color we can exit the function now
			if (Color == mFillColor)
				return;

			// Replace the fill color
			mFillColor = Color;
			mStrikeThroughFillColor = Color;
			mUnderlineFillColor = Color;

			// Replace all the color for the individual character with the new fill color by clearing the std::unordered_map
			if (OverrideOtherColor)
				mCharactersFillColor.clear();

			// Change vertex colors directly, no need to update whole geometry, if geometry is updated anyway, we can skip this step
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				auto VertexCount = mVertices.getVertexCount();
// 				for (std::size_t Index = computeVerticesStartPos(); Index < VertexCount; ++Index)
// 					mVertices[Index].color = mFillColor;
// 			}
		}

		void TComplexText::setCharacterFillColor(const sf::Color& Color, const std::size_t CharacterPos)
		{
			// If we try to modify a character that doesn't exist
			if (CharacterPos > mString.getSize())
				return;

			// If we are trying to replace the fill color with the same color we can exit the function now
			if (mCharactersFillColor[CharacterPos] == Color)
				return;

			mCharactersFillColor[CharacterPos] = Color;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				auto StartPos = computeVerticesStartPos();
// 
// 				mVertices[CharacterPos * 6 + StartPos + 0].color = Color;
// 				mVertices[CharacterPos * 6 + StartPos + 1].color = Color;
// 				mVertices[CharacterPos * 6 + StartPos + 2].color = Color;
// 				mVertices[CharacterPos * 6 + StartPos + 3].color = Color;
// 				mVertices[CharacterPos * 6 + StartPos + 4].color = Color;
// 				mVertices[CharacterPos * 6 + StartPos + 5].color = Color;
// 			}
		}

		void TComplexText::setCharacterFillColor(const sf::Color& Color, const std::size_t& CharacterBegin, const std::size_t& CharacterEnd)
		{
			// If we try to modify a character that doesn't exist
			if (CharacterEnd > mString.getSize())
				return;

			for (std::size_t Index = CharacterBegin; Index <= CharacterEnd; ++Index)
				mCharactersFillColor[Index] = Color;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				for (std::size_t Index = CharacterBegin; Index <= CharacterEnd; ++Index)
// 				{
// 					auto StartPos = computeVerticesStartPos();
// 
// 					mVertices[Index * 6 + StartPos + 0].color = Color;
// 					mVertices[Index * 6 + StartPos + 1].color = Color;
// 					mVertices[Index * 6 + StartPos + 2].color = Color;
// 					mVertices[Index * 6 + StartPos + 3].color = Color;
// 					mVertices[Index * 6 + StartPos + 4].color = Color;
// 					mVertices[Index * 6 + StartPos + 5].color = Color;
// 				}
// 			}
		}

		void TComplexText::setOutlineColor(const sf::Color& Color, const bool& OverrideOtherColor /*= true*/)
		{
			// If we are trying to replace the outline color with the same color we can exit the function now
			if (Color == mOutlineColor)
				return;

			// Replace the outline color
			mOutlineColor = Color;
			mStrikeThroughOutlineColor = Color;
			mUnderlineOutlineColor = Color;

			// Replace all the color for the individual character with the new outline color by clearing the std::unordered_map
			if (OverrideOtherColor)
				mCharactersOutlineColor.clear();

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				auto VertexCount = mVertices.getVertexCount();
// 				for (std::size_t Index = 0; Index < VertexCount; ++Index)
// 					mVertices[Index].color = mOutlineColor;
// 			}
		}

		void TComplexText::setCharacterOutlineColor(const sf::Color& Color, const std::size_t CharacterPos)
		{
			// If we try to modify a character that doesn't exist
			if (CharacterPos > mString.getSize())
				return;

			// If we are trying to replace the fill color with the same color we can exit the function now
			if (mCharactersOutlineColor[CharacterPos] == Color)
				return;

			mCharactersOutlineColor[CharacterPos] = Color;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				mVertices[CharacterPos * 6 + 0].color = Color;
// 				mVertices[CharacterPos * 6 + 1].color = Color;
// 				mVertices[CharacterPos * 6 + 2].color = Color;
// 				mVertices[CharacterPos * 6 + 3].color = Color;
// 				mVertices[CharacterPos * 6 + 4].color = Color;
// 				mVertices[CharacterPos * 6 + 5].color = Color;
// 			}
		}

		void TComplexText::setCharacterOutlineColor(const sf::Color& Color, const std::size_t& CharacterBegin, const std::size_t& CharacterEnd)
		{
			// If we try to modify a character that doesn't exist
			if (CharacterEnd > mString.getSize())
				return;

			for (std::size_t Index = CharacterBegin; Index <= CharacterEnd; ++Index)
				mCharactersOutlineColor[Index] = Color;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				for (std::size_t Index = CharacterBegin; Index <= CharacterEnd; ++Index)
// 				{
// 					mVertices[Index * 6 + 0].color = Color;
// 					mVertices[Index * 6 + 1].color = Color;
// 					mVertices[Index * 6 + 2].color = Color;
// 					mVertices[Index * 6 + 3].color = Color;
// 					mVertices[Index * 6 + 4].color = Color;
// 					mVertices[Index * 6 + 5].color = Color;
// 				}
// 			}
		}

		void TComplexText::setOutlineThickness(float Thickness)
		{
			// If we are trying to replace the internal thickness with the same thickness we can exit the function now
			if (mOutlineThickness == Thickness)
				return;

			mOutlineThickness = Thickness;
			mGeometryNeedupdate = true;
		}

		void TComplexText::setStrikeThroughFillColor(const sf::Color& Color)
		{
			mStrikeThroughFillColor = Color;
		}

		void TComplexText::setStrikeThroughOutlineColor(const sf::Color& Color)
		{
			mStrikeThroughOutlineColor = Color;
		}

		void TComplexText::setCharacterPosition(const std::size_t& CharacterPos, const sf::Vector2f& Position)
		{
			// If we try to modify a character that doesn't exist
			if (CharacterPos > mString.getSize())
				return;

			// If we are trying to replace the fill color with the same color we can exit the function now
			if (mCharactersPositions[CharacterPos] == Position)
				return;

			mCharactersPositions[CharacterPos] = Position;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				auto StartPos = computeVerticesStartPos();
// 
// 				mVertices[CharacterPos * 6 + StartPos + 0].position += Position;
// 				mVertices[CharacterPos * 6 + StartPos + 1].position += Position;
// 				mVertices[CharacterPos * 6 + StartPos + 2].position += Position;
// 				mVertices[CharacterPos * 6 + StartPos + 3].position += Position;
// 				mVertices[CharacterPos * 6 + StartPos + 4].position += Position;
// 				mVertices[CharacterPos * 6 + StartPos + 5].position += Position;
// 			}
		}

		void TComplexText::setCharacterPosition(const std::string& SubString, const sf::Vector2f& Position)
		{
			// If we try to modify a character that doesn't exist
			if (SubString.size() > mString.getSize())
				return;

			auto SubStringStartPos = mString.toAnsiString().find(SubString);
			auto SubStringEndPos = SubStringStartPos + SubString.size();
			for (auto Index = SubStringStartPos; Index < SubStringEndPos; ++Index)
				mCharactersPositions[Index] = Position;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			mGeometryNeedupdate = true;
// 			if (!mGeometryNeedupdate)
// 			{
// 				auto StartPos = computeVerticesStartPos();
// 
// 				for (auto Index = SubStringStartPos; Index < SubStringEndPos; ++Index)
// 				{
// 					mVertices[Index * 6 + StartPos + 0].position += Position;
// 					mVertices[Index * 6 + StartPos + 1].position += Position;
// 					mVertices[Index * 6 + StartPos + 2].position += Position;
// 					mVertices[Index * 6 + StartPos + 3].position += Position;
// 					mVertices[Index * 6 + StartPos + 4].position += Position;
// 					mVertices[Index * 6 + StartPos + 5].position += Position;
// 				}
// 			}
// 			else
// 			{
// 				mGeometryNeedupdate = true;
// 			}
		}

		const sf::String& TComplexText::getString() const
		{
			return mString;
		}

		const sf::Font* TComplexText::getFont() const
		{
			return mFont;
		}

		const std::size_t& TComplexText::getCharacterSize() const
		{
			return mCharacterSize;
		}

		const int& TComplexText::getLeading() const
		{
			return mLeading;
		}

		sf::Uint32 TComplexText::getStyle() const
		{
			return mStyle;
		}

		const sf::Color& TComplexText::getFillColor() const
		{
			return mFillColor;
		}

		const sf::Color& TComplexText::getCharacterFillColor(const std::size_t& CharactePos) const
		{
			//return mCharactersFillColor[CharactePos];

			//auto Temp = mCharactersFillColor[CharactePos].a = 50;;
			return mCharactersFillColor.at(CharactePos);
		}

		const sf::Color& TComplexText::getOutlineColor() const
		{
			return mOutlineColor;
		}

		const sf::Color& TComplexText::getCharacterOutlineColor(const std::size_t& CharactePos) const
		{
			return mCharactersOutlineColor.at(CharactePos);
		}

		float TComplexText::getOutlineThickness() const
		{
			return mOutlineThickness;
		}

		const sf::Color& TComplexText::getStrikeThroughFillColor() const
		{
			return mStrikeThroughFillColor;
		}

		const sf::Color& TComplexText::getStrikeThroughOutlineColor() const
		{
			return mStrikeThroughOutlineColor;
		}

		sf::FloatRect TComplexText::getLocalBounds() const
		{
			ensureGeometryUpdate();

			return mBounds;
		}

		sf::FloatRect TComplexText::getCharacterLocalBounds(std::size_t Index)
		{
			// Make sure that we have a valid font
			if (!mFont)
				return sf::FloatRect();

			// Adjust the index if it's out of range
			if (Index > mString.getSize())
				Index = mString.getSize();

			// Precompute the variables needed by the algorithm
			bool  bold = (mStyle & Bold) != 0;
			float hspace = static_cast<float>(mFont->getGlyph(L' ', mCharacterSize, bold).advance);
			float vspace = static_cast<float>(mFont->getLineSpacing(mCharacterSize));

			// Compute the position
			sf::Vector2f position;
			sf::Uint32 prevChar = 0;
			for (std::size_t Index = 0; Index < Index; ++Index)
			{
				sf::Uint32 curChar = mString[Index];

				// Apply the kerning offset
				position.x += static_cast<float>(mFont->getKerning(prevChar, curChar, mCharacterSize));
				prevChar = curChar;

				// Handle special characters
				switch (curChar)
				{
				case ' ':  position.x += hspace;                 continue;
				case '\t': position.x += hspace * 4;             continue;
				case '\n': position.y += vspace; position.x = 0; continue;
				}

				// For regular characters, add the advance offset of the glyph
				position.x += static_cast<float>(mFont->getGlyph(curChar, mCharacterSize, bold).advance);
			}

			auto Bound = mFont->getGlyph(Index, mCharacterSize, bold).bounds;

			// Return the character local bound
			return sf::FloatRect(position, { Bound.width, Bound.height });
		}

		sf::FloatRect TComplexText::getGlobalBounds() const
		{
			return getTransform().transformRect(getLocalBounds());
		}

		sf::FloatRect TComplexText::getCharacterGlobalBounds(std::size_t Index)
		{
			return getTransform().transformRect(getCharacterLocalBounds(Index));
		}
		
		void TComplexText::ensureGeometryUpdate() const
		{
			// Do nothing, if geometry has not changed
			if (!mGeometryNeedupdate)
				return;

			// Mark geometry as updated
			mGeometryNeedupdate = false;

			// Clear the previous geometry
			mVertices.clear();
			mBounds = sf::FloatRect();

			// No font or text: nothing to draw
			if (!mFont || mString.isEmpty())
				return;

			// Compute values related to the text style
			bool  bold = (mStyle & TStyle::Bold) != 0;
			bool  underlined = (mStyle & TStyle::Underlined) != 0;
			bool  strikeThrough = (mStyle & TStyle::StrikeThrough) != 0;
			float italic = (mStyle & TStyle::Italic) ? 0.208f : 0.f; // 12 degrees
			float underlineOffset = mFont->getUnderlinePosition(mCharacterSize);
			float underlineThickness = mFont->getUnderlineThickness(mCharacterSize);

			// Compute the size of the vector
			auto StringLength = mString.getSize();

			// The minimum size it's at least the length of the string times 6 (each charter needs 6 vertex to display a char)
			std::size_t NewVectorSize = StringLength * 6;

			// Compute the beginning point of our vertex array
			std::size_t VerticesStartPos = computeVerticesStartPos();

			// If we have a underlined adds 6 vertices because this style needs those extra vertices, or 12 if we have a thickness value set
			if (underlined)
				NewVectorSize += mOutlineThickness > 0.f ? 12 : 6;

			// If we have a strike-through adds 6 vertices because this style needs those extra vertices, or 12 if we have a thickness value set
			if (strikeThrough)
				NewVectorSize += mOutlineThickness > 0.f ? 12 : 6;

			// If we have a thickness adds new vertices to accommodate for the new vertices
			if (mOutlineThickness > 0.f)
				NewVectorSize += StringLength * 6;

			// Resize the array
			mVertices.resize(NewVectorSize);

			// Compute the location of the strike through dynamically
			// We use the center point of the lowercase 'x' glyph as the reference
			// We reuse the underline thickness as the thickness of the strike through as well
			sf::FloatRect xBounds = mFont->getGlyph(L'x', mCharacterSize, bold).bounds;
			float strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

			// Precompute the variables needed by the algorithm
			float hspace = static_cast<float>(mFont->getGlyph(L' ', mCharacterSize, bold).advance);
			float vspace = mLeading == NotSet ? static_cast<float>(mFont->getLineSpacing(mCharacterSize)) : static_cast<float>(mLeading);
			float x = 0.f;
			float substringX = 0.f;
			float y = static_cast<float>(mCharacterSize);

			// Create one quad for each character
			float minX = static_cast<float>(mCharacterSize);
			float minY = static_cast<float>(mCharacterSize);
			float maxX = 0.f;
			float maxY = 0.f;
			sf::Uint32 prevChar = 0;
			for (std::size_t Index = 0; Index < mString.getSize(); ++Index)
			{
				sf::Uint32 curChar = mString[Index];

				// Apply the kerning offset
				x += mFont->getKerning(prevChar, curChar, mCharacterSize);

				if (mCharactersPositions.find(Index) != mCharactersPositions.end())
					substringX += mFont->getGlyph(curChar, mCharacterSize, bold).advance;
				else
					substringX = 0.f;

				// If we're using the underlined style and there's a new line, draw a line
				if (underlined && (curChar == L'\n') && (prevChar != L'\n'))
				{
					if (mOutlineThickness != 0)
						addLine(Index * 6, x, y, mUnderlineOutlineColor, underlineOffset, underlineThickness, mOutlineThickness);

					addLine(Index * 6 + VerticesStartPos, x, y, mUnderlineFillColor, underlineOffset, underlineThickness);
				}

				// If we're using the strike through style and there's a new line, draw a line across all characters
				if (strikeThrough && (curChar == L'\n') && (prevChar != L'\n'))
				{
					if (mOutlineThickness != 0)
						addLine((Index + 1) * 6, x, y, mStrikeThroughOutlineColor, strikeThroughOffset, underlineThickness, mOutlineThickness);

					addLine((Index + 1) * 6 + VerticesStartPos, x, y, mStrikeThroughFillColor, strikeThroughOffset, underlineThickness);
				}

				prevChar = curChar;

				// Handle special characters
				if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
				{
					// Update the current bounds (min coordinates)
					minX = std::min(minX, x);
					minY = std::min(minY, y);

					switch (curChar)
					{
					case ' ':  x += hspace;        break;
					case '\t': x += hspace * 4;    break;
					case '\n': y += vspace; x = 0; break;
					}

					// Update the current bounds (max coordinates)
					maxX = std::max(maxX, x);
					maxY = std::max(maxY, y);

					// Next glyph, no need to create a quad for whitespace
					continue;
				}

				// Apply the outline
				if (mOutlineThickness != 0)
				{
					const sf::Glyph& glyph = mFont->getGlyph(curChar, mCharacterSize, bold, mOutlineThickness);

					float left = glyph.bounds.left;
					float top = glyph.bounds.top;
					float right = glyph.bounds.left + glyph.bounds.width;
					float bottom = glyph.bounds.top + glyph.bounds.height;

					// Add the outline glyph to the vertices

					auto CharacterOutlineColor = mCharactersOutlineColor.find(Index);
					auto CharacterPos = mCharactersPositions.find(Index);
					addGlyphQuad(Index * 6, CharacterPos == mCharactersPositions.end() ? sf::Vector2f(x, y) : CharacterPos->second, CharacterOutlineColor == mCharactersOutlineColor.end() ? mOutlineColor : CharacterOutlineColor->second, glyph, italic, mOutlineThickness);

					// Update the current bounds with the outlined glyph bounds
					minX = std::min(minX, x + left - italic * bottom - mOutlineThickness);
					maxX = std::max(maxX, x + right - italic * top - mOutlineThickness);
					minY = std::min(minY, y + top - mOutlineThickness);
					maxY = std::max(maxY, y
						+ bottom - mOutlineThickness);
				}

				// Extract the current glyph's description
				const sf::Glyph& glyph = mFont->getGlyph(curChar, mCharacterSize, bold);

				// 
				auto CharacterFillColor = mCharactersFillColor.find(Index);
				auto CharacterPos = mCharactersPositions.find(Index);
				auto StadardPos = sf::Vector2f(x, y);
				char DebugChar = static_cast<char>(curChar);

				addGlyphQuad(Index * 6, CharacterPos == mCharactersPositions.end() ? StadardPos : (sf::Vector2f(substringX, y) + CharacterPos->second), CharacterFillColor == mCharactersFillColor.end() ? mFillColor : CharacterFillColor->second, glyph, italic, mOutlineThickness);

				// Update the current bounds with the non outlined glyph bounds
				if (mOutlineThickness == 0)
				{
					float left = glyph.bounds.left;
					float top = glyph.bounds.top;
					float right = glyph.bounds.left + glyph.bounds.width;
					float bottom = glyph.bounds.top + glyph.bounds.height;

					minX = std::min(minX, x + left - italic * bottom);
					maxX = std::max(maxX, x + right - italic * top);
					minY = std::min(minY, y + top);
					maxY = std::max(maxY, y + bottom);
				}

				// Advance to the next character
				x += glyph.advance;
			}

			// If we're using the underlined style, add the last line
			if (underlined && (x > 0))
			{
				if (mOutlineThickness != 0)
					addLine(VerticesStartPos - 12, x, y, mUnderlineOutlineColor, underlineOffset, underlineThickness, mOutlineThickness);

				addLine(NewVectorSize - 12, x, y, mUnderlineFillColor, underlineOffset, underlineThickness);
			}

			// If we're using the strike through style, add the last line across all characters
			if (strikeThrough && (x > 0))
			{
				if (mOutlineThickness != 0)
					addLine(VerticesStartPos - 6, x, y, mStrikeThroughOutlineColor, strikeThroughOffset, underlineThickness, mOutlineThickness);

				addLine(NewVectorSize - 6, x, y, mStrikeThroughFillColor, strikeThroughOffset, underlineThickness);
			}

			// Update the bounding rectangle
			mBounds.left = minX;
			mBounds.top = minY;
			mBounds.width = maxX - minX;
			mBounds.height = maxY - minY;
		}

		std::size_t TComplexText::computeVerticesStartPos() const
		{
			// The start position of the normal vertices is 0 if we don't have any thickness, so we can exit now with 0...
			if (mOutlineThickness == 0.f)
				return 0;

			// ... Otherwise is the length of the string times 6 (each charter needs 6 vertex to display a char)
			std::size_t ReturnValue = mString.getSize() * 6;

			// If we have a underlined adds 6 vertices because this style needs those extra vertices
			if ((mStyle & TStyle::Underlined) != 0)
				ReturnValue += 6;

			// If we have a strike-through adds 6 vertices because this style needs those extra vertices
			if ((mStyle & TStyle::StrikeThrough) != 0)
				ReturnValue += 6;

			return ReturnValue;
		}

		void TComplexText::addLine(std::size_t CharactePos, float LineLength, float LineTop, const sf::Color& Color, float Offset, float Thickness, float OutlineThickness /*= 0*/) const
{
			float top = std::floor(LineTop + Offset - (Thickness / 2) + 0.5f);
			float bottom = top + std::floor(Thickness + 0.5f);

			mVertices[CharactePos + 0] = sf::Vertex(sf::Vector2f(-OutlineThickness, top - OutlineThickness), Color, sf::Vector2f(1, 1));
			mVertices[CharactePos + 1] = sf::Vertex(sf::Vector2f(LineLength + OutlineThickness, top - OutlineThickness), Color, sf::Vector2f(1, 1));
			mVertices[CharactePos + 2] = sf::Vertex(sf::Vector2f(-OutlineThickness, bottom + OutlineThickness), Color, sf::Vector2f(1, 1));
			mVertices[CharactePos + 3] = sf::Vertex(sf::Vector2f(-OutlineThickness, bottom + OutlineThickness), Color, sf::Vector2f(1, 1));
			mVertices[CharactePos + 4] = sf::Vertex(sf::Vector2f(LineLength + OutlineThickness, top - OutlineThickness), Color, sf::Vector2f(1, 1));
			mVertices[CharactePos + 5] = sf::Vertex(sf::Vector2f(LineLength + OutlineThickness, bottom + OutlineThickness), Color, sf::Vector2f(1, 1));
		}

		void TComplexText::addGlyphQuad(std::size_t CharactePos, sf::Vector2f Position, const sf::Color& Color, const sf::Glyph& Glyph, float Italic, float OutlineThickness /*= 0*/) const
{
			float left = Glyph.bounds.left;
			float top = Glyph.bounds.top;
			float right = Glyph.bounds.left + Glyph.bounds.width;
			float bottom = Glyph.bounds.top + Glyph.bounds.height;

			float u1 = static_cast<float>(Glyph.textureRect.left);
			float v1 = static_cast<float>(Glyph.textureRect.top);
			float u2 = static_cast<float>(Glyph.textureRect.left + Glyph.textureRect.width);
			float v2 = static_cast<float>(Glyph.textureRect.top + Glyph.textureRect.height);

			mVertices[CharactePos + 0] = sf::Vertex(sf::Vector2f(Position.x + left - Italic * top - OutlineThickness, Position.y + top - OutlineThickness), Color, sf::Vector2f(u1, v1));
			mVertices[CharactePos + 1] = sf::Vertex(sf::Vector2f(Position.x + right - Italic * top - OutlineThickness, Position.y + top - OutlineThickness), Color, sf::Vector2f(u2, v1));
			mVertices[CharactePos + 2] = sf::Vertex(sf::Vector2f(Position.x + left - Italic * bottom - OutlineThickness, Position.y + bottom - OutlineThickness), Color, sf::Vector2f(u1, v2));
			mVertices[CharactePos + 3] = sf::Vertex(sf::Vector2f(Position.x + left - Italic * bottom - OutlineThickness, Position.y + bottom - OutlineThickness), Color, sf::Vector2f(u1, v2));
			mVertices[CharactePos + 4] = sf::Vertex(sf::Vector2f(Position.x + right - Italic * top - OutlineThickness, Position.y + top - OutlineThickness), Color, sf::Vector2f(u2, v1));
			mVertices[CharactePos + 5] = sf::Vertex(sf::Vector2f(Position.x + right - Italic * bottom - OutlineThickness, Position.y + bottom - OutlineThickness), Color, sf::Vector2f(u2, v2));
		}

		void TComplexText::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			if (mFont)
			{
				ensureGeometryUpdate();

				states.transform *= getTransform();
				states.texture = &mFont->getTexture(mCharacterSize);

				target.draw(mVertices, states);
			}
		}

	}
}
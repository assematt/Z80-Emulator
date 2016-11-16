#include "TText.h"

namespace nne
{
	// Add an underline or strike through line to the vertex array
	void AddLine(sf::VertexArray& Vertices, float LineLength, float LineTop, const sf::Color& Color, float Offset, float Thickness, float OutlineThickness = 0)
	{
		float top = std::floor(LineTop + Offset - (Thickness / 2) + 0.5f);
		float bottom = top + std::floor(Thickness + 0.5f);

		Vertices.append(sf::Vertex(sf::Vector2f(-OutlineThickness, top - OutlineThickness), Color, sf::Vector2f(1, 1)));
		Vertices.append(sf::Vertex(sf::Vector2f(LineLength + OutlineThickness, top - OutlineThickness), Color, sf::Vector2f(1, 1)));
		Vertices.append(sf::Vertex(sf::Vector2f(-OutlineThickness, bottom + OutlineThickness), Color, sf::Vector2f(1, 1)));
		Vertices.append(sf::Vertex(sf::Vector2f(-OutlineThickness, bottom + OutlineThickness), Color, sf::Vector2f(1, 1)));
		Vertices.append(sf::Vertex(sf::Vector2f(LineLength + OutlineThickness, top - OutlineThickness), Color, sf::Vector2f(1, 1)));
		Vertices.append(sf::Vertex(sf::Vector2f(LineLength + OutlineThickness, bottom + OutlineThickness), Color, sf::Vector2f(1, 1)));
	}

	// Add a glyph quad to the vertex array
	void AddGlyphQuad(sf::VertexArray& Vertices, sf::Vector2f Position, const sf::Color& Color, const sf::Glyph& Glyph, float Italic, float OutlineThickness = 0)
	{
		float left = Glyph.bounds.left;
		float top = Glyph.bounds.top;
		float right = Glyph.bounds.left + Glyph.bounds.width;
		float bottom = Glyph.bounds.top + Glyph.bounds.height;

		float u1 = static_cast<float>(Glyph.textureRect.left);
		float v1 = static_cast<float>(Glyph.textureRect.top);
		float u2 = static_cast<float>(Glyph.textureRect.left + Glyph.textureRect.width);
		float v2 = static_cast<float>(Glyph.textureRect.top + Glyph.textureRect.height);

		Vertices.append(sf::Vertex(sf::Vector2f(Position.x + left - Italic * top - OutlineThickness, Position.y + top - OutlineThickness), Color, sf::Vector2f(u1, v1)));
		Vertices.append(sf::Vertex(sf::Vector2f(Position.x + right - Italic * top - OutlineThickness, Position.y + top - OutlineThickness), Color, sf::Vector2f(u2, v1)));
		Vertices.append(sf::Vertex(sf::Vector2f(Position.x + left - Italic * bottom - OutlineThickness, Position.y + bottom - OutlineThickness), Color, sf::Vector2f(u1, v2)));
		Vertices.append(sf::Vertex(sf::Vector2f(Position.x + left - Italic * bottom - OutlineThickness, Position.y + bottom - OutlineThickness), Color, sf::Vector2f(u1, v2)));
		Vertices.append(sf::Vertex(sf::Vector2f(Position.x + right - Italic * top - OutlineThickness, Position.y + top - OutlineThickness), Color, sf::Vector2f(u2, v1)));
		Vertices.append(sf::Vertex(sf::Vector2f(Position.x + right - Italic * bottom - OutlineThickness, Position.y + bottom - OutlineThickness), Color, sf::Vector2f(u2, v2)));
	}
}

namespace nne
{
	////////////////////////////////////////////////////////////
	TText::TText() :
		mString(),
		mFont(nullptr),
		mCharacterSize(30),
		mStyle(Regular),
		mFillColor(255, 255, 255),
		mOutlineColor(0, 0, 0),
		mOutlineThickness(0),
		mBounds(),
		mGeometryNeedupdate(false)
	{
		mVertices = std::make_shared<sf::VertexArray>(sf::Triangles);
		mOutlineVertices = std::make_shared<sf::VertexArray>(sf::Triangles);
	}

	TText::TText(const sf::String& String, const sf::Font& Font, unsigned int characterSize) :
		mString(String),
		mFont(&Font),
		mCharacterSize(characterSize),
		mStyle(Regular),
		mFillColor(255, 255, 255),
		mOutlineColor(0, 0, 0),
		mOutlineThickness(0),
		mBounds(),
		mGeometryNeedupdate(true)
	{
		mVertices = std::make_shared<sf::VertexArray>(sf::Triangles);
		mOutlineVertices = std::make_shared<sf::VertexArray>(sf::Triangles);
	}

	void TText::setString(const sf::String& String)
	{
		if (mString != String)
		{
			mString = String;
			mGeometryNeedupdate = true;
		}
	}

	void TText::setFont(const sf::Font& Font)
	{
		if (mFont != &Font)
		{
			mFont = &Font;
			mGeometryNeedupdate = true;
		}
	}

	void TText::setCharacterSize(std::size_t Size)
	{
		if (mCharacterSize != Size)
		{
			mCharacterSize = Size;
			mGeometryNeedupdate = true;
		}
	}

	void TText::setStyle(sf::Uint32 Style)
	{
		if (mStyle != Style)
		{
			mStyle = Style;
			mGeometryNeedupdate = true;
		}
	}
	
	void TText::setFillColor(const sf::Color& Color)
	{
		if (Color != mFillColor)
		{
			mFillColor = Color;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			if (!mGeometryNeedupdate)
			{
				for (std::size_t i = 0; i < (*mVertices).getVertexCount(); ++i)
					(*mVertices)[i].color = mFillColor;
			}
		}
	}

	void TText::setOutlineColor(const sf::Color& Color)
	{
		if (Color != mOutlineColor)
		{
			mOutlineColor = Color;

			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
			if (!mGeometryNeedupdate)
			{
				for (std::size_t i = 0; i < (*mOutlineVertices).getVertexCount(); ++i)
					(*mOutlineVertices)[i].color = mOutlineColor;
			}
		}
	}

	void TText::setOutlineThickness(float Thickness)
	{
		if (Thickness != mOutlineThickness)
		{
			mOutlineThickness = Thickness;
			mGeometryNeedupdate = true;
		}
	}

	const sf::String& TText::getString() const
	{
		return mString;
	}

	const sf::Font* TText::getFont() const
	{
		return mFont;
	}

	std::size_t TText::getCharacterSize() const
	{
		return mCharacterSize;
	}

	sf::Uint32 TText::getStyle() const
	{
		return mStyle;
	}

	const sf::Color& TText::getFillColor() const
	{
		return mFillColor;
	}

	const sf::Color& TText::getOutlineColor() const
	{
		return mOutlineColor;
	}

	float TText::getOutlineThickness() const
	{
		return mOutlineThickness;
	}

	sf::Vector2f TText::findCharacterPos(std::size_t Index) const
	{
		// Make sure that we have a valid font
		if (!mFont)
			return sf::Vector2f();

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
		for (std::size_t i = 0; i < Index; ++i)
		{
			sf::Uint32 curChar = mString[i];

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

		// Transform the position to global coordinates
		position = mParent->getComponentAsPtr<TTransformable>()->getTransform().transformPoint(position);

		return position;
	}

	sf::FloatRect TText::getLocalBounds() const
	{
		ensureGeometryupdate();

		return mBounds;
	}
	
	sf::FloatRect TText::getGlobalBounds() const
	{
		return mParent->getComponentAsPtr<TTransformable>()->getTransform().transformRect(getLocalBounds());
	}

	void TText::update()
	{
	}

	void TText::refresh()
	{
		if (!mGeometryNeedupdate)
			return;

		ensureGeometryupdate();
		mGeometryNeedupdate = false;
	}

	void TText::init()
	{
		mParent->getComponentAsPtr<TdrawableVector>()->pushdrawableObject({ mOutlineVertices });
		mParent->getComponentAsPtr<TdrawableVector>()->pushdrawableObject({ mVertices });
	}

	const sf::VertexArray& TText::getVertexArray() const
	{
		return *mVertices;
	}

	const sf::Texture* TText::getTexture() const
	{
		return &mFont->getTexture(mCharacterSize);
	}

	void TText::ensureGeometryupdate() const
{
		// Do nothing, if geometry has not changed
		if (!mGeometryNeedupdate)
			return;

		// Mark geometry as updated
		mGeometryNeedupdate = false;

		// Clear the previous geometry
		(*mVertices).clear();
		(*mOutlineVertices).clear();
		mBounds = sf::FloatRect();

		// No font or text: nothing to draw
		if (!mFont || mString.isEmpty())
			return;

		// Compute values related to the text style
		bool  bold = (mStyle & Bold) != 0;
		bool  underlined = (mStyle & Underlined) != 0;
		bool  strikeThrough = (mStyle & StrikeThrough) != 0;
		float italic = (mStyle & Italic) ? 0.208f : 0.f; // 12 degrees
		float underlineOffset = mFont->getUnderlinePosition(mCharacterSize);
		float underlineThickness = mFont->getUnderlineThickness(mCharacterSize);

		// Compute the location of the strike through dynamically
		// We use the center point of the lowercase 'x' glyph as the reference
		// We reuse the underline thickness as the thickness of the strike through as well
		sf::FloatRect xBounds = mFont->getGlyph(L'x', mCharacterSize, bold).bounds;
		float strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

		// Precompute the variables needed by the algorithm
		float hspace = static_cast<float>(mFont->getGlyph(L' ', mCharacterSize, bold).advance);
		float vspace = static_cast<float>(mFont->getLineSpacing(mCharacterSize));
		float x = 0.f;
		float y = static_cast<float>(mCharacterSize);

		// Create one quad for each character
		float minX = static_cast<float>(mCharacterSize);
		float minY = static_cast<float>(mCharacterSize);
		float maxX = 0.f;
		float maxY = 0.f;
		sf::Uint32 prevChar = 0;
		for (std::size_t i = 0; i < mString.getSize(); ++i)
		{
			sf::Uint32 curChar = mString[i];

			// Apply the kerning offset
			x += mFont->getKerning(prevChar, curChar, mCharacterSize);
			prevChar = curChar;

			// If we're using the underlined style and there's a new line, draw a line
			if (underlined && (curChar == L'\n'))
			{
				AddLine((*mVertices), x, y, mFillColor, underlineOffset, underlineThickness);

				if (mOutlineThickness != 0)
					AddLine((*mOutlineVertices), x, y, mOutlineColor, underlineOffset, underlineThickness, mOutlineThickness);
			}

			// If we're using the strike through style and there's a new line, draw a line across all characters
			if (strikeThrough && (curChar == L'\n'))
			{
				AddLine((*mVertices), x, y, mFillColor, strikeThroughOffset, underlineThickness);

				if (mOutlineThickness != 0)
					AddLine((*mOutlineVertices), x, y, mOutlineColor, strikeThroughOffset, underlineThickness, mOutlineThickness);
			}

			// Handle special characters
			if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
			{
				// update the current bounds (min coordinates)
				minX = std::min(minX, x);
				minY = std::min(minY, y);

				switch (curChar)
				{
				case ' ':  x += hspace;        break;
				case '\t': x += hspace * 4;    break;
				case '\n': y += vspace; x = 0; break;
				}

				// update the current bounds (max coordinates)
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
				nne::AddGlyphQuad((*mOutlineVertices), sf::Vector2f(x, y), mOutlineColor, glyph, italic, mOutlineThickness);

				// update the current bounds with the outlined glyph bounds
				minX = std::min(minX, x + left - italic * bottom - mOutlineThickness);
				maxX = std::max(maxX, x + right - italic * top - mOutlineThickness);
				minY = std::min(minY, y + top - mOutlineThickness);
				maxY = std::max(maxY, y + bottom - mOutlineThickness);
			}

			// Extract the current glyph's description
			const sf::Glyph& glyph = mFont->getGlyph(curChar, mCharacterSize, bold);

			// Add the glyph to the vertices
			nne::AddGlyphQuad((*mVertices), sf::Vector2f(x, y), mFillColor, glyph, italic);

			// update the current bounds with the non outlined glyph bounds
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
			AddLine((*mVertices), x, y, mFillColor, underlineOffset, underlineThickness);

			if (mOutlineThickness != 0)
				AddLine((*mOutlineVertices), x, y, mOutlineColor, underlineOffset, underlineThickness, mOutlineThickness);
		}

		// If we're using the strike through style, add the last line across all characters
		if (strikeThrough && (x > 0))
		{
			AddLine((*mVertices), x, y, mFillColor, strikeThroughOffset, underlineThickness);

			if (mOutlineThickness != 0)
				AddLine((*mOutlineVertices), x, y, mOutlineColor, strikeThroughOffset, underlineThickness, mOutlineThickness);
		}

		// update the bounding rectangle
		mBounds.left = minX;
		mBounds.top = minY;
		mBounds.width = maxX - minX;
		mBounds.height = maxY - minY;
	}
}
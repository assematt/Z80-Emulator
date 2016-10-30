#include "TFont.h"

namespace nne
{
	TFont::TFont() :
		mStyle(TStyle::NORMAL),
		mCharDefaultSize(40),
		mCharCurrentSize(40),
		mCharWidth(45),
		mCharHeight(45),
		mCharMap({ { 'A', 32 },{ 'B', 33 },{ 'C', 32 },{ 'D', 32 },{ 'E', 32 },{ 'F', 32 },{ 'G', 32 },{ 'H', 31 },{ 'I', 13 },{ 'J', 32 },{ 'K', 32 },{ 'L', 32 },{ 'M', 44 },{ 'N', 32 },{ 'O', 32 },{ 'P', 32 },{ 'Q', 32 },{ 'R', 32 },{ 'S', 32 },{ 'T', 32 },{ 'U', 32 },{ 'V', 32 },{ 'W', 45 },{ 'X', 32 },{ 'Y', 32 },{ 'Z', 32 },
		{ '0', 26 },{ '1', 16 },{ '2', 25 },{ '3', 25 },{ '4', 28 },{ '5', 25 },{ '6', 26 },{ '7', 26 },{ '8', 25 },{ '9', 26 },
		{ '!', 11 },{ '?', 32 },{ ',', 12 },{ ';', 12 },{ '.', 11 },{ ':', 11 },{ '-', 32 },{ '_', 38 },{ '#', 32 },{ '(', 17 },{ ')', 17 },{ '[', 23 },{ ']', 23 },{ '=', 32 },{ '$', 32 },{ '/', 32 },{ ' ', 24 }
	})
	{
	}

	const std::pair<sf::FloatRect, const TCharStruct&> TFont::ExtractCharacter(const char Char) const
	{
		// Get the number of char in the map
		auto CharMapSize = mCharMap.size();

		// Initialize the index
		auto Index = 0u;

		// Keep looking in the array until we found the char (toupper(Char) != mCharMap[Index++]) or we iterate through the entire vector (Index < CharMapSize)
		while (Index < CharMapSize && mCharMap[Index++] != toupper(Char));

		// Return the coordinate of the char in the texture and the char struct
		return{ sf::FloatRect((Index - 1) * mCharWidth, mCharHeight * mStyle, mCharMap[Index - 1].mCharWidth, mCharHeight), mCharMap[Index - 1] };
	}

	void TFont::Init()
	{
		mDrawableComponent = mParent->GetComponentAsPtr<TTexture>();
	}

	void TFont::SetFontSize(sf::Uint16 Size)
	{
		mCharCurrentSize = Size;
	}

	void TFont::SetText(const std::string& String)
	{
		mText = String;

		RenderText();
	}

	void TFont::SetStyle(TStyle Style)
	{
		mStyle = Style;

		RenderText();
	}

	const TFont::TStyle& TFont::GetStyle() const
	{
		return mStyle;
	}

	const sf::Uint16 & TFont::GetFontSize() const
	{
		return mCharCurrentSize;
	}

	const sf::Uint16& TFont::GetCharacterDefaultSize() const
	{
		return mCharDefaultSize;
	}

	const std::string& TFont::GetText() const
	{
		return mText;
	}

	void TFont::RenderText()
	{
		// Get the vertices array
		auto& Vertices = mDrawableComponent->GetVertexArray();

		// Resize the array to fit the entire text
		Vertices.resize(mText.size() * 4);

		// Keep count of how many element we are iterating
		int Index = 0;

		// Keep track of the left origin of the next chat to print
		int RightOffset = 0;

		// Iterate the string to display
		for (auto& Char : mText)
		{
			// Get the position of the char in the texture
			auto& CharStruct = ExtractCharacter(Char);

			// The amount of scale to adjust
			float CharScale = static_cast<float>(mCharCurrentSize) / mCharDefaultSize;

			// Set the position of the char and scales it appropriately 
			Vertices[Index * 4 + 0].position = sf::Vector2f(RightOffset, 0.f) * CharScale;
			Vertices[Index * 4 + 1].position = sf::Vector2f(RightOffset + CharStruct.second.mCharWidth, 0.f) * CharScale;
			Vertices[Index * 4 + 2].position = sf::Vector2f(RightOffset + CharStruct.second.mCharWidth, mCharHeight) * CharScale;
			Vertices[Index * 4 + 3].position = sf::Vector2f(RightOffset, mCharHeight) * CharScale;

			// Set the coordinate of the char texture
			Vertices[Index * 4 + 0].texCoords = { CharStruct.first.left, CharStruct.first.top };
			Vertices[Index * 4 + 1].texCoords = { CharStruct.first.left + CharStruct.first.width, CharStruct.first.top };
			Vertices[Index * 4 + 2].texCoords = { CharStruct.first.left + CharStruct.first.width, CharStruct.first.top + CharStruct.first.height };
			Vertices[Index * 4 + 3].texCoords = { CharStruct.first.left, CharStruct.first.top + CharStruct.first.height };

			// Increments the index
			++Index;

			// Add the width of the char to the offset 
			RightOffset += CharStruct.second.mCharWidth;
		}
	}
}


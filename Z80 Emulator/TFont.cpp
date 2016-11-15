#include "TFont.h"

namespace nne
{

// 	TFont::TFont() :
// 		mFontType(TFontType::STANDARD),
// 		mFontVertexArray(sf::Quads, 10),
// 		mStyle(0),
// 		mCharDefaultSize(40),
// 		mCharWidth(45),
// 		mCharHeight(45),
// 		mCharMap({ { 'A', 32 },{ 'B', 33 },{ 'C', 32 },{ 'D', 32 },{ 'E', 32 },{ 'F', 32 },{ 'G', 32 },{ 'H', 31 },{ 'I', 13 },{ 'J', 32 },{ 'K', 32 },{ 'L', 32 },{ 'M', 44 },{ 'N', 32 },{ 'O', 32 },{ 'P', 32 },{ 'Q', 32 },{ 'R', 32 },{ 'S', 32 },{ 'T', 32 },{ 'U', 32 },{ 'V', 32 },{ 'W', 45 },{ 'X', 32 },{ 'Y', 32 },{ 'Z', 32 },
// 		{ '0', 26 },{ '1', 16 },{ '2', 25 },{ '3', 25 },{ '4', 28 },{ '5', 25 },{ '6', 26 },{ '7', 26 },{ '8', 25 },{ '9', 26 },
// 		{ '!', 11 },{ '?', 32 },{ ',', 12 },{ ';', 12 },{ '.', 11 },{ ':', 11 },{ '-', 32 },{ '_', 38 },{ '#', 32 },{ '(', 17 },{ ')', 17 },{ '[', 23 },{ ']', 23 },{ '=', 32 },{ '$', 32 },{ '/', 32 },{ ' ', 24 }
// 	})
// 	{	
// 	}
// 
// 	bool TFont::LoadFromFile(const std::string& Path, bool IsStandardFont /*= true*/)
// 	{
// 		bool Result;
// 
// 		// If we are try to load a standard font
// 		if (IsStandardFont)
// 		{
// 			mFontType = TFontType::STANDARD;
// 			Result = mStandardFont.loadFromFile(Path);
// 		}
// 		// Load a custom font
// 		else
// 		{
// 			mFontType = TFontType::CUSTOM;
// 			sf::Texture TempTxt;
// 			Result = TempTxt.loadFromFile(Path);
// 			mCustomFont->SetTexture(TempTxt);
// 		}
// 
// 		return Result;
// 	}
// 
// 	const sf::Texture* TFont::GetFontTexture(const std::size_t CharacterSize) const
// 	{
// 		// If we loaded a standard font
// 		if (mFontType == TFontType::STANDARD)
// 			return &(mStandardFont.getTexture(CharacterSize));
// 		
// 		return &mCustomFont->GetTexture();
// 	}
// 
// 	const TFont::TFontType& TFont::GetFontType() const
// 	{
// 		return mFontType;
// 	}
// 
// 	void TFont::UpdateTextGeometry(const std::string& Text, const sf::Uint32 CharacterSize)
// 	{
// 		if (Text == "")
// 			return;
// 
// 		// Create a vertex array of proper length
// 		mFontVertexArray.resize(Text.size() * 4);
// 
// 		// Keep count of how many element we are iterating
// 		int Index = 0;
// 
// 		// Keep track of the left origin of the next chat to print
// 		int RightOffset = 0;
// 
// 		// Iterate the string to display
// 		for (auto& Char : Text)
// 		{
// 			// Get the position of the char in the texture
// 			TGlyph CharStruct = ExtractCharacter(Char, CharacterSize);
// 
// 			// Get the char width/heigth
// 			auto CharWidth = CharStruct.second.mCharWidth;
// 			auto CharHeight = mCharHeight;
// 
// 
// 			// The amount of scale to adjust
// 			//float CharScale = mIsStandardFontLoaded ? 1.f : static_cast<float>(CharacterSize) / mCharDefaultSize;
// 			float CharScale = static_cast<float>(CharacterSize) / mCharDefaultSize;
// 
// 			// Set the position of the char and scales it appropriately 
// 			mFontVertexArray[Index * 4 + 0].position = sf::Vector2f(RightOffset, 0.f) * CharScale;
// 			mFontVertexArray[Index * 4 + 1].position = sf::Vector2f(RightOffset + CharWidth, 0.f) * CharScale;
// 			mFontVertexArray[Index * 4 + 2].position = sf::Vector2f(RightOffset + CharWidth, CharHeight) * CharScale;
// 			mFontVertexArray[Index * 4 + 3].position = sf::Vector2f(RightOffset, CharHeight) * CharScale;
// 
// 			// Set the coordinate of the char texture
// 			mFontVertexArray[Index * 4 + 0].texCoords = { CharStruct.first.left, CharStruct.first.top };
// 			mFontVertexArray[Index * 4 + 1].texCoords = { CharStruct.first.left + CharStruct.first.width, CharStruct.first.top };
// 			mFontVertexArray[Index * 4 + 2].texCoords = { CharStruct.first.left + CharStruct.first.width, CharStruct.first.top + CharStruct.first.height };
// 			mFontVertexArray[Index * 4 + 3].texCoords = { CharStruct.first.left, CharStruct.first.top + CharStruct.first.height };
// 
// 			// Increments the index
// 			++Index;
// 
// 			// Add the width of the char to the offset 
// 			RightOffset += CharStruct.second.mCharWidth;
// 		}
// 	}
// 
// 	void TFont::Update()
// 	{
// 
// 	}
// 
// 	void TFont::Init()
// 	{
// 		mCustomFont = std::make_shared<TSprite>(*mParent->GetComponentAsPtr<TSprite>());
// 	}
// 
// 	const TFont::TGlyph TFont::ExtractCharacter(const char Char, const sf::Uint32 CharacterSize) const
// 	{
// 		// Get the number of char in the map
// 		auto CharMapSize = mCharMap.size();
// 
// 		// Initialize the index
// 		auto Index = 0u;
// 
// 		// Keep looking in the array until we found the char (toupper(Char) != mCharMap[Index++]) or we iterate through the entire vector (Index < CharMapSize)
// 		while (Index < CharMapSize && mCharMap[Index++] != toupper(Char));
// 
// 		// Return the coordinate of the char in the texture and the char struct
// 		return{ sf::FloatRect((Index - 1) * mCharWidth, mCharHeight * mStyle, mCharMap[Index - 1].mCharWidth, mCharHeight), mCharMap[Index - 1] };
// 	}

}
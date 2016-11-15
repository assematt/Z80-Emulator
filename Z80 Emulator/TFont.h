#pragma once

#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <memory>

#include "TCacheManager.h"
#include "TLoaders.h"
#include "IComponent.h"
#include "TSprite.h"
#include "TCharStruct.h"

namespace nne
{
// 	class _TTextOld;
// 
// 	class TFont : public IComponent
// 	{
// 	public:
// 		using TGlyph = std::pair<sf::FloatRect, const TCharStruct&>;
// 
// 		enum class TFontType : bool
// 		{
// 			CUSTOM = true,
// 			STANDARD = false
// 		};
// 
// 		TFont();
// 		
// 		/// Data loading
// 		bool LoadFromFile(const std::string& Path, bool IsStandardFont = true);
// 
// 		/// Get the font texture and vertex array for flexible rendering
// 		const sf::Texture* GetFontTexture(const std::size_t CharacterSize) const;
// 		
// 		/// Get the type of font we are using
// 		const TFontType& GetFontType() const;
// 
// 		void UpdateTextGeometry(const std::string& Text, const sf::Uint32 CharacterSize);
// 
// 		void Update() override;
// 		void Init() override;
// 		void Refresh() override {}
// 
// 	private:
// 		const TGlyph ExtractCharacter(const char Char, const sf::Uint32 CharacterSize) const;
// 
// 	private:
// 		sf::Font mStandardFont;
// 		std::shared_ptr<TSprite> mCustomFont;
// 		sf::VertexArray mFontVertexArray;
// 		TFontType mFontType;
// 
// 		/// Variables for our custom font
// 		mutable std::vector<TCharStruct> mCharMap;
// 		mutable sf::Uint16 mCharDefaultSize;
// 		mutable sf::Uint8 mCharWidth;
// 		mutable sf::Uint8 mCharHeight;
// 		sf::Uint8 mStyle;
// 
// 		friend class _TTextOld;
// 	};
// 
// 	struct TFontLoader
// 	{
// 		TFontLoader(const std::string& Path, bool IsStandardFont = true) :
// 			mPath(Path),
// 			mIsStandard(IsStandardFont)
// 		{
// 		}
// 
// 		TResource<TFont> operator() ()
// 		{
// 			std::unique_ptr<TFont> TempPtr = std::make_unique<TFont>();
// 			TempPtr->LoadFromFile(mPath, mIsStandard);
// 			return TempPtr;
// 		}
// 
// 	private:
// 		bool mIsStandard;
// 		std::string mPath;
// 	};
}
#pragma once

#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <memory>

#include "IComponent.h"
#include "TResource.h"
#include "TCharStruct.h"

namespace nne
{
	class TText;

	struct TFont : IComponent
	{
	public:
		using TGlyph = std::pair<sf::FloatRect, const TCharStruct&>;

		enum class TFontType : bool
		{
			CUSTOM = true,
			STANDARD = false
		};

		TFont();
		
		/// Data loading
		bool LoadFromFile(const std::string& Path, bool IsStandardFont = true);
		bool LoadFromMemory(const void* Data, std::size_t DataSize, bool IsStandardFont = true);
		bool LoadFromStream(sf::InputStream& Stream, bool IsStandardFont = true);

		/// Get the font texture and vertex array for flexible rendering
		const sf::Texture* GetFontTexture(const std::size_t CharacterSize) const;
		const sf::VertexArray& GetFontVertexArray() const;
		
		/// Get the type of font we are using
		const TFontType& GetFontType() const;

		void UpdateTextGeometry(const std::string& Text, const sf::Uint32 CharacterSize);

		void Update() override;
		void Init() override;
		void Refresh() override {}

	private:
		const TGlyph ExtractCharacter(const char Char, const sf::Uint32 CharacterSize) const;

	private:
		TResource<sf::Font> mStandardFont;
		TResource<sf::Texture> mCustomFont;
		sf::VertexArray mFontVertexArray;
		TFontType mFontType;

		/// Variables for our custom font
		const std::vector<TCharStruct> mCharMap;
		const sf::Uint16 mCharDefaultSize;
		const sf::Uint8 mCharWidth;
		const sf::Uint8 mCharHeight;
		sf::Uint8 mStyle;

		friend class TText;
	};
}
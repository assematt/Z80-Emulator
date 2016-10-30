#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <utility>

#include "IComponent.h"
#include "TTexture.h"
#include "TCharStruct.h"
#include "TRandom.h"

namespace nne
{
	

	struct TFont : nne::IComponent
	{
	public:
		enum TStyle : std::size_t
		{
			LINK,
			NORMAL,
			ACTIVE,
			INACTIVE
		};

		TFont();

		const std::pair<sf::FloatRect, const TCharStruct&> ExtractCharacter(const char Char) const;

		void Init() override;

		void Update() override {}
		
		void SetStyle(TStyle Style);

		void SetFontSize(sf::Uint16 Size);

		void SetText(const std::string& String);

		const TStyle& GetStyle() const;

		const sf::Uint16& GetFontSize() const;

		const sf::Uint16& GetCharacterDefaultSize() const;

		const std::string& GetText() const;

	private:
		void RenderText();

	private:
		std::shared_ptr<TTexture> mDrawableComponent;
		std::string mText;
		TStyle mStyle;

		const sf::Uint8 mCharWidth;
		const sf::Uint8 mCharHeight;

		const std::vector<TCharStruct> mCharMap;

		const sf::Uint16 mCharDefaultSize;
		sf::Uint16 mCharCurrentSize;
	};
}
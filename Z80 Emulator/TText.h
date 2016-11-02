#pragma once

#include <SFML/Graphics/Text.hpp>
#include "IComponent.h"
#include "TFont.h"
#include "TEntity.h"

namespace nne
{
	class TText : public IComponent
	{
	public:

		TText();

		void Init() final;
		void Update() final;
		void Refresh();

		void SetString(const std::string& String);

		void SetFont(const TFont& Font);

		void SetCharacterSize(unsigned int Size);

		void SetStyle(sf::Uint32 Style);
		
		void SetFillColor(const sf::Color& Color);

		void SetOutlineColor(const sf::Color& Color);

		void SetOutlineThickness(float Thickness);

		const sf::Text& GetDrawableText() const;

		const std::string& GetString() const;

		const TFont* GetFont() const;

		unsigned int GetCharacterSize() const;

		sf::Uint32 GetStyle() const;

		const sf::Color& GetFillColor() const;

		const sf::Color& GetOutlineColor() const;

		float GetOutlineThickness() const;

		sf::Vector2f findCharacterPos(std::size_t Index) const;

		sf::FloatRect GetLocalBounds() const;

		sf::FloatRect GetGlobalBounds() const;

	private:
		std::string mString;
		std::shared_ptr<sf::Text> mText;
		std::shared_ptr<TFont> mFont;
		bool mNeedsUpdate;
	};
}
#pragma once

#include <SFML/Config.hpp>

namespace nne
{
	struct TCharStruct
	{
		TCharStruct() = default;
		TCharStruct(char Char, sf::Uint8 Kerning);

		bool TCharStruct::operator!=(const int Char) const;
		bool TCharStruct::operator==(const int Char) const;

		char mCharCode;
		sf::Uint8 mCharWidth;
	};
}
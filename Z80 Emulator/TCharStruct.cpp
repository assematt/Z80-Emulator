#include "TCharStruct.h"

namespace nne
{

	bool TCharStruct::operator!=(const int Char) const
	{
		return !(Char == mCharCode);
	}

	bool TCharStruct::operator==(const int Char) const
	{
		return Char == mCharCode;
	}

	TCharStruct::TCharStruct(char Char, sf::Uint8 Kerning) :
		mCharCode(Char),
		mCharWidth(Kerning)
	{

	}

}
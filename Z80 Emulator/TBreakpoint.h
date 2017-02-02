#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Config.hpp>
#include <vector>

#include "TCacheManager.h"
#include "TValues.h"

namespace nne
{
	namespace debugger
	{
		using TCodeLine = sf::Uint32;

		struct TBreakpoint
		{
			TBreakpoint(const TMemoryAddress& MemoryAddress, const TCodeLine& CodeLine);

			operator const sf::Drawable& () const;

			explicit operator const TCodeLine& () const;

			operator const TMemoryAddress& () const;

			void setActive(const bool& IsActive);

			const bool& isActive() const;

		private:
			TCodeLine		mCodeLine;
			sf::Sprite		mSprite;
			TMemoryAddress	Position;
			bool			mIsActive;
		};

		using TBreakpoints = std::vector<TBreakpoint>;
	}
}
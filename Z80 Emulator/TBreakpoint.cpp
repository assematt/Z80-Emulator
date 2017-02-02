#include "TBreakpoint.h"

namespace nne
{
	namespace debugger
	{

		TBreakpoint::TBreakpoint(const TMemoryAddress& MemoryAddress, const TCodeLine& CodeLine) :
			Position(MemoryAddress),
			mCodeLine(CodeLine),
			mSprite(TCacheManager::getInstance().getResource<sf::Texture>("breakpoint"), { 0, 0, 12, 12 }),
			mIsActive(false)
		{
			mSprite.setPosition(4.f, 70.f + 24 * CodeLine);
		}

		TBreakpoint::operator const TCodeLine&() const
		{
			return mCodeLine;
		}

		TBreakpoint::operator const TMemoryAddress&() const
		{
			return Position;
		}

		void TBreakpoint::setActive(const bool& IsActive)
		{
			mIsActive = IsActive;

			mIsActive ? mSprite.setTextureRect({ 12, 0, 12, 12 }) : mSprite.setTextureRect({ 0, 0, 12, 12 });
		}

		const bool& TBreakpoint::isActive() const
		{
			return mIsActive;
		}

		TBreakpoint::operator const sf::Drawable&() const
		{
			return mSprite;
		}

	}
}
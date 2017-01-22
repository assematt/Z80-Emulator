#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "TZ80Component.h"
#include "TComplexText.h"
#include "TWidget.h"
#include "TValues.h"

namespace nne
{
	namespace tgui
	{
		class TCodeEditor : public TWidget
		{
		public:
			using Ptr = std::shared_ptr<TCodeEditor>;

			const sf::Color BreakpointsBarColor = { 0, 7, 13 };
			const sf::Color CodeLineBarColor = { 0, 21, 39 };
			const sf::Color MemoryDebuggerColor = { 0, 21, 39 };
			const sf::Color MainCodeWindowColor = { 0, 25, 46 };

			TCodeEditor();
			virtual ~TCodeEditor() = default;

			/// Set the character size
			void setCharacterSize(const std::size_t& CharacterSize);
			std::size_t getCharacterSize();

			/// Attach/Detach the source code
			void attachSourceCode(const TSourceCode& SourceCode);
			void detachSourceCode();
			

		protected:
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

			/// Update the button looks
			virtual void update(const sf::Time& ElapsedTime) override;

		private:

			/// Create a string that contains the line counter string
			std::string createLineCounterString(const sf::Uint32& Begin, const sf::Uint32& End) const;

			/// Create a string that contains the memory counter string
			std::string createMemoryCounterString(const TSourceCode& Source) const;

			/// Create a string that contains the memory counter string
			std::string createSourceCodeBytes(const TSourceCode& Source) const;

			/// Convert the source code from bytes to 
			std::string convertBytesToString(const TSourceCode& Source) const;

		private:
			std::size_t			mCharacterSize;
			const TSourceCode*	mSourceCode;
			sf::RectangleShape	mBreakpointsBarBackground;	// sf::RectangleShape object that stores the background of the breakpoints bar
			sf::RectangleShape	mCodeLineBarBackground;		// sf::RectangleShape object that stores the background of the code line
			sf::RectangleShape	mMemoryDebuggerBackground;	// sf::RectangleShape object that stores the background of memeory debugger code line
			sf::RectangleShape	mMainCodeWindowBackground;	// sf::RectangleShape object that stores the background of memeory debugger code line

			TComplexText		mCodeLinesCounter;			// TComplexText object that stores all the code lines
			TComplexText		mCodeMemoryCounter;			// TComplexText object that stores all the position of code lines in memory
			TComplexText		mCodeMemoryBytes;			// TComplexText object that stores all the position of code lines in memory
			TComplexText		mCodeSourceText;			// TComplexText object that stores the mnemonic version of the instructions
		};
	}
}
#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <unordered_set>

#include "TZ80Component.h"
#include "TComplexText.h"
#include "TBreakpoint.h"
#include "TWidget.h"
#include "TValues.h"

namespace nne
{
	namespace debugger
	{
		enum class TExecutionMode : sf::Uint8
		{
			STEP,
			NORMAL
		};
	}

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

			/// Functions to handle breakpoints
			void addBreakpoint(const TMemoryAddress& MemoryAddress, const debugger::TCodeLine& CodeLine);
			void removeBreakpoint(const TMemoryAddress& Position);
			debugger::TBreakpoint* getBreakpoint(const TMemoryAddress& Position);
			
			/// Functions to attach and detach a Z80Component to the editor
			void attachZ80(TZ80Component& Z80);
			void detachZ80();

			/// Function to change the size
			virtual void setSize(const sf::Vector2u& Size) override;

		protected:
			virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

			/// Update the button looks
			virtual void update(const sf::Time& ElapsedTime) override;


		protected:
			void onMouseClick(TWidget* Sender, const sf::Event& EventData);

			void onKeyPressUp(TWidget* Sender, const sf::Event& EventData);

		private:
			/// Attach/Detach the source code
			void updateSourceCodeText(const TSourceCode* SourceCode);

		private:
			/// Create a string that contains the line counter string
			std::string createLineCounterString(const sf::Uint32& Begin, const sf::Uint32& End) const;

			/// Create a string that contains the memory counter string
			std::string createMemoryCounterString(const TSourceCode& Source) const;

			/// Create a string that contains the memory counter string
			std::string createSourceCodeBytes(const TSourceCode& Source) const;

			/// Convert the source code from bytes to 
			std::string convertBytesToString(const TSourceCode& Source) const;

			/// 
			void assignCodeNumber(TSourceCode& SourceCode);
			
		private:
			TZ80Component*			mZ80Component;			// A pointer to the Z80Component
			mutable TSourceCode*	mSourceCode;			// Cache the source code	
			const T16BitRegister*	mPCRegister;			// Cache the value of the PC

			TMemoryAddress				mPausedPoint;		// Cache the position of the last point in which we stopped the application
			debugger::TBreakpoints		mBreakpoints;		// List of all the vectors
			debugger::TExecutionMode	mExecutionMode;		// The way we are executing the code, if normal or step by step

			std::size_t			mCharacterSize;
			sf::VertexArray		mLineDividers;
			sf::RectangleShape	mSelectedLine;				// sf::RectangleShape object that stores the background of the current selected line
			sf::RectangleShape	mBreakpointsBarBackground;	// sf::RectangleShape object that stores the background of the breakpoints bar
			sf::RectangleShape	mCodeMemoryDebuggerBackground;

			TComplexText		mCodeLinesCounter;			// TComplexText object that stores all the code lines
			TComplexText		mCodeMemoryCounter;			// TComplexText object that stores all the position of code lines in memory
			TComplexText		mCodeMemoryBytes;			// TComplexText object that stores all the position of code lines in memory
			TComplexText		mCodeSourceText;			// TComplexText object that stores the mnemonic version of the instructions
		};
	}
}

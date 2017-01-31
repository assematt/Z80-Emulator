#include "TCodeEditor.h"
#include "TCacheManager.h"

#include <sstream>
#include <iomanip>

#include "TPackageComponent.h"

namespace nne
{
	namespace tgui
	{

		TCodeEditor::TCodeEditor() :
			mSourceCode(nullptr),
			mCharacterSize(16u)
		{
			// Set some property for the breakpoints bar
			mBreakpointsBarBackground.setFillColor(BreakpointsBarColor);
			mBreakpointsBarBackground.setSize({ 20.f, 850.f });

			// Set some property for the selected line bar
			mSelectedLine.setSize({ 252.f, 24.f });
			mSelectedLine.setFillColor({ 0, 14, 26 });
			mSelectedLine.setPosition(20.f, 14.f);

			// Set some property for the line dividers
			mLineDividers.setPrimitiveType(sf::Lines);
			mLineDividers.append(sf::Vertex({ 81.f, 0.f }, { 128, 128,191 }));
			mLineDividers.append(sf::Vertex({ 81.f, 850.f }, { 128, 128,191 }));
			mLineDividers.append(sf::Vertex({ 273.f, 0.f }, sf::Color::White));
			mLineDividers.append(sf::Vertex({ 273.f, 850.f }, sf::Color::White));

			// Set some property for the memory debugger background
			mCodeMemoryDebuggerBackground.setFillColor({ 0, 21, 39 });
			mCodeMemoryDebuggerBackground.setPosition(20.f, 0.f);
			mCodeMemoryDebuggerBackground.setSize({ 253.f, 850.f });

			// Set some property for the memory debugger
			mMainCodeWindowBackground.setFillColor(MainCodeWindowColor);
			mMainCodeWindowBackground.setPosition(273.f, 0.f);
			mMainCodeWindowBackground.setSize({ 527.f, 850.f });

			// Set some property for the code lines text
			mCodeLinesCounter.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mCodeLinesCounter.setLeading(24);
			mCodeLinesCounter.setCharacterSize(mCharacterSize);
			mCodeLinesCounter.setFillColor(sf::Color::White);
			mCodeLinesCounter.setString(createLineCounterString(1u, 40u));
			mCodeLinesCounter.setPosition(32.f, 17.f);

			// Set some property for the position of code lines in memory
			mCodeMemoryCounter.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mCodeMemoryCounter.setLeading(24);
			mCodeMemoryCounter.setCharacterSize(mCharacterSize);
			mCodeMemoryCounter.setFillColor({ 191, 191, 191 });
			mCodeMemoryCounter.setString(createMemoryCounterString({}));
			mCodeMemoryCounter.setPosition(91.f, 17.f);

			// Set some property for source code memory bytes
			mCodeMemoryBytes.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mCodeMemoryBytes.setLeading(24);
			mCodeMemoryBytes.setCharacterSize(mCharacterSize);
			mCodeMemoryBytes.setFillColor({ 191, 191, 191 });
			mCodeMemoryBytes.setString(createSourceCodeBytes({}));
			mCodeMemoryBytes.setPosition(163.f, 17.f);

			// Set some property for source code memory bytes
			mCodeSourceText.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mCodeSourceText.setLeading(24);
			mCodeSourceText.setCharacterSize(mCharacterSize);
			mCodeSourceText.setFillColor({ 255, 255, 255 });
			mCodeSourceText.setString(convertBytesToString({}));
			mCodeSourceText.setPosition(383.f, 17.f);
		}

		void TCodeEditor::setCharacterSize(const std::size_t& CharacterSize)
		{
			mCharacterSize = CharacterSize;
		}

		std::size_t TCodeEditor::getCharacterSize()
		{
			return mCharacterSize;
		}
		
		void TCodeEditor::attachSourceCode(const TSourceCode& SourceCode)
		{
			mSourceCode = &SourceCode;

			mCodeMemoryBytes.setString(createSourceCodeBytes(SourceCode));
			mCodeMemoryCounter.setString(createMemoryCounterString(SourceCode));
			mCodeSourceText.setString(convertBytesToString(SourceCode));
		}

		void TCodeEditor::detachSourceCode()
		{
			mSourceCode = nullptr;
		}

		void TCodeEditor::attachProgramCounter(const T16BitRegister& PC)
		{
			mPCRegister = &PC;
		}

		void TCodeEditor::detachProgramCounter()
		{
			mPCRegister = nullptr;
		}

		void TCodeEditor::attachZ80(const TZ80Component& Z80)
		{
			mZ80Component = &Z80;

			attachProgramCounter(Z80.getRegisterCointainer().programCounter());
			attachSourceCode(Z80.getProgram());
		}

		void TCodeEditor::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			// Skip the rendering if we are not showing the widget
			if (!isVisible())
				return;

			// draw the base class
			TWidget::draw(Target, States);

			// Apply the widget transform
			States.transform *= getParentTransform();

			// draw this widget

			// Draw the backgrounds
			Target.draw(mCodeMemoryDebuggerBackground, States);
			Target.draw(mBreakpointsBarBackground, States);
			Target.draw(mMainCodeWindowBackground, States);
			Target.draw(mSelectedLine, States);
			Target.draw(mLineDividers, States);

			// Draw the text
			Target.draw(mCodeLinesCounter, States);
			Target.draw(mCodeMemoryCounter, States);
			Target.draw(mCodeMemoryBytes, States);
			Target.draw(mCodeSourceText, States);
		}

		void TCodeEditor::update(const sf::Time& ElapsedTime)
		{
			if (!mSourceCode || !mPCRegister || !mZ80Component->isRunning() || mZ80Component->getCurrentCycleMode() != TZ80Component::TMachineCycleMode::INSTRUCTION_FETCH)
				return;

			auto	Counter = 0u;
			auto	Index = 0u;
			auto&	Source = *mSourceCode;

			while (Counter < Source.size() && Source[Counter].InstructionPosition != mPCRegister->getInternalValue())
			{
				++Index;

				// Advance the program by the program size
				Counter += Source[Counter].InstructionSize;
			}

			mSelectedLine.setPosition(20.f, 14.f + 24 * Index);
		}

		std::string TCodeEditor::createLineCounterString(const sf::Uint32& Begin, const sf::Uint32& End) const
		{
			std::stringstream Result;

			for (auto Index = Begin; Index < End; ++Index)
				Result << std::setw(4) << Index << "\n";

			return Result.str();
		}

		std::string TCodeEditor::createMemoryCounterString(const TSourceCode& Source) const
		{
			if (Source.size() == 0)
				return std::string();

			std::stringstream Result;

			auto SourceSize = Source.size();
			auto SourcePos = 0;
			auto Counter = 0u;

			while (Counter < SourceSize)
			{
				// Print instruction
				// Small 5 bytes array that will contain the formatted position
				char FormattedCode[5];

				// Format the string
				sprintf_s(FormattedCode, "%04X", Source[Counter].InstructionPosition);

				// Add a new line char
				Result << FormattedCode << "\n";

				// Advance the program by the program size
				Counter += Source[Counter].InstructionSize;
			}

			return Result.str();
		}

		std::string TCodeEditor::createSourceCodeBytes(const TSourceCode& Source) const
		{
			if (Source.size() == 0)
				return std::string();

			std::stringstream Result;

			auto SourceSize = Source.size();
			auto Counter = 0u;

			while (Counter < SourceSize)
			{
				// Print instruction
				for (auto Index = 0; Index < Source[Counter].InstructionSize; ++Index)
				{
					// Small 3 bytes array that will contain the formatted instruction
					char FormattedCode[3];

					// Format the string
					sprintf_s(FormattedCode, "%02X", Source[Counter + Index].InstructionCode);

					// Put the formatted code in result sstring
					Result << FormattedCode << " ";
				}

				// Add a new line char
				Result << "\n";

				// Advance the program by the program size
				Counter += Source[Counter].InstructionSize;
			}

			return Result.str();
		}

		std::string TCodeEditor::convertBytesToString(const TSourceCode& Source) const
		{
			if (Source.size() == 0)
				return std::string();

			std::stringstream Result;

			auto SourceSize = Source.size();
			auto Counter = 0u;

			while (Counter < SourceSize)
			{
				// Get the instruction data
				auto Inst = std::find(InstructionSet.begin(), InstructionSet.end(), Source[Counter].InstructionCode);

				// Put the formatted code in result sstring
				Result << Source[Counter].InstructionName;

				// Print instruction
				switch (Source[Counter].InstructionSize)
				{
					case 2:
					{
						// Small 3 bytes array that will contain the formatted instruction
						char FormattedCode[4];

						// Format the string
						sprintf_s(FormattedCode, "%02XH", Source[Counter + 1].InstructionCode);

						// Put the formatted code in result sstring
						Result << FormattedCode << " ";
					} break;
					case 3:
					{
						// Small 3 bytes array that will contain the formatted instruction
						char FormattedCode[3];

						// Format the string
						sprintf_s(FormattedCode, "%02X", Source[Counter + 2].InstructionCode);

						Result << FormattedCode;

						// Put the formatted code in result sstring
						sprintf_s(FormattedCode, "%02X", Source[Counter + 1].InstructionCode);

						Result << FormattedCode << "H";
					} break;
				}

				// Add a new line char
				Result << "\n";

				// Advance the program by the program size
				Counter += Source[Counter].InstructionSize;
			}

			return Result.str();
		}

	}
}
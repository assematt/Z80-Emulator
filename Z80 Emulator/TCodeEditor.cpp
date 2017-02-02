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
			mCharacterSize(16u),
			mPausedPoint(InvalidMemoryAddress),
			mExecutionMode(debugger::TExecutionMode::NORMAL)
		{
			TWidget::setSize({ 800u, 850u });
			TWidget::setColor({ 0, 35, 64 });
			TWidget::setPosition(0.f, 0.f);

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
			
			// Set some property for the code lines text
			mCodeLinesCounter.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mCodeLinesCounter.setLeading(24);
			mCodeLinesCounter.setCharacterSize(mCharacterSize);
			mCodeLinesCounter.setFillColor(sf::Color::White);
			mCodeLinesCounter.setString(createLineCounterString(1u, 50u));
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

			// Attach events
			this->attachEvent(events::onMouseUp, std::bind(&TCodeEditor::onMouseClick, this, std::placeholders::_1, std::placeholders::_2));
			this->attachEvent(events::onKeyUp, std::bind(&TCodeEditor::onKeyPressUp, this, std::placeholders::_1, std::placeholders::_2));
		}

		void TCodeEditor::setCharacterSize(const std::size_t& CharacterSize)
		{
			mCharacterSize = CharacterSize;
		}

		std::size_t TCodeEditor::getCharacterSize()
		{
			return mCharacterSize;
		}
		
		void TCodeEditor::updateSourceCodeText(const TSourceCode* SourceCode)
		{
			if (SourceCode)
			{
				mCodeMemoryBytes.setString(createSourceCodeBytes(*SourceCode));
				mCodeMemoryCounter.setString(createMemoryCounterString(*SourceCode));
				mCodeSourceText.setString(convertBytesToString(*SourceCode));
			}
			else
			{
				mCodeMemoryBytes.setString(createSourceCodeBytes({}));
				mCodeMemoryCounter.setString(createMemoryCounterString({}));
				mCodeSourceText.setString(convertBytesToString({}));
			}
		}
		
		void TCodeEditor::addBreakpoint(const TMemoryAddress& MemoryAddress, const debugger::TCodeLine& CodeLine)
		{
			mBreakpoints.emplace_back(MemoryAddress, CodeLine);
		}

		void TCodeEditor::removeBreakpoint(const TMemoryAddress& Position)
		{
			auto It = std::find_if(mBreakpoints.cbegin(), mBreakpoints.cend(), [&] (const debugger::TBreakpoint& Breakpoint) {
				return Breakpoint == Position;
			});

			if (It != mBreakpoints.cend())
				mBreakpoints.erase(It);
		}

		nne::debugger::TBreakpoint* TCodeEditor::getBreakpoint(const TMemoryAddress& Position)
		{
			auto It = std::find_if(mBreakpoints.begin(), mBreakpoints.end(), [&] (const debugger::TBreakpoint& Breakpoint) {
				return Breakpoint == Position;
			});

			return It == mBreakpoints.end() ? nullptr : &(*It);
		}

		void TCodeEditor::attachZ80(TZ80Component& Z80)
		{
			// Save the Z80
			mZ80Component = &Z80;

			// Cache the PC
			mPCRegister = &Z80.getRegisterCointainer().programCounter();

			// Cache the source code
			mSourceCode = &const_cast<TSourceCode&>(Z80.getProgram());

			// Update the source code text
			updateSourceCodeText(&Z80.getProgram());

			// Assign the number of the source code
			assignCodeNumber(*mSourceCode);
		}

		void TCodeEditor::detachZ80()
		{
			// Reset the cached elements
			mZ80Component = nullptr;
			mPCRegister = nullptr;
			mSourceCode = nullptr;

			// Reset the source code Text
			updateSourceCodeText(nullptr);
		}

		void TCodeEditor::setSize(const sf::Vector2u& Size)
		{
			TWidget::setSize(Size);

			// Update the height of the breakpoints bar background
			mBreakpointsBarBackground.setSize({ 20.f, static_cast<float>(Size.y) });

			// Update the height of the divider bars
			mLineDividers[1].position.y = static_cast<float>(Size.y);
			mLineDividers[3].position.y = static_cast<float>(Size.y);

			// Update the height of the memory debugger
			mCodeMemoryDebuggerBackground.setSize({ 253.f, static_cast<float>(Size.y) });
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
			Target.draw(mSelectedLine, States);
			Target.draw(mLineDividers, States);

			// Draw the breakpoints
			for (auto& Breakpoint : mBreakpoints)
				Target.draw(Breakpoint);

			// Draw the text
			Target.draw(mCodeLinesCounter, States);
			Target.draw(mCodeMemoryCounter, States);
			Target.draw(mCodeMemoryBytes, States);
			Target.draw(mCodeSourceText, States);
		}

		void TCodeEditor::update(const sf::Time& ElapsedTime)
		{
			// Don't update the this widget if we haven't connected it to a z80 component and we aren't currently executing a INSTRUCTION_FETCH mcycle
			if (!mSourceCode || !mPCRegister || !mZ80Component->isRunning() || mZ80Component->getCurrentCycleMode() != TZ80Component::TMachineCycleMode::INSTRUCTION_FETCH)
				return;

			// Get the internal value of the PC register
			auto& PCValue = mPCRegister->getInternalValue();

			// Tries to get the instruction pointed by PC
			auto It = std::find_if(mSourceCode->cbegin(), mSourceCode->cend(), [&](const TInstruction& Instruction) {
				return Instruction.InstructionPosition == PCValue;
			});

			// If we find an instruction
			if (It != mSourceCode->cend())
			{
				// Move the selected line bar to highlight the current instruction
				mSelectedLine.setPosition(20.f, 14.f + 24 * It->InstructionCodeNumber);

				// If we are executing step by step
				if (mExecutionMode == debugger::TExecutionMode::STEP)
				{
					if (mPausedPoint == InvalidMemoryAddress)
					{
						// Pause the program execution
						mZ80Component->pauseExecution();

						// Cache the position in which the Z80 is paused
						mPausedPoint = PCValue;
					}
					else if (mPausedPoint != PCValue)
					{
						mPausedPoint = InvalidMemoryAddress;
					}
				}
				// If we are executing normally
				else if (mExecutionMode == debugger::TExecutionMode::NORMAL)
				{
					// Find if there is a breakpoint at this position
					auto Breakpoint = getBreakpoint(PCValue);

					// See if at this position we have a breakpoint and we haven't paused the Z80 yet (we can tell by the fact the mPausedPoint value is set to InvalidMemoryAddress)
					if (Breakpoint && mPausedPoint == InvalidMemoryAddress)
					{
						// Pause the program execution
						mZ80Component->pauseExecution();

						// Change the breakpoint sprite 
						Breakpoint->setActive(true);

						// Cache the position in which the Z80 is paused
						mPausedPoint = PCValue;
					}
					// If have resumed the CPU execution and we have passed the previously active breakpoint, reset the cached mPausedPoint
					else if (mPausedPoint != PCValue)
					{
						mPausedPoint = InvalidMemoryAddress;
					}
				}

				
			}
		}

		void TCodeEditor::onMouseClick(TWidget* Sender, const sf::Event& EventData)
		{
			// Only execute this code if we 
			if (!mBreakpointsBarBackground.getGlobalBounds().contains(EventData.mouseButton.x, EventData.mouseButton.y))
				return;

			// Find which
			auto	Counter = 0u;
			auto&	Source = *mSourceCode;

			while (Counter < Source.size())
			{
				auto& CodeLine = Source[Counter].InstructionCodeNumber;
				auto& InstructionPos = Source[Counter].InstructionPosition;

				sf::Vector2f Position = { 4.f, 70.f + 24 * CodeLine };
				sf::Vector2f Size = { 20.f, 24.f };
				sf::Vector2f MousePos = sf::Vector2f(EventData.mouseButton.x, EventData.mouseButton.y);
				
				if (sf::FloatRect(Position, Size).contains(MousePos))
				{
					getBreakpoint(InstructionPos) ? removeBreakpoint(InstructionPos) : addBreakpoint(InstructionPos, CodeLine);
					
					return;
				}

				// Advance the program by the program size
				Counter += Source[Counter].InstructionSize;
			}
		}
		
		void TCodeEditor::onKeyPressUp(TWidget* Sender, const sf::Event& EventData)
		{
			// If we press F7 when the program is halted in a brake point resume code execution
			if (EventData.key.code == sf::Keyboard::F7 && mZ80Component && !mZ80Component->isRunning())
			{
				// Resume program execution
				mZ80Component->resumeExecution();

				// Set to execute the program step by step
				mExecutionMode = debugger::TExecutionMode::NORMAL;

				// Tries to get the breakpoint at the current location
				if (auto Breakpoint = getBreakpoint(mPCRegister->getInternalValue()))
				{
					// Set the breakpoint as inactive
					Breakpoint->setActive(false);
				}
			}
			// If we press F8, we will execute the program step by step
			else if (EventData.key.code == sf::Keyboard::F8 && mZ80Component && !mZ80Component->isRunning())
			{
				// Resume program execution
				mZ80Component->resumeExecution();

				// Set to execute the program step by step
				mExecutionMode = debugger::TExecutionMode::STEP;

				// Tries to get the breakpoint at the current location
				if (auto Breakpoint = getBreakpoint(mPCRegister->getInternalValue()))
				{
					// Set the breakpoint as inactive
					Breakpoint->setActive(false);
				}
			}
			// If we press F8, we will execute the program normally
			else if (EventData.key.code == sf::Keyboard::F9 && mZ80Component && !mZ80Component->isRunning())
			{
				// Resume program execution
				mZ80Component->resumeExecution();

				// Set to execute the program step by step
				mExecutionMode = debugger::TExecutionMode::NORMAL;

				// Tries to get the breakpoint at the current location
				if (auto Breakpoint = getBreakpoint(mPCRegister->getInternalValue()))
				{
					// Set the breakpoint as inactive
					Breakpoint->setActive(false);
				}
			}
			
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

		void TCodeEditor::assignCodeNumber(TSourceCode& SourceCode)
		{
			// Find which
			auto	Counter = 0u;
			auto	Index = 0u;

			while (Counter < SourceCode.size())
			{
				SourceCode[Counter].InstructionCodeNumber = Index++;

				// Advance the program by the program size
				Counter += SourceCode[Counter].InstructionSize;
			}
		}

	}
}
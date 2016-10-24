#pragma once

#include "TInstruction.h"

/*
class TSourceParser
{
public:
	static std::pair<std::string, std::string> ParseInstruction(const std::string& String)
	{
		auto Result = std::make_pair<std::string, std::string>("", "");

		// Get the instruction command from the string
		auto InstructionCommandBegin = String.find_first_not_of(" ");
		auto InstructionCommandEnd = String.find_first_of(" ", InstructionCommandBegin);
		Result.first = String.substr(InstructionCommandBegin, InstructionCommandEnd - InstructionCommandBegin);

		// Get the instruction argument from the string
		auto InstructionArgumentBegin = String.find_first_not_of(" ", InstructionCommandEnd);
		auto InstructionArgumentEnd = String.find_last_of("ABCDEFGHIJKLMNOPQRSTUWXYZabcdefghijklmnopqrstuwxyz()");
		Result.second = String.substr(InstructionArgumentBegin, InstructionArgumentEnd - InstructionArgumentBegin + 1);

		return Result;
	}

	static TInstruction GetInstructionInfo(const std::string& Instruction, const std::string& Arguments)
	{
		TInstruction ReturnValue;

		// Get the number of argument
		auto NumberOfArgument = Arguments.find_first_of(',') == std::string::npos ? 1 : 2;

		// Get the arguments
		auto FirstArgument = NumberOfArgument == 1 ? Arguments : Arguments.substr(0, Arguments.find_first_of(','));
		auto SecondArgument = NumberOfArgument == 2 ? Arguments.substr(Arguments.find_first_not_of(", ", Arguments.find_first_of(','))) : "";

		return ReturnValue;
	}

	static TInstruction GetInstructionFromString(const std::string& String)
	{
		TInstruction Instruction;

		// Parse the command, first parameter is the instruction, second parameter is the arguments
		auto ParsedInstruction = ParseInstruction(String);

		// Return the instruction type
		return GetInstructionInfo(ParsedInstruction.first, ParsedInstruction.second);
	}

	void ParseSourceCode(std::vector<TInstruction> Instructions)
	{
		std::string SourceFile = "	ORG	0000H;\n\
									LD A, 00H; inizializzazione registro A\n\
									LD B, 00H; inizializzazione registro B\n\
									LD A, 08H; carica un dato nel registro A\n\
									LD B, 07H; carica un dato nel registro B\n\
									ADD	A, B;  esegue la somma tra A e B e salva il risultato nell’indirizzo A\n\
									END";

		FormatSource(SourceFile);

		// Read the code line by line
		std::size_t ScanPositionBegin = 0;
		std::size_t ScanPositionEnd = 0;

		while ((ScanPositionBegin = SourceFile.find_first_not_of('\n ', ScanPositionBegin)) != std::string::npos)
		{
			ScanPositionEnd = SourceFile.find_first_of('\n', ScanPositionBegin);

			auto Instruction = GetInstructionFromString(SourceFile.substr(ScanPositionBegin, ScanPositionEnd - ScanPositionBegin));

			ScanPositionBegin = ScanPositionEnd + 1;
		}


		std::size_t ScanPosition = 0;
		std::size_t EndPos = SourceFile.length();
		std::string InstructionString = "";

		// Scan the entire source code
		while (ScanPosition < EndPos)
		{
			InstructionString = "";

			while (SourceFile[ScanPosition] != ';' && ScanPosition < EndPos)
			{
				InstructionString += SourceFile[ScanPosition];

				++ScanPosition;
			}
		}
	}

	void FormatSource(std::string& Source)
	{
		// Replace all the tabs with a space
		std::replace(Source.begin(), Source.end(), '\t', ' ');

		// Remove all the comments
		std::size_t Begin = 0;
		while ((Begin = Source.find_first_of(';')) != std::string::npos)
		{
			std::size_t EndLine = Source.find_first_of('\n', Begin);
			Source.erase(Source.begin() + Begin, Source.begin() + EndLine);
		}

		// Put the entire source file in uppercase
		std::transform(Source.begin(), Source.end(), Source.begin(), ::toupper);
	}

private:
};*/
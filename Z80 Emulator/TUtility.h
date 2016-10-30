#pragma once

#include "TValues.h"

namespace nne
{
	namespace TUtility
	{
		inline TU16BitValue To16BitValue(TU8BitValue HighValue = 0, TU8BitValue LowValue = 0)
		{
			return HighValue << 8 | LowValue;
		}

		inline TU8BitValue GetUpper8Bit(const TU16BitValue& Value)
		{
			return Value >> 8;
		}
		inline TU8BitValue GetLower8Bit(const TU16BitValue& Value)
		{
			return Value & 0x00FF;
		}


		inline TU8BitValue GetUpperNible(const TU8BitValue& Value)
		{
			return Value >> 4;
		}
		inline TU8BitValue GetLowerNible(const TU8BitValue& Value)
		{
			return Value & 0xF0;
		}

		template <class T>
		inline bool ValueIsBetween(const T& Value, const T& LowBound, const T& HighBound, bool Esclusive = true)
		{
			return Esclusive ? Value > LowBound && Value < HighBound : Value >= LowBound && Value <= HighBound;
		}

		template <class T>
		inline const TU8BitValue GetBit(const T& Value, const TU8BitValue Position)
		{
			return (Value >> Position) & 1;
		}

		template <class T>
		inline void SetBit(T& Value, const TU8BitValue Position, const bool BitValue)
		{
			// Create the modifier mask
			auto Mask = 1 << Position;

			BitValue == 0 ? Value &= ~Mask : Value = (Value & ~Mask) | Mask;
		}

		inline bool IsSet(TU8BitValue& Bit)
		{
			return Bit == 1 ? true : false;
		}

		template <class T>
		inline bool CheckParity(const T& Value)
		{
			std::uint8_t Parity = 0;
			for (std::uint8_t NumberOfBit = 0; NumberOfBit < sizeof(Value); ++NumberOfBit)
			{
				(Value >> NumberOfBit) & 0xFE ? ++Parity : Parity;
			}

			return !(Parity & 1);
		}

		template <class T>
		inline TU8BitValue RotateLeft(T& Value)
		{
			// Get the 7th bit
			auto Bit = TUtility::GetBit(Value, 7);

			// Shift the value left by 1 bit
			Value <<= 1;

			// Return the value of the old 7th bit
			return Bit;
		}

		template <class T>
		inline TU8BitValue RotateRight(T& Value)
		{
			// Get the first bit
			auto Bit = TUtility::GetBit(Value, 7);

			// Shift the value right by 1 bit
			Value >>= 1;

			// Return the value of the old first bit
			return Bit;
		}
	
		template <class IDType>
		inline IDType GetUniqueID() noexcept
		{
			static IDType lastID = 0u;
			return lastID++;
		}

		template <class IDType, class T>
		inline IDType GetTypeID() noexcept
		{
			static IDType typeID = GetUniqueID<IDType>();
			return typeID;
		}
	}
}


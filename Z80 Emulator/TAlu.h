#pragma once

#include "TRegisterContainer.h"

namespace nne
{
	enum TFlags : TU8BitValue
	{
		/*
		C	- Carry Flag
		N	- Add/Subtract
		P/V	- Parity/Overflow Flag
		H	- Half Carry Flag
		Z	- Zero Flag
		S	- Sign Flag
		X	- Not Used
	
		Bit		 | 7 | 6 | 5 | 4 | 3 |  2  | 1 | 0
		Position | S | Z | X | H | X | P/V | N | C
	
		*/
	
		C = 0,	  // 0b00000001
		N = 1,	  // 0b00000010
		P_V = 2, // 0b00000100
		H = 4,	 // 0b00010000
		Z = 6,	  // 0b01000000
		S = 7,	  // 0b10000000
	};
	
	class TAlu
	{
	public:
	
		TAlu(TRegisterContainer& InternalRegister) :
			mRegistersReference(InternalRegister)
		{
		}
	
		/* Template where stupid stupid idea, but maybe I've fixed it */
	
		#pragma region ALU ADD
	
		template <class T>
		inline void aluAdd(T& Value) {}
		template <class T>
		inline void aluAdd(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		//	S is set if result is negative; otherwise, it is reset.
		//	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if carry from bit 3; otherwise, it is reset.
		// 	P/V is set if overflow; otherwise, it is reset.
		// 	N is reset.
		// 	C is set if carry from bit 7; otherwise, it is reset.
		template <>
		inline void aluAdd(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.accumulator();
	
			// Save the old value of the accumulator
			auto OldAccumulator = Accumulator;
	
			// Add the value to the register
			Accumulator += Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			checkCarryFromBit<TU8BitValue>(3, Accumulator, OldAccumulator) ? setFlag(TFlags::H) : resetFlag(TFlags::H);
	
			// P/V register
			checkOverflow(OldAccumulator, Accumulator) ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			resetFlag(TFlags::N);
	
			// C register
			Accumulator < OldAccumulator ? setFlag(TFlags::C) : resetFlag(TFlags::C);
		}
		template <>
		inline void aluAdd(TU8BitValue&& Value)
		{
			aluAdd(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		// 	S is not affected.
		// 	Z is not affected.
		// 	H is set if carry from bit 11; otherwise, it is reset.
		// 	P / V is not affected.
		// 	N is reset.
		// 	C is set if carry from bit 15; otherwise, it is reset.
		template <>
		inline void aluAdd(TU16BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& HLRegister = mRegistersReference.getRegister<nne::T16BitRegister>(TRegisterType::HL);
	
			// Save the old value of the accumulator
			auto OldHLRegister = HLRegister;
	
			// Add the value to the register
			HLRegister += Value;
	
			// H register
			checkCarryFromBit(11, HLRegister, OldHLRegister) ? setFlag(TFlags::H) : resetFlag(TFlags::H);
	
			// N register
			resetFlag(TFlags::N);
	
			// C register
			HLRegister < OldHLRegister ? setFlag(TFlags::C) : resetFlag(TFlags::C);
		}
		template <>
		inline void aluAdd(TU16BitValue&& Value)
		{
			aluAdd(Value);
		}
		#pragma endregion
	
		#pragma region ALU SUB
	
		template <class T>
		inline void aluSub(T& Value) {}
		template <class T>
		inline void aluSub(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 4; otherwise, it is reset.
		// 	P / V is set if overflow; otherwise, it is reset.
		// 	N is set.
		// 	C is set if borrow; otherwise, it is reset.
		template <>
		inline void aluSub(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.accumulator();
	
			// Save the old value of the accumulator
			auto OldAccumulator = Accumulator;
	
			// Add the value to the register
			Accumulator -= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			checkBorrowFromBit<TU8BitValue>(4, Accumulator, OldAccumulator) ? setFlag(TFlags::H) : resetFlag(TFlags::H);
	
			// P/V register
			checkOverflow(OldAccumulator, Accumulator) ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			setFlag(TFlags::N);
	
			// C register
			Accumulator > OldAccumulator ? setFlag(TFlags::C) : resetFlag(TFlags::C);
		}
		template <>
		inline void aluSub(TU8BitValue&& Value)
		{
			aluSub(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 12; otherwise, it is reset.
		// 	P/V is set if overflow; otherwise, it is reset.
		// 	N is set.
		// 	C is set if borrow; otherwise, it is reset.
		template <>
		inline void aluSub(TU16BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& HLRegister = mRegistersReference.getRegister<nne::T16BitRegister>(TRegisterType::HL);

			// Save the old value of the accumulator
			auto OldHLRegister = HLRegister;
	
			// Add the value to the register
			HLRegister -= Value;
	
			// S register
			HLRegister > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			HLRegister == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			checkBorrowFromBit<TU16BitValue>(12, HLRegister, OldHLRegister) ? setFlag(TFlags::H) : resetFlag(TFlags::H);
	
			// P/V register
			checkOverflow(OldHLRegister, HLRegister) ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			setFlag(TFlags::N);
	
			// C register
			HLRegister > OldHLRegister ? setFlag(TFlags::C) : resetFlag(TFlags::C);
		}
		template <>
		inline void aluSub(TU16BitValue&& Value)
		{
			aluSub(Value);
		}
		#pragma endregion
	
		#pragma region ALU INC
	
		template <class T>
		inline void aluInc(T& Value) {}
		template <class T>
		inline void aluInc(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if carry from bit 3; otherwise, it is reset.
		// 	P / V is set if r was 7Fh before operation; otherwise, it is reset.
		// 	N is reset.
		// 	C is not affected
		template <>
		inline void aluInc(TU8BitValue& Value)
		{	
			// Save the old value 
			auto OldValue = Value;

			// Increment the value
			++Value;
	
			// S register
			Value > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Value == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			checkCarryFromBit<TU8BitValue>(3, Value, OldValue) ? setFlag(TFlags::H) : resetFlag(TFlags::H);
	
			// P/V register
			OldValue == 0x7F ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			resetFlag(TFlags::N);
		}
		template <>
		inline void aluInc(TU8BitValue&& Value)
		{
			aluInc(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		template <>
		inline void aluInc(TU16BitValue& Value)
		{
			// Increment the value
			++Value;
		}
		template <>
		inline void aluInc(TU16BitValue&& Value)
		{
			aluInc(Value);
		}
		#pragma endregion
	
		#pragma region ALU DEC
	
		template <class T>
		inline void aluDec(T& Value) {}
		template <class T>
		inline void aluDec(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 4, otherwise, it is reset.
		// 	P / V is set if m was 80h before operation; otherwise, it is reset.
		// 	N is set.
		// 	C is not affected.
		template <>
		inline void aluDec(TU8BitValue& Value)
		{	
			// Save the old value 
			auto OldValue = Value;

			// Increment the value
			--Value;
	
			// S register
			Value > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Value == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			checkBorrowFromBit<TU8BitValue>(4, Value, OldValue) ? setFlag(TFlags::H) : resetFlag(TFlags::H);
	
			// P/V register
			OldValue == 0x80 ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			setFlag(TFlags::N);
		}
		template <>
		inline void aluDec(TU8BitValue&& Value)
		{
			aluDec(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		template <>
		inline void aluDec(TU16BitValue& Value)
		{
			// Decrement the value
			--Value;
		}
		template <>
		inline void aluDec(TU16BitValue&& Value)
		{
			aluDec(Value);
		}
		#pragma endregion
	
		#pragma region ALU AND
	
		template <class T>
		inline void aluAnd(T& Value) {}
		template <class T>
		inline void aluAnd(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set.
		// 	P/V is set if parity even; otherwise, it is reset.
		// 	N is reset.
		// 	C is reset.
		template <>
		inline void aluAnd(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.accumulator();
	
			// Add the value to the register
			Accumulator &= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			setFlag(TFlags::H);
	
			// P/V register
			checkParity(Accumulator) ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			resetFlag(TFlags::N);
	
			// C register
			resetFlag(TFlags::C);
		}
		template <>
		inline void aluAnd(TU8BitValue&& Value)
		{
			aluAnd(Value);
		}
		#pragma endregion
	
		#pragma region ALU OR
	
		template <class T>
		inline void aluOr(T& Value) {}
		template <class T>
		inline void aluOr(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is reset.
		// 	P/V is set if parity even; otherwise, it is reset.
		// 	N is reset.
		// 	C is reset.
		template <>
		inline void aluOr(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.accumulator();
	
			// Add the value to the register
			Accumulator |= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			resetFlag(TFlags::H);
	
			// P/V register
			checkParity(Accumulator) ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			resetFlag(TFlags::N);
	
			// C register
			resetFlag(TFlags::C);
		}
		template <>
		inline void aluOr(TU8BitValue&& Value)
		{
			aluOr(Value);
		}
		#pragma endregion
	
		#pragma region ALU XOR
	
		template <class T>
		inline void aluXor(T& Value) {}
		template <class T>
		inline void aluXor(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is reset.
		// 	P / V is set if parity even; otherwise, it is reset.
		// 	N is reset.
		// 	C is reset.
		template <>
		inline void aluXor(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.accumulator();
	
			// Add the value to the register
			Accumulator ^= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			resetFlag(TFlags::H);
	
			// P/V register
			checkParity(Accumulator) ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			resetFlag(TFlags::N);
	
			// C register
			resetFlag(TFlags::C);
		}
		template <>
		inline void aluXor(TU8BitValue&& Value)
		{
			aluXor(Value);
		}
		#pragma endregion
	
		#pragma region ALU CP
	
		template <class T>
		inline void aluCp(T& Value) {}
		template <class T>
		inline void aluCp(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 4; otherwise, it is reset.
		// 	P / V is set if overflow; otherwise, it is reset.
		// 	N is set.
		// 	C is set if borrow; otherwise, it is reset.
		template <>
		inline void aluCp(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.accumulator();
			auto& Flag = mRegistersReference.getRegister<nne::T8BitRegister>(TRegisterType::F);
	
			// Save the old value of the accumulator
			auto OldAccumulator = Accumulator;
	
			// Add the value to the register
			Accumulator -= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? setFlag(TFlags::S) : resetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? setFlag(TFlags::Z) : resetFlag(TFlags::Z);
	
			// H register
			checkBorrowFromBit(4, Accumulator, OldAccumulator) ? setFlag(TFlags::H) : resetFlag(TFlags::H);
	
			// P/V register
			checkOverflow(OldAccumulator, Accumulator) ? setFlag(TFlags::P_V) : resetFlag(TFlags::P_V);
	
			// N register
			setFlag(TFlags::N);
	
			// C register
			Accumulator > OldAccumulator ? setFlag(TFlags::C) : resetFlag(TFlags::C);
	
			// Since we are just comparing the two values, 
			Accumulator = OldAccumulator;
		}
		template <>
		inline void aluCp(TU8BitValue&& Value)
		{
			aluCp(Value);
		}
		#pragma endregion
	
		#pragma region Alu Rotate
	
		// Function to rotate the content of an 8 bit value left. The carry options allows to choose if we want to put the value of the carry or of the 7th bit in the first bit of the rotate 8 bit value
		template <class T>
		void rotateLeft(T& Value, bool Carry = true)
		{
			// Get the old value of the carry bit
			auto OldCarryBit = checkFlag(TFlags::C);
			auto Old7Bit = nne::TUtility::rotateLeft(Value);
	
			// Put the old 7 bit value in the carry
			Old7Bit ? setFlag(TFlags::C) : resetFlag(TFlags::C);
	
			// If Carry is true put the old value of the carry in the bit 0 otherwise put the 
			Carry ? nne::TUtility::setBit(Value, 0, OldCarryBit) : nne::TUtility::setBit(Value, 0, Old7Bit);
	
			// Reset the N and H flags
			resetFlag(TFlags::N | TFlags::H);
		}
	
		// Function to rotate the content of an 8 bit value right. The carry options allows to choose if we want to put the value of the carry or of the 0 bit in the 7th bit of the rotate 8 bit value
		template <class T>
		void rotateRight(T& Value, bool Carry = false)
		{
			// Get the old value of the carry bit
			auto OldCarryBit = checkFlag(TFlags::C);
			auto Old0Bit = nne::TUtility::rotateRight(Value);
	
			// Put the old 0 bit value in the carry
			Old0Bit ? setFlag(TFlags::C) : resetFlag(TFlags::C);
	
			// If Carry is true put the old value of the carry in the bit 0 otherwise put the 
			Carry ? nne::TUtility::setBit(Value, 7, OldCarryBit) : nne::TUtility::setBit(Value, 7, Old0Bit);
	
			// Reset the N and H flags
			resetFlag(TFlags::N | TFlags::H);
		}
		#pragma endregion
	
		/// Helper function for setting/resetting and checking the F register bit (CPU flags)
		inline void setFlag(const TU8BitValue Flag)
		{
			mRegistersReference.fLags() |= 1 << Flag;
		}
		inline void resetFlag(const TU8BitValue Flag)
		{
			mRegistersReference.fLags() &= ~(1 << Flag);
		}
		inline const bool checkFlag(const TU8BitValue Flag) const
		{		
			const auto& Flags = mRegistersReference.fLags();
	
			return (Flags >> Flag) & 1;
		}
	
		template <class T>
		bool checkParity(T Value)
		{
			std::uint8_t Parity = 0;
			for (std::uint8_t NumberOfBit = 0; NumberOfBit < sizeof(Value); ++NumberOfBit)
			{
				(Value >> NumberOfBit) & 0xFE ? ++Parity : Parity;
			}
	
			return !(Parity & 1);
		}
	
		template <class T, class S>
		bool checkCarryFromBit(std::uint8_t Bit, T OldValue, S NewValue)
		{
			// Create a bit mask
			int BitMask = 0xFF & (1 << (Bit + 1));
	
			OldValue &= BitMask;
			NewValue &= BitMask;
	
			return OldValue + NewValue > 0x0F;
		}
	
		template <class T, class S>
		bool checkBorrowFromBit(std::uint8_t Bit, T OldValue, S NewValue)
		{
			// Create a bit mask
			int BitMask = 0xFF & (0x80 >> (Bit - 1));
	
			OldValue &= BitMask;
			NewValue &= BitMask;
	
			return NewValue - OldValue < 0x0F;
		}
	
		template <class T, class S>
		bool checkOverflow(T OldValue, S NewValue)
		{
			// Check the overflow in the first 7 bit
			auto TempOldValue = OldValue & 0x7F;
			auto TempNewValue = NewValue & 0x7F;
	
			return TempOldValue > TempNewValue;
		}
	
	private:
		TRegisterContainer& mRegistersReference;
	};
}
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
		inline void AluAdd(T& Value) {}
		template <class T>
		inline void AluAdd(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		//	S is set if result is negative; otherwise, it is reset.
		//	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if carry from bit 3; otherwise, it is reset.
		// 	P/V is set if overflow; otherwise, it is reset.
		// 	N is reset.
		// 	C is set if carry from bit 7; otherwise, it is reset.
		template <>
		inline void AluAdd(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.Accumulator();
	
			// Save the old value of the accumulator
			auto OldAccumulator = Accumulator;
	
			// Add the value to the register
			Accumulator += Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			CheckCarryFromBit<TU8BitValue>(3, Accumulator, OldAccumulator) ? SetFlag(TFlags::H) : ResetFlag(TFlags::H);
	
			// P/V register
			CheckOverflow(OldAccumulator, Accumulator) ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			ResetFlag(TFlags::N);
	
			// C register
			Accumulator < OldAccumulator ? SetFlag(TFlags::C) : ResetFlag(TFlags::C);
		}
		template <>
		inline void AluAdd(TU8BitValue&& Value)
		{
			AluAdd(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		// 	S is not affected.
		// 	Z is not affected.
		// 	H is set if carry from bit 11; otherwise, it is reset.
		// 	P / V is not affected.
		// 	N is reset.
		// 	C is set if carry from bit 15; otherwise, it is reset.
		template <>
		inline void AluAdd(TU16BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& HLRegister = mRegistersReference.GetRegister<nne::T16BitRegister>(TRegisterType::HL);
	
			// Save the old value of the accumulator
			auto OldHLRegister = HLRegister;
	
			// Add the value to the register
			HLRegister += Value;
	
			// H register
			CheckCarryFromBit(11, HLRegister, OldHLRegister) ? SetFlag(TFlags::H) : ResetFlag(TFlags::H);
	
			// N register
			ResetFlag(TFlags::N);
	
			// C register
			HLRegister < OldHLRegister ? SetFlag(TFlags::C) : ResetFlag(TFlags::C);
		}
		template <>
		inline void AluAdd(TU16BitValue&& Value)
		{
			AluAdd(Value);
		}
		#pragma endregion
	
		#pragma region ALU SUB
	
		template <class T>
		inline void AluSub(T& Value) {}
		template <class T>
		inline void AluSub(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 4; otherwise, it is reset.
		// 	P / V is set if overflow; otherwise, it is reset.
		// 	N is set.
		// 	C is set if borrow; otherwise, it is reset.
		template <>
		inline void AluSub(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.Accumulator();
	
			// Save the old value of the accumulator
			auto OldAccumulator = Accumulator;
	
			// Add the value to the register
			Accumulator -= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			CheckBorrowFromBit<TU8BitValue>(4, Accumulator, OldAccumulator) ? SetFlag(TFlags::H) : ResetFlag(TFlags::H);
	
			// P/V register
			CheckOverflow(OldAccumulator, Accumulator) ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			SetFlag(TFlags::N);
	
			// C register
			Accumulator > OldAccumulator ? SetFlag(TFlags::C) : ResetFlag(TFlags::C);
		}
		template <>
		inline void AluSub(TU8BitValue&& Value)
		{
			AluSub(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 12; otherwise, it is reset.
		// 	P/V is set if overflow; otherwise, it is reset.
		// 	N is set.
		// 	C is set if borrow; otherwise, it is reset.
		template <>
		inline void AluSub(TU16BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& HLRegister = mRegistersReference.GetRegister<nne::T16BitRegister>(TRegisterType::HL);

			// Save the old value of the accumulator
			auto OldHLRegister = HLRegister;
	
			// Add the value to the register
			HLRegister -= Value;
	
			// S register
			HLRegister > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			HLRegister == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			CheckBorrowFromBit<TU16BitValue>(12, HLRegister, OldHLRegister) ? SetFlag(TFlags::H) : ResetFlag(TFlags::H);
	
			// P/V register
			CheckOverflow(OldHLRegister, HLRegister) ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			SetFlag(TFlags::N);
	
			// C register
			HLRegister > OldHLRegister ? SetFlag(TFlags::C) : ResetFlag(TFlags::C);
		}
		template <>
		inline void AluSub(TU16BitValue&& Value)
		{
			AluSub(Value);
		}
		#pragma endregion
	
		#pragma region ALU INC
	
		template <class T>
		inline void AluInc(T& Value) {}
		template <class T>
		inline void AluInc(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if carry from bit 3; otherwise, it is reset.
		// 	P / V is set if r was 7Fh before operation; otherwise, it is reset.
		// 	N is reset.
		// 	C is not affected
		template <>
		inline void AluInc(TU8BitValue& Value)
		{
			// Save the old value 
			auto OldValue = Value;
	
			// Increment the value
			++Value;
	
			// S register
			Value > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Value == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			CheckCarryFromBit<TU8BitValue>(3, Value, OldValue) ? SetFlag(TFlags::H) : ResetFlag(TFlags::H);
	
			// P/V register
			OldValue == 0x7F ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			ResetFlag(TFlags::N);
		}
		template <>
		inline void AluInc(TU8BitValue&& Value)
		{
			AluInc(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		template <>
		inline void AluInc(TU16BitValue& Value)
		{
			// Increment the value
			++Value;
		}
		template <>
		inline void AluInc(TU16BitValue&& Value)
		{
			AluInc(Value);
		}
		#pragma endregion
	
		#pragma region ALU DEC
	
		template <class T>
		inline void AluDec(T& Value) {}
		template <class T>
		inline void AluDec(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 4, otherwise, it is reset.
		// 	P / V is set if m was 80h before operation; otherwise, it is reset.
		// 	N is set.
		// 	C is not affected.
		template <>
		inline void AluDec(TU8BitValue& Value)
		{
			// Save the old value 
			auto OldValue = Value;
	
			// Increment the value
			--Value;
	
			// S register
			Value > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Value == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			CheckBorrowFromBit<TU8BitValue>(4, Value, OldValue) ? SetFlag(TFlags::H) : ResetFlag(TFlags::H);
	
			// P/V register
			OldValue == 0x80 ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			SetFlag(TFlags::N);
		}
		template <>
		inline void AluDec(TU8BitValue&& Value)
		{
			AluDec(Value);
		}
	
		/// 16 BIT SPECIALIZATION
		template <>
		inline void AluDec(TU16BitValue& Value)
		{
			// Decrement the value
			--Value;
		}
		template <>
		inline void AluDec(TU16BitValue&& Value)
		{
			AluDec(Value);
		}
		#pragma endregion
	
		#pragma region ALU AND
	
		template <class T>
		inline void AluAnd(T& Value) {}
		template <class T>
		inline void AluAnd(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set.
		// 	P/V is set if parity even; otherwise, it is reset.
		// 	N is reset.
		// 	C is reset.
		template <>
		inline void AluAnd(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.Accumulator();
	
			// Add the value to the register
			Accumulator &= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			SetFlag(TFlags::H);
	
			// P/V register
			CheckParity(Accumulator) ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			ResetFlag(TFlags::N);
	
			// C register
			ResetFlag(TFlags::C);
		}
		template <>
		inline void AluAnd(TU8BitValue&& Value)
		{
			AluAnd(Value);
		}
		#pragma endregion
	
		#pragma region ALU OR
	
		template <class T>
		inline void AluOr(T& Value) {}
		template <class T>
		inline void AluOr(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is reset.
		// 	P/V is set if parity even; otherwise, it is reset.
		// 	N is reset.
		// 	C is reset.
		template <>
		inline void AluOr(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.Accumulator();
	
			// Add the value to the register
			Accumulator |= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			ResetFlag(TFlags::H);
	
			// P/V register
			CheckParity(Accumulator) ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			ResetFlag(TFlags::N);
	
			// C register
			ResetFlag(TFlags::C);
		}
		template <>
		inline void AluOr(TU8BitValue&& Value)
		{
			AluOr(Value);
		}
		#pragma endregion
	
		#pragma region ALU XOR
	
		template <class T>
		inline void AluXor(T& Value) {}
		template <class T>
		inline void AluXor(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is reset.
		// 	P / V is set if parity even; otherwise, it is reset.
		// 	N is reset.
		// 	C is reset.
		template <>
		inline void AluXor(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.Accumulator();
	
			// Add the value to the register
			Accumulator ^= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			ResetFlag(TFlags::H);
	
			// P/V register
			CheckParity(Accumulator) ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			ResetFlag(TFlags::N);
	
			// C register
			ResetFlag(TFlags::C);
		}
		template <>
		inline void AluXor(TU8BitValue&& Value)
		{
			AluXor(Value);
		}
		#pragma endregion
	
		#pragma region ALU CP
	
		template <class T>
		inline void AluCp(T& Value) {}
		template <class T>
		inline void AluCp(T&& Value) {}
	
		/// 8 BIT SPECIALIZATION
		// 	S is set if result is negative; otherwise, it is reset.
		// 	Z is set if result is 0; otherwise, it is reset.
		// 	H is set if borrow from bit 4; otherwise, it is reset.
		// 	P / V is set if overflow; otherwise, it is reset.
		// 	N is set.
		// 	C is set if borrow; otherwise, it is reset.
		template <>
		inline void AluCp(TU8BitValue& Value)
		{
			// Get the value and address of the accumulator
			auto& Accumulator = mRegistersReference.Accumulator();
			auto& Flag = mRegistersReference.GetRegister<nne::T8BitRegister>(TRegisterType::F);
	
			// Save the old value of the accumulator
			auto OldAccumulator = Accumulator;
	
			// Add the value to the register
			Accumulator -= Value;
	
			// S register
			Accumulator > 0x7F /*(0111 1111)*/ ? SetFlag(TFlags::S) : ResetFlag(TFlags::S);
	
			// Z register
			Accumulator == 0 ? SetFlag(TFlags::Z) : ResetFlag(TFlags::Z);
	
			// H register
			CheckBorrowFromBit(4, Accumulator, OldAccumulator) ? SetFlag(TFlags::H) : ResetFlag(TFlags::H);
	
			// P/V register
			CheckOverflow(OldAccumulator, Accumulator) ? SetFlag(TFlags::P_V) : ResetFlag(TFlags::P_V);
	
			// N register
			SetFlag(TFlags::N);
	
			// C register
			Accumulator > OldAccumulator ? SetFlag(TFlags::C) : ResetFlag(TFlags::C);
	
			// Since we are just comparing the two values, 
			Accumulator = OldAccumulator;
		}
		template <>
		inline void AluCp(TU8BitValue&& Value)
		{
			AluCp(Value);
		}
		#pragma endregion
	
		#pragma region Alu Rotate
	
		// Function to rotate the content of an 8 bit value left. The carry options allows to choose if we want to put the value of the carry or of the 7th bit in the first bit of the rotate 8 bit value
		template <class T>
		void RotateLeft(T& Value, bool Carry = true)
		{
			// Get the old value of the carry bit
			auto OldCarryBit = CheckFlag(TFlags::C);
			auto Old7Bit = nne::TUtility::RotateLeft(Value);
	
			// Put the old 7 bit value in the carry
			Old7Bit ? SetFlag(TFlags::C) : ResetFlag(TFlags::C);
	
			// If Carry is true put the old value of the carry in the bit 0 otherwise put the 
			Carry ? nne::TUtility::SetBit(Value, 0, OldCarryBit) : nne::TUtility::SetBit(Value, 0, Old7Bit);
	
			// Reset the N and H flags
			ResetFlag(TFlags::N | TFlags::H);
		}
	
		// Function to rotate the content of an 8 bit value right. The carry options allows to choose if we want to put the value of the carry or of the 0 bit in the 7th bit of the rotate 8 bit value
		template <class T>
		void RotateRight(T& Value, bool Carry = false)
		{
			// Get the old value of the carry bit
			auto OldCarryBit = CheckFlag(TFlags::C);
			auto Old0Bit = nne::TUtility::RotateRight(Value);
	
			// Put the old 0 bit value in the carry
			Old0Bit ? SetFlag(TFlags::C) : ResetFlag(TFlags::C);
	
			// If Carry is true put the old value of the carry in the bit 0 otherwise put the 
			Carry ? nne::TUtility::SetBit(Value, 7, OldCarryBit) : nne::TUtility::SetBit(Value, 7, Old0Bit);
	
			// Reset the N and H flags
			ResetFlag(TFlags::N | TFlags::H);
		}
		#pragma endregion
	
		/// Helper function for setting/resetting and checking the F register bit (CPU flags)
		inline void SetFlag(const TU8BitValue Flag)
		{
			mRegistersReference.FLags() |= 1 << Flag;
		}
		inline void ResetFlag(const TU8BitValue Flag)
		{
			mRegistersReference.FLags() &= ~(1 << Flag);
		}
		inline const bool CheckFlag(const TU8BitValue Flag) const
		{		
			const auto& Flags = mRegistersReference.FLags();
	
			return (Flags >> Flag) & 1;
		}
	
		template <class T>
		bool CheckParity(T Value)
		{
			std::uint8_t Parity = 0;
			for (std::uint8_t NumberOfBit = 0; NumberOfBit < sizeof(Value); ++NumberOfBit)
			{
				(Value >> NumberOfBit) & 0xFE ? ++Parity : Parity;
			}
	
			return !(Parity & 1);
		}
	
		template <class T, class S>
		bool CheckCarryFromBit(std::uint8_t Bit, T OldValue, S NewValue)
		{
			// Create a bit mask
			int BitMask = 0xFF & (1 << (Bit + 1));
	
			OldValue &= BitMask;
			NewValue &= BitMask;
	
			return OldValue + NewValue > 0x0F;
		}
	
		template <class T, class S>
		bool CheckBorrowFromBit(std::uint8_t Bit, T OldValue, S NewValue)
		{
			// Create a bit mask
			int BitMask = 0xFF & (0x80 >> (Bit - 1));
	
			OldValue &= BitMask;
			NewValue &= BitMask;
	
			return NewValue - OldValue < 0x0F;
		}
	
		template <class T, class S>
		bool CheckOverflow(T OldValue, S NewValue)
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
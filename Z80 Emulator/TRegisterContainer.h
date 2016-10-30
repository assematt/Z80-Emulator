#pragma once

#include <array>

#include "TRegister.h"

namespace nne
{
	enum class TRegisterType : TU8BitValue
	{
		/*
		A is also called the "accumulator".It is the primary register for arithmetic operations and accessing memory.
		B is commonly used as an 8 - bit counter.
		C is used when you want to interface with hardware ports.
		D is not normally used in its 8 - bit form.Instead, it is used in conjuncture with E.
		E is again, not used in its 8 - bit form.
		F is known as the flags.It is the one register you cannot mess with on the byte level.It's uses will be discussed later in the Flags and Bit Level Instructions Section.
		H is another register not normally used in 8 - bit form.
		L is yet another register not normally used in 8 - bit form.
		I is the interrupt vector register.It is used by the calculator in the interrupt 2 mode.
		R is the refresh register.Although it holds no specific purpose to the OS, it can be used to generate random
	
		AF is not normally used because of the F, which is used to store flags.
		BC is used by instructions and code sections that operate on streams of bytes as a byte counter. Is also used as a 16 bit counter.
		DE holds the address of a memory location that is a destination.
		HL The general 16 bit register, it's used pretty much everywhere you use 16 bit registers. It's most common uses are for 16 bit arithmetic and storing the addresses of stuff (strings, pictures, labels, etc.). Note that HL usually holds the original address while DE holds the destination address.
		PC The program counter. It hold the point in memory that the processor is executing code from. No function can change PC except by actually jumping to a different location in memory.
		SP The stack pointer. It holds the current address of the top of the stack.
		IX is called an index register. It's use is similar to HL, but it's use should be limited as it has other purposes, and also runs slower than HL.
		IY is another index register. It holds the location of the system flags and is used when you want to change a certain flag. For now, we won't do anything to it.
		*/
	
		/// 8 Bit
		A = 20,
		B,
		C,
		D,
		E,
		F,
		H,
		L,
		I,
		R,
	
		/// 16 Bit
		AF = 0,
		BC,
		DE,
		HL,

		PC,
		SP,
		IX,
		IY,
	
		/// Alternate
		ALTAF,
		ALTBC,
		ALTDE,
		ALTHL,
	
		
	};
	
	class TRegisterContainer
	{
	public:
	
		/// Function to reset the state of the registers
		void Reset()
		{
			// Reset the input vector and refresh counter register
			mIRegister = 0;
			mRRegister = 0;
	
			// Reset the main register
			mAFRegister = 0;
			mBCRegister = 0;
			mDERegister = 0;
			mHLRegister = 0;
	
			// Reset the alternate register
			mAFAltRegister = 0;
			mBCAltRegister = 0;
			mDEAltRegister = 0;
			mHLAltRegister = 0;
	
			// Reset the program counter
			mPCRegister = 0;
	
			// Reset the index register
			mSPRegister = 0;
			mIXRegister = 0;
			mIYRegister = 0;
		}
	
		/// Function to get the value of the registers
		template <class T>
		inline T& GetRegister(const TRegisterType& Register);
		template <>
		inline nne::T8BitRegister& GetRegister(const TRegisterType& Register)
		{
			switch (Register)
			{
				// Accumulator
				case TRegisterType::A: return mAFRegister.GetHighOrderRegister();
	
				// BC register
				case TRegisterType::B: return mBCRegister.GetHighOrderRegister();
				case TRegisterType::C: return mBCRegister.GetLowOrderRegister();
	
				// DE register
				case TRegisterType::D: return mDERegister.GetHighOrderRegister();
				case TRegisterType::E: return mDERegister.GetLowOrderRegister();
	
				// Flag register
				case TRegisterType::F: return mAFRegister.GetLowOrderRegister();
	
				// HL register
				case TRegisterType::H: return mHLRegister.GetHighOrderRegister();
				case TRegisterType::L: return mHLRegister.GetLowOrderRegister();
	
				// Interrupt vector
				case TRegisterType::I: return mIRegister;
				case TRegisterType::R: return mRRegister;
			}
		}
		template <>
		inline nne::T16BitRegister& GetRegister(const TRegisterType& Register)
		{
			switch (Register)
			{
				// Main register
				case TRegisterType::AF: return mAFRegister;
				case TRegisterType::BC: return mBCRegister;
				case TRegisterType::DE: return mDERegister;
				case TRegisterType::HL: return mHLRegister;

				// Alternate register
				case TRegisterType::ALTAF: return mAFAltRegister;
				case TRegisterType::ALTBC: return mBCAltRegister;
				case TRegisterType::ALTDE: return mDEAltRegister;
				case TRegisterType::ALTHL: return mHLAltRegister;


				case TRegisterType::PC: return mPCRegister;
				case TRegisterType::SP: return mSPRegister;
				case TRegisterType::IX: return mIXRegister;
				case TRegisterType::IY: return mIYRegister;
			}
		}
	
		/// Function to get the value of the registers read-only
		template <class T>
		inline const T& GetRegister(const TRegisterType& Register) const;
		template <>
		inline const nne::T8BitRegister& GetRegister(const TRegisterType& Register) const
		{
			switch (Register)
			{
				// Accumulator
				case TRegisterType::A: return mAFRegister.GetHighOrderRegister();

				// BC register
				case TRegisterType::B: return mBCRegister.GetHighOrderRegister();
				case TRegisterType::C: return mBCRegister.GetLowOrderRegister();

				// DE register
				case TRegisterType::D: return mDERegister.GetHighOrderRegister();
				case TRegisterType::E: return mDERegister.GetLowOrderRegister();

				// Flag register
				case TRegisterType::F: return mAFRegister.GetLowOrderRegister();

				// HL register
				case TRegisterType::H: return mHLRegister.GetHighOrderRegister();
				case TRegisterType::L: return mHLRegister.GetLowOrderRegister();

				// Interrupt vector
				case TRegisterType::I: return mIRegister;
				case TRegisterType::R: return mRRegister;
			}
		}
		template <>
		inline const nne::T16BitRegister& GetRegister(const TRegisterType& Register) const
		{
			switch (Register)
			{
				// Main register
				case TRegisterType::AF: return mAFRegister;
				case TRegisterType::BC: return mBCRegister;
				case TRegisterType::DE: return mDERegister;
				case TRegisterType::HL: return mHLRegister;

				// Alternate register
				case TRegisterType::ALTAF: return mAFAltRegister;
				case TRegisterType::ALTBC: return mBCAltRegister;
				case TRegisterType::ALTDE: return mDEAltRegister;
				case TRegisterType::ALTHL: return mHLAltRegister;


				case TRegisterType::PC: return mPCRegister;
				case TRegisterType::SP: return mSPRegister;
				case TRegisterType::IX: return mIXRegister;
				case TRegisterType::IY: return mIYRegister;
			}
		}
	
		/// Helper function to get the program counter
		nne::T16BitRegister& ProgramCounter()
		{
			return mPCRegister;
		}
		const nne::T16BitRegister& ProgramCounter() const
		{
			return mPCRegister;
		}
	
		/// Helper function to get the stack pointer
		nne::T16BitRegister& StackPointer()
		{
			return mSPRegister;
		}
		const nne::T16BitRegister& StackPointer() const
		{
			return mSPRegister;
		}
	
		/// Helper function to get the accumulator
		nne::T8BitRegister& Accumulator()
		{
			return mAFRegister.GetHighOrderRegister();
		}
		const nne::T8BitRegister& Accumulator() const
		{
			return mAFRegister.GetHighOrderRegister();
		}
	
		/// Helper function to get the accumulator
		nne::T8BitRegister& FLags()
		{
			return mAFRegister.GetLowOrderRegister();
		}
		const nne::T8BitRegister& FLags() const
		{
			return mAFRegister.GetLowOrderRegister();
		}
	
	private:
		// Interrupt register
		nne::T8BitRegister mIRegister;
	
		// Memory refresh register
		nne::T8BitRegister mRRegister;
	
		// Main Registers
		nne::T16BitRegister mAFRegister;
		nne::T16BitRegister mBCRegister;
		nne::T16BitRegister mDERegister;
		nne::T16BitRegister mHLRegister;
		nne::T16BitRegister mPCRegister;
		nne::T16BitRegister mSPRegister;
		nne::T16BitRegister mIXRegister;
		nne::T16BitRegister mIYRegister;
	
		// Alternate Register
		nne::T16BitRegister mAFAltRegister;
		nne::T16BitRegister mBCAltRegister;
		nne::T16BitRegister mDEAltRegister;
		nne::T16BitRegister mHLAltRegister;


	};
}
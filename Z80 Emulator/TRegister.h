#pragma once

#include "TUtility.h"

namespace TInternals
{
	struct T8BitRegister
	{
		explicit T8BitRegister(TU8BitValue Data = 0);

		operator TU8BitValue();
		operator const TU8BitValue() const;

		/// Get the low order register
		TU8BitValue& GetInternalValue();
		const TU8BitValue& GetInternalValue() const;

		/// Simple assignment 
		T8BitRegister& operator =(const T8BitRegister& Right);
		T8BitRegister& operator =(const TU8BitValue& Right);

		/// Addition assignment
		T8BitRegister& operator +=(const T8BitRegister& Right);
		T8BitRegister& operator +=(const TU8BitValue& Right);

		/// Subtraction assignment 
		T8BitRegister& operator -=(const T8BitRegister& Right);
		T8BitRegister& operator -=(const TU8BitValue& Right);

		/// Pre-increment 	++a
		T8BitRegister& operator++();

		/// Pre-decrement 	--a
		T8BitRegister& operator--();

		/// Post-increment 	a++
		const T8BitRegister operator++(int);

		/// Post-decrement 	a--
		const T8BitRegister operator--(int);

		/// Assign bitwise and
		T8BitRegister& operator&=(const T8BitRegister& Right);
		T8BitRegister& operator&=(const TU8BitValue& Right);

		/// Assign xor
		T8BitRegister& operator^=(const T8BitRegister& Right);
		T8BitRegister& operator^=(const TU8BitValue& Right);

		/// Assign bitwise or
		T8BitRegister& operator|=(const T8BitRegister& Right);
		T8BitRegister& operator|=(const TU8BitValue& Right);

		/// Assign left shift
		T8BitRegister& operator<<=(const T8BitRegister& Right);
		T8BitRegister& operator<<=(const TU8BitValue& Right);

		/// Assign right shift
		T8BitRegister& operator>>=(const T8BitRegister& Right);
		T8BitRegister& operator>>=(const TU8BitValue& Right);

		/// Right shift
		T8BitRegister& operator >> (const TU8BitValue& Right);

		/// Left shift
		T8BitRegister& operator<<(const TU8BitValue& Right);

	private:
		TU8BitValue FullRegister;
	};

	union T16BitRegister
	{

		explicit T16BitRegister(TU16BitValue Data = 0);

		operator TU16BitValue();
		operator const TU16BitValue() const;

		/// Get the low order register
		T8BitRegister& GetLowOrderRegister();
		const T8BitRegister& GetLowOrderRegister() const;

		/// Get the high order register
		T8BitRegister& GetHighOrderRegister();
		const T8BitRegister& GetHighOrderRegister() const;

		/// Get the low order register
		TU16BitValue& GetInternalValue();
		const TU16BitValue& GetInternalValue() const;

		/// Simple assignment 
		T16BitRegister& operator =(const T16BitRegister& Right);
		T16BitRegister& operator =(const TU16BitValue& Right);

		/// Addition assignment
		T16BitRegister& operator +=(const T16BitRegister& Right);
		T16BitRegister& operator +=(const TU16BitValue& Right);

		/// Subtraction assignment 
		T16BitRegister& operator -=(const T16BitRegister& Right);
		T16BitRegister& operator -=(const TU16BitValue& Right);

		/// Pre-increment 	++a
		T16BitRegister& operator++();

		/// Pre-decrement 	--a
		T16BitRegister& operator--();

		/// Post-increment 	a++
		const T16BitRegister operator++(int);

		/// Post-decrement 	a--
		const T16BitRegister operator--(int);

		/// Assign bitwise and
		T16BitRegister &operator&=(const T16BitRegister& Right);
		T16BitRegister &operator&=(const TU16BitValue& Right);

		/// Assign xor
		T16BitRegister &operator^=(const T16BitRegister& Right);
		T16BitRegister &operator^=(const TU16BitValue& Right);

		/// Assign bitwise or
		T16BitRegister &operator|=(const T16BitRegister& Right);
		T16BitRegister &operator|=(const TU16BitValue& Right);

		/// Assign left shift
		T16BitRegister &operator<<=(const T16BitRegister& Right);
		T16BitRegister &operator<<=(const TU16BitValue& Right);

		/// Assign right shift
		T16BitRegister &operator>>=(const T16BitRegister& Right);
		T16BitRegister &operator>>=(const TU16BitValue& Right);

		/// Right shift
		T16BitRegister& operator >> (const TU8BitValue& Right);

		/// Left shift
		T16BitRegister& operator<<(const TU8BitValue& Right);
	private:
		TU16BitValue FullRegister;
		T8BitRegister PartialRegister[2];
	};
}
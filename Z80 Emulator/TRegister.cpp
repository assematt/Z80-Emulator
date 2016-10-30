#include "TRegister.h"

namespace nne
{
#pragma region T8BitRegister
	T8BitRegister& T8BitRegister::operator >> (const TU8BitValue& Right)
	{
		FullRegister = FullRegister >> Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator<<=(const TU8BitValue& Right)
	{
		FullRegister <<= Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator<<=(const T8BitRegister& Right)
	{
		FullRegister <<= Right.FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator|=(const TU8BitValue& Right)
	{
		FullRegister |= Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator|=(const T8BitRegister& Right)
	{
		FullRegister |= Right.FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator^=(const TU8BitValue& Right)
	{
		FullRegister ^= Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator^=(const T8BitRegister& Right)
	{
		FullRegister ^= Right.FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator&=(const TU8BitValue& Right)
	{
		FullRegister &= Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator&=(const T8BitRegister& Right)
	{
		FullRegister &= Right.FullRegister;

		return *this;
	}

	const T8BitRegister T8BitRegister::operator--(int)
	{
		auto Temp = *this;

		--(*this);

		return Temp;
	}

	T8BitRegister& T8BitRegister::operator--()
	{
		--this->FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator-=(const TU8BitValue& Right)
	{
		this->FullRegister -= Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator-=(const T8BitRegister& Right)
	{
		this->FullRegister -= Right.FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator+=(const TU8BitValue& Right)
	{
		this->FullRegister += Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator+=(const T8BitRegister& Right)
	{
		this->FullRegister += Right.FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator=(const TU8BitValue& Right)
	{
		this->FullRegister = Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator=(const T8BitRegister& Right)
	{
		this->FullRegister = Right.FullRegister;

		return *this;
	}

	T8BitRegister::T8BitRegister(TU8BitValue Data /*= 0*/) :
		FullRegister(Data)
	{

	}

	T8BitRegister::operator TU8BitValue()
	{
		return FullRegister;
	}

	T8BitRegister::operator const TU8BitValue() const
	{
		return FullRegister;
	}

	TU8BitValue& T8BitRegister::GetInternalValue()
	{
		return FullRegister;
	}

	const TU8BitValue& T8BitRegister::GetInternalValue() const
	{
		return FullRegister;
	}

	const T8BitRegister T8BitRegister::operator++(int)
	{
		auto Temp = *this;

		++(*this);

		return Temp;
	}

	T8BitRegister& T8BitRegister::operator++()
	{
		++this->FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator>>=(const T8BitRegister& Right)
	{
		FullRegister >>= Right.FullRegister;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator>>=(const TU8BitValue& Right)
	{
		FullRegister >>= Right;

		return *this;
	}

	T8BitRegister& T8BitRegister::operator<<(const TU8BitValue& Right)
	{
		FullRegister = FullRegister << Right;

		return *this;
	}
#pragma endregion

#pragma region T16BitRegister
	T16BitRegister& T16BitRegister::operator >> (const TU8BitValue& Right)
	{
		FullRegister = FullRegister >> Right;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator<<=(const TU16BitValue& Right)
	{
		FullRegister <<= Right;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator<<=(const T16BitRegister& Right)
	{
		FullRegister <<= Right.FullRegister;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator|=(const TU16BitValue& Right)
	{
		FullRegister |= Right;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator|=(const T16BitRegister& Right)
	{
		FullRegister |= Right.FullRegister;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator^=(const TU16BitValue& Right)
	{
		FullRegister ^= Right;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator^=(const T16BitRegister& Right)
	{
		FullRegister ^= Right.FullRegister;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator&=(const TU16BitValue& Right)
	{
		FullRegister &= Right;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator&=(const T16BitRegister& Right)
	{
		FullRegister &= Right.FullRegister;

		return *this;
	}

	const T16BitRegister T16BitRegister::operator--(int)
	{
		auto Temp = *this;

		--(*this);

		return Temp;
	}

	T16BitRegister& T16BitRegister::operator--()
	{
		--this->FullRegister;

		return *this;
	}

	T16BitRegister& T16BitRegister::operator-=(const TU16BitValue& Right)
	{
		this->FullRegister -= Right;

		return *this;
	}

	T16BitRegister& T16BitRegister::operator-=(const T16BitRegister& Right)
	{
		this->FullRegister -= Right.FullRegister;

		return *this;
	}

	T16BitRegister& T16BitRegister::operator+=(const TU16BitValue& Right)
	{
		this->FullRegister += Right;

		return *this;
	}

	T16BitRegister& T16BitRegister::operator+=(const T16BitRegister& Right)
	{
		this->FullRegister += Right.FullRegister;

		return *this;
	}

	T16BitRegister& T16BitRegister::operator=(const TU16BitValue& Right)
	{
		this->FullRegister = Right;

		return *this;
	}

	T16BitRegister& T16BitRegister::operator=(const T16BitRegister& Right)
	{
		this->FullRegister = Right.FullRegister;

		return *this;
	}

	T16BitRegister::T16BitRegister(TU16BitValue Data /*= 0*/) :
		FullRegister(Data)
	{

	}

	T16BitRegister::operator TU16BitValue()
	{
		return FullRegister;
	}

	T16BitRegister::operator const TU16BitValue() const
	{
		return FullRegister;
	}

	const T8BitRegister& T16BitRegister::GetLowOrderRegister() const
	{
		return PartialRegister[0];
	}

	T8BitRegister& T16BitRegister::GetLowOrderRegister()
	{
		return PartialRegister[0];
	}

	const T8BitRegister& T16BitRegister::GetHighOrderRegister() const
	{
		return PartialRegister[1];
	}

	T8BitRegister& T16BitRegister::GetHighOrderRegister()
	{
		return PartialRegister[1];
	}

	TU16BitValue& T16BitRegister::GetInternalValue()
	{
		return FullRegister;
	}

	const TU16BitValue& T16BitRegister::GetInternalValue() const
	{
		return FullRegister;
	}

	const T16BitRegister T16BitRegister::operator++(int)
	{
		auto Temp = *this;

		++(*this);

		return Temp;
	}

	T16BitRegister& T16BitRegister::operator++()
	{
		++this->FullRegister;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator>>=(const T16BitRegister& Right)
	{
		FullRegister >>= Right.FullRegister;

		return *this;
	}

	T16BitRegister & T16BitRegister::operator>>=(const TU16BitValue& Right)
	{
		FullRegister >>= Right;

		return *this;
	}

	T16BitRegister& T16BitRegister::operator<<(const TU8BitValue& Right)
	{
		FullRegister = FullRegister << Right;

		return *this;
	}
#pragma endregion
}

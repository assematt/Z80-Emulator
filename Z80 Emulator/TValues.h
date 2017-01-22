#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <array>
#include <vector>

// Unsigned 8 bit and 16 bit value and general value
namespace nne
{

	using TU8BitValue = std::uint8_t;
	using TU16BitValue = std::uint16_t;

	// Signed 8 bit and 16 bit value 
	using TS8BitValue = std::int8_t;
	using TS16BitValue = std::int16_t;

	// 
	using TMemoryAddress = std::uint16_t;
	using TMemory = std::vector<TU8BitValue>;

	template <class T>
	const sf::Vector2<T> InvalidVector = { std::numeric_limits<T>::max(), std::numeric_limits<T>::min() };
}

#define LOG_VALUE(Value) std::clog << __FILE__ << "[" << __LINE__ << "] " << ": " << Value << std::endl;
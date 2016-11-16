#pragma once

#include <cstdint>
#include <array>
#include <vector>

// Unsigned 8 bit and 16 bit value and general value
using TU8BitValue = std::uint8_t;
using TU16BitValue = std::uint16_t;

// Signed 8 bit and 16 bit value 
using TS8BitValue = std::int8_t;
using TS16BitValue = std::int16_t;

// 
using TMemoryAddress = std::uint16_t;
using TMemory = std::vector<TU8BitValue>;


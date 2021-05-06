#pragma once

#define USE_ECS 1
#define NNE 2

#define ENTITY_SYSTEM NNE 

#if ENTITY_SYSTEM == NNE
#define INCLUDE_COMPONENT_CLASS "IComponent.h"
#define INCLUDE_ENTITY_CLASS "TEntity.h"
#define BASE_COMPONENT_CLASS public nne::IComponent
#define MANAGER_CLASS nne::TManager
#define REFRESH_UPDATE_PARAMETER const sf::Time& ElapsedTime
#define ENTITY_PTR std::shared_ptr<TEntity>
#define CORRECT_MAKE_SHARED std::make_shared<nne::TEntity>()
#define FACTORY_ARGUMENT
#else
#define INCLUDE_COMPONENT_CLASS <ECS/Interfaces/_IComponent.h>
#define INCLUDE_ENTITY_CLASS <ECS/_TEntity.h>
#define BASE_COMPONENT_CLASS public nne::ecs::_IComponent
#define MANAGER_CLASS nne::ecs::_TManager
#define REFRESH_UPDATE_PARAMETER const float& ElapsedTime
#define ENTITY_PTR ecs::_TEntity::Ptr
#define CORRECT_MAKE_SHARED std::make_shared<ecs::_TEntity>(Manager, EntityID)
#define FACTORY_ARGUMENT ecs::_TManager& Manager, const ecs::_TEntity::ID& EntityID
#endif

#include <SFML/System/Vector2.hpp>
#include <type_traits>
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

	/// Invalid generic vector
	template <class T>
	const sf::Vector2<T> InvalidVector = { std::numeric_limits<T>::max(), std::numeric_limits<T>::min() };

	/// Invalid integral or floating point value
	template <class T>
	typename std::enable_if<std::is_arithmetic<T>::value, T>::type InvalidValue = std::numeric_limits<T>::max();;

	/// SOme type
	const auto InvalidID = InvalidValue<std::size_t>;
	const auto InvalidMemoryAddress = InvalidValue<TMemoryAddress>;
}

#define LOG_VALUE(Value) std::clog << __FILE__ << "[" << __LINE__ << "] " << ": " << Value << std::endl;
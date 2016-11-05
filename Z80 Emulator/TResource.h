#pragma once

#include <memory>

namespace nne
{
	/// Redefines the unique_ptr as a resource
	template <class Type>
	using TResource = std::unique_ptr<Type>;

	/// Generic resource that doesn't hold anything
	using TResourceGeneric = TResource<void*>;
}
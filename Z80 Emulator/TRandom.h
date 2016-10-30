#pragma once

#include <random>

namespace nne
{
	namespace TRandom
	{
		// T = class type
		// D = class distribution
		// G = class number generator
		// S = class randomizer
		template <class T, class D, class G, class S>
		struct TRandomGenerator
		{
			static T GenerateNumber(T Min, T Max)
			{
				// Return a random number
				return D()(G(S()()), D::param_type(Min, Max));
			}
		};

		using TRandomIntGenerator = TRandomGenerator<int, std::uniform_int_distribution<int>, std::mt19937, std::random_device>;
		using TRandomFloatGenerator = TRandomGenerator<float, std::uniform_real_distribution<float>, std::mt19937, std::random_device>;
	}
}
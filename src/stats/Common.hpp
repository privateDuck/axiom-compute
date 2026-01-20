#pragma once

#include <numeric>
#include <cmath>
#include <algorithm>
#include <type_traits>
#include "Concepts.hpp"

namespace stats {

	enum class Scope { Population, Sample };
	enum class Tail { TwoSided, Left, Right };
}
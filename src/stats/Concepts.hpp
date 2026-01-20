#pragma once

#include <concepts>
#include <ranges>

namespace stats {
	template<typename T>
	concept Numeric = std::is_arithmetic_v<T>;

	template<typename R>
	concept NumericRange = std::ranges::input_range<R> && Numeric<std::ranges::range_value_t<R>>;
}
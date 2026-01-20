#pragma once

#include <ankerl/unordered_dense.h>

using HashMapStrInt = ankerl::unordered_dense::map<std::string, uint64_t>;
using HashMapIntStr = ankerl::unordered_dense::map<uint64_t, std::string>;

template<typename T>
using HashMapIntT = ankerl::unordered_dense::map<uint64_t, T>;

template<typename T>
using HashMapStrT = ankerl::unordered_dense::map<std::string, T>;

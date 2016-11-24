/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  common.h -- Common defines and includes
*/

#ifndef _COMMON_H
#define _COMMON_H

#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using i32 = std::int32_t;
using u32 = std::uint32_t;
using f64 = double;

using str = std::string;

template <typename T>
using vec = std::vector<T>;

template <typename T>
std::ostream & operator<<(std::ostream & out, const std::vector<T> & v) {
    if(!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

#endif
